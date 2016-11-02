#include "ScriptPCH.h"

class npc_morph : public CreatureScript
{
public:
	npc_morph() : CreatureScript("npc_morph") { }

	bool OnGossipHello(Player *player, Creature *_creature)
	{
		if (player->isInCombat())
		{
			player->CLOSE_GOSSIP_MENU();
			_creature->MonsterWhisper("Combat!", player->GetGUID());
			return true;
		}
		else
		{
			player->ADD_GOSSIP_ITEM(3, "Gnome", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(3, "Human", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(3, "Tauren", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(3, "Goblin", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(3, "Blood Elf", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(3, "Broken", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(3, "Other", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(9, "Demorph", GOSSIP_SENDER_MAIN, 8);

		}

		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
	{
		if (sender == GOSSIP_SENDER_MAIN)
		{
			player->PlayerTalkClass->ClearMenus();
			switch (uiAction)
			{
			case 1://Gnome
				player->ADD_GOSSIP_ITEM(3, "Male", GOSSIP_SENDER_MAIN, 9);
				player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, 10);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

			case 2://Human
				player->ADD_GOSSIP_ITEM(3, "Male", GOSSIP_SENDER_MAIN, 11);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

			case 3://Tauren
				player->ADD_GOSSIP_ITEM(3, "Male", GOSSIP_SENDER_MAIN, 12);
				player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, 13);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

			case 4://Goblin
				player->ADD_GOSSIP_ITEM(3, "Male", GOSSIP_SENDER_MAIN, 14);
				player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, 15);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

			case 5://Blood Elf
				player->ADD_GOSSIP_ITEM(3, "Male", GOSSIP_SENDER_MAIN, 16);
				player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, 17);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

			case 6://Broken
				player->ADD_GOSSIP_ITEM(3, "Male", GOSSIP_SENDER_MAIN, 18);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

			case 7://Other
				player->ADD_GOSSIP_ITEM(3, "Champion", GOSSIP_SENDER_MAIN, 20);
				player->ADD_GOSSIP_ITEM(3, "Pirate", GOSSIP_SENDER_MAIN, 21);
				player->ADD_GOSSIP_ITEM(3, "Arthas", GOSSIP_SENDER_MAIN, 22);
				player->ADD_GOSSIP_ITEM(3, "Ghost", GOSSIP_SENDER_MAIN, 23);
				player->ADD_GOSSIP_ITEM(3, "Wolf", GOSSIP_SENDER_MAIN, 24);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;
			case 20://Champion
				player->ADD_GOSSIP_ITEM(3, "Darnassus", GOSSIP_SENDER_MAIN, 25);
				player->ADD_GOSSIP_ITEM(3, "Gnomeregan", GOSSIP_SENDER_MAIN, 26);
				player->ADD_GOSSIP_ITEM(3, "Ironforge", GOSSIP_SENDER_MAIN, 27);
				player->ADD_GOSSIP_ITEM(3, "Orgrimmar", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "Silvermoon", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(3, "Stormwind", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(3, "Exodar", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(3, "Undercity", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(3, "Thunder Bluff", GOSSIP_SENDER_MAIN, 33);
				player->ADD_GOSSIP_ITEM(3, "Ebon", GOSSIP_SENDER_MAIN, 34);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;
			case 21://Pirate
				player->ADD_GOSSIP_ITEM(3, "Male", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, 36);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

			case 9://Gnome - Male
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20580);
				break;

			case 10://Gnome - Female
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20581);
				break;

			case 11://Human - Male
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(19723);
				break;

			case 12://Tauren - Male
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20585);
				break;

			case 13://Tauren - Female
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20584);
				break;

			case 14://Goblin - Male
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20581);
				break;

			case 15://Goblin - Female
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20583);
				break;

			case 16://Blood Elf - Male
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20578);
				break;

			case 17://Blood Elf - Female
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20579);
				break;

			case 18://Broken - Male
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(21105);
				break;

			case 22://Arthas
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(22234);
				break;

			case 23://Ghost
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(14560);
				break;

			case 24://Wolf
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(741);
				break;

			case 35://Pirate - Male
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(4620);
				break;

			case 36://Pirate - Female
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(4619);
				break;

			case 25://Darnassus
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(29007);
				break;

			case 26://Gnomeregan
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(28859);
				break;

			case 27://Ironforge
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(28860);
				break;

			case 28://Orgrimmar
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(29053);
				break;

			case 29://Silvermoon
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(28862);
				break;

			case 30://Stormwind
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(28863);
				break;

			case 31://Exodar
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(30810);
				break;

			case 32://Undercity
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(28858);
				break;

			case 33://Thunder Bluff
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(28597);
				break;

			case 34://Ebon
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(30862);
				break;

			case 8://Demorph
				player->CLOSE_GOSSIP_MENU();
				player->DeMorph();
				break;
			default:
				break;
			}
		}
		return true;
	}
};

void AddSC_npc_morph()
{
	new npc_morph();
}