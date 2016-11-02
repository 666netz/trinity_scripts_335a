/*
NPC_GIVER_Glyph
testet: 3.3.5a
stand: 26.10.2016

SET @CREATURTEMPLATE_ENTRY = 96025;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (Glyph)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_GIVER_Glyph', 0);

mysql:
SELECT entry FROM `item_template` WHERE class='16' AND flags <> '65552' AND flags <> '0' ORDER BY subclass ASC,name ASC
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
class NPC_GIVER_Glyph : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_GIVER_Glyph() : CreatureScript("NPC_GIVER_Glyph") { }
	// ******************************************************************************
	// parameter (anpassbar)
	// ******************************************************************************
	array<uint32, 360> NPC_GIVER_Glyph_DATA = { 43420,43395,45790,43425,43396,43412,43397,43414,49084,43415,43400,45794,43416,43417,43418,43419,43426,43398,43421,43422,43413,43423,43430,43424,45797,45792,45795,43427,43428,43429,43399,43431,45793,43432,41101,41107,45741,43365,43340,43366,41104,41099,41098,45745,45743,41108,41103,41105,41095,45742,41097,41106,45746,43867,41092,43367,41100,45747,41094,41110,43868,43869,41109,43368,45744,41096,43369,41102,42897,42898,42901,42902,45625,42903,42904,45731,45733,43351,42905,42906,42907,42908,45732,43350,42900,42910,43354,42911,45735,43338,43356,45734,42912,42913,42914,42899,42909,43355,42915,42916,42917,42954,42955,42956,42957,43379,45769,42958,42959,43376,42960,42961,42962,45766,42963,42964,42965,42966,42967,45761,45762,45768,43377,43343,42968,42969,43378,42970,45764,42972,42973,42974,45767,43380,42971,42396,42397,45753,42398,43342,42399,42400,43371,45755,42401,45758,42402,43370,42403,42404,42405,42415,45757,45760,45756,42408,42409,42410,42411,42412,43373,42407,43372,42414,42406,43374,42416,42417,43533,43826,43535,43536,43537,43671,45799,43538,45804,43542,43541,43827,43539,45805,43543,43534,43544,45806,45800,43545,43546,43547,43672,43548,43673,44432,43550,43825,43551,43552,43549,43553,45803,43554,43384,43381,41517,41518,45775,41527,41552,45771,41529,41530,41531,41532,41547,43725,41533,41534,45777,41524,41540,41535,41536,41537,41538,43385,45772,41526,45778,41539,45770,44923,45776,43344,41541,43386,43388,41542,45738,44955,42734,43339,42735,42736,44920,42737,45736,50045,42738,42740,43357,42739,43359,42741,43360,42742,44684,42743,45740,42744,42745,42746,42748,45737,42749,42750,45739,42751,42752,42753,42747,43364,43362,43361,42754,45781,42454,42455,42456,43392,42457,45782,43390,43393,42458,42459,42460,45779,42461,42462,42463,42464,42465,42453,43391,45785,45780,50077,42466,42467,42468,45783,42469,45789,43394,42470,42471,43389,42472,42473,43336,43337,40948,40484,43316,45623,45601,43334,48720,43674,40924,44928,40896,40899,40914,40920,40908,40919,40915,40900,40897,45622,40923,45603,40903,50125,40909,40912,40913,40902,45604,40901,40921,40916,46372,40906,43335,43332,44922,43331,45602,40922 };
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 StartIndex = 0;
	vector<uint32> NPC_GIVER_Glyph_DATA_filtered;
	array<string, 9>  NPC_GIVER_Glyph_DATA_quality = { "404040","FFFFFF","008000","000080","a335ee","ffd100","800000","8080FF","8080FF" };
	array<string, 12>  NPC_GIVER_Glyph_DATA_class = { "Krieger","Paladin","Jäger","Schurke","Priester","Todesritter","Schamane","Magier","Hexenmeister","Mönch","Druide","Dämonenjäger" };
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
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Glyph_MajorWarrior:30:30:-18|t Alle '"+ NPC_GIVER_Glyph_DATA_class[player->getClass()]+"' Glyphen|r", GOSSIP_SENDER_MENU_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Glyph_MajorWarrior:30:30:-18|t Glyphen bis LV 15|r", GOSSIP_SENDER_MENU_MAIN, 110);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Glyph_MajorWarrior:30:30:-18|t Glyphen bis LV 20|r", GOSSIP_SENDER_MENU_MAIN, 115);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Glyph_MajorWarrior:30:30:-18|t Glyphen bis LV 40|r", GOSSIP_SENDER_MENU_MAIN, 120);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Glyph_MajorWarrior:30:30:-18|t Glyphen bis LV 60|r", GOSSIP_SENDER_MENU_MAIN, 125);
		AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff000000|TInterface\\icons\\INV_Glyph_MajorWarrior:30:30:-18|t Glyphen ab LV 61|r", GOSSIP_SENDER_MENU_MAIN, 130);
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
					DBdata_filter(player, 0, 99);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 110)
				{
					DBdata_filter(player, 0, 15);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 115)
				{
					DBdata_filter(player, 16, 20);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 120)
				{
					DBdata_filter(player, 21, 40);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 125)
				{
					DBdata_filter(player, 41, 60);
					OnGossipSelect_Sub(player, creature, StartIndex);
				}
				if (action == 130)
				{
					DBdata_filter(player, 61, 99);
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
					if (StartIndex > NPC_GIVER_Glyph_DATA_filtered.size())
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
					if (tindex <= 0 || NPC_GIVER_Glyph_DATA_filtered[tindex] <= 0) {
						creature->Say("Diese Glyphe habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
					}
					else
					{
						if (player->HasItemCount(NPC_GIVER_Glyph_DATA_filtered[tindex], 1, true))
						{
							creature->Say("Du hast diese Glyphe schon !", LANG_UNIVERSAL, NULL);
						}
						else
						{
							player->AddItem(NPC_GIVER_Glyph_DATA_filtered[tindex], 1);
							creature->Say("Ich habe Dir die gewuenschte Glyphe gegeben.", LANG_UNIVERSAL, NULL);
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
		uint32 MaxIndex = NPC_GIVER_Glyph_DATA_filtered.size();
		for (uint32 i = StartIndex; i < MaxIndex; i++)
		{
			ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Glyph_DATA_filtered[i]);
			AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cff" + NPC_GIVER_Glyph_DATA_quality[item_template->Quality] + "(*)|cff000000|t " + item_template->Name1 + "|r", GOSSIP_SENDER_MENU_GIVE, (100000 + i));
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
	};//ShowNPC_GIVER_Glyph_DATA
	// ******************************************************************************
	// DBdata_filter
	// ******************************************************************************
	void DBdata_filter(Player* player, uint32 t_requiredlevelmin,  uint32 t_requiredlevelmax)
	{
		NPC_GIVER_Glyph_DATA_filtered.clear();
		uint32 MaxIndex = NPC_GIVER_Glyph_DATA.size();
		for (uint32 i = 0; i < MaxIndex; i++)
		{
			if (NPC_GIVER_Glyph_DATA[i] > 0)
			{
				if (ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(NPC_GIVER_Glyph_DATA[i]))
				{
					if (!(item_template->AllowableRace & player->getRaceMask()))
						continue;
					if (!(item_template->AllowableClass & player->getClassMask()))
						continue;
					if (item_template->RequiredLevel < t_requiredlevelmin || item_template->RequiredLevel > t_requiredlevelmax)
						continue;
					// ---
					NPC_GIVER_Glyph_DATA_filtered.push_back(NPC_GIVER_Glyph_DATA[i]);
				}//if ItemTemplate
			}//if > 0
		}//for
	};//DBdata_filter
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_GIVER_Glyph()
{
	new NPC_GIVER_Glyph();
};