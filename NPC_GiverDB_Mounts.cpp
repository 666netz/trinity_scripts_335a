/*
NPC_GiverDB_Mounts
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96101;
SET @CREATURTEMPLATE_NAME = "Giver NPC (Mounts)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GiverDB_Mounts', 0);

MySQL Testsyntax:
SELECT RequiredLevel, count(*) FROM world.item_template WHERE class = '15' AND subclass = '5' AND spellid_2 > '0' AND RequiredSkill > '0' GROUP BY RequiredLevel ORDER BY RequiredLevel ASC
*/

// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GiverDB_Mounts : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GiverDB_Mounts() : CreatureScript("NPC_GiverDB_Mounts") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GiverDB_Mounts_DATA_filtered;
	array<string, 9>  NPC_GiverDB_Mounts_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Alle Reittiere|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere bis LV 20|r", GOSSIP_SENDER_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere bis LV 40|r", GOSSIP_SENDER_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere bis LV 60|r", GOSSIP_SENDER_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere ab LV 61|r", GOSSIP_SENDER_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Gib mir alle die du hast|r", GOSSIP_SENDER_MAIN, 130);
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
				FN_getMYSQL(player, 0, 99, "name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (Option 2)
			if (action == 110)
			{
				FN_getMYSQL(player, 0, 20, "RequiredLevel ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (Option 3)
			if (action == 115)
			{
				FN_getMYSQL(player, 21, 40, "RequiredLevel ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (Option 4)
			if (action == 120)
			{
				FN_getMYSQL(player, 41, 60, "RequiredLevel ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (Option 5)
			if (action == 125)
			{
				FN_getMYSQL(player, 61, 99, "RequiredLevel ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptmenu (Option 6)
			if (action == 130)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				FN_getMYSQL(player, 0, 999, "name ASC");
				uint32 MaxIndex = NPC_GiverDB_Mounts_DATA_filtered.size();
				for (uint32 i = 0; i < MaxIndex; i++)
				{
					ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Mounts_DATA_filtered[i]);
					if (!player->HasItemCount(NPC_GiverDB_Mounts_DATA_filtered[i], 1, true) && !player->HasSpell(item_template->Spells[1].SpellId))
					{
						//player->AddItem(NPC_GiverDB_Mounts_DATA_filtered[i], 1);
						player->LearnSpell(item_template->Spells[1].SpellId, false);
					}//if
				}//for
				creature->Say("Ich habe Dir alle moeglichen Reittiere gelehrt.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			// --- Submenu (abbruch)
			if (action == 999997)
			{
				StartIndex = 0;
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu (weiter)
			if (action == 999998)
			{
				StartIndex = StartIndex + 25;
				if (StartIndex > NPC_GiverDB_Mounts_DATA_filtered.size())
					StartIndex = 0;
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (zurueck)
			if (action == 999999)
			{
				StartIndex = StartIndex - 25;
				if (StartIndex < 0)
					StartIndex = 0;
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (auswahl)
			if (action >= 100000 && action < 999997)
			{
				uint32 i = (action - 100000);
				if (NPC_GiverDB_Mounts_DATA_filtered[i] <= 0) {
					creature->Say("Dieses Reittier habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Mounts_DATA_filtered[i]);
				if (player->HasItemCount(NPC_GiverDB_Mounts_DATA_filtered[i], 1, true) || player->HasSpell(item_template->Spells[1].SpellId))
				{
					creature->Say("Du hast dieses Reittier schon !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				player->AddItem(NPC_GiverDB_Mounts_DATA_filtered[i], 1);
				creature->Say("Ich habe Dir das gewuenschte Reittier gegeben.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipSelect_Sub(player, creature, StartIndex);
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
		uint32 MaxIndex = NPC_GiverDB_Mounts_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			// ---
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Mounts_DATA_filtered[i]);
			string t_name;
			string t_icon;
			if (ItemLocale const* item_locale = sObjectMgr->GetItemLocale(item_template->ItemId))
				sObjectMgr->GetLocaleString(item_locale->Name, player->GetSession()->GetSessionDbLocaleIndex() , t_name);
			else
				t_name = item_template->Name1;
			/* bis dato nicht in dbc_stores.cpp
			const ItemDisplayInfoEntry* dispInfo = NULL;
			dispInfo = sItemDisplayInfoStore.LookupEntry(item_template->DisplayInfoID);
			if (dispInfo)
				t_icon = dispInfo->inventoryIcon;
			char const ItemDisplayTemplateEntryfmt[] = "nxxxxxxxxxxixxxxxxxxxxx";
			DBCStorage <ItemDisplayInfoEntry> sItemDisplayInfoStore(ItemDisplayTemplateEntryfmt); //-- not used currently
			LoadDBC(dbcCount, availableDbcLocales, bad_dbc_files, sItemDisplayInfoStore,        dbcPath, "ItemDisplayInfo.dbc"); //    -- not used currently
			*/
			// ---
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|t " + t_name + "|n|cff" + NPC_GiverDB_Mounts_DATA_quality[item_template->Quality] + "|t (ab Level " + to_string(item_template->RequiredLevel) + ")|r", GOSSIP_SENDER_MAIN, 100000 + i);
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
	void FN_getMYSQL(Player* player, uint32 t_requiredlevelmin, uint32 t_requiredlevelmax, string ORDER)
	{
		NPC_GiverDB_Mounts_DATA_filtered.clear();

		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.item_template WHERE class = '15' AND subclass = '5' AND spellid_2 > '0' AND RequiredSkill > '0' AND (AllowableRace = '-1' OR (AllowableRace & %u) > 0) AND (AllowableClass = '-1' OR (AllowableClass & %u) > 0) AND RequiredLevel >= %u AND RequiredLevel <= %u ORDER BY %s",player->getRace(), player->getClass(), t_requiredlevelmin, t_requiredlevelmax, ORDER);
		if (result)
		{
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				NPC_GiverDB_Mounts_DATA_filtered.push_back(fields[0].GetUInt32());
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GiverDB_Mounts");
		}
		return;
	};//FN_getMYSQL
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GiverDB_Mounts()
{
	new NPC_GiverDB_Mounts();
};