/*
NPC_GiverDB_Hunterpets
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96104;
SET @CREATURTEMPLATE_NAME = "Giver NPC (Hunterpets)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GiverDB_Hunterpets', 0);

MySQL Testsyntax:
SELECT RequiredLevel, count(*) FROM world.item_template WHERE class = '15' AND subclass = '5' AND spellid_2 > '0' AND RequiredSkill > '0' GROUP BY RequiredLevel ORDER BY RequiredLevel ASC
*/

// ******************************************************************************
// include
// ******************************************************************************
#include "Pet.h"
// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GiverDB_Hunterpets : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GiverDB_Hunterpets() : CreatureScript("NPC_GiverDB_Hunterpets") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GiverDB_Hunterpets_DATA_filtered;
	array<string, 9>  NPC_GiverDB_Hunterpets_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	array<string, 47>  NPC_GiverDB_Hunterpets_DATA_family = { "NULL","Wolf","Cat","Spider","Bear","Boar","Crocolisk","Carrion","Crab","Gorilla","NULL","Raptor","Tallstrider","NULL","NULL","Felhunter","Voidwalker","Succubus","NULL","Doomguard","Scorpid","Turtle","NULL","Imp","Bat","Hyena","Owl","Wind Serpent","Remote Control","Felguard","Dragonhawk","Ravager","Warp Stalker","Sporebat","Nether Ray","Serpent","NULL","Moth","Chimaera","Devilsaur","Ghoul","Silithid","Worm","Rhino","Wasp","Core Hound","Spirit Beast" };
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t Alle zaehmbaren|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t nach Gruppen Seite 1|r", GOSSIP_SENDER_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t nach Gruppen Seite 2|r", GOSSIP_SENDER_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t Alle Exotischen|r", GOSSIP_SENDER_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-GroupLoot-Pass-Down:30:30:-18|t auf Wiedersehen|r", GOSSIP_SENDER_MAIN, 999);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}//OnGossipHello
	// ******************************************************************************
	// OnGossipSelect
	// ******************************************************************************
	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		if (sender == GOSSIP_SENDER_MAIN)
		{
			// --- verlassen
			if (action == 999)
			{
				creature->Say("Auf Wiedersehen.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			// --- im Kampf
			if (player->IsInCombat())
			{
				creature->Say("Du befindest Dich in einem Kampf. Da kann ich Dir nicht helfen !", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
				return true;
			}
			// --- Hauptmenu (Option 1)
			if (action == 105)
			{
				FN_getMYSQL(player, ">", 0, "=", "name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (Option 2)
			if (action == 110)
			{
				ClearGossipMenuFor(player);
				for (uint32 i = 1; i <= 25; i++)
				{
					if (NPC_GiverDB_Hunterpets_DATA_family[i] != "NULL")
						AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t zaehmbare '" + NPC_GiverDB_Hunterpets_DATA_family[i] + "'|r", GOSSIP_SENDER_MAIN, 1000 + i);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenu (Option 3)
			if (action == 115)
			{
				ClearGossipMenuFor(player);
				for (uint32 i = 26; i <= NPC_GiverDB_Hunterpets_DATA_family.size(); i++)
				{
					if (NPC_GiverDB_Hunterpets_DATA_family[i] != "NULL")
						AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t zaehmbare '" + NPC_GiverDB_Hunterpets_DATA_family[i] + "'|r", GOSSIP_SENDER_MAIN, 1000 + i);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenu (Option 4)
			if (action == 120)
			{
				FN_getMYSQL(player, ">", 0, ">", "name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (abbruch)
			if (action == 9997)
			{
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu (auswahl)
			if (action > 1000 && action < 9997)
			{
				uint32 i = (action - 1000);
				FN_getMYSQL(player, "=", i, "=", "name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- SubSubmenu (Hauptmenu)
			if (action == 999997)
			{
				StartIndex = 0;
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- SubSubmenu (weiter)
			if (action == 999998)
			{
				StartIndex = StartIndex + 25;
				if (StartIndex > NPC_GiverDB_Hunterpets_DATA_filtered.size())
					StartIndex = 0;
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- SubSubmenu (zurueck)
			if (action == 999999)
			{
				StartIndex = StartIndex - 25;
				if (StartIndex < 0)
					StartIndex = 0;
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- SubSubmenu (auswahl)
			if (action >= 100000 && action < 999997)
			{
				uint32 i = (action - 100000);
				if (NPC_GiverDB_Hunterpets_DATA_filtered[i] <= 0) {
					creature->Say("Diese zaehmbare Tier habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				CreatureTemplate const* creature_template = sObjectMgr->GetCreatureTemplate(NPC_GiverDB_Hunterpets_DATA_filtered[i]);
				if (!creature_template)
					return false;
				if (player->getClass() != CLASS_HUNTER)
				{
					creature->Say("Irgendwie siehts Du nicht wie einer aus der Jaegerklasse aus. Ich kann Dir daher kein Tier geben !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return true;
				}
				if (player->GetPet()) {
					creature->Say("Du musst erst dein aktives zaehmbare Tier 'parken' !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				if ((creature_template->type_flags & 65536) && !player->CanTameExoticPets())
				{
					creature->Say("Tja, Du kannst dieses exotische zaehmbare Tier (noch) nicht zaehmen. Ich kann Dir das daher auch nicht geben !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				Creature *creatureTarget = creature->SummonCreature(NPC_GiverDB_Hunterpets_DATA_filtered[i], player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
				if (!creatureTarget) 
					return false;
				Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
				if (!pet) 
					return false;
				creatureTarget->setDeathState(JUST_DIED);
				creatureTarget->RemoveCorpse();
				creatureTarget->SetHealth(0);
				pet->SetPower(POWER_HAPPINESS, 1048000);
				/*
				pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
				pet->GetMap()->Add((Creature*)pet);
				pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
				*/
				pet->UpdateAllStats();
				player->SetMinion(pet, true);
				pet->SavePetToDB(PET_SAVE_AS_CURRENT);
				pet->InitTalentForLevel();
				player->PetSpellInitialize();
				creature->Say("Ich habe Dir das gewuenschte zaehmbare Tier gegeben. Behandel es ja gut.", LANG_UNIVERSAL, NULL);
				return true;
			}
			return false;
		}//if sender
		return false;
	}//OnGossipSelect
	// ******************************************************************************
	// OnGossipSelect_Sub
	// ******************************************************************************
	bool OnGossipSelect_Sub(Player* player, Creature* creature, uint32 StartIndex)
	{
		ClearGossipMenuFor(player);
		uint32 zaehler = 0;
		uint32 MaxIndex = NPC_GiverDB_Hunterpets_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			// ---
			CreatureTemplate const* creature_template = sObjectMgr->GetCreatureTemplate(NPC_GiverDB_Hunterpets_DATA_filtered[i]);
			string t_name;
			if (CreatureLocale const* creature_locale = sObjectMgr->GetCreatureLocale(creature_template->Entry))
				sObjectMgr->GetLocaleString(creature_locale->Name, player->GetSession()->GetSessionDbLocaleIndex() , t_name);
			else
				t_name = creature_template->Name;
			// ---
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|t " + t_name + "|n|t (Familie '" + NPC_GiverDB_Hunterpets_DATA_family[creature_template->family] + "')|r", GOSSIP_SENDER_MAIN, 100000 + i);
			// ---
			zaehler = zaehler + 1;
			if (zaehler == 25)
			{
				StartIndex = i;
				break;
			}//if
		}//for
		if (StartIndex > 25)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 999999);
		if (StartIndex < MaxIndex)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-NextPage-Up:30:30:-18|t weiter|r", GOSSIP_SENDER_MAIN, 999998);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenu|r", GOSSIP_SENDER_MAIN, 999997);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	};//OnGossipSelect_Sub
	// ******************************************************************************
	// FN_getMYSQL
	// ******************************************************************************
	void FN_getMYSQL(Player* player, string t_familykennz, uint32 t_family, string t_exotickennz, string t_order)
	{
		NPC_GiverDB_Hunterpets_DATA_filtered.clear();
		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.creature_template WHERE type = '1' AND family > 0 AND (faction & %u) > '0' AND family %s '%u' AND (type_flags & 1) > '0' AND (type_flags & 65536) %s '0' ORDER BY %s", player->getFaction(), t_familykennz, t_family, t_exotickennz, t_order);
		if (result)
		{
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				NPC_GiverDB_Hunterpets_DATA_filtered.push_back(fields[0].GetUInt32());
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GiverDB_Hunterpets");
		}
		return;
	};//FN_getMYSQL
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GiverDB_Hunterpets()
{
	new NPC_GiverDB_Hunterpets();
};