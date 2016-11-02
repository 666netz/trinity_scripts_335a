  #include "ScriptPCH.h"

    class VIP_NPC : public CreatureScript
    {
            public:
            VIP_NPC() : CreatureScript("VIP_NPC") { }

            bool OnGossipHello(Player * pPlayer, Creature * pCreature)
            {
                                       if (pPlayer->GetSession()->GetSecurity() >= SEC_MODERATOR)
                    {
										pPlayer->ADD_GOSSIP_ITEM(6, "VIP VENDOR", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
                                        }
                                        else
                                        {
										 pPlayer->ADD_GOSSIP_ITEM(6, "Bye", GOSSIP_SENDER_MAIN,1);
										}
                    pPlayer->PlayerTalkClass->SendGossipMenu(9452, pCreature->GetGUID());
                    return true;
                                    }

            bool OnGossipSelect(Player *player, Creature * m_creature, uint32 sender, uint32 action)
    {
                player->PlayerTalkClass->ClearMenus();
                                switch (action)
                                {
                                case GOSSIP_OPTION_VENDOR:
                player->GetSession()->SendListInventory(m_creature->GetGUID());
                                break;
                                case 1:
                                m_creature->MonsterWhisper("Why are you here?  You are not a VIP!", player -> GetGUID());
								player->TeleportTo(1, -8790.0000f, 828.411987f, 97.642998f, 0.567000f);//Change me!
                                player->CLOSE_GOSSIP_MENU();
                                break;
                        }
        return true;
    }
};

        void AddSC_VIP_NPC()
{
    new VIP_NPC();
}