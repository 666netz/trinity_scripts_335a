/*
<--------------------------------------------------------------------------->
- Developer(s): Mthsena
- Complete: %100
- ScriptName: 'PresentationOfTheServer'
- Comment: Tested.
- Shared for:Emudevs by Synth
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"

enum Enums
{
	FIRST_TELEDELAY = 10000,
	SECOND_TELEDELAY = 20000,
	THIRD_TELEDELAY = 30000,
	FOURTH_TELEDELAY = 40000,
	BACK_TELEDELAY = 50000,
};

struct Event
{
	uint8 Events;
};
static std::map<uint32, Event> _events;

class Teleport : public BasicEvent
{
public:
	Teleport(Player* player) : _Plr(player) {}

	bool Execute(uint64 /*time*/, uint32 /*diff*/)
	{
		uint32 pEvent;
		pEvent = _Plr->GetGUID();

		switch (_events[pEvent].Events)
		{
		case 0: // First Teleport
			_Plr->TeleportTo(530, -1880.0f, 5381.0f, -12.0f, 1.0f); // Teleport Coordenates
			_Plr->GetSession()->SendAreaTriggerMessage("Here is Shattrath, blablabla..."); // Description, Tip
			_events[pEvent].Events = 1;
			break;

		case 1: // Second Teleport
			_Plr->TeleportTo(0, -13196.0f, 283.0f, 22.0f, 2.0f);
			_Plr->GetSession()->SendAreaTriggerMessage("Here is Gurubashi, blablabla...");
			_events[pEvent].Events = 2;
			break;

		case 2: // Third Teleport
			_Plr->TeleportTo(0, -14285.0f, 557.5f, 9.0f, 4.0f);
			_Plr->GetSession()->SendAreaTriggerMessage("Here is Booty Bay, blablabla...");
			_events[pEvent].Events = 3;
			break;

		case 3: // Fourth Teleport
			_Plr->TeleportTo(1, 16224.0f, 16254.0f, 13.0f, 2.0f);
			_Plr->GetSession()->SendAreaTriggerMessage("Here is GmIsland, blablabla...");
			_events[pEvent].Events = 4;
			break;

		case 4: // Back Teleport
			_Plr->TeleportTo(_Plr->GetStartPosition());
			_Plr->GetSession()->SendAreaTriggerMessage("Presentation finished, Enjoy!");
			_events.clear();
			break;
		}
		return true;
	}
	Player* _Plr;
};

class PresentationOfTheServer : public PlayerScript
{
public:
	PresentationOfTheServer() : PlayerScript("PresentationOfTheServer") {}

	void OnLogin(Player* player)
	{

		if (player->GetTotalPlayedTime() < 5)
		{
			QueryResult result = LoginDatabase.PQuery("SELECT numchars FROM realmcharacters WHERE acctid = %u", player->GetSession()->GetAccountId());
			Field* field = result->Fetch();
			int8 chars = field[0].GetInt8();

			if (chars > 1)
				return;

			player->GetSession()->SendAreaTriggerMessage("The system will teleport you in few seconds to present some things!"); // Initial message before starting...
			player->m_Events.AddEvent(new Teleport(player), player->m_Events.CalculateTime(FIRST_TELEDELAY));
			player->m_Events.AddEvent(new Teleport(player), player->m_Events.CalculateTime(SECOND_TELEDELAY));
			player->m_Events.AddEvent(new Teleport(player), player->m_Events.CalculateTime(THIRD_TELEDELAY));
			player->m_Events.AddEvent(new Teleport(player), player->m_Events.CalculateTime(FOURTH_TELEDELAY));
			player->m_Events.AddEvent(new Teleport(player), player->m_Events.CalculateTime(BACK_TELEDELAY));
		}
	}
};

void AddSC_PresentationOfTheServer()
{
	new PresentationOfTheServer;
}