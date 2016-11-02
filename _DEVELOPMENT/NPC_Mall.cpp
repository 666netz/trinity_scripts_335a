/*
Set @Entry: = 900004;
Set @Display: = 30736;  --Currently set to a totem display
Set @Name: = Server Name;
Set @Subname: = Sub Name;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES(@Entry, 0, 0, 0, 0, 0, @Display, 0, 0, 0, '@Name', '@Subname', 'Directions', 0, 80, 80, 0, 35, 3, 1, 1, 1, 2, 0, 1000, 1000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 0, 0, 0, 1000, 1000, 1000, 1000, 1000, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullAI', 1, 3, 1, 2.5, 0, 2.5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '@Mall_Guide', -1);
*/
// Mall Guide Created 10/07/2015
// By DPCoder   @[member=LordCraftDev].net
// Compiled on Trinitycore Revision 58
//  Not Tested In Game

#include "ScriptPCH.h"

class Mall_Guide : public CreatureScript
{
public:
	Mall_Guide() : CreatureScript("Mall_Guide") {}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		{
			player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Achievement_WorldEvent_Lunar:24|t|r Teleporter", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Achievement_Arena_3v3_6:24|t|r Gearing / Weapons", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Jewelcrafting_DragonsEye05:24|t|r Gems Vendors", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Enchant_ShardNexusLarge1:24|t|r Enhancement Vendors", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(3, "|TInterface\\icons\\INV_Misc_Book_06:24|t|r Class / Riding / Profession Trainers", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Inscription_MajorGlyph00:24|t|r Glyph Vendors", GOSSIP_SENDER_MAIN, 31);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Alchemy_EndlessFlask_06:24|t|r Food / Drink / Regeants", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(8, "|TInterface\\icons\\Achievement_PVP_A_01:24|t|r Guild Master / Tabard Designer / Bank", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_MISC_TABARDSUMMER01:24|t|r Mail Box / Barber Chairs", GOSSIP_SENDER_MAIN, 9);
			player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Achievement_BG_KillXEnemies_GeneralsRoom:24|t|r Battlemasters / Arena Masters", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\Achievement_Reputation_KirinTor:24|t|r Transmogrifier", GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_Quests_Completed_03:24|t|r Custom Quest Npcs", GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Achievement_PVP_A_01:24|t|r Training Dummies", GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Mounts / Companions", GOSSIP_SENDER_MAIN, 30);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		}
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{

		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{

			//    ---------->>>>> PLEASE READ THE FOLLOWING NOTES BEFORE CHANGING ANY OF THE TELEPORT LOCATIONS <<<<<------------

			//  NOTE - IF YOU WISH TO CHANGE THE LOCATIONS THEN MAKE SURE YOU LEAVE THE LETTER "f" AT THE END OF THE XYZ COORDINATES AND THE ORIENTATION

			//  EXAMPLE OF SETUP :- player->TeleportTo(MAP, XCoOrdinatef, YCoOrdinatef, ZCoOrdinatef, Orientationf);

			//  EXAMPLE OF WAY SHOULD LOOK :- player->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);  <--- THIS IS THE COORDINATES TO TELEPORT TO DALARAN

			// IF THE GPS HAS A - IN IT REMEMBER TO PUT THIS IN ALSO (EXAMPLE (player->TeleportTo(1, -1487.28f, -829.123f, 823.997f, 5.11f);

			//  YOU CAN GET THE COORDINATES FROM TYPING .GPS IN GAME, I SUGGEST STANDING IN FRONT ONF THE NPC TO DO THE .GPS (MAKE SURE YOU HAVE NOTHING TARGETTED)

		case 2:            // Teleporter
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);
			player->PlayerTalkClass->ClearMenus();
			break;

		case 3:          // Gearing & Weapons
		{
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Chest_Leather_03:24|t|r Starter Gear", GOSSIP_SENDER_MAIN, 14);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Chest_Leather_24:24|t|r End Gear", GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Cape_18:24|t|r Offset Vendors", GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Item_icecrownringB:24|t|r Jewellery Vendors", GOSSIP_SENDER_MAIN, 17);
			player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Achievement_Arena_2v2_3:24|t|r Weapons", GOSSIP_SENDER_MAIN, 18);
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 4:        // Gem Vendors
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 5:      // Enhancement Vendors
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 6:     // Class   Riding   Profession
		{
			player->ADD_GOSSIP_ITEM(3, "|TInterface\\icons\\INV_Misc_Book_10:24|t|r Class Trainers", GOSSIP_SENDER_MAIN, 19);
			player->ADD_GOSSIP_ITEM(3, "|TInterface\\icons\\INV_Misc_Book_08:24|t|r Riding  Trainer", GOSSIP_SENDER_MAIN, 20);
			player->ADD_GOSSIP_ITEM(3, "|TInterface\\icons\\INV_Misc_Book_03:24|t|r Profession Trainer", GOSSIP_SENDER_MAIN, 21);
		}
		break;

		case 7:     // Food   Drink  Regeants
		{
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Drink_25_HoneyTea:24|t|r Food / Drink Vendor", GOSSIP_SENDER_MAIN, 22);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_TradeskillItem_0:24|t|r Regeants Vendor", GOSSIP_SENDER_MAIN, 23);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Misc_Note_01:24|t|r Scrolls Vendor", GOSSIP_SENDER_MAIN, 24);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Potion_04:24|t|r Potions Vendor", GOSSIP_SENDER_MAIN, 25);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Alchemy_EndlessFlask_05:24|t|r Flasks Vendor", GOSSIP_SENDER_MAIN, 26);
			player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Alchemy_Elixir_01:24|t|r Elixers Vendor", GOSSIP_SENDER_MAIN, 27);
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 8:       // Guild Master  Tabard Desgner   Bank   
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 9:       //  Mail Box        Barber Chairs      Mounts      Companions
		{
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Letter_04:24|t|r Mail Box", GOSSIP_SENDER_MAIN, 28);
			player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Ability_Rogue_Disguise:24|t|r Barber Chairs", GOSSIP_SENDER_MAIN, 29);
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 10:  // Battlemaster     Arenamaster 
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 11:   //    Transmogrifier
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 12:  //  Custom Quests
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 13:  //  Training Dummies
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 14:  //  Starter Gear
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 15: //  End Gear
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 16: //  Offset Vendors
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 17:  // Jewelery Vendors
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 18:  // Weapon Vendors
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 19:   // Class Trainers
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 20:  //  Riding Trainer
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 21:  // Profession Trainer
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 22:  // Food & Drink
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 23:  // Regeants
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 24:  // Scrolls Vendor
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 25:  // Potions
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 26:  // Flasks
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 27:  // Elixers
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 28:  // Mail Box
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 29:  // Barber Chairs
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 30:  //  Mounts & Companions
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;

		case 31:  //  Glyph Vendors
		{
			player->TeleportTo(0, 0000.00f, 0000.00f, 000.00f, 0.00000f);  //  <<-----EDIT ONLY THE PIECE IN THE BRACKETS, MAKE SURE TO LEAVE THE "f" ON THE END OF THE XYZ AND ORIENTATION  (SEE EXAMPLE ABOVE)
			player->PlayerTalkClass->ClearMenus();
		}
		break;
		}
		return true;
	}
};

void AddSC_Mall_Guide()
{
	new Mall_Guide();
}