#include "ScriptPCH.h"
#include "Language.h"
#include "Upgrade.h"
#include "Transmogrification.h"
#include "ObjectMgr.h"

class NPC_Upgrade : public CreatureScript
{
public:
	NPC_Upgrade() : CreatureScript("NPC_Upgrade") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		WorldSession* session = player->GetSession();
		for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
		{
			if (const char* slotName = GetSlotName(slot, session))
			{
				Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
				if (!newItem)
					continue;
				uint32 entry = newItem->GetEntry();
				std::string icon = sTransmogrification->GetItemIcon(entry, 30, 30, -18, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, icon + std::string(slotName) + isFullUpgrade(newItem, player), EQUIPMENT_SLOT_END, slot);
			}
		}
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
	{
		WorldSession* session = player->GetSession();
		player->PlayerTalkClass->ClearMenus();
		switch (sender)
		{
		case EQUIPMENT_SLOT_END: // Show items you can use
		{
			if (Item* oldItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, uiAction))
			{
				_items.erase(player->GetGUIDLow());
				_items.insert(std::pair<uint64, uint32>(player->GetGUIDLow(), oldItem->GetEntry()));

				//const ItemTemplate* oldItemTemplate = oldItem->GetTemplate();

				uint32 limit = 0;
				uint32 price = 0;

				for (ListeItems::ListeItemsContainer::iterator itr = ListeItems::instance()->_listeItems.begin(); itr != ListeItems::instance()->_listeItems.end(); itr++)
				{
					if (limit > 30)
						break;

					const ItemTemplate* newItemTemplate = sObjectMgr->GetItemTemplate(itr->first);

					InventoryResult msg = player->CanUseItem(newItemTemplate);
					if (msg != EQUIP_ERR_OK)
						continue;

					if (!isGoodItem(oldItem->GetTemplate(), *newItemTemplate))
						continue;

					std::ostringstream ss_name;
					ss_name << "|cffffffff|Hitem:" << newItemTemplate->ItemId << ":0:0:0:0:0:0:0:80|h[" << newItemTemplate->Name1 << "]|h|r";
					//creature->Whisper(ss_name.str(), LANG_UNIVERSAL, player);

					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, sTransmogrification->GetItemIcon(newItemTemplate->ItemId, 30, 30, -18, 0) + GetItemName(newItemTemplate, session), newItemTemplate->ItemId, uiAction, "Voulez-vous acheter cette objet ?" + setPrice(newItemTemplate), price, false);
					limit++;
				}

				if (limit == 0)
				{
					session->SendNotification("Il n'y a plus d'améliorations possibles pour cet objet.");
					OnGossipHello(player, creature);
					break;
				}

				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|t<-[Retour]", EQUIPMENT_SLOT_END + 1, 0);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			}
			else
			{
				session->SendNotification("Il n'y a pas d'améliorations pour cet objet.");
				OnGossipHello(player, creature);
			}
		} break;
		case EQUIPMENT_SLOT_END + 1: // Back
		{
			OnGossipHello(player, creature);
		} break;

		default: // item acheté
		{
			//uiaction = slot & sender = entry newitem
			if (!uiAction && !sender)
			{
				OnGossipHello(player, creature);
				player->GetSession()->SendNotification("Erreur.");
				break;
			}

			Item* oldItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, uiAction);
			if (!oldItem)
			{
				OnGossipHello(player, creature);
				player->GetSession()->SendNotification("Erreur.");
				break;
			}

			if (oldItem->GetTemplate()->ItemId != _items[player->GetGUIDLow()])
			{
				OnGossipHello(player, creature);
				player->GetSession()->SendNotification("Erreur.");
				break;
			}

			if (const ItemTemplate* newItem = sObjectMgr->GetItemTemplate(sender))
			{
				if (!achat(newItem, player))
				{
					player->GetSession()->SendNotification("Vous ne pouvez pas acheter cet objet.");
					OnGossipHello(player, creature);
					return false;
				}

				player->DestroyItem(INVENTORY_SLOT_BAG_0, uiAction, true);
				player->StoreNewItemInBestSlots(sender, 1);
				player->GetSession()->SendNotification("Votre objet à bien été upgrade.");
				player->SaveToDB();
			}
			else
				player->GetSession()->SendNotification("L'objet choisi n'a pas été trouvé.");

			OnGossipHello(player, creature);
		} break;
		}
		return true;
	}

private:

	std::map<uint64, uint32> _items; // _items[lowGUID][entryItem] = item

	std::string GetItemName(const ItemTemplate* itemTemplate, WorldSession* session)
	{
		std::string name = itemTemplate->Name1;
		int loc_idx = session->GetSessionDbLocaleIndex();
		if (loc_idx >= 0)
			if (ItemLocale const* il = sObjectMgr->GetItemLocale(itemTemplate->ItemId))
				sObjectMgr->GetLocaleString(il->Name, loc_idx, name);
		return name;
	}

	bool isGoodItem(const ItemTemplate* oldItemTemplate, const ItemTemplate& NewItemTemplate)
	{
		if (NewItemTemplate.Class == oldItemTemplate->Class &&
			NewItemTemplate.SubClass == oldItemTemplate->SubClass &&
			(NewItemTemplate.InventoryType == oldItemTemplate->InventoryType || (NewItemTemplate.InventoryType == INVTYPE_CHEST && oldItemTemplate->InventoryType == INVTYPE_ROBE) || (oldItemTemplate->InventoryType == INVTYPE_CHEST && NewItemTemplate.InventoryType == INVTYPE_ROBE)) &&
			NewItemTemplate.ItemLevel == (oldItemTemplate->ItemLevel + 100))
			return true;
		else
			return false;
	}

	std::string isFullUpgrade(Item* oldItem, Player* player)
	{
		if (!oldItem)
			return " |cffFF0000[ERREUR]";

		bool exist = ListeItems::instance()->_listeItems[oldItem->GetEntry()];

		if (!exist || exist == false)
			return " |cffFF0000[Indisponible]";

		return " |cff1F9521[Disponible]";
	}

	const char* GetSlotName(uint8 slot, WorldSession* /*session*/) const
	{
		switch (slot)
		{
		case EQUIPMENT_SLOT_HEAD: return  "Tête";// session->GetTrinityString(LANG_SLOT_NAME_HEAD);
		case EQUIPMENT_SLOT_NECK: return  "Cou";// session->GetTrinityString(LANG_SLOT_NAME_HEAD);
		case EQUIPMENT_SLOT_SHOULDERS: return  "Epaules";// session->GetTrinityString(LANG_SLOT_NAME_SHOULDERS);
		case EQUIPMENT_SLOT_BODY: return  "Chemise";// session->GetTrinityString(LANG_SLOT_NAME_BODY);
		case EQUIPMENT_SLOT_CHEST: return  "Torse";// session->GetTrinityString(LANG_SLOT_NAME_CHEST);
		case EQUIPMENT_SLOT_WAIST: return  "Ceinture";// session->GetTrinityString(LANG_SLOT_NAME_WAIST);
		case EQUIPMENT_SLOT_LEGS: return  "Jambes";// session->GetTrinityString(LANG_SLOT_NAME_LEGS);
		case EQUIPMENT_SLOT_FEET: return  "Pieds";// session->GetTrinityString(LANG_SLOT_NAME_FEET);
		case EQUIPMENT_SLOT_WRISTS: return  "Poignets";// session->GetTrinityString(LANG_SLOT_NAME_WRISTS);
		case EQUIPMENT_SLOT_HANDS: return  "Mains";// session->GetTrinityString(LANG_SLOT_NAME_HANDS);
		case EQUIPMENT_SLOT_FINGER1: return  "Bague[1]";// session->GetTrinityString(LANG_SLOT_NAME_HANDS);
		case EQUIPMENT_SLOT_FINGER2: return  "Bague[2]";// session->GetTrinityString(LANG_SLOT_NAME_HANDS);
		case EQUIPMENT_SLOT_BACK: return  "Cape";// session->GetTrinityString(LANG_SLOT_NAME_BACK);
		case EQUIPMENT_SLOT_TRINKET1: return  "Bijou[1]";// session->GetTrinityString(LANG_SLOT_NAME_HANDS);
		case EQUIPMENT_SLOT_TRINKET2: return  "Bijou[2]";// session->GetTrinityString(LANG_SLOT_NAME_HANDS);
		case EQUIPMENT_SLOT_MAINHAND: return  "Main droite";// session->GetTrinityString(LANG_SLOT_NAME_MAINHAND);
		case EQUIPMENT_SLOT_OFFHAND: return  "Main gauche";// session->GetTrinityString(LANG_SLOT_NAME_OFFHAND);
		case EQUIPMENT_SLOT_RANGED: return  "Armes à distance";// session->GetTrinityString(LANG_SLOT_NAME_RANGED);
		case EQUIPMENT_SLOT_TABARD: return  "Tabard";// session->GetTrinityString(LANG_SLOT_NAME_TABARD);
		default: return NULL;
		}
	}

	bool achat(const ItemTemplate* newItemTemplate, Player* player)
	{
		uint32 itemLevel = newItemTemplate->ItemLevel;
		uint32 ptHonneur = 0;
		uint32 ptArene = 0;
		uint32 embleme = 0;

		switch (newItemTemplate->InventoryType)
		{
		case INVTYPE_2HWEAPON:
			ptHonneur += 90000;
			ptArene += 750;
			break;
		case INVTYPE_RANGED:
			ptHonneur += 90000;
			ptArene += 750;
			break;
		case INVTYPE_WEAPON:
			ptHonneur += 45000;
			ptArene += 375;
			break;
		case INVTYPE_SHIELD:
			ptHonneur += 45000;
			ptArene += 375;
			break;
		case INVTYPE_RELIC:
			ptHonneur += 45000;
			ptArene += 375;
			break;
		case INVTYPE_CLOAK:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		case INVTYPE_FINGER:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		case INVTYPE_NECK:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		case INVTYPE_TRINKET:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		default:
			ptHonneur += 60000;
			ptArene += 500;
			break;
		}

		switch (itemLevel)
		{
		case 100:
			embleme = 100000;
			break;
		case 200:
			embleme = 100001;
			break;
		case 300:
			embleme = 100002;
			break;
		case 400:
			ptArene = 0;
			break;
		case 500:
			ptHonneur *= 2;
			ptArene = 0;
			break;
		case 600:
			ptHonneur *= 3;
			ptArene = 0;
			break;
		case 700:
			if (player->GetMaxPersonalArenaRatingRequirement(0) < 500)
				return false;
			ptHonneur *= 4;
			break;
		case 800:
			if (player->GetMaxPersonalArenaRatingRequirement(0) < 1000)
				return false;
			ptArene *= 1000 / 750;
			ptHonneur *= 5;
			break;
		case 900:
			if (player->GetMaxPersonalArenaRatingRequirement(0) < 1500)
				return false;
			ptArene *= 1.2;
			ptHonneur *= 6;
			break;
		case 1000:
			if (player->GetMaxPersonalArenaRatingRequirement(0) < 2000)
				return false;
			ptArene *= 1.3;
			ptHonneur *= 7;
			break;
		default:
			break;
		}

		if (embleme != 0)
		{
			if (player->HasItemCount(embleme, 1))
			{
				player->DestroyItemCount(embleme, 1, true);
				return true;
			}
			else
				return false;
		}

		if (player->GetHonorPoints() < ptHonneur)
			return false;

		if (player->GetArenaPoints() < ptArene)
			return false;

		player->SetHonorPoints(player->GetHonorPoints() - ptHonneur);
		player->SetArenaPoints(player->GetArenaPoints() - ptArene);
		return true;
	}

	void trAchat(const ItemTemplate* newItemTemplate, uint32 &honneur, uint32 &arene, uint16 &coteArene)
	{
		uint32 itemLevel = newItemTemplate->ItemLevel;
		uint32 ptHonneur = 0;
		uint32 ptArene = 0;
		uint16 cote = 0;
		uint32 embleme = 0;

		switch (newItemTemplate->InventoryType)
		{
		case INVTYPE_2HWEAPON:
			ptHonneur += 90000;
			ptArene += 750;
			break;
		case INVTYPE_RANGED:
			ptHonneur += 90000;
			ptArene += 750;
			break;
		case INVTYPE_WEAPON:
			ptHonneur += 45000;
			ptArene += 375;
			break;
		case INVTYPE_SHIELD:
			ptHonneur += 45000;
			ptArene += 375;
			break;
		case INVTYPE_RELIC:
			ptHonneur += 45000;
			ptArene += 375;
			break;
		case INVTYPE_CLOAK:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		case INVTYPE_FINGER:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		case INVTYPE_NECK:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		case INVTYPE_TRINKET:
			ptHonneur += 40000;
			ptArene += 250;
			break;
		default:
			ptHonneur += 60000;
			ptArene += 500;
			break;
		}

		switch (itemLevel)
		{
		case 100:
			embleme = 100000;
			break;
		case 200:
			embleme = 100001;
			break;
		case 300:
			embleme = 100002;
			break;
		case 400:
			ptArene = 0;
			break;
		case 500:
			ptHonneur *= 2;
			ptArene = 0;
			break;
		case 600:
			ptHonneur *= 3;
			ptArene = 0;
			break;
		case 700:
			cote = 500;
			ptHonneur *= 4;
			break;
		case 800:
			cote = 1000;
			ptArene *= 1000 / 750;
			ptHonneur *= 5;
			break;
		case 900:
			cote = 1500;
			ptArene *= 1.2;
			ptHonneur *= 6;
			break;
		case 1000:
			cote = 2000;
			ptArene *= 1.3;
			ptHonneur *= 7;
			break;
		default:
			break;
		}

		if (embleme != 0)
		{
			honneur = embleme;
			arene = embleme;
			coteArene = 0;
			return;
		}

		honneur = ptHonneur;
		arene = ptArene;
		coteArene = cote;
	}

	std::string setPrice(const ItemTemplate* newItemTemplate)
	{
		uint32 ptHonneur = 0;
		uint32 ptArene = 0;
		uint16 cote = 0;

		trAchat(newItemTemplate, ptHonneur, ptArene, cote);

		if (ptHonneur == ptArene)
		{
			std::ostringstream ss_name;
			ss_name << "\nCet objet coûte :\n  - 1 " << sObjectMgr->GetItemTemplate(ptArene)->Name1;
			return ss_name.str();
		}

		if (ptHonneur != 0)
		{
			std::ostringstream ss_name;
			ss_name << "\nCet objet coûte :\n  - " << ptHonneur << " points d'honneur\n  - " << ptArene << " points d'arène \n|cffFF0000Requiert une côte personnel en arène de " << cote << ".";
			return ss_name.str();
		}
		else
			return "\nCet objet ne coûte rien et ne requiert aucune côte d'arène.";
	}
};

void ListeItems::LoadListeItems()
{
	ItemTemplateContainer const* its = sObjectMgr->GetItemTemplateStore();

	bool isGood = false;

	for (ItemTemplateContainer::const_iterator itr = its->begin(); itr != its->end(); itr++)
	{
		switch (itr->second.ItemLevel)
		{
		case 0:
		case 100:
		case 200:
		case 300:
		case 400:
		case 500:
		case 600:
		case 700:
		case 800:
		case 900:
		case 1000:
			for (ItemTemplateContainer::const_iterator itr2 = its->begin(); itr2 != its->end(); itr2++)
			{
				if (itr2->second.Class == itr->second.Class &&
					itr2->second.SubClass == itr->second.SubClass &&
					(itr2->second.InventoryType == itr->second.InventoryType || (itr2->second.InventoryType == INVTYPE_CHEST && itr->second.InventoryType == INVTYPE_ROBE) || (itr->second.InventoryType == INVTYPE_CHEST && itr2->second.InventoryType == INVTYPE_ROBE)) &&
					itr2->second.ItemLevel == (itr->second.ItemLevel + 100))
				{
					_listeItems.insert(std::pair<uint32, bool>(itr->second.ItemId, true));
					isGood = true;
					break;
				}
			}
			if (isGood == false)
				_listeItems.insert(std::pair<uint32, bool>(itr->second.ItemId, false));
			isGood = false;
		default:
			break;
		}
	}
}

void AddSC_NPC_Upgrade()
{
	new NPC_Upgrade();
}