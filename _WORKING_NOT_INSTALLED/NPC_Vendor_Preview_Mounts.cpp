/*
NPC_Vendor_Preview_Mounts
testet: 3.3.5a
stand: 22.10.2016

NOT WORKING (leer)

SET @CREATURTEMPLATE_ENTRY = 96040;
SET @CREATURTEMPLATE_NAME = "Vendor Preview Mounts (TEST)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 129, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Vendor_Preview_Mounts', 0);
*/

// ******************************************************************************
// include
// ******************************************************************************
#include "Common.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ObjectGuid.h"
#include "WorldPacket.h"
#include "WorldSession.h"
// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// init (global)
// ******************************************************************************
static unordered_map<uint32, vector<uint32> > NPC_Vendor_Preview_Mounts_VEC_ITEMLIST; // holds items from DB after startup
// ******************************************************************************
// class NPC_Vendor_Preview_Mounts_LOADER
// ******************************************************************************
class NPC_Vendor_Preview_Mounts_LOADER : public WorldScript // script that loads items from DB so you can customize the vendors without recompile and restart
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public:	NPC_Vendor_Preview_Mounts_LOADER() : WorldScript("NPC_Vendor_Preview_Mounts_LOADER") { }
	// ******************************************************************************
	// OnStartup
	// ******************************************************************************
	void OnStartup()
	{
		NPC_Vendor_Preview_Mounts_VEC_ITEMLIST.clear(); // reload
		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.item_template WHERE class = '15' AND subclass = '5' AND spellid_2 <> '0' ORDER BY name ASC");
		if (!result)
			return;
		do
		{
			uint32 entry = (*result)[0].GetUInt32();
			if (sObjectMgr->GetItemTemplate(entry))
				NPC_Vendor_Preview_Mounts_VEC_ITEMLIST[0].push_back(entry);
		} while (result->NextRow());
		TC_LOG_ERROR("misc", "DATABASE INFO - NPC_Vendor_Preview_Mounts_LOADER --- ROWS: %u ", NPC_Vendor_Preview_Mounts_VEC_ITEMLIST[0].size());//TEST
	}
	// you can reload config to reload the items.
	// Too lazy to make a command since all the RBAC stuff changes all the time now and not sure how you have it
	void OnConfigLoad(bool reload)
	{
		if (reload)
			OnStartup();
	}
};
// ******************************************************************************
// class NPC_Vendor_Preview_Mounts
// ******************************************************************************
class NPC_Vendor_Preview_Mounts : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public:	NPC_Vendor_Preview_Mounts() : CreatureScript("NPC_Vendor_Preview_Mounts") { }
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature)
	{
		CustomSendListInventory(player, creature->GetGUID());
		return true; // stop normal actions
	}
	// ******************************************************************************
	// CustomSendListInventory
	// ******************************************************************************
	void CustomSendListInventory(Player* player, ObjectGuid vendorGuid)
	{
		TC_LOG_ERROR("misc", "DATABASE INFO - NPC_Vendor_Preview_Mounts --- (1)");//TEST
		TC_LOG_ERROR("network", "WORLD: Sent custom SMSG_LIST_INVENTORY");
		WorldSession* session = player->GetSession();
		Creature* vendor = player->GetNPCIfCanInteractWith(vendorGuid, UNIT_NPC_FLAG_VENDOR);
		if (!vendor)
		{
			TC_LOG_ERROR("network", "WORLD: SendListInventory - %s not found or you can not interact with him.", vendorGuid.ToString().c_str());
			player->SendSellError(SELL_ERR_CANT_FIND_VENDOR, NULL, ObjectGuid::Empty, 0);
			return;
		}
		// remove fake death
		if (player->HasUnitState(UNIT_STATE_DIED))
			player->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);
		// Stop the npc if moving
		if (vendor->HasUnitState(UNIT_STATE_MOVING))
			vendor->StopMoving();
		/*
		// VendorItemData const* items = vendor->GetVendorItems();
		if (NPC_Vendor_Preview_Mounts_VEC_ITEMLIST.find(0) == NPC_Vendor_Preview_Mounts_VEC_ITEMLIST.end())
		{
			WorldPacket data(SMSG_LIST_INVENTORY, 8 + 1 + 1);
			data << uint64(vendorGuid);
			data << uint8(0);                                   // count == 0, next will be error code
			data << uint8(0);                                   // "Vendor has no inventory"
			session->SendPacket(&data);
			return;
		}
		*/
		vector<uint32> items = NPC_Vendor_Preview_Mounts_VEC_ITEMLIST[0];
		uint8 itemCount = items.size();
		TC_LOG_DEBUG("misc", "DATABASE INFO - NPC_Vendor_Preview_Mounts --- ROWS: %u ", itemCount);//TEST
		uint8 count = 0;
		WorldPacket data(SMSG_LIST_INVENTORY, 8 + 1 + itemCount * 8 * 4);
		data << uint64(vendorGuid);
		size_t countPos = data.wpos();
		data << uint8(count);
		// float discountMod = player->GetReputationPriceDiscount(vendor);
		for (uint8 slot = 0; slot < itemCount; ++slot)
		{
			if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(items[slot]))
			{
				if (!(itemTemplate->AllowableClass & player->getClassMask()) && itemTemplate->Bonding == BIND_WHEN_PICKED_UP && !player->IsGameMaster())
					continue;
				// Only display items in vendor lists for the team the
				// player is on. If GM on, display all items.
				if (!player->IsGameMaster() && ((itemTemplate->Flags2 & ITEM_FLAG2_FACTION_HORDE && player->GetTeam() == ALLIANCE) || (itemTemplate->Flags2 == ITEM_FLAG2_FACTION_ALLIANCE && player->GetTeam() == HORDE)))
					continue;

				// Items sold out are not displayed in list
				// uint32 leftInStock = !item->maxcount ? 0xFFFFFFFF : vendor->GetVendorItemCurrentCount(item);
				// if (!player->IsGameMaster() && !leftInStock)
				//     continue;
				uint32 leftInStock = 0xFFFFFFFF; // show all items

				if (!sConditionMgr->IsObjectMeetingVendorItemConditions(vendor->GetEntry(), items[slot], player, vendor))
				{
					TC_LOG_DEBUG("condition", "SendListInventory: conditions not met for creature entry %u item %u", vendor->GetEntry(), items[slot]);
					continue;
				}
				// reputation discount
				// int32 price = item->IsGoldRequired(itemTemplate) ? uint32(floor(itemTemplate->BuyPrice * discountMod)) : 0;
				int32 price = 0;
				data << uint32(slot + 1);       // client expects counting to start at 1
				data << uint32(items[slot]);
				data << uint32(itemTemplate->DisplayInfoID);
				data << int32(leftInStock); // left in stock
				data << uint32(price); // price
				data << uint32(itemTemplate->MaxDurability);
				data << uint32(itemTemplate->BuyCount);
				data << uint32(0); // extended cost
				if (++count >= MAX_VENDOR_ITEMS)
					break;
			}
		}
		if (count == 0)
		{
			data << uint8(0);
			session->SendPacket(&data);
			return;
		}
		data.put<uint8>(countPos, count);
		session->SendPacket(&data);
	}
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Vendor_Preview_Mounts()
{
	new NPC_Vendor_Preview_Mounts_LOADER;
	new NPC_Vendor_Preview_Mounts;
}