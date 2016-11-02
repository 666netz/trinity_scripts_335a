//Hamcake's Arena Reward NPC

#include "ScriptPCH.h"
#include "Chat.h"

#define T_REWARD "What rewards am I entitled to?"
#define T_NEXT "Next Page -->"
#define T_QUIT "Never mind"

class npc_sayge : public CreatureScript
{
public:
	npc_sayge() : CreatureScript("npc_sayge") { }
	uint32 RewardIds[] = {}; //Put item IDs in here
	uint32 RewardReqs[] = {}; //Put personal rating requirement under the item IDs

	bool CheckRewards(Player* player, Creature* creature, uint32 action)
	{
		if (!player)
			return false;

		if (!creature)
			return false;

		int rewardnum = 0;
		uint32 PersonalRatingA = player->GetArenaPersonalRating(0);
		uint32 PersonalRatingB = player->GetArenaPersonalRating(1);
		uint32 PersonalRatingC = player->GetArenaPersonalRating(2);
		ItemPrototype const* reward;
		int i = action;

		//Generates the list of rewards. Also stops and adds a 'next' button if the list is too big.
		for (; (i < (sizeof(RewardIds) / sizeof(RewardIds[0]))) && rewardnum < 11; i++)
		{
			reward = objmgr.GetItemPrototype(RewardIds[i]);
			char* text = reward->Name1;
			if (!text)
				return false;
			if (reward)
			{
				if ((PersonalRatingA >= RewardReqs[i]) || (PersonalRatingB >= RewardReqs[i]) || (PersonalRatingC >= RewardReqs[i]))
				{
					if (!player->HasItemCount(RewardIds[i], 1, true) && !player->HasSpell(reward->Spells[1].SpellId))
					{
						if (rewardnum < 10)
							player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, text, i, 0);
						rewardnum++;
					}
				}
			}
			if (rewardnum > 10)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, T_NEXT, 1002, i);
		}
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, T_QUIT, 1001, 0);
		if (rewardnum > 0)
		{
			player->SEND_GOSSIP_MENU(907, creature->GetGUID());
			return true;
		}
		else
			return false;
	}


	bool GossipHello_npc_arenarewards(Player *player, Creature *creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, T_REWARD, 1000, 0);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, T_QUIT, 1001, 0);
		player->SEND_GOSSIP_MENU(907, creature->GetGUID());
		return true;
	}


	bool GossipSelect_npc_arenarewards(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
	{
		uint32 PersonalRatingA = player->GetArenaPersonalRating(0);
		uint32 PersonalRatingB = player->GetArenaPersonalRating(1);
		uint32 PersonalRatingC = player->GetArenaPersonalRating(2);
		switch (sender)
		{
		case 1000:
			if (!CheckRewards(player, creature, 0))
			{
				creature->MonsterWhisper("You are not eligible for any rewards.", player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
			}
			break;

		case 1001:
			player->CLOSE_GOSSIP_MENU();
			break;

		case 1002:
			CheckRewards(player, creature, uiAction);
			break;
		}

		if (sender < 1000)
		{
			if ((PersonalRatingA >= RewardReqs[sender]) || (PersonalRatingB >= RewardReqs[sender]) || (PersonalRatingC >= RewardReqs[sender]))
				player->AddItem(RewardIds[sender], 1);
			if (!CheckRewards(player, creature, 0))
			{
				creature->MonsterWhisper("You are not eligible for any rewards.", player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
			}
		}
		return true;
	}
};

void AddSC_npc_arenarewards()
{
	new npc_arenarewards;
}