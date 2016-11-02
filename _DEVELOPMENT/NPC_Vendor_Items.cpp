/*
NPC_Vendor_Items
testet: 3.3.5a
stand: 14.10.2016

SET @CREATURTEMPLATE_ENTRY = 96100;
SET @CREATURTEMPLATE_NAME = "Haendler NPC (Items)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
SET @SCRIPTNAME = "NPC_Vendor_Items";
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
#include "GameEventMgr.h"
#include "WorldSession.h"

using namespace std;
struct DB_Items
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
vector<DB_Items> Data_Items;

uint32 StartNr_Items = 1;

void Get_DB_Items(string ORDER)
{
	// ---
	Data_Items.clear();
	// ---
	QueryResult result = WorldDatabase.PQuery("SELECT entry,name,displayid,Quality,ItemLevel,RequiredLevel,spellid_2 FROM world.item_template WHERE class = '15' AND subclass = '5' AND spellid2 <> '0' ORDER BY %s", ORDER);
	if (result)
	{
		Field * fields = NULL;
		do
		{
			fields = result->Fetch();
			DB_Items data;
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
				data.icon = "icons\\Spell_Nature_Swiftness";
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
				 /*
				 // ---
				 QueryResult result2 = WorldDatabase.PQuery("SELECT name_loc3 FROM world.locales_item WHERE entry = '%u'",data.entry);
				 Field * fields2 = NULL;
				 fields2 = result2->Fetch();
				 if (fields2[0].GetString().length() > 0)
				 {
				 data.nameloc = fields2[0].GetString();
				 }
				 else
				 {
				 data.nameloc = data.name+"~";
				 }
				 */
				 // ---
				Data_Items.push_back(data);
			}//if gueltig
		} while (result->NextRow());
	}
	else
	{
		TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_Vendor_Items");
	}
}//Get_DB_Items


class NPC_Vendor_Items : public CreatureScript
{
public: NPC_Vendor_Items() : CreatureScript("NPC_Vendor_Items") { }

		bool OnGossipHello(Player* player, Creature* creature)
		{
			Get_DB_Items("name ASC");
			for (uint32 i = 0; i <= Data_Items.size(); i++) {
				//
			}

		}

		bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
		{
			player->PlayerTalkClass->ClearMenus();
			CloseGossipMenuFor(player);
			return true;
		}
	};

void AddSC_NPC_Vendor_Items()
{
	new NPC_Vendor_Items;
}