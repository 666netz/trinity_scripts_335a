/*
NPC_GIVER_Ilevel
testet: 3.3.5a
stand: 25.10.2016

SET @CREATURTEMPLATE_ENTRY = 96022;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (iLevel)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `IlevelpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GIVER_Ilevel', 0);

mysql:
SELECT entry FROM `item_template` WHERE class='2' AND itemLevel > 245 ORDER BY subclass ASC, InventoryType ASC, ItemLevel DESC, name ASC
export csv
SELECT entry FROM `item_template` WHERE class='4' AND itemLevel > 245 ORDER BY subclass ASC, InventoryType ASC, ItemLevel DESC, name ASC
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
// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// class
// ******************************************************************************
class NPC_GIVER_Ilevel : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GIVER_Ilevel() : CreatureScript("NPC_GIVER_Ilevel") { }
	// ******************************************************************************
	// parameter (anpassbar)
	// ******************************************************************************
	array<uint32, 700> NPC_GIVER_Ilevel_DATA_2 = { 50737,50654,51516,50012,51947,51938,51916,50411,51515,47427,47475,47001,48507,47156,51795,50759,50787,51440,51526,51525,51439,48426,48440,49623,50709,51389,50415,51905,49888,51388,47446,47078,48402,50798,51395,50638,51927,51394,50034,48420,50776,51450,51834,50444,51845,51449,47521,47523,48424,51561,51385,45173,50738,50708,51520,49997,51937,51893,50179,51519,47528,48511,47526,50760,50050,50810,50734,50685,51454,50428,51944,51875,50028,51453,47206,48519,47483,51798,50051,51004,51446,51445,48435,50603,51391,51946,49919,51833,51390,47519,47520,48404,51796,50052,51562,50735,50727,51481,50425,50178,51857,51480,47239,47491,48517,51022,32466,50672,51522,50412,51858,51869,51521,47513,48513,47506,50046,51021,51010,50732,50704,50427,51932,50068,47517,47518,50771,50047,51448,51447,48438,33350,33475,50730,51393,50070,51936,51392,47515,47516,48406,50761,50049,50048,50731,50695,50725,50648,51403,51401,51432,51457,51405,50429,51943,51945,51887,50040,50181,51898,49992,51881,51828,51404,51456,51402,51431,51400,47524,51799,47130,48412,48414,48523,48521,48410,47525,51797,47463,50966,50805,50998,51582,50692,51524,51941,51876,50035,51523,51801,48515,51003,50710,51529,51444,50184,51819,51530,51443,48444,48432,51784,50736,50641,50621,50676,51518,50426,51942,51846,51868,49982,50183,50016,51517,47461,48509,46969,51800,47416,47113,51384,51011,50608,51398,51399,51939,51815,49968,51910,51406,51397,47422,46980,49191,48408,51803,51788,50793,51442,51528,51527,51441,48428,48442,51880,50474,51535,50999,50733,51412,49981,51940,51411,47428,48422,46995,51802,50684,50631,50033,51838,50472,51852,50204,51532,51531,51410,51451,51553,51326 };
	array<uint32, 1600> NPC_GIVER_Ilevel_DATA_4 = { 54581,50647,50658,50682,50724,50609,50700,50728,50627,50633,54557,53132,49989,50005,50023,50182,49975,51871,51842,50061,51867,50180,51934,50195,51863,51890,51822,50421,51894,50452,51335,51349,51331,51347,51333,51353,51355,51357,53103,47060,47433,47468,47466,47133,47110,47458,47144,53509,53499,51008,51548,53502,51012,50763,53503,51016,50852,51779,50809,17886,40599,54585,54576,50404,50398,52572,50402,50400,50604,50622,50618,50720,50642,50614,50610,50636,50693,50644,50664,50678,50657,50714,53490,54563,53133,54567,50403,50397,52571,50401,50399,51913,49949,51849,50185,50186,50447,50174,49985,49977,49967,50424,50414,49990,50008,50453,51878,51900,50025,51843,51884,49999,51855,50170,51336,51358,50388,50384,52570,50387,50386,47443,47237,47476,46966,47439,47489,47075,47224,47413,53116,47157,53110,50790,50375,50377,52569,50376,50378,51381,53495,53492,51001,51560,51558,51559,51557,50803,51387,50986,53501,51024,40727,54588,54589,54591,54590,50366,50726,50349,50363,50348,49686,50365,50364,50706,54572,54573,54571,54569,50359,50354,50352,50356,50362,50353,50355,50357,51377,51378,50345,50360,50358,50361,50346,50351,50344,50343,47464,47131,47451,47477,47188,47088,47059,47432,50340,50339,50341,50342,50719,50635,51407,51396,51408,51409,51922,50173,50423,47146,47470,47064,47437,49187,42527,42539,42533,50781,50661,51281,51255,51261,51231,51538,51484,51489,51465,50006,51837,51158,51184,51178,51208,51896,47796,47789,47761,47764,48085,48035,48088,48058,41995,50276,51715,51554,50392,51737,50765,51736,50241,51765,41994,41855,41916,41947,50807,51284,51257,51264,51234,50643,51540,51486,51491,51467,51883,51155,51182,51175,51205,49991,51859,50449,47793,47792,47758,47767,48082,48029,48091,48061,42013,50279,51712,50988,50396,51739,50767,51734,50244,51762,42012,41870,41935,41966,51020,51573,51572,50613,50702,54562,50996,51862,50997,51930,49978,50063,51337,51327,51365,47447,47419,47084,46973,53118,41900,51017,50773,50694,51282,51262,51258,51232,51539,51485,51490,51466,51882,51823,49891,49892,50056,51157,51177,51181,51207,47478,47795,47790,47760,47189,47062,47435,47765,48033,48084,48059,48089,42007,50277,51714,50769,51732,50393,51741,50242,51764,50990,51777,42006,41865,41928,41960,50699,49890,51899,51850,50062,49893,51338,51328,51366,47482,47097,47205,47454,50804,51380,53507,54582,50686,50651,53486,51918,50032,51872,49994,51339,51329,51367,47208,47143,47485,47467,41911,50785,51007,50663,50722,51280,51260,51256,51230,51537,51483,51488,51464,50984,51874,50983,50011,50176,51159,51179,51183,51209,51921,47236,47797,47487,47788,47762,47763,48037,48086,48057,48087,42019,50275,51716,50766,51735,50391,51738,50240,51766,51005,42018,41875,41941,41972,50782,54583,50628,50668,50718,50653,50677,47551,47553,47550,47548,47552,47554,47549,47546,47547,47545,54556,53489,51888,50468,50205,50014,51848,51826,50467,50470,50074,51912,50466,49998,51933,50469,50019,51334,51348,51330,51346,51332,51354,51356,53115,47095,48668,48673,48669,48670,48675,47418,48674,48671,47417,48666,46971,47490,47238,47481,47436,47063,48672,48667,46977,47452,47192,42083,50859,53506,51382,51584,50791,50764,53497,50629,51283,51259,51263,51233,50717,51536,51482,51487,51463,51851,50975,50974,50418,51813,51156,51180,51176,51206,50172,47425,46993,47794,47791,47759,47129,47462,47766,48083,48031,48090,48060,42000,50278,51713,51379,50394,51740,50768,51733,50243,51763,53498,41999,41860,41922,41954,51790,50713,50679,51290,51296,51302,51252,51427,51421,51494,51435,51866,50073,50026,51149,51143,51137,51187,51825,48235,48171,48204,48141,48174,48201,48144,48230,51013,50821,51704,50826,51699,50108,51694,41679,41322,41673,41328,50089,51745,51585,50646,51292,51304,51299,51254,50715,51430,51424,51496,51438,49987,51147,51135,51140,51185,51839,50171,51830,48237,48168,48207,48138,48177,48198,48147,48228,50819,51706,50113,51692,50824,51701,41716,41276,41684,41282,50105,51746,51552,51565,51574,51575,51576,50656,51250,54561,51492,51923,50001,51189,50972,47004,48233,53114,48232,47431,50780,53508,41651,50087,51743,50707,50705,50067,50994,51908,50069,51925,50995,51343,51340,51368,47469,47112,47460,47145,50795,50778,50697,50696,51297,51303,51293,51253,51428,51422,51495,51436,49899,50042,51841,50041,51897,49898,51889,51142,51136,51146,51186,48236,47479,46975,47190,47420,48140,48205,48170,48145,48200,48175,48229,51550,50825,51700,50109,51693,50820,51705,50806,50858,41668,41299,41656,41305,50090,51744,50665,50607,49894,51920,50009,49895,49950,51856,51344,51341,51369,47423,46989,47445,47077,50783,53504,51023,54584,54580,50630,50670,53134,53126,50417,50333,51820,51345,51342,51370,51885,47474,47438,47155,47066,51783,50985,50675,50615,51301,51291,51295,51251,54560,51426,51420,51493,51434,50021,50982,50981,49979,51814,51138,51148,51144,51188,51904,53117,48234,48172,48203,48142,48173,48202,48143,48231,51789,50107,51695,50822,51703,50827,51698,41774,41288,41768,41294,50799,50088,51742,50649,51298,51300,51294,51425,51419,51433,51870,49996,51141,51139,51145,50973,48206,48139,48169,47453,48199,48146,48176,47096,51009,50828,51697,50106,51696,50823,51702,41662,41311,41317,51286,51242,51247,51237,50605,50626,51460,51505,51511,51499,51906,51153,51197,51192,51202,49952,50202,51877,48353,48292,48323,48358,48307,48328,48267,48262,50115,51710,50832,51754,50837,51749,50843,51759,50797,41158,41152,41020,41014,51002,50673,50698,51288,51240,51235,51245,54566,51462,51508,51514,51502,50022,50059,51911,51151,51199,51204,51194,51811,51864,48351,48321,48290,48360,48330,48309,53113,48269,48260,50117,51708,50834,51756,50845,51761,50839,51751,50792,41218,41212,41045,41039,51792,51015,51578,51579,51577,50689,50723,51289,51244,51239,51249,51458,50038,51840,51903,50970,50177,50971,51150,51195,51200,51190,46965,47209,47412,47486,48355,48325,48294,48356,48326,48305,48265,48264,50118,51707,51551,50830,51752,50841,51757,50835,51747,50800,41088,54587,50671,50688,53488,50993,50015,51853,51919,51935,50413,50992,51374,51371,51350,47153,46991,47426,47472,51325,50784,50762,50645,51287,51236,51246,51241,51461,51506,51512,51500,49901,50450,49988,51829,49900,51860,51152,51203,51193,51198,47450,47480,47087,47191,48322,48291,48352,48329,48308,48359,48268,48261,50116,51709,50844,51760,50838,51750,50833,51755,51566,41206,41200,41034,41028,51019,53493,54577,50652,50711,54558,53127,49896,49993,49897,51873,51891,50071,51375,51372,51351,51818,53119,47099,47457,47109,47456,51006,50812,51785,50687,50655,50030,51929,51914,50000,51376,51373,51352,47068,47442,47074,47441,50774,50789,54592,50619,51285,51238,51243,51248,50703,51459,51504,51510,51498,50188,50980,51926,50979,51154,51201,51196,51191,51827,50064,48324,48354,48293,48327,48357,48306,48266,48263,50114,51711,50842,51758,50831,51753,50836,51748,50777,41144,41138,41008,41002,51583,51503,51509,51497,41082,40995,40994,50640,50701,50712,51266,51272,51277,51306,51312,51221,51227,51415,51470,51543,51476,49986,51924,50060,50072,51173,51167,51162,51133,51127,51218,51212,48468,48398,48550,48493,48649,48587,48619,48545,48488,48644,48582,48614,48433,48383,50779,50862,51729,50867,51724,50326,51719,40830,40934,40829,40831,50855,51689,50096,51684,50848,51774,50080,51769,50660,50674,50617,51269,51279,51273,51309,51314,51224,51229,51418,51473,51545,51479,50003,51824,50020,49980,51170,51160,51166,51130,51125,51215,51210,51865,51847,48470,48400,48552,48495,48647,48621,48585,48543,48486,48646,48612,48580,48455,48381,51586,50860,51731,50324,51721,50865,51726,40871,40964,40870,40872,51014,50853,51691,50098,51682,51383,51581,51580,50846,51776,50082,51767,50681,50606,50680,51275,51265,51274,51310,51305,51225,51220,51413,51468,51541,51474,51902,50024,50965,50968,51861,50969,49951,51917,50027,51164,51174,51165,51129,51134,51214,51219,47147,47086,47449,47471,46968,47415,48396,48466,48491,48548,48617,48651,48589,48490,48547,48616,48642,48584,48385,48451,40481,50801,51018,50786,50328,51717,50864,51727,50869,51722,40791,40910,40790,40792,53505,50094,51686,50857,51687,53500,50078,51771,50850,51772,50691,50620,50667,54565,50036,50451,50187,51821,51879,51831,50989,50987,51836,50991,50010,51359,51362,47444,47207,47002,47429,47076,47484,53121,51782,51000,53494,51564,51555,50623,50612,51271,51268,51278,51308,51313,51223,51228,50624,51416,51471,51544,51477,51854,51928,51895,50199,49964,51817,49903,49904,49902,51168,51171,51161,51131,51126,51216,51211,50192,48469,48399,48551,48494,47440,47132,47061,47465,47067,47434,48586,48648,48620,48544,48487,48581,48645,48613,48447,48382,51025,50775,50808,51786,50866,51725,50861,51730,50325,51720,40851,40940,40850,40852,50854,51690,50097,51683,50847,51775,50081,51768,54578,54586,54579,50639,50632,50625,53125,53487,54564,53129,51931,49983,51915,49907,50416,50190,49906,49905,51816,51360,51363,46986,47003,47430,47154,47473,47424,53111,50772,50788,51787,50611,50721,50659,54559,49960,51907,50175,51901,50002,51832,51361,51364,47459,46967,47414,47455,53112,47111,47098,50796,50802,51563,53491,50650,50690,51276,51270,51267,51311,51307,51226,51222,50716,51414,51469,51542,51475,49995,51886,51892,50037,50977,50976,50978,51163,51169,51172,51128,51132,51213,51217,50075,51844,51835,47492,47240,48397,48467,48492,48549,48618,48588,48650,48489,48546,48615,48583,48643,48384,48453,50967,50811,50327,51718,50868,51723,50863,51728,40811,40928,40810,40812,50095,51685,50856,51688,51386,51556,50079,51770,50849,51773,50616,50729,51452,51455,51533,49976,50065,51812,51909,47085,47448,46964,47421,53496,51791,50794,42566,42572,42561,51478,51472,50460,50461,50455,42854,42616,51429,51437,51423,50454,50456,50457,42591,42585,42580,51507,51513,51501,50458,50463,50464,42609,42604,42599,51417,50462,50459,42622 };
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GIVER_Ilevel_DATA_filtered;
	array<string, 9>  NPC_GIVER_Ilevel_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	enum GOSSIP_SENDER_MENU
	{
		GOSSIP_SENDER_MENU_MAIN,
		GOSSIP_SENDER_MENU_SUB,
		GOSSIP_SENDER_MENU_GIVE,
		GOSSIP_SENDER_MENU_EXIT,
	};
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		player->PlayerTalkClass->ClearMenus();
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Cloth_73:30:30:-18|t Ruestungen|r", GOSSIP_SENDER_MENU_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_14.blp:30:30:-18|t Waffen|r", GOSSIP_SENDER_MENU_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-GroupLoot-Pass-Up:30:30:-18|t auf Wiedersehen|r", GOSSIP_SENDER_MENU_EXIT, 1);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}
	// ******************************************************************************
	// OnGossipSelect
	// ******************************************************************************
	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		switch (sender)
		{
			case GOSSIP_SENDER_MENU_EXIT:
			{
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
				// --- Hauptmenu (Ruestungen)
				if (action == 105)
				{
					player->PlayerTalkClass->ClearMenus();
					if (player->getClass() == 1)// -- Krieger
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_22:30:30:-18|t Plattenruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040401);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_31:30:30:-18|t Plattenruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040403);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Plate01:30:30:-18|t Plattenruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040405);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_14:30:30:-18|t Plattenruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040406);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Plate_13:30:30:-18|t Plattenruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040407);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Plate_02:30:30:-18|t Plattenruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040408);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_24:30:30:-18|t Plattenruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040409);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_10:30:30:-18|t Plattenruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040410);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shield_09:30:30:-18|t Schilde|r", GOSSIP_SENDER_MENU_SUB, 1040614);
					}
					if (player->getClass() == 2)// -- Paladin
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_22:30:30:-18|t Plattenruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040401);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_31:30:30:-18|t Plattenruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040403);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Plate01:30:30:-18|t Plattenruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040405);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_14:30:30:-18|t Plattenruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040406);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Plate_13:30:30:-18|t Plattenruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040407);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Plate_02:30:30:-18|t Plattenruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040408);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_24:30:30:-18|t Plattenruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040409);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_10:30:30:-18|t Plattenruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040410);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shield_09:30:30:-18|t Schilde|r", GOSSIP_SENDER_MENU_SUB, 1040614);
					}
					if (player->getClass() == 3)// -- Jaeger
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_41:30:30:-18|t Kettenruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040301);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_69:30:30:-18|t Kettenruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040303);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Mail_13:30:30:-18|t Kettenruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040305);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_45B:30:30:-18|t Kettenruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040306);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Mail_35:30:30:-18|t Kettenruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040307);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Chain_09:30:30:-18|t Kettenruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040308);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_29:30:30:-18|t Kettenruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040309);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_11:30:30:-18|t Kettenruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040310);
					}
					if (player->getClass() == 4)// -- Schurke
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_15:30:30:-18|t Lederruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040201);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_28:30:30:-18|t Lederruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040303);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Leather_07:30:30:-18|t Lederruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040305);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_05:30:30:-18|t Lederruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040306);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Leather_36:30:30:-18|t Lederruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040307);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Leather_9:30:30:-18|t Lederruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040308);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_38:30:30:-18|t Lederruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040309);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_67:30:30:-18|t Lederruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040310);
					}
					if (player->getClass() == 5)// -- Priester
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_65:30:30:-18|t Stoffruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040101);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_09:30:30:-18|t Stoffruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040103);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Cloth_46:30:30:-18|t Stoffruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040105);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_26:30:30:-18|t Stoffruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040106);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Cloth_01:30:30:-18|t Stoffruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040107);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Cloth_10:30:30:-18|t Stoffruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040108);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_12:30:30:-18|t Stoffruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040109);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_16:30:30:-18|t Stoffruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040110);
					}
					if (player->getClass() == 6)// -- Todesritter
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_22:30:30:-18|t Plattenruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040401);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_31:30:30:-18|t Plattenruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040403);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Plate01:30:30:-18|t Plattenruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040405);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_14:30:30:-18|t Plattenruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040406);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Plate_13:30:30:-18|t Plattenruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040407);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Plate_02:30:30:-18|t Plattenruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040408);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_24:30:30:-18|t Plattenruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040409);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_10:30:30:-18|t Plattenruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040410);
					}
					if (player->getClass() == 7)// -- Schamane
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_41:30:30:-18|t Kettenruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040301);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_69:30:30:-18|t Kettenruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040303);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Mail_13:30:30:-18|t Kettenruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040305);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_45B:30:30:-18|t Kettenruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040306);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Mail_35:30:30:-18|t Kettenruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040307);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Chain_09:30:30:-18|t Kettenruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040308);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_29:30:30:-18|t Kettenruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040309);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_11:30:30:-18|t Kettenruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040310);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shield_09:30:30:-18|t Schilde|r", GOSSIP_SENDER_MENU_SUB, 1040614);
					}
					if (player->getClass() == 8)// -- Magier
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_65:30:30:-18|t Stoffruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040101);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_09:30:30:-18|t Stoffruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040103);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Cloth_46:30:30:-18|t Stoffruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040105);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_26:30:30:-18|t Stoffruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040106);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Cloth_01:30:30:-18|t Stoffruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040107);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Cloth_10:30:30:-18|t Stoffruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040108);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_12:30:30:-18|t Stoffruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040109);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_16:30:30:-18|t Stoffruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040110);
					}
					if (player->getClass() == 9)// -- Hexenmeister
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_65:30:30:-18|t Stoffruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040101);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_09:30:30:-18|t Stoffruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040103);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Cloth_46:30:30:-18|t Stoffruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040105);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_26:30:30:-18|t Stoffruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040106);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Cloth_01:30:30:-18|t Stoffruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040107);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Cloth_10:30:30:-18|t Stoffruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040108);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_12:30:30:-18|t Stoffruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040109);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_16:30:30:-18|t Stoffruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040110);
					}
					if (player->getClass() == 10)// -- Moench
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Ability_Creature_Cursed_02:30:30:-18|t Moench unterstuetze ich noch nicht|r", GOSSIP_SENDER_MENU_SUB, 9999997);
					}
					if (player->getClass() == 11)// -- Druide
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Helmet_15:30:30:-18|t Lederruestung Kopf|r", GOSSIP_SENDER_MENU_SUB, 1040201);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Shoulder_28:30:30:-18|t Lederruestung Schulter|r", GOSSIP_SENDER_MENU_SUB, 1040303);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Chest_Leather_07:30:30:-18|t Lederruestung Brust|r", GOSSIP_SENDER_MENU_SUB, 1040305);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Belt_05:30:30:-18|t Lederruestung Taille|r", GOSSIP_SENDER_MENU_SUB, 1040306);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Pants_Leather_36:30:30:-18|t Lederruestung Beine|r", GOSSIP_SENDER_MENU_SUB, 1040307);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Boots_Leather_9:30:30:-18|t Lederruestung Fuesse|r", GOSSIP_SENDER_MENU_SUB, 1040308);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Bracer_38:30:30:-18|t Lederruestung Handgelenke|r", GOSSIP_SENDER_MENU_SUB, 1040309);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Gauntlets_67:30:30:-18|t Lederruestung Haende|r", GOSSIP_SENDER_MENU_SUB, 1040310);
					}
					if (player->getClass() == 12)// -- Daemonenjaeger
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Ability_Creature_Cursed_02:30:30:-18|t Daemonenjaeger unterstuetze ich noch nicht|r", GOSSIP_SENDER_MENU_SUB, 9999997);
					}
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MENU_SUB, 9999997);
					SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				}
				// --- Hauptmenu (Waffen)
				if (action == 110)
				{
					player->PlayerTalkClass->ClearMenus();
					if (player->getClass() == 1)// -- Krieger
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 2)// -- Paladin
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 3)// -- Jaeger
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 5)// -- Priester
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 6)// -- Todesritter
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 7)// -- Schamane
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 8)// -- Magier
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 9)// -- Hexenmeister
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 10)// -- Moench
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Ability_Creature_Cursed_02:30:30:-18|t Moench unterstuetze ich noch nicht|r", GOSSIP_SENDER_MENU_SUB, 9999997);
					}
					if (player->getClass() == 11)// -- Druide
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_06:30:30:-18|t Waffe Einhandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020013);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Axe_73:30:30:-18|t Waffe Zweihandaexte|r", GOSSIP_SENDER_MENU_SUB, 1020117);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Bow_16:30:30:-18|t Waffe Bogen|r", GOSSIP_SENDER_MENU_SUB, 1020215);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Rifle_07:30:30:-18|t Waffe Schusswaffen|r", GOSSIP_SENDER_MENU_SUB, 1020326);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_03:30:30:-18|t Waffe Einhandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020413);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Mace_24:30:30:-18|t Waffe Zweihandstreitkolbenn|r", GOSSIP_SENDER_MENU_SUB, 1020517);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Halbard_01:30:30:-18|t Waffe Stangenwaffen|r", GOSSIP_SENDER_MENU_SUB, 1020617);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_04:30:30:-18|t Waffe Einhandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020713);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Sword_102:30:30:-18|t Waffe Zweihandschwerter|r", GOSSIP_SENDER_MENU_SUB, 1020817);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Staff_07:30:30:-18|t Waffe Stäbe|r", GOSSIP_SENDER_MENU_SUB, 1021017);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Hand_07:30:30:-18|t Waffe Faustwaffen|r", GOSSIP_SENDER_MENU_SUB, 1021313);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_ShortBlade_10:30:30:-18|t Waffe Dolche|r", GOSSIP_SENDER_MENU_SUB, 1021513);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_ThrowingKnife_02:30:30:-18|t Waffe Wurfwaffe|r", GOSSIP_SENDER_MENU_SUB, 1021625);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Weapon_Crossbow_23:30:30:-18|t Waffe Armbrueste|r", GOSSIP_SENDER_MENU_SUB, 1021826);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Wand_05:30:30:-18|t Waffe Zauberstaebe|r", GOSSIP_SENDER_MENU_SUB, 1021926);
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\INV_Fishingpole_02:30:30:-18|t Waffe Angelruten|r", GOSSIP_SENDER_MENU_SUB, 1022017);
					}
					if (player->getClass() == 12)// -- Daemonenjaeger
					{
						AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff404040|TInterface\\icons\\Ability_Creature_Cursed_02:30:30:-18|t Daemonenjaeger unterstuetze ich noch nicht|r", GOSSIP_SENDER_MENU_SUB, 9999997);
					}
					AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MENU_SUB, 9999997);
					SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				}
			}
			break;
			case GOSSIP_SENDER_MENU_SUB:
			{
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
					DBdata_filter(player, tclass, tsubclass, tinventorytype, tinventorytypeB, tinventorytypeC);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
			}
			break;
			case GOSSIP_SENDER_MENU_GIVE:
			{
				// --- Subsubmenu (Hauptmenu)
				if (action == 999997)
				{
					StartIndex = 0;
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					break;
				}
				// --- Subsubmenu (weiter)
				if (action == 999998)
				{
					StartIndex = StartIndex + 25;
					if (StartIndex > NPC_GIVER_Ilevel_DATA_filtered.size())
						StartIndex = 0;
					OnGossipSelect_Sub(player, creature, StartIndex);
					break;
				}
				// --- Subsubmenu (zurueck)
				if (action == 999999)
				{
					StartIndex = StartIndex - 25;
					if (StartIndex < 0)
						StartIndex = 0;
					OnGossipSelect_Sub(player, creature, StartIndex);
					break;
				}
				// --- SubSubmenu (auswahl)
				if (action > 100000 && action < 999997)
				{
					uint32 tindex = (action - 100000);
					if (tindex <= 0 || NPC_GIVER_Ilevel_DATA_filtered[tindex] <= 0)
					{
						creature->Say("Diesen Gegenstand habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					}
					else
					{
						if (player->HasItemCount(NPC_GIVER_Ilevel_DATA_filtered[tindex], 1, true))
						{
							creature->Say("Du hast bereits den Gegenstand. Nochmal geht leider nicht !", LANG_UNIVERSAL, NULL);
						}
						else
						{
							player->AddItem(NPC_GIVER_Ilevel_DATA_filtered[tindex], 1);
							creature->Say("Ich habe Dir den gewuenschten Gegenstand gegeben.", LANG_UNIVERSAL, NULL);

						}
					}
					player->PlayerTalkClass->ClearMenus();
					CloseGossipMenuFor(player);
					OnGossipSelect_Sub(player, creature, StartIndex);
					break;
				}
				break;
			}
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
		uint32 MaxIndex = NPC_GIVER_Ilevel_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Ilevel_DATA_filtered[i]);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff" + NPC_GIVER_Ilevel_DATA_quality[item_template->Quality] + "(*)|cff000000|t " + item_template->Name1 + "|r", GOSSIP_SENDER_MENU_GIVE, (100000 + i));
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
	};//ShowNPC_GIVER_Ilevel_DATA
	// ******************************************************************************
	// DBdata_filter
	// ******************************************************************************
	void DBdata_filter(Player* player, uint32 t_class, uint32 t_subclass, uint32 t_inventorytype, uint32 t_inventorytypeB, uint32 t_inventorytypeC)
	{
		if (t_class == 2)
		{
			NPC_GIVER_Ilevel_DATA_filtered.clear();
			uint32 MaxIndex = NPC_GIVER_Ilevel_DATA_2.size();
			uint32 j = 0;
			for (uint32 i = 0; i < MaxIndex; i++)
			{
				if (NPC_GIVER_Ilevel_DATA_2[i] > 0)
				{
					if (ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Ilevel_DATA_2[i]))
					{
						if (!(item_template->AllowableRace & player->getRaceMask()))
							continue;
						if (!(item_template->AllowableClass & player->getClassMask()))
							continue;
						if (item_template->SubClass != t_subclass)
							continue;
						if (item_template->InventoryType != t_inventorytype && item_template->InventoryType != t_inventorytypeB && item_template->InventoryType != t_inventorytypeC)
							continue;
						// ---
						NPC_GIVER_Ilevel_DATA_filtered.push_back(NPC_GIVER_Ilevel_DATA_2[i]);
						++j;
					}//if ItemTemplate
				}//if > 0
			}//for
		}// if t_class == 2
		if (t_class == 4)
		{
			NPC_GIVER_Ilevel_DATA_filtered.clear();
			uint32 MaxIndex = NPC_GIVER_Ilevel_DATA_4.size();
			for (uint32 i = 0; i < MaxIndex; i++)
			{
				if (NPC_GIVER_Ilevel_DATA_4[i] > 0)
				{
					if (ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Ilevel_DATA_4[i]))
					{
						if (!(item_template->AllowableRace & player->getRaceMask()))
							continue;
						if (!(item_template->AllowableClass & player->getClassMask()))
							continue;
						if (item_template->SubClass != t_subclass)
							continue;
						if (item_template->InventoryType != t_inventorytype && item_template->InventoryType != t_inventorytypeB && item_template->InventoryType != t_inventorytypeC)
							continue;
						// ---
						NPC_GIVER_Ilevel_DATA_filtered.push_back(NPC_GIVER_Ilevel_DATA_4[i]);
					}//if ItemTemplate
				}//if > 0
			}//for
		}// if t_class == 4
	};//DBdata_filter
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GIVER_Ilevel()
{
	new NPC_GIVER_Ilevel();
};