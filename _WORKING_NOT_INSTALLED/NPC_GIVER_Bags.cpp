/*
NPC_GIVER_Bags
testet: 3.3.5a
stand: 26.10.2016

SET @CREATURTEMPLATE_ENTRY = 96021;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (Bags)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GIVER_Bags', 0);

mysql:
SELECT entry FROM world.item_template WHERE class='1' ORDER BY ContainerSlots ASC, name ASC
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
class NPC_GIVER_Bags : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GIVER_Bags() : CreatureScript("NPC_GIVER_Bags") { }
	// ******************************************************************************
	// parameter (anpassbar)
	// ******************************************************************************
	array<uint32, 200> NPC_GIVER_Bags_DATA = { 37606,23389,22976,20474,22571,4930,6756,5081,4238,4957,5762,5571,828,4496,5572,805,2082,856,4498,3343,3233,5573,4241,11845,6754,23852,1537,2657,5763,5574,5603,4240,5765,931,918,932,5764,1729,4497,804,5576,5575,857,933,1470,3352,39489,4245,6446,4981,38145,16057,22250,4499,1725,3762,10050,1623,10051,22243,1652,19291,30744,11324,3914,14046,9587,1685,22244,10959,22246,10683,14155,21841,20400,4500,11742,14156,27680,21843,33117,17966,19914,22679,1977,22251,22248,30748,41599,30747,30745,34482,30746,50317,34845,21876,21340,35516,34067,38082,43345,49295,41600,50316,24270,34490,22249,23774,21341,51809,22252,21342,21872,38225,29540,21858,38399,41597,38307,45773,38347,41598,44446,23775,23162 };
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GIVER_Bags_DATA_filtered;
	array<string, 9>  NPC_GIVER_Bags_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	enum GOSSIP_SENDER_MENU
	{
		GOSSIP_SENDER_MENU_MAIN,
		GOSSIP_SENDER_MENU_EXIT,
		GOSSIP_SENDER_MENU_GIVE,
	};
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		player->PlayerTalkClass->ClearMenus();
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Alle Taschen|r", GOSSIP_SENDER_MENU_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen bis 10 Faecher|r", GOSSIP_SENDER_MENU_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen bis 20 Faecher|r", GOSSIP_SENDER_MENU_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen bis 30 Faecher|r", GOSSIP_SENDER_MENU_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Taschen ab 31 Faecher|r", GOSSIP_SENDER_MENU_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Sondertaschen|r", GOSSIP_SENDER_MENU_MAIN, 130);
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
					DBdata_filter(player, 0, 0, 99);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 110)
				{
					DBdata_filter(player, 0, 0, 10);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 115)
				{
					DBdata_filter(player, 0, 11, 20);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 120)
				{
					DBdata_filter(player, 0, 21, 30);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 125)
				{
					DBdata_filter(player, 0, 31, 99);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 130)
				{
					DBdata_filter(player, 99, 0, 99);
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
					if (StartIndex > NPC_GIVER_Bags_DATA_filtered.size())
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
					uint32 tindex = (action - 100000);
					if (tindex <= 0 || NPC_GIVER_Bags_DATA_filtered[tindex] <= 0) {
						creature->Say("Diese Tasche habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					}
					else
					{
						if (player->HasItemCount(NPC_GIVER_Bags_DATA_filtered[tindex], 20, true))
						{
							creature->Say("Du hast diese Tasche schon mehr als genug !", LANG_UNIVERSAL, NULL);
						}
						else
						{
							player->AddItem(NPC_GIVER_Bags_DATA_filtered[tindex], 1);
							creature->Say("Ich habe Dir die gewuenschte Tasche gegeben.", LANG_UNIVERSAL, NULL);
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
		uint32 MaxIndex = NPC_GIVER_Bags_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Bags_DATA_filtered[i]);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff" + NPC_GIVER_Bags_DATA_quality[item_template->Quality] + "(*)|cff000000|t " + item_template->Name1 + "|r", GOSSIP_SENDER_MENU_GIVE, (100000 + i));
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
	};//ShowNPC_GIVER_Bags_DATA
	// ******************************************************************************
	// DBdata_filter
	// ******************************************************************************
	void DBdata_filter(Player* player, uint32 t_subclass, uint32 t_containerslotsmin,  uint32 t_containerslotsmax)
	{
		NPC_GIVER_Bags_DATA_filtered.clear();
		uint32 MaxIndex = NPC_GIVER_Bags_DATA.size();
		for (uint32 i = 0; i < MaxIndex; i++)
		{
			if (NPC_GIVER_Bags_DATA[i] > 0)
			{
				if (ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Bags_DATA[i]))
				{
					if (!(item_template->AllowableRace & player->getRaceMask()))
						continue;
					if (!(item_template->AllowableClass & player->getClassMask()))
						continue;
					if (item_template->ContainerSlots < t_containerslotsmin || item_template->ContainerSlots > t_containerslotsmax)
						continue;
					if (t_subclass == 0 && item_template->SubClass != 0)
						continue;
					if (t_subclass != 0 && item_template->SubClass == 0)
						continue;
					// ---
					NPC_GIVER_Bags_DATA_filtered.push_back(NPC_GIVER_Bags_DATA[i]);
				}//if ItemTemplate
			}//if > 0
		}//for
	};//DBdata_filter
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GIVER_Bags()
{
	new NPC_GIVER_Bags();
};