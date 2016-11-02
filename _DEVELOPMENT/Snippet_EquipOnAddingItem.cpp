// ELUNA SCRIPT !

Item* EquipItem(Player* player, EquipmentSlots slot, uint32 entry)
{
    Item* item = Item::CreateItem(entry, 1, player);
    if (!item)
        return NULL;

    uint16 dest = 0;
    InventoryResult result = player->CanEquipItem(slot, dest, item, false);
    if (result != EQUIP_ERR_OK)
    {
        delete item;
        return NULL;
    }
    player->ItemAddedQuestCheck(entry, 1);
    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_RECEIVE_EPIC_ITEM, entry, 1);
    return player->EquipItem(dest, item, true);
}