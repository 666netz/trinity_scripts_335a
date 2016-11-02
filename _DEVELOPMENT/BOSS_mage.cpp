#include "ScriptPCH.h"  

enum Spells  
{  
    MANA_BUBLE = 70842,  //phase 3 
    DEATH_DECAY = 72110, //timer 
    DARK_SIMULACRUM = 77616, //timer     
    BERSERKERZ = 26662,  //For noobs ;D 
    DARK_BOLT = 72504,  // timer 
    GASS_BOMB_LATER_EXPLOSION = 71255, //timer 
    MASS_STUN = 71617, //phase 2 
    SUMMON_DRAGON = 70372, //phase 1 
    MASS = 71048, //timer 


};  
       
class Mage : public CreatureScript  
{  
    public:  
        Mage() : CreatureScript("Mage"){}  
             
        CreatureAI* GetAI(Creature* pCreature) const  
        {  
            return new MageAI(pCreature);  
        }  
       
        struct MageAI : public ScriptedAI  
        {  
            MageAI(Creature *c) : ScriptedAI(c) {}  
                  
            uint32 Mana_buble_timer;  
            uint32 Death_decay_timer; 
            uint32 Dark_simulacrum_timer; 
            uint32 Berserkerz_timer; 
            uint32 Dark_bolt_timer; 
            uint32 Gass_bomb_later_explosion_timer; 
            uint32 Mass_stun_timer; 
            uint32 Summon_dragon_timer; 
            uint32 Mass_timer; 
            uint32 currentPhase; 

       
            void Reset()  
            {  
                currentPhase = 0; 
                Mana_buble_timer = 1; 
                Death_decay_timer = 1; 
                Dark_simulacrum_timer = 60000; 
                Berserkerz_timer = 900000; 
                Dark_bolt_timer = 1; 
                Gass_bomb_later_explosion_timer = 1; 
                Mass_stun_timer = 0; 
                Summon_dragon_timer = 0; 
                Mass_timer = 1; 

            }  
        
            void JustDied(Unit * victim)  
            {  
                me->MonsterSay("You just lucky!!",LANG_UNIVERSAL,NULL);  
            }  
       
            void KilledUnit(Unit * victim)  
            {  
                me->MonsterSay("Noone can't defeat me!",LANG_UNIVERSAL,NULL);     
            }  
       
            void EnterCombat(Unit * /*who*/)  
            {  
                me->MonsterSay("You dont know what you do!",LANG_UNIVERSAL,NULL);  
            }  
                 
            void UpdateAI(const uint32 uiDiff)  
            {  
                if(!UpdateVictim())  
                    return;  

                  
//Phase 
//-------------------------------------------------------------------------- 

                      { 
	//if ((me->GetHealth() * 100 / me->GetMaxHealth() <= 70) && currentPhase == 0) 
	if (HealthAbovePct(70)&& currentPhase == 0) 
            
        { 
            me->CastStop();  
            DoCast(me->getVictim(), SUMMON_DRAGON); 
            me->MonsterYell("FEEL IT", LANG_UNIVERSAL, me->GetGUID()); 
            currentPhase = 1; 
        } 
      } 

//-------------------------------------------------------------------------- 

                      { 
       if ((me->GetHealth() * 100 / me->GetMaxHealth() <= 50) && currentPhase == 1) 
            
        { 
            me->CastStop();  
            DoCast(me->getVictim(), MASS_STUN); 
            me->MonsterYell("You are all weakly... SPIRITS OF SHADOW TAKE ME A POWER..!!!!!", LANG_UNIVERSAL, me->GetGUID()); 
            currentPhase = 2; 
        } 
      } 

//-------------------------------------------------------------------------- 
   
                      if ((me->GetHealth() * 100 / me->GetMaxHealth() <= 20) && currentPhase == 2) 
      
  { 
  me->CastStop();  
   DoCast(me->getVictim(), MANA_BUBLE); 
   DoCast(me->getVictim(), SUMMON_DRAGON); 
   if(me->GetPower(POWER_MANA) == 0) 
   { 
    me->CastStop(MANA_BUBLE); 
   } 
   me->MonsterYell("YES.YES! I feel it!! Try to kill my friend again! UHAHAHAHAAAAA!!!", LANG_UNIVERSAL, me->GetGUID()); 
   currentPhase = 3; 

//-------------------------------------------------------------------------- 


// Death&Decay :  

                    if(!UpdateVictim())  
                    return;  

                 if (Death_decay_timer <= uiDiff)  
                        {  
                        DoCast(me->getVictim(), DEATH_DECAY);   
                        Death_decay_timer = 40000;   
                    }  
            else  
                          Death_decay_timer -= uiDiff;  

//-------------------------------------------------------------------------- 


// Dark bolt :  

                    if(!UpdateVictim())  
                    return;  

                    if (Dark_bolt_timer <= uiDiff)  
                        {  
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0)) 
                        DoCast(pTarget, DARK_BOLT);   
                        Dark_bolt_timer = 35000;   
                    }  
            else  
                          Dark_bolt_timer -= uiDiff;  

                           

//-------------------------------------------------------------------------- 

// DARK SIMULACRUM :  

                    if(!UpdateVictim())  
                    return;  
                     
                    if (Dark_simulacrum_timer <= uiDiff)  
                        {  
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0)) 
                        DoCast(target, DARK_SIMULACRUM); 

                        Dark_simulacrum_timer = 60000;   
                    }  
            else  
                          Dark_simulacrum_timer -= uiDiff;  

//-------------------------------------------------------------------------- 



// Mass :  

                    if(!UpdateVictim())  
                    return;  

                 if (Mass_timer <= uiDiff)  
                        {  
                        DoCast(me->getVictim(), MASS);   
                        Mass_timer = 50000;   
                    }  
            else  
                          Mass_timer -= uiDiff;  

//-------------------------------------------------------------------------- 

// Mass Gass explosion :  

                    if(!UpdateVictim())  
                    return;  

                    if (Gass_bomb_later_explosion_timer <= uiDiff)  
                        {  
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0)) 
                        DoCast(pTarget, GASS_BOMB_LATER_EXPLOSION); 
                        Gass_bomb_later_explosion_timer = 120000;   
                    }  
            else  
                         Gass_bomb_later_explosion_timer -= uiDiff;  
                  

//-------------------------------------------------------------------------- 

if (!UpdateVictim()) 
    return; 

    if (Berserkerz_timer <= uiDiff) 
    { 
        DoCast(me, BERSERKERZ); 
    } 
     
//-------------------------------------------------------------------------- 





     

     
               DoMeleeAttackIfReady();  
            }  
            }         
        };  
};  
       
void AddSC_Mage()  
{  
    new Mage();  
}  