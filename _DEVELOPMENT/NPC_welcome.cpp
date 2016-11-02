/*
//Trinitycore//
Author : Philippe
Created for : Power-Arena
Shared By the Administrator of Power-Arena
Welcome NPC
//ArcEmu//
Author : ??
Lua Version : ??
DELETE FROM `creature_template` WHERE (`entry`=100010);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (100010, 0, 0, 0, 0, 0, 31119, 0, 0, 0, 'Welcome', 'Power-Arena', '', 0, 82, 82, 2, 35, 35, 3, 2, 2, 0.3, 3, 511, 612, 0, 337, 23, 1500, 1500, 2, 0, 0, 0, 0, 0, 0, 0, 331, 512, 1000, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1000000, 1000000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1073741823, 0, 'npc_welcome', 12340);
*/
#include "ScriptPCH.h"
enum eIcons
{
	CHAT_ICON = 0,
	VENDOR_ICON = 1,
	FLIGHT_ICON = 2,
	TRAINER_ICON = 3,
	GEAR_ICON = 4,
	GEAR_ICON_2 = 5,
	BANK_ICON = 6,
	CHAT_DOTS_ICON = 7,
	TABARD_ICON = 8,
	SWORDS_ICON = 9,
	GOLD_DOT_ICON = 10
};

class npc_welcome : public CreatureScript
{
public:
	npc_welcome() : CreatureScript("npc_welcome") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{

		{
			player->PrepareQuestMenu(creature->GetGUID());
			player->SendPreparedQuest(creature->GetGUID());
		}
		player->ADD_GOSSIP_ITEM(TRAINER_ICON, ">>", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
	{
		player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
		player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());

		switch (player->getClass())
		{
		case CLASS_WARRIOR:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(7384, false),
					player->learnSpell(47436, false),
					player->learnSpell(47450, false),
					player->learnSpell(11578, false),
					player->learnSpell(47465, false),
					player->learnSpell(47502, false),
					player->learnSpell(34428, false),
					player->learnSpell(1715, false),
					player->learnSpell(2687, false),
					player->learnSpell(71, false),
					player->learnSpell(7386, false),
					player->learnSpell(355, false),
					player->learnSpell(72, false),
					player->learnSpell(47437, false),
					player->learnSpell(57823, false),
					player->learnSpell(694, false),
					player->learnSpell(2565, false),
					player->learnSpell(676, false),
					player->learnSpell(47520, false),
					player->learnSpell(20230, false),
					player->learnSpell(12678, false),
					player->learnSpell(47471, false),
					player->learnSpell(1161, false),
					player->learnSpell(871, false),
					player->learnSpell(2458, false),
					player->learnSpell(20252, false),
					player->learnSpell(47475, false),
					player->learnSpell(18499, false),
					player->learnSpell(1680, false),
					player->learnSpell(6552, false),
					player->learnSpell(47488, false),
					player->learnSpell(1719, false),
					player->learnSpell(23920, false),
					player->learnSpell(47440, false),
					player->learnSpell(3411, false),
					player->learnSpell(64382, false),
					player->learnSpell(55694, false),
					player->learnSpell(57755, false),
					player->learnSpell(42459, false),
					player->learnSpell(750, false),
					player->learnSpell(5246, false);
				player->learnSpell(3127, false);
				player->SaveToDB();
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				/////////ARRMES/////////////
				player->learnSpell(750, false);
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->learnSpell(264, false);
				player->learnSpell(5011, false);
				player->learnSpell(266, false);
				player->learnSpell(2567, false);
				player->SaveToDB();
			}
			//////////////Restriction/////////////////
			if (player->HasSpell(12294))
			{
				player->learnSpell(47486, false);
			}
			//////////////Vengeur////////////////////
			if (player->HasSpell(20243))
			{
				player->learnSpell(47498, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			///////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_PALADIN:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(3127, false);
				player->learnSpell(19746, false);
				player->learnSpell(19752, false);
				player->learnSpell(750, false);
				player->learnSpell(48942, false);
				player->learnSpell(48782, false);
				player->learnSpell(48932, false);
				player->learnSpell(20271, false);
				player->learnSpell(498, false);
				player->learnSpell(10308, false);
				player->learnSpell(1152, false);
				player->learnSpell(10278, false);
				player->learnSpell(48788, false);
				player->learnSpell(53408, false);
				player->learnSpell(48950, false);
				player->learnSpell(48936, false);
				player->learnSpell(31789, false);
				player->learnSpell(62124, false);
				player->learnSpell(54043, false);
				player->learnSpell(25780, false);
				player->learnSpell(1044, false);
				player->learnSpell(20217, false);
				player->learnSpell(48819, false);
				player->learnSpell(48801, false);
				player->learnSpell(48785, false);
				player->learnSpell(5502, false);
				player->learnSpell(20164, false);
				player->learnSpell(10326, false);
				player->learnSpell(1038, false);
				player->learnSpell(53407, false);
				player->learnSpell(48943, false);
				player->learnSpell(20165, false);
				player->learnSpell(48945, false);
				player->learnSpell(642, false);
				player->learnSpell(48947, false);
				player->learnSpell(20166, false);
				player->learnSpell(4987, false);
				player->learnSpell(48806, false);
				player->learnSpell(6940, false);
				player->learnSpell(48817, false);
				player->learnSpell(48934, false);
				player->learnSpell(48938, false);
				player->learnSpell(25898, false);
				player->learnSpell(32223, false);
				player->learnSpell(31884, false);
				player->learnSpell(54428, false);
				player->learnSpell(61411, false);
				player->learnSpell(53601, false);
				player->learnSpell(33388, false);
				player->learnSpell(33391, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				/////////ARRMES/////////////
				player->learnSpell(750, false);
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->SaveToDB();
			}
			//////////////Restriction/////////////////
			if (player->HasSpell(20925))
			{
				player->learnSpell(48952, false);
			}
			//////////////Vengeur////////////////////
			if (player->HasSpell(12294))
			{
				player->learnSpell(48827, false);
			}
			//////////////Bene/////////////////////
			if (player->HasSpell(20911))
			{
				player->learnSpell(25899, false);
			}
			/////////////Horion/////////////////////
			if (player->HasSpell(20473))
			{
				player->learnSpell(48825, false);
			}
			////////////////////////////////////////
			if (player->GetTeam() == ALLIANCE) {
				player->learnSpell(31801, false);
				player->learnSpell(13819, false);
				player->learnSpell(23214, false);
			}
			else
			{
				player->learnSpell(53736, false);
				player->learnSpell(34769, false);
				player->learnSpell(34767, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			///////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_HUNTER:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(3043, false);
				player->learnSpell(3127, false);
				player->learnSpell(3045, false);
				player->learnSpell(3034, false);
				player->learnSpell(8737, false);
				player->learnSpell(1494, false);
				player->learnSpell(13163, false);
				player->learnSpell(48996, false);
				player->learnSpell(49001, false);
				player->learnSpell(49045, false);
				player->learnSpell(53338, false);
				player->learnSpell(5116, false);
				player->learnSpell(27044, false);
				player->learnSpell(883, false);
				player->learnSpell(2641, false);
				player->learnSpell(6991, false);
				player->learnSpell(982, false);
				player->learnSpell(1515, false);
				player->learnSpell(19883, false);
				player->learnSpell(20736, false);
				player->learnSpell(48990, false);
				player->learnSpell(2974, false);
				player->learnSpell(6197, false);
				player->learnSpell(1002, false);
				player->learnSpell(14327, false);
				player->learnSpell(5118, false);
				player->learnSpell(49056, false);
				player->learnSpell(53339, false);
				player->learnSpell(49048, false);
				player->learnSpell(19884, false);
				player->learnSpell(34074, false);
				player->learnSpell(781, false);
				player->learnSpell(14311, false);
				player->learnSpell(1462, false);
				player->learnSpell(19885, false);
				player->learnSpell(19880, false);
				player->learnSpell(13809, false);
				player->learnSpell(13161, false);
				player->learnSpell(5384, false);
				player->learnSpell(1543, false);
				player->learnSpell(19878, false);
				player->learnSpell(49067, false);
				player->learnSpell(3034, false);
				player->learnSpell(13159, false);
				player->learnSpell(19882, false);
				player->learnSpell(58434, false);
				player->learnSpell(49071, false);
				player->learnSpell(49052, false);
				player->learnSpell(19879, false);
				player->learnSpell(19263, false);
				player->learnSpell(19801, false);
				player->learnSpell(34026, false);
				player->learnSpell(34600, false);
				player->learnSpell(34477, false);
				player->learnSpell(61006, false);
				player->learnSpell(61847, false);
				player->learnSpell(53271, false);
				player->learnSpell(60192, false);
				player->learnSpell(62757, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				/////////ARRMES/////////////
				player->learnSpell(15590, false);
				player->learnSpell(8737, false);
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(200, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->learnSpell(264, false);
				player->learnSpell(266, false);
				player->learnSpell(5011, false);
				player->learnSpell(42459, false);
				player->SaveToDB();
			}
			//////////////Restriction/////////////////
			if (player->HasSpell(19386))
			{
				player->learnSpell(49012, false);
			}
			//////////////////////////////////
			if (player->HasSpell(53301))
			{
				player->learnSpell(60053, false);
			}
			///////////////////////////////////
			if (player->HasSpell(19306))
			{
				player->learnSpell(48999, false);
			}
			//////////////////////////////////
			if (player->HasSpell(19434))
			{
				player->learnSpell(49050, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			///////////////////////////////////////////////////////////////////////
		case CLASS_MAGE:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(42921, false);
				player->learnSpell(42842, false);
				player->learnSpell(42995, false);
				player->learnSpell(42833, false);
				player->learnSpell(27090, false);
				player->learnSpell(33717, false);
				player->learnSpell(42873, false);
				player->learnSpell(42846, false);
				player->learnSpell(12826, false);
				player->learnSpell(28271, false);
				player->learnSpell(61780, false);
				player->learnSpell(61721, false);
				player->learnSpell(28272, false);
				player->learnSpell(42917, false);
				player->learnSpell(43015, false);
				player->learnSpell(130, false);
				player->learnSpell(42926, false);
				player->learnSpell(43017, false);
				player->learnSpell(475, false);
				player->learnSpell(1953, false);
				player->learnSpell(42940, false);
				player->learnSpell(12051, false);
				player->learnSpell(43010, false);
				player->learnSpell(43020, false);
				player->learnSpell(43012, false);
				player->learnSpell(42859, false);
				player->learnSpell(2139, false);
				player->learnSpell(42931, false);
				player->learnSpell(42985, false);
				player->learnSpell(43008, false);
				player->learnSpell(45438, false);
				player->learnSpell(43024, false);
				player->learnSpell(43002, false);
				player->learnSpell(43046, false);
				player->learnSpell(42897, false);
				player->learnSpell(42914, false);
				player->learnSpell(66, false);
				player->learnSpell(58659, false);
				player->learnSpell(30449, false);
				player->learnSpell(42956, false);
				player->learnSpell(47610, false);
				player->learnSpell(61316, false);
				player->learnSpell(61024, false);
				player->learnSpell(55342, false);
				player->learnSpell(53142, false);
				player->learnSpell(7301, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				/////////ARRMES/////////////
				player->learnSpell(201, false);
				player->learnSpell(196, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->SaveToDB();
			}
			//////////////Restriction/////////////////
			if (player->GetTeam() == ALLIANCE) {
				player->learnSpell(32271, false);
				player->learnSpell(49359, false);
				player->learnSpell(3565, false);
				player->learnSpell(33690, false);
				player->learnSpell(3562, false);
				player->learnSpell(3561, false);
				player->learnSpell(11419, false);
				player->learnSpell(32266, false);
				player->learnSpell(11416, false);
				player->learnSpell(33691, false);
				player->learnSpell(49360, false);
			}
			else
			{
				player->learnSpell(3567, false);
				player->learnSpell(35715, false);
				player->learnSpell(3566, false);
				player->learnSpell(49358, false);
				player->learnSpell(32272, false);
				player->learnSpell(3563, false);
				player->learnSpell(11417, false);
				player->learnSpell(35717, false);
				player->learnSpell(32267, false);
				player->learnSpell(49361, false);
				player->learnSpell(11420, false);
				player->learnSpell(11418, false);
			}
			if (player->HasSpell(11366))
			{
				player->learnSpell(42891, false);
			}
			//////////////////////////////////
			if (player->HasSpell(11426))
			{
				player->learnSpell(43039, false);
			}
			///////////////////////////////////
			if (player->HasSpell(44457))
			{
				player->learnSpell(55360, false);
			}
			//////////////////////////////////
			if (player->HasSpell(31661))
			{
				player->learnSpell(42950, false);
			}
			//////////////////////////////////
			if (player->HasSpell(11113))
			{
				player->learnSpell(42945, false);
			}
			//////////////////////////////////
			if (player->HasSpell(44425))
			{
				player->learnSpell(44781, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			//////////////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_WARLOCK:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(696, false);
				player->learnSpell(47811, false);
				player->learnSpell(47809, false);
				player->learnSpell(688, false);
				player->learnSpell(47813, false);
				player->learnSpell(50511, false);
				player->learnSpell(57946, false);
				player->learnSpell(47864, false);
				player->learnSpell(6215, false);
				player->learnSpell(47878, false);
				player->learnSpell(47855, false);
				player->learnSpell(697, false);
				player->learnSpell(47856, false);
				player->learnSpell(47857, false);
				player->learnSpell(5697, false);
				player->learnSpell(47884, false);
				player->learnSpell(47815, false);
				player->learnSpell(47889, false);
				player->learnSpell(47820, false);
				player->learnSpell(698, false);
				player->learnSpell(712, false);
				player->learnSpell(126, false);
				player->learnSpell(5138, false);
				player->learnSpell(5500, false);
				player->learnSpell(11719, false);
				player->learnSpell(132, false);
				player->learnSpell(60220, false);
				player->learnSpell(18647, false);
				player->learnSpell(61191, false);
				player->learnSpell(47823, false);
				player->learnSpell(691, false);
				player->learnSpell(47865, false);
				player->learnSpell(47891, false);
				player->learnSpell(47888, false);
				player->learnSpell(17928, false);
				player->learnSpell(47860, false);
				player->learnSpell(47825, false);
				player->learnSpell(1122, false);
				player->learnSpell(47867, false);
				player->learnSpell(18540, false);
				player->learnSpell(47893, false);
				player->learnSpell(47838, false);
				player->learnSpell(29858, false);
				player->learnSpell(58887, false);
				player->learnSpell(47836, false);
				player->learnSpell(61290, false);
				player->learnSpell(48018, false);
				player->learnSpell(48020, false);
				player->learnSpell(33388, false);
				player->learnSpell(33391, false);
				player->learnSpell(23161, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				///////////ARMES/////////////
				player->learnSpell(196, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->SaveToDB();
			}
			//////////////Restriction/////////////////
			if (player->HasSpell(17877))
			{
				player->learnSpell(47827, false);
			}
			//////////////////////////////////
			if (player->HasSpell(30283))
			{
				player->learnSpell(47847, false);
			}
			///////////////////////////////////
			if (player->HasSpell(30108))
			{
				player->learnSpell(47843, false);
			}
			//////////////////////////////////
			if (player->HasSpell(50796))
			{
				player->learnSpell(59172, false);
			}
			//////////////////////////////////
			if (player->HasSpell(48181))
			{
				player->learnSpell(59164, false);
			}
			//////////////////////////////////
			if (player->HasSpell(18220))
			{
				player->learnSpell(59092, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_ROGUE:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(3127, false);
				player->learnSpell(42459, false);
				player->learnSpell(48668, false);
				player->learnSpell(48638, false);
				player->learnSpell(1784, false);
				player->learnSpell(48657, false);
				player->learnSpell(921, false);
				player->learnSpell(1776, false);
				player->learnSpell(26669, false);
				player->learnSpell(51724, false);
				player->learnSpell(6774, false);
				player->learnSpell(11305, false);
				player->learnSpell(1766, false);
				player->learnSpell(48676, false);
				player->learnSpell(48659, false);
				player->learnSpell(1804, false);
				player->learnSpell(8647, false);
				player->learnSpell(48691, false);
				player->learnSpell(51722, false);
				player->learnSpell(48672, false);
				player->learnSpell(1725, false);
				player->learnSpell(26889, false);
				player->learnSpell(2836, false);
				player->learnSpell(1833, false);
				player->learnSpell(1842, false);
				player->learnSpell(8643, false);
				player->learnSpell(2094, false);
				player->learnSpell(1860, false);
				player->learnSpell(57993, false);
				player->learnSpell(48674, false);
				player->learnSpell(31224, false);
				player->learnSpell(5938, false);
				player->learnSpell(57934, false);
				player->learnSpell(51723, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				///////////ARMES/////////////
				player->learnSpell(196, false);
				player->learnSpell(198, false);
				player->learnSpell(201, false);
				player->learnSpell(1180, false);
				player->learnSpell(2567, false);
				player->learnSpell(264, false);
				player->learnSpell(266, false);
				player->learnSpell(5011, false);
				player->learnSpell(15590, false);
				player->SaveToDB();
			}
			//////////////Restriction///////////
			if (player->HasSpell(16511))
			{
				player->learnSpell(48660, false);
			}
			//////////////////////////////////
			if (player->HasSpell(1329))
			{
				player->learnSpell(48666, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_PRIEST:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(528, false);
				player->learnSpell(2053, false);
				player->learnSpell(48161, false);
				player->learnSpell(48123, false);
				player->learnSpell(48125, false);
				player->learnSpell(48066, false);
				player->learnSpell(586, false);
				player->learnSpell(48068, false);
				player->learnSpell(48127, false);
				player->learnSpell(48171, false);
				player->learnSpell(48168, false);
				player->learnSpell(10890, false);
				player->learnSpell(6064, false);
				player->learnSpell(988, false);
				player->learnSpell(48300, false);
				player->learnSpell(6346, false);
				player->learnSpell(48071, false);
				player->learnSpell(48135, false);
				player->learnSpell(48078, false);
				player->learnSpell(453, false);
				player->learnSpell(10955, false);
				player->learnSpell(10909, false);
				player->learnSpell(8129, false);
				player->learnSpell(48073, false);
				player->learnSpell(605, false);
				player->learnSpell(48072, false);
				player->learnSpell(48169, false);
				player->learnSpell(552, false);
				player->learnSpell(1706, false);
				player->learnSpell(48063, false);
				player->learnSpell(48162, false);
				player->learnSpell(48170, false);
				player->learnSpell(48074, false);
				player->learnSpell(48158, false);
				player->learnSpell(48120, false);
				player->learnSpell(34433, false);
				player->learnSpell(48113, false);
				player->learnSpell(32375, false);
				player->learnSpell(64843, false);
				player->learnSpell(64901, false);
				player->learnSpell(53023, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				///////////ARMES/////////////
				player->learnSpell(196, false);
				player->learnSpell(198, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->SaveToDB();
			}
			//////////////Restriction///////////
			if (player->HasSpell(34914))
			{
				player->learnSpell(48160, false);
			}
			//////////////////////////////////
			if (player->HasSpell(47540))
			{
				player->learnSpell(53007, false);
			}
			//////////////////////////////////
			if (player->HasSpell(724))
			{
				player->learnSpell(48087, false);
			}
			//////////////////////////////////
			if (player->HasSpell(19236))
			{
				player->learnSpell(48173, false);
			}
			//////////////////////////////////
			if (player->HasSpell(34861))
			{
				player->learnSpell(48089, false);
			}
			//////////////////////////////////
			if (player->HasSpell(15407))
			{
				player->learnSpell(48156, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_DEATH_KNIGHT:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(3127, false);
				player->learnSpell(50842, false);
				player->learnSpell(49941, false);
				player->learnSpell(49930, false);
				player->learnSpell(47476, false);
				player->learnSpell(45529, false);
				player->learnSpell(3714, false);
				player->learnSpell(56222, false);
				player->learnSpell(48743, false);
				player->learnSpell(48263, false);
				player->learnSpell(49909, false);
				player->learnSpell(47528, false);
				player->learnSpell(45524, false);
				player->learnSpell(48792, false);
				player->learnSpell(57623, false);
				player->learnSpell(56815, false);
				player->learnSpell(47568, false);
				player->learnSpell(49895, false);
				player->learnSpell(50977, false);
				player->learnSpell(49576, false);
				player->learnSpell(49921, false);
				player->learnSpell(46584, false);
				player->learnSpell(49938, false);
				player->learnSpell(48707, false);
				player->learnSpell(48265, false);
				player->learnSpell(61999, false);
				player->learnSpell(42650, false);
				player->learnSpell(53428, false);
				player->learnSpell(53331, false);
				player->learnSpell(54447, false);
				player->learnSpell(53342, false);
				player->learnSpell(54446, false);
				player->learnSpell(53323, false);
				player->learnSpell(53344, false);
				player->learnSpell(70164, false);
				player->learnSpell(62158, false);
				player->learnSpell(33391, false);
				player->learnSpell(48778, false);
				player->learnSpell(51425, false);
				player->learnSpell(49924, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				///////////ARMES/////////////
				player->learnSpell(750, false);
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->SaveToDB();
			}
			//////////////Restriction///////////
			if (player->HasSpell(55050))
			{
				player->learnSpell(55262, false);
			}
			//////////////////////////////////
			if (player->HasSpell(49143))
			{
				player->learnSpell(55268, false);
			}
			//////////////////////////////////
			if (player->HasSpell(49184))
			{
				player->learnSpell(51411, false);
			}
			//////////////////////////////////
			if (player->HasSpell(55090))
			{
				player->learnSpell(55271, false);
			}
			//////////////////////////////////
			if (player->HasSpell(49158))
			{
				player->learnSpell(51328, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_SHAMAN:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(2062, false);
				player->learnSpell(8737, false);
				player->learnSpell(49273, false);
				player->learnSpell(49238, false);
				player->learnSpell(10399, false);
				player->learnSpell(49231, false);
				player->learnSpell(58753, false);
				player->learnSpell(2484, false);
				player->learnSpell(49281, false);
				player->learnSpell(58582, false);
				player->learnSpell(49233, false);
				player->learnSpell(58790, false);
				player->learnSpell(58704, false);
				player->learnSpell(58643, false);
				player->learnSpell(49277, false);
				player->learnSpell(61657, false);
				player->learnSpell(8012, false);
				player->learnSpell(526, false);
				player->learnSpell(2645, false);
				player->learnSpell(57994, false);
				player->learnSpell(8143, false);
				player->learnSpell(49236, false);
				player->learnSpell(58796, false);
				player->learnSpell(58757, false);
				player->learnSpell(49276, false);
				player->learnSpell(57960, false);
				player->learnSpell(131, false);
				player->learnSpell(58745, false);
				player->learnSpell(6196, false);
				player->learnSpell(58734, false);
				player->learnSpell(58774, false);
				player->learnSpell(58739, false);
				player->learnSpell(58656, false);
				player->learnSpell(546, false);
				player->learnSpell(556, false);
				player->learnSpell(66842, false);
				player->learnSpell(51994, false);
				player->learnSpell(8177, false);
				player->learnSpell(58749, false);
				player->learnSpell(20608, false);
				player->learnSpell(36936, false);
				player->learnSpell(36936, false);
				player->learnSpell(58804, false);
				player->learnSpell(49271, false);
				player->learnSpell(8512, false);
				player->learnSpell(6495, false);
				player->learnSpell(8170, false);
				player->learnSpell(66843, false);
				player->learnSpell(55459, false);
				player->learnSpell(66844, false);
				player->learnSpell(3738, false);
				player->learnSpell(2894, false);
				player->learnSpell(60043, false);
				player->learnSpell(51514, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				///////////ARMES/////////////
				player->learnSpell(8737, false);
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(227, false);
				player->learnSpell(15590, false);
				player->SaveToDB();
			}
			//////////////Restriction///////////
			//Faction
			if (player->GetTeam() == ALLIANCE) {
				player->learnSpell(32182, false);
			}
			else
			{
				player->learnSpell(2825, false);
			}
			//////////////////////////////////
			if (player->HasSpell(61295))
			{
				player->learnSpell(61301, false);
			}
			//////////////////////////////////
			if (player->HasSpell(974))
			{
				player->learnSpell(49284, false);
			}
			//////////////////////////////////
			if (player->HasSpell(30706))
			{
				player->learnSpell(57722, false);
			}
			//////////////////////////////////
			if (player->HasSpell(51490))
			{
				player->learnSpell(59159, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->PlayerTalkClass->SendCloseGossip();
			break;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CLASS_DRUID:
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
				player->learnSpell(48378, false);
				player->learnSpell(48469, false);
				player->learnSpell(48461, false);
				player->learnSpell(48463, false);
				player->learnSpell(48441, false);
				player->learnSpell(53307, false);
				player->learnSpell(53308, false);
				player->learnSpell(5487, false);
				player->learnSpell(48560, false);
				player->learnSpell(6795, false);
				player->learnSpell(48480, false);
				player->learnSpell(53312, false);
				player->learnSpell(18960, false);
				player->learnSpell(5229, false);
				player->learnSpell(48443, false);
				player->learnSpell(50763, false);
				player->learnSpell(8983, false);
				player->learnSpell(8946, false);
				player->learnSpell(1066, false);
				player->learnSpell(48562, false);
				player->learnSpell(783, false);
				player->learnSpell(770, false);
				player->learnSpell(16857, false);
				player->learnSpell(18658, false);
				player->learnSpell(768, false);
				player->learnSpell(1082, false);
				player->learnSpell(16979, false);
				player->learnSpell(49376, false);
				player->learnSpell(5215, false);
				player->learnSpell(48477, false);
				player->learnSpell(49800, false);
				player->learnSpell(48465, false);
				player->learnSpell(48572, false);
				player->learnSpell(26995, false);
				player->learnSpell(48574, false);
				player->learnSpell(2782, false);
				player->learnSpell(50213, false);
				player->learnSpell(2893, false);
				player->learnSpell(33357, false);
				player->learnSpell(5209, false);
				player->learnSpell(48575, false);
				player->learnSpell(48447, false);
				player->learnSpell(48577, false);
				player->learnSpell(48579, false);
				player->learnSpell(5225, false);
				player->learnSpell(22842, false);
				player->learnSpell(49803, false);
				player->learnSpell(9634, false);
				player->learnSpell(20719, false);
				player->learnSpell(48467, false);
				player->learnSpell(29166, false);
				player->learnSpell(62600, false);
				player->learnSpell(22812, false);
				player->learnSpell(48470, false);
				player->learnSpell(48564, false);
				player->learnSpell(48566, false);
				player->learnSpell(33943, false);
				player->learnSpell(49802, false);
				player->learnSpell(48451, false);
				player->learnSpell(48568, false);
				player->learnSpell(33786, false);
				player->learnSpell(40120, false);
				player->learnSpell(62078, false);
				player->learnSpell(52610, false);
				player->learnSpell(50464, false);
				player->learnSpell(48570, false);
				player->learnSpell(34093, false);
				player->learnSpell(33392, false);
				player->learnSpell(54197, false);
				player->SaveToDB();
				///////////ARMES/////////////
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(227, false);
				player->SaveToDB();
			}
			//////////////Restriction///////////
			if (player->HasSpell(50516))
			{
				player->learnSpell(61384, false);
			}
			//////////////////////////////////
			if (player->HasSpell(48505))
			{
				player->learnSpell(53201, false);
			}
			//////////////////////////////////
			if (player->HasSpell(48438))
			{
				player->learnSpell(53251, false);
			}
			//////////////////////////////////
			if (player->HasSpell(5570))
			{
				player->learnSpell(48468, false);
			}
			player->UpdateSkillsToMaxSkillsForLevel();
			player->SaveToDB();
			player->PlayerTalkClass->SendCloseGossip();
			break;

		case 15:
			player->PlayerTalkClass->SendCloseGossip();
			break;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}

		return true;
	}
};
void AddSC_npc_welcome()
{
	new npc_welcome();
}