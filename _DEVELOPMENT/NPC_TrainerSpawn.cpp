class npc_trainerspawn : public CreatureScript
{
public:
	npc_trainerspawn() : CreatureScript("npc_trainerspawn") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->IsInCombat())
		{
			player->PlayerTalkClass->SendCloseGossip();
			creature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
			return true;
		}
		if (player->GetMap()->IsBattlegroundOrArena())
		{
			player->PlayerTalkClass->SendCloseGossip();
			creature->MonsterSay("You can't summon trainers while in battleground or Arena!", LANG_UNIVERSAL, NULL);
			return true;
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spawn your Class Trainer.", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Maybe later.", GOSSIP_SENDER_MAIN, 2);
		player->SEND_GOSSIP_MENU(85004, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /* sender */, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case 1:
			switch (player->getClass())
			{
			case CLASS_DEATH_KNIGHT:
				HandleSummonTrainer(player, creature, 28474);
				break;
			case CLASS_DRUID:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 12042);
				else
					HandleSummonTrainer(player, creature, 5505);
				break;
			case CLASS_HUNTER:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 3406);
				else
					HandleSummonTrainer(player, creature, 5516);
				break;
			case CLASS_MAGE:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 5882);
				else
					HandleSummonTrainer(player, creature, 5497);
				break;
			case CLASS_PALADIN:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 20406);
				else
					HandleSummonTrainer(player, creature, 5492);
				break;
			case CLASS_PRIEST:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 6018);
				else
					HandleSummonTrainer(player, creature, 11397);
				break;
			case CLASS_ROGUE:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 3327);
				else
					HandleSummonTrainer(player, creature, 918);
				break;
			case CLASS_SHAMAN:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 3344);
				else
					HandleSummonTrainer(player, creature, 20407);
				break;
			case CLASS_WARLOCK:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 3325);
				else
					HandleSummonTrainer(player, creature, 5495);
				break;
			case CLASS_WARRIOR:
				if (player->GetTeam() == HORDE)
					HandleSummonTrainer(player, creature, 4593);
				else
					HandleSummonTrainer(player, creature, 5479);
				break;
			}
			break;
		case 2:
			creature->MonsterWhisper("Please come again.", player->GetGUID());
			break;
		}

		player->CLOSE_GOSSIP_MENU();
		return true;
	}

	void HandleSummonTrainer(Player* player, Creature* creature, uint32 entry)
	{
		player->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 5, player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 45000);
		creature->MonsterWhisper("Hello, I'm only here for a short period of time!", player->GetGUID());
	}
};

void AddSC_npc_trainerspawn()
{
	new npc_trainerspawn();
}