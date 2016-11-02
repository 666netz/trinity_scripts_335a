/*
NPC_Vendor_Multi
testet: 3.3.5a
stand: 20.10.2016

UNTESTET !

SET @CREATURTEMPLATE_ENTRY = 96022;
SET @CREATURTEMPLATE_NAME_M = "Vendor Multi";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
SET @SCRIPTNAME = "NPC_Vendor_Multi";
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `modelid1`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `ScriptName`)
VALUES (@CREATURTEMPLATE_ENTRY, @CREATURTEMPLATE_MODELID, @CREATURTEMPLATE_NAME_M, @CREATURTEMPLATE_SUBNAME, "Directions", 80, 80, 35, 3, @SCRIPTNAME);
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameEventMgr.h"
#include "Player.h"
#include "WorldSession.h"

/* **************************************************************************************************
pre script
************************************************************************************************** */
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
        for(uint32 i = 0; i < item_list->GetItemCount(); i++)
            items.AddItem(item_list->m_items[i]->item, 0, 0, item_list->m_items[i]->ExtendedCost);
    }
    VendorItemData items;
    int getGuid() { return m_GUID; }
    void setGuid(uint32 guid) { m_GUID = guid; }
    GossipOptionIcon getIcon() { return m_Icon; }
    void setIcon(GossipOptionIcon icon) { m_Icon = icon; }
    std::string getMessage() { return m_Message; }
    void setMessage(std::string message) { m_Message = message; }
};

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
                return true;
        }
        else
            return true; // the item doesn't even exist why would we send it
        /* GM's are exceptions */
		if (player->GetSession()->GetSecurity() >= 2)
			return false;
        /* If the item is class specific and Bind on Pickup */
        if (!(item_template->AllowableClass & player->getClassMask()) && item_template->Bonding == BIND_WHEN_PICKED_UP)
            return true;
        
        /* If the item is faction specific and player is wrong faction */
        if ((item_template->Flags2 & ITEM_FLAG2_FACTION_HORDE && player->GetTeam() == ALLIANCE) || 
            (item_template->Flags2 == ITEM_FLAG2_FACTION_ALLIANCE && player->GetTeam() == HORDE))
            return true;
        /* Anything else */
        return false;
    }
	public: SmsgListInventory(uint64 vendor_guid, WorldSession* player_session, VendorItemData* vendor_item_data, std::vector<ItemList> vendors)
	{
		m_opcode = SMSG_LIST_INVENTORY;
		m_vendorGuid = vendor_guid;
		m_itemCount = 0;
		for(uint32 i = 0; i < vendors.size(); i++)
			m_itemCount += vendors[i].GetItemCount();
		m_status = 0;
		m_session = player_session;
		for(uint32 i = 0; i < vendors.size(); i++)
			for(uint32 i2 = 0; i2 < vendors[i].GetItemCount(); i2++)
				m_completeVendorItemData.AddItem(vendors[i].GetVendor().items.m_items[i2]->item, 0, 0, vendors[i].GetVendor().items.m_items[i2]->ExtendedCost);
			for(uint32 i = 0; i < vendor_item_data->GetItemCount(); i++)
                m_vendorItemData.AddItem(vendor_item_data->m_items[i]->item, 0, 0, vendor_item_data->m_items[i]->ExtendedCost);
            for(uint32 i = 0; i < vendors.size(); i++)
                m_vendors.push_back(vendors[i]);
        }
        void Send(Creature* originalVendor, Player* player)
        {
            uint8 item_count = 0;
            std::vector<packetItem> items_to_send;
            ItemList item_list_to_send;
            bool haveUpdatedVendor = false;
			if (const VendorItemData* vendor_item_data = originalVendor->GetVendorItems())
			{
				if (vendor_item_data->GetItemCount() > 0)
					haveUpdatedVendor = true;
			}//if
			for (uint32 slot = 0; slot < m_itemCount; slot++)
				if (VendorItem const* item = m_completeVendorItemData.GetItem(slot))
			if(ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(item->item))
			{
				if (!haveUpdatedVendor)
					sObjectMgr->AddVendorItem(originalVendor->GetEntry(), item->item, 0, 0, item->ExtendedCost, false);
				if (SkipItem(item_template, player, slot))
					continue;
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
		}//void send
};
/* **************************************************************************************************
main script
Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Look at all the weapons I have");
ItemList items_1(&vendor_1);
items_1.AddItem(18582); // Azzinoth
items_1.AddItem(13262); // Ashbringer
itemlists.push_back(items_1);
Die erste Zeile erstellt ein "Vendor" Objekt mit:
- GUID 700000 (Muss verschieden zu allen anderen Vendoren sein)
- Zeigt das Händler Icon an
- Zeigt den Text "Look at all the weapons I have" an
Die zweite Zeile erstell eine Instanz vom ItemList Objekt mit Namen items_1
Die dritte und vierte Zeile sind Beispiele wie man Items zum Vendor hinzufügt(named items_1).
Man kann ItemExtendedCost als zweiten Parameter hinzufügen
Das Script unterstützt keine Zeitlimitierten oder respawnenden Items
Die letzte Zeile ist die wichtigste. Diese Zeile fügt deinen Vendor zur Liste der Vendoren hinzu.
************************************************************************************************** */
class NPC_Vendor_Multi : public CreatureScript
{
public: NPC_Vendor_Multi() : CreatureScript("NPC_Vendor_Multi"){ }
    std::vector<ItemList> GetVendorList()
    {
        std::vector<ItemList> itemlists;
		Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Tier 7 Set-Teile");
        ItemList items_1(&vendor_1);
        items_1.AddItem(40415); // 
        items_1.AddItem(40416); // 
		items_1.AddItem(40417); // 
		items_1.AddItem(40418); // 
		items_1.AddItem(40419); // 
		items_1.AddItem(40420); // 
		items_1.AddItem(40421); // 
		items_1.AddItem(40422); // 
		items_1.AddItem(40423); // 
		items_1.AddItem(40424); // 
		items_1.AddItem(40445); // 
		items_1.AddItem(40447); // 
		items_1.AddItem(40448); // 
		items_1.AddItem(40449); // 
		items_1.AddItem(40450); // 
		items_1.AddItem(40454); // 
		items_1.AddItem(40456); // 
		items_1.AddItem(40457); // 
		items_1.AddItem(40458); // 
		items_1.AddItem(40459); // 
		items_1.AddItem(40460); // 
		items_1.AddItem(40461); // 
		items_1.AddItem(40462); // 
		items_1.AddItem(40463); // 
		items_1.AddItem(40465); // 
		items_1.AddItem(40466); // 
		items_1.AddItem(40467); // 
		items_1.AddItem(40468); // 
		items_1.AddItem(40469); // 
		items_1.AddItem(40470); // 
		items_1.AddItem(40471); // 
		items_1.AddItem(40472); // 
		items_1.AddItem(40473); // 
		items_1.AddItem(40493); // 
		items_1.AddItem(40494); // 
		items_1.AddItem(40495); // 
		items_1.AddItem(40496); // 
		items_1.AddItem(40499); // 
		items_1.AddItem(40500); // 
		items_1.AddItem(40502); // 
		items_1.AddItem(40503); // 
		items_1.AddItem(40504); // 
		items_1.AddItem(40505); // 
		items_1.AddItem(40506); // 
		items_1.AddItem(40507); // 
		items_1.AddItem(40508); // 
		items_1.AddItem(40509); // 
		items_1.AddItem(40510); // 
		items_1.AddItem(40512); // 
		items_1.AddItem(40513); // 
		items_1.AddItem(40514); // 
		items_1.AddItem(40515); // 
		items_1.AddItem(40516); // 
		items_1.AddItem(40517); // 
		items_1.AddItem(40518); // 
		items_1.AddItem(40520); // 
		items_1.AddItem(40521); // 
		items_1.AddItem(40522); // 
		items_1.AddItem(40523); // 
		items_1.AddItem(40524); // 
		items_1.AddItem(40525); // 
		items_1.AddItem(40527); // 
		items_1.AddItem(40528); // 
		items_1.AddItem(40529); // 
		items_1.AddItem(40530); // 
		items_1.AddItem(40544); // 
		items_1.AddItem(40545); // 
		items_1.AddItem(40546); // 
		items_1.AddItem(40547); // 
		items_1.AddItem(40548); // 
		items_1.AddItem(40550); // 
		items_1.AddItem(40552); // 
		items_1.AddItem(40554); // 
		items_1.AddItem(40556); // 
		items_1.AddItem(40557); // 
		items_1.AddItem(40559); // 
		items_1.AddItem(40563); // 
		items_1.AddItem(40565); // 
		items_1.AddItem(40567); // 
		items_1.AddItem(40568); // 
		items_1.AddItem(40569); // 
		items_1.AddItem(40570); // 
		items_1.AddItem(40571); // 
		items_1.AddItem(40572); // 
		items_1.AddItem(40573); // 
		items_1.AddItem(40574); // 
		items_1.AddItem(40575); // 
		items_1.AddItem(40576); // 
		items_1.AddItem(40577); // 
		items_1.AddItem(40578); // 
		items_1.AddItem(40579); // 
		items_1.AddItem(40580); // 
		items_1.AddItem(40581); // 
		items_1.AddItem(40583); // 
		items_1.AddItem(40584); // 
        itemlists.push_back(items_1);

        Vendor vendor_2(700001, GOSSIP_ICON_VENDOR, "Tier 7 NonSets");
        ItemList items_2(&vendor_2);
        items_2.AddItem(39421); // 
        items_2.AddItem(39425); // 
		items_2.AddItem(39701); // 
		items_2.AddItem(39702); // 
		items_2.AddItem(39706); // 
		items_2.AddItem(39717); // 
		items_2.AddItem(39721); // 
		items_2.AddItem(39722); // 
		items_2.AddItem(39728); // 
		items_2.AddItem(39729); // 
		items_2.AddItem(39731); // 
		items_2.AddItem(39734); // 
		items_2.AddItem(39735); // 
		items_2.AddItem(39757); // 
		items_2.AddItem(39759); // 
		items_2.AddItem(39762); // 
		items_2.AddItem(39764); // 
		items_2.AddItem(39765); // 
		items_2.AddItem(40064); // 
		items_2.AddItem(40065); // 
		items_2.AddItem(40069); // 
		items_2.AddItem(40071); // 
		items_2.AddItem(40074); // 
		items_2.AddItem(40075); // 
		items_2.AddItem(40080); // 
		items_2.AddItem(40107); // 
		items_2.AddItem(40108); // 
		items_2.AddItem(40184); // 
		items_2.AddItem(40186); // 
		items_2.AddItem(40187); // 
		items_2.AddItem(40191); // 
		items_2.AddItem(40198); // 
		items_2.AddItem(40200); // 
		items_2.AddItem(40205); // 
		items_2.AddItem(40206); // 
		items_2.AddItem(40207); // 
		items_2.AddItem(40209); // 
		items_2.AddItem(40236); // 
		items_2.AddItem(40237); // 
		items_2.AddItem(40241); // 
		items_2.AddItem(40243); // 
		items_2.AddItem(40246); // 
		items_2.AddItem(40250); // 
		items_2.AddItem(40251); // 
		items_2.AddItem(40252); // 
		items_2.AddItem(40253); // 
		items_2.AddItem(40254); // 
		items_2.AddItem(40255); // 
		items_2.AddItem(40256); // 
		items_2.AddItem(40257); // 
		items_2.AddItem(40258); // 
		items_2.AddItem(40259); //
		items_2.AddItem(40260); //
		items_2.AddItem(40263); //
		items_2.AddItem(40267); //
		items_2.AddItem(40268); //
		items_2.AddItem(40269); //
		items_2.AddItem(40270); //
		items_2.AddItem(40271); //
		items_2.AddItem(40272); //
		items_2.AddItem(40274); //
		items_2.AddItem(40275); //
		items_2.AddItem(40278); //
		items_2.AddItem(40282); //
		items_2.AddItem(40297); //
		items_2.AddItem(40301); //
		items_2.AddItem(40306); //
		items_2.AddItem(40317); //
		items_2.AddItem(40320); //
		items_2.AddItem(40321); //
		items_2.AddItem(40322); //
		items_2.AddItem(40323); //
		items_2.AddItem(40324); //
		items_2.AddItem(40325); //
		items_2.AddItem(40326); //
		items_2.AddItem(40327); //
		items_2.AddItem(40330); //
		items_2.AddItem(40332); //
		items_2.AddItem(40337); //
		items_2.AddItem(40338); //
		items_2.AddItem(40341); //
		items_2.AddItem(40342); //
		items_2.AddItem(40367); //
		items_2.AddItem(40369); //
		items_2.AddItem(40370); //
		items_2.AddItem(40371); //
		items_2.AddItem(40372); //
		items_2.AddItem(40373); //
		items_2.AddItem(40374); //
		items_2.AddItem(40375); //
		items_2.AddItem(40378); //
		items_2.AddItem(40382); //
		items_2.AddItem(40409); //
		items_2.AddItem(40410); //
		items_2.AddItem(40412); //
        itemlists.push_back(items_2);

		Vendor vendor_3(700002, GOSSIP_ICON_VENDOR, "Tier 7 Waffen");
        ItemList items_3(&vendor_3);
        items_3.AddItem(39712); //
        items_3.AddItem(39714); //
		items_3.AddItem(39730); //
		items_3.AddItem(39758); //
		items_3.AddItem(39763); //
		items_3.AddItem(39766); //
		items_3.AddItem(40192); //
		items_3.AddItem(40208); //
		items_3.AddItem(40233); //
		items_3.AddItem(40239); //
		items_3.AddItem(40244); //
		items_3.AddItem(40245); //
		items_3.AddItem(40264); //
		items_3.AddItem(40273); //
		items_3.AddItem(40280); //
		items_3.AddItem(40281); //
		items_3.AddItem(40284); //
		items_3.AddItem(40300); //
		items_3.AddItem(40335); //
		items_3.AddItem(40336); //
		items_3.AddItem(40343); //
		items_3.AddItem(40345); //
		items_3.AddItem(40346); //
		items_3.AddItem(40348); //
		items_3.AddItem(40350); //
		items_3.AddItem(40368); //
		items_3.AddItem(40369); //
		items_3.AddItem(40383); //
		items_3.AddItem(40384); //
		items_3.AddItem(40385); //
		items_3.AddItem(40386); //
		items_3.AddItem(40388); //
		items_3.AddItem(40395); //
		items_3.AddItem(40400); //
		items_3.AddItem(40401); //
		items_3.AddItem(40402); //
        itemlists.push_back(items_3);

        /* Verändere nicht was hier drunter steht
         * Dies ist das Ende des editierbaren Abschnitts
         * Verändere nur Dinge ÜBER diesem Commentblock, solange du nicht weißt was du tust!
         *
         * Peace out
         * Evilfairy~ */

        return itemlists;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        std::vector<ItemList> vendors = GetVendorList();

        /* DO NOT EDIT ANYTHING BELOW THIS LINE */
        for(uint32 i = 0; i < vendors.size(); i++) // icon message sender guid
            AddGossipItemFor(player, vendors[i].GetVendor().getIcon(), vendors[i].GetVendor().getMessage(), GOSSIP_SENDER_MAIN, vendors[i].GetVendor().getGuid());

        player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
       SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        CloseGossipMenuFor(player);
        
        SendInventoryCustom(player, creature, action);
        
        return true;
    }

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

class NPC_Vendor_Multi_season : public CreatureScript
{
public:
    NPC_Vendor_Multi_season() : CreatureScript("NPC_Vendor_Multi_season"){ }

    std::vector<ItemList> GetVendorList()
    {
        std::vector<ItemList> itemlists;
        
        /* Nur Daten nach diesem Commentblock editieren!
         * Nicht anderes verändern!
         *
         * Example vendor:

        Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Look at all the weapons I have");
        ItemList items_1(&vendor_1);
        items_1.AddItem(18582); // Azzinoth
        items_1.AddItem(13262); // Ashbringer
        itemlists.push_back(items_1);
        
        * Die erste Zeile erstellt ein "Vendor" Objekt mit:
        *     GUID 700000 (Muss verschieden zu allen anderen Vendoren sein)
        *     Zeigt das Händler Icon an
        *     Zeigt den Text "Look at all the weapons I have" an
        * 
        *Die zweite Zeile erstell eine Instanz vom ItemList Objekt mit Namen items_1
        *    
        * 
        * Die dritte und vierte Zeile sind Beispiele wie man Items zum Vendor hinzufügt(named items_1).
        *     Man kann ItemExtendedCost als zweiten Parameter hinzufügen
        *     Das Script unterstützt keine Zeitlimitierten oder respawnenden Items
        * 
        * Die letzte Zeile ist die wichtigste. Diese Zeile fügt deinen Vendor zur Liste der Vendoren hinzu.
        * 
        *
        * Ende der Erklärung
        * 
        */

        Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Tier 7 Set-Teile");
        ItemList items_1(&vendor_1);
        items_1.AddItem(40415); // 
        items_1.AddItem(40416); // 
		items_1.AddItem(40417); // 
		items_1.AddItem(40418); // 
		items_1.AddItem(40419); // 
		items_1.AddItem(40420); // 
		items_1.AddItem(40421); // 
		items_1.AddItem(40422); // 
		items_1.AddItem(40423); // 
		items_1.AddItem(40424); // 
		items_1.AddItem(40445); // 
		items_1.AddItem(40447); // 
		items_1.AddItem(40448); // 
		items_1.AddItem(40449); // 
		items_1.AddItem(40450); // 
		items_1.AddItem(40454); // 
		items_1.AddItem(40456); // 
		items_1.AddItem(40457); // 
		items_1.AddItem(40458); // 
		items_1.AddItem(40459); // 
		items_1.AddItem(40460); // 
		items_1.AddItem(40461); // 
		items_1.AddItem(40462); // 
		items_1.AddItem(40463); // 
		items_1.AddItem(40465); // 
		items_1.AddItem(40466); // 
		items_1.AddItem(40467); // 
		items_1.AddItem(40468); // 
		items_1.AddItem(40469); // 
		items_1.AddItem(40470); // 
		items_1.AddItem(40471); // 
		items_1.AddItem(40472); // 
		items_1.AddItem(40473); // 
		items_1.AddItem(40493); // 
		items_1.AddItem(40494); // 
		items_1.AddItem(40495); // 
		items_1.AddItem(40496); // 
		items_1.AddItem(40499); // 
		items_1.AddItem(40500); // 
		items_1.AddItem(40502); // 
		items_1.AddItem(40503); // 
		items_1.AddItem(40504); // 
		items_1.AddItem(40505); // 
		items_1.AddItem(40506); // 
		items_1.AddItem(40507); // 
		items_1.AddItem(40508); // 
		items_1.AddItem(40509); // 
		items_1.AddItem(40510); // 
		items_1.AddItem(40512); // 
		items_1.AddItem(40513); // 
		items_1.AddItem(40514); // 
		items_1.AddItem(40515); // 
		items_1.AddItem(40516); // 
		items_1.AddItem(40517); // 
		items_1.AddItem(40518); // 
		items_1.AddItem(40520); // 
		items_1.AddItem(40521); // 
		items_1.AddItem(40522); // 
		items_1.AddItem(40523); // 
		items_1.AddItem(40524); // 
		items_1.AddItem(40525); // 
		items_1.AddItem(40527); // 
		items_1.AddItem(40528); // 
		items_1.AddItem(40529); // 
		items_1.AddItem(40530); // 
		items_1.AddItem(40544); // 
		items_1.AddItem(40545); // 
		items_1.AddItem(40546); // 
		items_1.AddItem(40547); // 
		items_1.AddItem(40548); // 
		items_1.AddItem(40550); // 
		items_1.AddItem(40552); // 
		items_1.AddItem(40554); // 
		items_1.AddItem(40556); // 
		items_1.AddItem(40557); // 
		items_1.AddItem(40559); // 
		items_1.AddItem(40563); // 
		items_1.AddItem(40565); // 
		items_1.AddItem(40567); // 
		items_1.AddItem(40568); // 
		items_1.AddItem(40569); // 
		items_1.AddItem(40570); // 
		items_1.AddItem(40571); // 
		items_1.AddItem(40572); // 
		items_1.AddItem(40573); // 
		items_1.AddItem(40574); // 
		items_1.AddItem(40575); // 
		items_1.AddItem(40576); // 
		items_1.AddItem(40577); // 
		items_1.AddItem(40578); // 
		items_1.AddItem(40579); // 
		items_1.AddItem(40580); // 
		items_1.AddItem(40581); // 
		items_1.AddItem(40583); // 
		items_1.AddItem(40584); // 
        itemlists.push_back(items_1);

        Vendor vendor_2(700001, GOSSIP_ICON_VENDOR, "Tier 7 NonSets");
        ItemList items_2(&vendor_2);
        items_2.AddItem(39421); // 
        items_2.AddItem(39425); // 
		items_2.AddItem(39701); // 
		items_2.AddItem(39702); // 
		items_2.AddItem(39706); // 
		items_2.AddItem(39717); // 
		items_2.AddItem(39721); // 
		items_2.AddItem(39722); // 
		items_2.AddItem(39728); // 
		items_2.AddItem(39729); // 
		items_2.AddItem(39731); // 
		items_2.AddItem(39734); // 
		items_2.AddItem(39735); // 
		items_2.AddItem(39757); // 
		items_2.AddItem(39759); // 
		items_2.AddItem(39762); // 
		items_2.AddItem(39764); // 
		items_2.AddItem(39765); // 
		items_2.AddItem(40064); // 
		items_2.AddItem(40065); // 
		items_2.AddItem(40069); // 
		items_2.AddItem(40071); // 
		items_2.AddItem(40074); // 
		items_2.AddItem(40075); // 
		items_2.AddItem(40080); // 
		items_2.AddItem(40107); // 
		items_2.AddItem(40108); // 
		items_2.AddItem(40184); // 
		items_2.AddItem(40186); // 
		items_2.AddItem(40187); // 
		items_2.AddItem(40191); // 
		items_2.AddItem(40198); // 
		items_2.AddItem(40200); // 
		items_2.AddItem(40205); // 
		items_2.AddItem(40206); // 
		items_2.AddItem(40207); // 
		items_2.AddItem(40209); // 
		items_2.AddItem(40236); // 
		items_2.AddItem(40237); // 
		items_2.AddItem(40241); // 
		items_2.AddItem(40243); // 
		items_2.AddItem(40246); // 
		items_2.AddItem(40250); // 
		items_2.AddItem(40251); // 
		items_2.AddItem(40252); // 
		items_2.AddItem(40253); // 
		items_2.AddItem(40254); // 
		items_2.AddItem(40255); // 
		items_2.AddItem(40256); // 
		items_2.AddItem(40257); // 
		items_2.AddItem(40258); // 
		items_2.AddItem(40259); //
		items_2.AddItem(40260); //
		items_2.AddItem(40263); //
		items_2.AddItem(40267); //
		items_2.AddItem(40268); //
		items_2.AddItem(40269); //
		items_2.AddItem(40270); //
		items_2.AddItem(40271); //
		items_2.AddItem(40272); //
		items_2.AddItem(40274); //
		items_2.AddItem(40275); //
		items_2.AddItem(40278); //
		items_2.AddItem(40282); //
		items_2.AddItem(40297); //
		items_2.AddItem(40301); //
		items_2.AddItem(40306); //
		items_2.AddItem(40317); //
		items_2.AddItem(40320); //
		items_2.AddItem(40321); //
		items_2.AddItem(40322); //
		items_2.AddItem(40323); //
		items_2.AddItem(40324); //
		items_2.AddItem(40325); //
		items_2.AddItem(40326); //
		items_2.AddItem(40327); //
		items_2.AddItem(40330); //
		items_2.AddItem(40332); //
		items_2.AddItem(40337); //
		items_2.AddItem(40338); //
		items_2.AddItem(40341); //
		items_2.AddItem(40342); //
		items_2.AddItem(40367); //
		items_2.AddItem(40369); //
		items_2.AddItem(40370); //
		items_2.AddItem(40371); //
		items_2.AddItem(40372); //
		items_2.AddItem(40373); //
		items_2.AddItem(40374); //
		items_2.AddItem(40375); //
		items_2.AddItem(40378); //
		items_2.AddItem(40382); //
		items_2.AddItem(40409); //
		items_2.AddItem(40410); //
		items_2.AddItem(40412); //
        itemlists.push_back(items_2);

		Vendor vendor_3(700002, GOSSIP_ICON_VENDOR, "Tier 7 Waffen");
        ItemList items_3(&vendor_3);
        items_3.AddItem(39712); //
        items_3.AddItem(39714); //
		items_3.AddItem(39730); //
		items_3.AddItem(39758); //
		items_3.AddItem(39763); //
		items_3.AddItem(39766); //
		items_3.AddItem(40192); //
		items_3.AddItem(40208); //
		items_3.AddItem(40233); //
		items_3.AddItem(40239); //
		items_3.AddItem(40244); //
		items_3.AddItem(40245); //
		items_3.AddItem(40264); //
		items_3.AddItem(40273); //
		items_3.AddItem(40280); //
		items_3.AddItem(40281); //
		items_3.AddItem(40284); //
		items_3.AddItem(40300); //
		items_3.AddItem(40335); //
		items_3.AddItem(40336); //
		items_3.AddItem(40343); //
		items_3.AddItem(40345); //
		items_3.AddItem(40346); //
		items_3.AddItem(40348); //
		items_3.AddItem(40350); //
		items_3.AddItem(40368); //
		items_3.AddItem(40369); //
		items_3.AddItem(40383); //
		items_3.AddItem(40384); //
		items_3.AddItem(40385); //
		items_3.AddItem(40386); //
		items_3.AddItem(40388); //
		items_3.AddItem(40395); //
		items_3.AddItem(40400); //
		items_3.AddItem(40401); //
		items_3.AddItem(40402); //
        itemlists.push_back(items_3);

        /* Verändere nicht was hier drunter steht
         * Dies ist das Ende des editierbaren Abschnitts
         * Verändere nur Dinge ÜBER diesem Commentblock, solange du nicht weißt was du tust!
         *
         * Peace out
         * Evilfairy~ */

        return itemlists;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        std::vector<ItemList> vendors = GetVendorList();

        /* DO NOT EDIT ANYTHING BELOW THIS LINE */
        for(uint32 i = 0; i < vendors.size(); i++) // icon message sender guid
            AddGossipItemFor(player, vendors[i].GetVendor().getIcon(), vendors[i].GetVendor().getMessage(), GOSSIP_SENDER_MAIN, vendors[i].GetVendor().getGuid());

        player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
       SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        CloseGossipMenuFor(player);
        
        SendInventoryCustom(player, creature, action);
        
        return true;
    }

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

void AddSC_NPC_Vendor_Multi()
{
    new NPC_Vendor_Multi;
	new NPC_Vendor_Multi_season;
}