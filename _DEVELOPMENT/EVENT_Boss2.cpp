#include "ScriptPCH.h"
#include "ScriptedCreature.h"

enum Spells
{
	SPELL_1			= SPELL ID, //This is the first spell the boss will cast.
	SPELL_2			= SPELL ID, //This is the first spell the boss will cast.
	SPELL_3			= SPELL ID, //This is the first spell the boss will cast.
	SPELL_4			= SPELL ID  //This is the frenzy spell the boss will cast.
};

class Boss_Segacedi: public CreatureScript
{
public:
	Boss_Segacedi() : CreatureScript("Boss_Segacedi") { } //Make a creature in your DB, and set Boss_Segacedi in the script collumn.

	CreatureAI* GetAI(Creature* creature) const
	{
		return new Boss_SegacediAI (creature);
	}
	struct Boss_SegacediAI : public ScriptedAI
	{
		uint32 SPELL1Timer;
		uint32 SPELL2Timer;
		uint32 SPELL3Timer;
		bool IsEnraged;

		void Reset()
		{
			SPELL1Timer = 6000;   // This is in milliseconds, 1000 milliseconds = 1 second. At the moment this spell will be casted every 6 seconds.
			SPELL2Timer = 12000;  // This is in milliseconds, 1000 milliseconds = 1 second. At the moment this spell will be casted every 12 seconds.
			SPELL3Timer = 18000;  // This is in milliseconds, 1000 milliseconds = 1 second. At the moment this spell will be casted every 18 seconds.
			isEnraged = false;
		}

		void EnterCombat(Unit* /*who*/)
		{
			me->MonsterSay("Who dare enters my lake?", LANG_UNIVERSAL, NULL); // When you enter combat with the creature he will say this. Edit in between the "" with your desired message.
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (SPELL1Timer < diff)
			{
				DoCastVictim(SPELL_1);
				SPELL1Timer = 6000;
			} else SPELL1Timer -= diff;

			if (SPELL2Timer < diff)
			{
				DoCastVictim(SPELL_2);
				SPELL2Timer = 12000;
			} else SPELL2Timer -= diff;
			
			if (SPELL3Timer < diff)
			{
				DoCastVictim(SPELL_3);
				SPELL3Timer = 18000;
			} else SPELL3Timer -= diff;

			if (!IsEnraged && HealthBelowPct(20))
			{
				DoCast(me, SPELL_FRENZY);
				isEnraged = true;
			}

			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_Boss_Segacedi ()
{
	new Boss_Segacedi();
}
This is NOT a copy and paste script you need to edit the SPELL ID and the timers. Should compile fine though just let me know if there are any errors, also remember this is my first C++ script.
