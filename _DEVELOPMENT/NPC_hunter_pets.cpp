		/*__________________________
		|	  Made by Obitus		|
		|	  March 8, 2016		    |
		|	  Tested on 3.3.5a		|
		|___________________________|
		*/

/*
-- Execute this query in WORLD DATABASE --
------------------------------------------
INSERT INTO `item_template` (`entry`, `class`, `name`, `displayid`, `Quality`, `Flags`, `AllowableClass`, `AllowableRace`, `maxcount`, `stackable`, `spellid_1`, `spellcooldown_1`, `spellcategorycooldown_1`, `spellcooldown_2`, `spellcategorycooldown_2`, `spellcooldown_3`, `spellcategorycooldown_3`, `spellcooldown_4`, `spellcategorycooldown_4`, `spellcooldown_5`, `spellcategorycooldown_5`, `bonding`, `description`, `RequiredDisenchantSkill`, `ScriptName`, `VerifiedBuild`) 
VALUES (191000, 15, 'Choose a pet', 20629, 7, 2147483680, 4, -1, 1, 1, 24228, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 'Right click on me.', -1, 'item_beastmaster', 12340);
*/

#include "ScriptMgr.h"
#include "Chat.h"
#include "Define.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Pet.h"
#include "ObjectMgr.h"
#include "WorldSession.h"

//      Creature        entry
#define CHIMERA			21879
#define CORE_HOUND		21108
#define DEVILSAUR		20931
#define RHINO			30445
#define SILITHID		5460
#define WORM			30148
#define LOQUE_NAHAK		32517
#define SKOLL			35189
#define GONDRIA			33776
#define SPIDER			2349
#define DRAGONHAWK		27946
#define BAT				28233
#define RAVAGER			17199
#define RAPTOR			14821
#define SERPENT			28358
#define BEAR			29319
#define BOAR			29996
#define WASP			28085
#define CAT				28097
#define CARRION_BIRD	26838
#define CRAB			24478
#define CROCOLISK		1417
#define GORILLA			28213
#define BLIGHT_HOUND	29452
#define HYENA			13036
#define MOTH			27421
#define OWL				23136
#define TALLSTRIDER		22807
#define SCORPID			9698
#define TURTLE			25482

//Gossip Menu
#define NORMAL_PET_PAGE_1			GOSSIP_ACTION_INFO_DEF + 1
#define NORMAL_PET_PAGE_2			GOSSIP_ACTION_INFO_DEF + 2
#define EXOTIC_PET					GOSSIP_ACTION_INFO_DEF + 3
#define STABLE_PET					GOSSIP_ACTION_INFO_DEF + 4
#define RESET_PET_TALENTS			GOSSIP_ACTION_INFO_DEF + 5
#define RENAME_PET					GOSSIP_ACTION_INFO_DEF + 6
#define MAIN_MENU					GOSSIP_ACTION_INFO_DEF + 7


class item_beastmaster : public ItemScript
{
	public:
		item_beastmaster() : ItemScript("item_beastmaster") {}

		void CreatePet(Player* player, Item* item, uint32 entry)
		{
			if (player->GetPet())
			{
				player->GetSession()->SendAreaTriggerMessage("You must leave or stable your current pet in order to gain a new one.");
				player->PlayerTalkClass->SendCloseGossip();
				return;
			}

			Creature *creatureTarget = player->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
			if (!creatureTarget) return;

			Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);

			if (!pet)
				return;

			creatureTarget->setDeathState(JUST_DIED);
			creatureTarget->RemoveCorpse();
			creatureTarget->SetHealth(0);                      

			pet->SetPower(POWER_HAPPINESS, 1048000);
			pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
			pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
			pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
			pet->GetMap()->AddToMap(pet->ToCreature());
			pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());

			pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
			if (!pet->InitStatsForLevel(player->getLevel()))
				pet->UpdateAllStats();

			player->SetMinion(pet, true);

			pet->SavePetToDB(PET_SAVE_AS_CURRENT);
			pet->InitTalentForLevel();
			player->PetSpellInitialize();

			player->PlayerTalkClass->SendCloseGossip();
		}


		bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
		{
			if (player->IsInCombat())
			{
				player->GetSession()->SendAreaTriggerMessage("You can't use this item in combat!");
				player->CLOSE_GOSSIP_MENU();
				return true;
			}
			player->PlayerTalkClass->ClearMenus();

			player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_BeastTaming:30|t New Pet", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_1);
			if (player->CanTameExoticPets())
			{
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_BeastMastery:30|t New Exotic Pet", GOSSIP_SENDER_MAIN, EXOTIC_PET);
			}
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\INV_Box_PetCarrier_01:30|t Stable Pet", GOSSIP_SENDER_MAIN, STABLE_PET);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_GoForTheThroat:30|t Reset Pet Talents", GOSSIP_SENDER_MAIN, RESET_PET_TALENTS);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\INV_Scroll_11:30|t Rename pet", GOSSIP_SENDER_MAIN, RENAME_PET);
			player->SEND_GOSSIP_MENU(1, item->GetGUID());
			return true;
		}

		void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override
		{
			
			player->PlayerTalkClass->ClearMenus();

			switch(action)
			{
			case MAIN_MENU:
				player->PlayerTalkClass->ClearMenus();

				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_BeastTaming:30|t New Pet", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_1);
				if (player->CanTameExoticPets())
				{
					player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_BeastMastery:30|t New Exotic Pet", GOSSIP_SENDER_MAIN, EXOTIC_PET);
				}
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\INV_Box_PetCarrier_01:30|t Stable Pet", GOSSIP_SENDER_MAIN, STABLE_PET);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_GoForTheThroat:30|t Reset Pet Talents", GOSSIP_SENDER_MAIN, RESET_PET_TALENTS);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\INV_Scroll_11:30|t Rename pet", GOSSIP_SENDER_MAIN, RENAME_PET);
				player->SEND_GOSSIP_MENU(1, item->GetGUID());
				break;

			case NORMAL_PET_PAGE_1:
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Bat:30|t Bat", GOSSIP_SENDER_MAIN,					1);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Bear:30|t Bear", GOSSIP_SENDER_MAIN,					2);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Boar:30|t Boar", GOSSIP_SENDER_MAIN,					3);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Cat:30|t Cat", GOSSIP_SENDER_MAIN,					4);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Vulture:30|t Carrion Bird", GOSSIP_SENDER_MAIN,		5);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Crab:30|t Crab", GOSSIP_SENDER_MAIN,					6);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Crocolisk:30|t Crocolisk", GOSSIP_SENDER_MAIN,		7);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_DragonHawk:30|t DragonHawk", GOSSIP_SENDER_MAIN,		8);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Gorilla:30|t Gorilla", GOSSIP_SENDER_MAIN,			9);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Wolf:30|t BlightHound", GOSSIP_SENDER_MAIN,			10);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Hyena:30|t Hyena", GOSSIP_SENDER_MAIN,				11);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Moth:30|t Moth", GOSSIP_SENDER_MAIN,					12);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Owl:30|t Owl", GOSSIP_SENDER_MAIN,					13);
				player->ADD_GOSSIP_ITEM(2, "|TInterface\\Icons\\Trade_Engineering:30|t Next Page ->", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_2);
				player->ADD_GOSSIP_ITEM(2, "|TInterface\\Icons\\Trade_Engineering:30|t Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(1, item->GetGUID());
				break;

			case NORMAL_PET_PAGE_2:
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Raptor:30|t Raptor", GOSSIP_SENDER_MAIN,				14);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Ravager:30|t Ravager", GOSSIP_SENDER_MAIN,			15);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_TallStrider:30|t Tallstrider", GOSSIP_SENDER_MAIN,	16);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Scorpid:30|t Scorpid", GOSSIP_SENDER_MAIN,			17);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Spider:30|t Spider", GOSSIP_SENDER_MAIN,				18);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_WindSerpent:30|t Serpent", GOSSIP_SENDER_MAIN,		19);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Turtle:30|t Turtle", GOSSIP_SENDER_MAIN,				20);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Wasp:30|t Wasp", GOSSIP_SENDER_MAIN,					21);
				player->ADD_GOSSIP_ITEM(2, "|TInterface\\Icons\\Trade_Engineering:30|t <- Previous Page", GOSSIP_SENDER_MAIN, NORMAL_PET_PAGE_1);
				player->ADD_GOSSIP_ITEM(2, "|TInterface\\Icons\\Trade_Engineering:30|t Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(1, item->GetGUID());
				break;

			case EXOTIC_PET:
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Chimera:30|t Chimera", GOSSIP_SENDER_MAIN,			22);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_CoreHound:30|t Core Hound", GOSSIP_SENDER_MAIN,		23);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Devilsaur:30|t Devilsaur", GOSSIP_SENDER_MAIN,		24);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Rhino:30|t Rhino", GOSSIP_SENDER_MAIN,				25);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Silithid:30|t Silithid", GOSSIP_SENDER_MAIN,			26);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Worm:30|t Worm", GOSSIP_SENDER_MAIN,					27);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\INV_Misc_Head_Tiger_01:30|t Loque'nahak", GOSSIP_SENDER_MAIN,			28);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\Ability_Hunter_Pet_Wolf:30|t Skoll", GOSSIP_SENDER_MAIN,				29);
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\Icons\\ability_mount_spectraltiger:30|t Spectral Tiger", GOSSIP_SENDER_MAIN,	30);
				player->ADD_GOSSIP_ITEM(2, "|TInterface\\Icons\\Trade_Engineering:30|t Back to Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(1, item->GetGUID());
				break;
				
			case 1:
				CreatePet(player, item, BAT);
				break;

			case 2:
				CreatePet(player, item, BEAR);
				break;

			case 3:
				CreatePet(player, item, BOAR);
				break;

			case 4:
				CreatePet(player, item, CAT);
				break;

			case 5:
				CreatePet(player, item, CARRION_BIRD);
				break;

			case 6:
				CreatePet(player, item, CRAB);
				break;

			case 7:
				CreatePet(player, item, CROCOLISK);
				break;

			case 8:
				CreatePet(player, item, DRAGONHAWK);
				break;

			case 9:
				CreatePet(player, item, GORILLA);
				break;

			case 10:
				CreatePet(player, item, BLIGHT_HOUND);
				break;

			case 11:
				CreatePet(player, item, HYENA);
				break;

			case 12:
				CreatePet(player, item, MOTH);
				break;

			case 13:
				CreatePet(player, item, OWL);
				break;

			case 14:
				CreatePet(player, item, RAPTOR);
				break;

			case 15:
				CreatePet(player, item, RAVAGER);
				break;

			case 16:
				CreatePet(player, item, TALLSTRIDER);
				break;

			case 17:
				CreatePet(player, item, SCORPID);
				break;

			case 18:
				CreatePet(player, item, SPIDER);
				break;

			case 19:
				CreatePet(player, item, SERPENT);
				break;

			case 20:
				CreatePet(player, item, TURTLE);
				break;

			case 21:
				CreatePet(player, item, WASP);
				break;

			case 22:
				CreatePet(player, item, CHIMERA);
				break;
			
			case 23:
				CreatePet(player, item, CORE_HOUND);
				break;
			
			case 24:
				CreatePet(player, item, DEVILSAUR);
				break;

			case 25:
				CreatePet(player, item, RHINO);
				break;

			case 26:
				CreatePet(player, item, SILITHID);
				break;

			case 27:
				CreatePet(player, item, WORM);
				break;

			case 28:
				CreatePet(player, item, LOQUE_NAHAK);
				break;

			case 29:
				CreatePet(player, item, SKOLL);
				break;

			case 30:
				CreatePet(player, item, GONDRIA);
				break;

			
					case RESET_PET_TALENTS: 
						if (player->GetPet())
						{
							player->ResetPetTalents();
							player->GetSession()->SendAreaTriggerMessage("Your pet talents have been reset.");
							player->CLOSE_GOSSIP_MENU();
							
						}
						else
						{
							player->GetSession()->SendNotification("You don't have a pet!");
							player->CLOSE_GOSSIP_MENU();
						}
						break;

						
					case STABLE_PET:
							player->CastSpell(player, 62757, true); // Call Stabled Pet
							player->CLOSE_GOSSIP_MENU();
						break;

						
					case RENAME_PET:
							player->CastSpell(player, 59385, true); //Certificate of Ownership Spell - no cast time
							player->CLOSE_GOSSIP_MENU();
						break;

				}
		}
};

void AddSC_item_beastmaster()
{
	new item_beastmaster;
}