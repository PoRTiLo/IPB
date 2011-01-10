//example from gloox....

#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/disco.h>
#include <string>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <gloox/component.h>
#include <ncurses.h>
#include <gloox/connectionlistener.h>
#include <gloox/rostermanager.h>
#include <gloox/presence.h>
using namespace std;
using namespace gloox;


class Bot : public RosterListener, LogHandler, MessageHandler, ConnectionListener  //dedi z MessageHandler
{
   public:
      Bot(){}
      Bot(string login, string pass)
      {
         JID jid(login);
			cerr << login << pass <<endl;
         j = new Client(jid, pass);
         j->registerConnectionListener(this);
         j->registerMessageHandler(this);
			j->rosterManager()->registerRosterListener(this);
         j->disco()->setVersion("Pokus", "0.0.1", "UBUNTU"); //zaobrazi se v infu, nazev, verze, system
         j->disco()->setIdentity( "client", "bot" );
			//PresenceType pesenece;// = Chat;
         //j->setPresence( Chat, 5 );   //Nastaveni statusuvailable

			j->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);

         
         if( !j->connect() )  //kontrola spojeni se servrem
         {
           cerr << "chyba, zadal jste spatne uzivatelske jmeno" << endl;
         }

			delete(j);
      }
		~Bot(){}
	
      virtual void onDisconnect( ConnectionError  ) {
         printf("onDisconecct \n"); 
      }
      virtual void onConnect() {

      }

      virtual bool onTLSConnect( const CertInfo& info ) {
         printf( "info %d:\n ",info.status);
         return true;
      }

		virtual void onResourceBindError( ResourceBindError error ) {
			printf("OnResourceError:%d\n", error);
		}

		virtual void onSessionCreateError( SessionCreateError error ) {
			printf("SessionCreateError:%d\n", error);
		}


		virtual void handleItemSubscribed( const JID& jid ) {
			printf("handled subscribed:%s\n", jid.bare().c_str());
		}

		virtual void handleItemAdded( const JID& jid ) {
			printf("handle ADD:%s\n", jid.bare().c_str());
		}

		virtual void handleItemUnsubscribed( const JID& jid ) {
			printf("hande UNSUBSCRIED:%s\n", jid.bare().c_str());
		}

		virtual void handleItemRemoved ( const JID& jid ) {
			printf("handle REMOVED:%s\n", jid.bare().c_str());
		}

		virtual void handleItemUpdated( const JID& jid ) {
			printf("handle UPDATE:%s\n", jid.bare().c_str());
		}

		virtual void handleRoster( const Roster& roster ) {
			printf("-----------------------------------------------------------\n");
			printf("Roster arrived\n");
			Roster::const_iterator it = roster.begin();
			for( ; it != roster.end(); ++it )
			{
				printf("jid: %s, name: %s, subscription: %d\n",(*it).second->jid().c_str(), (*it).second->name().c_str(), (*it).second->subscription());
				StringList g = (*it).second->groups();
				StringList::const_iterator it_g = g.begin();
				for( ; it_g != g.end(); ++it_g )
				{
					printf("\tgroup:%s\n",(*it_g).c_str());
				}
				RosterItem::ResourceMap::const_iterator rit = (*it).second->resources().begin();
				for( ; rit != (*it).second->resources().end(); ++rit )
				{
					printf("resources:%s\n",(*rit).first.c_str());
				}
			}
			printf(".................................................\n");
		}

		virtual void handleRosterError( const IQ& ) {
			printf("");
		}
		
		virtual void handleRosterPresence( const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& ) {
			printf("");
		}
		
		virtual void handleSelfPresence( const RosterItem& item, const std::string& resources, Presence::PresenceType presence, const std::string& ) {
			printf("");
		}

		virtual bool handleSubscriptionRequest( const JID& jid, const std::string& ) {
			printf("");
			StringList groups;
			JID id(jid);
			j->rosterManager()->subscribe(id, "", groups, "" );
			return true;
		}

		virtual bool handleUnsubscriptionRequest( const JID& jid, const std::string& ) {
			printf("");
			return true;
		}

		virtual void handleNonrosterPresence( const Presence& presence ) {
			printf("");
		}

		
	
		virtual void handleMessage( const Message& message, MessageSession * /*session=0*/ )	{
//		 message.subject();
			/*if( msg.body() == "quit" )quiPt*/
		}






// debugovaci fce
      virtual void handleLog( LogLevel level, LogArea area, const std::string& message ) {
         printf( "log level :%d, area :%d, %s\n", level, area, message.c_str() );
      }
   


   private:
      Client* j;
      RosterManager* roster;
};

int main( int argc, char* argv[] )
{

	
//rozparsrovat login
   string login = argv[1];
   char heslo[80];

   initscr();  //rozpozna typ terminalu, inicializuje curses datove struktury, vymaze obrazovku

   printw("Zadejte heslo : ");

   cbreak();   //znaky na vystupu nesou bufrovany, jsou okamzite k dispozice programu
   noecho();   //nepise znaky na terminal

   getstr(heslo); //nacte heslo

   endwin();   //nastavi terminal do puvodniho stavu

   cerr << login << ":" << heslo << endl;

   stringstream ss;  ss << heslo;  string pass;  ss>>pass;   //prevede char na string

	//Client* k;
	Bot bot(login, pass);
	//delete(k);

	return 0;
} 

