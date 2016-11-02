/*
* Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/* SQL Flag 129 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameEventMgr.h"
#include "Player.h"
#include "WorldSession.h"

class Vendor
{
private:
	int m_GUID;
	GossipOptionIcon m_Icon;
	std::string m_Message;
public:
	Vendor() {}
	Vendor(int guid, GossipOptionIcon icon, std::string message)
	{
		m_GUID = guid;
		m_Icon = icon;
		m_Message = message;
	}

	Vendor(int guid, GossipOptionIcon icon, std::string message, VendorItemData* item_list)
	{
		m_GUID = guid;
		m_Icon = icon;
		m_Message = message;
		for (int i = 0; i < item_list->GetItemCount(); i++)
			items.AddItem(item_list->m_items[i]->item, 0, 0, item_list->m_items[i]->ExtendedCost);
	}

	VendorItemData items;

	int getGuid() { return m_GUID; }
	void setGuid(int guid) { m_GUID = guid; }
	GossipOptionIcon getIcon() { return m_Icon; }
	void setIcon(GossipOptionIcon icon) { m_Icon = icon; }
	std::string getMessage() { return m_Message; }
	void setMessage(std::string message) { m_Message = message; }
};

class ItemList
{
public:
	ItemList() { /* Called while looping through vendors to find ours */ }

	ItemList(Vendor* myVendor)
	{
		m_vendor = Vendor(myVendor->getGuid(), myVendor->getIcon(), myVendor->getMessage());
	}

	ItemList(Vendor* myVendor, VendorItemData* item_list)
	{
		m_vendor = Vendor(myVendor->getGuid(), myVendor->getIcon(), myVendor->getMessage());
		for (int i = 0; i < item_list->GetItemCount(); i++)
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
		if (m_vendors[0].GetItemCount() > 0)
		{
			if ((slot + 1) > (m_vendors[0].GetItemCount()))
			{
				int totalItemsChecked = 0;
				/* For each vendor */
				for (int i = 0; i < m_vendors.size(); i++)
				{
					if ((totalItemsChecked + m_vendors[i].GetItemCount()) < (slot + 1))
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
		if (VendorItem* vendor_item = m_vendorItemData.GetItem(slot))
		{
			if (vendor_item->item != item_template->ItemId)
				return true;
		}
		else
			return true; // the item doesn't even exist why would we send it

						 /* GM's are exceptions */
		if (player->isGameMaster())
			return false;

		/* If the item is class specific and Bind on Pickup */
		if (!(item_template->AllowableClass & player->getClassMask()) && item_template->Bonding == BIND_WHEN_PICKED_UP)
			return true;

		/* If the item is faction specific and player is wrong faction */
		if ((item_template->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == ALLIANCE) ||
			(item_template->Flags2 == ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == HORDE))
			return true;

		/* Anything else */
		return false;
	}

public: SmsgListInventory(uint64 vendor_guid, WorldSession* player_session, VendorItemData* vendor_item_data, std::vector<ItemList> vendors)
{
	m_opcode = SMSG_LIST_INVENTORY;
	m_vendorGuid = vendor_guid;
	m_itemCount = 0;
	for (int i = 0; i < vendors.size(); i++)
		m_itemCount += vendors[i].GetItemCount();

	m_status = 0;
	m_session = player_session;
	for (int i = 0; i < vendors.size(); i++)
		for (int i2 = 0; i2 < vendors[i].GetItemCount(); i2++)
			m_completeVendorItemData.AddItem(vendors[i].GetVendor().items.m_items[i2]->item, 0, 0, vendors[i].GetVendor().items.m_items[i2]->ExtendedCost);

	for (int i = 0; i < vendor_item_data->GetItemCount(); i++)
		m_vendorItemData.AddItem(vendor_item_data->m_items[i]->item, 0, 0, vendor_item_data->m_items[i]->ExtendedCost);

	for (int i = 0; i < vendors.size(); i++)
		m_vendors.push_back(vendors[i]);
}

		void Send(Creature* originalVendor, Player* player)
		{
			uint8 item_count = 0;
			std::vector<packetItem> items_to_send;
			ItemList item_list_to_send;
			bool haveUpdatedVendor = false;
			if (const VendorItemData* vendor_item_data = originalVendor->GetVendorItems())
				if (vendor_item_data->GetItemCount() > 0)
					haveUpdatedVendor = true;

			for (int slot = 0; slot < m_itemCount; slot++)
				if (VendorItem const* item = m_completeVendorItemData.GetItem(slot))
					if (ItemTemplate const* item_template = sObjectMgr->GetItemTemplate(item->item))
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
					}

			WorldPacket packet(m_opcode, 8 + 1 + (m_itemCount > 0 ? m_itemCount * 8 * 4 : 1));
			packet << m_vendorGuid;
			packet << item_count;
			for (int i = 0; i < items_to_send.size(); i++)
			{
				packet << items_to_send[i].m_slot;
				packet << items_to_send[i].m_item;
				packet << items_to_send[i].m_displayId;
				packet << items_to_send[i].m_inStock;
				packet << items_to_send[i].m_price;
				packet << items_to_send[i].m_durability;
				packet << items_to_send[i].m_buyCount;
				packet << items_to_send[i].m_extendedCost;
			}
			m_session->SendPacket(&packet);
		}
};

class npc_multivendor : public CreatureScript
{
public:
	npc_multivendor() : CreatureScript("npc_multivendor") { }

	std::vector<ItemList> GetVendorList()
	{
		std::vector<ItemList> itemlists;

		/* ONLY EDIT THINGS BELOW THIS COMMENT BLOCK
		* DO NOT EDIT ANYTHING ELSE
		*
		* Example vendor:

		Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Look at all the weapons I have");
		ItemList items_1(&vendor_1);
		items_1.AddItem(18582); // Azzinoth
		items_1.AddItem(13262); // Ashbringer
		itemlists.push_back(items_1);

		* The first line creates a "Vendor" object named vendor_1 with:
		*     GUID 700000 (this must be different to all your other vendors)
		*     Displays the moneybag icon in the gossip list
		*     Displays the text "Look at all the weapons I have" in the gossip list
		*
		* The second line creates an instance of the ItemList object named items1.
		*     We pass it a reference to the vendor we created before. The class does the rest.
		*
		* The third and fourth lines are examples of adding items to our item list (named items_1).
		*     You can give an item an extended_cost by passing a second parameter to the function.
		*     This script does not support time-limited or respawning items
		*
		* The final line is the most important. This line adds your vendor to the internal list of vendors that will be processed by the script.
		*
		*
		* END OF EXPLANATION
		* I REPEAT ONCE MORE PLEASE DO NOT TOUCH ANYTHING ELSE IN THE FILE IT IS EXTREMELY DELICATE AND EXTREMELY COMPLEX
		*/

		Vendor vendor_1(700000, GOSSIP_ICON_VENDOR, "Cloth Armor");
		ItemList items_1(&vendor_1);
		items_1.AddItem(14150);
		items_1.AddItem(48691);
		items_1.AddItem(14371);
		items_1.AddItem(1486);
		items_1.AddItem(14369);
		items_1.AddItem(5202);
		items_1.AddItem(6226);
		items_1.AddItem(6264);
		items_1.AddItem(6465);
		items_1.AddItem(4320);
		items_1.AddItem(14374);
		items_1.AddItem(3065);
		items_1.AddItem(3076);
		items_1.AddItem(9767);
		items_1.AddItem(14159);
		items_1.AddItem(1560);
		items_1.AddItem(3066);
		items_1.AddItem(3074);
		items_1.AddItem(5970);
		items_1.AddItem(5195);
		items_1.AddItem(14162);
		items_1.AddItem(1974);
		items_1.AddItem(14148);
		items_1.AddItem(3647);
		items_1.AddItem(12987);
		items_1.AddItem(4316);
		items_1.AddItem(6568);
		items_1.AddItem(14171);
		items_1.AddItem(4708);
		items_1.AddItem(4785);
		items_1.AddItem(2911);
		items_1.AddItem(3229);
		items_1.AddItem(1299);
		items_1.AddItem(6570);
		items_1.AddItem(9766);
		items_1.AddItem(4314);
		items_1.AddItem(4315);
		items_1.AddItem(19972);
		itemlists.push_back(items_1);

		Vendor vendor_2(700001, GOSSIP_ICON_VENDOR, "Leather Armor");
		ItemList items_2(&vendor_2);
		items_2.AddItem(48687);
		items_2.AddItem(48689);
		items_2.AddItem(6473);
		items_2.AddItem(10399);
		items_2.AddItem(2314);
		items_2.AddItem(14562);
		items_2.AddItem(9782);
		items_2.AddItem(1121);
		items_2.AddItem(3057);
		items_2.AddItem(10411);
		items_2.AddItem(14568);
		items_2.AddItem(6582);
		items_2.AddItem(14572);
		items_2.AddItem(7285);
		items_2.AddItem(7284);
		items_2.AddItem(10413);
		items_2.AddItem(6586);
		items_2.AddItem(3230);
		items_2.AddItem(3202);
		items_2.AddItem(3205);
		items_2.AddItem(15331);
		items_2.AddItem(10410);
		items_2.AddItem(3022);
		items_2.AddItem(5199);
		items_2.AddItem(15117);
		items_2.AddItem(6587);
		items_2.AddItem(6319);
		items_2.AddItem(3429);
		items_2.AddItem(6468);
		items_2.AddItem(14567);
		items_2.AddItem(6382);
		items_2.AddItem(5975);
		items_2.AddItem(10403);
		items_2.AddItem(5404);
		items_2.AddItem(5254);
		items_2.AddItem(23909);
		items_2.AddItem(7997);
		itemlists.push_back(items_2);

		Vendor vendor_3(700002, GOSSIP_ICON_VENDOR, "Mail Armor");
		ItemList items_3(&vendor_3);
		items_3.AddItem(48677);
		items_3.AddItem(48683);
		items_3.AddItem(48685);
		items_3.AddItem(2866);
		items_3.AddItem(14730);
		items_3.AddItem(15500);
		items_3.AddItem(6580);
		items_3.AddItem(14742);
		items_3.AddItem(6459);
		items_3.AddItem(6573);
		items_3.AddItem(12982);
		items_3.AddItem(12994);
		items_3.AddItem(14747);
		items_3.AddItem(1448);
		items_3.AddItem(15509);
		items_3.AddItem(6577);
		items_3.AddItem(5943);
		items_3.AddItem(14147);
		items_3.AddItem(2867);
		items_3.AddItem(14743);
		items_3.AddItem(6574);
		items_3.AddItem(4816);
		items_3.AddItem(4800);
		items_3.AddItem(6087);
		items_3.AddItem(15511);
		items_3.AddItem(6578);
		items_3.AddItem(6460);
		items_3.AddItem(5750);
		items_3.AddItem(14746);
		items_3.AddItem(5425);
		items_3.AddItem(12978);
		items_3.AddItem(3480);
		items_3.AddItem(19972);
		itemlists.push_back(items_3);

		Vendor vendor_4(700003, GOSSIP_ICON_VENDOR, "One-Hand Weapons");
		ItemList items_4(&vendor_4);
		items_4.AddItem(885);
		items_4.AddItem(1459);
		items_4.AddItem(2807);
		items_4.AddItem(12990);
		items_4.AddItem(4445);
		items_4.AddItem(5196);
		items_4.AddItem(790);
		items_4.AddItem(42948);
		items_4.AddItem(44094);
		items_4.AddItem(48716);
		items_4.AddItem(2256);
		items_4.AddItem(6472);
		items_4.AddItem(5197);
		items_4.AddItem(1483);
		items_4.AddItem(2848);
		items_4.AddItem(15223);
		items_4.AddItem(44096);
		items_4.AddItem(42945);
		items_4.AddItem(5191);
		items_4.AddItem(1482);
		items_4.AddItem(6633);
		items_4.AddItem(20430);
		items_4.AddItem(20440);
		items_4.AddItem(5192);
		items_4.AddItem(2850);
		items_4.AddItem(1935);
		items_4.AddItem(2567);
		items_4.AddItem(20441);
		items_4.AddItem(20443);
		items_4.AddItem(5540);
		items_4.AddItem(6448);
		items_4.AddItem(2169);
		itemlists.push_back(items_4);

		Vendor vendor_5(700004, GOSSIP_ICON_VENDOR, "Two-Hand Weapons");
		ItemList items_5(&vendor_5);
		items_5.AddItem(3415);
		items_5.AddItem(890);
		items_5.AddItem(20425);
		items_5.AddItem(5201);
		items_5.AddItem(20434);
		items_5.AddItem(2271);
		items_5.AddItem(880);
		items_5.AddItem(1484);
		items_5.AddItem(1455);
		items_5.AddItem(1318);
		items_5.AddItem(5194);
		items_5.AddItem(5749);
		items_5.AddItem(2175);
		items_5.AddItem(872);
		items_5.AddItem(15269);
		items_5.AddItem(3199);
		items_5.AddItem(7230);
		items_5.AddItem(1458);
		items_5.AddItem(3194);
		items_5.AddItem(12983);
		items_5.AddItem(3198);
		items_5.AddItem(12992);
		items_5.AddItem(4818);
		items_5.AddItem(4817);
		itemlists.push_back(items_5);

		Vendor vendor_6(700005, GOSSIP_ICON_VENDOR, "Jewelry");
		ItemList items_6(&vendor_6);
		items_6.AddItem(20442);
		items_6.AddItem(20444);
		items_6.AddItem(21933);
		items_6.AddItem(21934);
		items_6.AddItem(25438);
		items_6.AddItem(12996);
		items_6.AddItem(20426);
		items_6.AddItem(20429);
		items_6.AddItem(20431);
		items_6.AddItem(20439);
		items_6.AddItem(30804);
		items_6.AddItem(12985);
		items_6.AddItem(6332);
		items_6.AddItem(24120);
		items_6.AddItem(24119);
		items_6.AddItem(24118);
		items_6.AddItem(12054);
		items_6.AddItem(42991);
		items_6.AddItem(42992);
		items_6.AddItem(19024);
		items_6.AddItem(1490);
		items_6.AddItem(10727);
		items_6.AddItem(19141);
		items_6.AddItem(10779);
		items_6.AddItem(10659);
		items_6.AddItem(19120);
		items_6.AddItem(40476);
		items_6.AddItem(40477);
		itemlists.push_back(items_6);

		Vendor vendor_7(700006, GOSSIP_ICON_VENDOR, "Cloaks and Off-Hands");
		ItemList items_7(&vendor_7);
		items_7.AddItem(2059);
		items_7.AddItem(45626);
		items_7.AddItem(6629);
		items_7.AddItem(20427);
		items_7.AddItem(20428);
		items_7.AddItem(6449);
		items_7.AddItem(4706);
		items_7.AddItem(4793);
		items_7.AddItem(4792);
		items_7.AddItem(4710);
		items_7.AddItem(9805);
		items_7.AddItem(6383);
		items_7.AddItem(4444);
		items_7.AddItem(12997);
		items_7.AddItem(6320);
		items_7.AddItem(2879);
		items_7.AddItem(6341);
		items_7.AddItem(43515);
		items_7.AddItem(5183);
		items_7.AddItem(15912);
		itemlists.push_back(items_7);

		Vendor vendor_8(700007, GOSSIP_ICON_VENDOR, "Enchants");
		ItemList items_8(&vendor_8);
		items_8.AddItem(38838);
		items_8.AddItem(38873);
		items_8.AddItem(38879);
		items_8.AddItem(38884);
		items_8.AddItem(38868);
		items_8.AddItem(38877);
		items_8.AddItem(38880);
		items_8.AddItem(38896);
		items_8.AddItem(38872);
		items_8.AddItem(38835);
		items_8.AddItem(38859);
		items_8.AddItem(38891);
		items_8.AddItem(38892);
		items_8.AddItem(38893);
		items_8.AddItem(38894);
		items_8.AddItem(38865);
		items_8.AddItem(38866);
		items_8.AddItem(38867);
		items_8.AddItem(38852);
		items_8.AddItem(38853);
		items_8.AddItem(38854);
		items_8.AddItem(38855);
		items_8.AddItem(38881);
		items_8.AddItem(38882);
		items_8.AddItem(38851);
		items_8.AddItem(38885);
		items_8.AddItem(38886);
		items_8.AddItem(38887);
		items_8.AddItem(38888);
		items_8.AddItem(38890);
		items_8.AddItem(38862);
		items_8.AddItem(38863);
		items_8.AddItem(38837);
		items_8.AddItem(38861);
		items_8.AddItem(38860);
		items_8.AddItem(4406);
		items_8.AddItem(11642);
		items_8.AddItem(11645);
		items_8.AddItem(11646);
		items_8.AddItem(11647);
		items_8.AddItem(11648);
		items_8.AddItem(11649);
		items_8.AddItem(18330);
		items_8.AddItem(18329);
		items_8.AddItem(18331);
		items_8.AddItem(11643);
		items_8.AddItem(11644);
		itemlists.push_back(items_8);

		Vendor vendor_9(700008, GOSSIP_ICON_VENDOR, "Bags");
		ItemList items_9(&vendor_9);
		items_9.AddItem(804);
		items_9.AddItem(805);
		items_9.AddItem(828);
		items_9.AddItem(856);
		items_9.AddItem(857);
		items_9.AddItem(918);
		items_9.AddItem(932);
		items_9.AddItem(933);
		items_9.AddItem(1470);
		items_9.AddItem(1537);
		items_9.AddItem(1652);
		items_9.AddItem(1685);
		items_9.AddItem(1725);
		items_9.AddItem(1729);
		items_9.AddItem(2082);
		items_9.AddItem(2657);
		items_9.AddItem(3233);
		items_9.AddItem(3343);
		items_9.AddItem(3352);
		items_9.AddItem(3914);
		items_9.AddItem(4238);
		items_9.AddItem(4240);
		items_9.AddItem(4241);
		items_9.AddItem(4245);
		items_9.AddItem(4496);
		items_9.AddItem(4497);
		items_9.AddItem(4498);
		items_9.AddItem(4499);
		items_9.AddItem(4500);
		items_9.AddItem(4957);
		items_9.AddItem(5081);
		items_9.AddItem(5571);
		items_9.AddItem(5572);
		items_9.AddItem(5573);
		items_9.AddItem(5574);
		items_9.AddItem(5575);
		items_9.AddItem(5576);
		items_9.AddItem(5762);
		items_9.AddItem(5763);
		items_9.AddItem(5764);
		items_9.AddItem(5765);
		items_9.AddItem(6446);
		items_9.AddItem(6756);
		items_9.AddItem(9587);
		items_9.AddItem(10050);
		items_9.AddItem(10051);
		items_9.AddItem(10959);
		items_9.AddItem(11324);
		items_9.AddItem(11742);
		items_9.AddItem(11845);
		items_9.AddItem(14046);
		items_9.AddItem(14155);
		items_9.AddItem(14156);
		items_9.AddItem(17966);
		items_9.AddItem(19291);
		items_9.AddItem(19914);
		items_9.AddItem(20400);
		items_9.AddItem(20474);
		items_9.AddItem(21340);
		items_9.AddItem(21341);
		items_9.AddItem(21342);
		items_9.AddItem(21841);
		items_9.AddItem(21843);
		items_9.AddItem(21858);
		items_9.AddItem(21872);
		items_9.AddItem(21876);
		items_9.AddItem(22243);
		items_9.AddItem(22244);
		items_9.AddItem(22246);
		items_9.AddItem(22248);
		items_9.AddItem(22249);
		items_9.AddItem(22250);
		items_9.AddItem(22251);
		items_9.AddItem(22252);
		items_9.AddItem(22571);
		items_9.AddItem(22679);
		items_9.AddItem(22976);
		items_9.AddItem(23162);
		items_9.AddItem(23389);
		items_9.AddItem(23774);
		items_9.AddItem(23775);
		items_9.AddItem(23852);
		items_9.AddItem(24270);
		items_9.AddItem(27680);
		items_9.AddItem(29540);
		items_9.AddItem(30744);
		items_9.AddItem(30745);
		items_9.AddItem(30746);
		items_9.AddItem(30747);
		items_9.AddItem(30748);
		items_9.AddItem(33117);
		items_9.AddItem(34067);
		items_9.AddItem(34482);
		items_9.AddItem(34490);
		items_9.AddItem(34845);
		items_9.AddItem(35516);
		items_9.AddItem(37606);
		items_9.AddItem(38082);
		items_9.AddItem(38145);
		items_9.AddItem(38225);
		items_9.AddItem(38347);
		items_9.AddItem(38399);
		items_9.AddItem(39489);
		items_9.AddItem(41597);
		items_9.AddItem(41598);
		items_9.AddItem(41599);
		items_9.AddItem(41600);
		items_9.AddItem(43345);
		items_9.AddItem(44446);
		items_9.AddItem(45773);
		items_9.AddItem(49295);
		items_9.AddItem(50316);
		items_9.AddItem(50317);
		items_9.AddItem(51809);
		itemlists.push_back(items_9);

		Vendor vendor_10(700009, GOSSIP_ICON_VENDOR, "Pets");
		ItemList items_10(&vendor_10);
		items_10.AddItem(4401);
		items_10.AddItem(8485);
		items_10.AddItem(8486);
		items_10.AddItem(8487);
		items_10.AddItem(8488);
		items_10.AddItem(8489);
		items_10.AddItem(8490);
		items_10.AddItem(8491);
		items_10.AddItem(8492);
		items_10.AddItem(8494);
		items_10.AddItem(8495);
		items_10.AddItem(8496);
		items_10.AddItem(8497);
		items_10.AddItem(8498);
		items_10.AddItem(8499);
		items_10.AddItem(8500);
		items_10.AddItem(8501);
		items_10.AddItem(10360);
		items_10.AddItem(10361);
		items_10.AddItem(10392);
		items_10.AddItem(10393);
		items_10.AddItem(10394);
		items_10.AddItem(10398);
		items_10.AddItem(10822);
		items_10.AddItem(11023);
		items_10.AddItem(11026);
		items_10.AddItem(11027);
		items_10.AddItem(11110);
		items_10.AddItem(11474);
		items_10.AddItem(11825);
		items_10.AddItem(11826);
		items_10.AddItem(12264);
		items_10.AddItem(12529);
		items_10.AddItem(15996);
		items_10.AddItem(18964);
		items_10.AddItem(19450);
		items_10.AddItem(19462);
		items_10.AddItem(20769);
		items_10.AddItem(21168);
		items_10.AddItem(21277);
		items_10.AddItem(21301);
		items_10.AddItem(21305);
		items_10.AddItem(21308);
		items_10.AddItem(21309);
		items_10.AddItem(22200);
		items_10.AddItem(22235);
		items_10.AddItem(23002);
		items_10.AddItem(23007);
		items_10.AddItem(23015);
		items_10.AddItem(23083);
		items_10.AddItem(27445);
		items_10.AddItem(29363);
		items_10.AddItem(29364);
		items_10.AddItem(29901);
		items_10.AddItem(29902);
		items_10.AddItem(29903);
		items_10.AddItem(29904);
		items_10.AddItem(29953);
		items_10.AddItem(29956);
		items_10.AddItem(29957);
		items_10.AddItem(29958);
		items_10.AddItem(29960);
		items_10.AddItem(31760);
		items_10.AddItem(32233);
		items_10.AddItem(32616);
		items_10.AddItem(32617);
		items_10.AddItem(32622);
		items_10.AddItem(33154);
		items_10.AddItem(33816);
		items_10.AddItem(33818);
		items_10.AddItem(33993);
		items_10.AddItem(34425);
		items_10.AddItem(34478);
		items_10.AddItem(34518);
		items_10.AddItem(34519);
		items_10.AddItem(34535);
		items_10.AddItem(34955);
		items_10.AddItem(35349);
		items_10.AddItem(35350);
		items_10.AddItem(35504);
		items_10.AddItem(37297);
		items_10.AddItem(37298);
		items_10.AddItem(37460);
		items_10.AddItem(38628);
		items_10.AddItem(38658);
		items_10.AddItem(39896);
		items_10.AddItem(39898);
		items_10.AddItem(39899);
		items_10.AddItem(39973);
		items_10.AddItem(40653);
		items_10.AddItem(41133);
		items_10.AddItem(43698);
		items_10.AddItem(44721);
		items_10.AddItem(44723);
		items_10.AddItem(44738);
		items_10.AddItem(44794);
		items_10.AddItem(44810);
		items_10.AddItem(44819);
		items_10.AddItem(44820);
		items_10.AddItem(44822);
		items_10.AddItem(44841);
		items_10.AddItem(44965);
		items_10.AddItem(44970);
		items_10.AddItem(44971);
		items_10.AddItem(44973);
		items_10.AddItem(44974);
		items_10.AddItem(44980);
		items_10.AddItem(44982);
		items_10.AddItem(44983);
		items_10.AddItem(44984);
		items_10.AddItem(44998);
		items_10.AddItem(45002);
		items_10.AddItem(45022);
		items_10.AddItem(45057);
		items_10.AddItem(45180);
		items_10.AddItem(45606);
		items_10.AddItem(45942);
		items_10.AddItem(46396);
		items_10.AddItem(46397);
		items_10.AddItem(46398);
		items_10.AddItem(46544);
		items_10.AddItem(46545);
		items_10.AddItem(46707);
		items_10.AddItem(46767);
		items_10.AddItem(46820);
		items_10.AddItem(46821);
		items_10.AddItem(46831);
		items_10.AddItem(48112);
		items_10.AddItem(48114);
		items_10.AddItem(48116);
		items_10.AddItem(48118);
		items_10.AddItem(48120);
		items_10.AddItem(48122);
		items_10.AddItem(48124);
		items_10.AddItem(48126);
		items_10.AddItem(49362);
		items_10.AddItem(49646);
		items_10.AddItem(49662);
		items_10.AddItem(49663);
		items_10.AddItem(49912);
		items_10.AddItem(50446);
		items_10.AddItem(54436);
		itemlists.push_back(items_10);

		Vendor vendor_11(700010, GOSSIP_ICON_VENDOR, "General Goods");
		ItemList items_11(&vendor_11);
		items_11.AddItem(21215);
		items_11.AddItem(6265);
		items_11.AddItem(17056);
		items_11.AddItem(5175);
		items_11.AddItem(5177);
		items_11.AddItem(5178);
		items_11.AddItem(5176);
		items_11.AddItem(2515);
		items_11.AddItem(2519);
		itemlists.push_back(items_11);

		Vendor vendor_12(700011, GOSSIP_ICON_VENDOR, "Potions and Scrolls");
		ItemList items_12(&vendor_10);
		items_12.AddItem(929);
		items_12.AddItem(3385);
		items_12.AddItem(6048);
		items_12.AddItem(5632);
		items_12.AddItem(3386);
		items_12.AddItem(3384);
		items_12.AddItem(6372);
		items_12.AddItem(6051);
		items_12.AddItem(2459);
		items_12.AddItem(2456);
		items_12.AddItem(5631);
		items_12.AddItem(38351);
		items_12.AddItem(2289);
		items_12.AddItem(1711);
		items_12.AddItem(1712);
		items_12.AddItem(1478);
		items_12.AddItem(2290);
		items_12.AddItem(1477);
		itemlists.push_back(items_12);

		Vendor vendor_13(700012, GOSSIP_ICON_VENDOR, "Enchanting Materials");
		ItemList items_13(&vendor_13);
		items_13.AddItem(6217);
		items_13.AddItem(6338);
		items_13.AddItem(11128);
		items_13.AddItem(4470);
		items_13.AddItem(10940);
		items_13.AddItem(11083);
		items_13.AddItem(10938);
		items_13.AddItem(10939);
		items_13.AddItem(10998);
		items_13.AddItem(11082);
		items_13.AddItem(10978);
		items_13.AddItem(11084);
		items_13.AddItem(17034);
		items_13.AddItem(5500);
		items_13.AddItem(2772);
		items_13.AddItem(3356);
		items_13.AddItem(6048);
		items_13.AddItem(6370);
		items_13.AddItem(6371);
		items_13.AddItem(3371);
		items_13.AddItem(3372);
		itemlists.push_back(items_13);

		Vendor vendor_14(700013, GOSSIP_ICON_VENDOR, "Enchanting Recipes");
		ItemList items_14(&vendor_14);
		items_14.AddItem(20758);
		items_14.AddItem(6342);
		items_14.AddItem(11150);
		items_14.AddItem(11101);
		items_14.AddItem(11098);
		items_14.AddItem(6377);
		items_14.AddItem(6375);
		items_14.AddItem(11081);
		items_14.AddItem(11039);
		items_14.AddItem(11038);
		items_14.AddItem(6349);
		items_14.AddItem(6348);
		items_14.AddItem(6347);
		items_14.AddItem(6346);
		items_14.AddItem(6344);
		items_14.AddItem(20752);
		items_14.AddItem(11152);
		items_14.AddItem(11151);
		itemlists.push_back(items_14);

		Vendor vendor_15(700014, GOSSIP_ICON_VENDOR, "Alchemy Materials");
		ItemList items_15(&vendor_15);
		items_15.AddItem(3371);
		items_15.AddItem(3372);
		items_15.AddItem(2447);
		items_15.AddItem(765);
		items_15.AddItem(2449);
		items_15.AddItem(785);
		items_15.AddItem(2452);
		items_15.AddItem(2450);
		items_15.AddItem(3164);
		items_15.AddItem(5635);
		items_15.AddItem(6358);
		items_15.AddItem(6522);
		items_15.AddItem(3820);
		items_15.AddItem(6370);
		items_15.AddItem(2453);
		items_15.AddItem(3355);
		items_15.AddItem(1288);
		items_15.AddItem(6359);
		items_15.AddItem(3369);
		items_15.AddItem(6371);
		items_15.AddItem(3356);
		itemlists.push_back(items_15);

		Vendor vendor_16(700015, GOSSIP_ICON_VENDOR, "Alchemy Recipes");
		ItemList items_16(&vendor_16);
		items_16.AddItem(44508);
		items_16.AddItem(2553);
		items_16.AddItem(4597);
		items_16.AddItem(2555);
		items_16.AddItem(5640);
		items_16.AddItem(6663);
		items_16.AddItem(6053);
		items_16.AddItem(3393);
		items_16.AddItem(3394);
		items_16.AddItem(6054);
		items_16.AddItem(3396);
		items_16.AddItem(6211);
		items_16.AddItem(5642);
		itemlists.push_back(items_16);

		Vendor vendor_17(700016, GOSSIP_ICON_VENDOR, "Engineering Materials");
		ItemList items_17(&vendor_17);
		items_17.AddItem(2835);
		items_17.AddItem(4382);
		items_17.AddItem(4357);
		items_17.AddItem(2589);
		items_17.AddItem(2840);
		items_17.AddItem(4359);
		items_17.AddItem(4361);
		items_17.AddItem(4399);
		items_17.AddItem(2880);
		items_17.AddItem(774);
		items_17.AddItem(2836);
		items_17.AddItem(4364);
		items_17.AddItem(4363);
		items_17.AddItem(2841);
		items_17.AddItem(2592);
		items_17.AddItem(2842);
		items_17.AddItem(2318);
		items_17.AddItem(818);
		items_17.AddItem(159);
		items_17.AddItem(4404);
		items_17.AddItem(2319);
		items_17.AddItem(4371);
		items_17.AddItem(1206);
		items_17.AddItem(1210);
		items_17.AddItem(2838);
		items_17.AddItem(4377);
		items_17.AddItem(4375);
		items_17.AddItem(4402);
		items_17.AddItem(814);
		items_17.AddItem(4234);
		items_17.AddItem(1705);
		items_17.AddItem(6530);
		items_17.AddItem(3577);
		items_17.AddItem(4368);
		itemlists.push_back(items_17);

		Vendor vendor_18(700017, GOSSIP_ICON_VENDOR, "Engineering Recipes");
		ItemList items_18(&vendor_18);
		items_18.AddItem(4408);
		items_18.AddItem(6716);
		items_18.AddItem(4409);
		items_18.AddItem(4410);
		items_18.AddItem(13309);
		items_18.AddItem(21726);
		items_18.AddItem(21725);
		items_18.AddItem(21724);
		items_18.AddItem(4411);
		items_18.AddItem(7560);
		items_18.AddItem(14639);
		items_18.AddItem(4412);
		items_18.AddItem(18647);
		items_18.AddItem(18648);
		items_18.AddItem(18649);
		itemlists.push_back(items_18);

		Vendor vendor_19(700018, GOSSIP_ICON_VENDOR, "Inscription Materials");
		ItemList items_19(&vendor_19);
		items_19.AddItem(39469);
		items_19.AddItem(43118);
		items_19.AddItem(43120);
		items_19.AddItem(43124);
		items_19.AddItem(43126);
		items_19.AddItem(43115);
		items_19.AddItem(43117);
		items_19.AddItem(39774);
		items_19.AddItem(43116);
		items_19.AddItem(39151);
		items_19.AddItem(37101);
		items_19.AddItem(39354);
		items_19.AddItem(39334);
		items_19.AddItem(10648);
		items_19.AddItem(39501);
		items_19.AddItem(39502);
		items_19.AddItem(43103);
		items_19.AddItem(39338);
		items_19.AddItem(43104);
		items_19.AddItem(39339);
		itemlists.push_back(items_19);

		Vendor vendor_20(700019, GOSSIP_ICON_VENDOR, "Jewelcrafting Materials");
		ItemList items_20(&vendor_20);
		items_20.AddItem(2840);
		items_20.AddItem(2835);
		items_20.AddItem(20816);
		items_20.AddItem(774);
		items_20.AddItem(818);
		items_20.AddItem(2841);
		items_20.AddItem(2836);
		items_20.AddItem(2842);
		items_20.AddItem(1210);
		items_20.AddItem(5498);
		items_20.AddItem(20817);
		items_20.AddItem(1206);
		items_20.AddItem(1705);
		items_20.AddItem(1529);
		items_20.AddItem(3575);
		items_20.AddItem(2838);
		items_20.AddItem(5637);
		items_20.AddItem(11083);
		items_20.AddItem(3827);
		items_20.AddItem(3391);
		items_20.AddItem(3577);
		items_20.AddItem(3864);
		items_20.AddItem(20963);
		itemlists.push_back(items_20);

		Vendor vendor_21(700020, GOSSIP_ICON_VENDOR, "Jewelcrafting Recipes");
		ItemList items_21(&vendor_21);
		items_21.AddItem(20854);
		items_21.AddItem(20970);
		items_21.AddItem(20971);
		items_21.AddItem(20855);
		items_21.AddItem(20973);
		items_21.AddItem(20856);
		itemlists.push_back(items_21);

		Vendor vendor_22(700021, GOSSIP_ICON_VENDOR, "Leatherworking Materials");
		ItemList items_22(&vendor_22);
		items_22.AddItem(2934);
		items_22.AddItem(2318);
		items_22.AddItem(2320);
		items_22.AddItem(783);
		items_22.AddItem(4289);
		items_22.AddItem(5082);
		items_22.AddItem(2324);
		items_22.AddItem(4231);
		items_22.AddItem(2321);
		items_22.AddItem(5498);
		items_22.AddItem(6470);
		items_22.AddItem(4232);
		items_22.AddItem(2319);
		items_22.AddItem(7286);
		items_22.AddItem(4340);
		items_22.AddItem(4243);
		items_22.AddItem(2997);
		items_22.AddItem(6471);
		items_22.AddItem(5784);
		items_22.AddItem(3383);
		items_22.AddItem(2457);
		items_22.AddItem(7287);
		items_22.AddItem(5373);
		items_22.AddItem(4233);
		items_22.AddItem(3389);
		items_22.AddItem(3182);
		items_22.AddItem(7067);
		items_22.AddItem(3356);
		items_22.AddItem(3390);
		items_22.AddItem(4234);
		items_22.AddItem(4235);
		items_22.AddItem(5637);
		itemlists.push_back(items_22);

		Vendor vendor_23(700022, GOSSIP_ICON_VENDOR, "Leatherworking Recipes");
		ItemList items_23(&vendor_23);
		items_23.AddItem(7288);
		items_23.AddItem(5083);
		items_23.AddItem(2407);
		items_23.AddItem(2408);
		items_23.AddItem(6710);
		items_23.AddItem(5786);
		items_23.AddItem(2406);
		items_23.AddItem(6474);
		items_23.AddItem(5787);
		items_23.AddItem(2409);
		items_23.AddItem(4293);
		items_23.AddItem(20576);
		items_23.AddItem(7289);
		items_23.AddItem(5972);
		items_23.AddItem(6475);
		items_23.AddItem(6476);
		items_23.AddItem(7360);
		items_23.AddItem(4294);
		items_23.AddItem(7290);
		items_23.AddItem(7362);
		items_23.AddItem(7361);
		items_23.AddItem(4296);
		items_23.AddItem(7363);
		items_23.AddItem(7364);
		items_23.AddItem(4297);
		items_23.AddItem(18731);
		itemlists.push_back(items_23);

		Vendor vendor_24(700023, GOSSIP_ICON_VENDOR, "Tailoring Materials");
		ItemList items_24(&vendor_24);
		items_24.AddItem(2589);
		items_24.AddItem(2996);
		items_24.AddItem(2320);
		items_24.AddItem(2324);
		items_24.AddItem(2318);
		items_24.AddItem(2604);
		items_24.AddItem(6260);
		items_24.AddItem(2605);
		items_24.AddItem(2321);
		items_24.AddItem(2592);
		items_24.AddItem(2997);
		items_24.AddItem(5498);
		items_24.AddItem(4340);
		items_24.AddItem(2319);
		items_24.AddItem(4306);
		items_24.AddItem(4305);
		items_24.AddItem(3182);
		items_24.AddItem(4234);
		items_24.AddItem(929);
		itemlists.push_back(items_24);

		Vendor vendor_25(700024, GOSSIP_ICON_VENDOR, "Tailoring Recipes");
		ItemList items_25(&vendor_25);
		items_25.AddItem(2598);
		items_25.AddItem(6271);
		items_25.AddItem(6270);
		items_25.AddItem(5771);
		items_25.AddItem(6272);
		items_25.AddItem(4345);
		items_25.AddItem(4292);
		items_25.AddItem(4346);
		items_25.AddItem(6274);
		items_25.AddItem(2601);
		items_25.AddItem(5772);
		items_25.AddItem(6275);
		items_25.AddItem(10316);
		items_25.AddItem(6391);
		items_25.AddItem(6390);
		items_25.AddItem(4347);
		items_25.AddItem(4349);
		items_25.AddItem(4348);
		items_25.AddItem(14627);
		items_25.AddItem(4350);
		items_25.AddItem(7092);
		items_25.AddItem(7114);
		items_25.AddItem(7091);
		items_25.AddItem(5773);
		itemlists.push_back(items_25);

		Vendor vendor_26(700025, GOSSIP_ICON_VENDOR, "Ranged Weapons");
		ItemList items_26(&vendor_26);
		items_26.AddItem(6469);
		items_26.AddItem(20438);
		items_26.AddItem(20437);
		items_26.AddItem(3039);
		items_26.AddItem(13136);
		items_26.AddItem(4372);
		items_26.AddItem(29201);
		items_26.AddItem(29584);
		items_26.AddItem(5198);
		items_26.AddItem(12984);
		items_26.AddItem(5243);
		items_26.AddItem(11288);
		itemlists.push_back(items_26);

		Vendor vendor_27(700026, GOSSIP_ICON_VENDOR, "Mounts");
		ItemList items_27(&vendor_27);
		items_27.AddItem(29465);
		items_27.AddItem(29471);
		items_27.AddItem(29468);
		items_27.AddItem(29467);
		items_27.AddItem(35906);
		items_27.AddItem(29466);
		items_27.AddItem(29469);
		items_27.AddItem(29470);
		items_27.AddItem(29472);
		items_27.AddItem(34129);
		itemlists.push_back(items_27);

		/* DO NOT EDIT ANYTHING BELOW HERE EITHER
		* THIS IS THE END OF THE EDITABLE SECTION
		* ONLY EDIT THINGS ABOVE THIS COMMENT BLOCK UNLESS YOU _REALLY_ KNOW WHAT YOU'RE DOING
		*
		* Peace out
		* Evilfairy~ */

		return itemlists;
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		std::vector<ItemList> vendors = GetVendorList();

		/* DO NOT EDIT ANYTHING BELOW THIS LINE */
		for (int i = 0; i < vendors.size(); i++) // icon message sender guid
			player->ADD_GOSSIP_ITEM(vendors[i].GetVendor().getIcon(), vendors[i].GetVendor().getMessage(), GOSSIP_SENDER_MAIN, vendors[i].GetVendor().getGuid());

		player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
		player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		player->CLOSE_GOSSIP_MENU();

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
		for (int i = 0; i < vendors.size(); i++)
		{
			if (vendors[i].GetVendor().getGuid() == guid)
			{
				myVendor = ItemList(&vendors[i].GetVendor(), &vendors[i].GetVendor().items);
				break;
			}
		}

		SmsgListInventory inventory_packet(vendor->GetGUID(), player->GetSession(), &myVendor.GetVendor().items, vendors);
		inventory_packet.Send(vendor, player);
	}
};

void AddSC_npc_multivendor()
{
	new npc_multivendor;
}