/*
NPC_GiverDB_Equipment
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96106;
SET @CREATURTEMPLATE_NAME = "Giver NPC (Equipment)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GiverDB_Equipment', 0);

MySQL Testsyntax:
SELECT class,subclass,InventoryType, count(*) FROM world.item_template WHERE (class = '2' OR class = '4') AND RequiredSkill > '0' GROUP BY class,subclass,InventoryType ORDER BY class,subclass,InventoryType
*/

// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GiverDB_Equipment : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GiverDB_Equipment() : CreatureScript("NPC_GiverDB_Equipment") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GiverDB_Equipment_DATA_filtered;
	array<string, 9>  NPC_GiverDB_Equipment_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	uint32  NPC_GiverDB_Equipment_DATA_itemlevel = 245;
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Cloth_73:30:30:-18|t Ruestungen|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_14.blp:30:30:-18|t Waffen|r", GOSSIP_SENDER_MAIN, 110);
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
				ClearGossipMenuFor(player);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_DEATH_KNIGHT)
				{
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_22:30:30:-18|t Plattenruestung Kopf|r", GOSSIP_SENDER_MAIN, 1040401);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_31:30:30:-18|t Plattenruestung Schulter|r", GOSSIP_SENDER_MAIN, 1040403);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Plate01:30:30:-18|t Plattenruestung Brust|r", GOSSIP_SENDER_MAIN, 1040405);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_14:30:30:-18|t Plattenruestung Taille|r", GOSSIP_SENDER_MAIN, 1040406);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Plate_13:30:30:-18|t Plattenruestung Beine|r", GOSSIP_SENDER_MAIN, 1040407);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Plate_02:30:30:-18|t Plattenruestung Fuesse|r", GOSSIP_SENDER_MAIN, 1040408);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_24:30:30:-18|t Plattenruestung Handgelenke|r", GOSSIP_SENDER_MAIN, 1040409);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_10:30:30:-18|t Plattenruestung Haende|r", GOSSIP_SENDER_MAIN, 1040410);
				}
				if (player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_SHAMAN)
				{
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_41:30:30:-18|t Kettenruestung Kopf|r", GOSSIP_SENDER_MAIN, 1040301);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_69:30:30:-18|t Kettenruestung Schulter|r", GOSSIP_SENDER_MAIN, 1040303);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Mail_13:30:30:-18|t Kettenruestung Brust|r", GOSSIP_SENDER_MAIN, 1040305);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_45B:30:30:-18|t Kettenruestung Taille|r", GOSSIP_SENDER_MAIN, 1040306);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Mail_35:30:30:-18|t Kettenruestung Beine|r", GOSSIP_SENDER_MAIN, 1040307);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Chain_09:30:30:-18|t Kettenruestung Fuesse|r", GOSSIP_SENDER_MAIN, 1040308);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_29:30:30:-18|t Kettenruestung Handgelenke|r", GOSSIP_SENDER_MAIN, 1040309);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_11:30:30:-18|t Kettenruestung Haende|r", GOSSIP_SENDER_MAIN, 1040310);
				}
				if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_DRUID)
				{
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_15:30:30:-18|t Lederruestung Kopf|r", GOSSIP_SENDER_MAIN, 1040201);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_28:30:30:-18|t Lederruestung Schulter|r", GOSSIP_SENDER_MAIN, 1040303);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Leather_07:30:30:-18|t Lederruestung Brust|r", GOSSIP_SENDER_MAIN, 1040305);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_05:30:30:-18|t Lederruestung Taille|r", GOSSIP_SENDER_MAIN, 1040306);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Leather_36:30:30:-18|t Lederruestung Beine|r", GOSSIP_SENDER_MAIN, 1040307);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Leather_9:30:30:-18|t Lederruestung Fuesse|r", GOSSIP_SENDER_MAIN, 1040308);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_38:30:30:-18|t Lederruestung Handgelenke|r", GOSSIP_SENDER_MAIN, 1040309);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_67:30:30:-18|t Lederruestung Haende|r", GOSSIP_SENDER_MAIN, 1040310);
				}
				if (player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
				{
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_65:30:30:-18|t Stoffruestung Kopf|r", GOSSIP_SENDER_MAIN, 1040101);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_09:30:30:-18|t Stoffruestung Schulter|r", GOSSIP_SENDER_MAIN, 1040103);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Cloth_46:30:30:-18|t Stoffruestung Brust|r", GOSSIP_SENDER_MAIN, 1040105);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_26:30:30:-18|t Stoffruestung Taille|r", GOSSIP_SENDER_MAIN, 1040106);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Cloth_01:30:30:-18|t Stoffruestung Beine|r", GOSSIP_SENDER_MAIN, 1040107);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Cloth_10:30:30:-18|t Stoffruestung Fuesse|r", GOSSIP_SENDER_MAIN, 1040108);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_12:30:30:-18|t Stoffruestung Handgelenke|r", GOSSIP_SENDER_MAIN, 1040109);
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_16:30:30:-18|t Stoffruestung Haende|r", GOSSIP_SENDER_MAIN, 1040110);
				}
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_SHAMAN)
				{
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shield_09:30:30:-18|t Schilde|r", GOSSIP_SENDER_MAIN, 1040614);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9999997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenu (Option 2)
			if (action == 110)
			{
				ClearGossipMenuFor(player);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_WARLOCK)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MAIN, 1020013);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_DRUID)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MAIN, 1020117);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MAIN, 1020215);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MAIN, 1020326);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_SHAMAN	|| player->getClass() == CLASS_DRUID)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MAIN, 1020413);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MAIN, 1020517);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_DEATH_KNIGHT)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MAIN, 1020617);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MAIN, 1020713);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_DEATH_KNIGHT)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MAIN, 1020817);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_PRIEST	|| player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK || player->getClass() == CLASS_DRUID)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MAIN, 1021017);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MAIN, 1021313);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK || player->getClass() == CLASS_DRUID)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MAIN, 1021513);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MAIN, 1021625);
				if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MAIN, 1021826);
				if (player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
					AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MAIN, 1021926);
				AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MAIN, 1022017);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 9999997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			}
			// --- Submenu (Hauptmenu)
			if (action == 9999997)
			{
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
			}
			// --- Submenu (auswahl)
			if (action > 1000000 && action < 9999997)
			{
				// 1040401   1 = dummy | 4 = Ruestung | 4 = Plattenruestung | 1 = Kopf
				// 1020117   1 = dummy | 2 = Waffen | 1 = Zweihandaexte | 0 = NULL
				uint32 tbasis = (action - 1000000);
				uint32 tclass = floor(tbasis / 10000);
				tbasis = tbasis - (tclass * 10000);
				uint32 tsubclass = floor(tbasis / 100);
				tbasis = tbasis - (tsubclass * 100);
				uint32 tinventorytype = tbasis;
				uint32 tinventorytypeB = tinventorytype;
				uint32 tinventorytypeC = tinventorytype;
				if (tclass == 2 && tsubclass == 0 && tinventorytype == 13)
				{
					tinventorytypeB = 21;
					tinventorytypeC = 26;
				}
				if (tclass == 2 && tsubclass == 4 && tinventorytype == 13)
				{
					tinventorytypeB = 21;
					tinventorytypeC = 26;
				}
				if (tclass == 2 && tsubclass == 7 && tinventorytype == 13)
				{
					tinventorytypeB = 21;
					tinventorytypeC = 26;
				}
				if (tclass == 2 && tsubclass == 13 && tinventorytype == 13)
				{
					tinventorytypeB = 21;
					tinventorytypeC = 22;
				}
				if (tclass == 2 && tsubclass == 15 && tinventorytype == 13)
				{
					tinventorytypeB = 21;
					tinventorytypeC = 22;
				}
				FN_getMYSQL(player, tclass, tsubclass, tinventorytype, tinventorytypeB, tinventorytypeC, NPC_GiverDB_Equipment_DATA_itemlevel, "InventoryType ASC, ItemLevel DESC, name ASC");
				OnGossipSelect_Sub(player, creature, StartIndex);
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
				if (StartIndex > NPC_GiverDB_Equipment_DATA_filtered.size())
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
			if (action > 100000 && action < 999997)
			{
				uint32 i = (action - 100000);
				if (i <= 0 || NPC_GiverDB_Equipment_DATA_filtered[i] <= 0)
				{
					creature->Say("Diesen Gegenstand habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				if (player->HasItemCount(NPC_GiverDB_Equipment_DATA_filtered[i], 1, true))
				{
					creature->Say("Du hast bereits den Gegenstand. Nochmal geht leider nicht !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					return true;
				}
				player->AddItem(NPC_GiverDB_Equipment_DATA_filtered[i], 1);
				creature->Say("Ich habe Dir den gewuenschten Gegenstand gegeben.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
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
		uint32 MaxIndex = NPC_GiverDB_Equipment_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			// ---
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GiverDB_Equipment_DATA_filtered[i]);
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
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|t " + t_name + "|n|cff" + NPC_GiverDB_Equipment_DATA_quality[item_template->Quality] + "|t (iLevel "+ to_string(item_template->ItemLevel)+")|r", GOSSIP_SENDER_MAIN, 100000+i);
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
	void FN_getMYSQL(Player* player, uint32 t_class, uint32 t_subclass, uint32 t_inventorytype, uint32 t_inventorytypeB, uint32 t_inventorytypeC, uint32 t_itemlevel, string t_order)
	{
		NPC_GiverDB_Equipment_DATA_filtered.clear();
		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.item_template WHERE class = '%u' AND subclass = '%u' AND (InventoryType = '%u' OR InventoryType = '%u' OR InventoryType = '%u') AND itemLevel > '%u' AND (AllowableRace = '-1' OR (AllowableRace & %u) > 0) AND (AllowableClass = '-1' OR (AllowableClass & %u) > 0) ORDER BY %s", t_class, t_subclass, t_inventorytype, t_inventorytypeB, t_inventorytypeC, t_itemlevel, player->getRace(), player->getClass(), t_order);
		if (result)
		{
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				NPC_GiverDB_Equipment_DATA_filtered.push_back(fields[0].GetUInt32());
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GiverDB_Equipment");
		}
		return;
	};//FN_getMYSQL
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GiverDB_Equipment()
{
	new NPC_GiverDB_Equipment();
};