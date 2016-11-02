	

    #include "ScriptPCH.h"
     
    #define COOLDOWN_DELAY  2*MINUTE
    #define CODE_LENGTH     16
     
    static std::list<std::string> cardKeys;
    static UNORDERED_MAP<uint32, time_t> cooldowns;
     
    static bool CheckKey(std::string str, Player* player = NULL)
    {
        if (str.empty() || str.length() != CODE_LENGTH || str.find_first_not_of("1234567890") != std::string::npos)
        {
            if (player)
                player->GetSession()->SendNotification("Invalid key inserted!");
            return false;
        }
        for (std::list<std::string>::const_iterator it = cardKeys.begin(); it != cardKeys.end(); ++it)
        {
            if ((*it) != str)
                continue;
            if (player)
                player->GetSession()->SendNotification("Key already used!");
            return false;
        }
        return true;
    }
     
    class paysafecardkey_receiver : public CreatureScript
    {
    public:
        paysafecardkey_receiver() : CreatureScript("paysafecardkey_receiver")
        {
        }
     
        bool OnGossipHello(Player* player, Creature* creature) OVERRIDE
        {
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Insert paysafecard key", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "Format: 1234567812345678", 0, true);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Nevermind..", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }
     
        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) OVERRIDE
        {
            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
     
        bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, char const* code) OVERRIDE
        {
            player->PlayerTalkClass->ClearMenus();
            if (sender == GOSSIP_SENDER_MAIN && action == GOSSIP_ACTION_INFO_DEF+1)
                Process(player, code);
            OnGossipHello(player, creature);
            return true;
        }
     
        void Process(Player* player, char const* code)
        {
            uint32 accId = player->GetSession()->GetAccountId();
            if (cooldowns.find(accId) != cooldowns.end())
            {
                double diff = difftime(cooldowns[accId], time(NULL));
                if (diff > 0)
                {
                    if (diff >= MINUTE)
                        player->GetSession()->SendNotification("You need to wait %u more minutes", uint32(ceil((diff-MINUTE/2)/MINUTE)));
                    else
                        player->GetSession()->SendNotification("You need to wait %u more seconds", uint32(ceil(diff)));
                    return;
                }
                cooldowns.erase(accId);
            }
            if (!CheckKey(code, player))
                return;
     
            // success
            cooldowns[accId] = time(NULL) + COOLDOWN_DELAY;
            cardKeys.push_front(code); // push back or front?
            LoginDatabase.PExecute("INSERT INTO paysafecardkeys (accId, paysafecardkey) VALUES (%u, \"%s\")", accId, code); // Note! Not instant!
            player->GetSession()->SendAreaTriggerMessage("Key succesfully used");  
        }
    };
     
    class paysafecardkey_loader : public WorldScript
    {
    public:
        paysafecardkey_loader() : WorldScript("paysafecardkey_loader")
        {
        }
     
        void OnStartup() OVERRIDE
        {
            QueryResult result = LoginDatabase.Query("SELECT DISTINCT paysafecardkey FROM paysafecardkeys");
            if (!result)
                return;
            do
            {
                std::string paysafecardkey = (*result)[0].GetString();
                if (!CheckKey(paysafecardkey))
                    continue;
                cardKeys.push_back(paysafecardkey);
            } while (result->NextRow());
        }
    };
     
    void AddSC_example_gossip_codebox()
    {
        new paysafecardkey_loader;
        new paysafecardkey_receiver;
    }