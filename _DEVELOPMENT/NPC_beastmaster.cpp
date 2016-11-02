
//original script created by ??
#include "ScriptPCH.h"

#define GOSSIP_ITEM_STABLE "Stable"
#define GOSSIP_ITEM_NEWPET "New Pet"
#define GOSSIP_ITEM_BOAR "Boar"
#define GOSSIP_ITEM_SERPENT "Serpent"
#define GOSSIP_ITEM_SCRAB "Scrab"
#define GOSSIP_ITEM_LION "Lion"
#define GOSSIP_ITEM_WOLF "Wolf"
#define GOSSIP_ITEM_RAVAGER "Ravenger"

#define GOSSIP_ITEM_UNTRAINEPET "Restart Pet"

class Npc_Beastmaster : public CreatureScript
{
public:
	Npc_Beastmaster() : CreatureScript("Npc_Beastmaster") { }

	void CreatePet(Player *player, Creature * m_creature, uint32 entry) {

		if (player->getClass() != CLASS_HUNTER) {
			m_creature->MonsterWhisper("You are not a Hunter!", player->GetGUID());
			player->PlayerTalkClass->CloseGossip();
			return;
		}

		if (player->GetPet()) {
			m_creature->MonsterWhisper("First you must drop your Pet!", player->GetGUID());
			player->PlayerTalkClass->CloseGossip();
			return;
		}

		Creature *creatureTarget = m_creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
		if (!creatureTarget) return;

		Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
		if (!pet) return;

		// kill original creature
		creatureTarget->setDeathState(JUST_DIED);
		creatureTarget->RemoveCorpse();
		creatureTarget->SetHealth(0); // just for nice GM-mode view

		pet->SetPower(POWER_HAPPINESS, 1048000);

		//pet->SetUInt32Value(UNIT_FIELD_PETEXPERIENCE,0);
		//pet->SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, uint32((Trinity::XP::xp_to_level(70))/4));

		// prepare visual effect for levelup
		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
		pet->GetMap()->Add((Creature*)pet);
		// visual effect for levelup
		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());


		if (!pet->InitStatsForLevel(player->getLevel()))
			sLog->outError("Pet Create fail: no init stats for entry %u", entry);

		pet->UpdateAllStats();

		// caster have pet now
		player->SetMinion(pet, true);

		pet->SavePetToDB(PET_SAVE_AS_CURRENT);
		pet->InitTalentForLevel();
		player->PetSpellInitialize();

		//end
		player->PlayerTalkClass->CloseGossip();
		m_creature->MonsterWhisper("Pet added. You might want to feed it and name it somehow.", player->GetGUID());
	}


	bool OnGossipHello(Player *player, Creature * m_creature)
	{

		if (player->getClass() != CLASS_HUNTER)
		{
			m_creature->MonsterWhisper("You are not a Hunter!", player->GetGUID());
			return true;
		}
		player->ADD_GOSSIP_ITEM(4, "Get a New Pet.", GOSSIP_SENDER_MAIN, 30);
		if (player->CanTameExoticPets())
		{
			player->ADD_GOSSIP_ITEM(4, "Get a New Exotic Pet.", GOSSIP_SENDER_MAIN, 50);
		}
		player->ADD_GOSSIP_ITEM(2, "Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
		player->ADD_GOSSIP_ITEM(6, "Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
		player->ADD_GOSSIP_ITEM(5, "Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
		player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature * m_creature, uint32 sender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{

		case 100:
			player->ADD_GOSSIP_ITEM(4, "Get a New Pet.", GOSSIP_SENDER_MAIN, 30);
			if (player->CanTameExoticPets())
			{
				player->ADD_GOSSIP_ITEM(4, "Get a New Exotic Pet.", GOSSIP_SENDER_MAIN, 50);
			}
			player->ADD_GOSSIP_ITEM(2, "Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
			player->ADD_GOSSIP_ITEM(6, "Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
			player->ADD_GOSSIP_ITEM(5, "Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
			player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
			break;

		case 150:
			player->CLOSE_GOSSIP_MENU();
			break;