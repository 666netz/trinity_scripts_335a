/*
NPC_GiverDB_Goods
testet: 3.3.5a
stand: 28.10.2016

SET @CREATURTEMPLATE_ENTRY = 96107;
SET @CREATURTEMPLATE_NAME = "Giver NPC (Goods)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GiverDB_Goods', 0);

MySQL Testsyntax:
SELECT class,subclass, count(*) FROM world.item_template WHERE (class = '7' OR class = '9' OR class = '3' OR class = '0') AND (AllowableRace = '-1' OR (AllowableRace & 1) > 0) AND (AllowableClass = '-1' OR (AllowableClass & 1) > 0) GROUP BY class,subclass ORDER BY class,subclass ASC
*/

// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GiverDB_Goods : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GiverDB_Goods() : CreatureScript("NPC_GiverDB_Goods") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GiverDB_Goods_DATA_filtered;
	array<string, 9>  NPC_GiverDB_Goods_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	array<string, 16>  NPC_GiverDB_goods_DATA_sieben = { "NULL","Teile","Sprengstoff","Geraete","Juwelierskunst","Stoff","Leder","Metall und Stein","Fleisch","Kraeuter","Elementare","Andere","Verzauberkunst","Materialien","Ruestung Verbesserungen","Waffen Verbesserungen" };
	array<string, 11>  NPC_GiverDB_goods_DATA_neun = { "Buecher","Lederverarbeitungsmuster","Schneidereimuster","Ingenieurschemata","Schmiedekunstplaene","Kochrezepte","Alchimierezepte","Erste Hilfe - Buecher","Verzauberkunstformeln","Angelbuecher","Juwelenschleifer Vorlagen" };
	array<string, 9>  NPC_GiverDB_goods_DATA_drei = { "Rote Edelsteine","Blaue Edelsteine","Gelbe Edelsteine","Violette Edelsteine","Gruene Edelsteine","Orangene Edelsteine","Meta - Edelsteine","Einfache Edelsteine","Prismatische Edelsteine" };
	array<string, 9>  NPC_GiverDB_goods_DATA_null = { "NULL","Traenke","Elixiere","Flaeschchen","Rollen","Essen und Trinken","Gegenstandsverzauberungen","Verbaende","Andere" };
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Misc_StoneTablet_03:30:30:-18|t Handwerkswaren|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Scroll_03:30:30:-18|t Rezepte|r", GOSSIP_SENDER_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Misc_Gem_Stone_01:30:30:-18|t Edelsteine|r", GOSSIP_SENDER_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Potion_03:30:30:-18|t Traenke, Essen und Co|r", GOSSIP_SENDER_MAIN, 120);
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
			{	creature->Say("Auf Wiedersehen.", LANG_UNIVERSAL, NULL);
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
				ClearGossipMenuFor(player);
				for (uint32 i = 0; i < NPC_GiverDB_goods_DATA_sieben.size(); i++)
				{
					if (NPC_GiverDB_goods_DATA_sieben[i] != "NULL")
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Misc_StoneTablet_03:30:30:-18|t '" + NPC_GiverDB_goods_DATA_sieben[i] + "'|r", GOSSIP_SENDER_MAIN, 1000 + i);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenu (Option 2)
			if (action == 110)
			{
				ClearGossipMenuFor(player);
				for (uint32 i = 0; i < NPC_GiverDB_goods_DATA_neun.size(); i++)
				{
					if (NPC_GiverDB_goods_DATA_neun[i] != "NULL")
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Scroll_03:30:30:-18|t '" + NPC_GiverDB_goods_DATA_neun[i] + "'|r", GOSSIP_SENDER_MAIN, 2000 + i);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenu (Option 3)
			if (action == 115)
			{
				ClearGossipMenuFor(player);
				for (uint32 i = 0; i < NPC_GiverDB_goods_DATA_drei.size(); i++)
				{
					if (NPC_GiverDB_goods_DATA_drei[i] != "NULL")
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Misc_Gem_Stone_01:30:30:-18|t '" + NPC_GiverDB_goods_DATA_drei[i] + "'|r", GOSSIP_SENDER_MAIN, 3000 + i);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenu (Option 4)
			if (action == 120)
			{
				ClearGossipMenuFor(player);
				for (uint32 i = 0; i < NPC_GiverDB_goods_DATA_null.size(); i++)
				{
					if (NPC_GiverDB_goods_DATA_null[i] != "NULL")
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Potion_03:30:30:-18|t '" + NPC_GiverDB_goods_DATA_null[i] + "'|r", GOSSIP_SENDER_MAIN, 4000 + i);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Submenu (abbruch)
			if (action == 9997)
			{
				StartIndex = 0;
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu (auswahl 1)
			if (action >= 1000 && action <= 1999)
			{
				uint32 i = (action - 1000);
				FN_getMYSQL(player, 7, i,"name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (auswahl 2)
			if (action >= 2000 && action <= 2999)
			{
				uint32 i = (action - 2000);
				FN_getMYSQL(player, 9, i, "name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (auswahl 3)
			if (action >= 3000 && action <= 3999)
			{
				uint32 i = (action - 3000);
				FN_getMYSQL(player, 3, i, "name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
				return true;
			}
			// --- Submenu (auswahl 4)
			if (action >= 4000 && action <= 4999)
			{
				uint32 i = (action - 4000);
				FN_getMYSQL(player, 0, i, "name ASC");
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
				if (StartIndex > NPC_GiverDB_Goods_DATA_filtered.size())
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
			// --- Submenu (auswahl)
			if (action >= 100000 && action < 999997)
			{
				uint32 i = (action - 100000);
				if (NPC_GiverDB_Goods_DATA_filtered[i] <= 0) {
					creature->Say("Dieses habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Goods_DATA_filtered[i]);
				if (player->HasItemCount(NPC_GiverDB_Goods_DATA_filtered[i], 1000, true))
				{
					creature->Say("Du hast dieses schon mehr als genug !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				if (item_template->Stackable == 20)
				{
					player->AddItem(NPC_GiverDB_Goods_DATA_filtered[i], item_template->Stackable);
					creature->Say("Ich habe Dir einen Stapel des gewuenschten gegeben.", LANG_UNIVERSAL, NULL);
				}
				else
				{
					player->AddItem(NPC_GiverDB_Goods_DATA_filtered[i], 1);
					creature->Say("Ich habe Dir ein Stueck des gewuenschten gegeben.", LANG_UNIVERSAL, NULL);
				}
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
		uint32 MaxIndex = NPC_GiverDB_Goods_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			// ---
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Goods_DATA_filtered[i]);
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
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|t " + t_name + "|r", GOSSIP_SENDER_MAIN, 100000 + i);
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
	void FN_getMYSQL(Player* player, uint32 t_class, uint32 t_subclass, string ORDER)
	{
		NPC_GiverDB_Goods_DATA_filtered.clear();

		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.item_template WHERE class = '%u' AND subclass = '%u' AND (AllowableRace = '-1' OR (AllowableRace & %u) > 0) AND (AllowableClass = '-1' OR (AllowableClass & %u) > 0) ORDER BY %s LIMIT 750", t_class, t_subclass, player->getRace(), player->getClass(), ORDER);
		if (result)
		{
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				NPC_GiverDB_Goods_DATA_filtered.push_back(fields[0].GetUInt32());
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GiverDB_Goods");
		}
		return;
	};//FN_getMYSQL
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GiverDB_Goods()
{
	new NPC_GiverDB_Goods();
};