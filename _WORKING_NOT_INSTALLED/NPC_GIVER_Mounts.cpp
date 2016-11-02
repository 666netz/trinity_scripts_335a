/*
NPC_GIVER_Mounts
testet: 3.3.5a
stand: 27.10.2016

SET @CREATURTEMPLATE_ENTRY = 96020;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (Mounts)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GIVER_Mounts', 0);

mysql:
SELECT entry FROM `item_template` WHERE class='15' AND subclass ='5' AND spellid_2 > '0' AND RequiredSkill > '0' ORDER BY RequiredLevel ASC, name ASC
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
class NPC_GIVER_Mounts : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GIVER_Mounts() : CreatureScript("NPC_GIVER_Mounts") { }
	// ******************************************************************************
	// parameter (anpassbar)
	// ******************************************************************************
	array<uint32, 500> NPC_GIVER_Mounts_DATA = { 1132,2411,2414,5655,5656,5665,5668,5864,5872,5873,8563,8586,8588,8591,8592,8595,8629,8631,8632,12302,12303,12325,12326,12327,12330,12351,12353,12354,13086,13317,13321,13322,13323,13324,13326,13327,13328,13329,13331,13332,13333,13334,13335,15277,15290,15292,15293,18241,18242,18243,18244,18245,18246,18247,18248,18766,18767,18768,18772,18773,18774,18776,18777,18778,18785,18786,18787,18788,18789,18790,18791,18793,18794,18795,18796,18797,18798,18902,19029,19030,19872,19902,21176,21218,21321,21323,21324,25470,25471,25472,25473,25474,25475,25476,25477,25527,25528,25529,25531,25532,25533,28481,28482,28915,28927,28936,29102,29103,29104,29105,29220,29221,29222,29223,29224,29227,29228,29229,29230,29231,29465,29466,29467,29468,29469,29470,29471,29472,29743,29744,29745,29746,29747,30480,30609,31829,31830,31831,31832,31833,31834,31835,31836,32314,32316,32317,32318,32319,32458,32768,32857,32858,32859,32860,32861,32862,33224,33225,33809,33976,33977,33999,34060,34061,34092,34129,35225,35226,35513,35906,37012,37598,37676,37719,37827,37828,38576,40775,40777,41508,43516,43599,43951,43952,43953,43954,43955,43956,43958,43959,43961,43962,43963,43964,43986,44077,44080,44083,44086,44151,44160,44164,44168,44175,44177,44178,44223,44224,44225,44226,44230,44231,44234,44235,44413,44554,44555,44556,44558,44689,44690,44707,44842,44843,45125,45586,45589,45590,45591,45592,45593,45595,45596,45597,45693,45725,45801,45802,46099,46100,46102,46109,46171,46308,46708,46743,46744,46745,46746,46747,46748,46749,46750,46751,46752,46755,46756,46757,46758,46759,46760,46761,46762,46763,46764,46778,46813,46814,46815,46816,47100,47101,47179,47180,47840,49044,49046,49096,49098,49282,49283,49284,49285,49286,49290,49636,50250,50435,50818,51954,51955,52200,54068,54069,54797,54811,54860 };
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GIVER_Mounts_DATA_filtered;
	array<string, 9>  NPC_GIVER_Mounts_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
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
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Alle Reittiere|r", GOSSIP_SENDER_MENU_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere bis LV 20|r", GOSSIP_SENDER_MENU_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere bis LV 40|r", GOSSIP_SENDER_MENU_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere bis LV 60|r", GOSSIP_SENDER_MENU_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere ab LV 61|r", GOSSIP_SENDER_MENU_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Gib mir alle die du hast|r", GOSSIP_SENDER_MENU_MAIN, 130);
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
					uint32 MaxIndex = NPC_GIVER_Mounts_DATA_filtered.size();
					for (uint32 i = 0; i < MaxIndex; i++)
					{
						if (!player->HasItemCount(NPC_GIVER_Mounts_DATA_filtered[i], 1, true))
						{
							player->AddItem(NPC_GIVER_Mounts_DATA_filtered[i], 1);
						}//if
					}//for
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
					if (StartIndex > NPC_GIVER_Mounts_DATA_filtered.size())
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
					if (tindex <= 0 || NPC_GIVER_Mounts_DATA_filtered[tindex] <= 0) {
						creature->Say("Dieses Reittier habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					}
					else
					{
						if (player->HasItemCount(NPC_GIVER_Mounts_DATA_filtered[tindex], 1, true))
						{
							creature->Say("Du hast dieses Reittier schon !", LANG_UNIVERSAL, NULL);
						}
						else
						{
							player->AddItem(NPC_GIVER_Mounts_DATA_filtered[tindex], 1);
							creature->Say("Ich habe Dir das gewuenschte Reittier gegeben.", LANG_UNIVERSAL, NULL);
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
		uint32 MaxIndex = NPC_GIVER_Mounts_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Mounts_DATA_filtered[i]);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff" + NPC_GIVER_Mounts_DATA_quality[item_template->Quality] + "(*)|cff000000|t " + item_template->Name1 + "|r", GOSSIP_SENDER_MENU_GIVE, (100000 + i));
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
	};//ShowNPC_GIVER_Mounts_DATA
	// ******************************************************************************
	// DBdata_filter
	// ******************************************************************************
	void DBdata_filter(Player* player, uint32 t_requiredlevelmin,  uint32 t_requiredlevelmax)
	{
		NPC_GIVER_Mounts_DATA_filtered.clear();
		uint32 MaxIndex = NPC_GIVER_Mounts_DATA.size();
		for (uint32 i = 0; i < MaxIndex; i++)
		{
			if (NPC_GIVER_Mounts_DATA[i] > 0)
			{
				if (ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Mounts_DATA[i]))
				{
					if (!(item_template->AllowableRace & player->getRaceMask()))
						continue;
					if (!(item_template->AllowableClass & player->getClassMask()))
						continue;
					if (item_template->RequiredLevel < t_requiredlevelmin || item_template->RequiredLevel > t_requiredlevelmax)
						continue;
					if (item_template->RequiredSkill <= 0)
						continue;
					// ---
					NPC_GIVER_Mounts_DATA_filtered.push_back(NPC_GIVER_Mounts_DATA[i]);
				}//if ItemTemplate
			}//if > 0
		}//for
	};//DBdata_filter
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GIVER_Mounts()
{
	new NPC_GIVER_Mounts();
};