/*
ITEM_SummonHelperNPC
testet: 3.3.5a
stand: 01.11.2016

SET @ITEMTEMPLATE_ENTRY = 60000;
SET @ITEMTEMPLATE_NAME = "Helper-NPC herbeirufen";
SET @ITEMTEMPLATE_DESCR = "Rechtsklick um einen Helper-NPC herbeizurufen";
DELETE a FROM characters.character_inventory AS a JOIN characters.item_instance AS b ON (a.item = b.guid) WHERE b.itemEntry = @ITEMTEMPLATE_ENTRY;
DELETE FROM world.item_template WHERE entry = @ITEMTEMPLATE_ENTRY;
INSERT INTO world.item_template VALUES
(@ITEMTEMPLATE_ENTRY, 15, 0, -1, @ITEMTEMPLATE_NAME, 20629, 7, 8388608, 0, 1, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 14867, 0, 0, 0, 60000, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0,
0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 1, @ITEMTEMPLATE_DESCR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0,
'ITEM_SummonHelperNPC', 0, 0, 0, 0, 0, 12340);
*/

// ******************************************************************************
// class
// ******************************************************************************
class ITEM_SummonHelperNPC : public ItemScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public:	ITEM_SummonHelperNPC() : ItemScript("ITEM_SummonHelperNPC") { }
	// ******************************************************************************
	// parameter
	// ******************************************************************************
	uint32 SUMMON_CREATUREID = 96000;// muss vorhanden sein !
	uint32 SUMMON_CREATUREFOLLOW = 1; //0=disabled / 1=emabled
	// ******************************************************************************
	// OnUse
	// ******************************************************************************
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
	{
		if (player->IsInCombat())
		{
			player->GetSession()->SendNotification("Du befindest Dich in einem Kampf. Da kann ich Dir nicht helfen.");
			return false;
		}
		if (player->InArena())
		{
			player->GetSession()->SendNotification("Du kannst den Gegenstand nicht in der Arena benutzen.");
			return false;
		}
		if (player->InBattleground())
		{
			player->GetSession()->SendNotification("Du kannst den Gegenstand nicht auf einem Schlachtfeld benutzen.");
			return false;
		}
		if (player->FindNearestCreature(SUMMON_CREATUREID, 50.0f))
		{
			player->GetSession()->SendNotification("Es befindet sich bereit ein Helper-NPC in der Naehe. Es kann nicht noch einer herbeigerufen werden.");
			return false;
		}
		Creature* creature = player->SummonCreature(SUMMON_CREATUREID, player->GetPositionX(), player->GetPositionY() - 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60 * IN_MILLISECONDS);
		creature->Say("Hallo. Ich bin der Helper-NPC und stehe Dir nun fuer 1 Minute zur Verfuegung.", LANG_UNIVERSAL, NULL);
		if (SUMMON_CREATUREFOLLOW == 1)
			creature->GetMotionMaster()->MoveFollow(player, 0.2f, PET_FOLLOW_ANGLE, MOTION_SLOT_ACTIVE);
		return true;
	};//OnUse
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_ITEM_SummonHelperNPC() // Add to custom_script_loader.cpp normally
{
	new ITEM_SummonHelperNPC;
}