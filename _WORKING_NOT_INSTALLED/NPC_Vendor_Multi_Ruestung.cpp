/*
NPC_Vendor_Multi_Ruestung
testet: 3.3.5a
stand: 23.10.2016

SET @CREATURTEMPLATE_ENTRY = 96030;
SET @CREATURTEMPLATE_NAME = "Vendor Multi Ruestung (TEST)";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
SET @SCRIPTNAME = "NPC_Vendor_Multi_Ruestung";
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0,  @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Vendor_Multi_Ruestung', 0);
*/

// ******************************************************************************
// include
// ******************************************************************************
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameEventMgr.h"
#include "Player.h"
#include "WorldSession.h"
// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
// ******************************************************************************
// init (global)
// ******************************************************************************
struct DBvector
{
	uint32 u_entry;
	uint32 u_class;
	uint32 u_subclass;
	uint32 u_inventorytype;
};
static vector<DBvector> NPC_Vendor_Multi_Ruestung_VEC_itemlist;
// ******************************************************************************
// class NPC_Vendor_Preview_Mounts_LOADER
// ******************************************************************************
class NPC_Vendor_Multi_Ruestung_LOADER : public WorldScript // script that loads items from DB so you can customize the vendors without recompile and restart
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public:	NPC_Vendor_Multi_Ruestung_LOADER() : WorldScript("NPC_Vendor_Multi_Ruestung_LOADER") { }
	// ******************************************************************************
	// OnStartup
	// ******************************************************************************
	void OnStartup()
	{
		// ******************************************************************************
		// MYSQL
		// ******************************************************************************
		NPC_Vendor_Multi_Ruestung_VEC_itemlist.clear();
		QueryResult result = WorldDatabase.PQuery("SELECT entry,class,subclass,InventoryType FROM world.item_template WHERE class = '4' AND ItemLevel >= '277' AND Quality >= '4' ORDER BY InventoryType ASC, subclass DESC, ItemLevel DESC, name ASC");
		if (result)
		{
			Field * fields = NULL;
			do
			{
				fields = result->Fetch();
				DBvector data;
				// ---
				if (fields[1].GetString().length() > 0)
				{
					// ---
					data.u_entry = fields[0].GetUInt32();
					data.u_class = fields[1].GetUInt32();
					data.u_subclass = fields[2].GetUInt32();
					data.u_inventorytype = fields[3].GetUInt32();
					NPC_Vendor_Multi_Ruestung_VEC_itemlist.push_back(data);
				}//if gueltig
			} while (result->NextRow());
			TC_LOG_ERROR("misc", "DATABASE NPC_Vendor_Multi_Ruestung - ROWS:%u", NPC_Vendor_Multi_Ruestung_VEC_itemlist.size());//TEST
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_Vendor_Multi_Ruestung");
		}
	}
	void OnConfigLoad(bool reload)
	{
		if (reload)
			OnStartup();
	}
};
// ******************************************************************************
// class pre
// ******************************************************************************
class Vendor
{
	private:
		int m_GUID;
		GossipOptionIcon m_Icon;
		std::string m_Message;
	public: Vendor() {}	Vendor(uint32 guid, GossipOptionIcon icon, std::string message)
    {
        m_GUID = guid;
        m_Icon = icon;
        m_Message = message;
    }
    Vendor(uint32 guid, GossipOptionIcon icon, std::string message, VendorItemData* item_list)
    {
        m_GUID = guid;
        m_Icon = icon;
        m_Message = message;
		uint8 zaehler = 0;
		for (uint32 i = 0; i < item_list->GetItemCount(); i++)
		{
			items.AddItem(item_list->m_items[i]->item, 0, 0, item_list->m_items[i]->ExtendedCost);
			if (++zaehler >= 150)
				break;
		}
    }
    VendorItemData items;
    int getGuid() { return m_GUID; }
    void setGuid(uint32 guid) { m_GUID = guid; }
    GossipOptionIcon getIcon() { return m_Icon; }
    void setIcon(GossipOptionIcon icon) { m_Icon = icon; }
    std::string getMessage() { return m_Message; }
    void setMessage(std::string message) { m_Message = message; }
};
// ******************************************************************************
// class pre
// ******************************************************************************
class ItemList
{
	public: ItemList() { /* Called while looping through vendors to find ours */ }
		ItemList(Vendor* myVendor)
		{
			m_vendor = Vendor(myVendor->getGuid(), myVendor->getIcon(), myVendor->getMessage());
		}
		ItemList(Vendor* myVendor, VendorItemData* item_list)
		{
			m_vendor = Vendor(myVendor->getGuid(), myVendor->getIcon(), myVendor->getMessage());
			for(uint32 i = 0; i < item_list->GetItemCount(); i++)
				m_vendor.items.AddItem(item_list->m_items[i]->item, 0, 0, item_list->m_items[i]->ExtendedCost);
		}
		void AddItem(uint32 item_id, uint32 extended_cost = 0) { m_vendor.items.AddItem(item_id, 0, 0, extended_cost); }
		void RemoveItem(uint32 item_id) { m_vendor.items.RemoveItem(item_id); }
		uint8 GetItemCount() { return m_vendor.items.GetItemCount(); }
		Vendor GetVendor() { return m_vendor; }
	private:
		Vendor m_vendor;
};
// ******************************************************************************
// class pre
// ******************************************************************************
class SmsgListInventory
{
	private:
		uint32 m_opcode;
		uint64 m_vendorGuid;
		uint8  m_itemCount;
		uint8  m_status;
		WorldSession* m_session;
		VendorItemData m_vendorItemData;
		VendorItemData m_completeVendorItemData;
		std::vector<ItemList> m_vendors;
    struct packetItem
    {
        uint32 m_slot;
        uint32 m_item;
        uint32 m_displayId;
        int32  m_inStock;
        uint32 m_price;
        uint32 m_durability;
        uint32 m_buyCount;
        uint32 m_extendedCost;
    };
    bool SkipItem(const ItemTemplate* item_template, Player* player, int slot)
    {
        /* Calculate relative slot position */
        if(m_vendors[0].GetItemCount() > 0)
        {
            if( (slot + 1) > (m_vendors[0].GetItemCount()))
            {
                int totalItemsChecked = 0;
                /* For each vendor */
                for(uint32 i = 0; i < m_vendors.size(); i++)
                {
                    if((totalItemsChecked + m_vendors[i].GetItemCount()) < (slot + 1))
                    {
                        totalItemsChecked += m_vendors[i].GetItemCount();
                        continue;
                    }
                    slot -= totalItemsChecked;
                    break;
                }
            }
        }
        /* Account for duplicate items across vendors */
        if(VendorItem* vendor_item = m_vendorItemData.GetItem(slot))
        {
            if(vendor_item->item != item_template->ItemId)
			{
                return true;
			}//if
        }
        else
		{
            return true; // the item doesn't even exist why would we send it
		}//if-else
		/*
		// --- wenn: GM Status darf alle
		if (player->GetSession()->GetSecurity() >= 2)
		{
		return false;
		}//if
		*/
		// --- wenn: nicht richtige race
		if (!(item_template->AllowableRace & player->getRaceMask()))
		{
			return true;
		}//if
		// --- wenn: nicht richtige class
		if (!(item_template->AllowableClass & player->getClassMask()))
		{
            return true;
		}//if
		// --- wenn: nicht richtige faction
		if ((item_template->Flags2 & ITEM_FLAG2_FACTION_HORDE && player->GetTeam() == ALLIANCE) || (item_template->Flags2 == ITEM_FLAG2_FACTION_ALLIANCE && player->GetTeam() == HORDE))
		{
            return true;
		}//if
        // sonst: ok
        return false;
    }//SkipItem
	public: SmsgListInventory(uint64 vendor_guid, WorldSession* player_session, VendorItemData* vendor_item_data, std::vector<ItemList> vendors)
	{
		m_opcode = SMSG_LIST_INVENTORY;
		m_vendorGuid = vendor_guid;
		m_itemCount = 0;
		for(uint32 i = 0; i < vendors.size(); i++)
		{
			m_itemCount += vendors[i].GetItemCount();
		}//for
		m_status = 0;
		m_session = player_session;
		for(uint32 i = 0; i < vendors.size(); i++)
		{
			for(uint32 i2 = 0; i2 < vendors[i].GetItemCount(); i2++)
			{
				m_completeVendorItemData.AddItem(vendors[i].GetVendor().items.m_items[i2]->item, 0, 0, vendors[i].GetVendor().items.m_items[i2]->ExtendedCost);
			}//if
		}//for
		for(uint32 i = 0; i < vendor_item_data->GetItemCount(); i++)
		{
			m_vendorItemData.AddItem(vendor_item_data->m_items[i]->item, 0, 0, vendor_item_data->m_items[i]->ExtendedCost);
		}//for
		for(uint32 i = 0; i < vendors.size(); i++)
		{
			m_vendors.push_back(vendors[i]);
		}//for
	}//SmsgListInventory
	void Send(Creature* originalVendor, Player* player)
	{
		uint8 item_count = 0;
		std::vector<packetItem> items_to_send;
		ItemList item_list_to_send;
		bool haveUpdatedVendor = false;
		if (const VendorItemData* vendor_item_data = originalVendor->GetVendorItems())
		{
			if (vendor_item_data->GetItemCount() > 0)
			{
				haveUpdatedVendor = true;
			}//if
		}//if
		for (uint32 slot = 0; slot < m_itemCount; slot++)
		{
			if (VendorItem const* item = m_completeVendorItemData.GetItem(slot))
			{
				if(ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(item->item))
				{
					if (!haveUpdatedVendor)
					{
						sObjectMgr->AddVendorItem(originalVendor->GetEntry(), item->item, 0, 0, item->ExtendedCost, false);
					}//if
					if (SkipItem(item_template, player, slot))
					{
						continue;
					}//if
					item_list_to_send.AddItem(item->item, item->ExtendedCost);
					item_count++;
					int32 price = item->IsGoldRequired(item_template) ? uint32(item_template->BuyPrice) : 0;
					packetItem packet;
					packet.m_slot = slot + 1;
					packet.m_item = item->item;
					packet.m_displayId = item_template->DisplayInfoID;
					packet.m_inStock = 0xFFFFFFFF;
					packet.m_price = price;
					packet.m_durability = item_template->MaxDurability;
					packet.m_buyCount = item_template->BuyCount;
					packet.m_extendedCost = item->ExtendedCost;
					items_to_send.push_back(packet);
				}//if
				WorldPacket packet(m_opcode, 8 + 1 + (m_itemCount > 0 ? m_itemCount * 8 * 4 : 1));
				packet << m_vendorGuid;
				packet << item_count;
				for(uint32 i = 0; i < items_to_send.size(); i++)
				{
					packet << items_to_send[i].m_slot;
					packet << items_to_send[i].m_item;
					packet << items_to_send[i].m_displayId;
					packet << items_to_send[i].m_inStock;
					packet << items_to_send[i].m_price;
					packet << items_to_send[i].m_durability;
					packet << items_to_send[i].m_buyCount;
					packet << items_to_send[i].m_extendedCost;
				}//for
				m_session->SendPacket(&packet);
			}//for
		}//if VendorItem
	}//void send
};
// ******************************************************************************
// class
// ******************************************************************************
class NPC_Vendor_Multi_Ruestung : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Vendor_Multi_Ruestung() : CreatureScript("NPC_Vendor_Multi_Ruestung"){ }
	// ******************************************************************************
	// GetVendorList
	// ******************************************************************************
	std::vector<ItemList> GetVendorList()
    {
        std::vector<ItemList> itemlists;
		// ---
		Vendor vendor_1(700001, GOSSIP_ICON_VENDOR, "Ruestung Kopf");
        ItemList items_1(&vendor_1);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 1)
				items_1.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
        itemlists.push_back(items_1);
		// ---
		Vendor vendor_2(700002, GOSSIP_ICON_VENDOR, "Ruestung Hals");
		ItemList items_2(&vendor_2);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 2)
				items_2.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_2);
		// ---
		Vendor vendor_3(700003, GOSSIP_ICON_VENDOR, "Ruestung Schulter");
		ItemList items_3(&vendor_3);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 3)
				items_3.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_3);
		// ---
		Vendor vendor_4(700004, GOSSIP_ICON_VENDOR, "Ruestung Hemd");
		ItemList items_4(&vendor_4);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 4)
				items_4.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_4);
		// ---
		Vendor vendor_5(700005, GOSSIP_ICON_VENDOR, "Ruestung Brust");
		ItemList items_5(&vendor_5);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 5)
				items_5.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_5);
		// ---
		Vendor vendor_6(700006, GOSSIP_ICON_VENDOR, "Ruestung Taile");
		ItemList items_6(&vendor_6);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 6)
				items_6.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_6);
		// ---
		Vendor vendor_7(700007, GOSSIP_ICON_VENDOR, "Ruestung Beine");
		ItemList items_7(&vendor_7);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 7)
				items_7.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_7);
		// ---
		Vendor vendor_8(700008, GOSSIP_ICON_VENDOR, "Ruestung Fuesse");
		ItemList items_8(&vendor_8);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 8)
				items_8.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_8);
		// ---
		Vendor vendor_9(700009, GOSSIP_ICON_VENDOR, "Ruestung Handgelenke");
		ItemList items_9(&vendor_9);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 9)
				items_9.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_9);
		// ---
		Vendor vendor_10(700010, GOSSIP_ICON_VENDOR, "Ruestung Haende");
		ItemList items_10(&vendor_10);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 10)
				items_10.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_10);
		// ---
		Vendor vendor_11(700011, GOSSIP_ICON_VENDOR, "Ruestung Finger");
		ItemList items_11(&vendor_11);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 11)
				items_11.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_11);
		// ---
		Vendor vendor_12(700012, GOSSIP_ICON_VENDOR, "Ruestung Schmuck");
		ItemList items_12(&vendor_12);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 12)
				items_12.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_12);
		// ---
		Vendor vendor_16(700016, GOSSIP_ICON_VENDOR, "Ruestung Ruecken");
		ItemList items_16(&vendor_16);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 16)
				items_16.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_16);
		// ---
		Vendor vendor_20(700020, GOSSIP_ICON_VENDOR, "Ruestung Robe");
		ItemList items_20(&vendor_20);
		for (uint32 i = 0; i < NPC_Vendor_Multi_Ruestung_VEC_itemlist.size(); i++)
		{
			if (NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_inventorytype == 20)
				items_20.AddItem(NPC_Vendor_Multi_Ruestung_VEC_itemlist[i].u_entry);
		}
		itemlists.push_back(items_20);
		// ---
		return itemlists;
    }
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
    bool OnGossipHello(Player* player, Creature* creature)
    {
        std::vector<ItemList> vendors = GetVendorList();
        for(uint32 i = 0; i < vendors.size(); i++) // icon message sender guid
		{
            AddGossipItemFor(player, vendors[i].GetVendor().getIcon(), vendors[i].GetVendor().getMessage(), GOSSIP_SENDER_MAIN, vendors[i].GetVendor().getGuid());
		}//for
		player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }
	// ******************************************************************************
	// OnGossipSelect
	// ******************************************************************************
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        CloseGossipMenuFor(player);
        
        SendInventoryCustom(player, creature, action);
        
        return true;
    }
	// ******************************************************************************
	// SendInventoryCustom
	// ******************************************************************************
    void SendInventoryCustom(Player* player, Creature* vendor, int guid)
    {
        /* Remove Feign Death effects */
        if (player->HasUnitState(UNIT_STATE_DIED))
            player->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

        /* Stop NPC moving */
        if (vendor->isMoving())
            vendor->StopMoving();

        std::vector<ItemList> vendors = GetVendorList();
        ItemList myVendor;
        for(uint32 i = 0; i < vendors.size(); i++)
        {
            if(vendors[i].GetVendor().getGuid() == guid)
            {
                myVendor = ItemList(&vendors[i].GetVendor(), &vendors[i].GetVendor().items);
                break;
            }
        }
        SmsgListInventory inventory_packet(vendor->GetGUID(), player->GetSession(), &myVendor.GetVendor().items, vendors);
        inventory_packet.Send(vendor, player);
    }
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Vendor_Multi_Ruestung()
{
    new NPC_Vendor_Multi_Ruestung_LOADER;
	new NPC_Vendor_Multi_Ruestung;
}