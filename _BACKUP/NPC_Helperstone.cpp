/*
NPC_Helperstone
testet: 3.3.5a
stand: 01.11.2016

SET @CREATURTEMPLATE_ENTRY = 96002;
SET @CREATURTEMPLATE_NAME = "Helperstone NPC";
SET @CREATURTEMPLATE_SUBNAME = "Darkstanley Inc.";
SET @CREATURTEMPLATE_MODELID = 24978;
DELETE FROM world.creature WHERE id = @CREATURTEMPLATE_ENTRY;
DELETE FROM world.creature_template WHERE entry = @CREATURTEMPLATE_ENTRY;
INSERT INTO world.creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CREATURTEMPLATE_ENTRY, 0, 0, 0, 0, 0, @CREATURTEMPLATE_MODELID, 0, 0, 0, @CREATURTEMPLATE_NAME, @CREATURTEMPLATE_SUBNAME, 'Directions', 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'NPC_Helperstone', 0);
*/

// ******************************************************************************
// class
// ******************************************************************************
class NPC_Helperstone : public CreatureScript
{
	// ******************************************************************************
	// public
	// ******************************************************************************
	public: NPC_Helperstone() : CreatureScript("NPC_Helperstone") { }
	// ******************************************************************************
	// init
	// ******************************************************************************
	uint32 NPC_Helperstone_ADDITEMID = 60000;// muss vorhanden sein !
	// ******************************************************************************
	// OnGossipHello
	// ******************************************************************************
	bool OnGossipHello(Player* player, Creature* creature) override
	{
		ClearGossipMenuFor(player);
		AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff404040|TInterface\\icons\\Achievement_Level_80:30:30:-18|t Gib mit einen HelperNPC-Stein|r", GOSSIP_SENDER_MAIN, 105);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|cff000000|TInterface\\buttons\\UI-GroupLoot-Pass-Down:30:30:-18|t auf Wiedersehen|r", GOSSIP_SENDER_MAIN, 999);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}//OnGossipHello
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
			// --- im Kampf
			if (player->IsInCombat())
			{
				creature->Say("Du befindest Dich in einem Kampf. Da kann ich nix fuer Dich tun !", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				return true;
			}
			if (action == 105)
			{
				if (player->HasItemCount(NPC_Helperstone_ADDITEMID, 1, false))
				{
					creature->Say("Du hast diesen Stein bereits bei Dir !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				if (player->HasItemCount(NPC_Helperstone_ADDITEMID, 1, true))
				{
					creature->Say("Du hast diesen Stein bereits in Deiner Bank liegen. Hol Dir den dort erstmal !", LANG_UNIVERSAL, NULL);
					ClearGossipMenuFor(player);
					CloseGossipMenuFor(player);
					OnGossipHello(player, creature);
					return true;
				}
				creature->CastSpell(player, 38588, false); // Nur als Effekt
				player->AddItem(NPC_Helperstone_ADDITEMID, 1);
				creature->Say("Ich habe Dir einen HelperNPC-Stein gegeben. Pass gut auf den auf.", LANG_UNIVERSAL, NULL);
				ClearGossipMenuFor(player);
				CloseGossipMenuFor(player);
				OnGossipHello(player, creature);
				return true;
			}
			return false;
		}//if sender
		return false;
	}//OnGossipSelect
};
// ******************************************************************************
// AddSC_...
// ******************************************************************************
void AddSC_NPC_Helperstone()
{
	new NPC_Helperstone();
};
