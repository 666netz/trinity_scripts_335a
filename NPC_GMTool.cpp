/*
NPC_GMTool
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 99999;
SET @CREATURTEMPLATE_NAME = "GMTool NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24935;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GMTool', 0);
*/

// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GMTool : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GMTool() : CreatureScript("NPC_GMTool") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 PLAYER_GUID = 0;
	uint32 PLAYER_TELE_M = 0;
	float PLAYER_TELE_X = 0;
	float PLAYER_TELE_Y = 0;
	float PLAYER_TELE_Z = 0;
	float PLAYER_TELE_O = 0;
	struct NPC_GMTool_PLAYERS_VECTOR
	{
		uint32 GUID;
		string name;
	};
	vector<NPC_GMTool_PLAYERS_VECTOR> NPC_GMTool_PLAYERS;
	struct NPC_GMTool_PLAYERSQUESTS_VECTOR
	{
		uint32 quest;
		string logtitle;
	};
	vector<NPC_GMTool_PLAYERSQUESTS_VECTOR> NPC_GMTool_PLAYERSQUESTS;
	// ******************************************************************************
	// parameter
	// ******************************************************************************
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		if (PLAYER_GUID <= 0)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "Player suchen", GOSSIP_SENDER_MAIN, 105, "Bitte Player-Name mit folgenden Fenster eingeben", 0, true);
		else
		{
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "Player hierher teleportieren", GOSSIP_SENDER_MAIN, 115);
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "Player zurueck teleportieren", GOSSIP_SENDER_MAIN, 120);
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "Player Quest complete", GOSSIP_SENDER_MAIN, 125);
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "Player freigeben", GOSSIP_SENDER_MAIN, 900);
		}
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "auf Wiedersehen", GOSSIP_SENDER_MAIN, 999);
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
			// --- zum Hauptmenu
			if (action == 997)
			{
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Player freigeben
			if (action == 900)
			{
				PLAYER_GUID = 0;
				PLAYER_TELE_M = 0;
				PLAYER_TELE_X = 0;
				PLAYER_TELE_Y = 0;
				PLAYER_TELE_Z = 0;
				PLAYER_TELE_O = 0;
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Player setzen
			if (action >= 100000 && action <= 199999)
			{
				uint32 i = action - 100000;
				PLAYER_GUID = NPC_GMTool_PLAYERS[i].GUID;
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Player hierher teleportieren
			if (action == 115)
			{
				Player* zielplayer = sObjectMgr->GetPlayerByLowGUID(PLAYER_GUID);
				/*
				if (zielplayer->IsAlive())
				{
					creature->Say("Kann Player nicht hierher teleportieren, da Tod !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				*/
				if (zielplayer->IsFlying())
				{
					creature->Say("Kann Player nicht hierher teleportieren, da momentan im Flug !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				if (zielplayer->IsInCombat())
				{
					creature->Say("Kann Player nicht hierher teleportieren, da momentan im Kampf !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				if (!zielplayer->IsInWorld())
				{
					creature->Say("Kann Player irgendwie nicht hierher teleportieren !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				uint32 PLAYER_TELE_M = zielplayer->GetMapId();
				float PLAYER_TELE_X = zielplayer->GetPositionX();
				float PLAYER_TELE_Y = zielplayer->GetPositionY();
				float PLAYER_TELE_Z = zielplayer->GetPositionZ();
				float PLAYER_TELE_O = zielplayer->GetOrientation();
				zielplayer->TeleportTo(player->GetMapId(), player->GetPositionX() + 2, player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation());
				creature->Say("Player wurde hierher teleportiert.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Player zurueck teleportieren
			if (action == 120)
			{
				if (PLAYER_TELE_M == 0 && PLAYER_TELE_X == 0 && PLAYER_TELE_Y == 0)
				{
					creature->Say("Kann Player nicht zurueck teleportieren !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				Player* zielplayer = sObjectMgr->GetPlayerByLowGUID(PLAYER_GUID);
				zielplayer->TeleportTo(PLAYER_TELE_M, PLAYER_TELE_X, PLAYER_TELE_Y, PLAYER_TELE_Z, PLAYER_TELE_O);
				creature->Say("Player wurde zurueck teleportiert.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Player Quests
			if (action == 125)
			{
				FN_GetPlayerQuestsFromDB(PLAYER_GUID);
				if (NPC_GMTool_PLAYERSQUESTS.size() <= 0)
				{
					creature->Say("Keine Quests mit diesen Angaben gefunden !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				ClearGossipMenuFor(player);
				for (uint32 i = 0; i < NPC_GMTool_PLAYERSQUESTS.size(); i++)
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "waehle Quest '" + NPC_GMTool_PLAYERSQUESTS[i].logtitle + "'", GOSSIP_SENDER_MAIN, 200000 + i);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "zurueck", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Player Quests setzen
			if (action >= 200000 && action <= 299999)
			{
				uint32 i = action - 200000;
				Player* zielplayer = sObjectMgr->GetPlayerByLowGUID(PLAYER_GUID);
				Quest const* zielquest = sObjectMgr->GetQuestTemplate(NPC_GMTool_PLAYERSQUESTS[i].quest);
				TC_LOG_ERROR("misc", "Marker 1 ziel:%u quest:%u", zielplayer->GetGUID(), zielquest->GetQuestId());
				zielplayer->CompleteQuest(zielquest->GetQuestId());
				creature->Say("Quest wurde completed.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			return false;
		}//if sender
	};//OnGossipSelect
	// ******************************************************************************
	// OnGossipSelectCode
	// ******************************************************************************
	bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) override
	{
		if (sender == GOSSIP_SENDER_MAIN)
		{
			// --- Player suchen & auflisten
			if (action == 105)
			{
				FN_GetPlayerFromDB(player,code);
				if (NPC_GMTool_PLAYERS.size() <= 0)
				{
					creature->Say("Keine Player mit diesen Angaben gefunden !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				if (NPC_GMTool_PLAYERS.size() > 25)
				{
					creature->Say("Ich habe zuviele gefunden. Bitte Namen weiter eingrenzen !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				ClearGossipMenuFor(player);
				for (uint32 i = 0; i < NPC_GMTool_PLAYERS.size(); i++)
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "waehle Player '"+NPC_GMTool_PLAYERS[i].name+"'", GOSSIP_SENDER_MAIN, 100000+i);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "zurueck", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			return false;
		}//if sender
	};//OnGossipSelectCode
	// ******************************************************************************
	// FN_GetPlayerFromDB
	// ******************************************************************************
	void FN_GetPlayerFromDB(Player* player, string SUCH) {
		NPC_GMTool_PLAYERS.clear();
		QueryResult result = WorldDatabase.PQuery("SELECT guid,name FROM characters.characters WHERE (guid = '%s' OR LOWER(name) LIKE LOWER('%s')) AND guid <> '%u' AND online = '1' ORDER BY name ASC", SUCH, SUCH, player->GetGUID());
		if (result)
		{
			NPC_GMTool_PLAYERS_VECTOR data;
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				data.GUID = fields[0].GetUInt32();
				data.name = fields[1].GetString();
				NPC_GMTool_PLAYERS.push_back(data);
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GMTool - FN_GetPlayerFromDB --- SELECT guid,name FROM characters.characters WHERE (guid = '%s' OR LOWER(name) LIKE LOWER('%s')) AND guid <> '%u' AND online = '1' ORDER BY name ASC", SUCH, SUCH, player->GetGUID());
		}
		return;
	}//FN_GetPlayerFromDB
	// ******************************************************************************
	// FN_GetPlayerQuestsFromDB
	// ******************************************************************************
	void FN_GetPlayerQuestsFromDB(uint32 GUID) {
		NPC_GMTool_PLAYERSQUESTS.clear();
		QueryResult result1 = CharacterDatabase.PQuery("SELECT quest FROM characters.character_queststatus WHERE guid = '%u' AND (status = '1' OR status = '3' OR status = '5') ORDER BY quest ASC LIMIT 25", GUID);
		if (result1)
		{
			NPC_GMTool_PLAYERSQUESTS_VECTOR data;
			Field * fields1 = NULL;
			Field * fields2 = NULL;
			do
			{
				fields1 = result1->Fetch();
				QueryResult result2 = WorldDatabase.PQuery("SELECT logtitle FROM world.quest_template WHERE ID = '%u' LIMIT 1", fields1[0].GetUInt32());
				fields2 = result2->Fetch();
				data.quest = fields1[0].GetUInt32();
				data.logtitle = fields2[0].GetString();
				NPC_GMTool_PLAYERSQUESTS.push_back(data);
			} while (result1->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GMTool - FN_GetPlayerQuestsFromDB");
		}
		return;
	}//FN_GetPlayerQuestsFromDB
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GMTool()
{
	new NPC_GMTool();
};
