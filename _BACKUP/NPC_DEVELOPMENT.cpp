/*
NPC_DEVELOPMENT
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96666;
SET @CREATURTEMPLATE_NAME = "DEVELOPMENT NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24935;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_DEVELOPMENT', 0);
*/

// ******************************************************************************
// class
// ******************************************************************************
class NPC_DEVELOPMENT : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_DEVELOPMENT() : CreatureScript("NPC_DEVELOPMENT") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	// ******************************************************************************
	// parameter
	// ******************************************************************************
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "Text Input", GOSSIP_SENDER_MAIN, 105,"Bereit, das Wort einzugeben ?", 0, true);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "Sicherheitsabfrage", GOSSIP_SENDER_MAIN, 110, "Bist Du dir sicher ?", 0, false);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "auf Wiedersehen", GOSSIP_SENDER_MAIN, 999);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}
	// ******************************************************************************
	// OnGossipSelect
	// ******************************************************************************
	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		if (sender == GOSSIP_SENDER_MAIN)
		{
			// --- verlassen
			if (action == 999)
			{
				creature->Say("Auf Wiedersehen.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			if (action == 110)
			{
				player->GetSession()->SendNotification("Bestaetigt mit 'ja'");
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			return false;
		}//if sender
	};//OnGossipSelect
	bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) override
	{
		if (sender == GOSSIP_SENDER_MAIN)
		{
			// ******************************************************************************
			// nach Texteingabe
			// ******************************************************************************
			if (action == 105)
			{
				//ChatHandler(player->GetSession()).PSendSysMessage("OnGossipSelectCode --- Eingabe: %s", code);
				player->GetSession()->SendNotification("OnGossipSelectCode --- Eingabe: %s", code);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			return false;
		}//if sender
	};//OnGossipSelectCode
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_DEVELOPMENT()
{
	new NPC_DEVELOPMENT();
};
