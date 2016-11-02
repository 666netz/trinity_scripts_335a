/*
NPC_Helper
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96000;
SET @CREATURTEMPLATE_NAME = "Helper NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 30076;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Helper', 0);
*/

// ******************************************************************************
// class
// ******************************************************************************
class NPC_Helper : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Helper() : CreatureScript("NPC_Helper") { }
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
	uint32 NPC_HELPER_DESPAWNAFTEREXIT = 1; //0=disabled / 1=emabled
	uint32 NPC_HELPER_SUMMON_CREATUREFOLLOW = 0; //0=disabled / 1=emabled
	uint32 NPC_HELPER_SUMMON_NPCTELEPORT = 96001;//muss vorhanden sein
	uint32 NPC_HELPER_SUMMON_NPCUPGRADER = 96002;//muss vorhanden sein
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Arcane_PortalShattrath:30:30:-18|t Teleportiere mich|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Nature_HealingTouch:30:30:-18|t Heile und Buffe mich|r", GOSSIP_SENDER_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Nature_RemoveDisease:30:30:-18|t Entferne Effekte von mir|r", GOSSIP_SENDER_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Holy_SummonChampion:30:30:-18|t Ruf mir weitere Helfer herbei|r", GOSSIP_SENDER_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_BG_winEOS_underXminutes:30:30:-18|t Helf mir mit Cheats|r", GOSSIP_SENDER_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_Dungeon_CoTStratholme_Heroic:30:30:-18|t Helf mir beim Leveln|r", GOSSIP_SENDER_MAIN, 130);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-GroupLoot-Pass-Down:30:30:-18|t auf Wiedersehen|r", GOSSIP_SENDER_MAIN, 999);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}
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
				if (NPC_HELPER_DESPAWNAFTEREXIT == 1)
					creature->DespawnOrUnsummon(1 * IN_MILLISECONDS);
				return true;
			}
			// --- zum Hauptmenu
			if (action == 997)
			{
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Hauptmenue (Option 1)
			if (action == 105)
			{
				ClearGossipMenuFor(player);
				if (player->getFaction() == ALLIANCE || player->GetSession()->GetSecurity() >= 2)
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_NightElf:30:30:-18|t Darnassus|r", GOSSIP_SENDER_MAIN, 105005);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Draenei:30:30:-18|t Die Exodar|r", GOSSIP_SENDER_MAIN, 105010);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_gnome:30:30:-18|t Eisenschmiede|r", GOSSIP_SENDER_MAIN, 105015);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff0000FF|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Human:30:30:-18|t Sturmwind|r", GOSSIP_SENDER_MAIN, 105020);
				}
				if (player->getFaction() == HORDE || player->GetSession()->GetSecurity() >= 2)
				{
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Orc:30:30:-18|t Orgrimmar|r", GOSSIP_SENDER_MAIN, 105025);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_BloodElf:30:30:-18|t Silbermond|r", GOSSIP_SENDER_MAIN, 105030);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_Tauren:30:30:-18|t Donnerfels|r", GOSSIP_SENDER_MAIN, 105035);
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Inv_Misc_Tournaments_Tabard_scourge:30:30:-18|t Unterstadt|r", GOSSIP_SENDER_MAIN, 105040);
				}
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Spell_Arcane_PortalShattrath:30:30:-18|t Shattrath|r", GOSSIP_SENDER_MAIN, 105045);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Spell_Arcane_PortalDalaran:30:30:-18|t Dalaran|r", GOSSIP_SENDER_MAIN, 105050);
				if (player->getClass() == CLASS_DEATH_KNIGHT || player->GetSession()->GetSecurity() >= 2)
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Spell_DeathKnight_AntiMagicZone:30:30:-18|t Acherus - Die Schwarze Festung|r", GOSSIP_SENDER_MAIN, 105055);
				if (player->GetSession()->GetSecurity() >= 2)
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff008000|TInterface\\icons\\Achievement_Zone_IsleOfQuelDanas:30:30:-18|t GM Insel|r", GOSSIP_SENDER_MAIN, 105060);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenue (Option 2)
			if (action == 110)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Nature_HealingTouch:30:30:-18|t Heile mich|r", GOSSIP_SENDER_MAIN, 110005);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Holy_HolyNova:30:30:-18|t Buffe mich|r", GOSSIP_SENDER_MAIN, 110010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Ability_Repair:30:30:-18|t Repariere meine Ausruestung|r", GOSSIP_SENDER_MAIN, 110015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenue (Option 3)
			if (action == 115)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Holy_ReviveChampion:30:30:-18|t Wiederbelebung entfernen|r", GOSSIP_SENDER_MAIN, 115005);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Holy_ConsumeMagic:30:30:-18|t Deserteur entfernen|r", GOSSIP_SENDER_MAIN, 115010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Ability_Creature_Cursed_02:30:30:-18|t Kampfbug entfernen|r", GOSSIP_SENDER_MAIN, 115015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenue (Option 4)
			if (action == 120)
			{
				ClearGossipMenuFor(player);
				if (NPC_HELPER_SUMMON_NPCTELEPORT > 0)
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Holy_SummonChampion:30:30:-18|t Ruf mir den Teleport-NPC|r", GOSSIP_SENDER_MAIN, 120005);
				if (NPC_HELPER_SUMMON_NPCUPGRADER > 0)
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Spell_Holy_SummonChampion:30:30:-18|t Ruf mir den Upgrader-NPC|r", GOSSIP_SENDER_MAIN, 120010);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenue (Option 5)
			if (action == 125)
			{
				ClearGossipMenuFor(player);
				if (!player->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_POWER))
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_BG_winEOS_underXminutes:30:30:-18|t Mach mich unverwundbar\n (God-Mode)|r", GOSSIP_SENDER_MAIN, 125005);
				else
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_BG_winEOS_underXminutes:30:30:-18|t Mach mich wieder verwundbar\n (God-Mode AUS)|r", GOSSIP_SENDER_MAIN, 125005);
				if (!player->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_CASTTIME))
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_BG_winEOS_underXminutes:30:30:-18|t Ich moechte Schneller Zaubern\n (Instant CastTime)|r", GOSSIP_SENDER_MAIN, 125010);
				else
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_BG_winEOS_underXminutes:30:30:-18|t Ich moechte normal schnell Zaubern\n (Instant CastTime AUS)|r", GOSSIP_SENDER_MAIN, 125010);
				if (!player->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_COOLDOWN))
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_BG_winEOS_underXminutes:30:30:-18|t Ich moechte oefters Zaubern\n (No Global Cooldowns)|r", GOSSIP_SENDER_MAIN, 125015);
				else
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\Achievement_BG_winEOS_underXminutes:30:30:-18|t Ich moechte normal oeft Zaubern\n (No Global Cooldowns AUS)|r", GOSSIP_SENDER_MAIN, 125015);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Hauptmenue (Option 6)
			if (action == 130)
			{
				ClearGossipMenuFor(player);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff404040|TInterface\\icons\\INV_Ore_Gold_01:30:30:-18|t Ich braeuchte was Gold|r", GOSSIP_SENDER_MAIN, 130005);
				AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenue|r", GOSSIP_SENDER_MAIN, 997);
				SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			// --- Submenu 1 (auswahl)
			if (action >= 105005 && action <= 105995)
			{
				creature->Say("Ich teleportiere Dich jetzt zu dem gewuenschten Ort.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				FN_wait(2000);
				switch (action)
				{
					// --- Hauptstaedte - Allianz
					case 105005: // Darnassus
						player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
						break;
					case 105010: // Exodar
						player->TeleportTo(530, -3954.20f, -11656.54f, -138.69f, 0.0f);
						break;
					case 105015: // Eisenschmiede
						player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
						break;
					case 105020: // Sturmwind
						player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
						break;
						// --- Hauptstaedte - Horde
					case 105025: // Orgrimmar
						player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
						break;
					case 105030: // Silbermond
						player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
						break;
					case 105035: // Donnerfels
						player->TeleportTo(1, -1290.0f, 147.033997f, 129.682007f, 4.919000f);
						break;
					case 105040: // Unterstadt
						player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
						break;
						// --- Hauptstaedte - Neutral
					case 105045:// Shattrath
						CloseGossipMenuFor(player);
						player->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
						break;
					case 105050: //Dalaran 
						player->TeleportTo(571, 5819.08f, 643.99f, 647.80f, 3.32f);
						break;
					case 105055:// Schwarze Festung
						player->TeleportTo(0, 2353.530029f, -5665.819824f, 426.028015f, 0.596f);
						break;
					case 105060:// GM-Insel
						player->TeleportTo(1, 16226.2f, 16257.0f, 13.2022f, 1.65007f);
						break;
					default:
						break;
				}//switch
				if (NPC_HELPER_DESPAWNAFTEREXIT == 1)
				{
					creature->Say("Auf Wiedersehen.", LANG_UNIVERSAL, NULL);
					creature->DespawnOrUnsummon(1 * IN_MILLISECONDS);
				}
				return true;
			}
			// --- Submenu 2 --- Heile mich
			if (action == 110005)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
				creature->Say("Du bist nun geheilt.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 2 --- Buffe mich
			if (action == 110010)
			{
				creature->CastSpell(player, 43223, true); //Großer Segen der Koenige
				creature->CastSpell(player, 48469, true); //Mal der Wildnis (24752?)
				creature->CastSpell(player, 42995, true); //Arkane Intelligenz
				creature->CastSpell(player, 48161, true); //Power Word
				creature->CastSpell(player, 48169, true); //Shad Pro
				creature->CastSpell(player, 48073, true); //Devine Spirit
				creature->Say("ich habe Dir die besten Buffs gegeben,", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Reparieren
			if (action == 110015)
			{
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->DurabilityRepairAll(false, 0.0f, true);
				creature->Say("Ich habe Deine komplette Ausruestung repariert.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 3 --- Wiederbelebung entfernen
			if (action == 115010)
			{
				if (!player->HasAura(15007))
				{
					creature->Say("Du hast keine Wiederbelebungs Nachwirkung. Da kann ich Dir dabei nicht helfen !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				creature->Say("Ich habe Deine Wiederbelebungs Nachwirkung entfernt.", LANG_UNIVERSAL, NULL);
				player->RemoveAurasDueToSpell(15007);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 3 --- Deserteur entfernen
			if (action == 115015)
			{
				if (!player->HasAura(26013))
				{
					creature->Say("Du bist gerade gar kein Deserteur. Daher kann ich Dir momentan auch nicht helfen !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				creature->Say("Du bist nun nicht mehr Deserteur.", LANG_UNIVERSAL, NULL);
				player->RemoveAurasDueToSpell(26013);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 3 --- Kampfbug entfernen
			if (action == 115020)
			{
				if (player->duel)
				{
					creature->Say("Du befindest dich in einem Duell. Da mache ich das nicht !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				if (!player->IsInCombat())
				{
					creature->Say("Du hast keinen 'Kampfbug' den ich entfernen koennte !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->ClearInCombat();
				creature->Say("Den 'Kampfbug' habe ich entfernt.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 4 --- Teleport-NPC
			if (action == 120005)
			{
				if (player->FindNearestCreature(NPC_HELPER_SUMMON_NPCTELEPORT, 50.0f))
				{
					player->GetSession()->SendNotification("Es befindet sich bereits einer von denen in der Naehe !");
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return true;
				}
				Creature* creature2 = player->SummonCreature(NPC_HELPER_SUMMON_NPCTELEPORT, player->GetPositionX() - 2, player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60 * IN_MILLISECONDS);
				if (!creature2)
				{
					player->GetSession()->SendNotification("Irgendwie reagiert da keiner auf die Rufe !");
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return true;
				}
				creature2->Say("Hallo. Ich stehe dir nun fuer 1 Minute zur Verfuegung.", LANG_UNIVERSAL, NULL);
				if (NPC_HELPER_SUMMON_CREATUREFOLLOW == 1)
					creature2->GetMotionMaster()->MoveFollow(player, 0.2f, PET_FOLLOW_ANGLE, MOTION_SLOT_ACTIVE);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}//action
			// --- Submenu 4 --- Upgrader-NPC
			if (action == 120010)
			{
				if (player->FindNearestCreature(NPC_HELPER_SUMMON_NPCUPGRADER, 50.0f))
				{
					player->GetSession()->SendNotification("Es befindet sich bereits einer von denen in der Naehe !");
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return true;
				}
				Creature* creature2 = player->SummonCreature(NPC_HELPER_SUMMON_NPCUPGRADER, player->GetPositionX() - 2, player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60 * IN_MILLISECONDS);
				if (!creature2)
				{
					player->GetSession()->SendNotification("Irgendwie reagiert da keiner auf die Rufe !");
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					return true;
				}
				creature2->Say("Hallo. Ich stehe dir nun fuer 1 Minute zur Verfuegung.", LANG_UNIVERSAL, NULL);
				if (NPC_HELPER_SUMMON_CREATUREFOLLOW == 1)
					creature2->GetMotionMaster()->MoveFollow(player, 0.2f, PET_FOLLOW_ANGLE, MOTION_SLOT_ACTIVE);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}//action
			// --- Submenu 5 --- GodMode
			if (action == 125005)
			{
				if (player->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_POWER))
				{
					creature->CastSpell(player, 38588, false); // Nur als Effekt
					player->GetSession()->GetPlayer()->SetCommandStatusOff(CHEAT_POWER);
					if (player->getClass() == CLASS_WARRIOR)
					{
						player->SetMaxPower(POWER_RAGE, 100);
						player->SetPower(POWER_RAGE, 0);
					}
					if (player->getClass() == CLASS_DEATH_KNIGHT)
					{
						player->SetMaxPower(POWER_RUNIC_POWER, 100);
						player->SetPower(POWER_RUNIC_POWER, 0);
					}
					creature->Say("Du bist nun NICHT MEHR unsterblich.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->GetSession()->GetPlayer()->SetCommandStatusOn(CHEAT_POWER);
				if (player->getClass() == CLASS_WARRIOR)
				{
					player->SetMaxPower(POWER_RAGE, 1000000);
					player->SetPower(POWER_RAGE, 1000000);
				}
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					player->SetMaxPower(POWER_RUNIC_POWER, 1000000);
					player->SetPower(POWER_RUNIC_POWER, 1000000);
				}
				creature->Say("Du bist nun unsterblich.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 5 --- CastTine
			if (action == 125010)
			{
				if (player->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_CASTTIME))
				{
					creature->CastSpell(player, 38588, false); // Nur als Effekt
					player->GetSession()->GetPlayer()->SetCommandStatusOff(CHEAT_CASTTIME);
					creature->Say("Du zauberst nun NICHT MEHR schneller.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->GetSession()->GetPlayer()->SetCommandStatusOn(CHEAT_CASTTIME);
				creature->Say("Du zauberst nun schneller.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 5 --- GlobalCooldown
			if (action == 125015)
			{
				if (player->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_COOLDOWN))
				{
					creature->CastSpell(player, 38588, false); // Nur als Effekt
					player->GetSession()->GetPlayer()->SetCommandStatusOff(CHEAT_COOLDOWN);
					creature->Say("Du zauberst nun NICHT MEHR oefters.", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->GetSession()->GetPlayer()->SetCommandStatusOn(CHEAT_COOLDOWN);
				creature->Say("Du zauberst nun oefters.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			// --- Submenu 6 --- Gold
			if (action == 130005)
			{
				if (player->GetMoney() > 1000000000)
				{
					creature->Say("Du hast wohl genug Geld. Dir gebe ich erstmal keins mehr !", LANG_UNIVERSAL, NULL);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				creature->CastSpell(player, 46642, false); // 5000 gold
				creature->Say("Ich habe Dir 5000 Gold gegeben. Ich hoffe Du gehst damit sparsam um.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			TC_LOG_ERROR("misc", "NPC_Helper - nicht implementierter Menupunkt (%u)",action);
			CloseGossipMenuFor(player);
			OnGossipHello(player, creature);
			return false;
		}//if sender
		return false;
	}//OnGossipSelect
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Helper()
{
	new NPC_Helper();
};
