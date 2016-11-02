// Scriptname to put into creature_template: PreviewVendor
// dont forget to add vendor flags to the NPC (128)

#include "Common.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ObjectGuid.h"
#include "WorldPacket.h"
#include "WorldSession.h"

static std::unordered_map<uint32, std::vector<uint32> > itemList; // holds items from DB after startup

class PreviewLoader : public WorldScript // script that loads items from DB so you can customize the vendors without recompile and restart
{
public:
	PreviewLoader() : WorldScript("PreviewLoader") { }

	void OnStartup()
	{
		itemList.clear(); // reload
		QueryResult result = WorldDatabase.Query("SELECT entry, item FROM npc_vendor_preview");
		if (!result)
			return;
		do
		{
			uint32 entry = (*result)[0].GetUInt32();
			uint32 item = (*result)[1].GetUInt32();
			if (sObjectMgr->GetItemTemplate(item))
				itemList[entry].push_back(item);
		} while (result->NextRow());
	}

	// you can reload config to reload the items.
	// Too lazy to make a command since all the RBAC stuff changes all the time now and not sure how you have it
	void OnConfigLoad(bool reload)
	{
		if (reload)
			OnStartup();
	}
};


class PreviewVendor : public CreatureScript
{
public:
	PreviewVendor() : CreatureScript("PreviewVendor") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		CustomSendListInventory(player, creature->GetGUID());
		return true; // stop normal actions
	}

	void CustomSendListInventory(Player* player, ObjectGuid vendorGuid)
	{
		TC_LOG_DEBUG("network", "WORLD: Sent custom SMSG_LIST_INVENTORY");

		WorldSession* session = player->GetSession();

		Creature* vendor = player->GetNPCIfCanInteractWith(vendorGuid, UNIT_NPC_FLAG_VENDOR);
		if (!vendor)
		{
			TC_LOG_DEBUG("network", "WORLD: SendListInventory - %s not found or you can not interact with him.", vendorGuid.ToString().c_str());
			player->SendSellError(SELL_ERR_CANT_FIND_VENDOR, NULL, ObjectGuid::Empty, 0);
			return;
		}

		// remove fake death
		if (player->HasUnitState(UNIT_STATE_DIED))
			player->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

		// Stop the npc if moving
		if (vendor->HasUnitState(UNIT_STATE_MOVING))
			vendor->StopMoving();

		// VendorItemData const* items = vendor->GetVendorItems();
		if (itemList.find(vendor->GetEntry()) == itemList.end())
		{
			WorldPacket data(SMSG_LIST_INVENTORY, 8 + 1 + 1);
			data << uint64(vendorGuid);
			data << uint8(0);                                   // count == 0, next will be error code
			data << uint8(0);                                   // "Vendor has no inventory"
			session->SendPacket(&data);
			return;
		}

		std::vector<uint32> items = itemList[vendor->GetEntry()];
		uint8 itemCount = items.size();
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
				if (!player->IsGameMaster() && ((itemTemplate->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == ALLIANCE) || (itemTemplate->Flags2 == ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == HORDE)))
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

void AddSC_PreviewVendor()
{
	new PreviewLoader;
	new PreviewVendor;
}