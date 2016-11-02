/*
//Trinitycore//
Author : Philippe
Special Thanks for : Lea (Ac-Web) / Snyth EmuDev to adding name to spells
Welcome NPC 2.0v
Version : 3.3.5
(Ac-Web)
Original V1 Thread: http://www.ac-web.org/forums/showthread.php?152774-trinitycore-c-Welcome-NPC&highlight=
(Emu-Dev)
Original V2 Thread: http://emudevs.com/showthread.php/1300-Welcome-NPC-V2-0?p=8193#post8193

//Spell List % Complete//
Warrior : 100 %
Mage : 100 %
Druid : 100 %
Paladin : 100 %
Warlock : 100 %
Hunter : 100 %
Shaman : 100 %
Rogue : 100 %
Priest : 100 %
DK : 100 %
Mount spells : 100 %

//Talent List Spell % Complete//
Warrior : 100 %
Mage : 100 %
Druid : 100 %
Paladin : 100 %
Warlock : 100 %
Hunter : 100 %
Shaman : 100 %
Rogue : 100 %
Priest : 100 %
DK : 100 %

//====SQL NPC====//
Set
@NPC_ENTRY = YOUR_ID,
@NPC_MORPH = YOUR_ID,
@NPC_SCRIPTNAME = "npc_welcome",
@NPC_NAME = "Welcome NPC 2.0",
@NPC_SUBNAME = "<Server Name>";

INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(@NPC_ENTRY, 0, 0, 0, 0, 0, @NPC_MORPH, 0, 0, 0, @NPC_NAME, @NPC_SUBNAME, '', 0, 80, 80, 0, 35, 35, 129, 1, 1.14286, 1, 3, 13, 17, 0, 42, 1, 1500, 0, 1, 515, 2048, 8, 0, 0, 0, 0, 0, 9, 13, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2147483647, 2, @NPC_SCRIPTNAME, 12340);
*/

#include "ScriptPCH.h"

enum eIcons
{
	CHAT_ICON = 0,
	VENDOR_ICON = 1,
	FLIGHT_ICON = 2,
	TRAINER_ICON = 3,
	GEAR_ICON = 4,
	GEAR_ICON_2 = 5,
	BANK_ICON = 6,
	CHAT_DOTS_ICON = 7,
	TABARD_ICON = 8,
	SWORDS_ICON = 9,
	GOLD_DOT_ICON = 10
};

enum Spell_Krieger
{
	Spell_Krieger_Overpower = 7384,
	Spell_Krieger_Battle_Shout = 47436,
	Spell_Krieger_Heroic_Strike = 47450,
	Spell_Krieger_Charge = 11578,
	Spell_Krieger_Rend = 47465,
	Spell_Krieger_Thunder_Clap = 47502,
	Spell_Krieger_Victory_Rush = 34428,
	Spell_Krieger_Hamstring = 1715,
	Spell_Krieger_Bloodrage = 2687,
	Spell_Krieger_Defensive_Stance = 71,
	Spell_Krieger_Sunder_Armor = 7386,
	Spell_Krieger_Taunt = 355,
	Spell_Krieger_Shield_Bash = 72,
	Spell_Krieger_Demoralizing_Shout = 47437,
	Spell_Krieger_Revenge = 57823,
	Spell_Krieger_Mocking_Blow = 694,
	Spell_Krieger_Shield_Block = 2565,
	Spell_Krieger_Disarm = 676,
	Spell_Krieger_Cleave = 47520,
	Spell_Krieger_Retaliation = 20230,
	Spell_Krieger_Stance_Mastery = 12678,
	Spell_Krieger_Execute = 47471,
	Spell_Krieger_Challenging_Shout = 1161,
	Spell_Krieger_Shield_Wall = 871,
	Spell_Krieger_Berserker_Stance = 2458,
	Spell_Krieger_Intercept = 20252,
	Spell_Krieger_Slam = 47475,
	Spell_Krieger_Berserker_Rage = 18499,
	Spell_Krieger_Whirlwind = 1680,
	Spell_Krieger_Pummel = 6552,
	Spell_Krieger_Sheild_Slam = 47488,
	Spell_Krieger_Recklessness = 1719,
	Spell_Krieger_Spell_Reflection = 23920,
	Spell_Krieger_Commanding_Shout = 47440,
	Spell_Krieger_Intervene = 3411,
	Spell_Krieger_Shattering_Throw = 64382,
	Spell_Krieger_Enraged_Regeneration = 55694,
	Spell_Krieger_Heroic_Throw = 57755,
	Spell_Krieger_Dual_Wield = 42459,
	Spell_Krieger_Intimidating_Shout = 5246,
	Spell_Krieger_Parry = 3127,
	//Talent - Krieger 
	Spell_Krieger_Devastate = 47498, // Talent - Proto
	Spell_Krieger_Mortal_Strike = 47486 // Talent - Arms
};

enum Spell_Paladin
{
	Spell_Paladin_Parry = 3127,
	Spell_Paladin_Concentration_Aura = 19746,
	Spell_Paladin_Divine_Intervention = 19752,
	Spell_Paladin_Plate_Mail_skill = 750,
	Spell_Paladin_Devotion_Aura = 48942,
	Spell_Paladin_Holy_Light = 48782,
	Spell_Paladin_Blessing_of_Might = 48932,
	Spell_Paladin_Judgement_of_Light = 20271,
	Spell_Paladin_Divine_Protection = 498,
	Spell_Paladin_Hammer_of_Justice = 10308,
	Spell_Paladin_Purify = 1152,
	Spell_Paladin_Hand_of_Protection = 10278,
	Spell_Paladin_Lay_on_Hands = 48788,
	Spell_Paladin_Judgement_of_Wisdom = 53408,
	Spell_Paladin_Redemption = 48950,
	Spell_Paladin_Blessing_of_Wisdom = 48936,
	Spell_Paladin_Righteous_Defense = 31789,
	Spell_Paladin_Hand_of_Reckoning = 62124,
	Spell_Paladin_Retribution_Aura = 54043,
	Spell_Paladin_Righteous_Fury = 25780,
	Spell_Paladin_Hand_of_Freedom = 1044,
	Spell_Paladin_Blessing_of_Kings = 20217,
	Spell_Paladin_Consecration = 48819,
	Spell_Paladin_Exorcism = 48801,
	Spell_Paladin_Flash_of_Light = 48785,
	Spell_Paladin_Sense_Undead = 5502,
	Spell_Paladin_Seal_of_Justice = 20164,
	Spell_Paladin_Turn_Evil = 10326,
	Spell_Paladin_Hand_of_Salvation = 1038,
	Spell_Paladin_Judgement_of_Justice = 53407,
	Spell_Paladin_Shadow_Resistance_Aura = 48943,
	Spell_Paladin_Seal_of_Light = 20165,
	Spell_Paladin_Frost_Resistance_Aura = 48945,
	Spell_Paladin_Divine_Shield = 642,
	Spell_Paladin_Fire_Resistance_Aura = 48947,
	Spell_Paladin_Seal_of_Wisdom = 20166,
	Spell_Paladin_Cleanse = 4987,
	Spell_Paladin_Hammer_of_Wrath = 48806,
	Spell_Paladin_Hand_of_Sacrifice = 6940,
	Spell_Paladin_Holy_Wrath = 48817,
	Spell_Paladin_Greater_Blessing_of_Might = 48934,
	Spell_Paladin_Greater_Blessing_of_Wisdom = 48938,
	Spell_Paladin_Greater_Blessing_of_Kings = 25898,
	Spell_Paladin_Crusader_Aura = 32223,
	Spell_Paladin_Avenging_Wrath = 31884,
	Spell_Paladin_Divine_Plea = 54428,
	Spell_Paladin_Shield_of_Righteousness = 61411,
	Spell_Paladin_Sacred_Shield = 53601,
	Spell_Paladin_Seal_of_Vengeance = 31801, // Alliance
	Spell_Paladin_Warhorse = 13819, // Alliance
	Spell_Paladin_Charger = 23214, // Alliance
	Spell_Paladin_Seal_of_Corruption = 53736, // Horde
	Spell_Paladin_Thalassian_Warhorse = 34769, // Horde
	Spell_Paladin_Thalassian_Charger = 34767, // Horde
	//Talent - Paladin
	Spell_Paladin_Holy_Shield = 48952,  // Talent - Protection
	Spell_Paladin_Avengers_Shield = 48827,  // Talent - Protection
	Spell_Paladin_Greater_Blessing_of_Sanctuary = 25899, // Talents - Protection
	Spell_Paladin_Holy_Shock = 48825, // Talents - Holy
};

enum Spell_Magier
{
	Spell_Magier_Arcane_Explosion = 42921,
	Spell_Magier_Frostbolt = 42842,
	Spell_Magier_Arcane_Intellect = 42995,
	Spell_Magier_Fireball = 42833,
	Spell_Magier_Conjure_Water = 27090,
	Spell_Magier_Conjure_Food = 33717,
	Spell_Magier_Fire_Blast = 42873,
	Spell_Magier_Arcane_Missiles = 42846,
	Spell_Magier_Polymorph = 12826,
	Spell_Magier_Polymorph_Turtle = 28271,
	Spell_Magier_Polymorph_Turkey = 61780,
	Spell_Magier_Polymorph_Rabbit = 61721,
	Spell_Magier_Polymorph_Pig = 28272,
	Spell_Magier_Frost_Nova = 42917,
	Spell_Magier_Dampen_Magic = 43015,
	Spell_Magier_Slow_Fall = 130,
	Spell_Magier_Flamestrike = 42926,
	Spell_Magier_Amplify_Magic = 43017,
	Spell_Magier_Remove_Curse = 475,
	Spell_Magier_Blink = 1953,
	Spell_Magier_Blizzard = 42940,
	Spell_Magier_Evocation = 12051,
	Spell_Magier_Fire_Ward = 43010,
	Spell_Magier_Mana_Shield = 43020,
	Spell_Magier_Frost_Ward = 43012,
	Spell_Magier_Scorch = 42859,
	Spell_Magier_Counterspell = 2139,
	Spell_Magier_Cone_of_Cold = 42931,
	Spell_Magier_Conjure_Mana_Gem = 42985,
	Spell_Magier_Ice_Armor = 43008,
	Spell_Magier_Ice_Block = 45438,
	Spell_Magier_Mage_Armor = 43024,
	Spell_Magier_Arcane_Brilliance = 43002,
	Spell_Magier_Molten_Armor = 43046,
	Spell_Magier_Arcane_Blast = 42897,
	Spell_Magier_Ice_Lance = 42914,
	Spell_Magier_Invisibility = 66,
	Spell_Magier_Ritual_of_Refreshment = 58659,
	Spell_Magier_Spellsteal = 30449,
	Spell_Magier_Conjure_Refreshment = 42956,
	Spell_Magier_Frostfire_Bolt = 47610,
	Spell_Magier_Dalaran_Brilliance = 61316,
	Spell_Magier_Dalaran_Intellect = 61024,
	Spell_Magier_Mirror_Image = 55342,
	Spell_Magier_Portal_Dalaran = 53142,
	Spell_Magier_Frost_Armor = 7301,
	Spell_Magier_Teleport_Exodar = 32271, // Alliance
	Spell_Magier_Teleport_Theramore = 49359, // Alliance
	Spell_Magier_Teleport_Darnassus = 3565, // Alliance
	Spell_Magier_Teleport_Shattrath = 33690, // Alliance
	Spell_Magier_Teleport_Ironforge = 3562, // Alliance
	Spell_Magier_Teleport_Stromwind = 3561, // Alliance
	Spell_Magier_Portal_Darnassus = 11419, // Alliance
	Spell_Magier_Portal_Exodar = 32266, // Alliance
	Spell_Magier_Portal_Ironforge = 11416, // Alliance
	Spell_Magier_Portal_Shattrath = 33691, // Alliance
	Spell_Magier_Portal_Theramore = 49360, // Alliance
	Spell_Magier_Teleport_Orgrimmar = 3567, // Horde
	Spell_Magier_Teleport_Shattrath_H = 35715, // Horde
	Spell_Magier_Teleport_Thunder_Bluff = 3566, // Horde
	Spell_Magier_Teleport_Stonard = 49358, // Horde
	Spell_Magier_Teleport_Silvermoon = 32272, // Horde
	Spell_Magier_Teleport_Undercity = 3563, // Horde
	Spell_Magier_Portal_Orgrimmar = 11417, // Horde
	Spell_Magier_Portal_Shattrath_H = 35717, // Horde
	Spell_Magier_Portal_Silvermoon = 32267, // Horde
	Spell_Magier_Portal_Stonard = 49361, // Horde
	Spell_Magier_Portal_Thunder_Bluff = 11420, // Horde
	Spell_Magier_Portal_Undercity = 11418, // Horde	
	//Talent - Magier
	Spell_Magier_Pyroblast = 42891, // Talent - Fire
	Spell_Magier_Ice_Barrier = 43039, // Talent - Frost
	Spell_Magier_Living_Bomb = 55360, // Talent - Fire
	Spell_Magier_Dragons_Breath = 42950, // Talent - Fire
	Spell_Magier_Blast_Wave = 42945, // Talent - Fire
	Spell_Magier_Arcane_Barrage = 44781 // Talent - Arcane
};

enum Spell_Todesritter
{
	Spell_Todesritter_Parry = 3127,
	Spell_Todesritter_Pestilence = 50842,
	Spell_Todesritter_Blood_Boil = 49941,
	Spell_Todesritter_Blood_Strike = 49930,
	Spell_Todesritter_Strangulate = 47476,
	Spell_Todesritter_Blood_Tap = 45529,
	Spell_Todesritter_Path_of_Frost = 3714,
	Spell_Todesritter_Dark_Command = 56222,
	Spell_Todesritter_Death_Pact = 48743,
	Spell_Todesritter_Frost_Presence = 48263,
	Spell_Todesritter_Icy_Touch = 49909,
	Spell_Todesritter_Mind_Freeze = 47528,
	Spell_Todesritter_Chains_of_Ice = 45524,
	Spell_Todesritter_Icebound_Fortitude = 48792,
	Spell_Todesritter_Horn_of_Winter = 57623,
	Spell_Todesritter_Rune_Strike = 56815,
	Spell_Todesritter_Empower_Rune_Weapon = 47568,
	Spell_Todesritter_Death_Coil = 49895,
	Spell_Todesritter_Death_Gate = 50977,
	Spell_Todesritter_Plague_Strike = 49921,
	Spell_Todesritter_Death_Grip = 49576,
	Spell_Todesritter_Raise_Dead = 46584,
	Spell_Todesritter_Death_and_Decay = 49938,
	Spell_Todesritter_Anti_Magic_Shell = 48707,
	Spell_Todesritter_Unholy_Presence = 48265,
	Spell_Todesritter_Raise_Ally = 61999,
	Spell_Todesritter_Army_of_the_Dead = 42650,
	Spell_Todesritter_Runeforging_skill = 53428,
	Spell_Todesritter_Uknowas = 53331,
	Spell_Todesritter_Uknowah = 54447,
	Spell_Todesritter_Uknowai = 53342,
	Spell_Todesritter_Uknowaz = 54446,
	Spell_Todesritter_Uknowan = 53323,
	Spell_Todesritter_Uknowab = 53344,
	Spell_Todesritter_Uknowav = 70164,
	Spell_Todesritter_Uknowaj = 62158,
	Spell_Todesritter_Uknowaq = 33391,
	Spell_Todesritter_Acherus_Deathcharger = 48778,
	Spell_Todesritter_Obliterate = 51425,
	Spell_Todesritter_Death_Strike = 49924,
	//Talent - Todesritter
	Spell_Todesritter_Heart_Strike = 55262, // Talent - Blood
	Spell_Todesritter_Frost_Strike = 55268, // Talent - Frost
	Spell_Todesritter_Howling_Blast = 51411, // Talent - Frost
	Spell_Todesritter_Scourge_Strike = 55271, // Talent - Unholy
	Spell_Todesritter_Corpse_Explosion = 51328 // Talent - Unholy

};

enum Spell_Druide
{
	Spell_Druide_Healing_Touch = 48378,
	Spell_Druide_Mark_of_the_Wild = 48469,
	Spell_Druide_Wrath = 48461,
	Spell_Druide_Moonfire = 48463,
	Spell_Druide_Rejuvenation = 48441,
	Spell_Druide_Thorns = 53307,
	Spell_Druide_Entangling_Roots = 53308,
	Spell_Druide_Bear_Form = 5487,
	Spell_Druide_Demoralizing_Roar = 48560,
	Spell_Druide_Growl = 6795,
	Spell_Druide_Maul = 48480,
	Spell_Druide_Natures_Grasp = 53312,
	Spell_Druide_Teleport_Moonglade = 18960,
	Spell_Druide_Enrage = 5229,
	Spell_Druide_Regrowth = 48443,
	Spell_Druide_Revive = 50763,
	Spell_Druide_Bash = 8983,
	Spell_Druide_Cure_Poison = 8946,
	Spell_Druide_Aquatic_Form = 1066,
	Spell_Druide_Swipe_Bear = 48562,
	Spell_Druide_Travel_Form = 783,
	Spell_Druide_Faerie_Fire = 770,
	Spell_Druide_Faerie_Fire_Feral = 16857,
	Spell_Druide_Hibernate = 18658,
	Spell_Druide_Cat_Form = 768,
	Spell_Druide_Feral_Charge_Bear = 16979,
	Spell_Druide_Feral_Charge_Cat = 49376,
	Spell_Druide_Prowl = 5215,
	Spell_Druide_Rebirth = 48477,
	Spell_Druide_Rip = 49800,
	Spell_Druide_Starfire = 48465,
	Spell_Druide_Shred = 48572,
	Spell_Druide_Soothe_Animal = 26995,
	Spell_Druide_Rake = 48574,
	Spell_Druide_Remove_Curse = 2782,
	Spell_Druide_Tigers_Fury = 50213,
	Spell_Druide_Abolish_Poison = 2893,
	Spell_Druide_Dash = 33357,
	Spell_Druide_Challenging_Roar = 5209,
	Spell_Druide_Cower = 48575,
	Spell_Druide_Tranquility = 48447,
	Spell_Druide_Ferocious_Bite = 48577,
	Spell_Druide_Ravage = 48579,
	Spell_Druide_Track_Humanoids = 5225,
	Spell_Druide_Frenzied_Regeneration = 22842,
	Spell_Druide_Pounce = 49803,
	Spell_Druide_Dire_Bear_Form = 9634,
	Spell_Druide_Feline_Grace = 20719,
	Spell_Druide_Hurricane = 48467,
	Spell_Druide_Innervate = 29166,
	Spell_Druide_Savage_Defense = 62600,
	Spell_Druide_Barkskin = 22812,
	Spell_Druide_Gift_of_the_Wild = 48470,
	Spell_Druide_Mangle_Bear = 48564,
	Spell_Druide_Mangle_Cat = 48566,
	Spell_Druide_Flight_Form = 33943,
	Spell_Druide_Maim = 49802,
	Spell_Druide_Lifebloom = 48451,
	Spell_Druide_Lacerate = 48568,
	Spell_Druide_Cyclone = 33786,
	Spell_Druide_Swift_Flight_Form = 40120,
	Spell_Druide_Swipe_Cat = 62078,
	Spell_Druide_Savage_Roar = 52610,
	Spell_Druide_Nourish = 50464,
	Spell_Druide_Claw_1 = 1082,
	Spell_Druide_Claw = 48570,
	//Talent - Druide
	Spell_Druide_Typhoon = 61384, // Talent - Balance
	Spell_Druide_Starfall = 53201, // Talent - Balance
	Spell_Druide_Wild_Growth = 53251, // Talent - Restoration
	Spell_Druide_Insect_Swarm = 48468 // Talent - Balance
};

enum Spell_Schamane
{
	Spell_Schamane_Earth_Elemental_Totem = 2062,
	Spell_Schamane_Healing_Wave = 49273,
	Spell_Schamane_Lightning_Bolt = 49238,
	Spell_Schamane_Rockbiter_Weapon = 10399,
	Spell_Schamane_Earth_Shock = 49231,
	Spell_Schamane_Stoneskin_Totem = 58753,
	Spell_Schamane_Earthbind_Totem = 2484,
	Spell_Schamane_Lightning_Shield = 49281,
	Spell_Schamane_Stoneclaw_Totem = 58582,
	Spell_Schamane_Flame_Shock = 49233,
	Spell_Schamane_Flametongue_Weapon = 58790,
	Spell_Schamane_Searing_Totem = 58704,
	Spell_Schamane_Strength_of_Earth_Totem = 58643,
	Spell_Schamane_Ancestral_Spirit = 49277,
	Spell_Schamane_Fire_Nova = 61657,
	Spell_Schamane_Purge = 8012,
	Spell_Schamane_Cure_Toxins = 526,
	Spell_Schamane_Ghost_Wolf = 2645,
	Spell_Schamane_Wind_Shear = 57994,
	Spell_Schamane_Tremor_Totem = 8143,
	Spell_Schamane_Frost_Shock = 49236,
	Spell_Schamane_Frostbrand_Weapon = 58796,
	Spell_Schamane_Healing_Stream_Totem = 58757,
	Spell_Schamane_Lesser_Healing_Wave = 49276,
	Spell_Schamane_Water_Shield = 57960,
	Spell_Schamane_Water_Breathing = 131,
	Spell_Schamane_Frost_Resistance_Totem = 58745,
	Spell_Schamane_Far_Sight = 6196,
	Spell_Schamane_Magma_Totem = 58734,
	Spell_Schamane_Mana_Spring_Totem = 58774,
	Spell_Schamane_Fire_Resistance_Totem = 58739,
	Spell_Schamane_Flametongue_Totem = 58656,
	Spell_Schamane_Water_Walking = 546,
	Spell_Schamane_Astral_Recall = 556,
	Spell_Schamane_Call_of_the_Elements = 66842,
	Spell_Schamane_Earthliving_Weapon = 51994,
	Spell_Schamane_Grounding_Totem = 8177,
	Spell_Schamane_Nature_Resistance_Totem = 58749,
	Spell_Schamane_Reincarnation = 20608,
	Spell_Schamane_Totemic_Recall = 36936,
	Spell_Schamane_Windfury_Weapon = 58804,
	Spell_Schamane_Chain_Lightning = 49271,
	Spell_Schamane_Windfury_Totem = 8512,
	Spell_Schamane_Sentry_Totem = 6495,
	Spell_Schamane_Cleansing_Totem = 8170,
	Spell_Schamane_Call_of_the_Ancestors = 66843,
	Spell_Schamane_Chain_Heal = 55459,
	Spell_Schamane_Call_of_the_Spirits = 66844,
	Spell_Schamane_Wrath_of_Air_Totem = 3738,
	Spell_Schamane_Fire_Elemental_Totem = 2894,
	Spell_Schamane_Lava_Burst = 60043,
	Spell_Schamane_Hex = 51514,
	Spell_Schamane_Bloodlust = 2825, // Horde
	Spell_Schamane_Heroism = 32182, // Alliance
	//Talent - Schamane
	Spell_Schamane_Riptide = 61301, // Talent - Restoration
	Spell_Schamane_Earth_Shield = 49284, // Talent - Restoration
	Spell_Schamane_Totem_of_Wrath = 57722, // Talent - Elemental
	Spell_Schamane_Thunderstorm = 59159   // Talent - Elemental
};

enum Spell_Jaeger
{
	Spell_Jaeger_Scorpid_Sting = 3043,
	Spell_Jaeger_Parry = 3127,
	Spell_Jaeger_Rapid_Fire = 3045,
	Spell_Jaeger_Viper_Sting = 3034,
	Spell_Jaeger_Track_Beasts = 1494,
	Spell_Jaeger_Aspect_of_the_Monkey = 13163,
	Spell_Jaeger_Raptor_Strike = 48996,
	Spell_Jaeger_Serpent_Sting = 49001,
	Spell_Jaeger_Arcane_Shot = 49045,
	Spell_Jaeger_Hunters_Mark = 53338,
	Spell_Jaeger_Concussive_Shot = 5116,
	Spell_Jaeger_Aspect_of_the_Hawk = 27044,
	Spell_Jaeger_Call_Pet = 883,
	Spell_Jaeger_Dismiss_Pet = 2641,
	Spell_Jaeger_Feed_Pet = 6991,
	Spell_Jaeger_Revive_Pet = 982,
	Spell_Jaeger_Tame_Beast = 1515,
	Spell_Jaeger_Track_Humanoids = 19883,
	Spell_Jaeger_Distracting_Shot = 20736,
	Spell_Jaeger_Mend_Pet = 48990,
	Spell_Jaeger_Wing_Clip = 2974,
	Spell_Jaeger_Eagle_Eye = 6197,
	Spell_Jaeger_Eyes_of_the_Beast = 1002,
	Spell_Jaeger_Scare_Beast = 14327,
	Spell_Jaeger_Aspect_of_the_Cheetah = 5118,
	Spell_Jaeger_Immolation_Trap = 49056,
	Spell_Jaeger_Mongoose_Bite = 53339,
	Spell_Jaeger_Multi_Shot = 49048,
	Spell_Jaeger_Track_Undead = 19884,
	Spell_Jaeger_Aspect_of_the_Viper = 34074,
	Spell_Jaeger_Disengage = 781,
	Spell_Jaeger_Freezing_Trap = 14311,
	Spell_Jaeger_Beast_Lore = 1462,
	Spell_Jaeger_Track_Hidden = 19885,
	Spell_Jaeger_Track_Elementals = 19880,
	Spell_Jaeger_Frost_Trap = 13809,
	Spell_Jaeger_Aspect_of_the_Beast = 13161,
	Spell_Jaeger_Feign_Death = 5384,
	Spell_Jaeger_Flare = 1543,
	Spell_Jaeger_Track_Demons = 19878,
	Spell_Jaeger_Explosive_Trap = 49067,
	Spell_Jaeger_Aspect_of_the_Pack = 13159,
	Spell_Jaeger_Track_Giants = 19882,
	Spell_Jaeger_Volley = 58434,
	Spell_Jaeger_Aspect_of_the_Wild = 49071,
	Spell_Jaeger_Steady_Shot = 49052,
	Spell_Jaeger_Track_Dragonkin = 19879,
	Spell_Jaeger_Deterrence = 19263,
	Spell_Jaeger_Tranquilizing_Shot = 19801,
	Spell_Jaeger_Kill_Command = 34026,
	Spell_Jaeger_Snake_Trap = 34600,
	Spell_Jaeger_Misdirection = 34477,
	Spell_Jaeger_Kill_Shot = 61006,
	Spell_Jaeger_Aspect_of_the_Dragonhawk = 61847,
	Spell_Jaeger_Masters_Call = 53271,
	Spell_Jaeger_Freezing_Arrow = 60192,
	Spell_Jaeger_Call_Stabled_Pet = 62757,
	Spell_Jaeger_Dual_Wield = 42459,
	//Talent - Jaeger
	Spell_Jaeger_Wyvern_Sting = 49012,  // Talent - Survival
	Spell_Jaeger_Explosive_Shot = 60053, // Talent - Survival
	Spell_Jaeger_Conterattack = 48999, // Talent - Survival
	Spell_Jaeger_Aimed_Shot = 49050  // Talent - Marksmanship
};

enum Spell_Schurke
{
	Spell_Schurke_Parry = 3127,
	Spell_Schurke_Dual_Wield = 42459,
	Spell_Schurke_Eviscerate = 48668,
	Spell_Schurke_Sinister_Strike = 48638,
	Spell_Schurke_Stealth = 1784,
	Spell_Schurke_Backstab = 48657,
	Spell_Schurke_Pick_Pocket = 921,
	Spell_Schurke_Gouge = 1776,
	Spell_Schurke_Evasion = 26669,
	Spell_Schurke_Sap = 51724,
	Spell_Schurke_Slice_and_Dice = 6774,
	Spell_Schurke_Sprint = 11305,
	Spell_Schurke_Kick = 1766,
	Spell_Schurke_Garrote = 48676,
	Spell_Schurke_Feint = 48659,
	Spell_Schurke_Lockpicking_skill = 1804,
	Spell_Schurke_Expose_Armor = 8647,
	Spell_Schurke_Ambush = 48691,
	Spell_Schurke_Dismantle = 51722,
	Spell_Schurke_Rupture = 48672,
	Spell_Schurke_Distract = 1725,
	Spell_Schurke_Vanish = 26889,
	Spell_Schurke_Detect_Traps = 2836,
	Spell_Schurke_Cheap_Shot = 1833,
	Spell_Schurke_Disarm_Trap = 1842,
	Spell_Schurke_Kidney_Shot = 8643,
	Spell_Schurke_Blind = 2094,
	Spell_Schurke_Safe_Fall = 1860,
	Spell_Schurke_Envenom = 57993,
	Spell_Schurke_Deadly_Throw = 48674,
	Spell_Schurke_Cloak_of_Shadows = 31224,
	Spell_Schurke_Shiv = 5938,
	Spell_Schurke_Tricks_of_the_Trade = 57934,
	Spell_Schurke_Fan_of_Knives = 51723,
	//Talent - Schurke
	Spell_Schurke_Hemorrhage = 48660, // Talent - Subtlety
	Spell_Schurke_Mutilate = 48666 // Talent - Assassination
};

enum Spell_Priester
{
	Spell_Priester_Cure_Disease = 528,
	Spell_Priester_Lesser_Heal = 2053,
	Spell_Priester_Power_Word_Fortitude = 48161,
	Spell_Priester_Smite = 48123,
	Spell_Priester_Shadow_Word_Pain = 48125,
	Spell_Priester_Power_Word_Shield = 48066,
	Spell_Priester_Fade = 586,
	Spell_Priester_Renew = 48068,
	Spell_Priester_Mind_Blast = 48127,
	Spell_Priester_Resurrection = 48171,
	Spell_Priester_Inner_Fire = 48168,
	Spell_Priester_Psychic_Scream = 10890,
	Spell_Priester_Heal = 6064,
	Spell_Priester_Dispel_Magic = 988,
	Spell_Priester_Devouring_Plague = 48300,
	Spell_Priester_Fear_Ward = 6346,
	Spell_Priester_Flash_Heal = 48071,
	Spell_Priester_Holy_Fire = 48135,
	Spell_Priester_Holy_Nova = 48078,
	Spell_Priester_Mind_Soothe = 453,
	Spell_Priester_Shackle_Undead = 10955,
	Spell_Priester_Mind_Vision = 10909,
	Spell_Priester_Mana_Burn = 8129,
	Spell_Priester_Divine_Spirit = 48073,
	Spell_Priester_Mind_Control = 605,
	Spell_Priester_Prayer_of_Healing = 48072,
	Spell_Priester_Shadow_Protection = 48169,
	Spell_Priester_Abolish_Disease = 552,
	Spell_Priester_Levitate = 1706,
	Spell_Priester_Greater_Heal = 48063,
	Spell_Priester_Prayer_of_Fortitude = 48162,
	Spell_Priester_Prayer_of_Shadow_Protection = 48170,
	Spell_Priester_Prayer_of_Spirit = 48074,
	Spell_Priester_Shadow_Word_Death = 48158,
	Spell_Priester_Binding_Heal = 48120,
	Spell_Priester_Shadowfiend = 34433,
	Spell_Priester_Prayer_of_Mending = 48113,
	Spell_Priester_Mass_Dispel = 32375,
	Spell_Priester_Divine_Hymn = 64843,
	Spell_Priester_Hymn_of_Hope = 64901,
	Spell_Priester_Mind_Sear = 53023,
	//Talent - Priester
	Spell_Priester_Vampiric_Touch = 48160, // Talent - Shadow
	Spell_Priester_Penance = 53007, // Talent - Discipline
	Spell_Priester_Lightwell = 48087, // Talent - Holy
	Spell_Priester_Desperate_Prayer = 48173, // Talent - Holy
	Spell_Priester_Circle_of_Healing = 48089, // Talent - Holy
	Spell_Priester_Mind_Flay = 48156 // Talent - Shadow
};

enum Spell_Hexenmeister
{
	Spell_Hexenmeister_Demon_Skin = 696,
	Spell_Hexenmeister_Immolate = 47811,
	Spell_Hexenmeister_Shadow_Bolt = 47809,
	Spell_Hexenmeister_Summon_Imp = 688,
	Spell_Hexenmeister_Corruption = 47813,
	Spell_Hexenmeister_Curse_of_Weakness = 50511,
	Spell_Hexenmeister_Life_Tap = 57946,
	Spell_Hexenmeister_Curse_of_Agony = 47864,
	Spell_Hexenmeister_Fear = 6215,
	Spell_Hexenmeister_Create_Healthstone = 47878,
	Spell_Hexenmeister_Drain_Soul = 47855,
	Spell_Hexenmeister_Summon_Voidwalker = 697,
	Spell_Hexenmeister_Health_Funnel = 47856,
	Spell_Hexenmeister_Drain_Life = 47857,
	Spell_Hexenmeister_Unending_Breath = 5697,
	Spell_Hexenmeister_Create_Soulstone = 47884,
	Spell_Hexenmeister_Searing_Pain = 47815,
	Spell_Hexenmeister_Demon_Armor = 47889,
	Spell_Hexenmeister_Rain_of_Fire = 47820,
	Spell_Hexenmeister_Ritual_of_Summoning = 698,
	Spell_Hexenmeister_Summon_Succubus = 712,
	Spell_Hexenmeister_Eye_of_Kilrogg = 126,
	Spell_Hexenmeister_Drain_Mana = 5138,
	Spell_Hexenmeister_Sense_Demons = 5500,
	Spell_Hexenmeister_Curse_of_Tongues = 11719,
	Spell_Hexenmeister_Detect_Invisibility = 132,
	Spell_Hexenmeister_Create_Firestone = 60220,
	Spell_Hexenmeister_Banish = 18647,
	Spell_Hexenmeister_Enslave_Demon = 61191,
	Spell_Hexenmeister_Hellfire = 47823,
	Spell_Hexenmeister_Summon_Felhunter = 691,
	Spell_Hexenmeister_Curse_of_the_Elements = 47865,
	Spell_Hexenmeister_Shadow_Ward = 47891,
	Spell_Hexenmeister_Create_Spellstone = 47888,
	Spell_Hexenmeister_Howl_of_Terror = 17928,
	Spell_Hexenmeister_Death_Coil = 47860,
	Spell_Hexenmeister_Soul_Fire = 47825,
	Spell_Hexenmeister_Inferno = 1122,
	Spell_Hexenmeister_Curse_of_Doom = 47867,
	Spell_Hexenmeister_Ritual_of_Doom = 18540,
	Spell_Hexenmeister_Fel_Armor = 47893,
	Spell_Hexenmeister_Incinerate = 47838,
	Spell_Hexenmeister_Soulshatter = 29858,
	Spell_Hexenmeister_Ritual_of_Souls = 58887,
	Spell_Hexenmeister_Seed_of_Corruption = 47836,
	Spell_Hexenmeister_Shadowflame = 61290,
	Spell_Hexenmeister_Demonic_Circle_Summon = 48018,
	Spell_Hexenmeister_Demonic_Circle_Teleport = 48020,
	Spell_Hexenmeister_Dreadsteed = 23161,
	//Talent - Hexenmeister
	Spell_Hexenmeister_Shadowburn = 47827, // Talent - Destruction
	Spell_Hexenmeister_Shadowfury = 47847, // Talent - Destruction
	Spell_Hexenmeister_Unstable_Affliction = 47843, // Talent - Affliction
	Spell_Hexenmeister_Chaos_Bolt = 59172, // Talent - Destruction
	Spell_Hexenmeister_Haunt = 59164, // Talent - Affliction
	Spell_Hexenmeister_Dark_Pact = 59092 // Talent - Affliction
};


enum Zusatz_Reiten
{
	//Zusatz_Reiten_Master_Riding = 90265, cata
	Zusatz_Reiten_Journeyman_Riding = 33392,
	Zusatz_Reiten_Cold_Weather_Flying = 54197,
	Zusatz_Reiten_Flight_Master_License = 90267
};

enum Zusatz_Reiten_itemid
{
	Mount_Invincibles_Reins = 50818,
};

//////////////////////WELCOME MENU/////////////////////////////////
#define Class_Skills  "I would like to learn my Class & Weapon skills"	   
#define Glyph_Menu    "I would like to buy somes glyphs"
#define Talent_Skills "Talent Skills & Reset Talents"
#define Riding_Skills "I would like to learn my Riding skills"
#define nevermind 	  "[nevermind]"		 
#define back 		  "[back]"
//SUB WELCOME MENU//
#define SUB_MENU_TALENT_OPTION_1 "Maxskill my Talent"
#define SUB_MENU_TALENT_OPTION_2 "Reset My Talent"
/////////////////////NPC ID MENU////////////////////////////////
/*You need to do 10 npc for this (Experimental)*/
//Change 0 To your NPC Vendor ID
enum GLYPH_NPC_ID
{
	GLYPH_NPC_ID_WARRIOR = 0,
	GLYPH_NPC_ID_PALADIN = 0,
	GLYPH_NPC_ID_HUNTER = 0,
	GLYPH_NPC_ID_MAGE = 0,
	GLYPH_NPC_ID_PRIEST = 0,
	GLYPH_NPC_ID_ROGUE = 0,
	GLYPH_NPC_ID_DRUID = 0,
	GLYPH_NPC_ID_WARLOCK = 0,
	GLYPH_NPC_ID_DK = 0,
	GLYPH_NPC_ID_SHAMAN = 0
};
enum CLASSES_MENU_ID
{
	MENU_WARRIOR = 1,
	MENU_PALADIN = 2,
	MENU_HUNTER = 3,
	MENU_ROGUE = 4,
	MENU_PRIEST = 5,
	MENU_DEATH_K = 6,
	MENU_SHAMAN = 7,
	MENU_MAGE = 8,
	MENU_WARLOCK = 9,
	MENU_DRUID = 10
};

enum OPTION_MENU_ID //11->50
{
	OPTION_MENU_ID_1 = 11,
	OPTION_MENU_ID_2 = 12,
	OPTION_MENU_ID_3 = 13,
	OPTION_MENU_ID_4 = 14
};

enum SUB_OPTION_MENU_ID //51->100
{
	SUB_OPTION_MENU_ID_1 = 51,
	SUB_OPTION_MENU_ID_2 = 52,
	SUB_OPTION_MENU_ID_3 = 53,
	SUB_OPTION_MENU_ID_4 = 54
};

enum BACK_OPTION //1000->
{
	BACK_OPTION_MENU_1 = 1000, //Main Menu
	BACK_OPTION_MENU_2 = 1001, //Other
};

class npc_welcome : public CreatureScript
{
public:
	npc_welcome() : CreatureScript("npc_welcome") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->getLevel() >= 80)
		{
			{
				player->PrepareQuestMenu(creature->GetGUID());
				player->SendPreparedQuest(creature->GetGUID());
			}
			if (player->getClass() == CLASS_WARRIOR)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_WARRIOR);
			}
			if (player->getClass() == CLASS_PALADIN)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_PALADIN);
			}
			if (player->getClass() == CLASS_HUNTER)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_HUNTER);
			}
			if (player->getClass() == CLASS_ROGUE)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_ROGUE);
			}
			if (player->getClass() == CLASS_PRIEST)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_PRIEST);
			}
			if (player->getClass() == CLASS_DEATH_KNIGHT)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_DEATH_K);
			}
			if (player->getClass() == CLASS_SHAMAN)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_SHAMAN);
			}
			if (player->getClass() == CLASS_MAGE)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_MAGE);
			}
			if (player->getClass() == CLASS_WARLOCK)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_WARLOCK);
			}
			if (player->getClass() == CLASS_DRUID)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_DRUID);
			}

			player->ADD_GOSSIP_ITEM(TRAINER_ICON, Talent_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_1);
			player->ADD_GOSSIP_ITEM(TRAINER_ICON, Riding_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_2);
			player->ADD_GOSSIP_ITEM(VENDOR_ICON, Glyph_Menu, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_3);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		}
		else
		{
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
	{
		WorldSession * PGS = player->GetSession();

		player->PlayerTalkClass->ClearMenus();
		{
			//=============================================Dual Specc=================================================//
			player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
			player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());
			//=====================================================================================================//
			switch (action)
			{
			//=============================================Krieger=================================================//
			case MENU_WARRIOR:
				player->learnSpell(Spell_Krieger_Overpower, false),
					player->learnSpell(Spell_Krieger_Battle_Shout, false),
					player->learnSpell(Spell_Krieger_Heroic_Strike, false),
					player->learnSpell(Spell_Krieger_Charge, false),
					player->learnSpell(Spell_Krieger_Rend, false),
					player->learnSpell(Spell_Krieger_Thunder_Clap, false),
					player->learnSpell(Spell_Krieger_Victory_Rush, false),
					player->learnSpell(Spell_Krieger_Hamstring, false),
					player->learnSpell(Spell_Krieger_Bloodrage, false),
					player->learnSpell(Spell_Krieger_Defensive_Stance, false),
					player->learnSpell(Spell_Krieger_Sunder_Armor, false),
					player->learnSpell(Spell_Krieger_Taunt, false),
					player->learnSpell(Spell_Krieger_Shield_Bash, false),
					player->learnSpell(Spell_Krieger_Demoralizing_Shout, false),
					player->learnSpell(Spell_Krieger_Revenge, false),
					player->learnSpell(Spell_Krieger_Mocking_Blow, false),
					player->learnSpell(Spell_Krieger_Shield_Block, false),
					player->learnSpell(Spell_Krieger_Disarm, false),
					player->learnSpell(Spell_Krieger_Cleave, false),
					player->learnSpell(Spell_Krieger_Retaliation, false),
					player->learnSpell(Spell_Krieger_Stance_Mastery, false),
					player->learnSpell(Spell_Krieger_Execute, false),
					player->learnSpell(Spell_Krieger_Challenging_Shout, false),
					player->learnSpell(Spell_Krieger_Shield_Wall, false),
					player->learnSpell(Spell_Krieger_Berserker_Stance, false),
					player->learnSpell(Spell_Krieger_Intercept, false),
					player->learnSpell(Spell_Krieger_Slam, false),
					player->learnSpell(Spell_Krieger_Berserker_Rage, false),
					player->learnSpell(Spell_Krieger_Whirlwind, false),
					player->learnSpell(Spell_Krieger_Pummel, false),
					player->learnSpell(Spell_Krieger_Sheild_Slam, false),
					player->learnSpell(Spell_Krieger_Recklessness, false),
					player->learnSpell(Spell_Krieger_Spell_Reflection, false),
					player->learnSpell(Spell_Krieger_Commanding_Shout, false),
					player->learnSpell(Spell_Krieger_Intervene, false),
					player->learnSpell(Spell_Krieger_Shattering_Throw, false),
					player->learnSpell(Spell_Krieger_Enraged_Regeneration, false),
					player->learnSpell(Spell_Krieger_Heroic_Throw, false),
					player->learnSpell(Spell_Krieger_Dual_Wield, false),
					player->learnSpell(Spell_Krieger_Intimidating_Shout, false);
				player->learnSpell(Spell_Krieger_Parry, false);
				player->learnSpell(54197, false); // ?
												  /////////WEAPON/////////////
				player->learnSpell(750, false); // ?
				player->learnSpell(196, false); // ?
				player->learnSpell(197, false); // ?
				player->learnSpell(198, false); // ?
				player->learnSpell(199, false); // ?
				player->learnSpell(200, false); // ?
				player->learnSpell(201, false); // ?
				player->learnSpell(202, false); // ?
				player->learnSpell(264, false); // ?
				player->learnSpell(5011, false); // ?
				player->learnSpell(266, false); // ?
				player->learnSpell(2567, false); // ?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================PALADIN=================================================//
			case MENU_PALADIN:
				player->learnSpell(Spell_Paladin_Parry, false);
				player->learnSpell(Spell_Paladin_Concentration_Aura, false);
				player->learnSpell(Spell_Paladin_Divine_Intervention, false);
				player->learnSpell(Spell_Paladin_Plate_Mail_skill, false);
				player->learnSpell(Spell_Paladin_Devotion_Aura, false);
				player->learnSpell(Spell_Paladin_Holy_Light, false);
				player->learnSpell(Spell_Paladin_Blessing_of_Might, false);
				player->learnSpell(Spell_Paladin_Judgement_of_Light, false);
				player->learnSpell(Spell_Paladin_Divine_Protection, false);
				player->learnSpell(Spell_Paladin_Hammer_of_Justice, false);
				player->learnSpell(Spell_Paladin_Purify, false);
				player->learnSpell(Spell_Paladin_Hand_of_Protection, false);
				player->learnSpell(Spell_Paladin_Lay_on_Hands, false);
				player->learnSpell(Spell_Paladin_Judgement_of_Wisdom, false);
				player->learnSpell(Spell_Paladin_Redemption, false);
				player->learnSpell(Spell_Paladin_Blessing_of_Wisdom, false);
				player->learnSpell(Spell_Paladin_Righteous_Defense, false);
				player->learnSpell(Spell_Paladin_Hand_of_Reckoning, false);
				player->learnSpell(Spell_Paladin_Retribution_Aura, false);
				player->learnSpell(Spell_Paladin_Righteous_Fury, false);
				player->learnSpell(Spell_Paladin_Hand_of_Freedom, false);
				player->learnSpell(Spell_Paladin_Blessing_of_Kings, false);
				player->learnSpell(Spell_Paladin_Consecration, false);
				player->learnSpell(Spell_Paladin_Exorcism, false);
				player->learnSpell(Spell_Paladin_Flash_of_Light, false);
				player->learnSpell(Spell_Paladin_Sense_Undead, false);
				player->learnSpell(Spell_Paladin_Seal_of_Justice, false);
				player->learnSpell(Spell_Paladin_Turn_Evil, false);
				player->learnSpell(Spell_Paladin_Hand_of_Salvation, false);
				player->learnSpell(Spell_Paladin_Judgement_of_Justice, false);
				player->learnSpell(Spell_Paladin_Shadow_Resistance_Aura, false);
				player->learnSpell(Spell_Paladin_Seal_of_Light, false);
				player->learnSpell(Spell_Paladin_Frost_Resistance_Aura, false);
				player->learnSpell(Spell_Paladin_Divine_Shield, false);
				player->learnSpell(Spell_Paladin_Fire_Resistance_Aura, false);
				player->learnSpell(Spell_Paladin_Seal_of_Wisdom, false);
				player->learnSpell(Spell_Paladin_Cleanse, false);
				player->learnSpell(Spell_Paladin_Hammer_of_Wrath, false);
				player->learnSpell(Spell_Paladin_Hand_of_Sacrifice, false);
				player->learnSpell(Spell_Paladin_Holy_Wrath, false);
				player->learnSpell(Spell_Paladin_Greater_Blessing_of_Might, false);
				player->learnSpell(Spell_Paladin_Greater_Blessing_of_Wisdom, false);
				player->learnSpell(Spell_Paladin_Greater_Blessing_of_Kings, false);
				player->learnSpell(Spell_Paladin_Crusader_Aura, false);
				player->learnSpell(Spell_Paladin_Avenging_Wrath, false);
				player->learnSpell(Spell_Paladin_Divine_Plea, false);
				player->learnSpell(Spell_Paladin_Shield_of_Righteousness, false);
				player->learnSpell(Spell_Paladin_Sacred_Shield, false);
				player->learnSpell(33388, false); //?
				player->learnSpell(33391, false); //?
				/////////WEAPONS/////////////
				player->learnSpell(750, false); //?
				player->learnSpell(196, false); //?
				player->learnSpell(197, false); //?
				player->learnSpell(198, false); //?
				player->learnSpell(199, false); //?
				player->learnSpell(200, false); //?
				player->learnSpell(201, false); //?
				player->learnSpell(202, false);	//?	 		
												//Spell Learned for different factions..
				if (player->GetTeam() == ALLIANCE) {
					player->learnSpell(Spell_Paladin_Seal_of_Vengeance, false);
					player->learnSpell(Spell_Paladin_Warhorse, false);
					player->learnSpell(Spell_Paladin_Charger, false);
				}
				else
				{
					player->learnSpell(Spell_Paladin_Seal_of_Corruption, false);
					player->learnSpell(Spell_Paladin_Thalassian_Warhorse, false);
					player->learnSpell(Spell_Paladin_Thalassian_Charger, false);
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================HUNTER=================================================//
			case MENU_HUNTER:
				player->learnSpell(Spell_Jaeger_Scorpid_Sting, false);
				player->learnSpell(Spell_Jaeger_Parry, false);
				player->learnSpell(Spell_Jaeger_Rapid_Fire, false);
				player->learnSpell(Spell_Jaeger_Viper_Sting, false);
				player->learnSpell(Spell_Jaeger_Track_Beasts, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Monkey, false);
				player->learnSpell(Spell_Jaeger_Raptor_Strike, false);
				player->learnSpell(Spell_Jaeger_Serpent_Sting, false);
				player->learnSpell(Spell_Jaeger_Arcane_Shot, false);
				player->learnSpell(Spell_Jaeger_Hunters_Mark, false);
				player->learnSpell(Spell_Jaeger_Concussive_Shot, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Hawk, false);
				player->learnSpell(Spell_Jaeger_Call_Pet, false);
				player->learnSpell(Spell_Jaeger_Dismiss_Pet, false);
				player->learnSpell(Spell_Jaeger_Feed_Pet, false);
				player->learnSpell(Spell_Jaeger_Revive_Pet, false);
				player->learnSpell(Spell_Jaeger_Tame_Beast, false);
				player->learnSpell(Spell_Jaeger_Track_Humanoids, false);
				player->learnSpell(Spell_Jaeger_Distracting_Shot, false);
				player->learnSpell(Spell_Jaeger_Mend_Pet, false);
				player->learnSpell(Spell_Jaeger_Wing_Clip, false);
				player->learnSpell(Spell_Jaeger_Eagle_Eye, false);
				player->learnSpell(Spell_Jaeger_Eyes_of_the_Beast, false);
				player->learnSpell(Spell_Jaeger_Scare_Beast, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Cheetah, false);
				player->learnSpell(Spell_Jaeger_Immolation_Trap, false);
				player->learnSpell(Spell_Jaeger_Mongoose_Bite, false);
				player->learnSpell(Spell_Jaeger_Multi_Shot, false);
				player->learnSpell(Spell_Jaeger_Track_Undead, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Viper, false);
				player->learnSpell(Spell_Jaeger_Disengage, false);
				player->learnSpell(Spell_Jaeger_Freezing_Trap, false);
				player->learnSpell(Spell_Jaeger_Beast_Lore, false);
				player->learnSpell(Spell_Jaeger_Track_Hidden, false);
				player->learnSpell(Spell_Jaeger_Track_Elementals, false);
				player->learnSpell(Spell_Jaeger_Frost_Trap, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Beast, false);
				player->learnSpell(Spell_Jaeger_Feign_Death, false);
				player->learnSpell(Spell_Jaeger_Flare, false);
				player->learnSpell(Spell_Jaeger_Track_Demons, false);
				player->learnSpell(Spell_Jaeger_Explosive_Trap, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Pack, false);
				player->learnSpell(Spell_Jaeger_Track_Giants, false);
				player->learnSpell(Spell_Jaeger_Volley, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Wild, false);
				player->learnSpell(Spell_Jaeger_Steady_Shot, false);
				player->learnSpell(Spell_Jaeger_Track_Dragonkin, false);
				player->learnSpell(Spell_Jaeger_Deterrence, false);
				player->learnSpell(Spell_Jaeger_Tranquilizing_Shot, false);
				player->learnSpell(Spell_Jaeger_Kill_Command, false);
				player->learnSpell(Spell_Jaeger_Snake_Trap, false);
				player->learnSpell(Spell_Jaeger_Misdirection, false);
				player->learnSpell(Spell_Jaeger_Kill_Shot, false);
				player->learnSpell(Spell_Jaeger_Aspect_of_the_Dragonhawk, false);
				player->learnSpell(Spell_Jaeger_Masters_Call, false);
				player->learnSpell(Spell_Jaeger_Freezing_Arrow, false);
				player->learnSpell(Spell_Jaeger_Call_Stabled_Pet, false);
				player->learnSpell(Spell_Jaeger_Dual_Wield, false);
				player->learnSpell(8737, false); //?
				/////////ARRMES/////////////
				player->learnSpell(15590, false); //?
				player->learnSpell(8737, false); //?
				player->learnSpell(196, false); //?
				player->learnSpell(197, false); //?
				player->learnSpell(200, false); //?
				player->learnSpell(201, false); //?
				player->learnSpell(202, false); //?
				player->learnSpell(264, false); //?
				player->learnSpell(266, false); //?
				player->learnSpell(5011, false); //?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================ROGUE=================================================//
			case MENU_ROGUE:
				player->learnSpell(Spell_Schurke_Parry, false);
				player->learnSpell(Spell_Schurke_Dual_Wield, false); //  ambi
				player->learnSpell(Spell_Schurke_Eviscerate, false);
				player->learnSpell(Spell_Schurke_Sinister_Strike, false);
				player->learnSpell(Spell_Schurke_Stealth, false);
				player->learnSpell(Spell_Schurke_Backstab, false);
				player->learnSpell(Spell_Schurke_Pick_Pocket, false);
				player->learnSpell(Spell_Schurke_Gouge, false);
				player->learnSpell(Spell_Schurke_Evasion, false);
				player->learnSpell(Spell_Schurke_Sap, false);
				player->learnSpell(Spell_Schurke_Slice_and_Dice, false);
				player->learnSpell(Spell_Schurke_Sprint, false);
				player->learnSpell(Spell_Schurke_Kick, false);
				player->learnSpell(Spell_Schurke_Garrote, false);
				player->learnSpell(Spell_Schurke_Feint, false);
				player->learnSpell(Spell_Schurke_Lockpicking_skill, false);
				player->learnSpell(Spell_Schurke_Expose_Armor, false);
				player->learnSpell(Spell_Schurke_Ambush, false);
				player->learnSpell(Spell_Schurke_Dismantle, false);
				player->learnSpell(Spell_Schurke_Rupture, false);
				player->learnSpell(Spell_Schurke_Distract, false);
				player->learnSpell(Spell_Schurke_Vanish, false);
				player->learnSpell(Spell_Schurke_Detect_Traps, false);
				player->learnSpell(Spell_Schurke_Cheap_Shot, false);
				player->learnSpell(Spell_Schurke_Disarm_Trap, false);
				player->learnSpell(Spell_Schurke_Kidney_Shot, false);
				player->learnSpell(Spell_Schurke_Blind, false);
				player->learnSpell(Spell_Schurke_Safe_Fall, false);
				player->learnSpell(Spell_Schurke_Envenom, false);
				player->learnSpell(Spell_Schurke_Deadly_Throw, false);
				player->learnSpell(Spell_Schurke_Cloak_of_Shadows, false);
				player->learnSpell(Spell_Schurke_Shiv, false);
				player->learnSpell(Spell_Schurke_Tricks_of_the_Trade, false);
				player->learnSpell(Spell_Schurke_Fan_of_Knives, false);
				///////////WEAPON/////////////
				player->learnSpell(196, false); //? 
				player->learnSpell(198, false); //? 
				player->learnSpell(201, false); //? 
				player->learnSpell(1180, false); //? 
				player->learnSpell(2567, false); //? 
				player->learnSpell(264, false); //? 
				player->learnSpell(266, false); //? 
				player->learnSpell(5011, false); //? 
				player->learnSpell(15590, false); //? 
				//======================================//
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case MENU_PRIEST:
				player->learnSpell(Spell_Priester_Cure_Disease, false);
				player->learnSpell(Spell_Priester_Lesser_Heal, false);
				player->learnSpell(Spell_Priester_Power_Word_Fortitude, false);
				player->learnSpell(Spell_Priester_Smite, false);
				player->learnSpell(Spell_Priester_Shadow_Word_Pain, false);
				player->learnSpell(Spell_Priester_Power_Word_Shield, false);
				player->learnSpell(Spell_Priester_Fade, false);
				player->learnSpell(Spell_Priester_Renew, false);
				player->learnSpell(Spell_Priester_Mind_Blast, false);
				player->learnSpell(Spell_Priester_Resurrection, false);
				player->learnSpell(Spell_Priester_Inner_Fire, false);
				player->learnSpell(Spell_Priester_Psychic_Scream, false);
				player->learnSpell(Spell_Priester_Heal, false);
				player->learnSpell(Spell_Priester_Dispel_Magic, false);
				player->learnSpell(Spell_Priester_Devouring_Plague, false);
				player->learnSpell(Spell_Priester_Fear_Ward, false);
				player->learnSpell(Spell_Priester_Flash_Heal, false);
				player->learnSpell(Spell_Priester_Holy_Fire, false);
				player->learnSpell(Spell_Priester_Holy_Nova, false);
				player->learnSpell(Spell_Priester_Mind_Soothe, false);
				player->learnSpell(Spell_Priester_Shackle_Undead, false);
				player->learnSpell(Spell_Priester_Mind_Vision, false);
				player->learnSpell(Spell_Priester_Mana_Burn, false);
				player->learnSpell(Spell_Priester_Divine_Spirit, false);
				player->learnSpell(Spell_Priester_Mind_Control, false);
				player->learnSpell(Spell_Priester_Prayer_of_Healing, false);
				player->learnSpell(Spell_Priester_Shadow_Protection, false);
				player->learnSpell(Spell_Priester_Abolish_Disease, false);
				player->learnSpell(Spell_Priester_Levitate, false);
				player->learnSpell(Spell_Priester_Greater_Heal, false);
				player->learnSpell(Spell_Priester_Prayer_of_Fortitude, false);
				player->learnSpell(Spell_Priester_Prayer_of_Shadow_Protection, false);
				player->learnSpell(Spell_Priester_Prayer_of_Spirit, false);
				player->learnSpell(Spell_Priester_Shadow_Word_Death, false);
				player->learnSpell(Spell_Priester_Binding_Heal, false);
				player->learnSpell(Spell_Priester_Shadowfiend, false);
				player->learnSpell(Spell_Priester_Prayer_of_Mending, false);
				player->learnSpell(Spell_Priester_Mass_Dispel, false);
				player->learnSpell(Spell_Priester_Divine_Hymn, false);
				player->learnSpell(Spell_Priester_Hymn_of_Hope, false);
				player->learnSpell(Spell_Priester_Mind_Sear, false);
				///////////WEAPON/////////////
				player->learnSpell(196, false); //?
				player->learnSpell(198, false); //?
				player->learnSpell(227, false); //?
				player->learnSpell(1180, false); //?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================DEATH KNGIHTS=================================================//
			case MENU_DEATH_K:
				player->learnSpell(Spell_Todesritter_Parry, false);
				player->learnSpell(Spell_Todesritter_Pestilence, false);
				player->learnSpell(Spell_Todesritter_Blood_Boil, false);
				player->learnSpell(Spell_Todesritter_Blood_Strike, false);
				player->learnSpell(Spell_Todesritter_Strangulate, false);
				player->learnSpell(Spell_Todesritter_Blood_Tap, false);
				player->learnSpell(Spell_Todesritter_Path_of_Frost, false);
				player->learnSpell(Spell_Todesritter_Dark_Command, false);
				player->learnSpell(Spell_Todesritter_Death_Pact, false);
				player->learnSpell(Spell_Todesritter_Frost_Presence, false);
				player->learnSpell(Spell_Todesritter_Icy_Touch, false);
				player->learnSpell(Spell_Todesritter_Mind_Freeze, false);
				player->learnSpell(Spell_Todesritter_Chains_of_Ice, false);
				player->learnSpell(Spell_Todesritter_Icebound_Fortitude, false);
				player->learnSpell(Spell_Todesritter_Horn_of_Winter, false);
				player->learnSpell(Spell_Todesritter_Rune_Strike, false);
				player->learnSpell(Spell_Todesritter_Empower_Rune_Weapon, false);
				player->learnSpell(Spell_Todesritter_Death_Coil, false);
				player->learnSpell(Spell_Todesritter_Death_Gate, false);
				player->learnSpell(Spell_Todesritter_Plague_Strike, false);
				player->learnSpell(Spell_Todesritter_Death_Grip, false);
				player->learnSpell(Spell_Todesritter_Raise_Dead, false);
				player->learnSpell(Spell_Todesritter_Death_and_Decay, false);
				player->learnSpell(Spell_Todesritter_Anti_Magic_Shell, false);
				player->learnSpell(Spell_Todesritter_Unholy_Presence, false);
				player->learnSpell(Spell_Todesritter_Raise_Ally, false);
				player->learnSpell(Spell_Todesritter_Army_of_the_Dead, false);
				player->learnSpell(Spell_Todesritter_Runeforging_skill, false);
				player->learnSpell(Spell_Todesritter_Acherus_Deathcharger, false);
				player->learnSpell(Spell_Todesritter_Obliterate, false);
				player->learnSpell(Spell_Todesritter_Death_Strike, false);
				player->learnSpell(Spell_Krieger_Dual_Wield, false);
				//================RuneForge================//
				player->learnSpell(Spell_Todesritter_Uknowas, false);
				player->learnSpell(Spell_Todesritter_Uknowah, false);
				player->learnSpell(Spell_Todesritter_Uknowai, false);
				player->learnSpell(Spell_Todesritter_Uknowaz, false);
				player->learnSpell(Spell_Todesritter_Uknowan, false);
				player->learnSpell(Spell_Todesritter_Uknowab, false);
				player->learnSpell(Spell_Todesritter_Uknowav, false);
				player->learnSpell(Spell_Todesritter_Uknowaj, false);
				player->learnSpell(Spell_Todesritter_Uknowaq, false);
				///////////WEAPON/////////////
				player->learnSpell(750, false);
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(200, false);
				player->learnSpell(201, false);
				player->learnSpell(202, false);
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================SHAMAN=================================================//
			case MENU_SHAMAN:
				player->learnSpell(8737, false);//?
				player->learnSpell(Spell_Schamane_Earth_Elemental_Totem, false);
				player->learnSpell(Spell_Schamane_Healing_Wave, false);
				player->learnSpell(Spell_Schamane_Lightning_Bolt, false);
				player->learnSpell(Spell_Schamane_Rockbiter_Weapon, false);
				player->learnSpell(Spell_Schamane_Earth_Shock, false);
				player->learnSpell(Spell_Schamane_Stoneskin_Totem, false);
				player->learnSpell(Spell_Schamane_Earthbind_Totem, false);
				player->learnSpell(Spell_Schamane_Lightning_Shield, false);
				player->learnSpell(Spell_Schamane_Stoneclaw_Totem, false);
				player->learnSpell(Spell_Schamane_Flame_Shock, false);
				player->learnSpell(Spell_Schamane_Flametongue_Weapon, false);
				player->learnSpell(Spell_Schamane_Searing_Totem, false);
				player->learnSpell(Spell_Schamane_Strength_of_Earth_Totem, false);
				player->learnSpell(Spell_Schamane_Ancestral_Spirit, false);
				player->learnSpell(Spell_Schamane_Fire_Nova, false);
				player->learnSpell(Spell_Schamane_Purge, false);
				player->learnSpell(Spell_Schamane_Cure_Toxins, false);
				player->learnSpell(Spell_Schamane_Ghost_Wolf, false);
				player->learnSpell(Spell_Schamane_Wind_Shear, false);
				player->learnSpell(Spell_Schamane_Tremor_Totem, false);
				player->learnSpell(Spell_Schamane_Frost_Shock, false);
				player->learnSpell(Spell_Schamane_Frostbrand_Weapon, false);
				player->learnSpell(Spell_Schamane_Healing_Stream_Totem, false);
				player->learnSpell(Spell_Schamane_Lesser_Healing_Wave, false);
				player->learnSpell(Spell_Schamane_Water_Shield, false);
				player->learnSpell(Spell_Schamane_Water_Breathing, false);
				player->learnSpell(Spell_Schamane_Frost_Resistance_Totem, false);
				player->learnSpell(Spell_Schamane_Far_Sight, false);
				player->learnSpell(Spell_Schamane_Magma_Totem, false);
				player->learnSpell(Spell_Schamane_Mana_Spring_Totem, false);
				player->learnSpell(Spell_Schamane_Fire_Resistance_Totem, false);
				player->learnSpell(Spell_Schamane_Flametongue_Totem, false);
				player->learnSpell(Spell_Schamane_Water_Walking, false);
				player->learnSpell(Spell_Schamane_Astral_Recall, false);
				player->learnSpell(Spell_Schamane_Call_of_the_Elements, false);
				player->learnSpell(Spell_Schamane_Earthliving_Weapon, false);
				player->learnSpell(Spell_Schamane_Grounding_Totem, false);
				player->learnSpell(Spell_Schamane_Nature_Resistance_Totem, false);
				player->learnSpell(Spell_Schamane_Reincarnation, false);
				player->learnSpell(Spell_Schamane_Totemic_Recall, false);
				player->learnSpell(Spell_Schamane_Windfury_Weapon, false);
				player->learnSpell(Spell_Schamane_Chain_Lightning, false);
				player->learnSpell(Spell_Schamane_Windfury_Totem, false);
				player->learnSpell(Spell_Schamane_Sentry_Totem, false);
				player->learnSpell(Spell_Schamane_Cleansing_Totem, false);
				player->learnSpell(Spell_Schamane_Call_of_the_Ancestors, false);
				player->learnSpell(Spell_Schamane_Chain_Heal, false);
				player->learnSpell(Spell_Schamane_Call_of_the_Spirits, false);
				player->learnSpell(Spell_Schamane_Wrath_of_Air_Totem, false);
				player->learnSpell(Spell_Schamane_Fire_Elemental_Totem, false);
				player->learnSpell(Spell_Schamane_Lava_Burst, false);
				player->learnSpell(Spell_Schamane_Hex, false);
				///////////WEAPONS/////////////
				player->learnSpell(8737, false);
				player->learnSpell(196, false);
				player->learnSpell(197, false);
				player->learnSpell(198, false);
				player->learnSpell(199, false);
				player->learnSpell(227, false);
				player->learnSpell(1180, false);
				player->learnSpell(15590, false);
				//Faction
				if (player->GetTeam() == ALLIANCE) {
					player->learnSpell(Spell_Schamane_Heroism, false);
				}
				else
				{
					player->learnSpell(Spell_Schamane_Bloodlust, false);
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================MAGE=================================================//
			case MENU_MAGE:
				player->learnSpell(Spell_Magier_Arcane_Explosion, false);
				player->learnSpell(Spell_Magier_Frostbolt, false);
				player->learnSpell(Spell_Magier_Arcane_Intellect, false);
				player->learnSpell(Spell_Magier_Fireball, false);
				player->learnSpell(Spell_Magier_Conjure_Water, false);
				player->learnSpell(Spell_Magier_Conjure_Food, false);
				player->learnSpell(Spell_Magier_Fire_Blast, false);
				player->learnSpell(Spell_Magier_Arcane_Missiles, false);
				player->learnSpell(Spell_Magier_Polymorph, false);
				player->learnSpell(Spell_Magier_Polymorph_Turtle, false);
				player->learnSpell(Spell_Magier_Polymorph_Turkey, false);
				player->learnSpell(Spell_Magier_Polymorph_Rabbit, false);
				player->learnSpell(Spell_Magier_Polymorph_Pig, false);
				player->learnSpell(Spell_Magier_Frost_Nova, false);
				player->learnSpell(Spell_Magier_Dampen_Magic, false);
				player->learnSpell(Spell_Magier_Slow_Fall, false);
				player->learnSpell(Spell_Magier_Flamestrike, false);
				player->learnSpell(Spell_Magier_Amplify_Magic, false);
				player->learnSpell(Spell_Magier_Remove_Curse, false);
				player->learnSpell(Spell_Magier_Blink, false);
				player->learnSpell(Spell_Magier_Blizzard, false);
				player->learnSpell(Spell_Magier_Evocation, false);
				player->learnSpell(Spell_Magier_Fire_Ward, false);
				player->learnSpell(Spell_Magier_Mana_Shield, false);
				player->learnSpell(Spell_Magier_Frost_Ward, false);
				player->learnSpell(Spell_Magier_Scorch, false);
				player->learnSpell(Spell_Magier_Counterspell, false);
				player->learnSpell(Spell_Magier_Cone_of_Cold, false);
				player->learnSpell(Spell_Magier_Conjure_Mana_Gem, false);
				player->learnSpell(Spell_Magier_Ice_Armor, false);
				player->learnSpell(Spell_Magier_Ice_Block, false);
				player->learnSpell(Spell_Magier_Mage_Armor, false);
				player->learnSpell(Spell_Magier_Arcane_Brilliance, false);
				player->learnSpell(Spell_Magier_Molten_Armor, false);
				player->learnSpell(Spell_Magier_Arcane_Blast, false);
				player->learnSpell(Spell_Magier_Ice_Lance, false);
				player->learnSpell(Spell_Magier_Invisibility, false);
				player->learnSpell(Spell_Magier_Ritual_of_Refreshment, false);
				player->learnSpell(Spell_Magier_Spellsteal, false);
				player->learnSpell(Spell_Magier_Conjure_Refreshment, false);
				player->learnSpell(Spell_Magier_Frostfire_Bolt, false);
				player->learnSpell(Spell_Magier_Dalaran_Brilliance, false);
				player->learnSpell(Spell_Magier_Dalaran_Intellect, false);
				player->learnSpell(Spell_Magier_Mirror_Image, false);
				player->learnSpell(Spell_Magier_Portal_Dalaran, false);
				player->learnSpell(Spell_Magier_Frost_Armor, false);
				player->learnSpell(61305, false);//?
				player->SaveToDB();
				/////////WEAPON/////////////
				player->learnSpell(201, false); //?
				player->learnSpell(196, false); //?
				player->learnSpell(227, false); //?
				player->learnSpell(1180, false); //?
				player->SaveToDB();
				/////////RESTRICTION/////////////
				if (player->GetTeam() == ALLIANCE) {
					player->learnSpell(Spell_Magier_Teleport_Exodar, false);
					player->learnSpell(Spell_Magier_Teleport_Theramore, false);
					player->learnSpell(Spell_Magier_Teleport_Darnassus, false);
					player->learnSpell(Spell_Magier_Teleport_Shattrath, false);
					player->learnSpell(Spell_Magier_Teleport_Ironforge, false);
					player->learnSpell(Spell_Magier_Teleport_Stromwind, false);
					player->learnSpell(Spell_Magier_Portal_Darnassus, false);
					player->learnSpell(Spell_Magier_Portal_Exodar, false);
					player->learnSpell(Spell_Magier_Portal_Ironforge, false);
					player->learnSpell(Spell_Magier_Portal_Shattrath, false);
					player->learnSpell(Spell_Magier_Portal_Theramore, false);
				}
				else {
					player->learnSpell(Spell_Magier_Teleport_Orgrimmar, false);
					player->learnSpell(Spell_Magier_Teleport_Shattrath_H, false);
					player->learnSpell(Spell_Magier_Teleport_Thunder_Bluff, false);
					player->learnSpell(Spell_Magier_Teleport_Stonard, false);
					player->learnSpell(Spell_Magier_Teleport_Silvermoon, false);
					player->learnSpell(Spell_Magier_Teleport_Undercity, false);
					player->learnSpell(Spell_Magier_Portal_Orgrimmar, false);
					player->learnSpell(Spell_Magier_Portal_Shattrath_H, false);
					player->learnSpell(Spell_Magier_Portal_Silvermoon, false);
					player->learnSpell(Spell_Magier_Portal_Stonard, false);
					player->learnSpell(Spell_Magier_Portal_Thunder_Bluff, false);
					player->learnSpell(Spell_Magier_Portal_Undercity, false);
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================WARLOCK=================================================//
			case MENU_WARLOCK:
				player->learnSpell(Spell_Hexenmeister_Demon_Skin, false);
				player->learnSpell(Spell_Hexenmeister_Immolate, false);
				player->learnSpell(Spell_Hexenmeister_Shadow_Bolt, false);
				player->learnSpell(Spell_Hexenmeister_Summon_Imp, false);
				player->learnSpell(Spell_Hexenmeister_Corruption, false);
				player->learnSpell(Spell_Hexenmeister_Curse_of_Weakness, false);
				player->learnSpell(Spell_Hexenmeister_Life_Tap, false);
				player->learnSpell(Spell_Hexenmeister_Curse_of_Agony, false);
				player->learnSpell(Spell_Hexenmeister_Fear, false);
				player->learnSpell(Spell_Hexenmeister_Create_Healthstone, false);
				player->learnSpell(Spell_Hexenmeister_Drain_Soul, false);
				player->learnSpell(Spell_Hexenmeister_Summon_Voidwalker, false);
				player->learnSpell(Spell_Hexenmeister_Health_Funnel, false);
				player->learnSpell(Spell_Hexenmeister_Drain_Life, false);
				player->learnSpell(Spell_Hexenmeister_Unending_Breath, false);
				player->learnSpell(Spell_Hexenmeister_Create_Soulstone, false);
				player->learnSpell(Spell_Hexenmeister_Searing_Pain, false);
				player->learnSpell(Spell_Hexenmeister_Demon_Armor, false);
				player->learnSpell(Spell_Hexenmeister_Rain_of_Fire, false);
				player->learnSpell(Spell_Hexenmeister_Ritual_of_Summoning, false);
				player->learnSpell(Spell_Hexenmeister_Summon_Succubus, false);
				player->learnSpell(Spell_Hexenmeister_Eye_of_Kilrogg, false);
				player->learnSpell(Spell_Hexenmeister_Drain_Mana, false);
				player->learnSpell(Spell_Hexenmeister_Sense_Demons, false);
				player->learnSpell(Spell_Hexenmeister_Curse_of_Tongues, false);
				player->learnSpell(Spell_Hexenmeister_Detect_Invisibility, false);
				player->learnSpell(Spell_Hexenmeister_Create_Firestone, false);
				player->learnSpell(Spell_Hexenmeister_Banish, false);
				player->learnSpell(Spell_Hexenmeister_Enslave_Demon, false);
				player->learnSpell(Spell_Hexenmeister_Hellfire, false);
				player->learnSpell(Spell_Hexenmeister_Summon_Felhunter, false);
				player->learnSpell(Spell_Hexenmeister_Curse_of_the_Elements, false);
				player->learnSpell(Spell_Hexenmeister_Shadow_Ward, false);
				player->learnSpell(Spell_Hexenmeister_Create_Spellstone, false);
				player->learnSpell(Spell_Hexenmeister_Howl_of_Terror, false);
				player->learnSpell(Spell_Hexenmeister_Death_Coil, false);
				player->learnSpell(Spell_Hexenmeister_Soul_Fire, false);
				player->learnSpell(Spell_Hexenmeister_Inferno, false);
				player->learnSpell(Spell_Hexenmeister_Curse_of_Doom, false);
				player->learnSpell(Spell_Hexenmeister_Ritual_of_Doom, false);
				player->learnSpell(Spell_Hexenmeister_Fel_Armor, false);
				player->learnSpell(Spell_Hexenmeister_Incinerate, false);
				player->learnSpell(Spell_Hexenmeister_Soulshatter, false);
				player->learnSpell(Spell_Hexenmeister_Ritual_of_Souls, false);
				player->learnSpell(Spell_Hexenmeister_Seed_of_Corruption, false);
				player->learnSpell(Spell_Hexenmeister_Shadowflame, false);
				player->learnSpell(Spell_Hexenmeister_Demonic_Circle_Summon, false);
				player->learnSpell(Spell_Hexenmeister_Demonic_Circle_Teleport, false);
				player->learnSpell(Spell_Hexenmeister_Dreadsteed, false);
				player->learnSpell(33388, false); //?
				player->learnSpell(33391, false); //?
												  ///////////ARMES/////////////
				player->learnSpell(196, false);//?
				player->learnSpell(227, false);//?
				player->learnSpell(1180, false);//?
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;
				//=============================================DRUID=================================================//
			case MENU_DRUID:
				if (player->getClass() == CLASS_DRUID)
				{
					player->learnSpell(Spell_Druide_Healing_Touch, false);
					player->learnSpell(Spell_Druide_Mark_of_the_Wild, false);
					player->learnSpell(Spell_Druide_Wrath, false);
					player->learnSpell(Spell_Druide_Moonfire, false);
					player->learnSpell(Spell_Druide_Rejuvenation, false);
					player->learnSpell(Spell_Druide_Thorns, false);
					player->learnSpell(Spell_Druide_Entangling_Roots, false);
					player->learnSpell(Spell_Druide_Bear_Form, false);
					player->learnSpell(Spell_Druide_Demoralizing_Roar, false);
					player->learnSpell(Spell_Druide_Growl, false);
					player->learnSpell(Spell_Druide_Maul, false);
					player->learnSpell(Spell_Druide_Natures_Grasp, false);
					player->learnSpell(Spell_Druide_Teleport_Moonglade, false);
					player->learnSpell(Spell_Druide_Enrage, false);
					player->learnSpell(Spell_Druide_Regrowth, false);
					player->learnSpell(Spell_Druide_Revive, false);
					player->learnSpell(Spell_Druide_Bash, false);
					player->learnSpell(Spell_Druide_Cure_Poison, false);
					player->learnSpell(Spell_Druide_Aquatic_Form, false);
					player->learnSpell(Spell_Druide_Swipe_Bear, false);
					player->learnSpell(Spell_Druide_Travel_Form, false);
					player->learnSpell(Spell_Druide_Faerie_Fire, false);
					player->learnSpell(Spell_Druide_Faerie_Fire_Feral, false);
					player->learnSpell(Spell_Druide_Hibernate, false);
					player->learnSpell(Spell_Druide_Cat_Form, false);
					//	player->learnSpell(Spell_Druide_Feral_Charge_Bear, false); // charge farouche 2
					//	player->learnSpell(Spell_Druide_Feral_Charge_Cat, false); // charge farouche
					player->learnSpell(Spell_Druide_Prowl, false);
					player->learnSpell(Spell_Druide_Rebirth, false);
					player->learnSpell(Spell_Druide_Rip, false);
					player->learnSpell(Spell_Druide_Starfire, false);
					player->learnSpell(Spell_Druide_Shred, false);
					player->learnSpell(Spell_Druide_Soothe_Animal, false);
					player->learnSpell(Spell_Druide_Rake, false);
					player->learnSpell(Spell_Druide_Remove_Curse, false);
					player->learnSpell(Spell_Druide_Tigers_Fury, false);
					player->learnSpell(Spell_Druide_Abolish_Poison, false);
					player->learnSpell(Spell_Druide_Dash, false);
					player->learnSpell(Spell_Druide_Challenging_Roar, false);
					player->learnSpell(Spell_Druide_Cower, false);
					player->learnSpell(Spell_Druide_Tranquility, false);
					player->learnSpell(Spell_Druide_Ferocious_Bite, false);
					player->learnSpell(Spell_Druide_Ravage, false);
					player->learnSpell(Spell_Druide_Track_Humanoids, false);
					player->learnSpell(Spell_Druide_Frenzied_Regeneration, false);
					player->learnSpell(Spell_Druide_Pounce, false);
					player->learnSpell(Spell_Druide_Dire_Bear_Form, false);
					player->learnSpell(Spell_Druide_Feline_Grace, false);
					player->learnSpell(Spell_Druide_Hurricane, false);
					player->learnSpell(Spell_Druide_Innervate, false);
					player->learnSpell(Spell_Druide_Savage_Defense, false);
					player->learnSpell(Spell_Druide_Barkskin, false);
					player->learnSpell(Spell_Druide_Gift_of_the_Wild, false);
					//	player->learnSpell(Spell_Druide_Mangle_Bear, false); mutilation farouche 2
					//	player->learnSpell(Spell_Druide_Mangle_Cat, false); mutilation farouche
					player->learnSpell(Spell_Druide_Flight_Form, false);
					player->learnSpell(Spell_Druide_Maim, false);
					player->learnSpell(Spell_Druide_Lifebloom, false);
					player->learnSpell(Spell_Druide_Lacerate, false);
					player->learnSpell(Spell_Druide_Cyclone, false);
					player->learnSpell(Spell_Druide_Swift_Flight_Form, false);
					player->learnSpell(Spell_Druide_Swipe_Cat, false);
					player->learnSpell(Spell_Druide_Savage_Roar, false);
					player->learnSpell(Spell_Druide_Nourish, false);
					player->learnSpell(Spell_Druide_Claw, false);
					player->learnSpell(Spell_Druide_Claw_1, false);//?
																  ///////////ARMES/////////////
					player->learnSpell(198, false); //?
					player->learnSpell(199, false); // ?
					player->learnSpell(200, false); //?
					player->learnSpell(227, false); //?
					player->SaveToDB();
				}
				player->UpdateSkillsToMaxSkillsForLevel();
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case OPTION_MENU_ID_1:
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, SUB_MENU_TALENT_OPTION_1, GOSSIP_SENDER_MAIN, SUB_OPTION_MENU_ID_1);
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, SUB_MENU_TALENT_OPTION_2, GOSSIP_SENDER_MAIN, SUB_OPTION_MENU_ID_2);
				player->ADD_GOSSIP_ITEM(CHAT_ICON, back, GOSSIP_SENDER_MAIN, BACK_OPTION_MENU_1);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case SUB_OPTION_MENU_ID_1:
				//=====WARRIOR TALENT=====//
				//Arms
				if (player->HasSpell(12294)) //Mortal Strike Rank 1 
				{
					player->learnSpell(Spell_Krieger_Mortal_Strike, false);
				}
				//Prot
				if (player->HasSpell(20243)) //Devastate Rank 1
				{
					player->learnSpell(Spell_Krieger_Devastate, false);
				}
				//=====PALADIN TALENT=====//
				//Holy
				if (player->HasSpell(20925)) //Holy Shield Rank 1
				{
					player->learnSpell(Spell_Paladin_Holy_Shield, false);
				}
				if (player->HasSpell(20473)) //Holy Shock Rank 1
				{
					player->learnSpell(Spell_Paladin_Holy_Shock, false);
				}
				//Prot
				if (player->HasSpell(31935)) //Avengers Shield Rank 1
				{
					player->learnSpell(Spell_Paladin_Avengers_Shield, false);
				}
				if (player->HasSpell(20911)) //Blessing of Sanctuary Rank 1
				{
					player->learnSpell(Spell_Paladin_Greater_Blessing_of_Sanctuary, false);
				}
				//=====HUNTER  TALENT=====//
				//Survival
				if (player->HasSpell(19386)) //Wyvern String Rank 1
				{
					player->learnSpell(Spell_Jaeger_Wyvern_Sting, false);
				}
				if (player->HasSpell(53301)) //Explosive Shot Rank 1
				{
					player->learnSpell(Spell_Jaeger_Explosive_Shot, false);
				}
				if (player->HasSpell(19306)) //Conter Attack Rank 1
				{
					player->learnSpell(Spell_Jaeger_Conterattack, false);
				}
				//Marksmanship
				if (player->HasSpell(19434)) //Aimed Shot Rank 1
				{
					player->learnSpell(Spell_Jaeger_Aimed_Shot, false);
				}
				//=====ROGUE   TALENT=====//
				//Subtlety
				if (player->HasSpell(16511)) //Hemorrhage Rank 1
				{
					player->learnSpell(Spell_Schurke_Hemorrhage, false);
				}
				//Assassination
				if (player->HasSpell(1329)) //Mutilate Rank 1
				{
					player->learnSpell(Spell_Schurke_Mutilate, false);
				}
				//=====PRIEST  TALENT=====//
				//Shadow
				if (player->HasSpell(34914)) //Vampiric Touch Rank 1
				{
					player->learnSpell(Spell_Priester_Vampiric_Touch, false);
				}
				//Discipline
				if (player->HasSpell(47540)) //Penance Rank 1
				{
					player->learnSpell(Spell_Priester_Penance, false);
				}
				//Holy
				if (player->HasSpell(724)) //LightWell Rank 1
				{
					player->learnSpell(Spell_Priester_Lightwell, false);
				}
				if (player->HasSpell(19236)) //Desperate Prayer Rank 1
				{
					player->learnSpell(Spell_Priester_Desperate_Prayer, false);
				}
				if (player->HasSpell(34861)) //Circle Of healing Rank 1
				{
					player->learnSpell(Spell_Priester_Circle_of_Healing, false);
				}
				//Shadow
				if (player->HasSpell(15407)) //Mind Flay Rank 1
				{
					player->learnSpell(Spell_Priester_Mind_Flay, false);
				}
				//=====DEATH_K TALENT=====//
				//Blood
				if (player->HasSpell(55050)) //Heart Strike Rank 1
				{
					player->learnSpell(Spell_Todesritter_Heart_Strike, false);
				}
				//Frost
				if (player->HasSpell(49143)) //Frost Strike Rank 1
				{
					player->learnSpell(Spell_Todesritter_Frost_Strike, false);
				}
				if (player->HasSpell(49184)) //Howling Blast Rank 1
				{
					player->learnSpell(Spell_Todesritter_Howling_Blast, false);
				}
				//UnHoly
				if (player->HasSpell(55090)) //Scourge Strike Rank 1
				{
					player->learnSpell(Spell_Todesritter_Scourge_Strike, false);
				}
				if (player->HasSpell(49158)) //Corpse Explosion Rank 1
				{
					player->learnSpell(Spell_Todesritter_Corpse_Explosion, false);
				}
				//=====SHAMAN  TALENT=====//
				//Restoration
				if (player->HasSpell(61295)) //Riptide Rank 1
				{
					player->learnSpell(Spell_Schamane_Riptide, false);
				}
				if (player->HasSpell(974)) //Earth Shield Rank 1
				{
					player->learnSpell(Spell_Schamane_Earth_Shield, false);
				}
				//Elemental
				if (player->HasSpell(30706)) //Totem of Wrath Rank 1
				{
					player->learnSpell(Spell_Schamane_Totem_of_Wrath, false);
				}
				if (player->HasSpell(51490)) //TunderStorm Rank 1
				{
					player->learnSpell(Spell_Schamane_Thunderstorm, false);
				}
				//=====MAGE    TALENT=====//
				//Arcane
				if (player->HasSpell(44425)) //Arcane Barrage Rank 1
				{
					player->learnSpell(Spell_Magier_Arcane_Barrage, false);
				}
				//Fire
				if (player->HasSpell(11113)) //Blast Wave Rank 1
				{
					player->learnSpell(Spell_Magier_Blast_Wave, false);
				}
				if (player->HasSpell(31661)) //Dragon Breath  Rank 1
				{
					player->learnSpell(Spell_Magier_Dragons_Breath, false);
				}
				if (player->HasSpell(44457)) //Living Bomb Rank 1
				{
					player->learnSpell(Spell_Magier_Living_Bomb, false);
				}
				if (player->HasSpell(11366)) //Pyroblast Rank 1
				{
					player->learnSpell(Spell_Magier_Pyroblast, false);
				}
				//Frost
				if (player->HasSpell(11426)) //Ice Barrier Rank 1
				{
					player->learnSpell(Spell_Magier_Ice_Barrier, false);
				}
				//=====WARLOCK TALENT=====//
				//Destruction
				if (player->HasSpell(17877)) //ShadowBurn Rank 1
				{
					player->learnSpell(Spell_Hexenmeister_Shadowburn, false);
				}
				if (player->HasSpell(30283)) //ShadowFury Rank 1
				{
					player->learnSpell(Spell_Hexenmeister_Shadowfury, false);
				}
				if (player->HasSpell(50796)) //Chaos Bolt Rank 1
				{
					player->learnSpell(Spell_Hexenmeister_Chaos_Bolt, false);
				}
				//Affliction
				if (player->HasSpell(30108)) //Unstable Affliction Rank 1
				{
					player->learnSpell(Spell_Hexenmeister_Unstable_Affliction, false);
				}
				if (player->HasSpell(48181)) //Spell Haunt Rank 1
				{
					player->learnSpell(Spell_Hexenmeister_Haunt, false);
				}
				if (player->HasSpell(18220)) //Dark Pact Rank 1
				{
					player->learnSpell(Spell_Hexenmeister_Dark_Pact, false);
				}
				//=====DRUID   TALENT=====//
				//Balance
				if (player->HasSpell(50516)) //Typhoon Rank 1
				{
					player->learnSpell(Spell_Druide_Typhoon, false);
				}
				if (player->HasSpell(48505)) //Starfall Rank 1
				{
					player->learnSpell(Spell_Druide_Starfall, false);
				}
				if (player->HasSpell(5570)) //Insect Swarm Rank 1
				{
					player->learnSpell(Spell_Druide_Insect_Swarm, false);
				}
				//Restoration
				if (player->HasSpell(48438)) //Wild Growth Rank 1
				{
					player->learnSpell(Spell_Druide_Wild_Growth, false);
				}
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case SUB_OPTION_MENU_ID_2:
				player->resetTalents(true);
				player->SendTalentsInfoData(false);
				player->MonsterTextEmote("Your talents has been reset!", 0, true);
				player->SaveToDB();
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case OPTION_MENU_ID_2:
				player->learnSpell(Zusatz_Reiten_Journeyman_Riding, false);
				player->learnSpell(Zusatz_Reiten_Cold_Weather_Flying, false);
				player->learnSpell(Zusatz_Reiten_Flight_Master_License, false);
				player->AddItem(Mount_Invincibles_Reins, 1); //Flying-Ground
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case OPTION_MENU_ID_3:
				if (player->getClass() == CLASS_WARRIOR)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_WARRIOR);
				}
				if (player->getClass() == CLASS_PALADIN)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_PALADIN);
				}
				if (player->getClass() == CLASS_MAGE)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_MAGE);
				}
				if (player->getClass() == CLASS_HUNTER)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_HUNTER);
				}
				if (player->getClass() == CLASS_DRUID)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_DRUID);
				}
				if (player->getClass() == CLASS_WARLOCK)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_WARLOCK);
				}
				if (player->getClass() == CLASS_PRIEST)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_PRIEST);
				}
				if (player->getClass() == CLASS_ROGUE)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_ROGUE);
				}
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_DK);
				}
				if (player->getClass() == CLASS_SHAMAN)
				{
					PGS->SendListInventory(creature->GetGUID(), GLYPH_NPC_ID_SHAMAN);
				}
				break;


			case BACK_OPTION_MENU_1://Main Menu
				if (player->getLevel() >= 80)
				{
					{
						player->PrepareQuestMenu(creature->GetGUID());
						player->SendPreparedQuest(creature->GetGUID());
					}
					if (player->getClass() == CLASS_WARRIOR)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_WARRIOR);
					}
					if (player->getClass() == CLASS_PALADIN)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_PALADIN);
					}
					if (player->getClass() == CLASS_HUNTER)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_HUNTER);
					}
					if (player->getClass() == CLASS_ROGUE)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_ROGUE);
					}
					if (player->getClass() == CLASS_PRIEST)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_PRIEST);
					}
					if (player->getClass() == CLASS_DEATH_KNIGHT)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_DEATH_K);
					}
					if (player->getClass() == CLASS_SHAMAN)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_SHAMAN);
					}
					if (player->getClass() == CLASS_MAGE)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_MAGE);
					}
					if (player->getClass() == CLASS_WARLOCK)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_WARLOCK);
					}
					if (player->getClass() == CLASS_DRUID)
					{
						player->ADD_GOSSIP_ITEM(TRAINER_ICON, Class_Skills, GOSSIP_SENDER_MAIN, MENU_DRUID);
					}

					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Talent_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_1);
					player->ADD_GOSSIP_ITEM(TRAINER_ICON, Riding_Skills, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_2);
					player->ADD_GOSSIP_ITEM(VENDOR_ICON, Glyph_Menu, GOSSIP_SENDER_MAIN, OPTION_MENU_ID_3);
					player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				}
				else
				{
					player->PlayerTalkClass->SendCloseGossip();
					return false;
				}
				break;

			}
		}
		return true;
	}
};



void AddSC_npc_welcome()
{
	new npc_welcome();
}