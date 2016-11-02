/*
NPC_GIVER_Hunterpets
testet: 3.3.5a
stand: 26.10.2016

SET @CREATURTEMPLATE_ENTRY = 96024;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (Hunterpets)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GIVER_Hunterpets', 0);

mysql:
SELECT entry FROM `creature_template` WHERE type = 1 AND family > 0 AND (type_flags & 1) > 0 ORDER BY family ASC, name ASC
export csv
*/

// ******************************************************************************
// include
// ******************************************************************************
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Object.h"
#include "Item.h"
#include "Config.h"
#include <cstring>
#include "GossipDef.h"
#include <string>
#include <array>
#include "Pet.h"
// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GIVER_Hunterpets : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GIVER_Hunterpets() : CreatureScript("NPC_GIVER_Hunterpets") { }
	// ******************************************************************************
	// parameter (anpassbar)
	// ******************************************************************************
	array<uint32, 1200> NPC_GIVER_Hunterpets_DATA = { 24133,2753,30320,24516,628,1258,7055,3861,19423,9696,10221,20330,20058,1923,26672,30762,24475,16926,30164,834,833,2727,18033,14339,10077,21340,17854,69,1817,299,27408,2729,9690,2275,24026,8961,8960,8959,19459,2728,29993,10981,22737,31975,37294,30455,29358,3825,3824,3823,9697,12431,27578,1922,26592,27523,26586,18670,21952,5287,5286,521,2923,525,10644,1766,995,25791,8211,30456,2959,2958,2960,118,24206,2730,565,3826,5288,17669,20574,1509,704,705,3939,21956,19458,29735,31678,9416,30430,17280,18059,2925,2926,2924,31233,9694,3862,24726,5356,1138,24677,4950,213,1133,26016,1979,1980,20748,1132,18476,18477,17548,25675,5596,22353,24517,29452,29889,2681,4482,2680,25447,24128,1131,24076,1765,923,1508,24530,24043,24064,14222,728,21723,700,698,2850,4126,28404,20615,23014,5865,28001,3121,14430,3475,2033,1713,15652,1085,2385,2034,3035,3566,29327,7431,7430,7433,7434,7432,3619,16348,16349,21022,21724,2407,5828,17202,2522,31636,1199,731,977,976,2032,2069,2071,2070,2237,2961,2406,4124,2042,2043,17203,736,28097,10200,2732,2731,2734,20671,18982,22173,5766,3243,3415,3416,3241,3425,768,2175,17411,684,28297,10737,10741,729,756,758,1201,15366,15372,15653,15651,16347,2384,682,772,767,26021,22005,20412,5807,4067,2031,683,681,11360,15068,11365,15101,15067,11361,11376,11366,11364,11921,930,18983,22162,20027,30206,1821,949,15975,29241,8933,4040,22044,616,1184,16170,16171,14279,4412,4411,4413,4414,4377,4378,4379,4376,4380,26625,31336,18647,769,4005,4263,4264,4007,4006,15974,29242,18466,18467,2348,1195,2350,30,120,4415,2349,2565,2001,1994,5856,5858,16352,505,569,14472,12433,7319,1111,1112,22132,43,1781,1780,471,17523,17522,574,16453,31747,1688,1505,1824,2563,539,11370,14532,8277,20998,20714,23958,11739,11738,5857,2707,14266,858,15041,16351,16350,10375,10359,26033,442,17236,20682,32475,8762,28342,28221,1822,15976,29243,217,1555,1998,2000,1986,1999,3821,3819,3820,2686,1185,1504,17683,8956,8957,8958,26482,3809,14280,1130,1129,1189,17345,17661,6788,1815,1816,3810,1186,17348,2356,7445,1778,3811,1797,2351,1188,17347,5272,2165,27131,34178,24547,1196,29319,26706,5268,5274,1961,14344,1225,5352,12432,24633,26643,7446,29994,7444,7443,32752,34025,2163,10806,12037,26644,2354,1128,822,4511,5992,2966,345,2954,3225,1125,3099,1127,3100,1192,157,547,8303,1126,119,1191,3098,1190,16117,390,330,4514,524,4512,1689,708,29996,113,26020,4535,1985,454,1984,24047,20773,3231,17952,20075,22163,4841,5053,3110,4341,4345,4343,4342,2635,2089,17144,2476,1693,28002,4344,28325,14233,1150,1151,1082,1087,3581,1152,34027,24138,1400,1084,1417,15043,23206,25963,5982,18470,5983,16972,16973,2830,26174,4695,1809,24172,428,21042,26483,4693,4694,4692,26838,2580,5429,23945,1109,2831,8207,154,14268,2579,1194,1811,5428,1810,4154,4158,5430,7376,8299,2829,2970,2971,26019,17042,21515,462,6013,2969,199,2578,2931,17217,4823,24287,3812,3228,6250,18241,3108,2233,12347,24478,23929,33712,24479,26521,25481,1088,3460,3106,2231,2236,2235,33713,830,831,1216,922,17216,4821,4822,2544,3814,3107,34026,2232,2234,1557,1511,5260,5264,5262,28096,28098,28213,1114,1559,1516,14491,1108,1558,2521,34028,9622,6585,6514,6513,6516,9577,20728,20729,4357,4351,4356,4352,4355,3123,3122,3227,22052,20754,20751,20734,14232,3632,3637,3636,3633,3634,26641,31340,26628,31343,29698,1019,21124,23873,29334,2561,1016,1015,1018,1017,2559,2560,3257,687,9684,9683,686,1020,1023,1021,1022,107,6505,6507,6506,1140,14821,1353,20634,685,3254,3255,3256,5842,26029,730,6508,854,856,855,34158,2956,21635,4725,2957,3246,21634,2322,2321,2323,24740,3244,17374,22807,3068,3245,2955,4724,2172,34022,17373,17372,22193,3126,30613,8301,3125,7078,3226,7405,5823,9695,22257,8926,9698,14476,3281,21864,4697,4696,4699,22100,7803,5424,5422,4140,5423,4139,3124,5989,5987,5988,3250,3252,11737,11736,11735,26031,7022,3127,9691,5937,4824,4825,6352,6369,14223,7977,4887,5432,8213,3653,33710,4399,4398,4400,4397,4396,3461,33711,2505,25482,13896,2408,4144,4143,4142,14123,13599,5431,34029,4425,3868,11368,8927,23959,26622,31337,1512,9521,14965,1553,4539,16174,4538,16355,1513,16353,8602,8601,8600,4862,10357,16173,4861,26017,1554,16354,17221,3866,28233,5426,4688,4250,14228,12418,13036,4127,4129,4128,4316,4662,4660,8208,4691,27329,4248,4249,5427,4690,5986,8300,10979,4304,5985,5829,5425,4689,5984,4548,34019,4534,6867,27294,27249,21470,35293,32481,19429,20686,21891,21989,21904,21990,23693,27244,17034,24747,24787,29044,28004,17129,18257,26369,7099,7097,7098,17035,17053,21468,17039,25817,14343,21495,18220,22265,21804,14283,22767,32098,37419,1997,1995,1996,26028,38154,17128,18996,18963,19055,7455,7456,5349,10882,5834,4117,19428,20688,3630,20797,5056,3631,5756,4119,21123,3249,26806,5291,8336,14234,26446,4346,4347,4348,5308,20749,20999,28477,29693,11357,11359,5708,20673,26038,3424,3247,5307,4118,3472,10581,18155,21544,15650,18851,20502,20517,15649,20039,20038,26024,18854,17525,17526,16900,17527,23326,16934,19189,17620,17198,17199,16932,16933,22123,26030,19349,19350,32751,23219,22191,22255,35292,19771,21015,21014,21012,21016,21013,21017,19770,26037,18878,18884,18465,18464,22120,18129,21246,18128,18280,34018,17724,20185,17736,20186,20387,18285,20196,21128,21841,17731,20173,18130,18131,18880,20681,21901,23501,26027,19784,5048,5762,5755,28011,5224,5225,11372,11373,11371,7268,26032,19785,28358,25498,25464,17349,27421,20752,21839,17350,18469,21372,20611,21373,34021,18468,16520,18437,12801,21033,10807,7448,7449,6167,12800,12802,7447,4031,24673,12803,8764,8763,20932,33504,8660,11497,21879,4032,6498,6499,27483,31349,32485,6584,33505,6500,20931,5460,6582,10040,6553,8205,5454,11723,11730,11734,15323,15320,11728,14473,4132,8204,33508,15622,15233,15230,15286,11789,30423,11741,11740,8925,11320,14477,26293,26358,26359,30148,5226,14237,29605,30291,30422,11787,11788,29390,33511,25454,30093,30445,29469,32361,30447,28009,33506,25489,25488,25487,18283,20197,20198,31871,22182,19632,20174,17732,20175,18133,24731,28085,28086,34024,18132,11673,11672,19207,21108,33502,10430,17447,21102,38453,33776,32517,35189,33510 };
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GIVER_Hunterpets_DATA_filtered;
	array<string, 47>  NPC_GIVER_Hunterpets_DATA_family = { "NULL","Wolf","Cat","Spider","Bear","Boar","Crocolisk","Carrion","Crab","Gorilla","NULL","Raptor","Tallstrider","NULL","NULL","Felhunter","Voidwalker","Succubus","NULL","Doomguard","Scorpid","Turtle","NULL","Imp","Bat","Hyena","Owl","Wind Serpent","Remote Control","Felguard","Dragonhawk","Ravager","Warp Stalker","Sporebat","Nether Ray","Serpent","NULL","Moth","Chimaera","Devilsaur","Ghoul","Silithid","Worm","Rhino","Wasp","Core Hound","Spirit Beast"};
	enum GOSSIP_SENDER_MENU
	{
		GOSSIP_SENDER_MENU_MAIN,
		GOSSIP_SENDER_MENU_SUB,
		GOSSIP_SENDER_MENU_EXIT,
		GOSSIP_SENDER_MENU_GIVE,
	};
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		player->PlayerTalkClass->ClearMenus();
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t Alle zaehmbaren|r", GOSSIP_SENDER_MENU_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t nach Gruppen Seite 1|r", GOSSIP_SENDER_MENU_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t nach Gruppen Seite 2|r", GOSSIP_SENDER_MENU_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t Alle Exotischen|r", GOSSIP_SENDER_MENU_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-GroupLoot-Pass-Up:30:30:-18|t auf Wiedersehen|r", GOSSIP_SENDER_MENU_EXIT, 1);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}//OnGossipHello
	// ******************************************************************************
	// OnGossipSelect
	// ******************************************************************************
	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		switch (sender)
		{
			case GOSSIP_SENDER_MENU_EXIT:
			{
				creature->Say("Auf Wiedersehen.", LANG_UNIVERSAL, NULL);
				player->PlayerTalkClass->ClearMenus();
				CloseGossipMenuFor(player);
				return false;
			}
			break;
			case GOSSIP_SENDER_MENU_MAIN:
			{
				if (player->IsInCombat())
				{
					creature->Say("Du befindest Dich in einem Kampf. Da kann ich Dir nicht helfen !", LANG_UNIVERSAL, NULL);
					player->PlayerTalkClass->ClearMenus();
					CloseGossipMenuFor(player);
					return false;
				}
				if (action == 105)
				{
					DBdata_filter(player, 99, 0);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 110)
				{
					player->PlayerTalkClass->ClearMenus();
					for (uint32 i = 1; i <= 25; i++)
					{
						if (NPC_GIVER_Hunterpets_DATA_family[i] != "NULL")
							AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t zaehmbare '" + NPC_GIVER_Hunterpets_DATA_family[i] + "'|r", GOSSIP_SENDER_MENU_SUB, (1000 + i));
					}
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MENU_SUB, 9997);
					SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
					return true;
				}
				if (action == 115)
				{
					player->PlayerTalkClass->ClearMenus();
					for (uint32 i = 26; i < NPC_GIVER_Hunterpets_DATA_family.size(); i++)
					{
						if (NPC_GIVER_Hunterpets_DATA_family[i] != "NULL")
							AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|cff000000|TInterface\\icons\\Ability_Hunter_BeastTaming:30:30:-18|t zaehmbare '" + NPC_GIVER_Hunterpets_DATA_family[i] + "'|r", GOSSIP_SENDER_MENU_SUB, (1000 + i));
					}
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MENU_SUB, 9997);
					SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
					return true;
				}
				if (action == 120)
				{
					DBdata_filter(player, 1, 0);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}

			}
			break;
			case GOSSIP_SENDER_MENU_SUB:
			{
				if (action == 9997)
				{
					StartIndex = 0;
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
				}
				if (action > 1000 && action < 9997)
				{
					uint32 tfamily = (action - 1000);
					DBdata_filter(player, 0, tfamily);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
			}
			break;
			case GOSSIP_SENDER_MENU_GIVE:
			{
				// --- Submenu (Hauptmenu)
				if (action == 999997)
				{
					StartIndex = 0;
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
				}
				// --- Submenu (weiter)
				if (action == 999998)
				{
					StartIndex = StartIndex + 25;
					if (StartIndex > NPC_GIVER_Hunterpets_DATA_filtered.size())
						StartIndex = 0;
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				// --- Submenu (zurueck)
				if (action == 999999)
				{
					StartIndex = StartIndex - 25;
					if (StartIndex < 0)
						StartIndex = 0;
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				// --- Submenu (auswahl)
				if (action > 100000 && action < 999997)
				{
					if (player->getClass() != CLASS_HUNTER)
					{
						creature->Say("Irgendwie siehts Du nicht wie einer aus der Jaegerklasse aus. Ich kann Dir daher kein Tier geben !", LANG_UNIVERSAL, NULL);
						player->PlayerTalkClass->ClearMenus();
						CloseGossipMenuFor(player);
					}
					else
					{
						uint32 tindex = (action - 100000);
						if (tindex <= 0 || NPC_GIVER_Hunterpets_DATA_filtered[tindex] <= 0) {
							creature->Say("Dieses Tier habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
						}
						else
						{
							CreatureTemplate const* creature_template = sObjectMgr->GetCreatureTemplate(NPC_GIVER_Hunterpets_DATA_filtered[tindex]);
							if (player->GetPet()) {
								creature->Say("Du musst erst dein aktives Tier 'parken' !", LANG_UNIVERSAL, NULL);
								CloseGossipMenuFor(player);
								OnGossipSelect_Sub(player, creature, StartIndex);
							}
							else
							{
								if ((creature_template->type_flags & 65536) && !player->CanTameExoticPets())
								{
									creature->Say("Tja, Du kannst dieses exotische Tier (noch) nicht zaehmen. Ich kann Dir das daher auch nicht geben !", LANG_UNIVERSAL, NULL);
									player->PlayerTalkClass->ClearMenus();
									CloseGossipMenuFor(player);
									OnGossipSelect_Sub(player, creature, StartIndex);
								}
								else
								{
									Creature *creatureTarget = creature->SummonCreature(NPC_GIVER_Hunterpets_DATA_filtered[tindex], player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
									if (!creatureTarget) return false;
									Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
									if (!pet) return false;
									creatureTarget->setDeathState(JUST_DIED);
									creatureTarget->RemoveCorpse();
									creatureTarget->SetHealth(0);
									pet->SetPower(POWER_HAPPINESS, 1048000);
									/*
									pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
									pet->GetMap()->Add((Creature*)pet);
									pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
									*/
									pet->UpdateAllStats();
									player->SetMinion(pet, true);
									pet->SavePetToDB(PET_SAVE_AS_CURRENT);
									pet->InitTalentForLevel();
									player->PetSpellInitialize();
									creature->Say("Ich habe Dir das gewuenschte Tier gegeben.", LANG_UNIVERSAL, NULL);
								}
							}
						}
					}
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
			}
			break;
		}//switch sender
		return true;
	}//OnGossipSelect
	// ******************************************************************************
	// OnGossipSelect_Sub
	// ******************************************************************************
	void OnGossipSelect_Sub(Player* player, Creature* creature, uint32 StartIndex)
	{
		player->PlayerTalkClass->ClearMenus();
		uint32 zaehler = 0;
		uint32 MaxIndex = NPC_GIVER_Hunterpets_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			CreatureTemplate const* creature_template = sObjectMgr->GetCreatureTemplate(NPC_GIVER_Hunterpets_DATA_filtered[i]);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|t " + creature_template->Name + "|r", GOSSIP_SENDER_MENU_GIVE, (100000 + i));
			zaehler = zaehler + 1;
			if (zaehler == 25) {
				StartIndex = i;
				break;
			}//if
		}//for
		if (StartIndex > 25)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MENU_GIVE, 999999);
		if (StartIndex < MaxIndex)
			AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-NextPage-Up:30:30:-18|t weiter|r", GOSSIP_SENDER_MENU_GIVE, 999998);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t Hauptmenu|r", GOSSIP_SENDER_MENU_GIVE, 999997);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	};//ShowNPC_GIVER_Hunterpets_DATA
	// ******************************************************************************
	// DBdata_filter
	// ******************************************************************************
	void DBdata_filter(Player* player, uint32 t_exotic, uint32 t_family)
	{
		NPC_GIVER_Hunterpets_DATA_filtered.clear();
		uint32 MaxIndex = NPC_GIVER_Hunterpets_DATA.size();
		for (uint32 i = 0; i < MaxIndex; i++)
		{
			if (NPC_GIVER_Hunterpets_DATA[i] > 0)
			{
				if (CreatureTemplate const* creature_template = sObjectMgr->GetCreatureTemplate(NPC_GIVER_Hunterpets_DATA[i]))
				{
					if (!(creature_template->faction & player->getFaction()))
						continue;
					if (t_family > 0 && creature_template->family != t_family)
						continue;
					if (t_exotic == 0 && (creature_template->type_flags & 65536))
						continue;
					if (t_exotic == 1 && !(creature_template->type_flags & 65536))
						continue;
					// ---
					NPC_GIVER_Hunterpets_DATA_filtered.push_back(NPC_GIVER_Hunterpets_DATA[i]);
				}//if ItemTemplate
			}//if > 0
		}//for
	};//DBdata_filter
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GIVER_Hunterpets()
{
	new NPC_GIVER_Hunterpets();
};