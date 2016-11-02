/*
-- Execute the following query
INSERT INTO world.item_template VALUES
(60001, 15, 0, -1, 'Summon NPC', 20629, 7, 8388608, 0, 1, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 14867, 0, 0, 0, 60000, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0,
0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 1, 'Right click on me.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0,
'item_summon_npc', 0, 0, 0, 0, 0, 12340);


*/

#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"
#include "Chat.h"


class item_summon_npc : public ItemScript
{
public:
	item_summon_npc() : ItemScript("item_summon_npc") { }

	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
	{
		if (player->IsInCombat())
		{
			player->GetSession()->SendNotification("You cannot use that item in combat");
			return true;
		}
		if (player->InArena())
		{
			player->GetSession()->SendNotification("You cannot use that item in Arena");
			return true;
		}
		if (player->InBattleground())
		{
			player->GetSession()->SendNotification("You cannot use that item in Battleground");
			return true;
		}
		//Replace 9999 with your Npc entry
		if (player->FindNearestCreature(96003, 50.0f))
		{
			player->GetSession()->SendNotification("Creature's Name can not be summoned because the same NPC is nearby.");
			return false;
		}

		//Replace 9999 with your Npc entry
		Creature* creature = player->SummonCreature(96003, player->GetPositionX(), player->GetPositionY() - 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60 * IN_MILLISECONDS);
		creature->Say("I'll be here for 1 minute.", LANG_UNIVERSAL, NULL);
		creature->GetMotionMaster()->MoveFollow(player, 0.2f, PET_FOLLOW_ANGLE, MOTION_SLOT_ACTIVE);
		return false;
	}

};

void AddSC_item_summon_npc() // Add to custom_script_loader.cpp normally
{
	new item_summon_npc;
}