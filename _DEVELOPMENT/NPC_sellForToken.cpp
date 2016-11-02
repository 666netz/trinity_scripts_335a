#include "ScriptPCH.h"
#include <cstring>

enum eEnums
{
	OFFSET_LEVELS				= 10,
    MAXIMAL_LEVEL				= 80,
	TOKEN_ID					= 52021,
	TOKENS_PER_LEVEL_1			= 1,
	INCREASE_RATE_PERCENTUAL    = 110
};


class npc_level_vendor : public CreatureScript
{
    public:

        npc_level_vendor()
            : CreatureScript("npc_level_vendor")
        {
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
			MainMenu(player, creature);
            return true;
        }

		int GetMaximum(Player *player)
		{
			return MAXIMAL_LEVEL - player->getLevel();
		}

		bool IsNumeric(std::string str)
		{
		   for (int i = 0; i < str.length(); i++) {
			   if (!std::iswdigit(str[i]))
				   return false;
		   }

		   return true;
		}

		std::string JoinStIn(std::string st, int in)
		{
			std::stringstream sstm;
			sstm << st << in;
			return sstm.str();
		}

		int StringToInt(std::string str)
		{
			if(IsNumeric(str))
			{
				int result;
				std::stringstream sstm(str);
				sstm >> result;
				return result;
			}
			else
				return -1;
		}

		float GetPriceForLevel(int level)
		{
			float price = TOKENS_PER_LEVEL_1;
			for(int x = 0; x < level; x++)
			{
				price = price * ((float)INCREASE_RATE_PERCENTUAL / (float)100);
			}
			return price;
		}

		void MainMenu(Player *player, Creature *creature)
		{
			std::string message = JoinStIn("Please enter amount of levels you would like to get. Maximal value you can enter is ", GetMaximum(player)) + ".";
			if(player->getLevel() < MAXIMAL_LEVEL)
				player->ADD_GOSSIP_ITEM_EXTENDED(0, "I'd like to purchase level or two :-)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3,
				message, 0, true);
			player->ADD_GOSSIP_ITEM(0, "Not interested", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

			player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
		}

		bool OnGossipSelectCode(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction, const char* code)
        {
            player->PlayerTalkClass->ClearMenus();
            if (uiSender == GOSSIP_SENDER_MAIN)
            {
                if (uiAction == GOSSIP_ACTION_INFO_DEF+3)
				{
					int reqIncrease = StringToInt(code);
					if(reqIncrease != -1 && player->getLevel() + reqIncrease < MAXIMAL_LEVEL + 1)
					{
						float toPay = GetPriceForLevel(player->getLevel() + reqIncrease) - GetPriceForLevel(player->getLevel());
						std::string message = JoinStIn("Buy ", reqIncrease) + JoinStIn(" for ", (int)toPay) + " tokens.";

						player->ADD_GOSSIP_ITEM(0, message, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+OFFSET_LEVELS+reqIncrease);
						player->ADD_GOSSIP_ITEM(0, "Thats too much!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

						player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());


					}
					else // not numeric value, or invalid
						MainMenu(player, creature);
				}
            }

            return false;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32, uint32 uiAction)
        {
			player->PlayerTalkClass->ClearMenus();
            if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
            {
					player->CLOSE_GOSSIP_MENU();
			}
			else if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
            {
					MainMenu(player, creature);
			}
			else if (uiAction > GOSSIP_ACTION_INFO_DEF+OFFSET_LEVELS)
			{
				int reqIncrease = uiAction - GOSSIP_ACTION_INFO_DEF - OFFSET_LEVELS;
				if(reqIncrease != -1 && player->getLevel() + reqIncrease < MAXIMAL_LEVEL + 1)
				{
					float toPay = GetPriceForLevel(player->getLevel() + reqIncrease) - GetPriceForLevel(player->getLevel());
					if(player->HasItemCount(TOKEN_ID, (int)toPay))
					{
						player->DestroyItemCount(TOKEN_ID, (int)toPay, true);
						player->GiveLevel(player->getLevel() + reqIncrease);
						player->SaveToDB();
						player->CLOSE_GOSSIP_MENU();
					}
					else
						MainMenu(player, creature); // not enough tokens
				}
				else
					MainMenu(player, creature); // player leveled up before clicking on buy
			}

			return true;
		}
};

void AddSC_npc_level_vendor()
{
    new npc_level_vendor();
}