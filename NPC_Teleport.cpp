/*
NPC_Teleport
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96001;
SET @CREATURTEMPLATE_NAME = "Teleport NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Teleport', 0);
*/

// ******************************************************************************
// class
// ******************************************************************************
class NPC_Teleport : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Teleport() : CreatureScript("NPC_Teleport") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	void FN_wait(unsigned int mseconds) //wartefunktion
	{
		clock_t goal = mseconds + clock();
		while (goal > clock());
	}
	// ******************************************************************************
	// parameter
	// ******************************************************************************
	uint32 PARAM_FILTERPLAYERLEVEL = 0;//0=disabled / 1=enabled (Info: z.Zt. nur Gebiete)
	uint32 PARAM_ALLOWPLAYERTREFF = 0;//0=disabled / 1=enabled
	uint32 PARAM_ALLOWGMINSEL = 0;//0=disabled / 1=enabled
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		if (player->GetTeam() == ALLIANCE)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Human:30:30:-18|t Allianz Hauptstaedte|r", GOSSIP_SENDER_MAIN, 1000);
		if (player->GetTeam() == HORDE)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Orc:30:30:-18|t Horde Hauptstaedte|r", GOSSIP_SENDER_MAIN, 2000);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\INV_Misc_TabardSummer02:30:30:-18|t Neutrale Staedte|r", GOSSIP_SENDER_MAIN, 3000);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\INV_Misc_Map_01:30:30:-18|t Gebiete|r", GOSSIP_SENDER_MAIN, 4000);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Dungeon_Ulduar80_Normal:30:30:-18|t Dungeons|r", GOSSIP_SENDER_MAIN, 5000);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Dungeon_Ulduar80_25man:30:30:-18|t Raids|r", GOSSIP_SENDER_MAIN, 6000);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Misc_HellifrePVPHonorHoldFavor:30:30:-18|t PVP-Gebiete|r", GOSSIP_SENDER_MAIN, 7000);
		if (PARAM_ALLOWPLAYERTREFF == 1 && player->GetTeam() == ALLIANCE)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_PVP_A_H:30:30:-18|t Zum Playertreff|r", GOSSIP_SENDER_MAIN, 19010);
		if (PARAM_ALLOWGMINSEL == 1 && player->GetTeam() == HORDE)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_PVP_A_H:30:30:-18|t Zum Playertreff|r", GOSSIP_SENDER_MAIN, 19015);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Shadow_GhostKey:30:30:-18|t Zu meiner Heimat|r", GOSSIP_SENDER_MAIN, 19020);
		if (PARAM_ALLOWGMINSEL == 1 && player->GetSession()->GetSecurity() >= 2) // Or RBAC 'HasPermission(rbac::PERMISSION_NAME);'
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\chatframe\\Achievement_Zone_IsleOfQuelDanas:30:30:-18|t Zur GM-Insel|r", GOSSIP_SENDER_MAIN, 19025);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-GroupLoot-Pass-Down:30:30:-18|t auf Wiedersehen|r", GOSSIP_SENDER_MAIN, 9999);
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
			if (action == 9999)
			{
				creature->Say("Auf Wiedersehen.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			// --- abbruch
			if (action == 9998)
			{
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Allianz Staedte
			if (action == 1000)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_NightElf:30:30:-18|t Darnassus|r", GOSSIP_SENDER_MAIN, 11010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Draenei:30:30:-18|t Die Exodar|r", GOSSIP_SENDER_MAIN, 11015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_gnome:30:30:-18|t Eisenschmiede|r", GOSSIP_SENDER_MAIN, 11020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Human:30:30:-18|t Sturmwind|r", GOSSIP_SENDER_MAIN, 11025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Horde Staedte
			if (action == 2000)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Orc:30:30:-18|t Orgrimmar|r", GOSSIP_SENDER_MAIN, 12010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_BloodElf:30:30:-18|t Silbermond|r", GOSSIP_SENDER_MAIN, 12015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Tauren:30:30:-18|t Donnerfels|r", GOSSIP_SENDER_MAIN, 12020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_scourge:30:30:-18|t Unterstadt|r", GOSSIP_SENDER_MAIN, 12025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Neutrale Staedte
			if (action == 3000)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Spell_Arcane_PortalShattrath:30:30:-18|t Shattrath|r", GOSSIP_SENDER_MAIN, 13010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Spell_Arcane_PortalDalaran:30:30:-18|t Dalaran|r", GOSSIP_SENDER_MAIN, 13015);
				if (player->getClass() == CLASS_DEATH_KNIGHT)//nur Todesritter
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Spell_DeathKnight_AntiMagicZone:30:30:-18|t Acherus - Die Schwarze Festung|r", GOSSIP_SENDER_MAIN, 13020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Achievement_PVP_G_09:30:30:-18|t Beutebucht|r", GOSSIP_SENDER_MAIN, 13025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Achievement_PVP_G_09:30:30:-18|t Ewige Warte|r", GOSSIP_SENDER_MAIN, 13030);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Achievement_PVP_G_09:30:30:-18|t Gadegetzan|r", GOSSIP_SENDER_MAIN, 13035);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Achievement_PVP_G_09:30:30:-18|t Mudsprocket|r", GOSSIP_SENDER_MAIN, 13040);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Achievement_PVP_G_09:30:30:-18|t Ratchet|r", GOSSIP_SENDER_MAIN, 13045);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Achievement_PVP_G_09:30:30:-18|t Insel von Quel'Danas|r", GOSSIP_SENDER_MAIN, 13050);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Gebiete
			if (action == 4000)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_Kalimdor_01:30:30:-18|t Kalimdor|r", GOSSIP_SENDER_MAIN, 4010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_EasternKingdoms_01:30:30:-18|t Oestliche Koenigreiche|r", GOSSIP_SENDER_MAIN, 4015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_Outland_01:30:30:-18|t Scherbenwelt|r", GOSSIP_SENDER_MAIN, 4020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_Northrend_01:30:30:-18|t Northrend|r", GOSSIP_SENDER_MAIN, 4025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Gebiete - Kalimor
			if (action == 4010)
			{
				ClearGossipMenuFor(player);
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 10))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Teldrassil (1-10)|r", GOSSIP_SENDER_MAIN, 14005);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Azuremyst Isle (1-10)|r", GOSSIP_SENDER_MAIN, 14010);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Durotar (1-10)|r", GOSSIP_SENDER_MAIN, 14015);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Mulgore (1-10)|r", GOSSIP_SENDER_MAIN, 14020);
				}//1>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 10))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Bloodmyst Isle (10-20)|r", GOSSIP_SENDER_MAIN, 14025);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Darkshore (10-20)|r", GOSSIP_SENDER_MAIN, 14030);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t The Barrens (10-25)|r", GOSSIP_SENDER_MAIN, 14035);
				}//10>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 10))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Stonetalon Mountains (15-27)|r", GOSSIP_SENDER_MAIN, 14040);
				}//15>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 18))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ashenvale (18-30)|r", GOSSIP_SENDER_MAIN, 14045);
				}//18>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 25))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Thousand Needles (25-35)|r", GOSSIP_SENDER_MAIN, 14050);
				}//25>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 30))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Desolace (30-40)|r", GOSSIP_SENDER_MAIN, 14055);
				}//30>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 35))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Dustwallow Marsh (35-45)|r", GOSSIP_SENDER_MAIN, 14060);
				}//35>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 40))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Tanaris (40-50)|r", GOSSIP_SENDER_MAIN, 14065);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Feralas (40-50)|r", GOSSIP_SENDER_MAIN, 14070);
				}//40>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 45))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Azshara (45-55)|r", GOSSIP_SENDER_MAIN, 14075);
				}//45>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 48))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Felwood (48-55)|r", GOSSIP_SENDER_MAIN, 14080);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Un'Goro Crater (45-55)|r", GOSSIP_SENDER_MAIN, 14085);
				}//48>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 55))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Silithus (55-60)|r", GOSSIP_SENDER_MAIN, 14090);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Winterspring (55-60)|r", GOSSIP_SENDER_MAIN, 14095);
				}//55>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 1))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Moonglade (1-80)|r", GOSSIP_SENDER_MAIN, 14100);
				}//1>
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Gebiete - Oestliche Koenigreiche
			if (action == 4015)
			{
				ClearGossipMenuFor(player);
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 1))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Eversong Woods (1-10)|r", GOSSIP_SENDER_MAIN, 14105);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Tirisfal Glades (1-10)|r", GOSSIP_SENDER_MAIN, 14110);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Dun Morogh (1-10)|r", GOSSIP_SENDER_MAIN, 14115);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Elwynn Forest (1-10)|r", GOSSIP_SENDER_MAIN, 14120);
				}//1>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 10))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ghostlands (10-20)|r", GOSSIP_SENDER_MAIN, 14125);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Silverpine Forest (10-20)|r", GOSSIP_SENDER_MAIN, 14130);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Westfall (10-20)|r", GOSSIP_SENDER_MAIN, 14135);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Loch Modan (10-20)|r", GOSSIP_SENDER_MAIN, 14140);
				}//10>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 15))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Redridge Mountains (15-25)|r", GOSSIP_SENDER_MAIN, 14145);
				}//18>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 18))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Duskwood (18-30)|r", GOSSIP_SENDER_MAIN, 14150);
				}//18>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 20))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Wetlands (20-30)|r", GOSSIP_SENDER_MAIN, 14155);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Hillsbrad Foothills (20-30)|r", GOSSIP_SENDER_MAIN, 14160);
				}//20>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 30))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Alterac Mountains (30-40)|r", GOSSIP_SENDER_MAIN, 14165);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Arathi Highlands (30-40)|r", GOSSIP_SENDER_MAIN, 14170);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Stranglethorn Vale (30-45)|r", GOSSIP_SENDER_MAIN, 14175);
				}//30>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 35))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Swamp of Sorrows (35-45)|r", GOSSIP_SENDER_MAIN, 14180);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Badlads (35-45)|r", GOSSIP_SENDER_MAIN, 14185);
				}//35>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 40))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t The Hinterlands (40-50)|r", GOSSIP_SENDER_MAIN, 14190);
				}//40>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 43))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Searing Gorge (43-50)|r", GOSSIP_SENDER_MAIN, 14195);
				}//43>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 45))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Blasted Lands (45-55)|r", GOSSIP_SENDER_MAIN, 14200);
				}//45>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 50))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Burning Steppes (50-58)|r", GOSSIP_SENDER_MAIN, 14205);
				}//50>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 51))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Western Plaguelands (51-58)|r", GOSSIP_SENDER_MAIN, 14210);
				}//51>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 53))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Eastern Plaguelands (53-60)|r", GOSSIP_SENDER_MAIN, 14215);
				}//53>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 55))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Deadwind Pass (55-60)|r", GOSSIP_SENDER_MAIN, 14220);
				}//55>
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Gebiete - Scherbenwelt
			if (action == 4020)
			{
				ClearGossipMenuFor(player);
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 58))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Hellfire Peninsula (58-63)|r", GOSSIP_SENDER_MAIN, 14225);
				}//58>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 60))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Zangarmarsh (60-64)|r", GOSSIP_SENDER_MAIN, 14230);
				}//60>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 62))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Terokkar Forest (62-65)|r", GOSSIP_SENDER_MAIN, 14235);
				}//62>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 64))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Nagrand (64-67)|r", GOSSIP_SENDER_MAIN, 14240);
				}//64>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 65))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Blade's Edge Mountains (65-68)|r", GOSSIP_SENDER_MAIN, 14245);
				}//65>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 67))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Shadowmoon Valley (67-70)|r", GOSSIP_SENDER_MAIN, 14250);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Netherstorm (67-70)|r", GOSSIP_SENDER_MAIN, 14255);
				}//67>
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Gebiete - Northrend
			if (action == 4025)
			{
				ClearGossipMenuFor(player);
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 68))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Borean Tundra (68-72)|r", GOSSIP_SENDER_MAIN, 14260);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Howling Fjord (68-72)|r", GOSSIP_SENDER_MAIN, 14265);
				}//68>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 71))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Dragonblight (71-74)|r", GOSSIP_SENDER_MAIN, 14270);
				}//71>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 73))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Grizzly Hills (73-75)|r", GOSSIP_SENDER_MAIN, 14275);
				}//73>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 74))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Zul'Drak (74-77)|r", GOSSIP_SENDER_MAIN, 14280);
				}//74>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 76))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Sholazar Basin (76-78)|r", GOSSIP_SENDER_MAIN, 14285);
				}//76>
				if (PARAM_FILTERPLAYERLEVEL == 0 || (PARAM_FILTERPLAYERLEVEL == 1 && player->getLevel() >= 77))
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Crystalsong Forest (77-80)|r", GOSSIP_SENDER_MAIN, 14290);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t The Storm Peaks (77-80)|r", GOSSIP_SENDER_MAIN, 14295);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Icecrown (77-80)|r", GOSSIP_SENDER_MAIN, 14300);
				}//77>
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Dungeons
			if (action == 5000)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_Kalimdor_01:30:30:-18|t Kalimdor|r", GOSSIP_SENDER_MAIN, 5010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_EasternKingdoms_01:30:30:-18|t Oestliche Koenigreiche|r", GOSSIP_SENDER_MAIN, 5015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_Outland_01:30:30:-18|t Scherbenwelt|r", GOSSIP_SENDER_MAIN, 5020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Zone_Northrend_01:30:30:-18|t Northrend|r", GOSSIP_SENDER_MAIN, 5025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Dungeons - Kalimdor
			if (action == 5010)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Blackfathom Deeps (20-30)|r", GOSSIP_SENDER_MAIN, 15005);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Caverns of Time (60-70)|r", GOSSIP_SENDER_MAIN, 150010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Dire Maul (50-60)|r", GOSSIP_SENDER_MAIN, 15015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Maraudon (30-46)|r", GOSSIP_SENDER_MAIN, 15020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Onyxia's Lair (??-??)|r", GOSSIP_SENDER_MAIN, 15025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ragefire Chasm (15-21)|r", GOSSIP_SENDER_MAIN, 15030);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Razorfen Downs (35-43)|r", GOSSIP_SENDER_MAIN, 15035);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Razorfen Kraul (30-40)|r", GOSSIP_SENDER_MAIN, 15040);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ruins of Ahn'Qiraj (??-??)|r", GOSSIP_SENDER_MAIN, 15045);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Temple of Ahn'Qiraj (??-??)|r", GOSSIP_SENDER_MAIN, 15050);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Wailing Caverns (15-25)|r", GOSSIP_SENDER_MAIN, 15055);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Zul'Farrak (40-48)|r", GOSSIP_SENDER_MAIN, 15060);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Dungeons - Oestliche Koenigreiche
			if (action == 5015)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Blackrock Depths (50-60)|r", GOSSIP_SENDER_MAIN, 15065);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Blackrock Spire (50-60)|r", GOSSIP_SENDER_MAIN, 15070);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Blackwing Lair (??-??)|r", GOSSIP_SENDER_MAIN, 15075);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Deadmines (15-21)|r", GOSSIP_SENDER_MAIN, 15080);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Gnomeregan (24-34)|r", GOSSIP_SENDER_MAIN, 15085);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Insel von Quel'Danas (??-??)|r", GOSSIP_SENDER_MAIN, 15090);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Karazhan (??-??)|r", GOSSIP_SENDER_MAIN, 15095);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Molten Core (??-??)|r", GOSSIP_SENDER_MAIN, 15100);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Scarlet Monastery (26-42)|r", GOSSIP_SENDER_MAIN, 15105);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Scholomance (50-60)|r", GOSSIP_SENDER_MAIN, 15110);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Shadowfang Keep (16-26)|r", GOSSIP_SENDER_MAIN, 15115);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Stratholme (50-60)|r", GOSSIP_SENDER_MAIN, 15120);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Sunken Temple (45-55)|r", GOSSIP_SENDER_MAIN, 15125);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t The Stockade (20-30)|r", GOSSIP_SENDER_MAIN, 15130);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Uldaman (35-45)|r", GOSSIP_SENDER_MAIN, 154135);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Zul'Aman (??-??)|r", GOSSIP_SENDER_MAIN, 154140);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Zul'Gurub|r", GOSSIP_SENDER_MAIN, 15145);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Dungeons - Scherbenwelt
			if (action == 5020)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Auchindoun (60-70)|r", GOSSIP_SENDER_MAIN, 15150);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Black Temple (??-??)|r", GOSSIP_SENDER_MAIN, 15155);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Coilfang Reservoir (60-69)|r", GOSSIP_SENDER_MAIN, 15160);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Gruul's Lair (??-??)|r", GOSSIP_SENDER_MAIN, 15165);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Hellfire Citadel (60-68)|r", GOSSIP_SENDER_MAIN, 15170);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Tempest Keep (60-70)|r", GOSSIP_SENDER_MAIN, 15175);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Dungeons - Northrend
			if (action == 5025)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ahn'Kahet - The Old Kingdom (73-75)|r", GOSSIP_SENDER_MAIN, 15180);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Azjol-Nerub (72-74)|r", GOSSIP_SENDER_MAIN, 15185);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Drak'Tharon Keep (74-76)|r", GOSSIP_SENDER_MAIN, 15190);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Gun'Drak (76-78)|r", GOSSIP_SENDER_MAIN, 15195);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Icecrown Citadel (??-??)|r", GOSSIP_SENDER_MAIN, 15200);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Naxxramas (??-??)|r", GOSSIP_SENDER_MAIN, 15205);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t The Nexus (71-73)|r", GOSSIP_SENDER_MAIN, 15210);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t The Obsidian Sanctum (??-??)|r", GOSSIP_SENDER_MAIN, 15215);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Utgarde Keep (70-72)|r", GOSSIP_SENDER_MAIN, 15220);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Utgarde Pinnacle (80)|r", GOSSIP_SENDER_MAIN, 15225);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ulduar (??-??)|r", GOSSIP_SENDER_MAIN, 15230);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Violet Hold (75-77)|r", GOSSIP_SENDER_MAIN, 15235);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Raids
			if (action == 6000)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Zul'Gurub (Lv60)|r", GOSSIP_SENDER_MAIN, 16005);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Molten Core (Lv60)|r", GOSSIP_SENDER_MAIN, 16010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Blackwing Lair (Lv60)|r", GOSSIP_SENDER_MAIN, 16015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ahn'Qiraj Ruins (Lv60)|r", GOSSIP_SENDER_MAIN, 16020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ahn'Qiraj Temple (Lv60)|r", GOSSIP_SENDER_MAIN, 16025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Karazhan (Lv70)|r", GOSSIP_SENDER_MAIN, 16030);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Gruul's Lair (Lv70)|r", GOSSIP_SENDER_MAIN, 16035);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Magtheridon's Lair (Lv70)|r", GOSSIP_SENDER_MAIN, 16040);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Zul'Aman (Lv70)|r", GOSSIP_SENDER_MAIN, 16045);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Serpentshrine Cavern (Lv70)|r", GOSSIP_SENDER_MAIN, 16050);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Tempest Keep: The Eye (Lv70)|r", GOSSIP_SENDER_MAIN, 16055);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Hyjal (Lv70)|r", GOSSIP_SENDER_MAIN, 16060);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Black Temple (Lv70)|r", GOSSIP_SENDER_MAIN, 16065);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Sunwell Plateau (Lv70)|r", GOSSIP_SENDER_MAIN, 16070);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Naxxramas (Lv80)|r", GOSSIP_SENDER_MAIN, 16075);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Obsidian Sanctum (Lv80)|r", GOSSIP_SENDER_MAIN, 16080);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ruby Sanctum (Lv80)|r", GOSSIP_SENDER_MAIN, 16085);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Vault of Archavon (Lv80)|r", GOSSIP_SENDER_MAIN, 16090);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Eye of Eternity (Lv80)|r", GOSSIP_SENDER_MAIN, 16095);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Ulduar (Lv80)|r", GOSSIP_SENDER_MAIN, 16100);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Icecrown Citadel (Lv80)|r", GOSSIP_SENDER_MAIN, 16105);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Trial of the Crusader (Lv80)|r", GOSSIP_SENDER_MAIN, 16110);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\buttons\\ButtonHilight-Square:30:30:-18|t Onyxia's Lair (Lv80)|r", GOSSIP_SENDER_MAIN, 61115);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- PVP-Gebiete
			if (action == 7000)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_PVP_P_06:30:30:-18|t Gurubashi Arena|r", GOSSIP_SENDER_MAIN, 17010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_PVP_P_07:30:30:-18|t Circle of Blood Arena|r", GOSSIP_SENDER_MAIN, 17015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_PVP_P_08:30:30:-18|t The Ring of Trials|r", GOSSIP_SENDER_MAIN, 17020);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_PVP_P_08:30:30:-18|t Wintergrasp|r", GOSSIP_SENDER_MAIN, 17025);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 9998);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- ausfuehrung
			if (action > 10000 && action < 19000)
			{
				// --- im Kampf
				if (player->IsInCombat())
				{
					creature->Say("Du befindest Dich in einem Kampf. Da kann ich Dich nirgends hinteleportieren !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return false;
				}
				// wartefunktion
				creature->Say("Ich teleportiere Dich jetzt zu dem gewuenschten Ort.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				FN_wait(2000);
				// --- switch
				switch (action)
				{
					// --- Hauptstaedte - Allianz
					case 11010: // Darnassus
						player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
						break;
					case 11015: // Exodar
						player->TeleportTo(530, -3954.20f, -11656.54f, -138.69f, 0.0f);
						break;
					case 11020: // Eisenschmiede
						player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
						break;
					case 11025: // Sturmwind
						player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
						break;
					// --- Hauptstaedte - Horde
					case 12010: // Orgrimmar
						player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
						break;
					case 12015: // Silbermond
						player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
						break;
					case 12020: // Donnerfels
						player->TeleportTo(1, -1290.0f, 147.033997f, 129.682007f, 4.919000f);
						break;
					case 12025: // Unterstadt
						player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
						break;
					// --- Hauptstaedte - Neutral
					case 13010:// Shattrath
						CloseGossipMenuFor(player);
						player->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
						break;
					case 13015: //Dalaran 
						player->TeleportTo(571, 5819.08f, 643.99f, 647.80f, 3.32f);
						break;
					case 13020:// Ebon Hold
						player->TeleportTo(0, 2353.530029f, -5665.819824f, 426.028015f, 0.596f);
						break;
					case 13025:// Booty Bay
						player->TeleportTo(0, -14438.2f, 472.22f, 15.32f, 0.65f);
						break;
					case 13030: //Everlook
						player->TeleportTo(1, 6724.77f, -4610.68f, 720.78f, 4.78f);
						break;
					case 13035: //Gadgetzan
						player->TeleportTo(1, -7173.26f, -3785.60f, 8.37f, 6.13f);
						break;
					case 13040: //Mudsprocket
						player->TeleportTo(1, -4564.79f, -3172.38f, 33.93f, 3.21f);
						break;
					case 13045: //Ratchet
						player->TeleportTo(1, -956.664f, -3754.71f, 5.33239f, 0.996637f);
						break;
					case 13050:// Insel von Quel'Danas
						player->TeleportTo(530, 12947.4f, -6893.31f, 5.68398f, 3.09154f);
						break;
					// --- Gebiete - Kalimdor
					case 14005: // Teldrassil
						player->TeleportTo(1, 10111.3f, 1557.73f, 1324.33f, 4.04239f);
						break;
					case 14010: // Azuremyst Isle
						player->TeleportTo(530, -4216.87f, -12336.9f, 4.34247f, 6.02008f);
						break;
					case 14015: // Durotar
						player->TeleportTo(1, 1007.78f, -4446.22f, 11.2022f, 0.20797f);
						break;
					case 14020: // Mulgore
						player->TeleportTo(1, -2192.62f, -736.317f, -13.3274f, 0.487569f);
						break;
					case 14025: // Bloodmyst Isle
						player->TeleportTo(530, -1993.62f, -11475.8f, 63.9657f, 5.29437f);
						break;
					case 14030: // Darkshore
						player->TeleportTo(1, 5756.25f, 298.505f, 20.6049f, 5.96504f);
						break;
					case 14035: // The Barrens
						player->TeleportTo(1, 884.54f, -3548.45f, 91.8532f, 2.95957f);
						break;
					case 14040: // Stonetalon Mountains
						player->TeleportTo(1, 1570.92f, 1031.52f, 137.959f, 3.33006f);
						break;
					case 14045: // Ashenvale
						player->TeleportTo(1, 1928.34f, -2165.95f, 93.7896f, 0.205731f);
						break;
					case 14050: // Thousand Needles
						player->TeleportTo(1, -4969.02f, -1726.89f, -62.1269f, 3.7933f);
						break;
					case 14055: // Desolace
						player->TeleportTo(1, -606.395f, 2211.75f, 92.9818f, 0.809746f);
						break;
					case 14060: // Dustwallow Marsh
						player->TeleportTo(1, -4043.65f, -2991.32f, 36.3984f, 3.37443f);
						break;
					case 14065: // Tanaris
						player->TeleportTo(1, -7931.2f, -3414.28f, 80.7365f, 0.66522f);
						break;
					case 14070: // Feralas
						player->TeleportTo(1, -4841.19f, 1309.44f, 81.3937f, 1.48501f);
						break;
					case 14075: // Azshara
						player->TeleportTo(1, 3341.36f, -4603.79f, 92.5027f, 5.28142f);
						break;
					case 14080: // Felwood
						player->TeleportTo(1, 4102.25f, -1006.79f, 272.717f, 0.790048f);
						break;
					case 14085: // Un'Goro Crater
						player->TeleportTo(1, -7943.22f, -2119.09f, -218.343f, 6.0727f);
						break;
					case 14090: // Silithus
						player->TeleportTo(1, -7426.87f, 1005.31f, 1.13359f, 2.96086f);
						break;
					case 14095: // Winterspring
						player->TeleportTo(1, 6759.18f, -4419.63f, 763.214f, 4.43476f);
						break;
					case 14100: // Moonglade
						player->TeleportTo(1, 7654.3f, -2232.87f, 462.107f, 5.96786f);
						break;
					// --- Gebiete - Oestliche Koenigreiche
					case 14105: // Eversong Woods
						player->TeleportTo(530, 9079.92f, -7193.23f, 55.6013f, 5.94597f);
						break;
					case 14110: // Tirisfal Glades
						player->TeleportTo(0, 2036.02f, 161.331f, 33.8674f, 0.143896f);
						break;
					case 14115: // Dun Morogh
						player->TeleportTo(0, -5451.55f, -656.992f, 392.675f, 0.66789f);
						break;
					case 14120: // Elwynn Forest
						player->TeleportTo(0, -9617.06f, -288.949f, 57.3053f, 4.72687f);
						break;
					case 14125: // Ghostlands
						player->TeleportTo(530, 7360.86f, -6803.3f, 44.2942f, 5.83679f);
						break;
					case 14130: // Silverpine Forest
						player->TeleportTo(0, 878.74f, 1359.33f, 50.355f, 5.89929f);
						break;
					case 14135: // Westfall
						player->TeleportTo(0, -10235.2f, 1222.47f, 43.6252f, 6.2427f);
						break;
					case 14140: // Loch Modan
						player->TeleportTo(0, -5202.94f, -2855.18f, 336.822f, 0.37651f);
						break;
					case 14145: // Redridge Mountains
						player->TeleportTo(0, -9551.81f, -2204.73f, 93.473f, 5.47141f);
						break;
					case 14150: // Duskwood
						player->TeleportTo(0, -10898.3f, -364.784f, 39.2681f, 3.04614f);
						break;
					case 14155: // Wetlands
						player->TeleportTo(0, -3242.81f, -2469.04f, 15.9226f, 6.03924f);
						break;
					case 14160: // Hillsbrad Foothills
						player->TeleportTo(0, -436.657f, -581.254f, 53.5944f, 1.25917f);
						break;
					case 14165: // Alterac Mountains
						player->TeleportTo(0, 370.763f, -491.355f, 175.361f, 5.37858f);
						break;
					case 14170: // Arathi Highlands
						player->TeleportTo(0, -1508.51f, -2732.06f, 32.4986f, 3.35708f);
						break;
					case 14175: // Strangelthorn Vale
						player->TeleportTo(0, -12644.3f, -377.411f, 10.1021f, 6.09978f);
						break;
					case 14180: // Swamp of Sorrows
						player->TeleportTo(0, -10345.4f, -2773.42f, 21.99f, 5.08426f);
						break;
					case 14185: // Badlands
						player->TeleportTo(0, -6779.2f, -3423.64f, 241.667f, 0.647481f);
						break;
					case 14190: // The Hinterlands
						player->TeleportTo(0, 119.387f, -3190.37f, 117.331f, 2.34064f);
						break;
					case 14195: // Searing Gorge
						player->TeleportTo(0, -7012.47f, -1065.13f, 241.786f, 5.63162f);
						break;
					case 14200: // Blasted Lands
						player->TeleportTo(0, -11182.5f, -3016.67f, 7.42235f, 4.0004f);
						break;
					case 14205: // Burning Steppes
						player->TeleportTo(0, -8118.54f, -1633.83f, 132.996f, 0.089067f);
						break;
					case 14210: // Western Plaguelands
						player->TeleportTo(0, 1728.65f, -1602.25f, 63.429f, 1.6558f);
						break;
					case 14215: // Eastern Plaguelands
						player->TeleportTo(0, 2300.97f, -4613.36f, 73.6231f, 0.367722f);
						break;
					case 14220: // Deadwind Pass
						player->TeleportTo(0, -10438.8f, -1932.75f, 104.617f, 4.77402f);
						break;
					// --- Gebiete - Scherbenwelt
					case 14225: // Hellfire Peninsula
						player->TeleportTo(530, -211.237f, 4278.54f, 86.5678f, 4.59776f);
						break;
					case 14230: // Zangarmarsh
						player->TeleportTo(530, -54.8621f, 5813.44f, 20.9764f, 0.081722f);
						break;
					case 14235: // Terokkar Forest
						player->TeleportTo(530, -2000.47f, 4451.54f, 8.37917f, 4.40447f);
						break;
					case 14240: // Nagrand
						player->TeleportTo(530, -1145.95f, 8182.35f, 3.60249f, 6.13478f);
						break;
					case 14245: // Blade's Edge Mountains
						player->TeleportTo(530, 3037.67f, 5962.86f, 130.774f, 1.27253f);
						break;
					case 14250: // Shadowmoon Valley
						player->TeleportTo(530, -3179.6f, 2716.43f, 68.6444f, 4.16414f);
						break;
					case 14255: // Netherstorm
						player->TeleportTo(530, 3830.23f, 3426.5f, 88.6145f, 5.16677f);
						break;
					// --- Gebiete - Northrend
					case 14260: // Borean Tundra
						player->TeleportTo(571, 3256.57f, 5278.23f, 40.8046f, 0.246367f);
						break;
					case 14265: // Howling Fjord
						player->TeleportTo(571, 1902.15f, -4883.91f, 171.363f, 3.11537f);
						break;
					case 14270: // Dragonblight
						player->TeleportTo(571, 4103.36f, 264.478f, 50.5019f, 3.09349f);
						break;
					case 14275: // Grizzly Hills
						player->TeleportTo(571, 4391.73f, -3587.92f, 238.531f, 3.57526f);
						break;
					case 14280: // Zul'Drak
						player->TeleportTo(571, 5560.23f, -3211.66f, 371.709f, 5.55055f);
						break;
					case 14285: // Sholazar Basin
						player->TeleportTo(571, 5323, 4942, -133.5f, 2.17f);
						break;
					case 14290: // Crystalsong Forest
						player->TeleportTo(571, 5659.35f, 359.053f, 158.214f, 3.69933f);
						break;
					case 14295: // The Storm Peaks
						player->TeleportTo(571, 7527.14f, -1260.89f, 919.049f, 2.0696f);
						break;
					case 14300: // Icecrown
						player->TeleportTo(571, 7253.64f, 1644.78f, 433.68f, 4.83412f);
						break;
					// --- Dungeons - Kalimdor
					case 15005:// Blackfathom Deeps
						player->TeleportTo(1, 4248.72f, 744.35f, -24.67f, 1.34f);
						break;
					case 15010:// Caverns of Time
						player->TeleportTo(1, -8173.66f, -4746.36f, 33.84f, 4.94f);
						break;
					case 15015:// Dire Maul
						player->TeleportTo(1, -3960.95f, 1130.64f, 161.05f, 0.0f);
						break;
					case 15020:// Maraudon
						player->TeleportTo(1, -1431.33f, 2962.34f, 98.23f, 4.74f);
						break;
					case 15025:// Onyxia's Lair
						player->TeleportTo(1, -4707.44f, -3726.82f, 54.6723f, 3.8f);
						break;
					case 15030:// Ragefire Chasm
						player->TeleportTo(1, 1814.47f, -4419.46f, -18.78f, 5.28f);
						break;
					case 15035:// Razorfen Downs
						player->TeleportTo(1, -4657.88f, -2525.59f, 81.4f, 4.16f);
						break;
					case 15040:// Razorfen Kraul
						player->TeleportTo(1, -4463.6f, -1664.53f, 82.26f, 0.85f);
						break;
					case 15045:// Ruins of Ahn'Qiraj
						player->TeleportTo(1, -8413.33f, 1501.27f, 29.64f, 2.61f);
						break;
					case 15050:// Temple of Ahn'Qiraj
						player->TeleportTo(1, -8245.837891f, 1983.736206f, 129.071686f, 0.936195f);
						break;
					case 15055:// Wailing Caverns
						player->TeleportTo(1, -722.53f, -2226.30f, 16.94f, 2.71f);
						break;
					case 15060:// Zul'Farrak
						player->TeleportTo(1, -6801.9f, -2890.22f, 8.88f, 6.25f);
						break;
					// --- Dungeon - Oestliche Koenigreiche
					case 15065:// Blackrock Depths
						player->TeleportTo(0, -7180.57f, -920.04f, 165.49f, 5.02f);
						break;
					case 15070:// Blackrock Spire
						player->TeleportTo(0, -7526.77f, -1225.64f, 285.73f, 5.31f);
						break;
					case 15075:// Blackwing Lair
						player->TeleportTo(469, -7672.61f, -1107.21f, 396.65f, 3.75f);
						break;
					case 15080:// Deadmines
						player->TeleportTo(0, -11208.2f, 1675.92f, 24.57f, 1.48f);
						break;
					case 15085:// Gnomeregan
						player->TeleportTo(0, -5163.32f, 927.18f, 257.158f, 1.44f);
						break;
					case 15090:// Insel von Quel'Danas
						player->TeleportTo(530, 13010.00f, -6907.64f, 9.58f, 4.58f);
						break;
					case 15095:// Karazhan
						player->TeleportTo(0, -11119.6f, -2011.42f, 47.09f, 0.65f);
						break;
					case 15100:// Molten Core
						player->TeleportTo(230, 1114.85f, -457.76f, -102.81f, 3.83f);
						break;
					case 15105:// Scarlet Monastery
						player->TeleportTo(0, 2843.89f, -693.74f, 139.32f, 5.11f);
						break;
					case 15110:// Scholomance
						player->TeleportTo(0, 1273.06f, -2574.01f, 92.66f, 2.06f);
						break;
					case 15115:// Shadowfang Keep
						player->TeleportTo(0, -239.54f, 1550.8f, 76.89f, 1.18f);
						break;
					case 15120:// Stratholme
						player->TeleportTo(0, 3370.76f, -3343.63f, 142.26f, 5.23f);
						break;
					case 15125:// Sunken Temple
						player->TeleportTo(0, -10346.92f, -3851.90f, -43.41f, 6.09f);
						break;
					case 15130:// The Stockade
						player->TeleportTo(0, -8766.89f, 844.6f, 88.43f, 0.69f);
						break;
					case 15135:// Uldaman
						player->TeleportTo(0, -6070.72f, -2955.33f, 209.78f, 0.05f);
						break;
					case 15140:// Zul'Aman
						player->TeleportTo(530, 6851.09f, -7979.71f, 183.54f, 4.72f);
						break;
					case 15145:// Zul'Gurub
						player->TeleportTo(0, -11916.4f, -1216.23f, 92.28f, 4.75f);
						break;
					// --- Dungeon - Scherbenwelt
					case 15150:// Auchindoun
						player->TeleportTo(530, -3322.92f, 4931.02f, -100.56f, 1.86f);
						break;
					case 15155:// Black Temple
						player->TeleportTo(530, -3649.1f, 317.33f, 35.19f, 2.97f);
						break;
					case 15160:// Coilfang Reservoir
						player->TeleportTo(530, 721.08f, 6846.77f, -68.75f, 0.34f);
						break;
					case 15165:// Gruul's Lair
						player->TeleportTo(530, 3539.01f, 5082.36f, 1.69f, 0.0f);
						break;
					case 15170:// Hellfire Citadel
						player->TeleportTo(530, -292.71f, 3146.77f, 31.60f, 2.05f);
						break;
					case 15175:// Tempest Keep
						player->TeleportTo(530, 3087.62f, 1376.27f, 184.8f, 4.63f);
						break;
					// --- Dungeon - Northrend
					case 15180:// Ahn'Kahet
						player->TeleportTo(571, 3646.76f, 2045.17f, 1.79f, 4.37f);
						break;
					case 15185:// Azjol-Nerub
						player->TeleportTo(571, 3675.43f, 2169.00f, 35.90f, 2.29f);
						break;
					case 15190:// Drak'Tharon Keep
						player->TeleportTo(571, 4450.86f, -2045.25f, 162.83f, 0.00f);
						break;
					case 15195:// Gun'Drak
						player->TeleportTo(571, 6937.54f, -4455.98f, 450.68f, 1.00f);
						break;
					case 15200:// Icecrown Citadel
						player->TeleportTo(571, 6139.24f, 2233.72f, 510.79f, 3.56f);
						break;
					case 15205:// Naxxramas
						player->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);
						break;
					case 15210:// The Nexus
						player->TeleportTo(571, 3789.95f, 6961.48f, 104.23f, 0.28f);
						break;
					case 15215:// The Obsidian Sanctum
						player->TeleportTo(571, 3625.78f, 280.4f, -120.14f, 3.25f);
						break;
					case 15220:// Ulduar
						player->TeleportTo(571, 1219.72f, -4865.28f, 41.25f, 0.31f);
						break;
					case 15225:// Utgarde Keep
						player->TeleportTo(571, 1245.69f, -4856.59f, 216.86f, 3.45f);
						break;
					case 15230:// Utgarde Pinnacle
						player->TeleportTo(571, 8976.24f, -1281.33f, 1059.01f, 0.58f);
						break;
					case 15235:// Violet Hold
						player->TeleportTo(571, 5679.82f, 486.80f, 652.40f, 4.08f);
						break;
					// --- Raids
					case 16005:// Zul'Gurub
						player->TeleportTo(0, -11916.7f, -1215.72f, 92.289f, 4.72454f);
						break;
					case 16010:// Molten Core
						player->TeleportTo(230, 1126.64f, -459.94f, -102.535f, 3.46095f);
						break;
					case 16015:// Blackwing Lair
						player->TeleportTo(229, 164.789f, -475.305f, 116.842f, 0.022714f);
						break;
					case 16020:// Ahn'Qiraj Ruins
						player->TeleportTo(1, -8409.82f, 1499.06f, 27.7179f, 2.51868f);
						break;
					case 16025:// Ahn'Qiraj Temple
						player->TeleportTo(1, -8240.09f, 1991.32f, 129.072f, 0.941603f);
						break;
					case 16030:// Karazhan
						player->TeleportTo(0, -11118.9f, -2010.33f, 47.0819f, 0.649895f);
						break;
					case 16035:// Gruul's Lair
						player->TeleportTo(530, 3530.06f, 5104.08f, 3.50861f, 5.51117f);
						break;
					case 16040:// Magtheridon's Lair
						player->TeleportTo(530, -312.7f, 3087.26f, -116.52f, 5.19026f);
						break;
					case 16045:// Zul'Aman
						player->TeleportTo(530, 6851.78f, -7972.57f, 179.242f, 4.64691f);
						break;
					case 16050:// Serpentshrine Cavern
						player->TeleportTo(530, 820.025f, 6864.93f, -66.7556f, 6.28127f);
						break;
					case 16055:// Tempest Keep: The Eye
						player->TeleportTo(530, 3088.49f, 1381.57f, 184.863f, 4.61973f);
						break;
					case 16060:// Hyjal
						player->TeleportTo(1, -8177.89f, -4181.23f, -167.552f, 0.913338f);
						break;
					case 16065:// Black Temple
						player->TeleportTo(530, -3649.92f, 317.469f, 35.2827f, 2.94285f);
						break;
					case 16070:// Sunwell Plateau
						player->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);
						break;
					case 16075:// Naxxarams
						player->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);
						break;
					case 16080:// Obsidian Sanctum
						player->TeleportTo(571, 3479.66f, 264.625f, -120.144f, 0.097f);
						break;
					case 16085:// Ruby Sanctum
						player->TeleportTo(571, 3479.66f, 264.625f, -120.144f, 0.097f);
						break;
					case 16090:// Vault of Archavon
						player->TeleportTo(571, 5453.72f, 2840.79f, 421.28f, 0.0f);
						break;
					case 16095:// The Eye of Eternity (+Dungeon)
						player->TeleportTo(571, 3781.81f, 6953.65f, 104.82f, 0.467432f);
						break;
					case 16100:// Uldar (+Dungeon)
						player->TeleportTo(571, 9049.37f, -1282.35f, 1060.19f, 5.8395f);
						break;
					case 16105:// Icecrown Citadel
						player->TeleportTo(571, 5873.82f, 2110.98f, 636.011f, 3.5523f);
						break;
					case 16110:// Trial of the Crusader (+Dungeon)
						player->TeleportTo(571, 8515.89f, 629.25f, 547.396f, 1.5747f);
						break;
					case 16115:// Onyxia's Liar
						player->TeleportTo(1, -4708.27f, -3727.64f, 54.5589f, 3.72786f);
						break;
					// --- PVP-Gebiete
					case 17010: // Gurubashi Arena
						player->TeleportTo(0, -13277.4f, 127.372f, 26.1418f, 1.11878f);
						break;
					case 17015: // Circle of Blood Arena
						player->TeleportTo(530, 2839.44f, 5930.17f, 11.1002f, 3.16284f);
						break;
					case 17020: // The Ring of Trials
						player->TeleportTo(530, -1999.94f, 6581.71f, 11.32f, 2.36528f);
						break;
					case 17025: // Wintergrasp
						player->TeleportTo(571, 4760.7f, 2143.7f, 423, 1.13f);
						break;
					// --- Sonstiges
					case 19010:// Allianz Playertreff
						player->TeleportTo(0, 2918.74f, -1437.36f, 150.782f, 4.28161f);
						break;
					case 19015:// Horde Playertreff
						player->TeleportTo(1, 7447.3f, -1693.77f, 194.899f, 2.43468f);
						break;
					case 19020:// Home
						player->CastSpell(player, 8690, true);
						break;
					case 19025:// GM-Insel
						player->TeleportTo(1, 16226.2f, 16257.0f, 13.2022f, 1.65007f);
						break;
					default:
						break;
				}//switch sender
				return true;
			}//if
			return false;
		}//if sender
		return false;
	}//OnGossipSelect
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Teleport()
{
	new NPC_Teleport();
};