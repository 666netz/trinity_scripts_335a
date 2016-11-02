#include "ScriptedPch.h"
#include "../../shared/Config/Config.h"
#ifndef _TRINITY_CORE_CONFIG
# define _TRINITY_CORE_CONFIG  "trinitycore.conf"
#endif _TRINITY_CORE_CONFIG

bool GossipHello_Npc_Buff(Player* pPlayer, Creature* pCreature)
{
	Config TScriptConfig;
	if(!TScriptConfig.SetSource(_TRINITY_CORE_CONFIG,true))
		error_log("TScript: Unable to open configuration file");

	if(TScriptConfig.GetBoolDefault("Npc_Buff.OnlyGMs", false)) // If Npc_Buff.OnlyGMs is enabled in trinitycore.conf
		if (pPlayer->GetSession()->GetSecurity() == SEC_PLAYER)
		{
			pCreature->MonsterWhisper("Sorry, I can only Buff game masters.", pPlayer->GetGUID());
			return true;
		}

	bool EnableSmallBuff = TScriptConfig.GetBoolDefault("Npc_Buff.EnableSmallBuff", true);
	bool EnableGreatBuff = TScriptConfig.GetBoolDefault("Npc_Buff.EnableGreatBuff", true);
	bool EnableGMBuff = TScriptConfig.GetBoolDefault("Npc_Buff.EnableGMBuff", true);
	bool EnablePlayerTools = TScriptConfig.GetBoolDefault("Npc_Buff.EnablePlayerTools", true);
	bool EnableResSickness = TScriptConfig.GetBoolDefault("Npc_Buff.EnableRemoveResSickness", true);
	bool EnableGivemeGold = TScriptConfig.GetBoolDefault("Npc_Buff.EnableGivemeGold", false);

	// Main Menu for Alliance
    if (pPlayer->GetTeam() == ALLIANCE)
	{
	// Check config if "Small  Buff " is enabled or not
	if(EnableSmallBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buff ->"              , GOSSIP_SENDER_MAIN, 1000);
	// Check config if "Great Buff" is enabled or not
	if(EnableGreatBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buff ->"              , GOSSIP_SENDER_MAIN, 2000);
	// Check config if "GM Buff" is enabled or not
	if(EnableGMBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buff ->"                 , GOSSIP_SENDER_MAIN, 3000);
	// Check config if "Player Tools" is enabled or not
	if(EnablePlayerTools)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
	}
	else // Main Menu for Horde
	{
	// Check config if "Small  Buff " is enabled or not
	if(EnableSmallBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buff ->"              , GOSSIP_SENDER_MAIN, 1000);
	// Check config if "Great Buff" is enabled or not
	if(EnableGreatBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buff ->"              , GOSSIP_SENDER_MAIN, 2000);
	// Check config if "GM Buff" is enabled or not
	if(EnableGMBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buff ->"                 , GOSSIP_SENDER_MAIN, 3000);
	// Check config if "Player Tools" is enabled or not
	if(EnablePlayerTools)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
	}

	// Check config file if "Remove res sickness" option is enabled or not
	if(EnableResSickness)
		pPlayer->ADD_GOSSIP_ITEM( 10, "Remove Resurrect Sickness" , GOSSIP_SENDER_MAIN, 5000);

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

return true;
}

void SendDefaultMenu_Npc_Buff(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

// Not allow in combat
if (pPlayer->isInCombat())
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
	return;
}

Config TScriptConfig;
if(!TScriptConfig.SetSource(_TRINITY_CORE_CONFIG,true))
		error_log("TScript: Unable to open configuration file");
	bool EnableSmallBuff = TScriptConfig.GetBoolDefault("Npc_Buff.EnableSmallBuff", true);
	bool EnableGreatBuff = TScriptConfig.GetBoolDefault("Npc_Buff.EnableGreatBuff", true);
	bool EnableGMBuff = TScriptConfig.GetBoolDefault("Npc_Buff.EnableGMBuff", true);
	bool EnablePlayerTools = TScriptConfig.GetBoolDefault("Npc_Buff.EnablePlayerTools", true);
	bool EnableResSickness = TScriptConfig.GetBoolDefault("Npc_Buff.EnableRemoveResSickness", true);
	bool EnableGivemeGold = TScriptConfig.GetBoolDefault("Npc_Buff.EnableGivemeGold", false);

//Money Check
if (pPlayer->GetMoney() < (TScriptConfig.GetFloatDefault("BuffGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterWhisper("You don't have enough money.", pPlayer->GetGUID());
	return;
}

switch(uiAction)
{

case 1000: //Small  Buff
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Mark of the Wild"                , GOSSIP_SENDER_MAIN, 1001);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Thorns"                          , GOSSIP_SENDER_MAIN, 1005);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Amplify Magic"                   , GOSSIP_SENDER_MAIN, 1010);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Arcane Intellect"                , GOSSIP_SENDER_MAIN, 1015);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Dalaran Intellect"               , GOSSIP_SENDER_MAIN, 1020);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Dampen Magic"                    , GOSSIP_SENDER_MAIN, 1025);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Blessing of Kings"               , GOSSIP_SENDER_MAIN, 1030);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Blessing of Might"               , GOSSIP_SENDER_MAIN, 1035);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Blessing of Wisdom"              , GOSSIP_SENDER_MAIN, 1040);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Divine Spirit"                   , GOSSIP_SENDER_MAIN, 1045);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Power Word: Fortitude"           , GOSSIP_SENDER_MAIN, 1050);
    	pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Shadow Protection"               , GOSSIP_SENDER_MAIN, 1055);
		pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

case 2000: //Great Buff
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Gift of the Wild"                , GOSSIP_SENDER_MAIN, 2001);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Arcane Brilliance"               , GOSSIP_SENDER_MAIN, 2005);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Dalaran Brilliance"              , GOSSIP_SENDER_MAIN, 2010);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Kings"       , GOSSIP_SENDER_MAIN, 2015);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Might"       , GOSSIP_SENDER_MAIN, 2020);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Sanctuary"   , GOSSIP_SENDER_MAIN, 2025);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Wisdom"      , GOSSIP_SENDER_MAIN, 2030);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Prayer of Fortitude"             , GOSSIP_SENDER_MAIN, 2035);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Prayer of Shadow Protection"     , GOSSIP_SENDER_MAIN, 2040);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Prayer of Spirit"                , GOSSIP_SENDER_MAIN, 2045);
		pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

case 3000: //GM  Buff
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Agamaggan's Agility"             , GOSSIP_SENDER_MAIN, 3001);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Agamaggan's Strength"            , GOSSIP_SENDER_MAIN, 3005);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Armor Magic"                     , GOSSIP_SENDER_MAIN, 3010);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Armor Penetration"               , GOSSIP_SENDER_MAIN, 3015);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Increased Stamina"               , GOSSIP_SENDER_MAIN, 3020);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Razorhide"                       , GOSSIP_SENDER_MAIN, 3025);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Rising Spirit"                   , GOSSIP_SENDER_MAIN, 3030);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Spirit of the Wind"              , GOSSIP_SENDER_MAIN, 3035);
    	pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Wisdom of Agamaggan"             , GOSSIP_SENDER_MAIN, 3040);
		pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

case 4000: //Player Tools
	// Check config if "Give me Gold" is enabled or not
	if(EnableGivemeGold)
		pPlayer->ADD_GOSSIP_ITEM( 5, "Give me Gold"                            , GOSSIP_SENDER_MAIN, 4001);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Give me Soul Shards"                     , GOSSIP_SENDER_MAIN, 4005);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Heal me Please"                          , GOSSIP_SENDER_MAIN, 4010);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Heal me and party members Please"        , GOSSIP_SENDER_MAIN, 4015);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Conjure Refreshment"                     , GOSSIP_SENDER_MAIN, 4020);
		pPlayer->ADD_GOSSIP_ITEM( 5, "Conjure Mana Gem"                        , GOSSIP_SENDER_MAIN, 4025);
		pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

case 5005: //Back To Main Menu
	// Main Menu for Alliance
    if (pPlayer->GetTeam() == ALLIANCE)
	{
	// Check config if "Small  Buff " is enabled or not
	if(EnableSmallBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buff ->"              , GOSSIP_SENDER_MAIN, 1000);
	// Check config if "Great Buff" is enabled or not
	if(EnableGreatBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buff ->"              , GOSSIP_SENDER_MAIN, 2000);
	// Check config if "GM Buff" is enabled or not
	if(EnableGMBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buff ->"                 , GOSSIP_SENDER_MAIN, 3000);
	// Check config if "Player Tools" is enabled or not
	if(EnablePlayerTools)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
	}
	else // Main Menu for Horde
	{
	// Check config if "Small  Buff " is enabled or not
	if(EnableSmallBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buff ->"              , GOSSIP_SENDER_MAIN, 1000);
	// Check config if "Great Buff" is enabled or not
	if(EnableGreatBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buff ->"              , GOSSIP_SENDER_MAIN, 2000);
	// Check config if "GM Buff" is enabled or not
	if(EnableGMBuff)
		pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buff ->"                 , GOSSIP_SENDER_MAIN, 3000);
	// Check config if "Player Tools" is enabled or not
	if(EnablePlayerTools)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
	}

	// Check if Ress Sickness option is enabled in scriptdev2.conf
	if(EnableResSickness)
		pPlayer->ADD_GOSSIP_ITEM( 10, "Remove Resurrect Sickness" , GOSSIP_SENDER_MAIN, 5000);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

//////////////////////////////////////////////////Small Buff///////////////////////////////////////////////////////////////

case 1001: // Buff me Mark of the Wild
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48469,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1005: // Buff me Thorns
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,53307,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1010: // Buff me Amplify Magic
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,43017,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1015: // Buff me Arcane Intellect
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,42995,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1020: // Buff me Dalaran Intellect
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,61024,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1025: // Buff me Dampen Magic
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,43015,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1030: // Buff me Blessing of Kings
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,20217,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1035: // Buff me Blessing of Might
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48932,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1040: // Buff me Blessing of Wisdom
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48936,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1045: // Buff me Divine Spirit
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48073,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1050: // Buff me Power Word: Fortitude
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48161,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 1055: // Buff me Shadow Protection
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48169,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

//////////////////////////////////////////////////Great Buff///////////////////////////////////////////////////////////////

case 2001: // Buff me Gift of the Wild
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,48470,true);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2005: // Buff me Arcane Brilliance
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,43002,true);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2010: // Buff me Dalaran Brilliance
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,61316,true);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2015: // Buff me Greater Blessing of Kings
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,25898,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2020: // Buff me Greater Blessing of Might
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48934,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2025: // Buff me Greater Blessing of Sanctuary
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,25899,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2030: // Buff me Greater Blessing of Wisdom
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,48938,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2035: // Buff me Prayer of Fortitude
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,48162,true);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2040: // Buff me Prayer of Shadow Protection
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,48170,true);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 2045: // Buff me Prayer of Spirit
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,48074,true);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

//////////////////////////////////////////////////GM Buff///////////////////////////////////////////////////////////////

case 3001: // Buff me Agamaggan's Agility
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,17013,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3005: // Buff me Agamaggan's Strength
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,16612,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3010: // Buff me Armor Magic
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,58453,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3015: // Buff me Armor Penetration
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,34106,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3020: // Buff me Increased Stamina
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,25661,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3025: // Buff me Razorhide
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,16610,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3030: // Buff me Rising Spirit
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,10767,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3035: // Buff me Spirit of the Wind
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,16618,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 3040: // Buff me Wisdom of Agamaggan
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,7764,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

//////////////////////////////////////////////////Player Tools///////////////////////////////////////////////////////////////

case 4001://Give me Gold
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,46642,false); // 5000 gold
break;

case 4005://Give me Soul Shards
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,24827,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 4010: // Heal me please
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->CastSpell(pPlayer,38588,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 4015: // Heal me and party members Please
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,53251,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 4020: // Conjure Refreshment
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,42956,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

case 4025: // Conjure Mana Gem
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,42985,false);
    pPlayer->ModifyMoney(-(TScriptConfig.GetFloatDefault("BuffGoldCost",0)));
break;

//case 5000://Remove Res Sickness
//	if(!pPlayer->HasAura(SPELL_RESURRECTION_SICKNESS_15007,0))
//	{
//		pCreature->MonsterWhisper("You don't have resurrection sickness.", pPlayer->GetGUID());
//		GossipHello_Npc_Buff(pPlayer, pCreature);
//		return;
//	}
//
//	pCreature->CastSpell(pPlayer,38588,false); // Healing effect
//	pPlayer->RemoveAurasDueToSpell(SPELL_RESURRECTION_SICKNESS_15007,0);
//	pPlayer->CLOSE_GOSSIP_MENU();
//break;

 pPlayer->CLOSE_GOSSIP_MENU();

} // end of switch
} //end of function



bool GossipSelect_Npc_Buff(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	// Main menu
	if (uiSender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_Npc_Buff(pPlayer, pCreature, uiAction);

return true;
}

void AddSC_Npc_Buff()
{
    Script *newscript;

	newscript = new Script;
    newscript->Name = "npc_buff";
    newscript->pGossipHello = &GossipHello_Npc_Buff;
    newscript->pGossipSelect = &GossipSelect_Npc_Buff;
    newscript->pItemHello = NULL;
    newscript->pGOHello = NULL;
    newscript->pAreaTrigger = NULL;
    newscript->pItemQuestAccept = NULL;
    newscript->pGOQuestAccept = NULL;
    newscript->pGOChooseReward = NULL;
    newscript->RegisterSelf();
}