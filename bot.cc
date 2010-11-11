#include "bot.h"

	Bot::Bot()
	{
		login = DEF_LOGIN;
		pass = DEF_PASS;
	}

	Bot::Bot(string log, string password)
	{
		login = log;
		pass = password;
	}

	void Bot::setLogin( string log ) {
		login = log;
	}

	void Bot::setPass( string password ) {
		pass = password;
	}

	string Bot::getLogin() {
		return login;
	}

	string Bot::getPass() {
		return pass;
	}

	bool Bot::run() {
		JID jid(login);
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
			fprintf(stderr, "chyba, zadal jste spatne uzivatelske jmeno");
		}

		delete(j);
	}

      void Bot::onDisconnect( ConnectionError  ) {
         printf("onDisconecct \n"); 
      }
      void Bot::onConnect() {

      }

      bool Bot::onTLSConnect( const CertInfo& info ) {
         printf( "info %d:\n ",info.status);
         return true;
      }

	

		void Bot::onResourceBindError( ResourceBindError error ) {
			printf("OnResourceError:%d\n", error);
		}

		void Bot::onSessionCreateError( SessionCreateError error ) {
			printf("SessionCreateError:%d\n", error);
		}


		void Bot::handleItemSubscribed( const JID& jid ) {
			printf("handled subscribed:%s\n", jid.bare().c_str());
		}

		void Bot::handleItemAdded( const JID& jid ) {
			printf("handle ADD:%s\n", jid.bare().c_str());
		}

		void Bot::handleItemUnsubscribed( const JID& jid ) {
			printf("hande UNSUBSCRIED:%s\n", jid.bare().c_str());
		}

		void Bot::handleItemRemoved ( const JID& jid ) {
			printf("handle REMOVED:%s\n", jid.bare().c_str());
		}

		void Bot::handleItemUpdated( const JID& jid ) {
			printf("handle UPDATE:%s\n", jid.bare().c_str());
		}

		void Bot::handleRoster( const Roster& roster ) {
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

		void Bot::handleRosterError( const IQ& ) {
			printf("");
		}
		
		void Bot::handleRosterPresence( const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& ) {
			printf("");
		}
		
		void Bot::handleSelfPresence( const RosterItem& item, const std::string& resources, Presence::PresenceType presence, const std::string& ) {
			printf("");
		}

		bool Bot::handleSubscriptionRequest( const JID& jid, const std::string& ) {
			printf("");
			StringList groups;
			JID id(jid);
			j->rosterManager()->subscribe(id, "", groups, "" );
			return true;
		}

		bool Bot::handleUnsubscriptionRequest( const JID& jid, const std::string& ) {
			printf("");
			return true;
		}

		void Bot::handleNonrosterPresence( const Presence& presence ) {
			printf("");
		}

		
	
		void Bot::handleMessage( const Message& message, MessageSession * /*session=0*/ )	{
		 message.subject();
			/*if( msg.body() == "quit" )quiPt*/
		}






// debugovaci fce
      void Bot::handleLog( LogLevel level, LogArea area, const std::string& message ) {
         printf( "log level :%d, area :%d, %s\n", level, area, message.c_str() );
      }



