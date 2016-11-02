/*
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (99999, 0, 0, 0, 0, 0, 18239, 0, 0, 0, 'Brewfest Title System', 'Title NPC', NULL, 0, 80, 80, 0, 35, 35, 1, 1, 1.14286, 0.25, 3, 500, 5000, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'Title_NPC', 0);
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `WDBVerified`) VALUES (20000, 'Title cost: 800 Brewfest Tokens!', '', 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 1);
*/

#include "ScriptPCH.h"

enum enums
{
	TITLE_TOKEN = 37829,
	TITLE_PRICE = 800,
};

class Title_NPC : public CreatureScript
{
public:
	Title_NPC() : CreatureScript("Title_NPC") { }
	bool OnGossipHello(Player * Player, Creature * Creature)
	{
		if (Player->GetTeam() == ALLIANCE)
		{
			Player->ADD_GOSSIP_ITEM(4, "Alliance Titles", GOSSIP_SENDER_MAIN, 0);
		}
		else
		{
			Player->ADD_GOSSIP_ITEM(4, "Horde Titles", GOSSIP_SENDER_MAIN, 1);
		}
		Player->PlayerTalkClass->SendGossipMenu(20000, Creature->GetGUID());
		return true;
	}
	bool OnGossipSelect(Player * Player, Creature * Creature, uint32 sender, uint32 uiAction)
	{

		std::string name;
		name = Player->GetName();

		if (sender == GOSSIP_SENDER_MAIN)
		{
			Player->PlayerTalkClass->ClearMenus();
			switch (uiAction)
			{
				{
			case 0:
				Player->ADD_GOSSIP_ITEM(4, name + " Hand of A'dal", GOSSIP_SENDER_MAIN, 2);
				Player->ADD_GOSSIP_ITEM(4, name + " the Seeker", GOSSIP_SENDER_MAIN, 4);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Ten Storms", GOSSIP_SENDER_MAIN, 6);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Emerald Dream", GOSSIP_SENDER_MAIN, 7);
				Player->ADD_GOSSIP_ITEM(4, name + " of Khaz Modan", GOSSIP_SENDER_MAIN, 11);
				Player->ADD_GOSSIP_ITEM(4, name + " the Lion Hearted", GOSSIP_SENDER_MAIN, 12);
				Player->ADD_GOSSIP_ITEM(4, name + " the Forsaken", GOSSIP_SENDER_MAIN, 13);
				Player->ADD_GOSSIP_ITEM(4, name + " the Magic Seeker", GOSSIP_SENDER_MAIN, 14);
				Player->ADD_GOSSIP_ITEM(4, name + " the Love Fool", GOSSIP_SENDER_MAIN, 16);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Nightfall", GOSSIP_SENDER_MAIN, 17);
				Player->ADD_GOSSIP_ITEM(4, name + " the Immortal", GOSSIP_SENDER_MAIN, 18);
				Player->ADD_GOSSIP_ITEM(4, name + " the Undying", GOSSIP_SENDER_MAIN, 19);
				Player->ADD_GOSSIP_ITEM(4, name + " the Insane", GOSSIP_SENDER_MAIN, 21);
				Player->ADD_GOSSIP_ITEM(4, name + " the Astral Walker", GOSSIP_SENDER_MAIN, 23);
				Player->ADD_GOSSIP_ITEM(4, name + " Herald of the Titans", GOSSIP_SENDER_MAIN, 24);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Alliance", GOSSIP_SENDER_MAIN, 27);
				Player->ADD_GOSSIP_ITEM(4, "Justicar " + name, GOSSIP_SENDER_MAIN, 25);
				Player->ADD_GOSSIP_ITEM(4, "Flame Keeper " + name, GOSSIP_SENDER_MAIN, 3);
				Player->ADD_GOSSIP_ITEM(4, "Arena Master " + name, GOSSIP_SENDER_MAIN, 5);
				Player->ADD_GOSSIP_ITEM(4, "Stalker " + name, GOSSIP_SENDER_MAIN, 8);
				Player->ADD_GOSSIP_ITEM(4, "Assassin " + name, GOSSIP_SENDER_MAIN, 9);
				Player->ADD_GOSSIP_ITEM(4, "Doctor " + name, GOSSIP_SENDER_MAIN, 10);
				Player->ADD_GOSSIP_ITEM(4, "Merrymaker " + name, GOSSIP_SENDER_MAIN, 15);
				Player->ADD_GOSSIP_ITEM(4, "Bloodsail Admiral " + name, GOSSIP_SENDER_MAIN, 20);
				Player->ADD_GOSSIP_ITEM(4, "Starcaller " + name, GOSSIP_SENDER_MAIN, 22);
				Player->PlayerTalkClass->SendGossipMenu(20000, Creature->GetGUID());
				break;

			case 1:
				Player->ADD_GOSSIP_ITEM(4, name + " Hand of A'dal", GOSSIP_SENDER_MAIN, 2);
				Player->ADD_GOSSIP_ITEM(4, name + " the Seeker", GOSSIP_SENDER_MAIN, 4);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Ten Storms", GOSSIP_SENDER_MAIN, 6);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Emerald Dream", GOSSIP_SENDER_MAIN, 7);
				Player->ADD_GOSSIP_ITEM(4, name + " of Khaz Modan", GOSSIP_SENDER_MAIN, 11);
				Player->ADD_GOSSIP_ITEM(4, name + " the Lion Hearted", GOSSIP_SENDER_MAIN, 12);
				Player->ADD_GOSSIP_ITEM(4, name + " the Forsaken", GOSSIP_SENDER_MAIN, 13);
				Player->ADD_GOSSIP_ITEM(4, name + " the Magic Seeker", GOSSIP_SENDER_MAIN, 14);
				Player->ADD_GOSSIP_ITEM(4, name + " the Love Fool", GOSSIP_SENDER_MAIN, 16);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Nightfall", GOSSIP_SENDER_MAIN, 17);
				Player->ADD_GOSSIP_ITEM(4, name + " the Immortal", GOSSIP_SENDER_MAIN, 18);
				Player->ADD_GOSSIP_ITEM(4, name + " the Undying", GOSSIP_SENDER_MAIN, 19);
				Player->ADD_GOSSIP_ITEM(4, name + " the Insane", GOSSIP_SENDER_MAIN, 21);
				Player->ADD_GOSSIP_ITEM(4, name + " the Astral Walker", GOSSIP_SENDER_MAIN, 23);
				Player->ADD_GOSSIP_ITEM(4, name + ", Herald of the Titans", GOSSIP_SENDER_MAIN, 24);
				Player->ADD_GOSSIP_ITEM(4, name + " of the Horde", GOSSIP_SENDER_MAIN, 28);
				Player->ADD_GOSSIP_ITEM(4, "Conqueror " + name, GOSSIP_SENDER_MAIN, 26);
				Player->ADD_GOSSIP_ITEM(4, "Flame Keeper " + name, GOSSIP_SENDER_MAIN, 3);
				Player->ADD_GOSSIP_ITEM(4, "Arena Master " + name, GOSSIP_SENDER_MAIN, 5);
				Player->ADD_GOSSIP_ITEM(4, "Stalker " + name, GOSSIP_SENDER_MAIN, 8);
				Player->ADD_GOSSIP_ITEM(4, "Assassin " + name, GOSSIP_SENDER_MAIN, 9);
				Player->ADD_GOSSIP_ITEM(4, "Doctor " + name, GOSSIP_SENDER_MAIN, 10);
				Player->ADD_GOSSIP_ITEM(4, "Merrymaker " + name, GOSSIP_SENDER_MAIN, 15);
				Player->ADD_GOSSIP_ITEM(4, "Bloodsail Admiral " + name, GOSSIP_SENDER_MAIN, 20);
				Player->ADD_GOSSIP_ITEM(4, "Starcaller " + name, GOSSIP_SENDER_MAIN, 22);
				Player->PlayerTalkClass->SendGossipMenu(20000, Creature->GetGUID());
				break;

			case 2:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(64);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Hand of A'dal title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 3:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(76);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Flame Keeper title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 4:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(81);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Seeker title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 5:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(82);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Arena Master title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 6:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(86);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Ten Storms title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 7:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(87);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Emerald Dreams title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 8:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(91);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Stalker title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 9:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(95);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Assasin title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 10:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(101);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Doctor title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 11:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(112);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Khaz Modan title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 12:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(114);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Lion Hearted title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 13:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(119);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Forsaken title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 14:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(120);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Magic Seeker title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 15:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(134);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Merrymaker title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 16:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(135);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Love Fool title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 17:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(140);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Nightfall title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 18:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(141);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Immortal title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 19:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(142);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Undying title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 20:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(144);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Bloodsail Admiral title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 21:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(145);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Insane title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 22:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(164);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Starcaller title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 23:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(165);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Astral Walker title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 24:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(166);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Herald of the Titans title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 25:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(48);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Justicar title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 26:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(47);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned Conqueror title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 27:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(126);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Alliance title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 28:
				if (Player->HasItemCount(TITLE_TOKEN, TITLE_PRICE, true))
				{
					Player->DestroyItemCount(TITLE_TOKEN, TITLE_PRICE, true);
					CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(127);
					Player->SetTitle(titleInfo, false);
					Creature->MonsterWhisper("You earned the Horde title!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Creature->MonsterWhisper("You don't have Brewfest Prize Tokens!", Player->GetGUID());
					Player->CLOSE_GOSSIP_MENU();
				}
				}
			}
		}
		return true;
	}
};

void AddSC_Title_NPC()
{
	new Title_NPC();
}