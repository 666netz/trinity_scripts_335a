#include "ScriptPCH.h"

class npc_customize : public CreatureScript
{
public:
	npc_customize() : CreatureScript("npc_customize") { }

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
			player->ADD_GOSSIP_ITEM(1, "Rename [5.000 Honor]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(6, "Customize [10.000 Honor]", GOSSIP_SENDER_MAIN, 2);
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
			case 1: //Rename 
				if (player->GetHonorPoints() >= 5000)
				{
					player->CLOSE_GOSSIP_MENU();
					player->ModifyHonorPoints(-5000);
					player->SetAtLoginFlag(AT_LOGIN_RENAME);
					_creature->MonsterWhisper("Mas Rename!", player->GetGUID());
				}
				else if (player->GetHonorPoints() < 5000)
				{
					player->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("Nedostatok Honor Points!", player->GetGUID());
					return false;
				}
				break;

			case 2: //Customize
				if (player->GetHonorPoints() >= 10000)
				{
					player->CLOSE_GOSSIP_MENU();
					player->ModifyHonorPoints(-10000);
					player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
					_creature->MonsterWhisper("Mas Customize!", player->GetGUID());
				}
				else if (player->GetHonorPoints() < 5000)
				{
					player->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("Nedostatok Honor Points!", player->GetGUID());
					return false;
				}
				break;
			} // koniec switchu
		} // koniec if-u
		return true;
	} // koniec metody
}; // koniec triedy

void AddSC_npc_customize()
{
	new npc_customize();
}