/*
<--------------------------------------------------------------------------->
 - Developer(s): Foxthecrash (Dwark)
 - Complete: 90% (I want to add more things in future and optimize the code)
 - ScriptName: 'Change Faction to Horde'
 - Comment: Tested
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"

// Define la zona donde el jugador sera teletransportado si -> el Item expira o esta en una zona restringida
// Define your zone to player will be teleported if -> Item expire or is in restricted zone
// value: MapId, X, Y, Z, Orientation
#define zone 1, -8531.564f, 2010.638f, 100.7205f, 0.380013f

class Item_Alliance : public ItemScript
{

public:
	Item_Alliance() : ItemScript("Item_Alliance") {}

	bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
	{ // 61849 aura de 1 hora - 24705 aura de 2 horas - 37128 aura de 15 minutos - 
		// 26898 aura de 1 hora (dura muerto) - 

		uint32 Ali = player->getRace() == RACE_DRAENEI || RACE_DWARF || RACE_GNOME || RACE_HUMAN || RACE_NIGHTELF;
		if (player->IsInCombat() || player->IsMounted() || player->isMoving() || player->IsFlying()) // Combate, Montura, Moviendose, Volando
		{
			/*player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF No puedes Cambiar de faccion en combate, Montura, Moviendote, Volando!");*/
			player->GetSession()->SendNotification("|cFFFFFC00[System]|cFF00FFFF You can't change faction when you'r moving, on mount or flying!");
			return false;
		}
		else if (player->GetGroupInvite() || player->InArena() || player->InBattleground() || player->InBattlegroundQueue() || player->inRandomLfgDungeon() || player->isUsingLfg()) //Arena, BG y colas
		{
			/*player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF No puedes Cambiar de faccion en Arenas, BG o estando en cola para Aleatorias (BG e Instancias)!");*/
			player->GetSession()->SendNotification("|cFFFFFC00[System]|cFF00FFFF You can't change faction in Arenas, BG or LFG!");
			return false;
		}
		// Restriction for Horde in Stormwind, Elwyn Forest
		// Restriccion para la horda en Ventormenta, Bosque de Elwyn
		else if (player->GetAreaId() == 14 && player->GetZoneId() == 14 || player->GetAreaId() == 12 && player->GetZoneId() == 12 && player->HasAura(14268))
		{
			// If you want to teleport player when use the item in restricted zone just uncomment
			// Si quieres que teletransporte al jugador cuando usa el item en las zonas restringidas solo descomenta
			/*player->TeleportTo(zone);*/
			/*player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF No puedes Cambiar de faccion en esta zona!");*/
			player->GetSession()->SendNotification("|cFFFFFC00[System]|cFF00FFFF You can't change faction in this area!");
			return false;
		}
		// Restriction for Alliance in Orgrimmar, Durotar
		// Restriccion para la Alianza en Orgrimmar, Durotar
		else if (player->GetAreaId() == 1519 && player->GetZoneId() == 1519 || player->GetAreaId() == 1637 && player->GetZoneId() == 1637 && player->HasAura(14267))
		{
			// If you want to teleport player when use the item in restricted zone just uncomment
			// Si quieres que teletransporte al jugador cuando usa el item en las zonas restringidas solo descomenta
			/*player->TeleportTo(zone);*/
			/*player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF No puedes Cambiar de faccion en esta zona!");*/
			player->GetSession()->SendNotification("|cFFFFFC00[System]|cFF00FFFF You can't change faction in this area!");
		}
		else if (player->HasAura(5384) || player->HasAura(1784) || player->HasAura(1856) || player->HasAura(26889) || player->HasAura(2645) || player->HasAura(66) || player->HasAura(45438) || player->HasAura(5215) || player->HasAura(3448) || player->HasAura(11464) || player->HasAura(11392) || player->HasStealthAura()) // spells
		{
			// Restricted spells to prevent abuse
			// Hechizos restringidos para evitar abuso
			/*player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF No puedes Cambiar de faccion con hechizos como Sigilo, Bloque de Hielo, Inivisibilidad, etc.!");*/
			player->GetSession()->SendNotification("|cFFFFFC00[System]|cFF00FFFF You can't change faction if you'r using stealth, ice block, invisibility, etc.!");
			return false;
		}
		/*else if (player->duel)
		{
		player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF No puedes Cambiar de faccion estando en un duelo!");
		return true;
		}*/
		else
		{
			if (player->HasAura(14268)) // Prevent the player has double aura (Alianza and Horde) just to be safe
			{
				player->RemoveAura(14268);
				player->setFactionForRace(RACE_HUMAN || RACE_DRAENEI);
			}
			else if (player->HasAura(14267)) // If player uses the item again, remove the aura and restore faction to the alliance
			{
				player->RemoveAura(14267);
				player->setFactionForRace(RACE_HUMAN || RACE_DRAENEI);
			}
			else
			{
				player->AddAura(14267, player); // Add Aura and if player has the aura aply the new faction
				if (player->HasAura(14267))
				{
					player->setFactionForRace(2); //horda 1 hora
					player->GetSession()->SendNotification("|cFFFFFC00[System]|cFF00FFFF Now you'r Horde!");
					/*player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF Ahora eres Horda!");*/
					ChatHandler(player->GetSession()).PSendSysMessage("|cFFFFFC00[System]|cFF00FFFF If you logout your factión will restore, then use the item again to get the Horde faction!");
					/*ChatHandler(player->GetSession()).PSendSysMessage("|cFFFFFC00[Sistema]|cFF00FFFF Si desconectas tu volveras a tu facción original, usa denuevo el item para ser Horda!");*/
				}
			}
			return true;
		}

		return true;
	}

	bool OnExpire(Player* player, ItemTemplate const* proto)
	{
		uint8 Ali = player->getRace() == RACE_DRAENEI || RACE_DWARF || RACE_GNOME || RACE_HUMAN || RACE_NIGHTELF;
			player->RemoveAura(14267);
			if (player->getRace() == Ali)
			{
				player->setFactionForRace(RACE_HUMAN || RACE_DRAENEI);
			}
			player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF Your faction back to the original!");
			/*player->GetSession()->SendNotification("|cFFFFFC00[Sistema]|cFF00FFFF Has vuelto a tu facción original!");*/
			player->TeleportTo(zone);

		return true;
	}
};

void AddSC_Item_Alliance()
{
	new Item_Alliance();
}


----------------------------
insert into `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `WDBVerified`) values('842','0','0','-1','Faction to Horde','7015','7','201326624','131072','1','0','0','0','-1','-1','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','45523','0','0','0','0','0','0','0','0','0','0','-1','0','-1','0','0','0','0','-1','0','-1','0','0','0','0','-1','0','-1','0','0','0','0','-1','0','-1','1','Change your Faction to horde','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','-1','0','3600','0','0','Item_Alliance','0','0','0','0','0','1');
insert into `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `WDBVerified`) values('823','0','0','-1','Faction to Alliance','7014','7','201326624','131072','1','0','0','0','-1','-1','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','49375','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','Change your Faction yo Alliance','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','-1','0','3600','0','0','Item_Horde','0','0','0','0','0','1');