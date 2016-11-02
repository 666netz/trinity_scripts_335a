/*
###################################
#
# Made by Paddo-Head.
#
####################################
*/

#include "ScriptPCH.h" 
#define TOKEN_ID   49927           // Replace 49927 to YOUR_TOKEN_ID 

class vote_NPC : public CreatureScript

{
public:

	vote_NPC() : CreatureScript("vote_NPC") {}

	bool OnGossipHello(Player* pPlayer, Creature* _creature)
	{
		pPlayer->ADD_GOSSIP_ITEM(5, "Required vote tokens in ( )", GOSSIP_SENDER_MAIN, 111212);
		pPlayer->ADD_GOSSIP_ITEM(9, "10000 honor (2)", GOSSIP_SENDER_MAIN, 1);
		pPlayer->ADD_GOSSIP_ITEM(9, "30000 honor (4)", GOSSIP_SENDER_MAIN, 2);
		pPlayer->ADD_GOSSIP_ITEM(9, "50000 honor (6)", GOSSIP_SENDER_MAIN, 3);
		pPlayer->ADD_GOSSIP_ITEM(5, "---------------", GOSSIP_SENDER_MAIN, 3983882);
		pPlayer->ADD_GOSSIP_ITEM(9, "300 arena points (2)", GOSSIP_SENDER_MAIN, 4);
		pPlayer->ADD_GOSSIP_ITEM(9, "600 arena points (4)", GOSSIP_SENDER_MAIN, 5);
		pPlayer->ADD_GOSSIP_ITEM(9, "1200 arena points (6)", GOSSIP_SENDER_MAIN, 6);
		pPlayer->ADD_GOSSIP_ITEM(5, "----------------", GOSSIP_SENDER_MAIN, 1272616);
		pPlayer->ADD_GOSSIP_ITEM(9, "40 emblem of frost (2)", GOSSIP_SENDER_MAIN, 7);
		pPlayer->ADD_GOSSIP_ITEM(9, "90 emblem of frost (4)", GOSSIP_SENDER_MAIN, 8);
		pPlayer->PlayerTalkClass->SendGossipMenu(907, _creature->GetGUID());
		return true;

	}

	bool OnGossipSelect(Player* pPlayer, Creature* _creature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		if (uiSender == GOSSIP_SENDER_MAIN)
		{

			switch (uiAction)
			{

			case 1: // 10000 honor (2) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 2, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->ModifyHonorPoints(+10000);
					pPlayer->DestroyItemCount(TOKEN_ID, 2, true);
					_creature->MonsterWhisper("Your honor points have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;

			case 2: // 30000 honor (4) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 4, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->ModifyHonorPoints(+30000);
					pPlayer->DestroyItemCount(TOKEN_ID, 4, true);
					_creature->MonsterWhisper("Your honor points have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;

			case 3: // 50000 honor (6) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 6, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->ModifyHonorPoints(+50000);
					pPlayer->DestroyItemCount(TOKEN_ID, 6, true);
					_creature->MonsterWhisper("Your honor points have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;

			case 4: // 200 Arena points (2) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 2, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->ModifyArenaPoints(+200);
					pPlayer->DestroyItemCount(TOKEN_ID, 2, true);
					_creature->MonsterWhisper("Your arena points have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;

			case 5: // 600 Arena points (4) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 4, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->ModifyArenaPoints(+600);
					pPlayer->DestroyItemCount(TOKEN_ID, 4, true);
					_creature->MonsterWhisper("Your arena points have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;


			case 6: // 1200 Arena points (6) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 6, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->ModifyArenaPoints(+1200);
					pPlayer->DestroyItemCount(TOKEN_ID, 6, true);
					_creature->MonsterWhisper("Your arena points have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;

			case 7: // 40 emblem of frost (2) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 2, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->AddItem(49426, 40);
					pPlayer->DestroyItemCount(TOKEN_ID, 2, true);
					_creature->MonsterWhisper("Your emblems of frost have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;

			case 8: // 90 emblem of frost (4) vote tokens 
				if (pPlayer->HasItemCount(TOKEN_ID, 4, true))
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->AddItem(49426, 90);
					pPlayer->DestroyItemCount(TOKEN_ID, 4, true);
					_creature->MonsterWhisper("Your emblems of frost points have been added.", pPlayer->GetGUID());
				}
				else
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("You dont have enough vote tokens.", pPlayer->GetGUID());
					return false;
				}
				break;

			}

		}

	}
};

void AddSC_vote_NPC()
{
	new vote_NPC();
}


