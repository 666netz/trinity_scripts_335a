/*
NPC_Equiper
testet: 3.3.5a
stand: 01.11.2016

NOT WORKING

SET @CREATURTEMPLATE_ENTRY = 96005;
SET @CREATURTEMPLATE_NAME = "Equiper NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Equiper', 0);
*/

// ******************************************************************************
// class
// ******************************************************************************
class NPC_Equiper : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Equiper() : CreatureScript("NPC_Equiper") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	// ******************************************************************************
	// parameter
	// ******************************************************************************
	uint32 NPC_Equiper_GM = 0;//0=disabled / 1=enabled
	/*
	0 Brust
	1 Kopf
	2 Haende
	3 Beine
	4 Schulter
	5 Amulett
	6-7 Ring
	8-9 Schmuck
	10 Armschiene
	11 Taile
	12-14 Waffe (Haupt,Neben,Fern)
	15 Munition (OPTIONAL)
	*/
	uint32 NPC_Equiper_ARR_SET277[22][16] = {
	{ 0 },																							   //Dummy
	{ 51220,51221,51222,51223,51224 ,50627 ,50622,50657 ,50349,50726 ,50611 ,0 ,51448,50729,0     ,0 },//1  = Krieger Tank (1x1H+S)
	{ 51225,51226,51227,51228,51229 ,50682 ,50622,50657 ,50349,50726 ,50659 ,0 ,51393,0    ,0     ,0 },//2  = Krieger Schaden (2H)
	{ 51225,51226,51227,51228,51229 ,50682 ,50622,50657 ,50349,50726 ,50659 ,0 ,51448,51448,0     ,0 },//3  = Krieger Furor (2x1H)
	{ 51275,51276,51277,51278,51279 ,50658 ,50720,50657 ,50348,50365 ,50721 ,0 ,51446,50616,0     ,0 },//4  = Paladin Tank (1x1H+S)
	{ 51275,51276,51277,51278,51279 ,50658 ,50720,50657 ,50348,50365 ,50721 ,0 ,51391,0    ,0     ,0 },//5  = Paladin Vergelter (2H)
	{ 51270,51271,51272,51273,51274 ,50609 ,50720,50657 ,50348,50365 ,50721 ,0 ,51446,50616,0     ,0 },//6  = Paladin Heilig (1x1H+S)
	{ 51285,51286,51287,51288,51289 ,50633 ,50604,50693 ,50365,50349 ,50655 ,0 ,50654,0    ,50638 ,52021 },//7  = Jaeger
	{ 51250,51251,51253,51254,0     ,50633 ,50604,50693 ,50365,50349 ,50670 ,0 ,51442,51442,0	  ,0 },//8  = Schurke
	{ 51255,51256,51257,51258,51259 ,50658 ,50636,50720 ,50348,50365 ,50651 ,0 ,51398,0    ,50684 ,0 },//9  = Priester
	{ 51305,51306,51307,51308,51309 ,50627 ,50622,50657 ,50349,50726 ,50659 ,0 ,51393,0    ,0     ,0 },//10 = Todesritter 1
	{ 51310,51311,51312,51313,51314 ,50728 ,50622,50657 ,50349,50726 ,50659 ,0 ,51393,0    ,0     ,0 },//11 = Todesritter 2
	{ 51235,51236,51237,51238,51239 ,50658 ,51235,50604 ,50348,50365 ,50687 ,0 ,51516,50729,30023 ,0 },//12 = Schamane 1
	{ 51240,51241,51242,51243,51244 ,50658 ,51235,50604 ,50348,50365 ,50687 ,0 ,51516,50729,30023 ,0 },//13 = Schamane 2
	{ 51280,51281,51282,51283,51284 ,50724 ,50636,50720 ,50348,50365 ,50686 ,0 ,51399,0    ,50684 ,0 },//14 = Magier
	{ 51230,51231,51232,51233,51234 ,50700 ,50636,50720 ,50348,50365 ,50651 ,0 ,51398,0    ,50684 ,0 },//15 = Hexenmeister
	{ 0,0,0,0,0 ,0 ,0,0 ,0,0 ,0 ,0 ,0,0,0 ,0 },														   //16 = Moench (nicht unterstuetzt)
	{ 51290,51291,51292,51293,51294 ,50682 ,50622,50657 ,50349,50726 ,50670 ,0 ,51403,0    ,51423 ,0 },//17 = Druide Tank
	{ 51295,51296,51297,51298,51299 ,50658 ,50610,50614 ,50366,50726 ,50630 ,0 ,51401,0    ,51429 ,0 },//18 = Druide Caster
	{ 51300,51301,51302,51303,51304 ,50633 ,50604,50622 ,50348,50349 ,50670 ,0 ,51403,0    ,51437 ,0 },//19 = Druide Feral
	{ 0,0,0,0,0 ,0 ,0,0 ,0,0 ,0 ,0 ,0,0,0 ,0 },											               //20 = Daemonenjaeger (nicht unterstuetzt)
	{ 11508,2586,12064,100,0 ,0 ,0,0 ,0,0 ,0 ,0 ,0,0,0 ,0 }											   //21 = GM (wenn enabled)
	};
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		if (player->getClass() == CLASS_WARRIOR)// -- Krieger
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Krieger T10-Set Tank|r", GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Krieger T10-Set Schaden|r", GOSSIP_SENDER_MAIN, 2);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Krieger T10-Set Furor|r", GOSSIP_SENDER_MAIN, 3);
		}
		if (player->getClass() == CLASS_PALADIN)// -- Paladin
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Paladin T10-Set Tank|r", GOSSIP_SENDER_MAIN, 4);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Paladin T10-Set Vergelter|r", GOSSIP_SENDER_MAIN, 5);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Paladin T10-Set Heilig|r", GOSSIP_SENDER_MAIN, 6);
		}
		if (player->getClass() == CLASS_HUNTER)// -- Jaeger
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Jaeger T10-Set|r", GOSSIP_SENDER_MAIN, 7);
		}
		if (player->getClass() == CLASS_ROGUE)// -- Schurke
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Schurke T10-Set|r", GOSSIP_SENDER_MAIN, 8);
		}
		if (player->getClass() == CLASS_PRIEST)// -- Priester
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Priester T10-Set|r", GOSSIP_SENDER_MAIN, 9);
		}
		if (player->getClass() == CLASS_DEATH_KNIGHT)// -- Todesritter
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Todesritter T10-Set|r", GOSSIP_SENDER_MAIN, 10);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Todesritter T10-Set|r", GOSSIP_SENDER_MAIN, 11);
		}
		if (player->getClass() == CLASS_SHAMAN)// -- Schamane
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Schamane T10-Set|r", GOSSIP_SENDER_MAIN, 12);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Schamane T10-Set|r", GOSSIP_SENDER_MAIN, 13);
		}
		if (player->getClass() == CLASS_MAGE)// -- Magier
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Magier T10-Set|r", GOSSIP_SENDER_MAIN, 14);
		}
		if (player->getClass() == CLASS_WARLOCK)// -- Hexenmeister
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Hexenmeister T10-Set|r", GOSSIP_SENDER_MAIN, 15);
		}
		if (player->getClass() == 10)// -- Moench
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Moench unterstuetze ich noch nicht|r", GOSSIP_SENDER_MAIN, 16);
		}
		if (player->getClass() == CLASS_DRUID)// -- Druide
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Druide T10-Set Tank|r", GOSSIP_SENDER_MAIN, 17);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Druide T10-Set Schaden|r", GOSSIP_SENDER_MAIN, 18);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Druide T10-Set Feral|r", GOSSIP_SENDER_MAIN, 19);
		}
		if (player->getClass() == 12)// -- Daemonenjaeger
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Achievement_PVP_P_09:30:30:-18|t Daemonenjaeger unterstuetze ich noch nicht|r", GOSSIP_SENDER_MAIN, 20);
		}
		if (NPC_Equiper_GM == 1 && player->GetSession()->GetSecurity() >= 2) // Or RBAC 'HasPermission(rbac::PERMISSION_NAME);'
		{
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR,  "|cff404040|TInterface\\chatframe\\UI-ChatIcon-Blizz:30:30:-18|t GM-Ausruestung|r", GOSSIP_SENDER_MAIN, 22);
		}
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
				return false;
			}
			// --- im Kampf
			if (player->IsInCombat())
			{
				creature->Say("Du befindest Dich in einem Kampf. Da kann ich Dir nichts geben !", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return false;
			}
			// --- nicht unterstuetze class
			if (action == 10 || action == 12)
			{
				creature->Say("Deine Charakter-Klasse unterstuetze ich (noch) nicht !", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return false;
			}
			// --- unterstuetze class
			if (action >= 10 && action <= 22)
			{
				uint32 anzahl = 0;
				for (uint32 i = 0; i <= 15; i++)
				{
					if (i <= 14)
						anzahl = 1;
					if (i == 15)
						anzahl = 1000;
					if (NPC_Equiper_ARR_SET277[action][i] > 0 && player->HasItemCount(NPC_Equiper_ARR_SET277[action][i], 1, true) == 0)
						player->AddItem(NPC_Equiper_ARR_SET277[action][i], anzahl);
				}//for
				creature->Say("Ich habe Dir das gewuenschte Set, soweit wie moeglich, gegeben.", LANG_UNIVERSAL, NULL);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}//if action
			return false;
		}//if sender
		return false;
	}//OnGossipSelect
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Equiper()
{
	new NPC_Equiper();
};
