/*
NPC_Upgrader
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96003;
SET @CREATURTEMPLATE_NAME = "Upgrader NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Upgrader', 0);
*/

// ******************************************************************************
// class
// ******************************************************************************
class NPC_Upgrader : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Upgrader() : CreatureScript("NPC_Upgrader") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\Achievement_Level_80:30:30:-18|t Maximal Level|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\Achievement_BG_winAB_5cap-Square:30:30:-18|t Fertigkeiten Maximum|r", GOSSIP_SENDER_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\INV_Inscription_Tradeskill01:30:30:-18|t Skills Maximum|r", GOSSIP_SENDER_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\Ability_Mount_RidingHorse:30:30:-18|t Reiten lernen|r", GOSSIP_SENDER_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\INV_Ore_Gold_01:30:30:-18|t Gib mir Gold|r", GOSSIP_SENDER_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\Ability_DualWieldSpecialization:30:30:-18|t Lern mir die Duale Talentspezialisierung|r", GOSSIP_SENDER_MAIN, 150);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\Achievement_BG_tophealer_AV:30:30:-18|t Setze meine Faehigkeiten zurueck|r", GOSSIP_SENDER_MAIN, 155);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\achievement_general:30:30:-18|t Ich moechte mich umbenenen|r", GOSSIP_SENDER_MAIN, 160);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\achievement_general:30:30:-18|t Ich moechte mich umstylen|r", GOSSIP_SENDER_MAIN, 165);
		if (player->getClass() == CLASS_HUNTER || player->GetSession()->GetSecurity() >= 2)
		{
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff004000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t Skills meines Jaegertier zuruecksetzen|r", GOSSIP_SENDER_MAIN, 1305);
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff004000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t Mein Jaegertier umbenennen|r", GOSSIP_SENDER_MAIN, 1310);
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff004000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t Gib mir 4 Stallplaetze|r", GOSSIP_SENDER_MAIN, 1315);
		}
		if (player->getClass() == CLASS_WARLOCK || player->GetSession()->GetSecurity() >= 2)
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff000040|TInterface\\icons\\INV_SpiritShard_01:30:30:-18|t Gib mir Seelensteine|r", GOSSIP_SENDER_MAIN, 1905);
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
				creature->Say("Du befindest Dich in einem Kampf. Da kann ich nix fuer Dich tun !", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			// --- Maximal Level
			if (action == 105)
			{
				int16 levelsoll = 80;//anpassbar, je nach expansion. Hier: WoltK
				int16 levelist = player->getLevel();
				int16 leveldiff = levelsoll - levelist;
				if (leveldiff <= 0)
				{
					creature->Say("Du bist bereits auf dem Maximal Level. Da kann ich Dir damit nicht weiterhelfen !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->GiveLevel(leveldiff);
				creature->Say("Du bist nun auf dem Maximal Level.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Fertigkeiten Maximum
			if (action == 110)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				// --- Dual Spec
				player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
				player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());
				// --- wenn Klasse: Krieger
				if (player->getClass() == CLASS_WARRIOR)
				{
					// -- basis
					player->LearnSpell(7384, false);
					player->LearnSpell(47436, false);
					player->LearnSpell(47450, false);
					player->LearnSpell(11578, false);
					player->LearnSpell(47465, false);
					player->LearnSpell(47502, false);
					player->LearnSpell(34428, false);
					player->LearnSpell(1715, false);
					player->LearnSpell(2687, false);
					player->LearnSpell(71, false);
					player->LearnSpell(7386, false);
					player->LearnSpell(355, false);
					player->LearnSpell(72, false);
					player->LearnSpell(47437, false);
					player->LearnSpell(57823, false);
					player->LearnSpell(694, false);
					player->LearnSpell(2565, false);
					player->LearnSpell(676, false);
					player->LearnSpell(47520, false);
					player->LearnSpell(20230, false);
					player->LearnSpell(12678, false);
					player->LearnSpell(47471, false);
					player->LearnSpell(1161, false);
					player->LearnSpell(871, false);
					player->LearnSpell(2458, false);
					player->LearnSpell(20252, false);
					player->LearnSpell(47475, false);
					player->LearnSpell(18499, false);
					player->LearnSpell(1680, false);
					player->LearnSpell(6552, false);
					player->LearnSpell(47488, false);
					player->LearnSpell(1719, false);
					player->LearnSpell(23920, false);
					player->LearnSpell(47440, false);
					player->LearnSpell(3411, false);
					player->LearnSpell(64382, false);
					player->LearnSpell(55694, false);
					player->LearnSpell(57755, false);
					player->LearnSpell(42459, false);
					player->LearnSpell(750, false);
					player->LearnSpell(5246, false);
					player->LearnSpell(3127, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(750, false);
					player->LearnSpell(196, false);
					player->LearnSpell(197, false);
					player->LearnSpell(198, false);
					player->LearnSpell(199, false);
					player->LearnSpell(200, false);
					player->LearnSpell(201, false);
					player->LearnSpell(202, false);
					player->LearnSpell(264, false);
					player->LearnSpell(5011, false);
					player->LearnSpell(266, false);
					player->LearnSpell(2567, false);
					// -- sonstige
					if (player->HasSpell(12294))
					{
						player->LearnSpell(47486, false);
					}
					if (player->HasSpell(20243))
					{
						player->LearnSpell(47498, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Paladin
				if (player->getClass() == CLASS_PALADIN)
				{
					// -- basis
					player->LearnSpell(3127, false);
					player->LearnSpell(19746, false);
					player->LearnSpell(19752, false);
					player->LearnSpell(750, false);
					player->LearnSpell(48942, false);
					player->LearnSpell(48782, false);
					player->LearnSpell(48932, false);
					player->LearnSpell(20271, false);
					player->LearnSpell(498, false);
					player->LearnSpell(10308, false);
					player->LearnSpell(1152, false);
					player->LearnSpell(10278, false);
					player->LearnSpell(48788, false);
					player->LearnSpell(53408, false);
					player->LearnSpell(48950, false);
					player->LearnSpell(48936, false);
					player->LearnSpell(31789, false);
					player->LearnSpell(62124, false);
					player->LearnSpell(54043, false);
					player->LearnSpell(25780, false);
					player->LearnSpell(1044, false);
					player->LearnSpell(20217, false);
					player->LearnSpell(48819, false);
					player->LearnSpell(48801, false);
					player->LearnSpell(48785, false);
					player->LearnSpell(5502, false);
					player->LearnSpell(20164, false);
					player->LearnSpell(10326, false);
					player->LearnSpell(1038, false);
					player->LearnSpell(53407, false);
					player->LearnSpell(48943, false);
					player->LearnSpell(20165, false);
					player->LearnSpell(48945, false);
					player->LearnSpell(642, false);
					player->LearnSpell(48947, false);
					player->LearnSpell(20166, false);
					player->LearnSpell(4987, false);
					player->LearnSpell(48806, false);
					player->LearnSpell(6940, false);
					player->LearnSpell(48817, false);
					player->LearnSpell(48934, false);
					player->LearnSpell(48938, false);
					player->LearnSpell(25898, false);
					player->LearnSpell(32223, false);
					player->LearnSpell(31884, false);
					player->LearnSpell(54428, false);
					player->LearnSpell(61411, false);
					player->LearnSpell(53601, false);
					player->LearnSpell(33388, false);
					player->LearnSpell(33391, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(750, false);
					player->LearnSpell(196, false);
					player->LearnSpell(197, false);
					player->LearnSpell(198, false);
					player->LearnSpell(199, false);
					player->LearnSpell(200, false);
					player->LearnSpell(201, false);
					player->LearnSpell(202, false);
					// -- sonstige
					if (player->HasSpell(20925))
					{
						player->LearnSpell(48952, false);
					}
					if (player->HasSpell(12294))
					{
						player->LearnSpell(48827, false);
					}
					if (player->HasSpell(20911))
					{
						player->LearnSpell(25899, false);
					}
					if (player->HasSpell(20473))
					{
						player->LearnSpell(48825, false);
					}
					if (player->GetTeam() == ALLIANCE)
					{
						player->LearnSpell(31801, false);
						player->LearnSpell(13819, false);
						player->LearnSpell(23214, false);
					}
					if (player->GetTeam() == HORDE)
					{
						player->LearnSpell(53736, false);
						player->LearnSpell(34769, false);
						player->LearnSpell(34767, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Jaeger
				if (player->getClass() == CLASS_HUNTER)
				{
					// -- basis
					player->LearnSpell(3043, false);
					player->LearnSpell(3127, false);
					player->LearnSpell(3045, false);
					player->LearnSpell(3034, false);
					player->LearnSpell(8737, false);
					player->LearnSpell(1494, false);
					player->LearnSpell(13163, false);
					player->LearnSpell(48996, false);
					player->LearnSpell(49001, false);
					player->LearnSpell(49045, false);
					player->LearnSpell(53338, false);
					player->LearnSpell(5116, false);
					player->LearnSpell(27044, false);
					player->LearnSpell(883, false);
					player->LearnSpell(2641, false);
					player->LearnSpell(6991, false);
					player->LearnSpell(982, false);
					player->LearnSpell(1515, false);
					player->LearnSpell(19883, false);
					player->LearnSpell(20736, false);
					player->LearnSpell(48990, false);
					player->LearnSpell(2974, false);
					player->LearnSpell(6197, false);
					player->LearnSpell(1002, false);
					player->LearnSpell(14327, false);
					player->LearnSpell(5118, false);
					player->LearnSpell(49056, false);
					player->LearnSpell(53339, false);
					player->LearnSpell(49048, false);
					player->LearnSpell(19884, false);
					player->LearnSpell(34074, false);
					player->LearnSpell(781, false);
					player->LearnSpell(14311, false);
					player->LearnSpell(1462, false);
					player->LearnSpell(19885, false);
					player->LearnSpell(19880, false);
					player->LearnSpell(13809, false);
					player->LearnSpell(13161, false);
					player->LearnSpell(5384, false);
					player->LearnSpell(1543, false);
					player->LearnSpell(19878, false);
					player->LearnSpell(49067, false);
					player->LearnSpell(3034, false);
					player->LearnSpell(13159, false);
					player->LearnSpell(19882, false);
					player->LearnSpell(58434, false);
					player->LearnSpell(49071, false);
					player->LearnSpell(49052, false);
					player->LearnSpell(19879, false);
					player->LearnSpell(19263, false);
					player->LearnSpell(19801, false);
					player->LearnSpell(34026, false);
					player->LearnSpell(34600, false);
					player->LearnSpell(34477, false);
					player->LearnSpell(61006, false);
					player->LearnSpell(61847, false);
					player->LearnSpell(53271, false);
					player->LearnSpell(60192, false);
					player->LearnSpell(62757, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(15590, false);
					player->LearnSpell(8737, false);
					player->LearnSpell(196, false);
					player->LearnSpell(197, false);
					player->LearnSpell(200, false);
					player->LearnSpell(201, false);
					player->LearnSpell(202, false);
					player->LearnSpell(264, false);
					player->LearnSpell(266, false);
					player->LearnSpell(5011, false);
					player->LearnSpell(42459, false);
					// -- sonstige
					if (player->HasSpell(19386))
					{
						player->LearnSpell(49012, false);
					}
					if (player->HasSpell(53301))
					{
						player->LearnSpell(60053, false);
					}
					if (player->HasSpell(19306))
					{
						player->LearnSpell(48999, false);
					}
					if (player->HasSpell(19434))
					{
						player->LearnSpell(49050, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Schurke
				if (player->getClass() == CLASS_ROGUE)
				{
					// -- basis
					player->LearnSpell(3127, false);
					player->LearnSpell(42459, false);
					player->LearnSpell(48668, false);
					player->LearnSpell(48638, false);
					player->LearnSpell(1784, false);
					player->LearnSpell(48657, false);
					player->LearnSpell(921, false);
					player->LearnSpell(1776, false);
					player->LearnSpell(26669, false);
					player->LearnSpell(51724, false);
					player->LearnSpell(6774, false);
					player->LearnSpell(11305, false);
					player->LearnSpell(1766, false);
					player->LearnSpell(48676, false);
					player->LearnSpell(48659, false);
					player->LearnSpell(1804, false);
					player->LearnSpell(8647, false);
					player->LearnSpell(48691, false);
					player->LearnSpell(51722, false);
					player->LearnSpell(48672, false);
					player->LearnSpell(1725, false);
					player->LearnSpell(26889, false);
					player->LearnSpell(2836, false);
					player->LearnSpell(1833, false);
					player->LearnSpell(1842, false);
					player->LearnSpell(8643, false);
					player->LearnSpell(2094, false);
					player->LearnSpell(1860, false);
					player->LearnSpell(57993, false);
					player->LearnSpell(48674, false);
					player->LearnSpell(31224, false);
					player->LearnSpell(5938, false);
					player->LearnSpell(57934, false);
					player->LearnSpell(51723, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(196, false);
					player->LearnSpell(198, false);
					player->LearnSpell(201, false);
					player->LearnSpell(1180, false);
					player->LearnSpell(2567, false);
					player->LearnSpell(264, false);
					player->LearnSpell(266, false);
					player->LearnSpell(5011, false);
					player->LearnSpell(15590, false);
					// -- sonstige
					if (player->HasSpell(16511))
					{
						player->LearnSpell(48660, false);
					}
					if (player->HasSpell(1329))
					{
						player->LearnSpell(48666, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Priester
				if (player->getClass() == CLASS_PRIEST)
				{
					// -- basis
					player->LearnSpell(528, false);
					player->LearnSpell(2053, false);
					player->LearnSpell(48161, false);
					player->LearnSpell(48123, false);
					player->LearnSpell(48125, false);
					player->LearnSpell(48066, false);
					player->LearnSpell(586, false);
					player->LearnSpell(48068, false);
					player->LearnSpell(48127, false);
					player->LearnSpell(48171, false);
					player->LearnSpell(48168, false);
					player->LearnSpell(10890, false);
					player->LearnSpell(6064, false);
					player->LearnSpell(988, false);
					player->LearnSpell(48300, false);
					player->LearnSpell(6346, false);
					player->LearnSpell(48071, false);
					player->LearnSpell(48135, false);
					player->LearnSpell(48078, false);
					player->LearnSpell(453, false);
					player->LearnSpell(10955, false);
					player->LearnSpell(10909, false);
					player->LearnSpell(8129, false);
					player->LearnSpell(48073, false);
					player->LearnSpell(605, false);
					player->LearnSpell(48072, false);
					player->LearnSpell(48169, false);
					player->LearnSpell(552, false);
					player->LearnSpell(1706, false);
					player->LearnSpell(48063, false);
					player->LearnSpell(48162, false);
					player->LearnSpell(48170, false);
					player->LearnSpell(48074, false);
					player->LearnSpell(48158, false);
					player->LearnSpell(48120, false);
					player->LearnSpell(34433, false);
					player->LearnSpell(48113, false);
					player->LearnSpell(32375, false);
					player->LearnSpell(64843, false);
					player->LearnSpell(64901, false);
					player->LearnSpell(53023, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(196, false);
					player->LearnSpell(198, false);
					player->LearnSpell(227, false);
					player->LearnSpell(1180, false);
					// -- sonstige
					if (player->HasSpell(34914))
					{
						player->LearnSpell(48160, false);
					}
					if (player->HasSpell(47540))
					{
						player->LearnSpell(53007, false);
					}
					if (player->HasSpell(724))
					{
						player->LearnSpell(48087, false);
					}
					if (player->HasSpell(19236))
					{
						player->LearnSpell(48173, false);
					}
					if (player->HasSpell(34861))
					{
						player->LearnSpell(48089, false);
					}
					if (player->HasSpell(15407))
					{
						player->LearnSpell(48156, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Todesritter
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					// -- basis
					player->LearnSpell(3127, false);
					player->LearnSpell(50842, false);
					player->LearnSpell(49941, false);
					player->LearnSpell(49930, false);
					player->LearnSpell(47476, false);
					player->LearnSpell(45529, false);
					player->LearnSpell(3714, false);
					player->LearnSpell(56222, false);
					player->LearnSpell(48743, false);
					player->LearnSpell(48263, false);
					player->LearnSpell(49909, false);
					player->LearnSpell(47528, false);
					player->LearnSpell(45524, false);
					player->LearnSpell(48792, false);
					player->LearnSpell(57623, false);
					player->LearnSpell(56815, false);
					player->LearnSpell(47568, false);
					player->LearnSpell(49895, false);
					player->LearnSpell(50977, false);
					player->LearnSpell(49576, false);
					player->LearnSpell(49921, false);
					player->LearnSpell(46584, false);
					player->LearnSpell(49938, false);
					player->LearnSpell(48707, false);
					player->LearnSpell(48265, false);
					player->LearnSpell(61999, false);
					player->LearnSpell(42650, false);
					player->LearnSpell(53428, false);
					player->LearnSpell(53331, false);
					player->LearnSpell(54447, false);
					player->LearnSpell(53342, false);
					player->LearnSpell(54446, false);
					player->LearnSpell(53323, false);
					player->LearnSpell(53344, false);
					player->LearnSpell(70164, false);
					player->LearnSpell(62158, false);
					player->LearnSpell(33391, false);
					player->LearnSpell(48778, false);
					player->LearnSpell(51425, false);
					player->LearnSpell(49924, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(750, false);
					player->LearnSpell(196, false);
					player->LearnSpell(197, false);
					player->LearnSpell(198, false);
					player->LearnSpell(199, false);
					player->LearnSpell(200, false);
					player->LearnSpell(201, false);
					player->LearnSpell(202, false);
					// -- sonstige
					if (player->HasSpell(55050))
					{
						player->LearnSpell(55262, false);
					}
					if (player->HasSpell(49143))
					{
						player->LearnSpell(55268, false);
					}
					if (player->HasSpell(49184))
					{
						player->LearnSpell(51411, false);
					}
					if (player->HasSpell(55090))
					{
						player->LearnSpell(55271, false);
					}
					if (player->HasSpell(49158))
					{
						player->LearnSpell(51328, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Schamane
				if (player->getClass() == CLASS_SHAMAN)
				{
					// -- basis
					player->LearnSpell(2062, false);
					player->LearnSpell(8737, false);
					player->LearnSpell(49273, false);
					player->LearnSpell(49238, false);
					player->LearnSpell(10399, false);
					player->LearnSpell(49231, false);
					player->LearnSpell(58753, false);
					player->LearnSpell(2484, false);
					player->LearnSpell(49281, false);
					player->LearnSpell(58582, false);
					player->LearnSpell(49233, false);
					player->LearnSpell(58790, false);
					player->LearnSpell(58704, false);
					player->LearnSpell(58643, false);
					player->LearnSpell(49277, false);
					player->LearnSpell(61657, false);
					player->LearnSpell(8012, false);
					player->LearnSpell(526, false);
					player->LearnSpell(2645, false);
					player->LearnSpell(57994, false);
					player->LearnSpell(8143, false);
					player->LearnSpell(49236, false);
					player->LearnSpell(58796, false);
					player->LearnSpell(58757, false);
					player->LearnSpell(49276, false);
					player->LearnSpell(57960, false);
					player->LearnSpell(131, false);
					player->LearnSpell(58745, false);
					player->LearnSpell(6196, false);
					player->LearnSpell(58734, false);
					player->LearnSpell(58774, false);
					player->LearnSpell(58739, false);
					player->LearnSpell(58656, false);
					player->LearnSpell(546, false);
					player->LearnSpell(556, false);
					player->LearnSpell(66842, false);
					player->LearnSpell(51994, false);
					player->LearnSpell(8177, false);
					player->LearnSpell(58749, false);
					player->LearnSpell(20608, false);
					player->LearnSpell(36936, false);
					player->LearnSpell(36936, false);
					player->LearnSpell(58804, false);
					player->LearnSpell(49271, false);
					player->LearnSpell(8512, false);
					player->LearnSpell(6495, false);
					player->LearnSpell(8170, false);
					player->LearnSpell(66843, false);
					player->LearnSpell(55459, false);
					player->LearnSpell(66844, false);
					player->LearnSpell(3738, false);
					player->LearnSpell(2894, false);
					player->LearnSpell(60043, false);
					player->LearnSpell(51514, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(8737, false);
					player->LearnSpell(196, false);
					player->LearnSpell(197, false);
					player->LearnSpell(198, false);
					player->LearnSpell(199, false);
					player->LearnSpell(227, false);
					player->LearnSpell(15590, false);
					// -- sonstige
					if (player->GetTeam() == ALLIANCE)
					{
						player->LearnSpell(32182, false);
					}
					if (player->GetTeam() == HORDE)
					{
						player->LearnSpell(2825, false);
					}
					if (player->HasSpell(61295))
					{
						player->LearnSpell(61301, false);
					}
					if (player->HasSpell(974))
					{
						player->LearnSpell(49284, false);
					}
					if (player->HasSpell(30706))
					{
						player->LearnSpell(57722, false);
					}
					if (player->HasSpell(51490))
					{
						player->LearnSpell(59159, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Magier
				if (player->getClass() == CLASS_MAGE)
				{
					// -- basis
					player->LearnSpell(42921, false);
					player->LearnSpell(42842, false);
					player->LearnSpell(42995, false);
					player->LearnSpell(42833, false);
					player->LearnSpell(27090, false);
					player->LearnSpell(33717, false);
					player->LearnSpell(42873, false);
					player->LearnSpell(42846, false);
					player->LearnSpell(12826, false);
					player->LearnSpell(28271, false);
					player->LearnSpell(61780, false);
					player->LearnSpell(61721, false);
					player->LearnSpell(28272, false);
					player->LearnSpell(42917, false);
					player->LearnSpell(43015, false);
					player->LearnSpell(130, false);
					player->LearnSpell(42926, false);
					player->LearnSpell(43017, false);
					player->LearnSpell(475, false);
					player->LearnSpell(1953, false);
					player->LearnSpell(42940, false);
					player->LearnSpell(12051, false);
					player->LearnSpell(43010, false);
					player->LearnSpell(43020, false);
					player->LearnSpell(43012, false);
					player->LearnSpell(42859, false);
					player->LearnSpell(2139, false);
					player->LearnSpell(42931, false);
					player->LearnSpell(42985, false);
					player->LearnSpell(43008, false);
					player->LearnSpell(45438, false);
					player->LearnSpell(43024, false);
					player->LearnSpell(43002, false);
					player->LearnSpell(43046, false);
					player->LearnSpell(42897, false);
					player->LearnSpell(42914, false);
					player->LearnSpell(66, false);
					player->LearnSpell(58659, false);
					player->LearnSpell(30449, false);
					player->LearnSpell(42956, false);
					player->LearnSpell(47610, false);
					player->LearnSpell(61316, false);
					player->LearnSpell(61024, false);
					player->LearnSpell(55342, false);
					player->LearnSpell(53142, false);
					player->LearnSpell(7301, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(201, false);
					player->LearnSpell(196, false);
					player->LearnSpell(227, false);
					player->LearnSpell(1180, false);
					// -- sonstige
					if (player->GetTeam() == ALLIANCE)
					{
						player->LearnSpell(32271, false);
						player->LearnSpell(49359, false);
						player->LearnSpell(3565, false);
						player->LearnSpell(33690, false);
						player->LearnSpell(3562, false);
						player->LearnSpell(3561, false);
						player->LearnSpell(11419, false);
						player->LearnSpell(32266, false);
						player->LearnSpell(11416, false);
						player->LearnSpell(33691, false);
						player->LearnSpell(49360, false);
					}
					if (player->GetTeam() == HORDE)
					{
						player->LearnSpell(3567, false);
						player->LearnSpell(35715, false);
						player->LearnSpell(3566, false);
						player->LearnSpell(49358, false);
						player->LearnSpell(32272, false);
						player->LearnSpell(3563, false);
						player->LearnSpell(11417, false);
						player->LearnSpell(35717, false);
						player->LearnSpell(32267, false);
						player->LearnSpell(49361, false);
						player->LearnSpell(11420, false);
						player->LearnSpell(11418, false);
					}
					if (player->HasSpell(11366))
					{
						player->LearnSpell(42891, false);
					}
					if (player->HasSpell(11426))
					{
						player->LearnSpell(43039, false);
					}
					if (player->HasSpell(44457))
					{
						player->LearnSpell(55360, false);
					}
					if (player->HasSpell(31661))
					{
						player->LearnSpell(42950, false);
					}
					if (player->HasSpell(11113))
					{
						player->LearnSpell(42945, false);
					}
					if (player->HasSpell(44425))
					{
						player->LearnSpell(44781, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Hexenmeister
				if (player->getClass() == CLASS_WARLOCK)
				{
					// -- basis
					player->LearnSpell(696, false);
					player->LearnSpell(47811, false);
					player->LearnSpell(47809, false);
					player->LearnSpell(688, false);
					player->LearnSpell(47813, false);
					player->LearnSpell(50511, false);
					player->LearnSpell(57946, false);
					player->LearnSpell(47864, false);
					player->LearnSpell(6215, false);
					player->LearnSpell(47878, false);
					player->LearnSpell(47855, false);
					player->LearnSpell(697, false);
					player->LearnSpell(47856, false);
					player->LearnSpell(47857, false);
					player->LearnSpell(5697, false);
					player->LearnSpell(47884, false);
					player->LearnSpell(47815, false);
					player->LearnSpell(47889, false);
					player->LearnSpell(47820, false);
					player->LearnSpell(698, false);
					player->LearnSpell(712, false);
					player->LearnSpell(126, false);
					player->LearnSpell(5138, false);
					player->LearnSpell(5500, false);
					player->LearnSpell(11719, false);
					player->LearnSpell(132, false);
					player->LearnSpell(60220, false);
					player->LearnSpell(18647, false);
					player->LearnSpell(61191, false);
					player->LearnSpell(47823, false);
					player->LearnSpell(691, false);
					player->LearnSpell(47865, false);
					player->LearnSpell(47891, false);
					player->LearnSpell(47888, false);
					player->LearnSpell(17928, false);
					player->LearnSpell(47860, false);
					player->LearnSpell(47825, false);
					player->LearnSpell(1122, false);
					player->LearnSpell(47867, false);
					player->LearnSpell(18540, false);
					player->LearnSpell(47893, false);
					player->LearnSpell(47838, false);
					player->LearnSpell(29858, false);
					player->LearnSpell(58887, false);
					player->LearnSpell(47836, false);
					player->LearnSpell(61290, false);
					player->LearnSpell(48018, false);
					player->LearnSpell(48020, false);
					player->LearnSpell(33388, false);
					player->LearnSpell(33391, false);
					player->LearnSpell(23161, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(196, false);
					player->LearnSpell(227, false);
					player->LearnSpell(1180, false);
					// -- sonstige
					if (player->HasSpell(17877))
					{
						player->LearnSpell(47827, false);
					}
					if (player->HasSpell(30283))
					{
						player->LearnSpell(47847, false);
					}
					if (player->HasSpell(30108))
					{
						player->LearnSpell(47843, false);
					}
					if (player->HasSpell(50796))
					{
						player->LearnSpell(59172, false);
					}
					if (player->HasSpell(48181))
					{
						player->LearnSpell(59164, false);
					}
					if (player->HasSpell(18220))
					{
						player->LearnSpell(59092, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Moench
				if (player->getClass() == 10)
				{
					creature->Yell("Deine Klasse unterstuetze ich z.Zt. noch nicht !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Druide
				if (player->getClass() == CLASS_DRUID)
				{
					// -- basis
					player->LearnSpell(48378, false);
					player->LearnSpell(48469, false);
					player->LearnSpell(48461, false);
					player->LearnSpell(48463, false);
					player->LearnSpell(48441, false);
					player->LearnSpell(53307, false);
					player->LearnSpell(53308, false);
					player->LearnSpell(5487, false);
					player->LearnSpell(48560, false);
					player->LearnSpell(6795, false);
					player->LearnSpell(48480, false);
					player->LearnSpell(53312, false);
					player->LearnSpell(18960, false);
					player->LearnSpell(5229, false);
					player->LearnSpell(48443, false);
					player->LearnSpell(50763, false);
					player->LearnSpell(8983, false);
					player->LearnSpell(8946, false);
					player->LearnSpell(1066, false);
					player->LearnSpell(48562, false);
					player->LearnSpell(783, false);
					player->LearnSpell(770, false);
					player->LearnSpell(16857, false);
					player->LearnSpell(18658, false);
					player->LearnSpell(768, false);
					player->LearnSpell(1082, false);
					player->LearnSpell(16979, false);
					player->LearnSpell(49376, false);
					player->LearnSpell(5215, false);
					player->LearnSpell(48477, false);
					player->LearnSpell(49800, false);
					player->LearnSpell(48465, false);
					player->LearnSpell(48572, false);
					player->LearnSpell(26995, false);
					player->LearnSpell(48574, false);
					player->LearnSpell(2782, false);
					player->LearnSpell(50213, false);
					player->LearnSpell(2893, false);
					player->LearnSpell(33357, false);
					player->LearnSpell(5209, false);
					player->LearnSpell(48575, false);
					player->LearnSpell(48447, false);
					player->LearnSpell(48577, false);
					player->LearnSpell(48579, false);
					player->LearnSpell(5225, false);
					player->LearnSpell(22842, false);
					player->LearnSpell(49803, false);
					player->LearnSpell(9634, false);
					player->LearnSpell(20719, false);
					player->LearnSpell(48467, false);
					player->LearnSpell(29166, false);
					player->LearnSpell(62600, false);
					player->LearnSpell(22812, false);
					player->LearnSpell(48470, false);
					player->LearnSpell(48564, false);
					player->LearnSpell(48566, false);
					player->LearnSpell(33943, false);
					player->LearnSpell(49802, false);
					player->LearnSpell(48451, false);
					player->LearnSpell(48568, false);
					player->LearnSpell(33786, false);
					player->LearnSpell(40120, false);
					player->LearnSpell(62078, false);
					player->LearnSpell(52610, false);
					player->LearnSpell(50464, false);
					player->LearnSpell(48570, false);
					player->LearnSpell(34093, false);
					player->LearnSpell(33392, false);
					player->LearnSpell(54197, false);
					// -- waffen
					player->LearnSpell(198, false);
					player->LearnSpell(199, false);
					player->LearnSpell(200, false);
					player->LearnSpell(227, false);
					// -- sonstige
					if (player->HasSpell(50516))
					{
						player->LearnSpell(61384, false);
					}
					if (player->HasSpell(48505))
					{
						player->LearnSpell(53201, false);
					}
					if (player->HasSpell(48438))
					{
						player->LearnSpell(53251, false);
					}
					if (player->HasSpell(5570))
					{
						player->LearnSpell(48468, false);
					}
					creature->Say("Ich habe Dir die maximalen Fertigkeiten Deiner Klasse verpasst.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}//class
				// --- wenn Klasse: Daemonenjaeger
				if (player->getClass() == 12)
				{
					creature->Yell("Deine Klasse unterstuetze ich z.Zt. noch nicht !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				return false;
			}
			// --- max skills
			if (action == 115)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->UpdateSkillsToMaxSkillsForLevel();
				creature->Say("Ich habe Deine Skills auf das Maximum gesetzt.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- reiten
			if (action == 120)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->LearnSpell(33388, false);//Unerfahrener Reiter
				player->LearnSpell(33391, false);//Geuebtes Reiten
				player->LearnSpell(34090, false);//Erfahrenes Reiten
				player->LearnSpell(34091, false);//Gekonntes Reiten
				player->LearnSpell(90265, false);//Meisterhaftes Reiten
				player->LearnSpell(90267, false);//Fluglizenz
				player->LearnSpell(54197, false);//Kaltwetterflug
				//player->LearnSpell(191645, false);//Pfadfinder von Draenor (ab 6.x)
				//player->LearnSpell(115913, false);//Weissheit der vier Winde (ab 6.x)
				creature->Say("Ich habe Deine Reitfertigkeiten auf das Maximum gesetzt.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- gib mir gold
			if (action == 125)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				creature->CastSpell(player, 46642, false); // 5000 gold
				creature->Say("Ich habe Dir 5000 Gold gegeben. Ich hoffe Du gehst damit sparsam damit um.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Duale Specc
			if (action == 150)
			{
				if (player->GetSpecsCount() == 2)
				{
					creature->Say("Du hast bereits die Duale Talentspezialisierung !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
				player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());
				creature->Say("Ich habe Dir die Duale Talentspezialisierung gegeben", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Reset Skills
			if (action == 155)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->ResetTalents(true);
				player->SendTalentsInfoData(false);
				creature->Say("Deine Faehigkeiten wurden zurueckgesetzt.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- char umbenennen
			if (action == 160)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->SetAtLoginFlag(AT_LOGIN_RENAME);
				creature->Say("Du kannst Dich beim naechsten Login umbenennen.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- char umstylen
			if (action == 160)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
				creature->Say("Du kannst Dich beim naechsten Login umstylen.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- CLASS_WARLOCK: Gib mir Seelensteine
			if (action == 1905)
			{
				if (player->getClass() != CLASS_WARLOCK)
				{
					creature->Say("Du bist kein Hexenmeister. Daher kann ich Dir das nicht geben !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				creature->CastSpell(player, 24827, false); // Seelensteine
				creature->Say("Ich habe Dir einen Seelenstein gegeben", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- CLASS_HUNTER: Hunterpet reset
			if (action == 1305)
			{
				if (player->getClass() != CLASS_HUNTER)
				{
					creature->Say("Du bist kein Jaeger. Daher kann ich Dir nicht helfen !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				if (!player->GetPet())
				{
					creature->Say("Du hast kein Tier aktiv. Wie soll ich Dir da helfen !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->ResetPetTalents();
				player->SendTalentsInfoData(false);
				creature->Say("Ich habe die Talente deines Tieres zurueckgesetzt.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- CLASS_HUNTER: Hunterpet rename
			if (action == 1310)
			{
				if (player->getClass() != CLASS_HUNTER)
				{
					creature->Say("Du bist kein Jaeger. Daher kann ich Dir nicht helfen !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->CastSpell(player, 59385, true); //Certificate of Ownership Spell - no cast time
				creature->Say("Du kannst jetzt Dein Tier umbenennen.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- CLASS_HUNTER: 4 Stallplaetze
			if (action == 1315)
			{
				if (player->getClass() != CLASS_HUNTER)
				{
					creature->Say("Du bist kein Jaeger. Daher kann ich Dir nicht helfen !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				if (player->m_stableSlots >= 4)
				{
					creature->Say("Du hast bereits 4 Stallplaetze. Uebertreib es nicht !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->m_stableSlots = 4;
				creature->Say("Du hast nun 4 Stallplaetze zur Verfuegung", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			return false;
		}//if sender
		return false;
	}//OnGossipSelect
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Upgrader()
{
	new NPC_Upgrader();
};
