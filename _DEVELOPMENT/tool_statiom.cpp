#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "WorldSession.h"

enum Auras
{
	Love_Hearts_Vis = 20372,
	Ghostly_Skull_Vis = 69663,
	Spheres_Vis = 56102,
	Shadowmourne_Vis = 72521,
	Purple_Mist_Vis = 39947,
	Headless_Horseman_Vis = 43184,
	Durak_Shield_Vis = 74621,
	Blood_Orb_Vis = 72100,
	Gas_Mask_Vis = 71947,
	Holy_Zone_Vis = 70571,
	Sacred_Shield_Vis = 70491,
	Well_Souls_Vis = 68855,
	Hunt_Mark_Vis = 64328,
	Sleep_Vis = 20373,
	Green_Glow_Vis = 20371,
	Red_Glow_Vis = 20370,
	Purple_Ball_Vis = 20369,
	Red_Skull_Vis = 20368,
	Lightening_Vis = 64785,
	Sardonite_Fog_Vis = 63096,
	White_Hole_Vis = 62348,
};

enum Tokens
{
	Customise_Token = 9991810, // SET ID OF TOKEN FOR PLAYERS TO USE TO CUSTOMISE, RACE, FACTION CHANGE
	VIP_Token = 9991811, // SET ID OF TOKEN FOR PLAYERS TO USE TO ACTIVATE VIP ACCOUNT
};

enum Morphs
{

	night_elf_male = 20318,
	night_elf_female = 37919,
	human_male = 19723,
	human_female = 19724,
	gnome_male = 20580,
	gnome_female = 20320,
	dwarf_male = 20317,
	dwarf_female = 37918,
	draenei_male = 37916,
	draenei_female = 20323,
	orc_male = 21267,
	orc_female = 20316,
	blood_elf_male = 20578,
	blood_elf_female = 20579,
	tauren_male = 20585,
	tauren_female = 37922,
	undead_male = 37923,
	undead_female = 37924,
	troll_male = 19124,
	troll_female = 19185,
	goblin_male = 20582,
	goblin_female = 20583,
	worgen_male = 37915,
	worgen_female = 37914,
	illidan = 27571,
	lich_king = 30721,
	pandarian_monk = 30414,
	mini_thor = 32670,
	lil_kt = 30507,
	lil_xt = 32031,
};

enum ArenaPointRequire
{				// AMOUNT OF AREN POINTS REQUIRED TO SHOW THE AURA MENUS
	Arena_Points_Required1 = 500,
	Arena_Points_Required2 = 1000,
	Arena_Points_Required3 = 1500,
	Arena_Points_Required4 = 2000,
};

enum Honor
{				// THE AMOUNT OF HONOR PLAYER REQUIRES TO HAVE THE AURA CAST ON THEM
				// THIS IS NOT CURRENTLY SETUP - TO SET THIS YOU WILL HAVE TO ADD THE "IF" STATMENTS BELOW TO THE LINES MENTIONED.

	Honour_Amount1 = 5000,
	Honour_Amount2 = 10000,
	Honour_Amount3 = 15000,
	Honour_Amount4 = 20000,
};

class Tool_Station : public ItemScript
{
public:
	Tool_Station() : ItemScript("Tool_Station") { }

	uint32 GetTotalHonorPoints(Player* player)
	{
		QueryResult result = CharacterDatabase.PQuery("SELECT totalHonorPoints FROM characters WHERE guid = %u", player->GetGUID());
		if (result)
		{
			Field* field = result->Fetch();
			if (field)
				return field[0].GetUInt32();
		}
		return NULL;
	}

	uint32 GetTotalArenaPoints(Player* player)
	{
		QueryResult result = CharacterDatabase.PQuery("SELECT totalArenaPoints FROM characters WHERE guid = %u", player->GetGUID());
		if (result)
		{
			Field* field = result->Fetch();
			if (field)
				return field[0].GetUInt32();
		}
		return NULL;
	}

	bool OnUse(Player* Player, Item* Item, SpellCastTargets const& targets) override
	{
		Player->ADD_GOSSIP_ITEM(3, "Player Buff's", GOSSIP_SENDER_MAIN, 1);
		Player->ADD_GOSSIP_ITEM(3, "Player Tools", GOSSIP_SENDER_MAIN, 2);
		Player->ADD_GOSSIP_ITEM(3, "Morphs", GOSSIP_SENDER_MAIN, 3);
		Player->ADD_GOSSIP_ITEM(3, "Auras (Require Honor To See Menus)", GOSSIP_SENDER_MAIN, 4);
		return true;
	}
	void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
	{
		WorldSession* ws = player->GetSession();
		switch (action)
		{
		case 1: // Player Buffs
		{
			player->ADD_GOSSIP_ITEM(2, "Buffs With Blessing Of Kings", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(2, "Buffs With Blessing Of Might", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(2, "Buffs With Blessing Of Wisdom", GOSSIP_SENDER_MAIN, 7);
		}
		break;

		case 2: // Player Tools
		{
			player->ADD_GOSSIP_ITEM(2, "Heal Me", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(2, "Remove Ress Sickness", GOSSIP_SENDER_MAIN, 9);
			player->ADD_GOSSIP_ITEM(2, "Remove Deserter", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(2, "Repair Items", GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(2, "Clear Combat", GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(2, "Max Skills", GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(2, "Customize Charecter / Name Change", GOSSIP_SENDER_MAIN, 14);
			player->ADD_GOSSIP_ITEM(2, "Race Change", GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(2, "Faction Change", GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(2, "I Have A ViP Token", GOSSIP_SENDER_MAIN, 17);
		}
		break;

		case 3: // Morphs
		{
			player->ADD_GOSSIP_ITEM(4, "Horde Racial Morphs", GOSSIP_SENDER_MAIN, 18);
			player->ADD_GOSSIP_ITEM(4, "Alliance Racial Morphs", GOSSIP_SENDER_MAIN, 19);
			player->ADD_GOSSIP_ITEM(4, "Other Morphs", GOSSIP_SENDER_MAIN, 20);
			player->ADD_GOSSIP_ITEM(4, "Demorph", GOSSIP_SENDER_MAIN, 21);
		}
		break;

		case 4: // Aura's
			if (player->GetArenaPoints() >= Arena_Points_Required1)
			{
				player->ADD_GOSSIP_ITEM(4, "Sleep Visual", GOSSIP_SENDER_MAIN, 22);
				player->ADD_GOSSIP_ITEM(4, "Love Hearts Visual", GOSSIP_SENDER_MAIN, 23);
				player->ADD_GOSSIP_ITEM(4, "Hunters Mark Visual", GOSSIP_SENDER_MAIN, 24);
				player->ADD_GOSSIP_ITEM(4, "Red Skull Visual", GOSSIP_SENDER_MAIN, 25);
				player->ADD_GOSSIP_ITEM(4, "Ghostly Skull Visual", GOSSIP_SENDER_MAIN, 26);
				player->ADD_GOSSIP_ITEM(4, "Remove Auras", GOSSIP_SENDER_MAIN, 72);
			}

			if (player->GetArenaPoints() >= Arena_Points_Required2)
			{
				player->ADD_GOSSIP_ITEM(4, "Gas Mask Visual", GOSSIP_SENDER_MAIN, 27);
				player->ADD_GOSSIP_ITEM(4, "White Hole Visual", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(4, "Green Glow Visual", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(4, "Red Glow Visual", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(4, "Headless Horseman Visual", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(4, "Remove Auras", GOSSIP_SENDER_MAIN, 72);
			}

			if (player->GetArenaPoints() >= Arena_Points_Required3)
			{
				player->ADD_GOSSIP_ITEM(4, "Holy Zone Visual", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(4, "Sacred Shield Visual", GOSSIP_SENDER_MAIN, 33);
				player->ADD_GOSSIP_ITEM(4, "Sphere Visual", GOSSIP_SENDER_MAIN, 34);
				player->ADD_GOSSIP_ITEM(4, "Lightening Visual", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(4, "Sardonite Fog Visual", GOSSIP_SENDER_MAIN, 36);
				player->ADD_GOSSIP_ITEM(4, "Remove Auras", GOSSIP_SENDER_MAIN, 72);
			}

			if (player->GetArenaPoints() >= Arena_Points_Required4)
			{
				player->ADD_GOSSIP_ITEM(4, "Durak Shield Visual", GOSSIP_SENDER_MAIN, 37);
				player->ADD_GOSSIP_ITEM(4, "Blood Orb Visual", GOSSIP_SENDER_MAIN, 38);
				player->ADD_GOSSIP_ITEM(4, "Purple Ball Visual", GOSSIP_SENDER_MAIN, 39);
				player->ADD_GOSSIP_ITEM(4, "Purple Mist Visual", GOSSIP_SENDER_MAIN, 40);
				player->ADD_GOSSIP_ITEM(4, "Shadowmourne Visual", GOSSIP_SENDER_MAIN, 41);
				player->ADD_GOSSIP_ITEM(4, "Well Of Souls Visual", GOSSIP_SENDER_MAIN, 42);
				player->ADD_GOSSIP_ITEM(4, "Remove Auras", GOSSIP_SENDER_MAIN, 72);
			}
			break;

		case 5: // Buffs with Kings
		{
			player->CastSpell(player, 48469, true); // Mark Wild
			player->CastSpell(player, 58054, true); // Kings
			player->CastSpell(player, 42995, true); // Arcane Intel
			player->CastSpell(player, 48161, true); // Power Word
			player->CastSpell(player, 48169, true); // Shad Pro
			player->CastSpell(player, 48073, true); // Devine Spirit
			ws->SendNotification("You have been buffed, Please enjoy your buffs!!");
		}
		break;

		case 6: // Buffs with Might
		{
			player->CastSpell(player, 48469, true); // Mark Wild
			player->CastSpell(player, 48932, true); // Might
			player->CastSpell(player, 42995, true); // Arcane Intel
			player->CastSpell(player, 48161, true); // Power Word
			player->CastSpell(player, 48169, true); // Shad Pro
			player->CastSpell(player, 48073, true); // Devine Spirit
			ws->SendNotification("You have been buffed, Please enjoy your buffs!!");
		}
		break;

		case 7: // Buffs with Wisdom
		{
			player->CastSpell(player, 48469, true); // Mark Wild
			player->CastSpell(player, 48936, true); // Wisdom
			player->CastSpell(player, 42995, true); // Arcane Intel
			player->CastSpell(player, 48161, true); // Power Word
			player->CastSpell(player, 48169, true); // Shad Pro
			player->CastSpell(player, 48073, true); // Devine Spirit
			ws->SendNotification("You have been buffed, Please enjoy your buffs!!");
		}
		break;

		case 8: // Heal Me
			if (player->IsInCombat())
			{
				ws->SendNotification("You are in combat");
			}
			else
			{
				player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
				ws->SendNotification("You have been healed!");

			}
			break;

		case 9: // Remove Ressurection
			if (player->HasAura(26013))
			{
				player->RemoveAura(26013);
				ws->SendNotification("Ressurection Sickness has been removed");
			}
			else
			{
				ws->SendNotification("You are currently not suffering from Ressurection Sickness");

			}
			break;

		case 10: // Remove Deserter
			if (player->HasAura(15007))
			{
				player->RemoveAura(15007);
				ws->SendNotification("Deserter has been removed");
			}
			else
			{
				ws->SendNotification("You are currently not a deserter");

			}
			break;

		case 11: // Repair Items
		{
			player->DurabilityRepairAll(false, 0.0f, true);
			ws->SendNotification("I repaired all your items, including items from bank.");

		}
		break;

		case 12: // Clear Combat
			if (!player->duel) // Checks if a player is in a duel or not.
			{
				ws->SendNotification("You're in a duel! You can not use this!!");
			}
			else
			{
				player->ClearInCombat();
				ws->SendNotification("I have cleared your combat");

			}
			break;

		case 13: // Max Skills
		{
			player->UpdateSkillsToMaxSkillsForLevel();
			ws->SendNotification("Your skills have been advanced to maximum level.");

		}
		break;

		case 14: // Customise and Name Change
			if (player->HasItemCount(Customise_Token, 1))
			{
				player->DestroyItemCount(Customise_Token, 1, true, false);
				player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
				ws->SendNotification("You need to relog, to customize!");
			}
			else
			{
				ws->SendNotification("You require a change token!");
			}
			break;

		case 15: // Race Change
			if (player->HasItemCount(Customise_Token, 1))
			{
				player->DestroyItemCount(Customise_Token, 1, true, false);
				player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
				ws->SendNotification("You need to relog, to change your race!");
			}
			else
			{
				ws->SendNotification("You require a change token!");
			}
			break;

		case 16: // Faction Change
			if (player->HasItemCount(Customise_Token, 1))
			{
				player->DestroyItemCount(Customise_Token, 1, true, false);
				player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
				ws->SendNotification("You need to relog, to change your faction!");
			}
			else
			{
				ws->SendNotification("You require a change token!");
			}
			break;

		case 17: // ViP Token
			if (player->HasItemCount(VIP_Token, 1, false))
			{
				player->DestroyItemCount(VIP_Token, 1, true, false);
				LoginDatabase.PExecute("INSERT INTO account_access VALUES('%u', '1', '1')", player->GetSession()->GetAccountId());
				LoginDatabase.PExecute("INSERT INTO rbac_account_permissions VALUES('%u', '194', '1', '-1')", player->GetSession()->GetAccountId());
				ws->SendNotification("You will need to relog to gain your VIP account");
				player->SaveToDB();
			}
			else
			{
				ws->SendNotification("You do not have a VIP Token so I can not grant you VIP Status");
			}
			break;

		case 18: // Horde Morphs
		{
			player->ADD_GOSSIP_ITEM(4, "Orc Male", GOSSIP_SENDER_MAIN, 43);
			player->ADD_GOSSIP_ITEM(4, "Orc Female", GOSSIP_SENDER_MAIN, 44);
			player->ADD_GOSSIP_ITEM(4, "Troll Male", GOSSIP_SENDER_MAIN, 45);
			player->ADD_GOSSIP_ITEM(4, "Troll Female", GOSSIP_SENDER_MAIN, 46);
			player->ADD_GOSSIP_ITEM(4, "Tauren Male", GOSSIP_SENDER_MAIN, 47);
			player->ADD_GOSSIP_ITEM(4, "Tauren Female", GOSSIP_SENDER_MAIN, 48);
			player->ADD_GOSSIP_ITEM(4, "Undead Male", GOSSIP_SENDER_MAIN, 49);
			player->ADD_GOSSIP_ITEM(4, "Undead Female", GOSSIP_SENDER_MAIN, 50);
			player->ADD_GOSSIP_ITEM(4, "Blood Elf Male", GOSSIP_SENDER_MAIN, 51);
			player->ADD_GOSSIP_ITEM(4, "Blood Elf Female", GOSSIP_SENDER_MAIN, 52);
		}
		break;

		case 19: // Alliance Morphs
		{
			player->ADD_GOSSIP_ITEM(4, "Human Male", GOSSIP_SENDER_MAIN, 53);
			player->ADD_GOSSIP_ITEM(4, "Human Female", GOSSIP_SENDER_MAIN, 54);
			player->ADD_GOSSIP_ITEM(4, "Night Elf Male", GOSSIP_SENDER_MAIN, 55);
			player->ADD_GOSSIP_ITEM(4, "Night Elf Female", GOSSIP_SENDER_MAIN, 56);
			player->ADD_GOSSIP_ITEM(4, "Gnome Male", GOSSIP_SENDER_MAIN, 57);
			player->ADD_GOSSIP_ITEM(4, "Gnome Female", GOSSIP_SENDER_MAIN, 58);
			player->ADD_GOSSIP_ITEM(4, "Dreneai Male", GOSSIP_SENDER_MAIN, 59);
			player->ADD_GOSSIP_ITEM(4, "Dreneai Female", GOSSIP_SENDER_MAIN, 60);
			player->ADD_GOSSIP_ITEM(4, "Dwarf Male", GOSSIP_SENDER_MAIN, 61);
			player->ADD_GOSSIP_ITEM(4, "Dwarf Female", GOSSIP_SENDER_MAIN, 62);
		}
		break;

		case 20: // Other Morphs
		{
			player->ADD_GOSSIP_ITEM(4, "Illidan", GOSSIP_SENDER_MAIN, 63);
			player->ADD_GOSSIP_ITEM(4, "Lich King", GOSSIP_SENDER_MAIN, 64);
			player->ADD_GOSSIP_ITEM(4, "Worgen Male", GOSSIP_SENDER_MAIN, 65);
			player->ADD_GOSSIP_ITEM(4, "Worgen Female", GOSSIP_SENDER_MAIN, 66);
			player->ADD_GOSSIP_ITEM(4, "Goblin Male", GOSSIP_SENDER_MAIN, 67);
			player->ADD_GOSSIP_ITEM(4, "Goblin Female", GOSSIP_SENDER_MAIN, 68);
			player->ADD_GOSSIP_ITEM(4, "Pandarian Monk", GOSSIP_SENDER_MAIN, 69);
			player->ADD_GOSSIP_ITEM(4, "Lil KT", GOSSIP_SENDER_MAIN, 70);
			player->ADD_GOSSIP_ITEM(4, "Mini Thor", GOSSIP_SENDER_MAIN, 71);
		}
		break;

		case 21: // Demorph
		{
			player->DeMorph();
		}
		break;

		// ------------------ Visual Aura's -----------------------

		case 22: // Sleep Visual
		{
			player->AddAura(Sleep_Vis, player);
		}
		break;
		case 23: // Love Hearts Visual
			if (player->GetHonorPoints() >= Honour_Amount1)
			{
				player->AddAura(Love_Hearts_Vis, player);
			}
			break;
		case 24: // Hunters Mark Visual
			if (player->GetHonorPoints() >= Honour_Amount1)
			{
				player->AddAura(Hunt_Mark_Vis, player);
			}
			break;
		case 25: // Red Skull Visual
			if (player->GetHonorPoints() >= Honour_Amount1)
			{
				player->AddAura(Red_Skull_Vis, player);
			}
			break;
		case 26: // Ghostly Skull Visual
			if (player->GetHonorPoints() >= Honour_Amount1)
			{
				player->AddAura(Ghostly_Skull_Vis, player);
			}
			break;
		case 27: // Gas Mask Visual
			if (player->GetHonorPoints() >= Honour_Amount2)
			{
				player->AddAura(Gas_Mask_Vis, player);
			}
			break;
		case 28: // White Hole Visual
			if (player->GetHonorPoints() >= Honour_Amount2)
			{
				player->AddAura(White_Hole_Vis, player);
			}
			break;
		case 29: // Green Glow Visual
			if (player->GetHonorPoints() >= Honour_Amount2)
			{
				player->AddAura(Green_Glow_Vis, player);
			}
			break;
		case 30: // Red Glow Visual
			if (player->GetHonorPoints() >= Honour_Amount2)
			{
				player->AddAura(Red_Glow_Vis, player);
			}
			break;
		case 31: // Headless Horseman Visual
			if (player->GetHonorPoints() >= Honour_Amount2)
			{
				player->AddAura(Headless_Horseman_Vis, player);
			}
			break;
		case 32: // Holy Zone Visual
			if (player->GetHonorPoints() >= Honour_Amount3)
			{
				player->AddAura(Holy_Zone_Vis, player);
			}
			break;
		case 33: // Sacred Shield Visual
			if (player->GetHonorPoints() >= Honour_Amount3)
			{
				player->AddAura(Sacred_Shield_Vis, player);
			}
			break;
		case 34: // Sphere Visual
			if (player->GetHonorPoints() >= Honour_Amount3)
			{
				player->AddAura(Spheres_Vis, player);
			}
			break;
		case 35: // Lightening Visual
			if (player->GetHonorPoints() >= Honour_Amount3)
			{
				player->AddAura(Lightening_Vis, player);
			}
			break;
		case 36: // Sardonite Fog Visual
			if (player->GetHonorPoints() >= Honour_Amount3)
			{
				player->AddAura(Sardonite_Fog_Vis, player);
			}
			break;
		case 37: // Durak Shield Visual
			if (player->GetHonorPoints() >= Honour_Amount4)
			{
				player->AddAura(Durak_Shield_Vis, player);
			}
			break;
		case 38: // Blood Orb Visual
			if (player->GetHonorPoints() >= Honour_Amount4)
			{
				player->AddAura(Blood_Orb_Vis, player);
			}
			break;
		case 39: // Purple Ball Visual
			if (player->GetHonorPoints() >= Honour_Amount4)
			{
				player->AddAura(Purple_Ball_Vis, player);
			}
			break;
		case 40: // Purple Mist Visual
			if (player->GetHonorPoints() >= Honour_Amount4)
			{
				player->AddAura(Purple_Mist_Vis, player);
			}
			break;
		case 41: // Shadowmourne Visual
			if (player->GetHonorPoints() >= Honour_Amount4)
			{
				player->AddAura(Shadowmourne_Vis, player);
			}
			break;
		case 42: // Well Of Souls Visual
			if (player->GetHonorPoints() >= Honour_Amount4)
			{
				player->AddAura(Well_Souls_Vis, player);
			}
			break;

			// ----------------- Morphs --------------------------

		case 43: //	Orc Male
		{
			player->SetDisplayId(orc_male);
		}
		break;
		case 44: // Orc Female
		{
			player->SetDisplayId(orc_female);
		}
		break;
		case 45: // Troll Male
		{
			player->SetDisplayId(troll_male);
		}
		break;
		case 46: // Troll Female
		{
			player->SetDisplayId(troll_female);
		}
		break;
		case 47: // Tauren Male
		{
			player->SetDisplayId(tauren_male);
		}
		break;
		case 48: // Tauren Female
		{
			player->SetDisplayId(tauren_female);
		}
		break;
		case 49: // Undead Male
		{
			player->SetDisplayId(undead_male);
		}
		break;
		case 50: // Undead Female
		{
			player->SetDisplayId(undead_female);
		}
		break;
		case 51: // Blood Elf Male
		{
			player->SetDisplayId(blood_elf_male);
		}
		break;
		case 52: // Blood Elf Female
		{
			player->SetDisplayId(blood_elf_female);
		}
		break;
		case 53: // Human Male
		{
			player->SetDisplayId(human_male);
		}
		break;
		case 54: // Human Female
		{
			player->SetDisplayId(human_female);
		}
		break;
		case 55: // Night Elf Male
		{
			player->SetDisplayId(night_elf_male);
		}
		break;
		case 56: // Night Elf Female
		{
			player->SetDisplayId(night_elf_female);
		}
		break;
		case 57: // Gnome Male
		{
			player->SetDisplayId(gnome_male);
		}
		break;
		case 58: // Gnome Female
		{
			player->SetDisplayId(gnome_female);
		}
		break;
		case 59: // Dreneai Male
		{
			player->SetDisplayId(draenei_male);
		}
		break;
		case 60: // Dreneai Female
		{
			player->SetDisplayId(draenei_female);
		}
		break;
		case 61: // Dwarf Male
		{
			player->SetDisplayId(dwarf_male);
		}
		break;
		case 62: // Dwarf Female
		{
			player->SetDisplayId(dwarf_female);
		}
		break;
		case 63: // Illidan
		{
			player->SetDisplayId(illidan);
			ws->SendNotification("You were not prepared");
		}
		break;
		case 64: // Lich King
		{
			player->SetDisplayId(lich_king);
		}
		break;
		case 65: // Worgen Male
		{
			player->SetDisplayId(worgen_male);
		}
		break;
		case 66: // Worgen Female
		{
			player->SetDisplayId(worgen_female);
		}
		break;
		case 67: // Goblin Male
		{
			player->SetDisplayId(goblin_male);
		}
		break;
		case 68: // Goblin Female
		{
			player->SetDisplayId(goblin_female);
		}
		break;
		case 69: // Pandarian Monk
		{
			player->SetDisplayId(pandarian_monk);
			ws->SendNotification("Kung Fu Panda");
		}
		break;
		case 70: // Lil KT
		{
			player->SetDisplayId(lil_kt);
		}
		break;
		case 71: // Mini Thor
		{
			player->SetDisplayId(mini_thor);
			ws->SendNotification("Oh my you have guns!!");
		}
		break;
		case 72: // Remove Auras
		{
			player->RemoveAllAuras();
		}
		break;

		}
	}
};

void AddSC_Tool_Station()
{
	new Tool_Station();
}