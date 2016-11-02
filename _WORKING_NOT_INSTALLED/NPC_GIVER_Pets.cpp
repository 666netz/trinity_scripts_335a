/*
NPC_GIVER_Pets
testet: 3.3.5a
stand: 27.10.2016

SET @CREATURTEMPLATE_ENTRY = 96023;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (Pets)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GIVER_Pets', 0);

mysql:
SELECT entry FROM `item_template` WHERE class='15' AND subclass ='2' AND spellid_2 > '0' ORDER BY entry ASC
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
class NPC_GIVER_Pets : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GIVER_Pets() : CreatureScript("NPC_GIVER_Pets") { }
	// ******************************************************************************
	// parameter (anpassbar)
	// ******************************************************************************
	array<uint32, 500> NPC_GIVER_Pets_DATA = { 4401,8485,8486,8487,8488,8489,8490,8491,8492,8494,8495,8496,8497,8498,8499,8500,8501,10360,10361,10392,10393,10394,10398,10822,11023,11026,11027,11110,11474,11825,11826,11903,13582,13583,13584,15996,18964,19054,19055,19450,20371,20651,20769,21168,21277,22114,22235,22780,22781,23002,23007,23015,23083,23712,23713,25535,27445,29363,29364,29901,29902,29903,29904,29953,29956,29957,29958,29960,32233,32465,32498,32588,33154,33816,33818,33993,34425,34478,34492,34493,34518,34519,34535,35349,35350,35504,37297,37298,38050,38628,38658,39286,39656,39896,39898,39899,39973,40653,41133,43517,43698,44721,44723,44738,44819,44822,44841,44965,44970,44971,44972,44973,44974,44980,44982,44983,44984,44998,45002,45022,45180,45606,45942,46398,46544,46545,46707,46767,46802,46820,46821,46892,48112,48114,48116,48118,48120,48122,48124,48126,48527,49287,49343,49362,49646,49662,49663,49665,49693,49912,50446,54436,54810,54847,54857,56806 };
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GIVER_Pets_DATA_filtered;
	array<string, 9>  NPC_GIVER_Pets_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
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
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Box_PetCarrier_01:30:30:-18|t Alle Haustiere|r", GOSSIP_SENDER_MENU_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Box_PetCarrier_01:30:30:-18|t Haustiere bis iLV 20|r", GOSSIP_SENDER_MENU_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Box_PetCarrier_01:30:30:-18|t Haustiere bis iLV 40|r", GOSSIP_SENDER_MENU_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Box_PetCarrier_01:30:30:-18|t Haustiere bis iLV 60|r", GOSSIP_SENDER_MENU_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Box_PetCarrier_01:30:30:-18|t Haustiere ab iLV 61|r", GOSSIP_SENDER_MENU_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Box_PetCarrier_01:30:30:-18|t Gib mir alle die du hast|r", GOSSIP_SENDER_MENU_MAIN, 130);
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
					DBdata_filter(player, 0, 999);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 110)
				{
					DBdata_filter(player, 0, 20);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 115)
				{
					DBdata_filter(player, 21, 40);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 120)
				{
					DBdata_filter(player, 41, 60);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 125)
				{
					DBdata_filter(player, 61, 999);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 130)
				{
					creature->CastSpell(player, 38588, false); // Nur als Effekt
					DBdata_filter(player, 0, 999);
					uint32 MaxIndex = NPC_GIVER_Pets_DATA_filtered.size();
					for (uint32 i = 0; i < MaxIndex; i++)
					{
						if (!player->HasItemCount(NPC_GIVER_Pets_DATA_filtered[i], 1, true))
						{
							player->AddItem(NPC_GIVER_Pets_DATA_filtered[i], 1);
						}//if
					}
					creature->Say("Ich habe Dir alle moeglichen Reittiere gelehrt.", LANG_UNIVERSAL, NULL);
					player->PlayerTalkClass->ClearMenus();
					CloseGossipMenuFor(player);
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
					if (StartIndex > NPC_GIVER_Pets_DATA_filtered.size())
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
					if (tindex <= 0 || NPC_GIVER_Pets_DATA_filtered[tindex] <= 0)
					{
						creature->Say("Dieses Haustier habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					}
					else
					{
						if (player->HasItemCount(NPC_GIVER_Pets_DATA_filtered[tindex], 1, true))
						{
							creature->Say("Du hast dieses Haustier schon !", LANG_UNIVERSAL, NULL);
						}
						else
						{
							player->AddItem(NPC_GIVER_Pets_DATA_filtered[tindex], 1);
							creature->Say("Ich habe Dir das gewuenschte Haustier gegeben.", LANG_UNIVERSAL, NULL);
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
		uint32 MaxIndex = NPC_GIVER_Pets_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Pets_DATA_filtered[i]);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff" + NPC_GIVER_Pets_DATA_quality[item_template->Quality] + "(*)|cff000000|t " + item_template->Name1 + "|r", GOSSIP_SENDER_MENU_GIVE, (100000 + i));
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
	};//ShowNPC_GIVER_Pets_DATA
	// ******************************************************************************
	// DBdata_filter
	// ******************************************************************************
	void DBdata_filter(Player* player, uint32 t_itemlevelmin,  uint32 t_itemlevelmax)
	{
		NPC_GIVER_Pets_DATA_filtered.clear();
		uint32 MaxIndex = NPC_GIVER_Pets_DATA.size();
		for (uint32 i = 0; i < MaxIndex; i++)
		{
			if (NPC_GIVER_Pets_DATA[i] > 0)
			{
				if (ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Pets_DATA[i]))
				{
					if (!(item_template->AllowableRace & player->getRaceMask()))
						continue;
					if (!(item_template->AllowableClass & player->getClassMask()))
						continue;
					if (item_template->ItemLevel < t_itemlevelmin || item_template->ItemLevel > t_itemlevelmax)
						continue;
					// ---
					NPC_GIVER_Pets_DATA_filtered.push_back(NPC_GIVER_Pets_DATA[i]);
				}//if ItemTemplate
			}//if > 0
		}//for
	};//DBdata_filter
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GIVER_Pets()
{
	new NPC_GIVER_Pets();
};