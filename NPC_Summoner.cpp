/*
NPC_Summoner
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96006;
SET @CREATURTEMPLATE_NAME = "NPC Summoner";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Summoner', 0);
*/

// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_Summoner : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Summoner() : CreatureScript("NPC_Summoner") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	vector<uint32> NPC_Summoner_DATA_filtered;
	// ******************************************************************************
	// parameter
	// ******************************************************************************
	uint32 SUMMONER_CREATUREFOLLOW = 0; //0=disabled / 1=emabled
	uint32 SUMMONER_DESPAWNAFTER = 1; //0=disabled / 1=emabled
	uint32 SUMMONER_CREATUREENTRYMIN = 96001;
	uint32 SUMMONER_CREATUREENTRYMAX = 96010;
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		FN_getMYSQL(SUMMONER_CREATUREENTRYMIN, SUMMONER_CREATUREENTRYMAX);
		for (uint32 i = 0; i < NPC_Summoner_DATA_filtered.size(); i++)
		{
			CreatureTemplate const* creature_template = sObjectMgr->GetCreatureTemplate(NPC_Summoner_DATA_filtered[i]);
			AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t " + creature_template->Name +" herbeirufen|r", GOSSIP_SENDER_MAIN, NPC_Summoner_DATA_filtered[i]);
		}
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
				player->GetSession()->SendNotification("Du befindest Dich in einem Kampf. Da kann ich Dir nicht helfen !");
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			// --- ausfuehrung
			if (action >= SUMMONER_CREATUREENTRYMIN && action <= SUMMONER_CREATUREENTRYMAX)
			{
				if (NPC_Summoner_DATA_filtered[action] == creature->GetEntry())
				{
					player->GetSession()->SendNotification("Ich kann mich doch nicht selber nochmal beschwoeren !");
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return true;
				}
				if (player->FindNearestCreature(action, 50.0f))
				{
					player->GetSession()->SendNotification("Es befindet sich bereits einer von denen in der Naehe !");
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return true;
				}
				Creature* creature2 = player->SummonCreature(action, player->GetPositionX() - 2, player->GetPositionY() + 5, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60 * IN_MILLISECONDS);
				creature2->Say("Hallo. Ich stehe dir nun fuer 1 Minute zur Verfuegung.", LANG_UNIVERSAL, NULL);
				if (SUMMONER_CREATUREFOLLOW == 1)
					creature2->GetMotionMaster()->MoveFollow(player, 0.2f, PET_FOLLOW_ANGLE, MOTION_SLOT_ACTIVE);
				if (SUMMONER_DESPAWNAFTER == 1)
					creature->DespawnOrUnsummon(1 * IN_MILLISECONDS);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			return false;
		}//if sender
		return false;
	}//OnGossipSelect
	// ******************************************************************************
	// FN_getMYSQL
	// ******************************************************************************
	void FN_getMYSQL(uint32 t_entrymin, uint32 t_entrymax)
	{
		NPC_Summoner_DATA_filtered.clear();
		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.creature_template WHERE entry >= '%u' AND entry <= '%u' ORDER BY name ASC", t_entrymin, t_entrymax);
		if (result)
		{
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				NPC_Summoner_DATA_filtered.push_back(fields[0].GetUInt32());
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_NPCSummoner");
		}
		return;
	};//FN_getMYSQL
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Summoner()
{
	new NPC_Summoner();
};
