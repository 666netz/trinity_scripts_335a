#include "ScriptPCH.h"
#include "Player.h"
#include "Pet.h"

class ralph : public CreatureScript
{
public:
	ralph() : CreatureScript("ralph")
	{
	}

	bool OnGossipHello(Player * player, Creature * creature)
	{
		if (player->getClass() == CLASS_PALADIN)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1007); //PALADIN
		if (player->getClass() == CLASS_MAGE)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1008); //MAGE
		if (player->getClass() == CLASS_WARRIOR)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1009);//WARRIOR
		if (player->getClass() == CLASS_PRIEST)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1010);//PRIEST
		if (player->getClass() == CLASS_HUNTER)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1011); //HUNTER
		if (player->getClass() == CLASS_ROGUE)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1012); //ROGUE
		if (player->getClass() == CLASS_SHAMAN)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1013); //SHAMAN
		if (player->getClass() == CLASS_WARLOCK)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1014); //WARLOCK
		if (player->getClass() == CLASS_DRUID)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1015); //DRUID
		if (player->getClass() == CLASS_PALADIN)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1016); //PALADIN
		if (player->getClass() == CLASS_MAGE)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1017); //MAGE
		if (player->getClass() == CLASS_WARRIOR)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1018);//WARRIOR
		if (player->getClass() == CLASS_PRIEST)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1019);//PRIEST
		if (player->getClass() == CLASS_HUNTER)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1020); //HUNTER
		if (player->getClass() == CLASS_ROGUE)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1021); //ROGUE
		if (player->getClass() == CLASS_SHAMAN)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1022); //SHAMAN
		if (player->getClass() == CLASS_WARLOCK)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1023); //WARLOCK
		if (player->getClass() == CLASS_DRUID)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1024); //DRUID
		if (player->getClass() == CLASS_DEATH_KNIGHT)
			player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1025); //DK
		if (player->getClass() == CLASS_DEATH_KNIGHT)
			player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1026); //DK
		player->ADD_GOSSIP_ITEM(3, "Racials", GOSSIP_SENDER_MAIN, 1002);
		player->ADD_GOSSIP_ITEM(3, "Reset my talents", GOSSIP_SENDER_MAIN, 10000);
		if (player->getClass() == CLASS_HUNTER)
			player->ADD_GOSSIP_ITEM(3, "Reset my pet's talents", GOSSIP_SENDER_MAIN, 10003);
		if (player->GetSpecsCount() == 1)
		{
			player->ADD_GOSSIP_ITEM(3, "Teach me dual specialization", GOSSIP_SENDER_MAIN, 10002);
		}
		if (player->m_stableSlots == 1 && player->getClass() == CLASS_HUNTER)
		{
			player->ADD_GOSSIP_ITEM(3, "Give me four stable slots", GOSSIP_SENDER_MAIN, 10005);
		}
		if (player->getClass() == CLASS_HUNTER)
			player->ADD_GOSSIP_ITEM(3, "Hunter Pets", GOSSIP_SENDER_MAIN, 2032); //HUNTER
		player->ADD_GOSSIP_ITEM(6, "General goods", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
		player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);

		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}
	void CreatePet(Player *player, Creature * creature, uint32 entry)
	{
		if (player->getClass() != CLASS_HUNTER) {
			creature->Whisper("Only hunters can have a starter pet.", LANG_UNIVERSAL, player);
			player->PlayerTalkClass->SendCloseGossip();
			return;
		}

		if (player->GetPet())
		{
			creature->Whisper("You already have a pet. Put it in the stable or abandon it.", LANG_UNIVERSAL, player);
			player->PlayerTalkClass->SendCloseGossip();
			return;
		}

		Creature *creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
		if (!creatureTarget) return;

		Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
		if (!pet) return;

		creatureTarget->setDeathState(JUST_DIED);
		creatureTarget->RemoveCorpse();
		creatureTarget->SetHealth(0);                       // just for nice GM-mode view

		pet->SetPower(POWER_HAPPINESS, 1048000);

		pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
		pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());

		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
		pet->GetMap()->AddToMap(pet->ToCreature());

		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());

		pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);

		pet->UpdateAllStats();

		player->SetMinion(pet, true);

		pet->SavePetToDB(PET_SAVE_AS_CURRENT);
		pet->InitTalentForLevel();
		player->PetSpellInitialize();

		player->PlayerTalkClass->SendCloseGossip();

	}

	void SendDefaultMenu(Player * player, Creature * creature, uint32 uiAction)
	{

		if (player->IsInCombat())
		{
			player->CLOSE_GOSSIP_MENU();
			creature->Whisper("Leave combat before speaking to me.", LANG_UNIVERSAL, player);
			return;
		}

		WorldSession * m_session = player->GetSession();
		switch (uiAction)
		{

		case GOSSIP_OPTION_VENDOR:
			player->PlayerTalkClass->ClearMenus();
			player->GetSession()->SendListInventory(creature->GetGUID());
			break;

		case 2032:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "BY USING THESE OPTIONS YOU ACKNOWLEDGE THAT YOU MAY LOSE YOUR PET IF IT IS DISMISSED, DEAD OR MISSING FOR ANY REASON. YOU SHOULD STABLE ANY PETS YOU WISH TO KEEP.", GOSSIP_SENDER_MAIN, 2032);
			player->ADD_GOSSIP_ITEM(3, "YES, give me a racial based pet.", GOSSIP_SENDER_MAIN, 2033);
			player->ADD_GOSSIP_ITEM(3, "List of pets", GOSSIP_SENDER_MAIN, 2034);
			player->ADD_GOSSIP_ITEM(3, "NO, I do not want a pet", GOSSIP_SENDER_MAIN, 1006);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 2034:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(6, "Bat", GOSSIP_SENDER_MAIN, 2035);
			player->ADD_GOSSIP_ITEM(6, "Bear", GOSSIP_SENDER_MAIN, 2036);
			player->ADD_GOSSIP_ITEM(6, "Boar", GOSSIP_SENDER_MAIN, 2037);
			player->ADD_GOSSIP_ITEM(6, "Cat", GOSSIP_SENDER_MAIN, 2038);
			player->ADD_GOSSIP_ITEM(6, "Carrion Bird", GOSSIP_SENDER_MAIN, 2039);
			player->ADD_GOSSIP_ITEM(6, "Crab", GOSSIP_SENDER_MAIN, 2040);
			player->ADD_GOSSIP_ITEM(6, "Crocolisk", GOSSIP_SENDER_MAIN, 2041);
			player->ADD_GOSSIP_ITEM(6, "Dragonhawk", GOSSIP_SENDER_MAIN, 2042);
			player->ADD_GOSSIP_ITEM(6, "Gorilla", GOSSIP_SENDER_MAIN, 2043);
			player->ADD_GOSSIP_ITEM(6, "Hound", GOSSIP_SENDER_MAIN, 2044);
			player->ADD_GOSSIP_ITEM(6, "Hyena", GOSSIP_SENDER_MAIN, 2045);
			player->ADD_GOSSIP_ITEM(6, "Moth", GOSSIP_SENDER_MAIN, 2046);
			player->ADD_GOSSIP_ITEM(6, "Owl", GOSSIP_SENDER_MAIN, 2047);
			player->ADD_GOSSIP_ITEM(4, "Page 2", GOSSIP_SENDER_MAIN, 2048);
			if (player->HasSpell(53270))
				player->ADD_GOSSIP_ITEM(4, "Page 3 - Exotic", GOSSIP_SENDER_MAIN, 2057);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 2048:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(6, "Raptor", GOSSIP_SENDER_MAIN, 2049);
			player->ADD_GOSSIP_ITEM(6, "Ravager", GOSSIP_SENDER_MAIN, 2050);
			player->ADD_GOSSIP_ITEM(6, "Strider", GOSSIP_SENDER_MAIN, 2051);
			player->ADD_GOSSIP_ITEM(6, "Scorpid", GOSSIP_SENDER_MAIN, 2052);
			player->ADD_GOSSIP_ITEM(6, "Spider", GOSSIP_SENDER_MAIN, 2053);
			player->ADD_GOSSIP_ITEM(6, "Serpent", GOSSIP_SENDER_MAIN, 2054);
			player->ADD_GOSSIP_ITEM(6, "Turtle", GOSSIP_SENDER_MAIN, 2055);
			player->ADD_GOSSIP_ITEM(6, "Wasp", GOSSIP_SENDER_MAIN, 2056);
			player->ADD_GOSSIP_ITEM(4, "Page 1", GOSSIP_SENDER_MAIN, 2034);
			if (player->HasSpell(53270))
				player->ADD_GOSSIP_ITEM(4, "Page 3 - Exotic", GOSSIP_SENDER_MAIN, 2057);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 2057:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(6, "Chimaera", GOSSIP_SENDER_MAIN, 2058);
			player->ADD_GOSSIP_ITEM(6, "Core Hound", GOSSIP_SENDER_MAIN, 2059);
			player->ADD_GOSSIP_ITEM(6, "Devilsaur", GOSSIP_SENDER_MAIN, 2060);
			player->ADD_GOSSIP_ITEM(6, "Rhino", GOSSIP_SENDER_MAIN, 2061);
			player->ADD_GOSSIP_ITEM(6, "Silithid", GOSSIP_SENDER_MAIN, 2062);
			player->ADD_GOSSIP_ITEM(6, "Worm", GOSSIP_SENDER_MAIN, 2063);
			player->ADD_GOSSIP_ITEM(6, "Loque'nahak", GOSSIP_SENDER_MAIN, 2064);
			player->ADD_GOSSIP_ITEM(6, "Skoll", GOSSIP_SENDER_MAIN, 2065);
			player->ADD_GOSSIP_ITEM(6, "Gondria", GOSSIP_SENDER_MAIN, 2066);
			player->ADD_GOSSIP_ITEM(4, "Page 1", GOSSIP_SENDER_MAIN, 2034);
			player->ADD_GOSSIP_ITEM(4, "Page 2", GOSSIP_SENDER_MAIN, 2048);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 2033:
			player->PlayerTalkClass->SendCloseGossip();
			if (player->getRace() == RACE_HUMAN)
				CreatePet(player, creature, 26016);
			if (player->getRace() == RACE_ORC)
				CreatePet(player, creature, 26020);
			if (player->getRace() == RACE_DWARF)
				CreatePet(player, creature, 34025);
			if (player->getRace() == RACE_NIGHTELF)
				CreatePet(player, creature, 26021);
			if (player->getRace() == RACE_UNDEAD_PLAYER)
				CreatePet(player, creature, 26033);
			if (player->getRace() == RACE_TAUREN)
				CreatePet(player, creature, 34022);
			if (player->getRace() == RACE_GNOME)
				CreatePet(player, creature, 26020);
			if (player->getRace() == RACE_TROLL)
				CreatePet(player, creature, 26029);
			if (player->getRace() == RACE_BLOODELF)
				CreatePet(player, creature, 26024);
			if (player->getRace() == RACE_DRAENEI)
				CreatePet(player, creature, 34021);
			break;

		case 2058: //chimera
			CreatePet(player, creature, 21879);
			break;
		case 2059: //core hound
			CreatePet(player, creature, 21108);
			break;
		case 2060: //Devilsaur
			CreatePet(player, creature, 20931);
			break;
		case 2061: //rhino
			CreatePet(player, creature, 30445);
			break;
		case 2062: //silithid
			CreatePet(player, creature, 5460);
			break;
		case 2063: //Worm
			CreatePet(player, creature, 30148);
			break;
		case 2064: //Loque'nahak
			CreatePet(player, creature, 32517);
			break;
		case 2065: //Skoll
			CreatePet(player, creature, 35189);
			break;
		case 2066: //Gondria
			CreatePet(player, creature, 33776);
			break;
		case 2053: //Spider
			CreatePet(player, creature, 2349);
			break;
		case 2042: //Dragonhawk
			CreatePet(player, creature, 27946);
			break;
		case 2035: //Bat
			CreatePet(player, creature, 28233);
			break;
		case 2050: //Ravager
			CreatePet(player, creature, 17199);
			break;
		case 2049: //Raptor
			CreatePet(player, creature, 14821);
			break;
		case 2054: //Serpent
			CreatePet(player, creature, 28358);
			break;
		case 2036: //bear
			CreatePet(player, creature, 29319);
			break;
		case 2037: //Boar
			CreatePet(player, creature, 29996);
			break;
		case 2038: //cat
			CreatePet(player, creature, 28097);
			break;
		case 2039: //carrion
			CreatePet(player, creature, 26838);
			break;
		case 2040: //crab
			CreatePet(player, creature, 24478);
			break;
		case 2041: //crocolisk
			CreatePet(player, creature, 1417);
			break;
		case 2043: //gorila
			CreatePet(player, creature, 28213);
			break;
		case 2044: //hound
			CreatePet(player, creature, 29452);
			break;
		case 2045: //hynea
			CreatePet(player, creature, 13036);
			break;
		case 2046: //Moth
			CreatePet(player, creature, 27421);
			break;
		case 2047: //owl
			CreatePet(player, creature, 23136);
			break;
		case 2051: //strider
			CreatePet(player, creature, 22807);
			break;
		case 2052: //scorpid
			CreatePet(player, creature, 9698);
			break;
		case 2055: //turtle
			CreatePet(player, creature, 25482);
			break;
		case 2056: //wasp
			CreatePet(player, creature, 24731);
			break;

		case 1000:
			player->PlayerTalkClass->ClearMenus();
			if (player->getClass() == CLASS_PALADIN)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1007); //PALADIN
			if (player->getClass() == CLASS_MAGE)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1008); //MAGE
			if (player->getClass() == CLASS_WARRIOR)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1009);//WARRIOR
			if (player->getClass() == CLASS_PRIEST)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1010);//PRIEST
			if (player->getClass() == CLASS_HUNTER)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1011); //HUNTER
			if (player->getClass() == CLASS_ROGUE)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1012); //ROGUE
			if (player->getClass() == CLASS_SHAMAN)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1013); //SHAMAN
			if (player->getClass() == CLASS_WARLOCK)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1014); //WARLOCK
			if (player->getClass() == CLASS_DRUID)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1015); //DRUID
			if (player->getClass() == CLASS_PALADIN)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1016); //PALADIN
			if (player->getClass() == CLASS_MAGE)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1017); //MAGE
			if (player->getClass() == CLASS_WARRIOR)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1018);//WARRIOR
			if (player->getClass() == CLASS_PRIEST)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1019);//PRIEST
			if (player->getClass() == CLASS_HUNTER)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1020); //HUNTER
			if (player->getClass() == CLASS_ROGUE)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1021); //ROGUE
			if (player->getClass() == CLASS_SHAMAN)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1022); //SHAMAN
			if (player->getClass() == CLASS_WARLOCK)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1023); //WARLOCK
			if (player->getClass() == CLASS_DRUID)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1024); //DRUID
			if (player->getClass() == CLASS_DEATH_KNIGHT)
				player->ADD_GOSSIP_ITEM(3, "Class Path", GOSSIP_SENDER_MAIN, 1025); //DK
			if (player->getClass() == CLASS_DEATH_KNIGHT)
				player->ADD_GOSSIP_ITEM(3, "Major Glyphs", GOSSIP_SENDER_MAIN, 1026); //DK
			player->ADD_GOSSIP_ITEM(3, "Racials", GOSSIP_SENDER_MAIN, 1002);
			player->ADD_GOSSIP_ITEM(3, "Reset my talents", GOSSIP_SENDER_MAIN, 10000);
			if (player->getClass() == CLASS_HUNTER)
				player->ADD_GOSSIP_ITEM(3, "Reset my pet's talents", GOSSIP_SENDER_MAIN, 10003);
			if (player->GetSpecsCount() == 1)
			{
				player->ADD_GOSSIP_ITEM(3, "Teach me dual specialization", GOSSIP_SENDER_MAIN, 10002);
			}
			if (player->getClass() == CLASS_HUNTER)
				player->ADD_GOSSIP_ITEM(3, "Hunter Pets", GOSSIP_SENDER_MAIN, 2032); //HUNTER
			player->ADD_GOSSIP_ITEM(6, "General goods", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1007: //pally
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cffE066FFRetribution|r specialization features Divine Storm.", GOSSIP_SENDER_MAIN, 0);
			player->ADD_GOSSIP_ITEM(3, "The |cffFFFFFFHoly|r specialization features Flash of Light, Concentration Aura, and Improved Concentration Aura, which reduces the duration of any Silence or Interrupt effect used against an affected group member by 20%.", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(3, "The |cff2E37FEProtection|r specialization features Avenger's Shield and Shield of the Templar, which reduces all damage taken by 3% and grants your Avenger's Shield a 100% chance to silence your targets for 3 sec.", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1008: //mage
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff1D7CF2Arcane|r specialization features Mage Armor and Evocation.", GOSSIP_SENDER_MAIN, 2100);
			player->ADD_GOSSIP_ITEM(3, "The |cffB22222Fire|r specialization features Burning Soul, which reduces the pushback suffered the pushback suffered from damaging attacks while casting Fire spells by 70% and reduces the threat caused by your Fire spells by 20%.", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(3, "The |cff0EBFE9Frost|r specialization features Ice Barrier and Cone of Cold.", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1009: //warior
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff7B68EEArms|r specialization features Hamstring.", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(3, "The |cff8B2500Fury|r specialization features Dual Wield, Berserker Stance, and Whirlwind.", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(3, "The |cff8B5742Protection|r specialization features Hamstring.", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1010: //priest
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cffFFFFFFHoly|r specialization features Heal.", GOSSIP_SENDER_MAIN, 2102);
			player->ADD_GOSSIP_ITEM(3, "The |cff78AB46Discipline|r specialization features Heal.", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(3, "The |cff757575Shadow|r specialization features Shadowform, Dispersion, Mind Flay and Vampiric Touch.", GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1011: //hunter
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff800000Marksmanship|r specialization features Arcane Shot.", GOSSIP_SENDER_MAIN, 2103);
			player->ADD_GOSSIP_ITEM(3, "The |cff7BCC70Survival|r specialization features Feign Death.", GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(3, "The |cff8A2BE2Beastmastery|r specialization features Beast Mastery and Kill Command", GOSSIP_SENDER_MAIN, 2101);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1012: //rogue
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff838EDESubtlety|r specialization features Hemorrhage.", GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(3, "The |cff8B3626Assassination|r specialization features Mutilate.", GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(3, "The |cff87CEEBCombat|r specialization features Adrenaline Rush.", GOSSIP_SENDER_MAIN, 17);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1013: //shaman
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff7BBF6ARestoration|r specialization features Purge, Earthliving Weapon and Healing Focus, which reduces the pushback suffered from damaging attacks while casting any Shaman healing spell by 70%.", GOSSIP_SENDER_MAIN, 18);
			player->ADD_GOSSIP_ITEM(3, "The |cffD9D919Enhancement|r specialization features Dual Wield, Stormstrike, Wind Shear and Improved Stormstrike, so when you Stormstrike you have a 100% chance to immediately grant you 20% of your base mana.", GOSSIP_SENDER_MAIN, 19);
			player->ADD_GOSSIP_ITEM(3, "The |cff912CEEElemental|r specialization features Purge and Wind Shear.", GOSSIP_SENDER_MAIN, 20);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1014: //warlock
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff9CCB19Affliciton|r specialization features Curse of Agony and Corruption.", GOSSIP_SENDER_MAIN, 21);
			player->ADD_GOSSIP_ITEM(3, "The |cffA020F0Demonology|r specialization  features Summon Felguard, Demonic Empowerment, and Demonic Circle.", GOSSIP_SENDER_MAIN, 22);
			player->ADD_GOSSIP_ITEM(3, "The |cff9E0508Destruction|r specialization features Conflagrate and Backlash (Rank 3).", GOSSIP_SENDER_MAIN, 23);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1015: //druid
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff8968CDGuardian|r specialization features Survival of the Fittest, which increases all attributes by 6 %, reduces the chance you'll be critically hit by melee attacks by 6%, and increases your armor contribution from cloth and leather items in Bear Form and Dire Bear Form by 33%.", GOSSIP_SENDER_MAIN, 24);
			player->ADD_GOSSIP_ITEM(3, "The |cffE6E6FABalance|r specialization features Moonkin Form, Typhoon, and Eclipse (Rank 3).", GOSSIP_SENDER_MAIN, 25);
			player->ADD_GOSSIP_ITEM(3, "The |cff7BBF6ARestoration|r specialization features Regrowth.", GOSSIP_SENDER_MAIN, 26);
			player->ADD_GOSSIP_ITEM(3, "The |cff7B3F00Feral|r specialization features Cat Form.", GOSSIP_SENDER_MAIN, 27);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1025: //DK
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "The |cff5C0000Blood|r specialization features Dancing Rune Weapon and Rune Tap", GOSSIP_SENDER_MAIN, 9900);
			player->ADD_GOSSIP_ITEM(3, "The |cff0099CCFrost|r specialization features Chillblains, which reduces movement speed by 15% for victims of Frost Fever, and Acclimation, which gives a stacking resistance to a spell type when struck with it.", GOSSIP_SENDER_MAIN, 9901);
			player->ADD_GOSSIP_ITEM(3, "The |cff006600Unholy|r specialization features Anti-Magic Zone and Desecration, which causes your plague strike to cause the desecrated ground effect, reducing movement speed inside the desecrated ground by 50%", GOSSIP_SENDER_MAIN, 9902);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 1002:
		{
			player->PlayerTalkClass->ClearMenus();
			if (player->getClass() == CLASS_PALADIN)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Dwarf Racials|r - Stoneform, Gun Specialization, Frost Resistance, Find Treasure, and Mace Specialization", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Blood Elf Racials|r - Arcane Torrent and Magic Resistance", GOSSIP_SENDER_MAIN, 36);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Draenei Racials|r - Gift of the Naaru, Heroic Presence, and Shadow Resistance", GOSSIP_SENDER_MAIN, 37);
			}
			if (player->getClass() == CLASS_DRUID)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Night Elf Racials|r - Shadowmeld, Quickness, Wisp Spirit and Nature Resistance", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Tauren Racials|r - War Stomp, Endurance, and Nature Resistance", GOSSIP_SENDER_MAIN, 33);
			}
			if (player->getClass() == CLASS_HUNTER)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Orc Racials|r - Blood Fury, Hardiness, Command, and Axe Specialization", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Dwarf Racials|r - Stoneform, Gun Specialization, Frost Resistance, Find Treasure, and Mace Specialization", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Night Elf Racials|r - Shadowmeld, Quickness, Wisp Spirit and Nature Resistance", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Tauren Racials|r - War Stomp, Endurance, and Nature Resistance", GOSSIP_SENDER_MAIN, 33);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Troll Racials|r - Berserking, Regeneration, Beast Slaying, Throwing Specialization, Bow Specialization and The Voodoo Shuffle", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Blood Elf Racials|r - Arcane Torrent and Magic Resistance", GOSSIP_SENDER_MAIN, 36);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Draenei Racials|r - Gift of the Naaru, Heroic Presence, and Shadow Resistance", GOSSIP_SENDER_MAIN, 37);
			}
			if (player->getClass() == CLASS_MAGE)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Undead Racials|r - Will of the Forsaken, Cannibalize, Underwater Breathing and Shadow Resistance", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Gnome Racials|r - Escape Artist, Expansive Mind, and Arcane Resistance", GOSSIP_SENDER_MAIN, 34);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Troll Racials|r - Berserking, Regeneration, Beast Slaying, Throwing Specialization, Bow Specialization and The Voodoo Shuffle", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Blood Elf Racials|r - Arcane Torrent and Magic Resistance", GOSSIP_SENDER_MAIN, 36);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Draenei Racials|r - Gift of the Naaru, Heroic Presence, and Shadow Resistance", GOSSIP_SENDER_MAIN, 37);
			}
			if (player->getClass() == CLASS_WARLOCK)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Orc Racials|r - Blood Fury, Hardiness, Command, and Axe Specialization", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Undead Racials|r - Will of the Forsaken, Cannibalize, Underwater Breathing and Shadow Resistance", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Gnome Racials|r - Escape Artist, Expansive Mind, and Arcane Resistance", GOSSIP_SENDER_MAIN, 34);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Blood Elf Racials|r - Arcane Torrent and Magic Resistance", GOSSIP_SENDER_MAIN, 36);
			}
			if (player->getClass() == CLASS_SHAMAN)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Orc Racials|r - Blood Fury, Hardiness, Command, and Axe Specialization", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Tauren Racials|r - War Stomp, Endurance, and Nature Resistance", GOSSIP_SENDER_MAIN, 33);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Troll Racials|r - Berserking, Regeneration, Beast Slaying, Throwing Specialization, Bow Specialization and The Voodoo Shuffle", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Draenei Racials|r - Gift of the Naaru, Heroic Presence, and Shadow Resistance", GOSSIP_SENDER_MAIN, 37);
			}
			if (player->getClass() == CLASS_WARRIOR)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Orc Racials|r - Blood Fury, Hardiness, Command, and Axe Specialization", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Dwarf Racials|r - Stoneform, Gun Specialization, Frost Resistance, Find Treasure, and Mace Specialization", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Night Elf Racials|r - Shadowmeld, Quickness, Wisp Spirit and Nature Resistance", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Undead Racials|r - Will of the Forsaken, Cannibalize, Underwater Breathing and Shadow Resistance", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Tauren Racials|r - War Stomp, Endurance, and Nature Resistance", GOSSIP_SENDER_MAIN, 33);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Gnome Racials|r - Escape Artist, Expansive Mind, and Arcane Resistance", GOSSIP_SENDER_MAIN, 34);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Troll Racials|r - Berserking, Regeneration, Beast Slaying, Throwing Specialization, Bow Specialization and The Voodoo Shuffle", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Draenei Racials|r - Gift of the Naaru, Heroic Presence, and Shadow Resistance", GOSSIP_SENDER_MAIN, 37);
			}
			if (player->getClass() == CLASS_PRIEST)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Dwarf Racials|r - Stoneform, Gun Specialization, Frost Resistance, Find Treasure, and Mace Specialization", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Night Elf Racials|r - Shadowmeld, Quickness, Wisp Spirit and Nature Resistance", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Undead Racials|r - Will of the Forsaken, Cannibalize, Underwater Breathing and Shadow Resistance", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Troll Racials|r - Berserking, Regeneration, Beast Slaying, Throwing Specialization, Bow Specialization and The Voodoo Shuffle", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Blood Elf Racials|r - Arcane Torrent and Magic Resistance", GOSSIP_SENDER_MAIN, 36);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Draenei Racials|r - Gift of the Naaru, Heroic Presence, and Shadow Resistance", GOSSIP_SENDER_MAIN, 37);
			}
			if (player->getClass() == CLASS_ROGUE)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Orc Racials|r - Blood Fury, Hardiness, Command, and Axe Specialization", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Dwarf Racials|r - Stoneform, Gun Specialization, Frost Resistance, Find Treasure, and Mace Specialization", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Night Elf Racials|r - Shadowmeld, Quickness, Wisp Spirit and Nature Resistance", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Undead Racials|r - Will of the Forsaken, Cannibalize, Underwater Breathing and Shadow Resistance", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Gnome Racials|r - Escape Artist, Expansive Mind, and Arcane Resistance", GOSSIP_SENDER_MAIN, 34);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Troll Racials|r - Berserking, Regeneration, Beast Slaying, Throwing Specialization, Bow Specialization and The Voodoo Shuffle", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Blood Elf Racials|r - Arcane Torrent and Magic Resistance", GOSSIP_SENDER_MAIN, 36);
			}
			if (player->getClass() == CLASS_DEATH_KNIGHT)
			{
				player->ADD_GOSSIP_ITEM(3, "|cff339966Human Racials|r - Perception, The Human Spirit, Diplomacy, Sword Specialization, Mace Specialization, Every Man For Himself", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Orc Racials|r - Blood Fury, Hardiness, Command, and Axe Specialization", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Dwarf Racials|r - Stoneform, Gun Specialization, Frost Resistance, Find Treasure, and Mace Specialization", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Night Elf Racials|r - Shadowmeld, Quickness, Wisp Spirit and Nature Resistance", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Undead Racials|r - Will of the Forsaken, Cannibalize, Underwater Breathing and Shadow Resistance", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Tauren Racials|r - War Stomp, Endurance, and Nature Resistance", GOSSIP_SENDER_MAIN, 33);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Gnome Racials|r - Escape Artist, Expansive Mind, and Arcane Resistance", GOSSIP_SENDER_MAIN, 34);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Troll Racials|r - Berserking, Regeneration, Beast Slaying, Throwing Specialization, Bow Specialization and The Voodoo Shuffle", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Blood Elf Racials|r - Arcane Torrent and Magic Resistance", GOSSIP_SENDER_MAIN, 36);
				player->ADD_GOSSIP_ITEM(3, "|cff339966Draenei Racials|r - Gift of the Naaru, Heroic Presence, and Shadow Resistance", GOSSIP_SENDER_MAIN, 37);
			}
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1006: // Close Gossips
		{
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;

		case 1016: //paladin glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Beacon of Light|r - Increases the duration of Beacon of Light by 30 sec", GOSSIP_SENDER_MAIN, 390);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Seal of Righteousness|r - Increases the damage done by Seal of Righteousness by 10%", GOSSIP_SENDER_MAIN, 391);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Holy Shock|r - Increases the critical effect chance of Holy Shock by 5%", GOSSIP_SENDER_MAIN, 392);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Seal of Wisdom|r - While Seal of Wisdom is active, the cost of your healing spells is reduced by 5%", GOSSIP_SENDER_MAIN, 393);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Cleansing|r - Reduces the mana cost of your Cleanse by 20%", GOSSIP_SENDER_MAIN, 394);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Seal of Light|r - While Seal of Light is active, the effect of your healing spells is increased by 5%", GOSSIP_SENDER_MAIN, 395);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Turn Evil|r - Reduces the casting time of your Turn Evil spell by 100%, but increases the cooldown by 8 sec", GOSSIP_SENDER_MAIN, 396);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Flash of Light|r - Your Flash of Light has an additional 5% critical strike chance", GOSSIP_SENDER_MAIN, 397);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Consecration|r - Increases the duration and cooldown of Consecration by 2 sec", GOSSIP_SENDER_MAIN, 398);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Exorcism|r - Your Exorcism causes an additional 20% of its damage over 6 sec", GOSSIP_SENDER_MAIN, 399);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5438);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5439);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5438: //paladin glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Holy Light|r - Your Holy Light grants 10% of its heal amount to up to 5 friendly targets within 8 yards of the initial target", GOSSIP_SENDER_MAIN, 400);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Lay on Hands|r - Your Lay on Hands grants twice as much mana as normal and also grants you as much mana as it grants your target", GOSSIP_SENDER_MAIN, 401);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Holy Wrath|r - Reduces the cooldown of your Holy Wrath spell by 15 sec", GOSSIP_SENDER_MAIN, 402);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shield of Righteousness|r - Reduces the mana cost of Shield of Righteousness by 80%", GOSSIP_SENDER_MAIN, 403);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Divine Plea|r - While Divine Plea is active, you take 3% reduced damage from all sources", GOSSIP_SENDER_MAIN, 404);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hammer of the Righteous|r - Your Hammer of the Righteous hits 1 additional target", GOSSIP_SENDER_MAIN, 405);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Avenger's Shield|r - Your Avenger's Shield hits 2 fewer targets, but for 100% more damage", GOSSIP_SENDER_MAIN, 406);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Salvation|r - When you cast Hand of Salvation on yourself, it also reduces damage taken by 20%", GOSSIP_SENDER_MAIN, 407);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Spiritual Attunement|r - Increases the amount of mana gained from your Spiritual Attunement spell by an additional 2%", GOSSIP_SENDER_MAIN, 40);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hammer of Justice|r - Increases your Hammer of Justice range by 5 yards", GOSSIP_SENDER_MAIN, 409);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1016);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5439);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5439: //paladin glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Righteous Defense|r - Increases the chance for your Righteous Defense and Hand of Reckoning abilities to work successfully by 8% on each target", GOSSIP_SENDER_MAIN, 410);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Avenging Wrath|r - Reduces the cooldown of your Hammer of Wrath spell by 50% while Avenging Wrath is active", GOSSIP_SENDER_MAIN, 411);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Divine Storm|r - Your Divine Storm now heals for an additional 15% of the damage it causes", GOSSIP_SENDER_MAIN, 412);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Seal of Righteousness|r - Increases the damage done by Seal of Righteousness by 10%", GOSSIP_SENDER_MAIN, 413);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Seal of Vengeance|r - Your Seal of Vengeance or Seal of Corruption also grants 10 expertise while active", GOSSIP_SENDER_MAIN, 414);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hammer of Wrath|r - Reduces the mana cost of Hammer of Wrath by 100%", GOSSIP_SENDER_MAIN, 415);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Crusader Strike|r - Reduces the mana cost of your Crusader Strike ability by 20%", GOSSIP_SENDER_MAIN, 416);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Seal of Command|r - You gain 8% of your base mana each time you use a Judgement with Seal of Command active", GOSSIP_SENDER_MAIN, 417);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Judgement|r - Your Judgements deal 10% more damage", GOSSIP_SENDER_MAIN, 418);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1016);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5438);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1017: //mage glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mirror Image|r - Your Mirror Image spell now creates a 4th copy", GOSSIP_SENDER_MAIN, 360);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Frostfire|r - Increases the initial damage dealt by Frostfire Bolt by 2% and its critical strike chance by 2%", GOSSIP_SENDER_MAIN, 361);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Blast Wave|r - The mana cost of your Blast Wave spell is reduced by 15%, but it no longer knocks enemies back", GOSSIP_SENDER_MAIN, 362);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Invisibility|r - Increases the duration of the Invisibility effect by 10 sec", GOSSIP_SENDER_MAIN, 363);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Ice Lance|r - Your Ice Lance now causes 4 times damage against frozen targets higher level than you instead of triple damage", GOSSIP_SENDER_MAIN, 364);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Arcane Blast|r - Increases the damage from your Arcane Blast buff by 3%", GOSSIP_SENDER_MAIN, 365);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Molten Armor|r - Your Molten Armor spell grants an additional 20% of your spirit as critical strike rating", GOSSIP_SENDER_MAIN, 366);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Living Bomb|r - The periodic damage from your Living Bomb can now be critical strikes", GOSSIP_SENDER_MAIN, 367);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Arcane Barrage|r - Reduces the mana cost of Arcane Barrage by 20%", GOSSIP_SENDER_MAIN, 368);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Deep Freeze|r - Increases the range of Deep Freeze by 10 yards", GOSSIP_SENDER_MAIN, 369);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5436);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5437);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5436: //mage glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Eternal Water|r - Your Summon Water Elemental now lasts indefinitely, but your Water Elemental can no longer cast Freeze", GOSSIP_SENDER_MAIN, 370);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Water Elemental|r - Reduces the cooldown of your Summon Water Elemental spell by 30 sec", GOSSIP_SENDER_MAIN, 371);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Ice Barrier|r - Increases the amount of damage absorbed by your Ice Barrier by 30%", GOSSIP_SENDER_MAIN, 372);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Arcane Power|r - Increases the duration of Arcane Power by 3 sec", GOSSIP_SENDER_MAIN, 373);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mage Armor|r - Your Mage Armor spell grants an additional 20% mana regeneration while casting", GOSSIP_SENDER_MAIN, 374);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Ice Block|r - Your Frost Nova cooldown is now reset every time you use Ice Block", GOSSIP_SENDER_MAIN, 375);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mana Gem|r - Increases the mana received from using a mana gem by 40%", GOSSIP_SENDER_MAIN, 376);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Blink|r - Increases the distance you travel with the Blink spell by 5 yards", GOSSIP_SENDER_MAIN, 377);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Evocation|r - Your Evocation ability also causes you to regain 60% of your health over its duration", GOSSIP_SENDER_MAIN, 378);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Icy Veins|r - Your Icy Veins ability also removes all movement slowing and cast time slowing effects", GOSSIP_SENDER_MAIN, 379);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1017);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5437);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5437: //mage glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Scorch|r - Increases the damage of your Scorch spell by 20%", GOSSIP_SENDER_MAIN, 380);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Remove Curse|r - Your Remove Curse spell also makes the target immune to all curses for 4 sec.", GOSSIP_SENDER_MAIN, 381);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Arcane Explosion|r - Reduces mana cost of Arcane Explosion by 10%", GOSSIP_SENDER_MAIN, 382);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Arcane Missiles|r - Increases the critical strike damage bonus of Arcane Missiles by 25%", GOSSIP_SENDER_MAIN, 383);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fire Blast|r - Increases the critical strike chance of Fire Blast by 50% when the target is stunned or incapacitated", GOSSIP_SENDER_MAIN, 384);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fireball|r - Reduces the casting time of your Fireball spell by 0.15 sec, but removes the damage over time effect", GOSSIP_SENDER_MAIN, 385);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Frostbolt|r - Increases the damage dealt by Frostbolt by 5%, but removes the slowing effect", GOSSIP_SENDER_MAIN, 386);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Frost Nova|r - Your Frost Nova targets can take an additional 20% damage before the Frost Nova effect automatically breaks", GOSSIP_SENDER_MAIN, 387);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Ice Armor|r - Your Ice Armor and Frost Armor spells grant an additional 50% armor and resistance", GOSSIP_SENDER_MAIN, 388);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Polymorph|r - Your Polymorph spell also removes all damage over time effects from the target", GOSSIP_SENDER_MAIN, 389);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1017);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5436);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1018: //warrior glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Bladestorm|r - Reduces the cooldown on Bladestorm by 15 sec", GOSSIP_SENDER_MAIN, 531);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mortal Strike|r - Increases the damage of your Mortal Strike ability by 10%", GOSSIP_SENDER_MAIN, 532);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Barbaric Insults|r - Your Mocking Blow ability generates 100% additional threat", GOSSIP_SENDER_MAIN, 533);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hamstring|r - Gives your Hamstring ability a 10% chance to immobilize the target for 5 sec", GOSSIP_SENDER_MAIN, 534);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Heroic Strike|r - You gain 10 rage when you critically strike with your Heroic Strike ability", GOSSIP_SENDER_MAIN, 535);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Overpower|r - Adds a 100% chance to enable your Overpower when your attacks are parried", GOSSIP_SENDER_MAIN, 536);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rapid Charge|r - Reduces the cooldown of your Charge ability by 7%", GOSSIP_SENDER_MAIN, 537);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rending|r - Increases the duration of your Rend ability by 6 sec", GOSSIP_SENDER_MAIN, 538);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Resonating Power|r - Reduces the rage cost of your Thunder Clap ability by 5", GOSSIP_SENDER_MAIN, 539);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Enraged Regeneration|r - Your Enraged Regeneration ability heals for an additional 10% of your health over its duration", GOSSIP_SENDER_MAIN, 540);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5448);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5449);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5448: //warrior glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Victory Rush|r - Your Victory Rush ability has a 30% increased critical strike chance", GOSSIP_SENDER_MAIN, 541);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Bloodthirst|r - Increases the healing you receive from your Bloodthirst ability by 100%", GOSSIP_SENDER_MAIN, 542);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Whirlwind|r - Reduces the cooldown of your Whirlwind by 2 sec.", GOSSIP_SENDER_MAIN, 543);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Sweeping Strikes|r - Reduces the rage cost of your Sweeping Strikes ability by 100%", GOSSIP_SENDER_MAIN, 544);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Execution|r - Your Execute ability deals damage as if you had 10 additional rage", GOSSIP_SENDER_MAIN, 545);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Cleaving|r - Increases the number of targets your Cleave hits by 1", GOSSIP_SENDER_MAIN, 546);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Intervene|r - Increases the number attacks you intercept for your Intervene target by 1", GOSSIP_SENDER_MAIN, 547);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Spell Reflection|r - Reduces the cooldown on Spell Reflection by 1 sec", GOSSIP_SENDER_MAIN, 548);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shockwave|r - Reduces the cooldown on Shockwave by 3 sec", GOSSIP_SENDER_MAIN, 549);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Blocking|r - Increases your block value by 10% for 10 sec after using your Shield Slam ability", GOSSIP_SENDER_MAIN, 550);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1018);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5449);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5449: //warrior glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Devastate|r - Your Devastate ability now applies two stacks of Sunder Armor", GOSSIP_SENDER_MAIN, 551);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Vigilance|r - Your Vigilance ability transfers an additional 5% of your target's threat to you", GOSSIP_SENDER_MAIN, 552);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shield Wall|r - Reduces the cooldown on Shield Wall by 2 min, but Shield Wall now only reduces damage taken by 40%", GOSSIP_SENDER_MAIN, 553);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Last Stand|r - Reduces the cooldown of your Last Stand ability by 1 min", GOSSIP_SENDER_MAIN, 554);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Revenge|r - After using Revenge, your next Heroic Strike costs no rage", GOSSIP_SENDER_MAIN, 555);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Sunder Armor|r - Your Sunder Armor ability affects a second nearby target", GOSSIP_SENDER_MAIN, 556);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Taunt|r - Increases the chance for your Taunt ability to succeed by 8%", GOSSIP_SENDER_MAIN, 557);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1018);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5448);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1019: //priest glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mass Dispel|r - Reduces the mana cost of Mass Dispel by 35%", GOSSIP_SENDER_MAIN, 419);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Penance|r - Reduces the cooldown of Penance by 2 sec", GOSSIP_SENDER_MAIN, 420);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Pain Suppression|r - Allows Pain Suppression to be cast while stunned", GOSSIP_SENDER_MAIN, 421);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Dispel Magic|r - Your Dispel Magic spell also heals your target for 3% of maximum health", GOSSIP_SENDER_MAIN, 422);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Inner Fire|r - Increases the armor from your Inner Fire spell by 50%", GOSSIP_SENDER_MAIN, 423);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Power Word: Shield|r - Your Power Word: Shield also heals the target for 20% of the absorption amount", GOSSIP_SENDER_MAIN, 424);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Guardian Spirit|r - If your Guardian Spirit lasts its entire duration without being triggered, the cooldown is reset to 1 min", GOSSIP_SENDER_MAIN, 425);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hymn of  Hope|r - Your Hymn of Hope lasts an additional 2 sec", GOSSIP_SENDER_MAIN, 426);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Circle of Healing|r - Your Circle of Healing spell heals 1 additional target", GOSSIP_SENDER_MAIN, 427);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Lightwell|r - Increases the amount healed by your Lightwell by 20%", GOSSIP_SENDER_MAIN, 428);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5440);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5441);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5440: //priest glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Prayer of Healing|r - Your Prayer of Healing spell also heals an additional 20% of its initial heal over 6 sec", GOSSIP_SENDER_MAIN, 429);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Flash Heal|r - Reduces the mana cost of your Flash Heal by 10%", GOSSIP_SENDER_MAIN, 430);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Holy Nova|r - Increases the damage and healing of your Holy Nova spell by an additional 20%", GOSSIP_SENDER_MAIN, 431);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Renew|r - Reduces the duration of your Renew by 3 sec. but increases the amount healed each tick by 25%", GOSSIP_SENDER_MAIN, 432);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Divine Plea|r - While Divine Plea is active, you take 3% reduced damage from all sources", GOSSIP_SENDER_MAIN, 433);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Smite|r - Your Smite spell inflicts an additional 20% damage against targets afflicted by Holy Fire", GOSSIP_SENDER_MAIN, 434);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Spirit of Redemption|r - Increases the duration of Spirit of Redemption by 6 sec", GOSSIP_SENDER_MAIN, 435);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mind Sear|r - Increases the radius of effect on Mind Sear by 5 yards", GOSSIP_SENDER_MAIN, 436);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shadow Word: Death|r - Targets below 35% health take an additional 10% damage from your Shadow Word: Death spell", GOSSIP_SENDER_MAIN, 437);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Dispersion|r - Reduces the cooldown on Dispersion by 45 sec", GOSSIP_SENDER_MAIN, 438);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1019);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5441);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5441: //priest glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mind Control|r - Reduces the chance targets will resist or break your Mind Control spell by an additional 17%", GOSSIP_SENDER_MAIN, 439);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fear Ward|r - Reduces cooldown and duration of Fear Ward by 30 sec", GOSSIP_SENDER_MAIN, 440);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mind Flay|r - Increases the damage done by your Mind Flay spell by 10% when your target is afflicted with Shadow Word: Pain", GOSSIP_SENDER_MAIN, 441);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shadow|r - While in Shadowform, your non-periodic spell critical strikes increase your spell power by 30% of your Spirit for 10 sec", GOSSIP_SENDER_MAIN, 442);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Psychic Scream|r - Increases the duration of your Psychic Scream by 2 sec. and increases its cooldown by 8 sec", GOSSIP_SENDER_MAIN, 443);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fade|r - Reduces the cooldown of your Fade spell by 9 sec", GOSSIP_SENDER_MAIN, 444);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shadow Word: Pain|r - The periodic damage ticks of your Shadow Word: Pain spell restore 1% of your base mana", GOSSIP_SENDER_MAIN, 445);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Scourge Imprisonment|r - Reduces the cast time of your Shackle Undead by 1 sec", GOSSIP_SENDER_MAIN, 446);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1019);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5440);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1020: //hunter glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Kill Shot|r - Reduces the cooldown of Kill Shot by 6 sec", GOSSIP_SENDER_MAIN, 332);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Snake Trap|r - Snakes generated by your Snake Trap take 90% reduced damge from area of effect spells", GOSSIP_SENDER_MAIN, 333);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Steady Shot|r - Increases the damage dealt by Steady Shot by 10% when your target is afflicted with Serpent Sting", GOSSIP_SENDER_MAIN, 334);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Chimera Shot|r - Reduces the cooldown of Chimera Shot by 1 sec", GOSSIP_SENDER_MAIN, 335);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Explosive Shot|r - Increases the critical strike chance of Explosive Shot by 4%", GOSSIP_SENDER_MAIN, 336);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Trueshot Aura|r - While your Trueshot Aura is active, you have 10% increased critical strike chance on your Aimed Shot", GOSSIP_SENDER_MAIN, 337);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Volley|r - Decreases the mana cost of Volley by 20%", GOSSIP_SENDER_MAIN, 338);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Wyvern Sting|r - Decreases the cooldown of your Wyvern Sting by 6 sec", GOSSIP_SENDER_MAIN, 339);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Bestial Wrath|r - Decreases the cooldown of Bestial Wrath by 20 sec", GOSSIP_SENDER_MAIN, 340);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Kill Shot|r - Reduces the cooldown of Kill Shot by 6 sec", GOSSIP_SENDER_MAIN, 341);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5434);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5435);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5434: //hunter glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Explosive Trap|r - The periodic damage from your Explosive Trap can now be critical strikes", GOSSIP_SENDER_MAIN, 342);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of the Beast|r - Increases the attack power bonus of Aspect of the Beast for you and your pet by an additional 2%", GOSSIP_SENDER_MAIN, 343);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Frost Trap|r - Increases the radius of the effect from your Frost Trap by 2 yards", GOSSIP_SENDER_MAIN, 344);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rapid Fire|r - Increases the haste from Rapid Fire by an additional 8%", GOSSIP_SENDER_MAIN, 345);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Deterrence|r - Decreases the cooldown of Deterrence by 10 sec", GOSSIP_SENDER_MAIN, 346);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Aspect of the Viper|r - Increases the amount of mana gained from attacks while Aspect of the Viper is active by 10%", GOSSIP_SENDER_MAIN, 347);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Disengage|r - Decreases the cooldown of Disengage by 5 sec", GOSSIP_SENDER_MAIN, 348);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Scatter Shot|r - Increases the range of Scatter Shot by 3 yards", GOSSIP_SENDER_MAIN, 349);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Freezing Trap|r - When your Freezing Trap breaks, the victim's movement speed is reduced by 30% for 4 sec", GOSSIP_SENDER_MAIN, 350);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Aimed Shot|r - Reduces the cooldown of your Aimed Shot ability by 2 sec", GOSSIP_SENDER_MAIN, 351);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1020);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5435);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5435: //hunter glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Multi-Shot|r - Decreases the cooldown of Multi-Shot by 1 sec", GOSSIP_SENDER_MAIN, 352);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Immolation Trap|r - Decreases the duration of the effect from your Immolation Trap by 6 sec., but damage while active is increased by 100%", GOSSIP_SENDER_MAIN, 353);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Arcane Shot|r - Your Arcane Shot refunds 20% of its mana cost if the target has one of your Stings active on it", GOSSIP_SENDER_MAIN, 354);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Improved Aspect of the Hawk|r - Increases the haste bonus of the Improved Aspect of the Hawk effect by an additional 6%", GOSSIP_SENDER_MAIN, 355);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hunter's Mark|r - Increases the attack power bonus of your Hunter's Mark by 20%", GOSSIP_SENDER_MAIN, 356);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mending|r - Increases the healing done by your Mend Pet ability by 40%", GOSSIP_SENDER_MAIN, 357);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Raptor Strike|r - Reduces damage taken by 20% for 3 sec after using Raptor Strike", GOSSIP_SENDER_MAIN, 358);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Serpent Sting|r - Increases the duration of your Serpent Sting by 6 sec", GOSSIP_SENDER_MAIN, 359);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1020);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5434);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1021: //rogue glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fan of Knives|r - Increases the damage done by Fan of Knives by 20%", GOSSIP_SENDER_MAIN, 447);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Tricks of the Trade|r - The bonus damage and threat redirection granted by your Tricks of the Trade ability lasts an additional 4 sec", GOSSIP_SENDER_MAIN, 448);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Vigor|r - Vigor grants an additional 10 maximum energy", GOSSIP_SENDER_MAIN, 449);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Cloak of Shadows|r - While Cloak of Shadows is active, you take 40% less physical damage", GOSSIP_SENDER_MAIN, 450);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Deadly Throw|r - Increases the slowing effect on Deadly Throw by 20%", GOSSIP_SENDER_MAIN, 451);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hunger for Blood|r - Increases the bonus damage from Hunger For Blood by 3%", GOSSIP_SENDER_MAIN, 452);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shadow Dance|r - Increases the duration of Shadow Dance by 2 sec", GOSSIP_SENDER_MAIN, 453);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Killing Spree|r - Reduces the cooldown on Killing Spree by 45 sec", GOSSIP_SENDER_MAIN, 454);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mutilate|r - Reduces the cost of Mutilate by 5 energy", GOSSIP_SENDER_MAIN, 455);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Adrenaline Rush|r - Increases the duration of Adrenaline Rush by 5 sec", GOSSIP_SENDER_MAIN, 456);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5442);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5443);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5442: //rogue glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Blade Flurry|r - Reduces the penalty to energy regeneration while Blade Flurry is active by 50%", GOSSIP_SENDER_MAIN, 457);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hemorrhage|r - Increases the damage bonus against targets afflicted by Hemorrhage by 40%", GOSSIP_SENDER_MAIN, 458);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Preparation|r - Your Preparation ability also instantly resets the cooldown of Blade Flurry, Dismantle, and Kick", GOSSIP_SENDER_MAIN, 459);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rupture|r - Increases the duration of Rupture by 4 sec", GOSSIP_SENDER_MAIN, 460);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Crippling Poison|r - Increases the chance to inflict your target with Crippling Poison by an additional 20%", GOSSIP_SENDER_MAIN, 461);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Ghostly Strike|r - Increases the damage dealt by Ghostly Strike by 40% and the duration of its effect by 4 sec., but increases its cooldown by 10 sec", GOSSIP_SENDER_MAIN, 462);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Ambush|r - Increases the range on Ambush by 5 yards", GOSSIP_SENDER_MAIN, 463);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Feint|r - Reduces the energy cost of Feint by 20", GOSSIP_SENDER_MAIN, 464);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Backstab|r - Your Backstab increases the duration of your Rupture effect on the target by 2 sec, up to a maximum of 6 additional sec", GOSSIP_SENDER_MAIN, 465);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Expose Armor|r - Increases the duration of Expose Armor by 12 sec", GOSSIP_SENDER_MAIN, 466);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1021);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5443);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5443: //rogue glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Evasion|r - Increases the duration of Evasion by 5 sec", GOSSIP_SENDER_MAIN, 467);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Eviscerate|r - Increases the critical strike chance of Eviscerate by 10%", GOSSIP_SENDER_MAIN, 468);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Garrote|r - Reduces the duration of your Garrote ability by 3 sec and increases the total damage it deals by 20%", GOSSIP_SENDER_MAIN, 469);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Gouge|r - Reduces the energy cost of Gouge by 15", GOSSIP_SENDER_MAIN, 470);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Sap|r - Increases the duration of Sap by 20 sec", GOSSIP_SENDER_MAIN, 471);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Sinister Strike|r - Your Sinister Strike critical strikes have a 50% chance to add an additional combo point", GOSSIP_SENDER_MAIN, 472);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Slice and Dice|r - Increases the duration of Slice and Dice by 3 sec", GOSSIP_SENDER_MAIN, 473);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Sprint|r - Increases the movement speed of your Sprint ability by an additional 30%", GOSSIP_SENDER_MAIN, 474);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1021);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5442);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1022: //shaman glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hex|r - Increases the damage your Hex target can take before the Hex effect is removed by 20%", GOSSIP_SENDER_MAIN, 475);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fire Elemental Totem|r - Reduces the cooldown of your Fire Elemental Totem by 5 min", GOSSIP_SENDER_MAIN, 476);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Thunder|r - Reduces the cooldown on Thunderstorm by 10 sec", GOSSIP_SENDER_MAIN, 477);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Totem of Wrath|r - When you cast Totem of Wrath, you gain 30% of the totem's bonus spell power for 5 min", GOSSIP_SENDER_MAIN, 478);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Elemental Mastery|r - Reduces the cooldown of your Elemental Mastery ability by 30 sec", GOSSIP_SENDER_MAIN, 479);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Chain Lightning|r - Your Chain Lightning strikes 1 additional target", GOSSIP_SENDER_MAIN, 480);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Frost Shock|r - Increases the duration of your Frost Shock by 2 sec", GOSSIP_SENDER_MAIN, 481);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Flame Shock|r - Increases the critical strike damage bonus of your Flame Shock damage by 60%", GOSSIP_SENDER_MAIN, 482);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fire Nova|r - Reduces the cooldown of your Fire Nova spell by 3 seconds", GOSSIP_SENDER_MAIN, 483);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Lightning Bolt|r - Increases the damage dealt by Lightning Bolt by 4%", GOSSIP_SENDER_MAIN, 484);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5444);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5445);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5444: //shaman glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Stoneclaw Totem|r - Your Stoneclaw Totem also places a damage absorb shield on you, equal to 4 times the strength of the shield it places on your totems", GOSSIP_SENDER_MAIN, 485);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Feral Spirit|r - Your spirit wolves gain an additional 30% of your attack power", GOSSIP_SENDER_MAIN, 486);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Stormstrike|r - Increases the nature damage bonus from your Stormstrike ability by an additional 8%", GOSSIP_SENDER_MAIN, 487);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Windfury Weapon|r - Increases the chance per swing for Windfury Weapon to trigger by 2%", GOSSIP_SENDER_MAIN, 488);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Flametongue Weapon|r - Increases spell critical strike chance by 2% while Flametongue Weapon is active", GOSSIP_SENDER_MAIN, 489);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Lightning Shield|r - Increases the damage from Lightning Shield by 20%", GOSSIP_SENDER_MAIN, 490);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Lava Lash|r - Damage on your Lava Lash is increased by an additional 10% if your weapon is enchanted with Flametongue", GOSSIP_SENDER_MAIN, 491);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Riptide|r - Increases the duration of Riptide by 6 sec", GOSSIP_SENDER_MAIN, 492);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Earth Shield|r - Increases the amount healed by your Earth Shield by 20%", GOSSIP_SENDER_MAIN, 493);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Chain Heal|r - Your Chain Heal heals 1 additional target", GOSSIP_SENDER_MAIN, 494);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1022);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5445);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5445: //shaman glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mana Tide Totem|r - Your Mana Tide Totem grants an additional 1% of each target's maximum mana each time it pulses", GOSSIP_SENDER_MAIN, 495);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Earthliving Weapon|r - Increases the chance for your Earthliving weapon to trigger by 5%", GOSSIP_SENDER_MAIN, 496);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Healing Stream Totem|r - Your Healing Stream Totem heals for an additional 20%", GOSSIP_SENDER_MAIN, 497);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Lesser Healing Wave|r - Your Lesser Healing Wave heals for 20% more if the target is also affected by your Earth Shield", GOSSIP_SENDER_MAIN, 498);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Water Mastery|r - Increases the passive mana regeneration of your Water Shield spell by 30%", GOSSIP_SENDER_MAIN, 499);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Healing Wave|r - Your Healing Wave also heals you for 20% of the healing effect when you heal someone else", GOSSIP_SENDER_MAIN, 500);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shocking|r - Reduces the global cooldown triggered by your shock spells to 1 sec", GOSSIP_SENDER_MAIN, 501);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1022);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5444);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1023: //warlock glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Demonic Circle|r - Reduces the cooldown on Demonic Circle by 4 sec", GOSSIP_SENDER_MAIN, 502);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shadowflame|r - Your Shadowflame also applies a 70% movement speed slow on its victims", GOSSIP_SENDER_MAIN, 503);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Chaos Bolt|r - Reduces the cooldown on Chaos Bolt by 2 sec", GOSSIP_SENDER_MAIN, 504);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Haunt|r - The bonus damage granted by your Haunt spell is increased by an additional 3%", GOSSIP_SENDER_MAIN, 505);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Metamorphosis|r - Increases the duration of your Metamorphosis by 6 sec", GOSSIP_SENDER_MAIN, 506);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Felguard|r - Increases the Felguard's total attack power by 20%", GOSSIP_SENDER_MAIN, 507);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Unstable Affliction|r - Decreases the casting time of your Unstable Affliction by 0.2 sec", GOSSIP_SENDER_MAIN, 508);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Death Coil|r - Increases the duration of your Death Coil by 0.5 sec", GOSSIP_SENDER_MAIN, 509);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Conflagrate|r - Your Conflagrate spell no longer consumes your Immolate or Shadowflame spell from the target", GOSSIP_SENDER_MAIN, 510);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Howl of Terror|r - Reduces the cooldown on your Howl of Terror spell by 8 sec", GOSSIP_SENDER_MAIN, 511);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5446);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5447);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5446: //warlock glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Felhunter|r - When your Felhunter uses Devour Magic, you will also be healed for that amount", GOSSIP_SENDER_MAIN, 512);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Siphon Life|r - Increases the healing you receive from your Siphon Life talent by 25%", GOSSIP_SENDER_MAIN, 513);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Succubus|r - Your Succubus's Seduction ability also removes all damage over time effects from the target", GOSSIP_SENDER_MAIN, 514);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shadowburn|r - Increases the critical strike chance of Shadowburn by 20% when the target is below 35% health", GOSSIP_SENDER_MAIN, 515);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Soul Link|r - Increases the percentage of damage shared via your Soul Link by an additional 5%", GOSSIP_SENDER_MAIN, 516);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Soulstone|r - Increases the amount of health you gain from resurrecting via your Soulstone by 300%", GOSSIP_SENDER_MAIN, 517);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Searing Pain|r - Increases the critical strike bonus of your Searing Pain by 20%", GOSSIP_SENDER_MAIN, 518);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Corruption|r - You Corruption spell has a 4% chance to cause you to enter a Shadow Trance state after damaging the opponent. The Shadow Trance state reduces the casting time of your next Shadow Bolt spell by 100%", GOSSIP_SENDER_MAIN, 519);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Curse of Agony|r - Increases the duration of your Curse of Agony by 4 sec", GOSSIP_SENDER_MAIN, 520);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Fear|r - Increases the damage your Fear target can take before the Fear effect is removed by 20%", GOSSIP_SENDER_MAIN, 521);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1023);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5447);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5447: //warlock glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Immolate|r - Increases the periodic damage of your immolate by 10%", GOSSIP_SENDER_MAIN, 522);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Imp|r - Increases the damage done by your Imp's Firebolt spell by 20%", GOSSIP_SENDER_MAIN, 523);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Health Funnel|r - Increases the chance you'll resist spell interruption when channeling your Health Funnel spell by 100%", GOSSIP_SENDER_MAIN, 524);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Healthstone|r - You receive 30% more healing from using a healthstone.", GOSSIP_SENDER_MAIN, 525);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Life Tap|r - When you use Life Tap or Dark Pact, you gain 20% of your Spirit as spell power for 40 sec", GOSSIP_SENDER_MAIN, 526);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Quick Decay|r - Your haste now reduces the time between periodic damage ticks of your Corruption spell", GOSSIP_SENDER_MAIN, 527);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shadow Bolt|r - Reduces the mana cost of your Shadow Bolt by 10%", GOSSIP_SENDER_MAIN, 528);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Voidwalker|r - Increases your Voidwalker's total Stamina by 20%", GOSSIP_SENDER_MAIN, 529);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Incinerate|r - Increases the damage done by Incinerate by 5%", GOSSIP_SENDER_MAIN, 530);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1023);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5446);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1024: //druid glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Focus|r - Increases damage done by Starfall by 10%, but decreases its radius by 50%", GOSSIP_SENDER_MAIN, 301);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Starfall|r - Decreases cooldown on Starfall by 30 seconds", GOSSIP_SENDER_MAIN, 302);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Monsoon|r - Reduces cooldown of your Typhoon spell by 3 seconds", GOSSIP_SENDER_MAIN, 303);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hurricane|r - Your Hurricane ability now also slows the movement speed of its victims by 20%", GOSSIP_SENDER_MAIN, 304);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Insect Swarm|r - Increases the damage of your Insect Swarm ability by 30%, but it no longer affects your victim's chance to hit", GOSSIP_SENDER_MAIN, 305);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Starfire|r - Your Starfire ability increases the duration of your Moonfire effect on the target by 3 sec, up to a maximum of 9 additional sec", GOSSIP_SENDER_MAIN, 306);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Entangling Roots|r - Increases the damage your Entangling Roots victims can take before the Entangling Roots automatically breaks by 20%", GOSSIP_SENDER_MAIN, 307);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Moonfire|r - Increases the periodic damage of your Moonfire ability by 75%, but initial damage is decreased by 90%", GOSSIP_SENDER_MAIN, 308);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Wrath|r - Reduces the pushback suffered from damaging attacks while casting your Wrath spell by 50%", GOSSIP_SENDER_MAIN, 309);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Savage Roar|r - Your Savage Roar ability grants an additional 3% bonus damage done", GOSSIP_SENDER_MAIN, 310);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5432);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5433);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5432: //druid glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Berserk|r - Increases the duration of Berserk by 5 sec", GOSSIP_SENDER_MAIN, 311);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Mangle|r - Increases the damage done by Mangle by 10%", GOSSIP_SENDER_MAIN, 312);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Barkskin|r - Reduces the chance you'll be critically hit by melee attacks by 25% while Barkskin is active", GOSSIP_SENDER_MAIN, 313);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Frenzied Regeneration|r - While Frenzied Regeneration is active, healing effects on you are 20% more powerful", GOSSIP_SENDER_MAIN, 314);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rake|r - Your Rake ability prevents targets from fleeing", GOSSIP_SENDER_MAIN, 315);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Shred|r - Each time you Shred, the duration of your Rip on the target is extended 2 sec, up to a maximum of 6 sec", GOSSIP_SENDER_MAIN, 316);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Survival Instincts|r - Your Survival Instincts ability grants an additional 15% of your maximum health", GOSSIP_SENDER_MAIN, 317);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rip|r - Increases the duration of your Rip ability by 4 sec", GOSSIP_SENDER_MAIN, 318);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Claw|r - Reduces the energy cost of your claw ability by 5", GOSSIP_SENDER_MAIN, 319);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Growl|r - Increases the chance for your Growl ability to work successfully by 8%", GOSSIP_SENDER_MAIN, 320);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1024);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5433);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5433: //druid glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Maul|r - Your Maul ability now hits 1 additional target", GOSSIP_SENDER_MAIN, 321);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Nourish|r - Your Nourish heals an additional 6% for each of your heal over time effects present on the target", GOSSIP_SENDER_MAIN, 322);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Lifebloom|r - Increases the duration of Lifebloom by 1 sec", GOSSIP_SENDER_MAIN, 323);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Wild Growth|r - Wild Growth can affect 1 additional target", GOSSIP_SENDER_MAIN, 324);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Swiftmend|r - Your Swiftmend ability no longer consumes a Rejuvenation or Regrowth effect from the target", GOSSIP_SENDER_MAIN, 325);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rapid Rejuvenation|r - Your haste now reduces the time between the periodic healing ticks of your Rejuvenation spell", GOSSIP_SENDER_MAIN, 326);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Regrowth|r - Increases the healing of your Regrowth spell by 20% if your Regrowth effect is still active on the target", GOSSIP_SENDER_MAIN, 327);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rejuvenation|r - While your rejuvenation targets are below 50% health, you will heal them for an additional 50% health", GOSSIP_SENDER_MAIN, 328);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Healing Touch|r - Decreases the cast time of Healing Touch by 1.5 sec., the mana cost by 25%, and the amount healed by 50%", GOSSIP_SENDER_MAIN, 329);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Innervate|r - Innervate now grants the caster 45% of their base mana pool over 10 sec in addition to the normal effects of Innervate", GOSSIP_SENDER_MAIN, 330);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rebirth|r - Players resurrected by Rebirth are returned to life with 100% health", GOSSIP_SENDER_MAIN, 331);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1024);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5432);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 1026: //dk glyphs
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Howling Blast|r - Your Howling Blast ability now infects your targets with Frost Fever", GOSSIP_SENDER_MAIN, 558);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Dancing Rune Weapon|r - Increases the duration of Dancing Rune Weapon by 5 sec", GOSSIP_SENDER_MAIN, 559);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Hungering Cold|r - Reduces the cost of Hungering Cold by 40 runic power", GOSSIP_SENDER_MAIN, 560);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Unholy Blight|r - Increases the damage done by Unholy Blight by 40%", GOSSIP_SENDER_MAIN, 561);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Anti-Magic Shell|r - Increases the duration of your Anti-Magic Shell by 2 sec", GOSSIP_SENDER_MAIN, 562);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Blood Strike|r - Your Blood Strike causes an additional 20% damage to snared targets", GOSSIP_SENDER_MAIN, 563);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Bone Shield|r - Adds 1 additional charge to your Bone Shield", GOSSIP_SENDER_MAIN, 564);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Chains of Ice|r - Your Chains of Ice also causes 144 to 156 Frost damage, increased by your attack power", GOSSIP_SENDER_MAIN, 565);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Dark Command|r - Increases the chance for your Dark Command ability to work successfully by 8%", GOSSIP_SENDER_MAIN, 566);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Dark Death|r - Increases the damage or healing done by Death Coil by 15%", GOSSIP_SENDER_MAIN, 567);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5450);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5451);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5450: //dk glyphs 2
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Death and Decay|r - Increases the duration of your Death and Decay by 50%", GOSSIP_SENDER_MAIN, 568);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Death Grip|r - When you deal a killing blow that grants honor or experience, the cooldown of your Death Grip is refreshed", GOSSIP_SENDER_MAIN, 569);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Death Strike|r - Increases your Death Strike's damage by 1% for every 1 runic power you currently have (up to a maximum of 25%). The runic power is not consumed by this effect", GOSSIP_SENDER_MAIN, 570);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Disease|r - Your Pestilence ability now refreshes disease durations on your primary target back to their maximum duration", GOSSIP_SENDER_MAIN, 571);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Frost Strike|r - Reduces the cost of your Frost Strike by 8 Runic Power", GOSSIP_SENDER_MAIN, 572);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Ghoul|r - Your Ghoul receives an additional 40% of your Strength and 40% of your Stamina", GOSSIP_SENDER_MAIN, 573);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Icebound Fortitute|r - Your Icebound Fortitude now always grants at least 40% damage reduction, regardless of your defense skill", GOSSIP_SENDER_MAIN, 574);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Icy Touch|r - Your Frost Fever disease deals 20% additional damage", GOSSIP_SENDER_MAIN, 575);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rune Strike|r - Increases the critical strike chance of your Rune Strike by 10%", GOSSIP_SENDER_MAIN, 576);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Strangulate|r - Increases the range of your Strangulate by 20 yards", GOSSIP_SENDER_MAIN, 577);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1026);
			player->ADD_GOSSIP_ITEM(0, "Page 3", GOSSIP_SENDER_MAIN, 5450);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 5451: //dk glyphs 3
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Vampiric Blood|r - Increases the duration of your Vampiric Blood by 5 sec", GOSSIP_SENDER_MAIN, 578);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Obliterate|r - Increases the damage of your Obliterate ability by 25%", GOSSIP_SENDER_MAIN, 579);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Plague Strike|r - Your Plague Strike does 20% additional damage", GOSSIP_SENDER_MAIN, 580);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Rune Tap|r - Your Rune Tap heals yourself for an additional 10% of the effect, and also heals your party for 10% of their maximum health", GOSSIP_SENDER_MAIN, 581);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Scourge Strike|r - Your Scourge Strike increases the duration of your diseases on the target by 3 sec, up to a maximum of 9 additional seconds", GOSSIP_SENDER_MAIN, 582);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Unbreakable Armor|r - Increases the total armor granted by Unbreakable Armor to 30%", GOSSIP_SENDER_MAIN, 583);
			player->ADD_GOSSIP_ITEM(3, "|cff9900CCGlyph of Heart Strike|r - Your Heart Strike also reduces the movement speed of your target by 50% for 10 sec", GOSSIP_SENDER_MAIN, 584);
			player->ADD_GOSSIP_ITEM(0, "Page 1", GOSSIP_SENDER_MAIN, 1026);
			player->ADD_GOSSIP_ITEM(0, "Page 2", GOSSIP_SENDER_MAIN, 5451);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(7, "Never mind", GOSSIP_SENDER_MAIN, 1006);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		}
		break;

		case 10000: // Reset Talent Points
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(0, "YES, please reset my talents", GOSSIP_SENDER_MAIN, 10001);
			player->ADD_GOSSIP_ITEM(0, "NO, do not reset my talents", GOSSIP_SENDER_MAIN, 1006);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 10003: // Reset Talent Points
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(0, "YES, please reset my pet's talents", GOSSIP_SENDER_MAIN, 10004);
			player->ADD_GOSSIP_ITEM(0, "NO, do not reset my pet's talents", GOSSIP_SENDER_MAIN, 1006);
			player->ADD_GOSSIP_ITEM(7, "Back to main menu", GOSSIP_SENDER_MAIN, 1000);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case 10001:
			player->ResetTalents(true);
			player->SendTalentsInfoData(false);
			player->SaveToDB();
			creature->Whisper("Your talents have been reset.", LANG_UNIVERSAL, player);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 10004:
			player->ResetPetTalents();
			player->SendTalentsInfoData(false);
			player->SaveToDB();
			creature->Whisper("Your pet's talents have been reset.", LANG_UNIVERSAL, player);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 10002:
			player->PlayerTalkClass->ClearMenus();
			player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
			player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());

			if (player->getClass() == CLASS_HUNTER)
			{
				player->m_stableSlots = 4;
				creature->Whisper("You now have dual specialization and 4 stable slots.", LANG_UNIVERSAL, player);
				player->CLOSE_GOSSIP_MENU();
			}
			else
				creature->Whisper("You now have dual specialization.", LANG_UNIVERSAL, player);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 10005:
			player->PlayerTalkClass->ClearMenus();

			player->m_stableSlots = 4;
			creature->Whisper("You now four stable slots.", LANG_UNIVERSAL, player);
			player->CLOSE_GOSSIP_MENU();
			break;

			// Paladin
		case 0: //Retribution
			player->RemoveSpell(19750, false);
			player->RemoveSpell(19746, false);
			player->RemoveSpell(20256, false);

			player->RemoveSpell(31935, false);
			player->RemoveSpell(20196, false); player->RemoveSpell(20197, false); player->RemoveSpell(20198, false);
			player->RemoveSpell(53709, false); player->RemoveSpell(53710, false); player->RemoveSpell(53711, false);

			player->LearnSpell(53385, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 1: //Holy
			player->RemoveSpell(53385, false);

			player->RemoveSpell(31935, false);
			player->RemoveSpell(20196, false); player->RemoveSpell(20197, false); player->RemoveSpell(20198, false);
			player->RemoveSpell(53709, false); player->RemoveSpell(53710, false); player->RemoveSpell(53711, false);

			player->LearnSpell(19750, false);
			player->LearnSpell(19746, false);
			player->LearnSpell(20256, false);
			player->CLOSE_GOSSIP_MENU();
			break;
		case 2:  //Protection
			player->RemoveSpell(53385, false);

			player->LearnSpell(31935, false);
			player->LearnSpell(20196, false); player->LearnSpell(20197, false); player->LearnSpell(20198, false);
			player->LearnSpell(53709, false); player->LearnSpell(53710, false); player->LearnSpell(53711, false);

			player->RemoveSpell(19750, false);
			player->RemoveSpell(19746, false);
			player->RemoveSpell(20256, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Mage
		case 2100: // Arcane
			player->RemoveSpell(11083, false); player->RemoveSpell(12351, false);

			player->RemoveSpell(11426, false);
			player->RemoveSpell(120, false);
			player->RemoveSpell(44614, false);

			player->LearnSpell(6117, false);
			player->LearnSpell(12051, false);
			player->LearnSpell(1463, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 4: // Fire
			player->LearnSpell(11083, false); player->LearnSpell(12351, false);

			player->RemoveSpell(11426, false);
			player->RemoveSpell(120, false);
			player->RemoveSpell(44614, false);

			player->RemoveSpell(6117, false);
			player->RemoveSpell(12051, false);
			player->RemoveSpell(1463, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 5: // Frost
			player->RemoveSpell(11083, false); player->RemoveSpell(12351, false);

			player->LearnSpell(11426, false);
			player->RemoveSpell(120, false);
			player->LearnSpell(44614, false);

			player->RemoveSpell(6117, false);
			player->RemoveSpell(12051, false);
			player->RemoveSpell(1463, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Warrior
		case 6: // Arms
			player->RemoveSpell(674, false);
			player->RemoveSpell(2458, false);
			player->RemoveSpell(1680, false);

			//player->RemoveSpell(1715, false);

			player->LearnSpell(1715, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 7: // Fury
			player->LearnSpell(674, false);
			player->LearnSpell(2458, false);
			player->LearnSpell(1680, false);

			//player->RemoveSpell(1715, false);

			player->RemoveSpell(1715, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 8: // Protection
			player->RemoveSpell(674, false);
			player->RemoveSpell(2458, false);
			player->RemoveSpell(1680, false);

			player->LearnSpell(1715, false);

			//player->RemoveSpell(1715, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Priest
		case 2012: // Holy
			player->RemoveSpell(47540, false);
			player->RemoveSpell(45234, false); player->RemoveSpell(45243, false); player->RemoveSpell(45244, false);

			player->RemoveSpell(15473, false);
			player->RemoveSpell(47585, false);
			player->RemoveSpell(15407, false);
			player->RemoveSpell(34914, false);

			player->LearnSpell(2054, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 10: // Discipline
			player->LearnSpell(2054, false);

			player->RemoveSpell(15473, false);
			player->RemoveSpell(47585, false);
			player->RemoveSpell(15407, false);
			player->RemoveSpell(34914, false);

			//player->RemoveSpell(2054, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 11: // Shadow
			player->RemoveSpell(2054, false);

			player->LearnSpell(15473, false);
			player->LearnSpell(47585, false);
			player->LearnSpell(15407, false);
			player->LearnSpell(34914, false);


			//player->RemoveSpell(2054, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Hunter
		case 2103: // Marksman
			player->UnsummonPetTemporaryIfAny();
			player->RemoveSpell(53270, false);
			player->RemoveSpell(34026, false);

			player->RemoveSpell(5384, false);

			player->LearnSpell(3044, false); player->LearnSpell(14281, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 13: // Survival
			player->UnsummonPetTemporaryIfAny();
			player->RemoveSpell(53270, false);
			player->RemoveSpell(34026, false);

			player->LearnSpell(5384, false);

			player->RemoveSpell(3044, false); player->RemoveSpell(14281, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 2101: // Beastmaster
			player->LearnSpell(53270, false);
			player->LearnSpell(34026, false);

			player->RemoveSpell(5384, false);

			player->RemoveSpell(3044, false); player->RemoveSpell(14281, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Rogue
		case 15: //Sub
			player->RemoveSpell(1329, false);

			player->RemoveSpell(13750, false);

			player->LearnSpell(16511, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 16: // Assassination
			player->LearnSpell(1329, false);

			player->RemoveSpell(13750, false);
			player->RemoveSpell(31124, false);

			player->RemoveSpell(16511, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 17: // Combat
			player->RemoveSpell(1329, false);

			player->LearnSpell(13750, false);

			player->RemoveSpell(16511, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Shaman
		case 18: //Restoration
			player->RemoveSpell(57994, false);
			//player->RemoveSpell(370, false);

			player->RemoveSpell(30798, false);
			player->RemoveSpell(17364, false);
			player->RemoveSpell(57994, false);
			player->RemoveSpell(51521, false); player->RemoveSpell(51522, false);
			player->RemoveSpell(674, false);

			player->LearnSpell(370, false);
			player->LearnSpell(51730, false);
			player->LearnSpell(16181, false); player->LearnSpell(16230, false); player->LearnSpell(16232, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 19: // Enhancement
				 //player->RemoveSpell(57994, false);
			player->RemoveSpell(370, false);

			player->LearnSpell(30798, false);
			player->LearnSpell(17364, false);
			player->LearnSpell(57994, false);
			player->LearnSpell(51521, false); player->LearnSpell(51522, false);
			player->LearnSpell(674, false);

			player->RemoveSpell(370, false);
			player->RemoveSpell(51730, false);
			player->RemoveSpell(16181, false); player->RemoveSpell(16230, false); player->RemoveSpell(16232, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 20: // Elemental
			player->LearnSpell(57994, false);
			player->LearnSpell(370, false);

			player->RemoveSpell(30798, false);
			player->RemoveSpell(17364, false);
			//player->RemoveSpell(57994, false);
			player->RemoveSpell(51521, false); player->RemoveSpell(51522, false);
			player->RemoveSpell(674, false);

			//player->RemoveSpell(370, false);
			player->RemoveSpell(51730, false);
			player->RemoveSpell(16181, false); player->RemoveSpell(16230, false); player->RemoveSpell(16232, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Warlock
		case 21: //Affliction
			player->LearnSpell(980, false); player->LearnSpell(1014, false);
			player->LearnSpell(172, false); player->LearnSpell(6222, false);

			player->RemoveSpell(30146, false);
			player->RemoveSpell(47193, false);
			player->RemoveSpell(48018, false); player->RemoveSpell(48020, false);

			player->RemoveSpell(17962, false);
			player->RemoveSpell(47258, false); player->RemoveSpell(47259, false); player->RemoveSpell(47260, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 22: // Demonology
			player->RemoveSpell(980, false); player->RemoveSpell(1014, false);
			player->RemoveSpell(172, false); player->RemoveSpell(6222, false);

			player->LearnSpell(30146, false);
			player->LearnSpell(47193, false);
			player->LearnSpell(48018, false); player->LearnSpell(48020, false);


			player->RemoveSpell(17962, false);
			player->RemoveSpell(47258, false); player->RemoveSpell(47259, false); player->RemoveSpell(47260, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 23: //Destruction
			player->RemoveSpell(980, false); player->RemoveSpell(1014, false);
			player->RemoveSpell(172, false); player->RemoveSpell(6222, false);

			player->RemoveSpell(30146, false);
			player->RemoveSpell(47193, false);
			player->RemoveSpell(48018, false); player->RemoveSpell(48020, false);

			player->LearnSpell(17962, false);
			player->LearnSpell(47258, false); player->LearnSpell(47259, false); player->LearnSpell(47260, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// Druid
		case 24: //Guardian
			player->RemoveSpell(24858, false);
			player->RemoveSpell(50516, false);
			player->RemoveSpell(48516, false); player->RemoveSpell(48521, false); player->RemoveSpell(48525, false);

			player->RemoveSpell(768, false);
			player->RemoveSpell(1850, false);

			player->LearnSpell(33853, false); player->LearnSpell(33855, false); player->LearnSpell(33856, false);

			player->RemoveSpell(8936, false); player->RemoveSpell(8938, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 25: // Balance
			player->LearnSpell(24858, false);
			player->LearnSpell(50516, false);
			player->LearnSpell(48516, false); player->LearnSpell(48521, false); player->LearnSpell(48525, false);

			player->RemoveSpell(768, false);
			player->RemoveSpell(1850, false);

			player->RemoveSpell(33853, false); player->RemoveSpell(33855, false); player->RemoveSpell(33856, false);

			player->RemoveSpell(8936, false); player->RemoveSpell(8938, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 26: //Restoration	
			player->RemoveSpell(24858, false);
			player->RemoveSpell(50516, false);
			player->RemoveSpell(48516, false); player->RemoveSpell(48521, false); player->RemoveSpell(48525, false);

			player->RemoveSpell(768, false);
			player->RemoveSpell(1850, false);

			player->RemoveSpell(33853, false); player->RemoveSpell(33855, false); player->RemoveSpell(33856, false);

			player->LearnSpell(8936, false); player->LearnSpell(8938, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 27: //Feral
			player->RemoveSpell(24858, false);
			player->RemoveSpell(50516, false);
			player->RemoveSpell(48516, false); player->RemoveSpell(48521, false); player->RemoveSpell(48525, false);

			player->LearnSpell(768, false);
			player->LearnSpell(1850, false);

			player->RemoveSpell(33853, false); player->RemoveSpell(33855, false); player->RemoveSpell(33856, false);

			player->RemoveSpell(8936, false); player->RemoveSpell(8938, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			// DK 
		case 9900: // Blood
			player->RemoveSpell(50151, false);
			player->RemoveSpell(50040, false);

			player->RemoveSpell(51052, false);
			player->RemoveSpell(55667, false);

			player->LearnSpell(49028, false);
			player->LearnSpell(48982, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 9901: // Frost
			player->LearnSpell(50151, false);
			player->LearnSpell(50040, false);

			player->RemoveSpell(51052, false);
			player->RemoveSpell(55667, false);

			player->RemoveSpell(49028, false);
			player->RemoveSpell(48982, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;
		case 9902: // Unholy
			player->RemoveSpell(50151, false);
			player->RemoveSpell(50040, false);

			player->LearnSpell(51052, false);
			player->LearnSpell(55667, false);

			player->RemoveSpell(49028, false);
			player->RemoveSpell(48982, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your specialization has been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 28: //human
			player->LearnSpell(58985, false); player->LearnSpell(20598, false); player->LearnSpell(20599, false); player->LearnSpell(20597, false); player->LearnSpell(20864, false); player->LearnSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); /*player->RemoveSpell(20864, false);*/
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 29: //orc
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			{if (player->getClass() == CLASS_WARRIOR || CLASS_ROGUE || CLASS_HUNTER || CLASS_SHAMAN) player->LearnSpell(20572, false); else player->LearnSpell(33702, false); } player->LearnSpell(20573, false); player->LearnSpell(21563, false); player->LearnSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 30: //dwarf
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); /*player->RemoveSpell(20864, false);*/ player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->LearnSpell(20594, false); player->LearnSpell(20595, false); player->LearnSpell(20596, false); player->LearnSpell(2481, false); player->LearnSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 31: //night elf
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->LearnSpell(58984, false); player->LearnSpell(20585, false); player->LearnSpell(20582, false); player->LearnSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); /*player->RemoveSpell(20551, false);*/
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 32: //undead
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->LearnSpell(7744, false); player->LearnSpell(20577, false); player->LearnSpell(5227, false); player->LearnSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); /*player->RemoveSpell(59535, false);*/
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 33: //tauren
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); /*player->RemoveSpell(20551, false);*/
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->LearnSpell(20549, false); player->LearnSpell(20550, false); player->LearnSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 34: //gnome
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->LearnSpell(20589, false); player->LearnSpell(20591, false); player->LearnSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 35: //troll
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->LearnSpell(26297, false); player->LearnSpell(20555, false); player->LearnSpell(20557, false); player->LearnSpell(20558, false); player->LearnSpell(26290, false); player->LearnSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 36: //blood elf
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); player->RemoveSpell(59535, false);
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			{if (player->getClass() == CLASS_ROGUE) player->LearnSpell(25046, false); else if (player->getClass() == CLASS_DEATH_KNIGHT) player->LearnSpell(50613, false); else player->LearnSpell(28730, false); } player->LearnSpell(822, false);
			player->RemoveSpell(59542, false); player->RemoveSpell(6562, false); player->RemoveSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

		case 37: //draenei
			player->RemoveSpell(58985, false); player->RemoveSpell(20598, false); player->RemoveSpell(20599, false); player->RemoveSpell(20597, false); player->RemoveSpell(20864, false); player->RemoveSpell(59752, false);
			player->RemoveSpell(20572, false); player->RemoveSpell(33702, false); player->RemoveSpell(20573, false); player->RemoveSpell(21563, false); player->RemoveSpell(20574, false);
			player->RemoveSpell(20594, false); player->RemoveSpell(20595, false); player->RemoveSpell(20596, false); player->RemoveSpell(2481, false); player->RemoveSpell(20864, false);
			player->RemoveSpell(58984, false); player->RemoveSpell(20585, false); player->RemoveSpell(20582, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(7744, false); player->RemoveSpell(20577, false); player->RemoveSpell(5227, false); /*player->RemoveSpell(59535, false);*/
			player->RemoveSpell(20549, false); player->RemoveSpell(20550, false); player->RemoveSpell(20551, false);
			player->RemoveSpell(20589, false); player->RemoveSpell(20591, false); player->RemoveSpell(20592, false);
			player->RemoveSpell(26297, false); player->RemoveSpell(20555, false); player->RemoveSpell(20557, false); player->RemoveSpell(20558, false); player->RemoveSpell(26290, false); player->RemoveSpell(58943, false);
			player->RemoveSpell(25046, false); player->RemoveSpell(50613, false); player->RemoveSpell(28730, false); player->RemoveSpell(822, false);
			player->LearnSpell(59542, false); player->LearnSpell(6562, false); player->LearnSpell(59535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your racial spells have been set. Passive spells may not give you a notification, but you do have them.", LANG_UNIVERSAL, player);
			break;

			//glyphs
		case 301:
			player->CastSpell(player, 62161, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 302:
			player->CastSpell(player, 54874, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 303:
			player->CastSpell(player, 63739, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 304:
			player->CastSpell(player, 62134, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 305:
			player->CastSpell(player, 54872, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 306:
			player->CastSpell(player, 54871, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 307:
			player->CastSpell(player, 54877, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 308:
			player->CastSpell(player, 54876, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 309:
			player->CastSpell(player, 54875, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 310:
			player->CastSpell(player, 63718, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 311:
			player->CastSpell(player, 63714, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 312:
			player->CastSpell(player, 54857, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 313:
			player->CastSpell(player, 63740, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 314:
			player->CastSpell(player, 54854, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 315:
			player->CastSpell(player, 54863, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 316:
			player->CastSpell(player, 54859, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 317:
			player->CastSpell(player, 65244, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 318:
			player->CastSpell(player, 54860, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 319:
			player->CastSpell(player, 67599, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 320:
			player->CastSpell(player, 54812, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 321:
			player->CastSpell(player, 54811, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 322:
			player->CastSpell(player, 63717, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 323:
			player->CastSpell(player, 54870, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 324:
			player->CastSpell(player, 63715, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 325:
			player->CastSpell(player, 54864, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 326:
			player->CastSpell(player, 71014, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 327:
			player->CastSpell(player, 54867, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 328:
			player->CastSpell(player, 54868, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 329:
			player->CastSpell(player, 54869, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 330:
			player->CastSpell(player, 54865, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 331:
			player->CastSpell(player, 54866, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 332:
			player->CastSpell(player, 63855, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 333:
			player->CastSpell(player, 56885, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 334:
			player->CastSpell(player, 56886, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 335:
			player->CastSpell(player, 63741, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 336:
			player->CastSpell(player, 63854, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 337:
			player->CastSpell(player, 56887, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 338:
			player->CastSpell(player, 56888, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 339:
			player->CastSpell(player, 56889, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 340:
			player->CastSpell(player, 56874, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 342:
			player->CastSpell(player, 63856, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 343:
			player->CastSpell(player, 56871, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 344:
			player->CastSpell(player, 56878, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 345:
			player->CastSpell(player, 56883, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 346:
			player->CastSpell(player, 56875, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 347:
			player->CastSpell(player, 56873, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 348:
			player->CastSpell(player, 56876, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 349:
			player->CastSpell(player, 63857, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 350:
			player->CastSpell(player, 56877, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 351:
			player->CastSpell(player, 56869, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 352:
			player->CastSpell(player, 56882, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 353:
			player->CastSpell(player, 56880, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 354:
			player->CastSpell(player, 56870, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 355:
			player->CastSpell(player, 56881, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 356:
			player->CastSpell(player, 56879, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 357:
			player->CastSpell(player, 56872, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 358:
			player->CastSpell(player, 63858, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 359:
			player->CastSpell(player, 56884, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 360:
			player->CastSpell(player, 63863, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 361:
			player->CastSpell(player, 61206, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 362:
			player->CastSpell(player, 62127, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 363:
			player->CastSpell(player, 56596, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 364:
			player->CastSpell(player, 56593, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 365:
			player->CastSpell(player, 62353, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 366:
			player->CastSpell(player, 56599, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 367:
			player->CastSpell(player, 63860, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 368:
			player->CastSpell(player, 63862, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 369:
			player->CastSpell(player, 63859, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 370:
			player->CastSpell(player, 70938, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 371:
			player->CastSpell(player, 56602, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 372:
			player->CastSpell(player, 63864, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 373:
			player->CastSpell(player, 56544, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 374:
			player->CastSpell(player, 56597, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 375:
			player->CastSpell(player, 56592, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 376:
			player->CastSpell(player, 56598, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 377:
			player->CastSpell(player, 56546, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 378:
			player->CastSpell(player, 56547, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 379:
			player->CastSpell(player, 42746, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 380:
			player->CastSpell(player, 56595, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 381:
			player->CastSpell(player, 56601, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 382:
			player->CastSpell(player, 56540, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 383:
			player->CastSpell(player, 56542, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 384:
			player->CastSpell(player, 56588, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 385:
			player->CastSpell(player, 56587, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 386:
			player->CastSpell(player, 56590, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 387:
			player->CastSpell(player, 56589, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 388:
			player->CastSpell(player, 56591, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 389:
			player->CastSpell(player, 56600, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 390:
			player->CastSpell(player, 63865, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 391:
			player->CastSpell(player, 59428, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 392:
			player->CastSpell(player, 63870, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 393:
			player->CastSpell(player, 55124, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 394:
			player->CastSpell(player, 55119, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 395:
			player->CastSpell(player, 55125, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 396:
			player->CastSpell(player, 55117, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 397:
			player->CastSpell(player, 55120, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 398:
			player->CastSpell(player, 57023, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 399:
			player->CastSpell(player, 55118, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 400:
			player->CastSpell(player, 55121, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 401:
			player->CastSpell(player, 55123, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 402:
			player->CastSpell(player, 59427, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 403:
			player->CastSpell(player, 63868, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 404:
			player->CastSpell(player, 63869, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 405:
			player->CastSpell(player, 63866, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 406:
			player->CastSpell(player, 55116, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 407:
			player->CastSpell(player, 63871, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 408:
			player->CastSpell(player, 55111, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 409:
			player->CastSpell(player, 55110, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 410:
			player->CastSpell(player, 55115, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 411:
			player->CastSpell(player, 55122, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 412:
			player->CastSpell(player, 63867, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 413:
			player->CastSpell(player, 59428, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 414:
			player->CastSpell(player, 59429, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 415:
			player->CastSpell(player, 55112, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 416:
			player->CastSpell(player, 55113, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 417:
			player->CastSpell(player, 55109, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 418:
			player->CastSpell(player, 55003, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 419:
			player->CastSpell(player, 56170, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 420:
			player->CastSpell(player, 63874, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 421:
			player->CastSpell(player, 63877, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 422:
			player->CastSpell(player, 56163, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 423:
			player->CastSpell(player, 56168, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 424:
			player->CastSpell(player, 56175, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 425:
			player->CastSpell(player, 63873, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 426:
			player->CastSpell(player, 63876, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 427:
			player->CastSpell(player, 42396, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 428:
			player->CastSpell(player, 56169, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 429:
			player->CastSpell(player, 56176, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 430:
			player->CastSpell(player, 56166, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 431:
			player->CastSpell(player, 56167, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 432:
			player->CastSpell(player, 56178, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 434:
			player->CastSpell(player, 56182, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 435:
			player->CastSpell(player, 56183, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 436:
			player->CastSpell(player, 63875, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 437:
			player->CastSpell(player, 56180, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 438:
			player->CastSpell(player, 63872, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 439:
			player->CastSpell(player, 56171, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 440:
			player->CastSpell(player, 56165, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 441:
			player->CastSpell(player, 56181, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 442:
			player->CastSpell(player, 56174, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 443:
			player->CastSpell(player, 56177, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 444:
			player->CastSpell(player, 56164, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 445:
			player->CastSpell(player, 56172, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 446:
			player->CastSpell(player, 56179, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 447:
			player->CastSpell(player, 63897, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 448:
			player->CastSpell(player, 63898, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 449:
			player->CastSpell(player, 57300, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 450:
			player->CastSpell(player, 63901, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 451:
			player->CastSpell(player, 57145, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 452:
			player->CastSpell(player, 63878, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 453:
			player->CastSpell(player, 63880, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 454:
			player->CastSpell(player, 63879, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 455:
			player->CastSpell(player, 63899, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 456:
			player->CastSpell(player, 57109, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 457:
			player->CastSpell(player, 57142, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 458:
			player->CastSpell(player, 57296, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 459:
			player->CastSpell(player, 57297, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 460:
			player->CastSpell(player, 57298, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 461:
			player->CastSpell(player, 57144, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 462:
			player->CastSpell(player, 57293, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 463:
			player->CastSpell(player, 57140, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 464:
			player->CastSpell(player, 57149, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 465:
			player->CastSpell(player, 57141, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 466:
			player->CastSpell(player, 57148, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 467:
			player->CastSpell(player, 57146, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 468:
			player->CastSpell(player, 57147, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 469:
			player->CastSpell(player, 57150, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 470:
			player->CastSpell(player, 57295, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 471:
			player->CastSpell(player, 57299, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 472:
			player->CastSpell(player, 57302, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 473:
			player->CastSpell(player, 57303, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 474:
			player->CastSpell(player, 57304, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 475:
			player->CastSpell(player, 63927, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 476:
			player->CastSpell(player, 55542, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 477:
			player->CastSpell(player, 63902, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 478:
			player->CastSpell(player, 63926, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 479:
			player->CastSpell(player, 55561, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 480:
			player->CastSpell(player, 55538, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 481:
			player->CastSpell(player, 55547, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 482:
			player->CastSpell(player, 55545, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 483:
			player->CastSpell(player, 55544, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 484:
			player->CastSpell(player, 55554, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 485:
			player->CastSpell(player, 63929, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 486:
			player->CastSpell(player, 63903, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 487:
			player->CastSpell(player, 55559, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 488:
			player->CastSpell(player, 55562, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 489:
			player->CastSpell(player, 55546, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 490:
			player->CastSpell(player, 55553, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 491:
			player->CastSpell(player, 55560, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 492:
			player->CastSpell(player, 63904, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 493:
			player->CastSpell(player, 63925, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 494:
			player->CastSpell(player, 55537, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 495:
			player->CastSpell(player, 55558, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 496:
			player->CastSpell(player, 55541, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 497:
			player->CastSpell(player, 55548, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 498:
			player->CastSpell(player, 55552, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 499:
			player->CastSpell(player, 55535, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 500:
			player->CastSpell(player, 55551, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 501:
			player->CastSpell(player, 55540, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 502:
			player->CastSpell(player, 63937, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 503:
			player->CastSpell(player, 63938, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 504:
			player->CastSpell(player, 63933, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 505:
			player->CastSpell(player, 63930, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 506:
			player->CastSpell(player, 63932, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 507:
			player->CastSpell(player, 56285, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 508:
			player->CastSpell(player, 56301, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 509:
			player->CastSpell(player, 56283, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 510:
			player->CastSpell(player, 56270, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 511:
			player->CastSpell(player, 56290, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 512:
			player->CastSpell(player, 56286, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 513:
			player->CastSpell(player, 56296, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 514:
			player->CastSpell(player, 56299, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 515:
			player->CastSpell(player, 56295, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 516:
			player->CastSpell(player, 63943, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 517:
			player->CastSpell(player, 56297, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 518:
			player->CastSpell(player, 56293, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 519:
			player->CastSpell(player, 56271, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 520:
			player->CastSpell(player, 56282, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 521:
			player->CastSpell(player, 56284, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 522:
			player->CastSpell(player, 56291, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 523:
			player->CastSpell(player, 56292, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 524:
			player->CastSpell(player, 56288, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 525:
			player->CastSpell(player, 56289, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 526:
			player->CastSpell(player, 63941, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 527:
			player->CastSpell(player, 70948, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 528:
			player->CastSpell(player, 56294, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 529:
			player->CastSpell(player, 56302, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 530:
			player->CastSpell(player, 56268, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 531:
			player->CastSpell(player, 63945, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 532:
			player->CastSpell(player, 58389, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 533:
			player->CastSpell(player, 58401, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 534:
			player->CastSpell(player, 58404, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 535:
			player->CastSpell(player, 58403, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 536:
			player->CastSpell(player, 58400, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 537:
			player->CastSpell(player, 58409, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 538:
			player->CastSpell(player, 58399, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 539:
			player->CastSpell(player, 58392, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 540:
			player->CastSpell(player, 63950, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 541:
			player->CastSpell(player, 58391, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 542:
			player->CastSpell(player, 58408, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 543:
			player->CastSpell(player, 58390, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 544:
			player->CastSpell(player, 58394, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 545:
			player->CastSpell(player, 58405, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 546:
			player->CastSpell(player, 58407, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 547:
			player->CastSpell(player, 58402, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 548:
			player->CastSpell(player, 63951, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 549:
			player->CastSpell(player, 63948, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 550:
			player->CastSpell(player, 58397, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 551:
			player->CastSpell(player, 58406, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 552:
			player->CastSpell(player, 63949, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 553:
			player->CastSpell(player, 63952, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 554:
			player->CastSpell(player, 58396, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 555:
			player->CastSpell(player, 58398, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 556:
			player->CastSpell(player, 58395, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 557:
			player->CastSpell(player, 58393, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 558:
			player->CastSpell(player, 63961, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 559:
			player->CastSpell(player, 63953, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 560:
			player->CastSpell(player, 63954, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 561:
			player->CastSpell(player, 63955, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 562:
			player->CastSpell(player, 58705, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 563:
			player->CastSpell(player, 59333, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 564:
			player->CastSpell(player, 58708, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 565:
			player->CastSpell(player, 58709, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 566:
			player->CastSpell(player, 58614, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 567:
			player->CastSpell(player, 63958, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 568:
			player->CastSpell(player, 58710, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 569:
			player->CastSpell(player, 58713, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 570:
			player->CastSpell(player, 59337, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 571:
			player->CastSpell(player, 63959, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 572:
			player->CastSpell(player, 58715, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 573:
			player->CastSpell(player, 58721, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 574:
			player->CastSpell(player, 58717, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 575:
			player->CastSpell(player, 58718, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 576:
			player->CastSpell(player, 58722, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 577:
			player->CastSpell(player, 58724, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 578:
			player->CastSpell(player, 58726, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 579:
			player->CastSpell(player, 58719, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 580:
			player->CastSpell(player, 58720, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 581:
			player->CastSpell(player, 59328, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 582:
			player->CastSpell(player, 58723, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 583:
			player->CastSpell(player, 58725, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;

		case 584:
			player->CastSpell(player, 58706, false);
			player->CLOSE_GOSSIP_MENU(); creature->Whisper("Your major glyph slot has been set.", LANG_UNIVERSAL, player);
			break;
		}
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
	{
		//main menu
		if (sender == GOSSIP_SENDER_MAIN)
			SendDefaultMenu(player, creature, uiAction);

		return true;
	}
};


void AddSC_ralph()
{
	new ralph();
}