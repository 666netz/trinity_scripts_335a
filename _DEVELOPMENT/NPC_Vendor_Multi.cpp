/*
NPC_Vendor_Multi
testet: 3.3.5a
stand: 20.10.2016

UNTESTET !

SET @CREATURTEMPLATE_ENTRY = 96030;
SET @CREATURTEMPLATE_NAME_M = "Vendor Multi";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
SET @SCRIPTNAME = "NPC_Vendor_Multi";
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0,  @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, @SCRIPTNAME, 0);

class / subclass z.b. bei 4 - x
0 => "Verbrauchbar"
	1 => "Tränke"
	2 => "Elixiere"
	3 => "Fläschchen"
	5 => "Essen & Trinken"
	6 => "Gegenstandsverzauberungen (Dauerhafte)"
	7 => "Verbände"
	8 => "Andere (Verbrauchbar)"
1 => "Behälter"
	0 => "Taschen"
	1 => "Seelentasche"
	2 => "Kräutertaschen"
	3 => "Verzauberertaschen"
	4 => "Ingenieurstaschen"
	5 => "Edelsteintaschen"
	6 => "Bergbautaschen"
	7 => "Lederertaschen"
	8 => "Schreibertaschen"
	9 => "Spinnerkästen"
2 => "Waffe"
	0 => "Einhandäxte"
	1 => "Zweihandäxte"
	2 => "Bogen"
	3 => "Schusswaffen"
	4 => "Einhandstreitkolbenn"
	5 => "Zweihandstreitkolbenn"
	6 => "Stangenwaffen"
	7 => "Einhandschwerter"
	8 => "Zweihandschwerter"
	9 => "Kriegsgleven"
	10 => "Stäbe"
	11 => "Exotisch"
	12 => "Exotisch"
	13 => "Faustwaffen"
	14 => "Verschiedenes (Waffen)"
	15 => "Dolche"
	16 => "Wurfwaffe"
	17 => "Speer"
	18 => "Armbrüste"
	19 => "Zauberstäbe"
	20 => "Angelruten"
3 => Edelsteine
	0 => "Rote Edelsteine"
	1 => "Blaue Edelsteine"
	2 => "Gelbe Edelsteine"
	3 => "Violette Edelsteine"
	4 => "Grüne Edelsteine"
	5 => "Orangefarbene Edelsteine"
	6 => "Meta-Edelsteine"
	8 => "Prismatische Edelsteine"
4 => "Rüstung"
	0 => "Verschiedenes (Rüstung)"
	1 => "Stoffrüstung"
	2 => "Lederrüstung"
	3 => "Kettenrüstung"
	4 => "Plattenrüstung"
	5 => "Buckler(OBSOLETE)"
	6 => "Schild"
	7 => "Libram"
	8 => "Idol"
	9 => "Totem"
	10 => "Sigil"
5 => "Reagent"
6 => "Schusswaffen"
	0 => "Wand(OBSOLETE)"
	1 => "Bolzen(OBSOLETE)"
	2 => "Pfeile"
	3 => "Kugeln"
	4 => "Thrown(OBSOLETE)"
7 => "Handwerkswaren"
	1 => "Teile"
	2 => "Sprengstoff"
	3 => "Geräte"
	4 => "Juwelierskunst"
	5 => "Stoff"
	6 => "Leder"
	7 => "Metall & Stein"
	8 => "Fleisch"
	9 => "Kräuter"
	10 => "Elementare"
	11 => "Andere (Handwerkswaren)"
	12 => "Verzauberkunst"
8 =>"ALT(OBSOLETE)"
	0 => "ALT(OBSOLETE)"
	1 => "ALT(OBSOLETE)"
	2 => "ALT(OBSOLETE)"
	3 => "ALT(OBSOLETE)"
	4 => "ALT(OBSOLETE)"
	5 => "ALT(OBSOLETE)"
	6 => "ALT(OBSOLETE)"
	7 => "ALT(OBSOLETE)"
	8 => "ALT(OBSOLETE)"
	9 => "ALT(OBSOLETE)"
	10 => "ALT(OBSOLETE)"
	11 => "ALT(OBSOLETE)"
9=>"Rezepte"
	0=>"Bücher"
	1=>"Lederverarbeitungsmuster"
	2=>"Schneidereimuster"
	3=>"Ingenieurschemata"
	4=>"Schmiedekunstpläne"
	5=>"Kochrezepte"
	6=>"Alchimierezepte"
	7=>"Erste Hilfe-Bücher"
	8=>"Verzauberkunstformeln"
	9=>"Angelbücher"
	10=>"Juwelenschleifer-Vorlagen"
	11=>"Inschriftenkundentechniken"
10 => "Money(OBSOLETE)"
11 => "Munitionstaschen"
	0 => "Koecher(OBSOLETE)"
	1 => "Koecher(OBSOLETE)"
	2 => "Koecher"
	3 => "Kugelbeutel"
12 => "Quest"
13 => "Schluessel"
	0 => "Schluessel"
	1 => "Schlossknacken"
14 => "Permament"
	0 => "Permanent"
15 => "Verschiedenes"
	0 => "Plunder"
	1 => "Reagenzien"
	2 => "Haustiere"
	3 => "Feiertag"
	4 => "Andere (Verschiedenes)"
	5 => "Reittiere"
16 => "Glyphen"
	1 => "Kriegerglyphen"
	2 => "Paladinglyphen"
	3 => "Jägerglyphen"
	4 => "Schurkenglyphen"
	5 => "Priesterglyphen"
	6 => "Todesritterglyphen"
	7 => "Schamanenglyphen"
	8 => "Magierglyphen"
	9 => "Hexenmeisterglyphen"
	11 => "Druidenglyphen"

inventorytype
1 => "Kopf"
2 => "Hals"
3 => "Schulter"
4 => "Hemd"
5 => "Brust"
6 => "Taille"
7 => "Beine"
8 => "Füße"
9 => "Handgelenke"
10 => "Hände"
11 => "Finger"
12 => "Schmuck"
13 => "Waffe"
14 => "Schild"
15 => "Fernwaffen"
16 => "Ruecken"
17 => "Zweihand"
18 => "Tasche"
19 => "Wappenrock"
20 => "Robe"
21 => "Haupthand"
22 => "Nebenhand"
23 => "Holdable (Tome)"
24 => "Munition"
25 => "Wurf"
26 => "Ranged right (Wands Guns)"
27 => "Munitionstaschen"
28 => "Relikt"
*/

// ******************************************************************************
// include
// ******************************************************************************
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "GameEventMgr.h"
#include "WorldSession.h"
#include <cstring>
#include <string>
// ******************************************************************************
// namespace
// ******************************************************************************
using namespace std;
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
        // --- Slot kalkulieren
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
		// --- Doppelte innerhalb Vendor
		if (VendorItem* vendor_item = m_vendorItemData.GetItem(slot))
		{
			if (vendor_item->item != item_template->ItemId)
			{
				return true;
			}//if
        }
        else
		{
            return true; // the item doesn't even exist why would we send it
		}//if-else
        // --- wenn GM dann immer OK
		if (player->GetSession()->GetSecurity() >= 2)
		{
			return false;
		}//if
		// --- wenn level falsch
		if (item_template->RequiredLevel > player->getLevel())
		{
			return true;
		}//if
		// --- wenn race falsch
		if (!item_template->AllowableRace & player->getRaceMask())
		{
			return true;
		}//if
		// --- wenn class falsch
		if (!item_template->AllowableClass & player->getClassMask())
		{
			return true;
		}//if
		// --- wenn faction falsch
        if ((item_template->Flags2 & ITEM_FLAG2_FACTION_HORDE && player->GetTeam() == ALLIANCE) ||  (item_template->Flags2 == ITEM_FLAG2_FACTION_ALLIANCE && player->GetTeam() == HORDE))
		{
			return true;
		}//if
        // --- sonst
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
// ******************************************************************************
// class
// ******************************************************************************
class NPC_Vendor_Multi : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Vendor_Multi() : CreatureScript("NPC_Vendor_Multi"){ }
	// ******************************************************************************
	// init
	// ******************************************************************************
	struct DBvector
	{
		uint32 entry;
	};
	vector<DBvector> DBdata;
	// ---
	std::vector<ItemList> GetVendorList()
	{
		std::vector<ItemList> itemlists;
		// ---
		Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Gruppe 1");
		ItemList items_1(&vendor_1);
		GetDBdata(0, 0, 0, 0);//class,subclass,inventorytype,itemlevel
		for (uint16 i = 0; i < DBdata.size(); i++)
		{
			items_1.AddItem(DBdata[i].entry); // 
		}//for
		itemlists.push_back(items_1);
		// ---
		Vendor vendor_2(700001, GOSSIP_ICON_VENDOR, "Gruppe 2");
		ItemList items_2(&vendor_2);
		GetDBdata(0, 1, 0, 0);//class,subclass,inventorytype,itemlevel
		for (uint16 i = 0; i < DBdata.size(); i++)
		{
			items_2.AddItem(DBdata[i].entry); // 
		}//for
		itemlists.push_back(items_2);
		// ---
		Vendor vendor_3(700002, GOSSIP_ICON_VENDOR, "Gruppe 3");
		ItemList items_3(&vendor_3);
		GetDBdata(0, 2, 0, 0);//class,subclass,inventorytype,itemlevel
		for (uint16 i = 0; i < DBdata.size(); i++)
		{
			items_3.AddItem(DBdata[i].entry); // 
		}//for
		itemlists.push_back(items_3);
		// ---
		return itemlists;
    }
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
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
	// ******************************************************************************
	// GetDBdata
	// ******************************************************************************
	void GetDBdata(uint16 tclass, uint16 tsubclass, uint16 tinventorytype, uint16 titemlevel)
	{
		// ---
		DBdata.clear();
		// ---
		string zinventorytype = "=";
		string zitemlevel = "<=";
		if (tinventorytype == 0)
			zinventorytype = ">=";
		if (titemlevel == 0)
			zitemlevel = ">=";
		// ---
		QueryResult result = WorldDatabase.PQuery("SELECT entry FROM world.item_template WHERE class = '%u' AND subclass = '%u' AND InventoryType %s '%u' AND ItemLevel %s '%u' ORDER BY ItemLevel DESC, name ASC", tclass, tsubclass, zinventorytype, tinventorytype, zitemlevel, titemlevel);
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
					data.entry = fields[0].GetUInt32();
					// ---
					DBdata.push_back(data);
				}//if gueltig
			} while (result->NextRow());
		}
		else
		{
			TC_LOG_ERROR("misc", "DATABASE ERROR - NPC_Vendor_Multi");
		}
	}//GetDBdata
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Vendor_Multi()
{
    new NPC_Vendor_Multi;
}