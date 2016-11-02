/*
NPC_GiverDB_Bags
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96102;
SET @CREATURTEMPLATE_NAME = "Giver NPC (Bags)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GiverDB_Bags', 0);

MySQL Testsyntax:
SELECT subclass,ContainerSlots, count(*) FROM world.item_template WHERE class = '1' GROUP BY subclass,ContainerSlots ORDER BY subclass ASC, ContainerSlots ASC
*/

// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GiverDB_Bags : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GiverDB_Bags() : CreatureScript("NPC_GiverDB_Bags") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GiverDB_Bags_DATA_filtered;
	array<string, 9>  NPC_GiverDB_Bags_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Alle Taschen|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen bis 10 Faecher|r", GOSSIP_SENDER_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen bis 20 Faecher|r", GOSSIP_SENDER_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen bis 30 Faecher|r", GOSSIP_SENDER_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen ab 31 Faecher|r", GOSSIP_SENDER_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Sondertaschen|r", GOSSIP_SENDER_MAIN, 130);
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
			// --- Hauptemnu (Option 1)
			if (action == 105)
			{
				FN_getMYSQL(player, "=", 0, 99, "name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptemnu (option 2)
			if (action == 110)
			{
				FN_getMYSQL(player, "=", 0, 10, "ContainerSlots ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptemnu (option 3)
			if (action == 115)
			{
				FN_getMYSQL(player, "=", 11, 20, "ContainerSlots ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptemnu (option 4)
			if (action == 120)
			{
				FN_getMYSQL(player, "=", 21, 30, "ContainerSlots ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptemnu (option 5)
			if (action == 125)
			{
				FN_getMYSQL(player, "=", 31, 99, "ContainerSlots ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Hauptemnu (option 6)
			if (action == 130)
			{
				FN_getMYSQL(player, ">", 0, 99, "ContainerSlots ASC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
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
				if (StartIndex > NPC_GiverDB_Bags_DATA_filtered.size())
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
				if (NPC_GiverDB_Bags_DATA_filtered[i] <= 0) {
					creature->Say("Diese Tasche habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Bags_DATA_filtered[i]);
				if (player->HasItemCount(NPC_GiverDB_Bags_DATA_filtered[i], 20, true))
				{
					creature->Say("Du hast diese Taschen schon mehr als genug !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				player->AddItem(NPC_GiverDB_Bags_DATA_filtered[i], 1);
				creature->Say("Ich habe Dir die gewuenschte Tasche gegeben.", LANG_UNIVERSAL, NULL);
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
		uint32 MaxIndex = NPC_GiverDB_Bags_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			// ---
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Bags_DATA_filtered[i]);
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
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|t " + t_name + "|n|cff" + NPC_GiverDB_Bags_DATA_quality[item_template->Quality] + "|t (Faecher " + to_string(item_template->ContainerSlots) + ")|r", GOSSIP_SENDER_MAIN, 100000 + i);
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
	void FN_getMYSQL(Player* player, string t_subclasskennz, uint32 t_containerslotsmin, uint32 t_containerslotsmax, string ORDER)
	{
		NPC_GiverDB_Bags_DATA_filtered.clear();

		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.item_template WHERE class = '1' AND (AllowableRace = '-1' OR (AllowableRace & %u) > 0) AND (AllowableClass = '-1' OR (AllowableClass & %u) > 0) AND subclass %s '0' AND ContainerSlots >= '%u' AND ContainerSlots <= '%u' ORDER BY %s", player->getRace(), player->getClass(), t_subclasskennz, t_containerslotsmin, t_containerslotsmax, ORDER);
		if (result)
		{
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				NPC_GiverDB_Bags_DATA_filtered.push_back(fields[0].GetUInt32());
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GiverDB_Bags");
		}
		return;
	};//FN_getMYSQL
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GiverDB_Bags()
{
	new NPC_GiverDB_Bags();
};