/*
NPC_GIVER_Mounts
testet: 3.3.5a
stand: 19.10.2016

SET @CREATURTEMPLATE_ENTRY = 96020;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (Mounts)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
SET @SCRIPTNAME = "NPC_GIVER_Mounts";
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, @SCRIPTNAME, 0);
*/

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

// --- INIT
using namespace std;
struct DB_Mounts
{
	uint32 entry;
	string name;
	uint32 displayid;
	uint32 quality;
	uint32 itemlevel;
	uint32 requiredlevel;
	uint32 spellid2;
	string icon;
	string color;
	string nameloc;
};
vector<DB_Mounts> Data_Mounts;

// --- PARAMETER
uint32 StartNr_Mounts = 1;

void Get_DB_Mounts(string ORDER , uint16 LOCALE)
{
	// ---
	Data_Mounts.clear();
	// ---
	QueryResult result = WorldDatabase.PQuery("SELECT entry,name,displayid,Quality,ItemLevel,RequiredLevel,spellid_2 FROM world.item_template WHERE class = '15' AND subclass = '5' AND spellid_2 <> '0' ORDER BY %s", ORDER);
	if (result)
	{
		Field * fields = NULL;
		do
		{
			fields = result->Fetch();
			uint32 data;
			// ---
			if (fields[1].GetString().length() > 0)
			{
				// ---
				data.entry = fields[0].GetUInt32();
				data.name = fields[1].GetString();
				data.displayid = fields[2].GetUInt32();
				data.quality = fields[3].GetUInt32();
				data.itemlevel = fields[4].GetUInt32();
				data.requiredlevel = fields[5].GetUInt32();
				data.spellid2 = fields[6].GetUInt32();
				data.icon = "buttons\\ButtonHilight-Square";
				switch (data.quality)
				{
				case 0:
					data.color = "404040";
					break;
				case 1:
					data.color = "FFFFFF";
					break;
				case 2:
					data.color = "008000";
					break;
				case 3:
					data.color = "000080";
					break;
				case 4:
					data.color = "a335ee";
					break;
				case 5:
					data.color = "ffd100";
					break;
				case 6:
					data.color = "800000";
					break;
				case 7:
					data.color = "8080FF";
					break;
				case 8:
					data.color = "8080FF";
					break;
				}//switch
				// ---
				if (LOCALE == 3)
				{
					QueryResult result2 = WorldDatabase.PQuery("SELECT name_loc3 FROM world.locales_item WHERE entry = '%u'", data.entry);
					Field * fields2 = NULL;
					fields2 = result2->Fetch();
					if (fields2[0].GetString().length() > 0)
					{
						data.name = fields2[0].GetString();
					}
				}//if LOCALE == 3
				// ---
				Data_Mounts.push_back(data);
			}//if gueltig
		} while (result->NextRow());
	}
	else
	{
		TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_GIVER_Mounts");
	}
}//Get_DB_Mounts

void Show_DB_Mounts(Player* player, Creature* creature, vector<DB_Mounts> Data_Mounts , uint32 tStartNr_Mounts)
{
	uint32 tEndNr = tStartNr_Mounts + 30;
	if (tEndNr > Data_Mounts.size()) {
		tEndNr = Data_Mounts.size();
	}
	if (tStartNr_Mounts > 30)
	{
		AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-PrevPage-Up:30:30:-18|t zurueck|r", GOSSIP_SENDER_MAIN, 100);
	}
	for (uint32 i = tStartNr_Mounts; i < tEndNr; i++)
	{
		AddGossipItemFor(player, GOSSIP_ICON_TAXI, "|cff" + Data_Mounts[i].color + "|TInterface\\" + Data_Mounts[i].icon + ":30:30:-18|t " + Data_Mounts[i].name + "|r", GOSSIP_SENDER_MAIN, (10000 + i));
	}
	if (tEndNr < Data_Mounts.size())
	{
		AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "|cff000000|TInterface\\buttons\\UI-SpellbookIcon-NextPage-Up:30:30:-18|t weiter|r", GOSSIP_SENDER_MAIN, 105);
	}
	SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
}//Show_DB_Mounts


class NPC_GIVER_Mounts : public CreatureScript
{
	public: NPC_GIVER_Mounts() : CreatureScript("NPC_GIVER_Mounts") { }

	bool OnGossipHello(Player* player, Creature* creature) override
	{
		AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere nach Alphabet|r", GOSSIP_SENDER_MAIN, 10);
		AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere nach ItemLevel|r", GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Reittiere nach Qualitaet|r", GOSSIP_SENDER_MAIN, 20);
		AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "|cff000000|TInterface\\icons\\Achievement_BG_kill_on_mount:30:30:-18|t Gib mir alle die du hast|r", GOSSIP_SENDER_MAIN, 25);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}//OnGossipHello

	void SendDefaultMenu(Player* player, Creature* creature, uint32 action)
	{
		// Aus Hauptmenu
		if (action == 10)
		{
			Get_DB_Mounts("name ASC", 3);
			Show_DB_Mounts(player, creature, Data_Mounts, StartNr_Mounts);
		}
		if (action == 15)
		{
			Get_DB_Mounts("ItemLevel DESC", 3);
			Show_DB_Mounts(player, creature, Data_Mounts, StartNr_Mounts);
		}
		if (action == 20)
		{
			Get_DB_Mounts("Quality DESC", 3);
			Show_DB_Mounts(player, creature, Data_Mounts, StartNr_Mounts);
		}
		if (action == 25)
		{
			Get_DB_Mounts("name ASC", 3);
			for (uint32 i = 1; i < Data_Mounts.size(); i++)
			{
				//player->AddItem(Data_Mounts[ZielNr].entry, 1);
				player->LearnSpell(Data_Mounts[i].spellid2, false);
			}
			CloseGossipMenuFor(player);
			creature->Say("Ich habe Dir alle Reittiere gegeben.", LANG_UNIVERSAL, NULL);
		}
		// Aus Submenu (weiter/zurueck)
		if (action == 100)
		{
			StartNr_Mounts = StartNr_Mounts - 30;
			if (StartNr_Mounts < 1)
			{
				StartNr_Mounts = 1;
			}
			Show_DB_Mounts(player, creature, Data_Mounts, StartNr_Mounts);
		}
		if (action == 105)
		{
			StartNr_Mounts = StartNr_Mounts + 30;
			if (StartNr_Mounts > Data_Mounts.size())
			{
				StartNr_Mounts = 1;
			}
			Show_DB_Mounts(player, creature, Data_Mounts, StartNr_Mounts);
		}
		// Aus Submenu (Auswahl)
		if (action > 10000)
		{
			uint32 ZielNr = (action-10000);
			if (ZielNr <= 0) {
				player->PlayerTalkClass->ClearMenus();
				CloseGossipMenuFor(player);
				creature->Say("Dieses Reittier habe ich z.Zt. nicht im Angebot.", LANG_UNIVERSAL, NULL);
				return;
			}
			else
			{
				player->PlayerTalkClass->ClearMenus();
				CloseGossipMenuFor(player);
				//player->AddItem(Data_Mounts[ZielNr].entry, 1);
				player->LearnSpell(Data_Mounts[ZielNr].spellid2, false);
				creature->Say("Ich habe Dir das gewuenschte Reittier gegeben.", LANG_UNIVERSAL, NULL);
				return;
			}
		}
	};//SendDefaultMenu

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		player->PlayerTalkClass->ClearMenus();
		if (sender == GOSSIP_SENDER_MAIN)
			SendDefaultMenu(player, creature, action);
		return true;
	}//OnGossipSelect

};

void AddSC_NPC_GIVER_Mounts()
{
	new NPC_GIVER_Mounts();
};