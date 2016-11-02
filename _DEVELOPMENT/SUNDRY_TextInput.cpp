class npc_tut : public CreatureScript
{
public:
npc_tut() : CreatureScript("npc_tut") { } CreatureScript("npc_tut")

bool OnGossipHello(Player* player, Creature* creature) override
{
player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Input a word.", GOSSIP_SENDER_MAIN, 1, "YOU BETTER INSERT A WORD", 0, true);
player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Non-code input menu", 0, 2);
player->SEND_GOSSIP_MENU(1, creature->GetGUID());
return true;
}

// For non-code input menus
bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
{
player->PlayerTalkClass->ClearMenus();
if (actions == 2)
{
player->GetSession()->SendAreaTriggerMessage("Non-code input menu");
player->CLOSE_GOSSIP_MENU();
}
return true;
}

// For code input
// "code" parameter is what the player enters in the box
bool OnGossipSelectCode(Player* player, Creature* creature, uint32 /*sender*/, uint32 action, const char* code) override
{
player->PlayerTalkClass->ClearMenus();
if (actions == 1)
{
ChatHandler(player->GetSession()).PSendSysMessage("You input: %s", code);
player->CLOSE_GOSSIP_MENU();
}
return true;
}
};

void AddSC_tutorial() // This is your ScriptLoader.cpp setup function
{
new npc_tut; // Call any new classes here as 'new classname;'
}
