#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
//
// check for alliance | horde locations
// check for pvp areans level > 40 only.
// Send me home 30 minute cooldown
// shattrath level 60 - dalaran level 75 requirement

class teleportstone : public ItemScript
{
public:
	teleportstone() : ItemScript("teleportstone") { }

	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
	{
		if (player->IsInCombat())
		{
			player->GetSession()->SendNotification("You are in combat!");
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(0, "|cff1C6224|TInterface\\icons\\INV_Misc_Bag_FelclothBag:30|t Send Me Home|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		player->ADD_GOSSIP_ITEM(0, "|cff4169E1|TInterface\\icons\\Achievement_Leader_King_Varian_Wrynn:30|t Alliance Capital Cities|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
		player->ADD_GOSSIP_ITEM(0, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|t Horde Capital Cities|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
		player->ADD_GOSSIP_ITEM(0, "|cffFF0000|TInterface\\icons\\Achievement_FeatsOfStrength_Gladiator_10:30|t PvP Areas|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 60);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
		return true;
	}

	void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case GOSSIP_ACTION_INFO_DEF + 1: //Use Hearthstone.
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, 8690, true);
			player->GetSession()->SendNotification("You have been sent home.");
			break;

		case GOSSIP_ACTION_INFO_DEF + 20: //alliance locations
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(2, "|cff4169E1|TInterface\\icons\\Achievement_Leader_King_Varian_Wrynn.png:30|t Stormwind|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
			player->ADD_GOSSIP_ITEM(2, "|cff4169E1|TInterface\\icons\\Achievement_Leader_King_Magni_Bronzebeard.png:30|t Ironforge|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
			player->ADD_GOSSIP_ITEM(2, "|cff4169E1|TInterface\\icons\\Achievement_Leader_Tyrande_Whisperwind.png:30|t Darnassus|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
			player->ADD_GOSSIP_ITEM(2, "|cff4169E1|TInterface\\icons\\Achievement_Leader_Prophet_Velen.png:30|t The Exodar|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
			player->ADD_GOSSIP_ITEM(2, "|cffCC00CC|TInterface\\icons\\Ability_Druid_TwilightsWrath.png:30|t Shattrath City|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
			player->ADD_GOSSIP_ITEM(2, "|cffCC00CC|TInterface\\icons\\Ability_Mount_RocketMount.png:30|t Dalaran|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
			player->ADD_GOSSIP_ITEM(1, "|cffFF0000<- Close Menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
			break;

		case GOSSIP_ACTION_INFO_DEF + 40: //horde locations
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(2, "|cffFF0000|TInterface\\icons\\Achievement_Leader_ Thrall.png:30|t Orgrimmar|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41);
			player->ADD_GOSSIP_ITEM(2, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas.png:30|t Undercity|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42);
			player->ADD_GOSSIP_ITEM(2, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Cairne Bloodhoof.png:30|t Thunder Bluff|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43);
			player->ADD_GOSSIP_ITEM(2, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Lorthemar_Theron .png:30|t Silvermoon|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 44);
			player->ADD_GOSSIP_ITEM(2, "|cffCC00CC|TInterface\\icons\\Ability_Druid_TwilightsWrath.png:30|t Shattrath City|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 45);
			player->ADD_GOSSIP_ITEM(2, "|cffCC00CC|TInterface\\icons\\Ability_Mount_RocketMount.png:30|t Dalaran|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 46);
			player->ADD_GOSSIP_ITEM(1, "|cffFF0000<- Close Menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
			break;

		case GOSSIP_ACTION_INFO_DEF + 60: //pvp areas
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Ability_Rogue_Ambush.png:30|t Gurubashi Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 61);
			player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Ability_Rogue_MurderSpree.png:30|t Circle of Blood Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 62);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\Ability_TheBlackArrow.png:30|t The Ring of Trials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 63);
			player->ADD_GOSSIP_ITEM(1, "|cffFF0000<- Close Menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
			break;

			//Alliance locations
		case GOSSIP_ACTION_INFO_DEF + 21: // Stormwind
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 22: // Ironforge
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 23: // Darnassus
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 24: // Exodar
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 25: // Shattrath city
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 26: // Dalaran
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);
			break;

			//Horde locations
		case GOSSIP_ACTION_INFO_DEF + 41: // Orgrimmar
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1629.36f, -4373.39f, 31.2564f, 3.54839f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 42: // Undercity
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 43: // Thunderbluff
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -1277.37f, 124.804f, 131.287f, 5.22274f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 44: // Silvermoon
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 45: // Shattrath city
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 46: // Dalaran
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);
			break;
			//Pvp Areas
		case GOSSIP_ACTION_INFO_DEF + 61: //Gurubashi arena
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -13277.4f, 127.372f, 26.1418f, 1.11878f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 62: //Circle of Blood
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 2839.44f, 5930.17f, 11.1002f, 3.16284f);
			break;
		case GOSSIP_ACTION_INFO_DEF + 63: // The Ring of Trials
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1999.94f, 6581.71f, 11.32f, 2.36528f);
			break;

			//Misc
		case GOSSIP_ACTION_INFO_DEF + 999://menu sluit als dit uitgevoerd word.
			player->CLOSE_GOSSIP_MENU();
			break;
		}
	}
};

void AddSC_teleportstone()
{
	new teleportstone();
}