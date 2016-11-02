#include "ScriptPCH.h"
#include "Config.h"
#include "ScriptedCreature.h"
#include "Language.h"
#include "time.h"
#include <cmath>

#define STOCKNUMBER 5

namespace
{
	class CS_StockExchange : public CreatureScript
	{
	public:
		CS_StockExchange() : CreatureScript("Creature_StockExchange") { }



		bool OnGossipHello(Player* plr, Creature* creature) override //MAIN MENU
		{
			WorldSession* session = plr->GetSession();
			QueryResult licencetest = CharacterDatabase.PQuery("SELECT `1`, `2`, `3`, `4`, `5`  FROM `character_stockdata` WHERE iD = %u", plr->GetGUIDLow());
			plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Scroll_08:30:30:-18:0|tQuels sont les cours actuels du marche?", GOSSIP_SENDER_MAIN, 2);
			plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tQuelles actions sont en ventes?", GOSSIP_SENDER_MAIN, 1);
			if (!licencetest)
			{
				plr->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_MISC_NOTE_02:30:30:-18:0|tJe veux acheter une licence d'investissement.", GOSSIP_SENDER_MAIN, 12, "Cette action vous coutera", 400000, false);
			}
			else //Player can invest if he has a licence
			{
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Coin_02:30:30:-18:0|tJ'aimerais gerer mes investissements.", GOSSIP_SENDER_MAIN, 3);
			}
			plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tUn plaisir d'avoir fait affaire avec vous.", GOSSIP_SENDER_MAIN, 4);
			plr->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player* plr, Creature* creature, uint32 sender, uint32 uiAction) override
		{
			uint32 stock = 0;
			int32 amount = 0;
			plr->PlayerTalkClass->ClearMenus();
			WorldSession* session = plr->GetSession();
			std::ostringstream message;
			float ownedratio[5];
			int scale[5];
			for (int iter = 1; iter < 6; iter++)
			{
				QueryResult result = WorldDatabase.PQuery("SELECT `OwnedRatio`,`Scale`  FROM `stocks` WHERE iD = %u", iter);
				if (!result)
					return false;
				Field* field = result->Fetch();
				ownedratio[iter - 1] = field[0].GetFloat();
				scale[iter - 1] = field[1].GetInt32();
			}
			switch (uiAction)
			{
			case 1: //REMAINING STOCKS
				message << "ACTIONS A VENDRE SUR MARCHE$BManoir de Ravenholdt : " << StockFunction(1)*scale[0] * (1 - ownedratio[0]) << "$BLa Voile Sanglante : " << StockFunction(2)*scale[1] * (1 - ownedratio[1]) << "$BCartel Fusetincelle : " << StockFunction(3)*scale[2] * (1 - ownedratio[2]) << "$BMarchands de soie de Theramore : " << StockFunction(4)*scale[3] * (1 - ownedratio[3]) << "$BEldoar'norore : " << StockFunction(5)*scale[4] * (1 - ownedratio[4]);
				creature->Whisper(message.str(), LANG_UNIVERSAL, plr);
				plr->PlayerTalkClass->SendCloseGossip();
				OnGossipHello(plr, creature);
				break;
			case 2: //CURRENT EXCHANGE RATES
				message << "COURS ACTUELS DU MARCHE$BManoir de Ravenholdt : " << StockFunction(1)*scale[0] << "$BLa Voile Sanglante : " << StockFunction(2)*scale[1] << "$BCartel Fusetincelle : " << StockFunction(3)*scale[2] << "$BMarchands de soie de Theramore : " << StockFunction(4)*scale[3] << "$BEldoar'norore : " << StockFunction(5)*scale[4];
				creature->Whisper(message.str(), LANG_UNIVERSAL, plr);
				plr->PlayerTalkClass->SendCloseGossip();
				OnGossipHello(plr, creature);
				break;
			case 3: //MANAGE PORTFOLIO MENU (5-10)
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Helmet_30:30:30:-18:0|tManoir de Ravenholdt", GOSSIP_SENDER_MAIN, 5);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Helmet_66:30:30:-18:0|tLa Voile Sanglante", GOSSIP_SENDER_MAIN, 6);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Bomb_03:30:30:-18:0|tCartel Fusetincelle", GOSSIP_SENDER_MAIN, 7);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Chest_Cloth_56:30:30:-18:0|tMarchands de soie de Theramore", GOSSIP_SENDER_MAIN, 8);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_FireDancer_01:30:30:-18:0|tEldoar'norore", GOSSIP_SENDER_MAIN, 9);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tRetour au menu principal", GOSSIP_SENDER_MAIN, 10);
				plr->SEND_GOSSIP_MENU(50002, creature->GetGUID());
				break;
			case 4: //CLOSE GOSSIP
				plr->PlayerTalkClass->SendCloseGossip();
				break;
			case 5: //MANAGE RAVENHOLDT STOCK
				stock = 1;
				plr->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Letter_03:30:30:-18:0|tAcheter des parts", stock, 0, "Combien de pieces d'or desirez-vous investir?", 0, true);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Coin_16:30:30:-18:0|tVendre les parts", stock, 11);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tRetour au menu precedent", GOSSIP_SENDER_MAIN, 3);
				plr->SEND_GOSSIP_MENU(50002, creature->GetGUID());
				return true;
				break;
			case 6: //MANAGE BLOODSAIL STOCK
				stock = 2;
				plr->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Letter_03:30:30:-18:0|tAcheter des parts", stock, 0, "Combien de pieces d'or desirez-vous investir?", 0, true);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Coin_16:30:30:-18:0|tVendre les parts", stock, 11);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tRetour au menu precedent", GOSSIP_SENDER_MAIN, 3);
				plr->SEND_GOSSIP_MENU(50002, creature->GetGUID());
				break;
			case 7: //MANAGE GOBLIN STOCK
				stock = 3;
				plr->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Letter_03:30:30:-18:0|tAcheter des parts", stock, 0, "Combien de pieces d'or desirez-vous investir?", 0, true);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Coin_16:30:30:-18:0|tVendre les parts", stock, 11);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tRetour au menu precedent", GOSSIP_SENDER_MAIN, 3);
				plr->SEND_GOSSIP_MENU(50002, creature->GetGUID());
				break;
			case 8: //MANAGE SILKTRADERS STOCK
				stock = 4;
				plr->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Letter_03:30:30:-18:0|tAcheter des parts", stock, 0, "Combien de pieces d'or desirez-vous investir?", 0, true);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Coin_16:30:30:-18:0|tVendre les parts", stock, 11);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tRetour au menu precedent", GOSSIP_SENDER_MAIN, 3);
				plr->SEND_GOSSIP_MENU(50002, creature->GetGUID());
				break;
			case 9: //MANAGE ELDOAR'NORORE STOCK
				stock = 5;
				plr->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Letter_03:30:30:-18:0|tAcheter des parts", stock, 0, "Combien de pieces d'or desirez-vous investir?", 0, true);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Coin_16:30:30:-18:0|tVendre les parts", stock, 11);
				plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tRetour au menu precedent", GOSSIP_SENDER_MAIN, 3);
				plr->SEND_GOSSIP_MENU(50002, creature->GetGUID());
				return true;
				break;
			case 11: //TRANSACTION = SELL
				if (!SellStock(plr, stock))
					plr->GetSession()->SendNotification("Erreur lors de la vente des parts");
				plr->PlayerTalkClass->SendCloseGossip();
				OnGossipHello(plr, creature);
				break;
			case 12: //CREATE PLAYER LICENCE ( = ROW IN CHARACTER_STOCKDATA )
				if (plr->GetMoney() >= 400000)
				{
					if (CreateLicence(plr))
					{
						amount = 400000;
						plr->ModifyMoney(-amount);
						message << "Votre licence a ete achetee avec succes, " << plr->GetName() << "!";
						creature->Say(message.str(), LANG_UNIVERSAL, plr);
					}
					else
						plr->GetSession()->SendNotification("Erreur lors de l'enregistrement de votre licence... Prenez contact avec l'administrateur.");
				}
				else
				{
					message << "Navre, " << plr->GetName() << ", vous n'avez pas ces quarantes pieces d'or...";
					creature->Say(message.str().c_str(), LANG_UNIVERSAL, plr);
				}

				plr->PlayerTalkClass->SendCloseGossip();
				OnGossipHello(plr, creature);
				break;
			default:
				OnGossipHello(plr, creature);
				break;
			}

			return true;
		}
		bool OnGossipSelectCode(Player* plr, Creature* creature, uint32 stock, uint32 uiAction, const char* code) override
		{
			plr->PlayerTalkClass->ClearMenus();
			std::ostringstream message;
			int32 amount = 0;

			std::string investment = code;
			static const char* allowedcharacters = "1234567890";
			if (!investment.length() || investment.find_first_not_of(allowedcharacters) != std::string::npos) //If investment was specified incorrectly
			{
				plr->GetSession()->SendNotification("L'investissement doit-être declare en chiffres. N'utilisez que 0,1,2,3,4,5,6,7,8 et 9, stupide ignare que vous etes.");
			}
			else //If investment was specified properly
			{
				//Statements
				uint32 investmentI = uint32(atol(code) * 10000);
				if (investmentI <= plr->GetMoney())
				{
					double stockfunction = StockFunction(stock);

					QueryResult result1 = WorldDatabase.PQuery("SELECT `OwnedRatio`,`Scale`  FROM `stocks` WHERE iD = %u", stock);
					if (!result1)
						return false;
					Field* field = result1->Fetch();
					float ownedratio = field[0].GetFloat();
					int scale = field[1].GetInt32();
					QueryResult result2 = CharacterDatabase.PQuery("SELECT `%u` FROM `character_stockdata` WHERE iD = %u", stock, plr->GetGUIDLow());
					if (!result2)
						return false;
					field = result2->Fetch();
					float initialratio = field[0].GetFloat();
					float ratio = investmentI / scale / stockfunction;
					if (ratio <= (1 - ownedratio)) //If enough stocks left
					{
						int amount = investmentI;
						plr->ModifyMoney(-amount);  // substract it from player money
						CharacterDatabase.PExecute("UPDATE `character_stockdata` SET `%u` = %f WHERE `iD` = %u", stock, initialratio + ratio, plr->GetGUIDLow());
						WorldDatabase.PExecute("UPDATE `stocks` SET `OwnedRatio` = %f WHERE `iD` = %u", ownedratio + ratio, stock);
					}
					else
					{
						plr->GetSession()->SendNotification("Il n'y a pas assez de parts a acheter pour le montant que vous voulez investir, consultez les parts restantes avant d'investir.");
					}

				}
				else
				{
					message << "Vous n'avez pas tout cet argent a investir, " << plr->GetName() << ".";
					creature->Say(message.str().c_str(), LANG_UNIVERSAL, plr);
				}
			}

			plr->PlayerTalkClass->SendCloseGossip();
			OnGossipHello(plr, creature);
			return true;
		}

	private:
		bool SellStock(Player* plr, uint32 stock) /*SELL ALL THE SHARES OF THE SPECIFIED STOCK */
		{
			QueryResult result2 = WorldDatabase.PQuery("SELECT `OwnedRatio`,`Scale`  FROM `stocks` WHERE iD = %u", stock);
			if (!result2)
				return false;
			QueryResult result1 = CharacterDatabase.PQuery("SELECT `1`, `2`, `3`, `4`, `5`  FROM `character_stockdata` WHERE iD = %u", plr->GetGUIDLow());
			if (!result1)
				return false;
			Field* field = result1->Fetch();
			float ratio = field[stock - 1].GetFloat();
			if (ratio == 0)
			{
				plr->GetSession()->SendNotification("Vous n'avez aucune part a vendre pour ce marche...");
			}
			else //ONLY IF PLAYER OWNS SOMETHING
			{
				Field* field = result2->Fetch();
				float ownedratio = field[0].GetFloat();
				int scale = field[1].GetInt32();
				double stockfunction = StockFunction(stock);


				plr->ModifyMoney(int32(scale*stockfunction*ratio));  // add it to player money
				CharacterDatabase.PExecute("UPDATE `character_stockdata` SET `%u` = 0 WHERE `iD` = %u", stock, plr->GetGUIDLow());
				WorldDatabase.PExecute("UPDATE `stocks` SET `OwnedRatio` = %f WHERE `iD` = %u", ownedratio - ratio, 1);
			}
			return true;
		}

		bool CreateLicence(Player* plr)
		{
			SQLTransaction trans = CharacterDatabase.BeginTransaction();
			trans->PAppend("REPLACE INTO `character_stockdata` (`iD`, `1`, `2`, `3`, `4`, `5`) VALUES (%u, 0, 0, 0, 0, 0)", plr->GetGUIDLow());
			CharacterDatabase.CommitTransaction(trans);
			return true;
		}

		double StockFunction(uint32 stock) /* Works out the current exchange rate according to time ellapsed since stock market release */
		{
			// HOW MUCH TIME HAS PASSED...
			time_t now;
			struct tm y2k;
			double minutes;

			time(&now); //...UNTIL NOW...
			y2k = *localtime(&now);
			y2k.tm_hour = 18;   y2k.tm_min = 20; y2k.tm_sec = 0;
			y2k.tm_year = 115; y2k.tm_mon = 6; y2k.tm_mday = 27; //...SINCE STOCK MARKET RELEASE (This date might be updated at some point)

			minutes = abs(difftime(mktime(&y2k), now)) / 3600;

			switch (stock)
			{
			case 1: //Ravenholdt
				return (10 + 3 * sin(0.3* minutes) + sin(3 * minutes));
				break;
			case 2: //Bloodsail
				return (-atan(tan(minutes)) + 2);
				break;
			case 3: //Goblin
				return (2 + sin(30 * minutes)*cos(100 * minutes));
				break;
			case 4: //SilkTraders
				return (atan(tan(minutes)) + 2 + 0.1*minutes);
				break;
			case 5: //Eldoar'norore
				return (0.3*minutes + sin(5 * minutes)*cos(10 * minutes) + 1);
				break;
			default:
				return 0;
				break;
			}
		}
	};
}

void AddSC_Stock()
{
	new CS_StockExchange();
}
