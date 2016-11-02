/*----------------------------------------------*\
|			Coded By Obitus					     |
|			March 27, 2016					     |
|		Tested on TrinityCore 3.3.5			     |
|     Added distance check Thanks to Phil		 |
|	 This is 2.1 version without gossip          |
|  Sep 25, 2016 UPDATE: Added Internal cooldown  |
\*----------------------------------------------*/

//I was insipired by http://www.wowhead.com/spell=83968/mass-resurrection

/*
-- Execute this query in your DATABASE
INSERT INTO world.item_template (`entry`, `class`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `AllowableClass`, `AllowableRace`, `RequiredLevel`, `maxcount`, `stackable`, `delay`, `spellid_1`, `spellcooldown_1`, `spellcategorycooldown_1`, `spellcooldown_2`, `spellcategorycooldown_2`, `spellcooldown_3`, `spellcategorycooldown_3`, `spellcooldown_4`, `spellcategorycooldown_4`, `spellcooldown_5`, `spellcategorycooldown_5`, `description`, `RequiredDisenchantSkill`, `ScriptName`)
VALUES (192001, 15, -1, 'Mass Resurrection', 67105, 7, 0, 0, 1, 228800000, 34, -1, -1, 28, 1, 1, 1000, 14093, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 'Brings all dead party and raid members back to life with 35% health and 35% mana. Cannot be cast in combat or while in a battleground or arena.\r\nYou can use this item once every 10 minutes.', -1, 'item_res_group');

*/


#include "ScriptMgr.h"
#include "Player.h"
#include "Group.h"
#include "ObjectAccessor.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"
#include "Chat.h"

class item_res_group : public ItemScript
{
public:
	item_res_group() : ItemScript("item_res_group") { }

	bool DistanceIsValid(Position* playerWhoUsesTheItem, Position* deadPlayersInGroup)
	{
		if (std::abs(deadPlayersInGroup->GetPositionX() - playerWhoUsesTheItem->GetPositionX()) <= 91.44) //91.44 meters = 100 yards
			return true;
		return false;
	}

	bool OnUse(Player* playerWhoUsesTheItem, Item* item, SpellCastTargets const& /*targets*/)
	{
		SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(14093);
		int32 basepoints0 = 0;
		Group* group = playerWhoUsesTheItem->GetGroup();
		Group::MemberSlotList const &members = group->GetMemberSlots();

		//if (playerWhoUsesTheItem->HasAura(38910)) //Fel Weakness 
		//{
		//	playerWhoUsesTheItem->GetSession()->SendNotification("You must wait 15 minutes in order to use this item again");
		//	return false;
		//}

		if (playerWhoUsesTheItem->GetSpellHistory()->GetRemainingCooldown(spellInfo) > 600)
		{
			ChatHandler(playerWhoUsesTheItem->GetSession()).PSendSysMessage("You must wait %u minutes in order to use this item again.", playerWhoUsesTheItem->GetSpellHistory()->GetRemainingCooldown(spellInfo) / 1000 / 60);
			return false;
		}

		if (!playerWhoUsesTheItem->GetGroup())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("You are not in a group!");
			return false;
		}
		/* //What if the leader is dead?
		if (playerWhoUsesTheItem->GetGroup()->GetLeaderGUID() != playerWhoUsesTheItem->GetGUID())
		{
		playerWhoUsesTheItem->GetSession()->SendNotification("You are not the group leader!");
		return false;
		}
		*/
		if (playerWhoUsesTheItem->InBattleground())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("You cannot use this item in Battleground!");
			return false;
		}

		if (playerWhoUsesTheItem->InArena())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("You cannot use this item in Arena!");
			return false;
		}

		if (playerWhoUsesTheItem->IsInCombat())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("You cannot use this item in combat!");
			return false;
		}

		else
		{
			for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
			{
				Group::MemberSlot const &slot = *itr;
				Player* deadPlayersInGroup = ObjectAccessor::FindPlayer((*itr).guid);

				//skip if player/s is/are offline //--This check is mandatory. the server will crash without it
				if (!deadPlayersInGroup || deadPlayersInGroup->GetSession()->PlayerDisconnected())
				{
					playerWhoUsesTheItem->CLOSE_GOSSIP_MENU();
				}

				if (deadPlayersInGroup && deadPlayersInGroup->GetSession() && deadPlayersInGroup->isDead() && playerWhoUsesTheItem->GetSession() && DistanceIsValid(playerWhoUsesTheItem, deadPlayersInGroup))
				{
					deadPlayersInGroup->ResurrectPlayer(0.35f, false); //35% hp and mana, don't apply Resurrection Sickness
					deadPlayersInGroup->CastSpell(deadPlayersInGroup, 48171, true); //Visual Spell Resurrect (priest)
					deadPlayersInGroup->DurabilityRepairAll(0, 0, false); //Repair All - upon resurrection
					playerWhoUsesTheItem->GetSpellHistory()->AddCooldown(14093, 54452, std::chrono::seconds(600));
				}
			}
		}
		return true;
	}
};


void AddSC_item_res_group()
{
	new item_res_group;
}