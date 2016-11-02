/*
How to add a teleport location:
You go to the first menu. where you see "Mall", "Leveling Zone" etc.
You copy from there one line and paste it on the location you want it to appear ingame, when you talk to the creature.
After that, at the end, you add a number which is the link to the action of "what to do in case the player clicked that".
When you've done that, you roll DOOOOOOOOOOOOOOOOOOOOOOOOOOWN to nearly the end and you see there text like this:
case 248:
*text text text*
break;
(note: you must not forget "break;", it's important!

You will need to copy one of them and paste it after the break; from the case above you.
Now all what you need to do is to modify the teleport location and that's it.

How to edit teleport location:
On the second third of the each case (mostly), you will see this line (or something similar since each line on each case is different):
"player->TeleportTo(player->TeleportTo(530, -4216.87f, -12336.9f, 4.34247f, 6.02008f);"
What you will need to do is just to edit the numbers.

What each of them means?
player->TeleportTo(530,				-4216.87f,										-12336.9f,									4.34247f,				 6.02008f);
^					^												^											^						^
MapID		X location (MUST HAVE "f" AT THE END!				Y location (f at the end)				Z location (f at the end)			Orientation (f at the end!)


REMEMBER TO EDIT THE CUSTOM INSTANCES' CORDS AND THE MALL'S CORDS SINCE AT THE MOMENT THEY ALL LEAD TO THE SAME LOCATION.

CREDIT FOR CREATING THE SCRIPT GOES TO ULTARG.
Editing is credit for me, Zeraax.
*/

#include "ScriptPCH.h"

class Teleporter : public CreatureScript
{
public:
	Teleporter()
		: CreatureScript("Teleporter")
	{}

	void CreatureWhisperBasedOnBool(const char *text, Creature *creature, Player *player, bool value)
	{
		if (value)
			creature->MonsterWhisper(text, player, false);
	}

	void MainMenu(Player *player, Creature *creature)
	{
		if (player->getClass() == CLASS_DEATH_KNIGHT && player->getLevel() == 80 && !player->HasSpell(48778))
		{
			player->learnSpell(47476, false);
			player->learnSpell(50842, false);
			player->learnSpell(48778, false);
			player->learnSpell(48266, false);
			player->learnSpell(50977, false);
			player->learnSpell(49576, false);
			player->learnSpell(49142, false);
			player->learnSpell(46584, false);
			player->learnSpell(48263, false);
			player->learnSpell(48528, false);
			player->learnSpell(45524, false);
			player->learnSpell(48792, false);
			player->learnSpell(45529, false);
			player->learnSpell(56222, false);
			player->learnSpell(48743, false);
			player->learnSpell(56815, false);
			player->learnSpell(48707, false);
			player->learnSpell(48265, false);
			player->learnSpell(41999, false);
			player->learnSpell(47568, false);
			player->learnSpell(57623, false);
			player->learnSpell(49941, false);
			player->learnSpell(49909, false);
			player->learnSpell(42650, false);
			player->learnSpell(49930, false);
			player->learnSpell(49938, false);
			player->learnSpell(49895, false);
			player->learnSpell(49924, false);
			player->learnSpell(49921, false);
			player->learnSpell(3714, false);
			player->learnSpell(196, false);
			player->learnSpell(197, false);
			player->learnSpell(201, false);
			player->learnSpell(202, false);
			player->learnSpell(198, false);
			player->learnSpell(199, false);
			player->learnSpell(200, false);
			player->learnSpell(53428, false);
			player->learnSpell(54447, false);
			player->learnSpell(53331, false);
			player->learnSpell(54446, false);
			player->learnSpell(53323, false);
			player->learnSpell(53344, false);
			player->learnSpell(70164, false);
			player->learnSpell(62158, false);
			player->learnSpell(47528, false);
			player->learnSpell(61999, false);
			player->learnSpell(51425, false);

		}
		if (player->GetMapId() == 609)
		{
		}
		else{
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Mall]", GOSSIP_SENDER_MAIN, 13000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Teleport Menu]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[World Bosses]", GOSSIP_SENDER_MAIN, 710);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "[Custom Instances]", GOSSIP_SENDER_MAIN, 10000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "[Events]", GOSSIP_SENDER_MAIN, 555);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "[Leveling Zone]", GOSSIP_SENDER_MAIN, 11000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Tools]", GOSSIP_SENDER_MAIN, 23);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "[Sickness Removal]", GOSSIP_SENDER_MAIN, 103);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Nevermind...]", GOSSIP_SENDER_MAIN, 557);
		}
		player->SEND_GOSSIP_MENU(907, creature->GetGUID());
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		MainMenu(player, creature);

		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
	{
		if (player->IsInCombat())
		{
			creature->MonsterWhisper("You are in combat.", player, false);//
			player->CLOSE_GOSSIP_MENU();

			return true;
		}
		player->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
		case 0:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Mall]", GOSSIP_SENDER_MAIN, 13000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Teleport Menu]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[World Bosses]", GOSSIP_SENDER_MAIN, 710);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "[Custom Instances]", GOSSIP_SENDER_MAIN, 10000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "[Events]", GOSSIP_SENDER_MAIN, 555);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "[Leveling Zone]", GOSSIP_SENDER_MAIN, 11000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Tools]", GOSSIP_SENDER_MAIN, 23);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "[Sickness Removal]", GOSSIP_SENDER_MAIN, 103);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Nevermind...]", GOSSIP_SENDER_MAIN, 557);

			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 710: //World Bosses
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Custom Boss 1]", GOSSIP_SENDER_MAIN, 656);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Custom Boss 2]", GOSSIP_SENDER_MAIN, 657);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 10000:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Hellfire Citadel]", GOSSIP_SENDER_MAIN, 10001);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Gruul's Lair]", GOSSIP_SENDER_MAIN, 10002);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[The Obsidian Sanctum]", GOSSIP_SENDER_MAIN, 10003);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Utgarde Keep]", GOSSIP_SENDER_MAIN, 10004);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Zul Farrak]", GOSSIP_SENDER_MAIN, 10005);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Ragefire Chasm]", GOSSIP_SENDER_MAIN, 10006);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[The Stockade]", GOSSIP_SENDER_MAIN, 10007);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Sunwell Plateau]", GOSSIP_SENDER_MAIN, 10008);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Black Temple]", GOSSIP_SENDER_MAIN, 10009);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Icecrown Citadel Dungeons]", GOSSIP_SENDER_MAIN, 10010);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Gundrak]", GOSSIP_SENDER_MAIN, 10011);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[The Stockade]", GOSSIP_SENDER_MAIN, 10012);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Zul Aman]", GOSSIP_SENDER_MAIN, 10013);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Azjol Nerub]", GOSSIP_SENDER_MAIN, 10014);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

		case 555: // Events
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "[Event 1]", GOSSIP_SENDER_MAIN, 556);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "[Event 2]", GOSSIP_SENDER_MAIN, 558);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1: // Teleport Menu
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Home cities]", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Neutral cities]", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Zones]", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Dungeons]", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Raids]", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[PvP Areas]", GOSSIP_SENDER_MAIN, 22);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 2: // Zones
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Eastern Kingdoms]", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Kalimdor]", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Outland]", GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Northrend]", GOSSIP_SENDER_MAIN, 13);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 3: // Dungeons.
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Dungeons (1-60)]", GOSSIP_SENDER_MAIN, 14);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Dungeons (60-70)]", GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Dungeons (70-80)]", GOSSIP_SENDER_MAIN, 17);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 4: // Raids
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Level 60 Raids]", GOSSIP_SENDER_MAIN, 19);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Level 70 Raids]", GOSSIP_SENDER_MAIN, 20);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Level 80 Raids]", GOSSIP_SENDER_MAIN, 21);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 5: // Home Cities
			if (player->GetTeam() == HORDE)
			{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Orgrimmar", GOSSIP_SENDER_MAIN, 118);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Thunderbluff", GOSSIP_SENDER_MAIN, 119);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Silvermoon", GOSSIP_SENDER_MAIN, 120);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Undercity", GOSSIP_SENDER_MAIN, 121);
			}
			else{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stormwind", GOSSIP_SENDER_MAIN, 122);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ironforge", GOSSIP_SENDER_MAIN, 123);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Exodar", GOSSIP_SENDER_MAIN, 124);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Darnassus", GOSSIP_SENDER_MAIN, 125);
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 6: // Neutral Cities
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Dalaran", GOSSIP_SENDER_MAIN, 126);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shattrath", GOSSIP_SENDER_MAIN, 127);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Booty Bay", GOSSIP_SENDER_MAIN, 128);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Gadgetzan", GOSSIP_SENDER_MAIN, 129);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 7: // Zones - Eastern Kingdoms Page 1
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eversong Woods (1-10)", GOSSIP_SENDER_MAIN, 187);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tirisfal Glades (1-10)", GOSSIP_SENDER_MAIN, 188);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dun Morogh (1-10)", GOSSIP_SENDER_MAIN, 189);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Elwynn Forest (1-10)", GOSSIP_SENDER_MAIN, 190);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ghostlands (10-20)", GOSSIP_SENDER_MAIN, 191);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silverpine Forest (10-20)", GOSSIP_SENDER_MAIN, 192);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Westfall (10-20)", GOSSIP_SENDER_MAIN, 193);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Loch Modan (10-20)", GOSSIP_SENDER_MAIN, 194);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Redridge Mountains (15-25)", GOSSIP_SENDER_MAIN, 195);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Duskwood (18-30)", GOSSIP_SENDER_MAIN, 196);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[More]", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 8: // Zones - Eastern Kingdoms Page 2
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wetlands (20-30)", GOSSIP_SENDER_MAIN, 197);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hillsbrad Foothills (20-30)", GOSSIP_SENDER_MAIN, 198);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Alterac Mountains (30-40)", GOSSIP_SENDER_MAIN, 199);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Arathi Highlands (30-40)", GOSSIP_SENDER_MAIN, 200);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stranglethorn Vale (30-45)", GOSSIP_SENDER_MAIN, 201);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Swamp of Sorrows (35-45)", GOSSIP_SENDER_MAIN, 202);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Badlads (35-45)", GOSSIP_SENDER_MAIN, 203);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Hinterlands (40-50)", GOSSIP_SENDER_MAIN, 204);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Searing Gorge (43-50)", GOSSIP_SENDER_MAIN, 205);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blasted Lands (45-55)", GOSSIP_SENDER_MAIN, 206);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Burning Steppes (50-58)", GOSSIP_SENDER_MAIN, 207);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[More]", GOSSIP_SENDER_MAIN, 9);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 9: // Zones - Eastern Kingdoms Page 3
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Western Plaguelands (51-58)", GOSSIP_SENDER_MAIN, 208);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eastern Plaguelands (53-60)", GOSSIP_SENDER_MAIN, 209);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Deadwind Pass (55-60)", GOSSIP_SENDER_MAIN, 210);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 10: // Zones - Kalimdor Page 1
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Teldrassil (1-10)", GOSSIP_SENDER_MAIN, 211);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azuremyst Isle (1-10)", GOSSIP_SENDER_MAIN, 212);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Durotar (1-10)", GOSSIP_SENDER_MAIN, 213);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Mulgore (1-10)", GOSSIP_SENDER_MAIN, 214);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bloodmyst Isle (10-20)", GOSSIP_SENDER_MAIN, 215);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Darkshore (10-20)", GOSSIP_SENDER_MAIN, 216);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Barrens (10-25)", GOSSIP_SENDER_MAIN, 217);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stonetalon Mountains (15-27)", GOSSIP_SENDER_MAIN, 218);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ashenvale (18-30)", GOSSIP_SENDER_MAIN, 219);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Thousand Needles (25-35)", GOSSIP_SENDER_MAIN, 220);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[More]", GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 11: // Zones - Kalimdor Page 2
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Desolace (30-40)", GOSSIP_SENDER_MAIN, 221);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dustwallow Marsh (35-45)", GOSSIP_SENDER_MAIN, 222);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tanaris (40-50)", GOSSIP_SENDER_MAIN, 223);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Feralas (40-50)", GOSSIP_SENDER_MAIN, 224);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azshara (45-55)", GOSSIP_SENDER_MAIN, 225);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Felwood (48-55)", GOSSIP_SENDER_MAIN, 226);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Un'Goro Crater (45-55)", GOSSIP_SENDER_MAIN, 227);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silithus (55-60)", GOSSIP_SENDER_MAIN, 228);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Winterspring (55-60)", GOSSIP_SENDER_MAIN, 229);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Moonglade (1-80)", GOSSIP_SENDER_MAIN, 230);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 12: // Zones - Outlands
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hellfire Peninsula (58-63)", GOSSIP_SENDER_MAIN, 231);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zangarmarsh (60-64)", GOSSIP_SENDER_MAIN, 232);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Terokkar Forest (62-65)", GOSSIP_SENDER_MAIN, 233);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Nagrand (64-67)", GOSSIP_SENDER_MAIN, 234);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blade's Edge Mountains (65-68)", GOSSIP_SENDER_MAIN, 235);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shadowmoon Valley (67-70)", GOSSIP_SENDER_MAIN, 236);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Netherstorm (67-70)", GOSSIP_SENDER_MAIN, 237);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 13: // Zones - Northrend
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Borean Tundra (68-72)", GOSSIP_SENDER_MAIN, 238);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Howling Fjord (68-72)", GOSSIP_SENDER_MAIN, 239);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dragonblight (71-74)", GOSSIP_SENDER_MAIN, 240);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Grizzly Hills (73-75)", GOSSIP_SENDER_MAIN, 241);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Drak (74-77)", GOSSIP_SENDER_MAIN, 242);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sholazar Basin (76-78)", GOSSIP_SENDER_MAIN, 243);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Crystalsong Forest (77-80)", GOSSIP_SENDER_MAIN, 244);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Storm Peaks (77-80)", GOSSIP_SENDER_MAIN, 245);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Icecrown (77-80)", GOSSIP_SENDER_MAIN, 246);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wintergrasp (PvP)", GOSSIP_SENDER_MAIN, 247);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 14: // Dungeons 1-60 Page 1
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ragefire Chasm (15-21)", GOSSIP_SENDER_MAIN, 133);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Deadmines (15-21)", GOSSIP_SENDER_MAIN, 134);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wailing Caverns (15-25)", GOSSIP_SENDER_MAIN, 135);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shadowfang Keep (16-26)", GOSSIP_SENDER_MAIN, 136);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackfathom Deeps (20-30)", GOSSIP_SENDER_MAIN, 137);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stormwind Stockade (20-30)", GOSSIP_SENDER_MAIN, 138);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gnomeregan (24-34)", GOSSIP_SENDER_MAIN, 139);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Scarlet Monastery (26-42)", GOSSIP_SENDER_MAIN, 140);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Razorfen Kraul (30-40)", GOSSIP_SENDER_MAIN, 141);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[More]", GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 15: // Dungeons 1-60 Page 2
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Maraudon (30-46)", GOSSIP_SENDER_MAIN, 142);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Uldaman (35-45)", GOSSIP_SENDER_MAIN, 143);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Razorfen Downs (35-43)", GOSSIP_SENDER_MAIN, 144);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul Farrak (40-48)", GOSSIP_SENDER_MAIN, 145);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sunken Temple (45-55)", GOSSIP_SENDER_MAIN, 146);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dire Maul (50-60)", GOSSIP_SENDER_MAIN, 147);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackrock Depths (50-60)", GOSSIP_SENDER_MAIN, 148);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackrock Spire (50-60)", GOSSIP_SENDER_MAIN, 149);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Scholomance (50-60)", GOSSIP_SENDER_MAIN, 150);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stratholme (50-60)", GOSSIP_SENDER_MAIN, 151);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 14);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 16: // Dungeons 60-70
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hellfire Citadel (60-68)", GOSSIP_SENDER_MAIN, 152);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Coilfang Reservoir (60-69)", GOSSIP_SENDER_MAIN, 153);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Auchindoun (60-70)", GOSSIP_SENDER_MAIN, 154);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tempest Keep (60-70)", GOSSIP_SENDER_MAIN, 155);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Caverns of Time (60-70)", GOSSIP_SENDER_MAIN, 156);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magisters' Terrace (68-72)", GOSSIP_SENDER_MAIN, 157);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 17: // Dungeons 70-80 Page 1
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Utgarde Keep (70-72)", GOSSIP_SENDER_MAIN, 158);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Nexus (71-73)", GOSSIP_SENDER_MAIN, 159);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azjol-Nerub (72-74)", GOSSIP_SENDER_MAIN, 160);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Kahet: The Old Kingdom (73-75)", GOSSIP_SENDER_MAIN, 160);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Drak'Tharon Keep (74-76)", GOSSIP_SENDER_MAIN, 161);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Violet Hold (75-77)", GOSSIP_SENDER_MAIN, 162);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gundrak (76-78)", GOSSIP_SENDER_MAIN, 163);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Stone (77-79)", GOSSIP_SENDER_MAIN, 164);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Lightning (80)", GOSSIP_SENDER_MAIN, 164);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[More]", GOSSIP_SENDER_MAIN, 18);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 18: // Dungeons 70-80 Page 2
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Oculus (80)", GOSSIP_SENDER_MAIN, 159);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Culling of Stratholme (80)", GOSSIP_SENDER_MAIN, 156);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Utgarde Pinnacle (80)", GOSSIP_SENDER_MAIN, 165);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Trial of Champion (80)", GOSSIP_SENDER_MAIN, 166);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Pit of Saron (80)", GOSSIP_SENDER_MAIN, 167);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Forge of Souls (80)", GOSSIP_SENDER_MAIN, 167);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Reflection (80)", GOSSIP_SENDER_MAIN, 167);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 17);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 19: // Level 60 Raids
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Gurub", GOSSIP_SENDER_MAIN, 168);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Molten Core", GOSSIP_SENDER_MAIN, 169);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackwing Lair", GOSSIP_SENDER_MAIN, 170);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Qiraj Ruins", GOSSIP_SENDER_MAIN, 171);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Qiraj Temple", GOSSIP_SENDER_MAIN, 172);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 20: // Level 70 Raids
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Karazhan", GOSSIP_SENDER_MAIN, 173);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gruul's Lair", GOSSIP_SENDER_MAIN, 174);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magtheridon's Lair", GOSSIP_SENDER_MAIN, 175);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Aman", GOSSIP_SENDER_MAIN, 176);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Serpentshrine Cavern", GOSSIP_SENDER_MAIN, 177);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tempest Keep: The Eye", GOSSIP_SENDER_MAIN, 178);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hyjal", GOSSIP_SENDER_MAIN, 179);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Black Temple", GOSSIP_SENDER_MAIN, 180);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sunwell Plateau", GOSSIP_SENDER_MAIN, 181);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 21: // Level 80 Raids
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Naxxramas", GOSSIP_SENDER_MAIN, 182);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Obsidian Sanctum", GOSSIP_SENDER_MAIN, 183);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ruby Sanctum", GOSSIP_SENDER_MAIN, 183);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Vault of Archavon", GOSSIP_SENDER_MAIN, 184);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eye of Eternity", GOSSIP_SENDER_MAIN, 159);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ulduar", GOSSIP_SENDER_MAIN, 164);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Icecrown Citadel", GOSSIP_SENDER_MAIN, 185);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Trial of the Crusader", GOSSIP_SENDER_MAIN, 166);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Onyxia's Lair", GOSSIP_SENDER_MAIN, 186);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 22: // PvP Areas
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gurubashi Arena", GOSSIP_SENDER_MAIN, 130);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Circle of Blood Arena", GOSSIP_SENDER_MAIN, 131);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Ring of Trials", GOSSIP_SENDER_MAIN, 132);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 23: // Player Tools
			if (player->getClass() != CLASS_DEATH_KNIGHT)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Learn Spells]", GOSSIP_SENDER_MAIN, 100);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Professions]", GOSSIP_SENDER_MAIN, 24);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Repair]", GOSSIP_SENDER_MAIN, 101);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Maximize Weapon Skills]", GOSSIP_SENDER_MAIN, 102);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Riding]", GOSSIP_SENDER_MAIN, 117);
			if (player->getClass() == CLASS_DEATH_KNIGHT)
			{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Fix Talent Points (DK)]", GOSSIP_SENDER_MAIN, 252);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Reset Talent Points]", GOSSIP_SENDER_MAIN, 252);
			}
			else{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Reset Talent Points]", GOSSIP_SENDER_MAIN, 252);
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case 24: // Professions
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Alchemy]", GOSSIP_SENDER_MAIN, 104);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Blacksmithing]", GOSSIP_SENDER_MAIN, 105);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Enchanting]", GOSSIP_SENDER_MAIN, 106);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Engineering]", GOSSIP_SENDER_MAIN, 107);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Herbalism]", GOSSIP_SENDER_MAIN, 108);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Leatherworking]", GOSSIP_SENDER_MAIN, 109);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Mining]", GOSSIP_SENDER_MAIN, 110);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Skinning]", GOSSIP_SENDER_MAIN, 111);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Tailoring]", GOSSIP_SENDER_MAIN, 112);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Cooking]", GOSSIP_SENDER_MAIN, 113);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[First Aid]", GOSSIP_SENDER_MAIN, 114);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Fishing]", GOSSIP_SENDER_MAIN, 115);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Jewelcrafting]", GOSSIP_SENDER_MAIN, 116);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Inscription]", GOSSIP_SENDER_MAIN, 250);

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Back]", GOSSIP_SENDER_MAIN, 23);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Main Menu]", GOSSIP_SENDER_MAIN, 0);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 100: // Learn Spells
			if (player->getClass() == CLASS_WARRIOR && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(15590, false);
				player->learnSpell(264, false);
				player->learnSpell(5011, false);
				player->learnSpell(266, false);
				player->learnSpell(2567, false);

				player->learnSpell(2457, false);
				player->learnSpell(1715, false);
				player->learnSpell(2687, false);
				player->learnSpell(64382, false);
				player->learnSpell(3127, false);
				player->learnSpell(42459, false);
				player->learnSpell(18499, false);
				player->learnSpell(71, false);
				player->learnSpell(750, false);
				player->learnSpell(355, false);
				player->learnSpell(7384, false);
				player->learnSpell(72, false);
				player->learnSpell(694, false);
				player->learnSpell(2565, false);
				player->learnSpell(676, false);
				player->learnSpell(20230, false);
				player->learnSpell(12678, false);
				player->learnSpell(5246, false);
				player->learnSpell(1161, false);
				player->learnSpell(871, false);
				player->learnSpell(2458, false);
				player->learnSpell(20252, false);
				player->learnSpell(18449, false);
				player->learnSpell(1680, false);
				player->learnSpell(6552, false);
				player->learnSpell(11578, false);
				player->learnSpell(1719, false);
				player->learnSpell(34428, false);
				player->learnSpell(23920, false);
				player->learnSpell(3411, false);
				player->learnSpell(55694, false);
				player->learnSpell(47450, false);
				player->learnSpell(47465, false);
				player->learnSpell(47520, false);
				player->learnSpell(47436, false);
				player->learnSpell(47502, false);
				player->learnSpell(47437, false);
				player->learnSpell(47475, false);
				player->learnSpell(47440, false);
				player->learnSpell(47471, false);
				player->learnSpell(57755, false);
				player->learnSpell(57823, false);
				player->learnSpell(47488, false);
			}
			if (player->getClass() == CLASS_DRUID && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(15590, false);

				player->learnSpell(62600, false);
				player->learnSpell(16857, false);
				player->learnSpell(770, false);
				player->learnSpell(50464, false);
				player->learnSpell(5487, false);
				player->learnSpell(6795, false);
				player->learnSpell(18960, false);
				player->learnSpell(5229, false);
				player->learnSpell(8946, false);
				player->learnSpell(1066, false);
				player->learnSpell(768, false);
				player->learnSpell(2782, false);
				player->learnSpell(2893, false);
				player->learnSpell(5209, false);
				player->learnSpell(783, false);
				player->learnSpell(5225, false);
				player->learnSpell(22842, false);
				player->learnSpell(9634, false);
				player->learnSpell(20719, false);
				player->learnSpell(29166, false);
				player->learnSpell(22812, false);
				player->learnSpell(8983, false);
				player->learnSpell(18658, false);
				player->learnSpell(5215, false);
				player->learnSpell(33357, false);
				player->learnSpell(33786, false);
				player->learnSpell(26995, false);
				player->learnSpell(40120, false);
				player->learnSpell(62078, false);
				player->learnSpell(49802, false);
				player->learnSpell(53307, false);
				player->learnSpell(52610, false);
				player->learnSpell(48575, false);
				player->learnSpell(48476, false);
				player->learnSpell(48560, false);
				player->learnSpell(49803, false);
				player->learnSpell(48443, false);
				player->learnSpell(48562, false);
				player->learnSpell(53308, false);
				player->learnSpell(48577, false);
				player->learnSpell(53312, false);
				player->learnSpell(48574, false);
				player->learnSpell(48465, false);
				player->learnSpell(48570, false);
				player->learnSpell(48378, false);
				player->learnSpell(48480, false);
				player->learnSpell(48579, false);
				player->learnSpell(48477, false);
				player->learnSpell(50213, false);
				player->learnSpell(48461, false);
				player->learnSpell(48470, false);
				player->learnSpell(48467, false);
				player->learnSpell(48568, false);
				player->learnSpell(48451, false);
				player->learnSpell(48469, false);
				player->learnSpell(48463, false);
				player->learnSpell(48441, false);
				player->learnSpell(50763, false);
				player->learnSpell(49800, false);
				player->learnSpell(48572, false);
				player->learnSpell(48447, false);
			}
			if (player->getClass() == CLASS_HUNTER && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->learnSpell(200, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(15590, false);
				player->learnSpell(200, false);
				player->learnSpell(264, false);
				player->learnSpell(5011, false);
				player->learnSpell(266, false);

				player->learnSpell(8737, false);
				player->learnSpell(42459, false);
				player->learnSpell(3127, false);
				player->learnSpell(62757, false);
				player->learnSpell(75, false);
				player->learnSpell(1494, false);
				player->learnSpell(13163, false);
				player->learnSpell(5116, false);
				player->learnSpell(883, false);
				player->learnSpell(2641, false);
				player->learnSpell(6991, false);
				player->learnSpell(982, false);
				player->learnSpell(1515, false);
				player->learnSpell(19883, false);
				player->learnSpell(20736, false);
				player->learnSpell(2974, false);
				player->learnSpell(6197, false);
				player->learnSpell(1002, false);
				player->learnSpell(19884, false);
				player->learnSpell(5118, false);
				player->learnSpell(34074, false);
				player->learnSpell(781, false);
				player->learnSpell(3043, false);
				player->learnSpell(1462, false);
				player->learnSpell(19885, false);
				player->learnSpell(3045, false);
				player->learnSpell(19880, false);
				player->learnSpell(13809, false);
				player->learnSpell(13161, false);
				player->learnSpell(5384, false);
				player->learnSpell(1543, false);
				player->learnSpell(19878, false);
				player->learnSpell(3034, false);
				player->learnSpell(13159, false);
				player->learnSpell(19882, false);
				player->learnSpell(14327, false);
				player->learnSpell(19879, false);
				player->learnSpell(19263, false);
				player->learnSpell(14311, false);
				player->learnSpell(19801, false);
				player->learnSpell(34026, false);
				player->learnSpell(27044, false);
				player->learnSpell(34600, false);
				player->learnSpell(34477, false);
				player->learnSpell(53271, false);
				player->learnSpell(49071, false);
				player->learnSpell(53338, false);
				player->learnSpell(49067, false);
				player->learnSpell(48996, false);
				player->learnSpell(49052, false);
				player->learnSpell(49056, false);
				player->learnSpell(49045, false);
				player->learnSpell(49001, false);
				player->learnSpell(61847, false);
				player->learnSpell(60192, false);
				player->learnSpell(61006, false);
				player->learnSpell(48990, false);
				player->learnSpell(53339, false);
				player->learnSpell(49048, false);
				player->learnSpell(58434, false);
			}
			if (player->getClass() == CLASS_MAGE && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(201, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(5009, false);

				player->learnSpell(55342, false);
				player->learnSpell(27090, false);
				player->learnSpell(33717, false);
				player->learnSpell(42995, false);
				player->learnSpell(42926, false);
				player->learnSpell(42931, false);
				player->learnSpell(130, false);
				player->learnSpell(475, false);
				player->learnSpell(1953, false);
				player->learnSpell(12051, false);
				player->learnSpell(7301, false);
				player->learnSpell(2139, false);
				player->learnSpell(45438, false);
				player->learnSpell(12826, false);
				player->learnSpell(66, false);
				player->learnSpell(30449, false);
				player->learnSpell(42917, false);
				player->learnSpell(43015, false);
				player->learnSpell(43017, false);
				player->learnSpell(42985, false);
				player->learnSpell(43010, false);
				player->learnSpell(42833, false);
				player->learnSpell(42914, false);
				player->learnSpell(42859, false);
				player->learnSpell(42846, false);
				player->learnSpell(43012, false);
				player->learnSpell(42842, false);
				player->learnSpell(43008, false);
				player->learnSpell(43024, false);
				player->learnSpell(43020, false);
				player->learnSpell(43046, false);
				player->learnSpell(42897, false);
				player->learnSpell(43002, false);
				player->learnSpell(42921, false);
				player->learnSpell(42940, false);
				player->learnSpell(42956, false);
				player->learnSpell(61316, false);
				player->learnSpell(61024, false);
				player->learnSpell(42973, false);
				player->learnSpell(47610, false);
				player->learnSpell(58659, false);
				player->learnSpell(59634, false);

				if (player->GetTeam() == HORDE)
				{
					player->learnSpell(11418, false);
					player->learnSpell(11420, false);
					player->learnSpell(35717, false);
					player->learnSpell(35715, false);
					player->learnSpell(32267, false);
					player->learnSpell(11417, false);
					player->learnSpell(53142, false);
					player->learnSpell(3567, false);
					player->learnSpell(32272, false);
					player->learnSpell(3566, false);
					player->learnSpell(3563, false);
					player->learnSpell(53140, false);
					player->learnSpell(49358, false);
					player->learnSpell(49361, false);
				}
				else{
					player->learnSpell(10059, false);
					player->learnSpell(11419, false);
					player->learnSpell(32266, false);
					player->learnSpell(11416, false);
					player->learnSpell(53142, false);
					player->learnSpell(33690, false);
					player->learnSpell(33691, false);
					player->learnSpell(53140, false);
					player->learnSpell(3565, false);
					player->learnSpell(32271, false);
					player->learnSpell(3562, false);
					player->learnSpell(3561, false);
					player->learnSpell(49360, false);
					player->learnSpell(49359, false);
				}
			}
			if (player->getClass() == CLASS_PALADIN && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(3127, false);
				player->learnSpell(750, false);

				player->learnSpell(34769, false);
				player->learnSpell(20217, false);
				player->learnSpell(21084, false);
				player->learnSpell(20271, false);
				player->learnSpell(498, false);
				player->learnSpell(1152, false);
				player->learnSpell(53408, false);
				player->learnSpell(31789, false);
				player->learnSpell(62124, false);
				player->learnSpell(25780, false);
				player->learnSpell(1044, false);
				player->learnSpell(5502, false);
				player->learnSpell(19746, false);
				player->learnSpell(20164, false);
				player->learnSpell(10326, false);
				player->learnSpell(1038, false);
				player->learnSpell(53407, false);
				player->learnSpell(19752, false);
				player->learnSpell(20165, false);
				player->learnSpell(642, false);
				player->learnSpell(10278, false);
				player->learnSpell(20166, false);
				player->learnSpell(4987, false);
				player->learnSpell(6940, false);
				player->learnSpell(10308, false);
				player->learnSpell(25898, false);
				player->learnSpell(32223, false);
				player->learnSpell(53736, false);
				player->learnSpell(31884, false);
				player->learnSpell(54428, false);
				player->learnSpell(54043, false);
				player->learnSpell(48943, false);
				player->learnSpell(48936, false);
				player->learnSpell(48945, false);
				player->learnSpell(48938, false);
				player->learnSpell(48947, false);
				player->learnSpell(48817, false);
				player->learnSpell(48788, false);
				player->learnSpell(48932, false);
				player->learnSpell(48942, false);
				player->learnSpell(48801, false);
				player->learnSpell(48785, false);
				player->learnSpell(48934, false);
				player->learnSpell(48950, false);
				player->learnSpell(48819, false);
				player->learnSpell(48806, false);
				player->learnSpell(48782, false);
				player->learnSpell(53601, false);
				player->learnSpell(61411, false);
				player->learnSpell(34767, false);
			}
			if (player->getClass() == CLASS_PRIEST && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(198, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(5009, false);

				player->learnSpell(586, false);
				player->learnSpell(2053, false);
				player->learnSpell(528, false);
				player->learnSpell(6346, false);
				player->learnSpell(453, false);
				player->learnSpell(8129, false);
				player->learnSpell(605, false);
				player->learnSpell(552, false);
				player->learnSpell(6064, false);
				player->learnSpell(1706, false);
				player->learnSpell(988, false);
				player->learnSpell(10909, false);
				player->learnSpell(10890, false);
				player->learnSpell(60931, false);
				player->learnSpell(10955, false);
				player->learnSpell(34433, false);
				player->learnSpell(32375, false);
				player->learnSpell(48072, false);
				player->learnSpell(48169, false);
				player->learnSpell(48168, false);
				player->learnSpell(48170, false);
				player->learnSpell(48120, false);
				player->learnSpell(48063, false);
				player->learnSpell(48135, false);
				player->learnSpell(48171, false);
				player->learnSpell(48300, false);
				player->learnSpell(48071, false);
				player->learnSpell(48127, false);
				player->learnSpell(48113, false);
				player->learnSpell(48123, false);
				player->learnSpell(47951, false);
				player->learnSpell(48073, false);
				player->learnSpell(48078, false);
				player->learnSpell(53023, false);
				player->learnSpell(48161, false);
				player->learnSpell(48066, false);
				player->learnSpell(48162, false);
				player->learnSpell(48074, false);
				player->learnSpell(48068, false);
				player->learnSpell(48158, false);
				player->learnSpell(48125, false);
				player->learnSpell(64901, false);
			}
			if (player->getClass() == CLASS_ROGUE && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(201, false);
				player->learnSpell(196, false);
				player->learnSpell(198, false);
				player->learnSpell(201, false);
				player->learnSpell(1180, false);
				player->learnSpell(15590, false);
				player->learnSpell(264, false);
				player->learnSpell(5011, false);
				player->learnSpell(266, false);
				player->learnSpell(2567, false);

				player->learnSpell(3127, false);
				player->learnSpell(8647, false);
				player->learnSpell(1784, false);
				player->learnSpell(921, false);
				player->learnSpell(1776, false);
				player->learnSpell(1766, false);
				player->learnSpell(1804, false);
				player->learnSpell(51722, false);
				player->learnSpell(1725, false);
				player->learnSpell(2836, false);
				player->learnSpell(1833, false);
				player->learnSpell(1842, false);
				player->learnSpell(2094, false);
				player->learnSpell(1860, false);
				player->learnSpell(6774, false);
				player->learnSpell(26669, false);
				player->learnSpell(8643, false);
				player->learnSpell(11305, false);
				player->learnSpell(26889, false);
				player->learnSpell(31224, false);
				player->learnSpell(5938, false);
				player->learnSpell(51724, false);
				player->learnSpell(57934, false);
				player->learnSpell(48674, false);
				player->learnSpell(48659, false);
				player->learnSpell(48668, false);
				player->learnSpell(48672, false);
				player->learnSpell(48691, false);
				player->learnSpell(48657, false);
				player->learnSpell(57993, false);
				player->learnSpell(51723, false);
				player->learnSpell(48676, false);
				player->learnSpell(48638, false);
			}
			if (player->getClass() == CLASS_SHAMAN && player->getLevel() == 80)
			{
				if (!player->HasItemCount(5175, 1, true))
					player->AddItem(5175, 1);
				if (!player->HasItemCount(5176, 1, true))
					player->AddItem(5176, 1);
				if (!player->HasItemCount(5177, 1, true))
					player->AddItem(5177, 1);
				if (!player->HasItemCount(5178, 1, true))
					player->AddItem(5178, 1);
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(15590, false);

				player->learnSpell(8737, false);
				player->learnSpell(66844, false);
				player->learnSpell(66843, false);
				player->learnSpell(66842, false);
				player->learnSpell(32182, false);
				player->learnSpell(30671, false);
				player->learnSpell(2484, false);
				player->learnSpell(526, false);
				player->learnSpell(57994, false);
				player->learnSpell(8143, false);
				player->learnSpell(2645, false);
				player->learnSpell(2870, false);
				player->learnSpell(8166, false);
				player->learnSpell(131, false);
				player->learnSpell(10399, false);
				player->learnSpell(6196, false);
				player->learnSpell(546, false);
				player->learnSpell(556, false);
				player->learnSpell(8177, false);
				player->learnSpell(20608, false);
				player->learnSpell(36936, false);
				player->learnSpell(8012, false);
				player->learnSpell(8512, false);
				player->learnSpell(6495, false);
				player->learnSpell(8170, false);
				player->learnSpell(3738, false);
				player->learnSpell(2062, false);
				player->learnSpell(2894, false);
				player->learnSpell(57960, false);
				player->learnSpell(49276, false);
				player->learnSpell(49236, false);
				player->learnSpell(58734, false);
				player->learnSpell(58582, false);
				player->learnSpell(58753, false);
				player->learnSpell(49231, false);
				player->learnSpell(49238, false);
				player->learnSpell(49277, false);
				player->learnSpell(55459, false);
				player->learnSpell(49271, false);
				player->learnSpell(51994, false);
				player->learnSpell(61657, false);
				player->learnSpell(58739, false);
				player->learnSpell(49233, false);
				player->learnSpell(58656, false);
				player->learnSpell(58790, false);
				player->learnSpell(58745, false);
				player->learnSpell(58796, false);
				player->learnSpell(58757, false);
				player->learnSpell(49273, false);
				player->learnSpell(51514, false);
				player->learnSpell(60043, false);
				player->learnSpell(49281, false);
				player->learnSpell(58774, false);
				player->learnSpell(58749, false);
				player->learnSpell(58704, false);
				player->learnSpell(58643, false);
				player->learnSpell(58804, false);
			}
			if (player->getClass() == CLASS_WARLOCK && player->getLevel() == 80)
			{
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(201, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(5009, false);

				player->learnSpell(1710, false);
				player->learnSpell(48020, false);
				player->learnSpell(59671, false);
				player->learnSpell(688, false);
				player->learnSpell(696, false);
				player->learnSpell(697, false);
				player->learnSpell(5697, false);
				player->learnSpell(698, false);
				player->learnSpell(712, false);
				player->learnSpell(126, false);
				player->learnSpell(5138, false);
				player->learnSpell(5500, false);
				player->learnSpell(132, false);
				player->learnSpell(691, false);
				player->learnSpell(18647, false);
				player->learnSpell(11719, false);
				player->learnSpell(1122, false);
				player->learnSpell(17928, false);
				player->learnSpell(6215, false);
				player->learnSpell(18540, false);
				player->learnSpell(23161, false);
				player->learnSpell(29858, false);
				player->learnSpell(50511, false);
				player->learnSpell(61191, false);
				player->learnSpell(47884, false);
				player->learnSpell(47856, false);
				player->learnSpell(47813, false);
				player->learnSpell(47855, false);
				player->learnSpell(47888, false);
				player->learnSpell(47865, false);
				player->learnSpell(47860, false);
				player->learnSpell(47857, false);
				player->learnSpell(47823, false);
				player->learnSpell(47891, false);
				player->learnSpell(47878, false);
				player->learnSpell(47864, false);
				player->learnSpell(57595, false);
				player->learnSpell(47893, false);
				player->learnSpell(47820, false);
				player->learnSpell(47815, false);
				player->learnSpell(47809, false);
				player->learnSpell(60220, false);
				player->learnSpell(47867, false);
				player->learnSpell(47889, false);
				player->learnSpell(48018, false);
				player->learnSpell(47811, false);
				player->learnSpell(47838, false);
				player->learnSpell(57946, false);
				player->learnSpell(58887, false);
				player->learnSpell(47836, false);
				player->learnSpell(61290, false);
				player->learnSpell(47825, false);
			}
			break;
		case 101: // Repair Items
			player->DurabilityRepairAll(false, 0.0f, true);
			creature->MonsterWhisper("Your items have been repaired!", player, false);
			player->CLOSE_GOSSIP_MENU();
			break;
		case 102: // Max-Out Skills
			player->UpdateSkillsToMaxSkillsForLevel();
			creature->MonsterWhisper("Your weapon skills have been advanced to maximum level.", player, false);
			player->CLOSE_GOSSIP_MENU();
			break;
		case 103: // Remove Rez Sickness
			player->CLOSE_GOSSIP_MENU();
			if (player->HasAura(15007))
			{
				player->RemoveAura(15007);
				creature->MonsterWhisper("I have removed your Ressurection Sickness.", player, false);
			}
			else
				creature->MonsterWhisper("You don't have Ressurection Sickness.", player, false);
			break;
			// # Learn Professions #
		case 104: // Alchemy
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(2259, false);
			player->learnSpell(3101, false);
			player->learnSpell(3464, false);
			player->learnSpell(11611, false);
			player->learnSpell(28596, false);
			player->learnSpell(51304, false);

			player->UpdateSkill(171, 450);
			player->GetSession()->SendNotification("You've been taught Alchemy.");
			break;
		case 105: // Blacksmithing
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(2018, false);
			player->learnSpell(3100, false);
			player->learnSpell(3538, false);
			player->learnSpell(9785, false);
			player->learnSpell(29844, false);
			player->learnSpell(51300, false);

			player->UpdateSkill(164, 450);
			player->GetSession()->SendNotification("You've been taught Blacksmithing.");
			break;
		case 106: // Enchanting
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(7411, false);
			player->learnSpell(7412, false);
			player->learnSpell(7413, false);
			player->learnSpell(13920, false);
			player->learnSpell(28029, false);
			player->learnSpell(51313, false);

			player->UpdateSkill(333, 450);
			player->GetSession()->SendNotification("You've been taught Enchanting.");
			break;
		case 107: // Engineering
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(4036, false);
			player->learnSpell(4037, false);
			player->learnSpell(4038, false);
			player->learnSpell(12656, false);
			player->learnSpell(30350, false);
			player->learnSpell(51306, false);

			player->UpdateSkill(202, 450);
			player->GetSession()->SendNotification("You've been taught Engineering.");
			break;
		case 108: // Herbalism
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(2366, false);
			player->learnSpell(2368, false);
			player->learnSpell(3570, false);
			player->learnSpell(11993, false);
			player->learnSpell(28695, false);
			player->learnSpell(50300, false);

			player->UpdateSkill(182, 450);
			player->GetSession()->SendNotification("You've been taught Herbalism.");
			break;
		case 109: // Leatherworking
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(2108, false);
			player->learnSpell(3104, false);
			player->learnSpell(3811, false);
			player->learnSpell(10662, false);
			player->learnSpell(32549, false);
			player->learnSpell(51302, false);

			player->UpdateSkill(165, 450);
			player->GetSession()->SendNotification("You've been taught Leatherworking.");
			break;
		case 110: // Mining
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(2575, false);
			player->learnSpell(2576, false);
			player->learnSpell(3564, false);
			player->learnSpell(10248, false);
			player->learnSpell(29354, false);
			player->learnSpell(50310, false);

			player->UpdateSkill(186, 450);
			player->GetSession()->SendNotification("You've been taught Mining.");
			break;
		case 111: // Skinning
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(8613, false);
			player->learnSpell(8617, false);
			player->learnSpell(8618, false);
			player->learnSpell(10768, false);
			player->learnSpell(32678, false);
			player->learnSpell(50305, false);

			player->UpdateSkill(393, 450);
			player->GetSession()->SendNotification("You've been taught Skinning.");
			break;
		case 112: // Tailoring
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(3908, false);
			player->learnSpell(3909, false);
			player->learnSpell(3910, false);
			player->learnSpell(12180, false);
			player->learnSpell(26790, false);
			player->learnSpell(51309, false);

			player->UpdateSkill(197, 450);
			player->GetSession()->SendNotification("You've been taught Tailoring.");
			break;
		case 113: // Cooking
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(2550, false);
			player->learnSpell(3102, false);
			player->learnSpell(3413, false);
			player->learnSpell(18260, false);
			player->learnSpell(33359, false);
			player->learnSpell(51296, false);

			player->UpdateSkill(185, 450);
			player->GetSession()->SendNotification("You've been taught Cooking.");
			break;
		case 114: // First Aid
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(3273, false);
			player->learnSpell(3274, false);
			player->learnSpell(7924, false);
			player->learnSpell(10846, false);
			player->learnSpell(27028, false);
			player->learnSpell(45542, false);

			player->UpdateSkill(129, 450);
			player->GetSession()->SendNotification("You've been taught First Aid.");
			break;
		case 115: // Fishing
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(7620, false);
			player->learnSpell(7731, false);
			player->learnSpell(7732, false);
			player->learnSpell(18248, false);
			player->learnSpell(33095, false);
			player->learnSpell(51294, false);

			player->UpdateSkill(356, 450);
			player->GetSession()->SendNotification("You've been taught Fishing.");
			break;
		case 116: // Jewelcrafting
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(25229, false);
			player->learnSpell(25230, false);
			player->learnSpell(28894, false);
			player->learnSpell(28895, false);
			player->learnSpell(28897, false);
			player->learnSpell(51311, false);

			player->UpdateSkill(755, 450);
			player->GetSession()->SendNotification("You've been taught Jewelcrafting.");
			break;
		case 250: // Inscription
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(45357, false);
			player->learnSpell(45358, false);
			player->learnSpell(45359, false);
			player->learnSpell(45360, false);
			player->learnSpell(45361, false);
			player->learnSpell(45363, false);

			player->UpdateSkill(773, 450);
			player->GetSession()->SendNotification("You've been taught Inscription.");
			break;
		case 117: // Riding
			player->CLOSE_GOSSIP_MENU();
			player->learnSpell(33388, false);
			player->learnSpell(33391, false);
			player->learnSpell(34090, false);
			player->learnSpell(34091, false);

			player->UpdateSkill(762, 300);
			player->GetSession()->SendNotification("You've been taught Riding.");
			break;
			// ### Teleport Coordinates ###
			// # Main Cities #

		case 118: // Orgrimmar
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1629.36f, -4373.39f, 31.2564f, 3.54839f);
			break;
		case 119: // Thunderbluff
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -1277.37f, 124.804f, 131.287f, 5.22274f);
			break;
		case 120: // Silvermoon
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);
			break;
		case 121: // Undercity
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);
			break;
		case 122: // Stormwind
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);
			break;
		case 123: // Ironforge
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);
			break;
		case 124: // Exodar
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);
			break;
		case 125: // Darnassus
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);
			break;

			// # Neutral Cities #.

		case 126: // Dalaran
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);
			break;
		case 127: // Shattrath
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);
			break;
		case 128: // Booty Bay
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -14297.2f, 530.993f, 8.77916f, 3.98863f);
			break;
		case 129: // Gadgetzan
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7177.15f, -3785.34f, 8.36981f, 6.10237f);
			break;

			// # PvP Areas #

		case 130: // Gurubashi Arena
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -13277.4f, 127.372f, 26.1418f, 1.11878f);
			break;
		case 131: // Circle of Blood
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 2839.44f, 5930.17f, 11.1002f, 3.16284f);
			break;
		case 132: // The Ring of Trials
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1999.94f, 6581.71f, 11.32f, 2.36528f);
			break;

			// # Dungeons #

		case 133: // Dungeons 1-60 - Ragefire Chasm
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1811.78f, -4410.5f, -18.4704f, 5.20165f);
			break;
		case 134: // Dungeons 1-60 - The Deadmines
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -11208.7f, 1673.52f, 24.6361f, 1.51067f);
			break;
		case 135: // Dungeons 1-60 - Wailing Caverns
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -805.049f, -2032.03f, 95.8796f, 6.18912f);
			break;
		case 136: // Dungeons 1-60 - Shadowfang Keep
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -234.675f, 1561.63f, 76.8921f, 1.24031f);
			break;
		case 137: // Dungeons 1-60 - Blackfathom Deeps
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 4249.99f, 740.102f, -25.671f, 1.34062f);
			break;
		case 138: // Dungeons 1-60 - Stormwind Stockade
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -8773.32f, 839.031f, 91.6376f, 0.648292f);
			break;
		case 139: // Dungeons 1-60 - Gnomergan
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -5163.54f, 925.423f, 257.181f, 1.57423f);
			break;
		case 140: // Dungeons 1-60 - Scarlet Monastery
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 2842.533691f, -690.716248f, 139.331131f, 5.166503f);
			break;
		case 141: // Dungeons 1-60 - Razorfen Kraul
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4470.28f, -1677.77f, 81.3925f, 1.16302f);
			break;
		case 142: // Dungeons 1-60 - Maraudon
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -1419.13f, 2908.14f, 137.464f, 1.57366f);
			break;
		case 143: // Dungeons 1-60 - Uldaman
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -6071.37f, -2955.16f, 209.782f, 0.015708f);
			break;
		case 144: // Dungeons 1-60 - Razorfen Downs
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4657.3f, -2519.35f, 81.0529f, 4.54808f);
			break;
		case 145: // Dungeons 1-60 - Zul Farrack
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -6801.19f, -2893.02f, 9.00388f, 0.158639f);
			break;
		case 146: // Dungeons 1-60 - Sunken Temple
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10177.9f, -3994.9f, -111.239f, 6.01885f);
			break;
		case 147: // Dungeons 1-60 - Dire Maul
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -3521.29f, 1085.2f, 161.097f, 4.7281f);
			break;
		case 148: // Dungeons 1-60 - Blackrock Depths
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -7179.34f, -921.212f, 165.821f, 5.09599f);
			break;
		case 149: // Dungeons 1-60 - Blackrock Spire
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -7527.05f, -1226.77f, 285.732f, 5.29626f);
			break;
		case 150: // Dungeons 1-60 - Scholomance
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 1269.64f, -2556.21f, 93.6088f, 0.620623f);
			break;
		case 151: // Dungeons 1-60 - Stratholme
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 3352.92f, -3379.03f, 144.782f, 6.25978f);
			break;
		case 152: // Dungeons 60-70 - Hellfire Citadel
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -390.863f, 3130.64f, 4.51327f, 0.218692f);
			break;
		case 153: // Dungeons 60-70 - Coilfang Reservoir
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 735.066f, 6883.45f, -66.2913f, 5.89172f);
			break;
		case 154: // Dungeons 60-70 - Auchindoun
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -3324.49f, 4943.45f, -101.239f, 4.63901f);
			break;
		case 155: // Dungeons 60-70 - Tempest Keep
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3099.36f, 1518.73f, 190.3f, 4.72592f);
			break;
		case 156: // Dungeons 60-70 - Caverns of Time
			// Dungeons 60-70 - Culting of Stratholme
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8204.88f, -4495.25f, 9.0091f, 4.72574f);
			break;
		case 157: // Dungeons 60-70 - Magisters' Terrace
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 12884.6f, -7317.69f, 65.5023f, 4.799f);
			break;
		case 158: // Dungeons 70-80 - Utgarde Keep
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 1219.72f, -4865.28f, 41.2479f, 0.313228f);
			break;
		case 159: // Dungeons 70-80 - The Nexus
			// Dungeons 70-80 - The Oculus
			// Dungeons 70-80 - The Eye of Eternity
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3781.81f, 6953.65f, 104.82f, 0.467432f);
			break;
		case 160: // Dungeons 70-80 - Azjol-Nerub
			// Dungeons 70-80 - Ahn'Kahet: The Old Kingdom
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3707.86f, 2150.23f, 36.76f, 3.22f);
			break;
		case 161: // Dungeons 70-80 - Drak'Tharon Keep
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4774.6f, -2032.92f, 229.15f, 1.59f);
			break;
		case 162: // Dungeons 70-80 - The Violet Hold
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5696.73f, 507.4f, 652.97f, 4.03f);
			break;
		case 163: // Dungeons 70-80 - Gundrak
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 6898.72f, -4584.94f, 451.12f, 2.34455f);
			break;
		case 164: // Dungeons 70-80 - Halls of Stone
			// Dungeons 70-80 - Halls of Lightning
			// Dungeons 70-80 - Uldar
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 9049.37f, -1282.35f, 1060.19f, 5.8395f);
			break;
		case 165: // Dungeons 70-80 - Utgarde Pinnacle
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 1259.33f, -4852.02f, 215.763f, 3.48293f);
			break;
		case 166: // Dungeons 70-80 - Trial of Champion
			// Dungeons 70-80 - Trial of Crusader
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 8515.89f, 629.25f, 547.396f, 1.5747f);
			break;
		case 167: // Dungeons 70-80 - Pit of Saron
			// Dungeons 70-80 - Forge of Souls
			// Dungeons 70-80 - Halls of Reflection
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5638.26f, 2053.01f, 798.046f, 4.59295f);
			break;

			// # Raids #

		case 168: // Level 60 Raids - Zul'Gurub
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -11916.7f, -1215.72f, 92.289f, 4.72454f);
			break;
		case 169: // Level 60 Raids - Molten Core
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(230, 1126.64f, -459.94f, -102.535f, 3.46095f);
			break;
		case 170: // Level 60 Raids - Blackwing Lair
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(229, 164.789f, -475.305f, 116.842f, 0.022714f);
			break;
		case 171: // Level 60 Raids - Ahn'Qiraj Ruins
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8409.82f, 1499.06f, 27.7179f, 2.51868f);
			break;
		case 172: // Level 60 Raids - Ahn'Qiraj Temple
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8240.09f, 1991.32f, 129.072f, 0.941603f);
			break;
		case 173: // Level 70 Raids - Karazhan
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -11118.9f, -2010.33f, 47.0819f, 0.649895f);
			break;
		case 174: // Level 70 Raids - Gruul's Lair
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3530.06f, 5104.08f, 3.50861f, 5.51117f);
			break;
		case 175: // Level 70 Raids - Magtheridon's Lair
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -312.7f, 3087.26f, -116.52f, 5.19026f);
			break;
		case 176: // Level 70 Raids - Zul'Aman
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 6851.78f, -7972.57f, 179.242f, 4.64691f);
			break;
		case 177: // Level 70 Raids - Serpentshrine Cavern
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 820.025f, 6864.93f, -66.7556f, 6.28127f);
			break;
		case 178: // Level 70 Raids - Tempest Keep: The Eye
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3088.49f, 1381.57f, 184.863f, 4.61973f);
			break;
		case 179: // Level 70 Raids - Hyjal
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8177.89f, -4181.23f, -167.552f, 0.913338f);
			break;
		case 180: // Level 70 Raids - Black Temple
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -3649.92f, 317.469f, 35.2827f, 2.94285f);
			break;
		case 181: // Level 70 Raids - Sunwell Plateau
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);
			break;
		case 182: // Level 80 Raids - Naxxarams
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);
			break;
		case 183: // Level 80 Raids - Obsidian Sanctum
			// Level 80 Raids - Ruby Sanctum
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3479.66f, 264.625f, -120.144f, 0.097f);
			break;
		case 184: // Level 80 Raids - Vault of Archavon
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5453.72f, 2840.79f, 421.28f, 0.0f);
			break;
		case 185: // Level 80 Raids - Icecrown Citadel
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5873.82f, 2110.98f, 636.011f, 3.5523f);
			break;
		case 186: // Level 80 Raids - Onyxia's Liar
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4708.27f, -3727.64f, 54.5589f, 3.72786f);
			break;

			// # Zones #

		case 187: // Zones - Eastern Kingdoms - Eversong Woods
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 9079.92f, -7193.23f, 55.6013f, 5.94597f);
			break;
		case 188: // Zones - Eastern Kingdoms - Tirisfal Glades
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 2036.02f, 161.331f, 33.8674f, 0.143896f);
			break;
		case 189: // Zones - Eastern Kingdoms - Dun Morogh
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -5451.55f, -656.992f, 392.675f, 0.66789f);
			break;
		case 190: // Zones - Eastern Kingdoms - Elwynn Forest
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -9617.06f, -288.949f, 57.3053f, 4.72687f);
			break;
		case 191: // Zones - Eastern Kingdoms - Ghostlands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 7360.86f, -6803.3f, 44.2942f, 5.83679f);
			break;
		case 192: // Zones - Eastern Kingdoms - Silverpine Forest
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 878.74f, 1359.33f, 50.355f, 5.89929f);
			break;
		case 193: // Zones - Eastern Kingdoms - Westfall
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10235.2f, 1222.47f, 43.6252f, 6.2427f);
			break;
		case 194: // Zones - Eastern Kingdoms - Loch Modan
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -5202.94f, -2855.18f, 336.822f, 0.37651f);
			break;
		case 195: // Zones - Eastern Kingdoms - Redridge Mountains
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -9551.81f, -2204.73f, 93.473f, 5.47141f);
			break;
		case 196: // Zones - Eastern Kingdoms - Duskwood
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10898.3f, -364.784f, 39.2681f, 3.04614f);
			break;
		case 197: // Zones - Eastern Kingdoms - Wetlands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -3242.81f, -2469.04f, 15.9226f, 6.03924f);
			break;
		case 198: // Zones - Eastern Kingdoms - Hillsbrad Foothills
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -436.657f, -581.254f, 53.5944f, 1.25917f);
			break;
		case 199: // Zones - Eastern Kingdoms - Alterac Mountains
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 370.763f, -491.355f, 175.361f, 5.37858f);
			break;
		case 200: // Zones - Eastern Kingdoms - Arathi Highlands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -1508.51f, -2732.06f, 32.4986f, 3.35708f);
			break;
		case 201: // Zones - Eastern Kingdoms - Strangelthorn Vale
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -12644.3f, -377.411f, 10.1021f, 6.09978f);
			break;
		case 202: // Zones - Eastern Kingdoms - Swamp of Sorrows
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10345.4f, -2773.42f, 21.99f, 5.08426f);
			break;
		case 203: // Zones - Eastern Kingdoms - Badlands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -6779.2f, -3423.64f, 241.667f, 0.647481f);
			break;
		case 204: // Zones - Eastern Kingdoms - The Hinterlands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 119.387f, -3190.37f, 117.331f, 2.34064f);
			break;
		case 205: // Zones - Eastern Kingdoms - Searing Gorge
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -7012.47f, -1065.13f, 241.786f, 5.63162f);
			break;
		case 206: // Zones - Eastern Kingdoms - Blasted Lands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -11182.5f, -3016.67f, 7.42235f, 4.0004f);
			break;
		case 207: // Zones - Eastern Kingdoms - Burning Steppes
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -8118.54f, -1633.83f, 132.996f, 0.089067f);
			break;
		case 208: // Zones - Eastern Kingdoms - Western Plaguelands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 1728.65f, -1602.25f, 63.429f, 1.6558f);
			break;
		case 209: // Zones - Eastern Kingdoms - Eastern Plaguelands
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 2300.97f, -4613.36f, 73.6231f, 0.367722f);
			break;
		case 210: // Zones - Eastern Kingdoms - Deadwind Pass
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10438.8f, -1932.75f, 104.617f, 4.77402f);
			break;
		case 211: // Zones - Kalimdor - Teldrassil
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 10111.3f, 1557.73f, 1324.33f, 4.04239f);
			break;
		case 212: // Zones - Kalimdor - Azuremyst Isle
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -4216.87f, -12336.9f, 4.34247f, 6.02008f);
			break;
		case 213: // Zones - Kalimdor - Durotar
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1007.78f, -4446.22f, 11.2022f, 0.20797f);
			break;
		case 214: // Zones - Kalimdor - Mulgore
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -2192.62f, -736.317f, -13.3274f, 0.487569f);
			break;
		case 215: // Zones - Kalimdor - Bloodmyst Isle
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1993.62f, -11475.8f, 63.9657f, 5.29437f);
			break;
		case 216: // Zones - Kalimdor - Darkshore
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 5756.25f, 298.505f, 20.6049f, 5.96504f);
			break;
		case 217: // Zones - Kalimdor - The Barrens
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 884.54f, -3548.45f, 91.8532f, 2.95957f);
			break;
		case 218: // Zones - Kalimdor - Stonetalon Mountains
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1570.92f, 1031.52f, 137.959f, 3.33006f);
			break;
		case 219: // Zones - Kalimdor - Ashenvale
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1928.34f, -2165.95f, 93.7896f, 0.205731f);
			break;
		case 220: // Zones - Kalimdor - Thousand Needles
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4969.02f, -1726.89f, -62.1269f, 3.7933f);
			break;
		case 221: // Zones - Kalimdor - Desolace
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -606.395f, 2211.75f, 92.9818f, 0.809746f);
			break;
		case 222: // Zones - Kalimdor - Dustwallow Marsh
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4043.65f, -2991.32f, 36.3984f, 3.37443f);
			break;
		case 223: // Zones - Kalimdor - Tanaris
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7931.2f, -3414.28f, 80.7365f, 0.66522f);
			break;
		case 224: // Zones - Kalimdor - Feralas
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4841.19f, 1309.44f, 81.3937f, 1.48501f);
			break;
		case 225: // Zones - Kalimdor - Azshara
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 3341.36f, -4603.79f, 92.5027f, 5.28142f);
			break;
		case 226: // Zones - Kalimdor - Felwood
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 4102.25f, -1006.79f, 272.717f, 0.790048f);
			break;
		case 227: // Zones - Kalimdor - Un'Goro Crater
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7943.22f, -2119.09f, -218.343f, 6.0727f);
			break;
		case 228: // Zones - Kalimdor - Silithus
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7426.87f, 1005.31f, 1.13359f, 2.96086f);
			break;
		case 229: // Zones - Kalimdor - Winterspring
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 6759.18f, -4419.63f, 763.214f, 4.43476f);
			break;
		case 230: // Zones - Kalimdor - Moonglade
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 7654.3f, -2232.87f, 462.107f, 5.96786f);
			break;
		case 231: // Zones - Outlands - Hellfire Peninsula
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -211.237f, 4278.54f, 86.5678f, 4.59776f);
			break;
		case 232: // Zones - Outlands - Zangarmarsh
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -54.8621f, 5813.44f, 20.9764f, 0.081722f);
			break;
		case 233: // Zones - Outlands - Terokkar Forest
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -2000.47f, 4451.54f, 8.37917f, 4.40447f);
			break;
		case 234: // Zones - Outlands - Nagrand
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1145.95f, 8182.35f, 3.60249f, 6.13478f);
			break;
		case 235: // Zones - Outlands - Blade's Edge Mountains
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3037.67f, 5962.86f, 130.774f, 1.27253f);
			break;
		case 236: // Zones - Outlands - Shadowmoon Valley
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -3179.6f, 2716.43f, 68.6444f, 4.16414f);
			break;
		case 237: // Zones - Outlands - Netherstorm
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3830.23f, 3426.5f, 88.6145f, 5.16677f);
			break;
		case 238: // Zones - Northrend - Borean Tundra
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3256.57f, 5278.23f, 40.8046f, 0.246367f);
			break;
		case 239: // Zones - Northrend - Howling Fjord
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 1902.15f, -4883.91f, 171.363f, 3.11537f);
			break;
		case 240: // Zones - Northrend - Dragonblight
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4103.36f, 264.478f, 50.5019f, 3.09349f);
			break;
		case 241: // Zones - Northrend - Grizzly Hills
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4391.73f, -3587.92f, 238.531f, 3.57526f);
			break;
		case 242: // Zones - Northrend - Zul'Drak
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5560.23f, -3211.66f, 371.709f, 5.55055f);
			break;
		case 243: // Zones - Northrend - Sholazar Basin
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5323, 4942, -133.5f, 2.17f);
			break;
		case 244: // Zones - Northrend - Crystalsong Forest
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5659.35f, 359.053f, 158.214f, 3.69933f);
			break;
		case 245: // Zones - Northrend - The Storm Peaks
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 7527.14f, -1260.89f, 919.049f, 2.0696f);
			break;
		case 246: // Zones - Northrend - Icecrown
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 7253.64f, 1644.78f, 433.68f, 4.83412f);
			break;
		case 247: // Zones - Northrend - Wintergrasp
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4760.7f, 2143.7f, 423, 1.13f);
			break;

			////////////// EVENTS ////////////////////////////

		case 556: // Event 1
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 9639.551f, -8054.838f, 0.549f, 5.973f);
			break;

		case 558: // Event 2
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -9111.680f, -4421.038f, 118.956f, 0.1169f);
			break;

		case 658: // Event 3
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -9111.680f, -4421.038f, 118.956f, 0.1169f);
			break;



			//////////////////////// Custom Bosses/////////////////////

		case 656: // Boss 1
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 4246.639f, -7807.3955f, 8.0943f, 3.5643f);
			break;

		case 657: // Boss 2
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f);
			break;

		case 557: // Close Gossip
			player->CLOSE_GOSSIP_MENU();
			break;


		case 252: // DK Talent Fix /Other Classes Reset
			player->CLOSE_GOSSIP_MENU();
			player->resetTalents(true);
			((Player*)player)->GiveLevel(1);
			((Player*)player)->GiveLevel(80);
			break;



			////// CUSTOM INSTANCES ////////////////////

		case 10001: // Hellfire Citadel
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10002: // Gruul's Lair
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10003: // The Obsidian Sanctum
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10004: // Ragefire Chasm
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10005: // Zul Farrak
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10006: // Ragefire Chasm
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10007: // The Stockade
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10008: // Sunwell Plateau
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10009: // Black Temple
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10010: // Icecrown Citadel Dungeons
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10011: // Gundrak
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10012: // The Stockade
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10013: // Zul Aman
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;

		case 10014: // Azjol Nerub
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 264.814f, -1423.120f, 50.4118f, 4.3938f); // edit the cords!!!
			break;


			/////// LEVELING AREA/////////////////

		case 11000: // Leveling Area
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 2083.850586f, 2484.402344f, 131.252350f, 3.22494f); //did this according to your cords on AC-Web
			break;




			// # Malls #
		case 13000: // Mall
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(MAP_ID, Xf, Yf, Zf, Of); //edit the cords here
			break;
		}
		return true;
	}
};

void AddSC_Teleporter()
{
	new Teleporter();
}