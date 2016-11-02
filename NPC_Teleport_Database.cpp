/*
NPC_Teleport_Database
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96004;
SET @CREATURTEMPLATE_NAME = "TeleportViaDatabase NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Teleport_Database', 0);
*/

// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_Teleport_Database : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Teleport_Database() : CreatureScript("NPC_Teleport_Database") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	struct DBvector
	{
		uint32 id;
		float position_x;
		float position_y;
		float position_z;
		float orientation;
		uint32 map;
		string name;
		string icon;
	};
	vector<DBvector> NPC_Teleport_Database_DATAMYSQL;
	uint32 StartIndex = 0;
	// ---
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_TAXI, "|cff000000|TInterface\\icons\\Spell_Arcane_PortalShattrath:30:30:-18|t aus 'game_tele'|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_TAXI, "|cff000000|TInterface\\icons\\Spell_Arcane_PortalShattrath:30:30:-18|t aus 'areatrigger_teleport'|r", GOSSIP_SENDER_MAIN, 110);
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
				string Tabelle = "game_tele";
				FN_getMYSQL(Tabelle);
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (Option 2)
			if (action == 110)
			{
				string Tabelle = "areatrigger_teleport";
				FN_getMYSQL(Tabelle);
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (abbruch)
			if (action == 99997)
			{
				StartIndex = 0;
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu (weiter)
			if (action == 99998)
			{
				StartIndex = StartIndex + 25;
				if (StartIndex > NPC_Teleport_Database_DATAMYSQL.size())
					StartIndex = 0;
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (zurueck)
			if (action == 99999)
			{
				StartIndex = StartIndex - 25;
				if (StartIndex < 1)
					StartIndex = 0;
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (auswahl)
			if (action >= 10000 && action < 99997)
			{
				uint32 i = (action - 10000);
				if (i <= 0) {
					creature->Say("Diesen Ort kenne ich garnicht !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				creature->Say("Ich habe Dich teleportiert.", LANG_UNIVERSAL, NULL);
				player->TeleportTo(NPC_Teleport_Database_DATAMYSQL[i].map, NPC_Teleport_Database_DATAMYSQL[i].position_x, NPC_Teleport_Database_DATAMYSQL[i].position_y, NPC_Teleport_Database_DATAMYSQL[i].position_z, NPC_Teleport_Database_DATAMYSQL[i].orientation);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
		}//if sender
	}//OnGossipSelect
	// ******************************************************************************
	// OnGossipSelect_Sub
	// ******************************************************************************
	bool OnGossipSelect_Sub(Player* player, Creature* creature, uint32 StartIndex)
	{
		ClearGossipMenuFor(player);
		uint32 zaehler = 0;
		uint32 MaxIndex = NPC_Teleport_Database_DATAMYSQL.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			// ---
			AddGossipItemFor(player, GOSSIP_ICON_TAXI, "|cff000000|t " + NPC_Teleport_Database_DATAMYSQL[i].name + "|r", GOSSIP_SENDER_MAIN, 10000 + i);
			// ---
			zaehler = zaehler + 1;
			if (zaehler == 25)
			{
				StartIndex = i;
				break;
			}//if
		}//for
		if (StartIndex > 25)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 99999);
		if (StartIndex < MaxIndex)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-NextPage-Up:30:30:-18|t weiter|r", GOSSIP_SENDER_MAIN, 99998);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenu|r", GOSSIP_SENDER_MAIN, 99997);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	};//OnGossipSelect_Sub
	// ******************************************************************************
	// FN_getMYSQL
	// ******************************************************************************
	void FN_getMYSQL(string tTabelle)
	{
		NPC_Teleport_Database_DATAMYSQL.clear();
		// ---
		if (tTabelle == "game_tele")
		{
			QueryResult result = WorldDatabase.PQuery("SELECT id,position_x,position_y,position_z,orientation,map,name FROM world.game_tele ORDER BY name ASC");
			if (result)
			{
				Field * fields = NULL;
				do
				{
					fields = result->Fetch();
					DBvector data;
					if (fields[6].GetString().length() > 2)
					{
						data.id = fields[0].GetUInt32();
						data.position_x = fields[1].GetFloat();
						data.position_y = fields[2].GetFloat();
						data.position_z = fields[3].GetFloat();
						data.orientation = fields[4].GetFloat();
						data.map = fields[5].GetUInt32();
						data.name = fields[6].GetString();
						NPC_Teleport_Database_DATAMYSQL.push_back(data);
					}//if gueltig
				} while (result->NextRow());
			}
			else
			{
				TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_Teleport_Database");
			}
		}//if game_tele
		// ---
		if (tTabelle == "areatrigger_teleport")
		{
			QueryResult result = WorldDatabase.PQuery("SELECT ID,Name,target_map,target_position_x,target_position_y,target_position_z,target_orientation FROM world.areatrigger_teleport ORDER BY Name ASC");
			if (result)
			{
				Field * fields = NULL;
				do
				{
					fields = result->Fetch();
					DBvector data;
					if (fields[1].GetString().length() > 2)
					{
						data.id = fields[0].GetUInt32();
						data.position_x = fields[3].GetFloat();
						data.position_y = fields[4].GetFloat();
						data.position_z = fields[5].GetFloat();
						data.orientation = fields[6].GetFloat();
						data.map = fields[2].GetUInt32();
						data.name = fields[1].GetString();
						NPC_Teleport_Database_DATAMYSQL.push_back(data);
					}//if gueltig
				} while (result->NextRow());
			}
			else
			{
				TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_Teleport_Database");
			}
		}//if areatrigger_teleport
	}//FN_getMYSQL
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Teleport_Database()
{
	new NPC_Teleport_Database();
};