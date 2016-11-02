
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"

enum Bosses
{
	BOSS_UNO = 29793, //Bfx CHANGE ME
	BOSS_DOS = 26577, //Bfx CHANGE ME
	BOSS_TRES = 29793, //Bfx CHANGE ME
	BOSS_CUATRO = 26577, //Bfx CHANGE ME
	BOSS_CINCO = 29793, //Bfx CHANGE ME
	BOSS_SEIS = 20870, //Bfx CHANGE ME
	BOSS_SIETE = 29793, //Bfx CHANGE ME
	BOSS_OCHO = 26577, //Bfx CHANGE ME
	BOSS_NUEVE = 29793, //Bfx CHANGE ME
	BOSS_DIES = 90001, //Bfx CHANGE ME
	BOSS_ONCE = 90000, //Bfx CHANGE ME
	BOSS_DOCE = 90001, //Bfx CHANGE ME
	BOSS_TRECE = 90000, //Bfx CHANGE ME
	BOSS_CATORCE = 90001, //Bfx CHANGE ME
};
enum items
{
	ITEM_BADGE_OF_JUSITCE = 29434,
};

enum actions
{
	ACTION_BOSS_LIST = 2,
	ACTION_BOSS_UNO = 5,
	ACTION_BOSS_DOS = 6,
	ACTION_GOOD_BYE = 99,
};

/* Warning Do not Spawn Bosses that are linked to instances such as algalon Lich king and so on so fourth outside of an instance , doing so will cause the core to crash */


class npc_player_summon_bosses : public CreatureScript
{
public: npc_player_summon_bosses() : CreatureScript("npc_player_summon_bosses") { }

		bool OnGossipHello(Player *player, Creature *_creature)
		{

			player->ADD_GOSSIP_ITEM(2, "I wish to Summon Some Bosses.", GOSSIP_SENDER_MAIN, ACTION_BOSS_LIST);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
		{

			if (player->IsInCombat())
			{
				player->CLOSE_GOSSIP_MENU();
				_creature->MonsterWhisper("You Must First Leave Combat!", player->GetGUID());
				return true;
			}

			if (sender == GOSSIP_SENDER_MAIN)
			{
				player->PlayerTalkClass->ClearMenus();
				switch (uiAction)
				{
				case ACTION_BOSS_LIST: //Bfx Boss Choices
				{
					player->ADD_GOSSIP_ITEM(2, "Matar brujas", GOSSIP_SENDER_MAIN, ACTION_BOSS_UNO);
					player->ADD_GOSSIP_ITEM(2, "Completar mision sin matar brujas", GOSSIP_SENDER_MAIN, ACTION_BOSS_DOS);
					player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				}
				break;
				case ACTION_BOSS_UNO: //Bfx Rename
				{
					player->CLOSE_GOSSIP_MENU();
					player->SummonCreature(BOSS_UNO, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_TRES, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_CUATRO, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_CINCO, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_SEIS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_SIETE, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_OCHO, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					_creature->MonsterYell("MORIRAS POR FEA JAJAJJAAJ", LANG_UNIVERSAL, NULL);
				}
				break;
				case ACTION_BOSS_DOS: //Bfx Rename
				{
					player->CLOSE_GOSSIP_MENU();
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					player->SummonCreature(BOSS_DOS, _creature->GetPositionX() + (rand() % 5), _creature->GetPositionY() + (rand() % 5), _creature->GetPositionZ(), float(rand() % 5), TEMPSUMMON_TIMED_DESPAWN, 500000);
					_creature->MonsterYell("QUE MANCO ERES xD", LANG_UNIVERSAL, NULL);
				}
				break;
				case ACTION_GOOD_BYE: //Goodbye
				{
					player->CLOSE_GOSSIP_MENU();
				}
				break;
				default:
					break;
				}
			}
			return true;
		}


};
void AddSC_npc_player_summon_bosses()
{
	new npc_player_summon_bosses();
}