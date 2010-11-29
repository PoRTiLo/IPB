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
		
		StringList ca;
		ca.push_back( "/pathto/cacert.crt" );
		j->setCACerts(ca);
		m_vManager = new VCardManager(j);

		database = new Database();
		database->start();

		if( !j->connect() )  //kontrola spojeni se servrem
		{
			getErrors( ENOCONNECT );
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

			m_vManager->fetchVCard(jid,this);
			//handleVCard(jid(), this);
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
			Roster::const_iterator it = roster.begin();
			for( ; it != roster.end(); ++it )
			{
				m_vManager->fetchVCard((*it).second->jid(), this);
			}
			printf("....................KONEC.............................\n");
				
		//	delete(m_vManager);
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

		
	
		void Bot::handleMessage( const Message& msg, MessageSession * /*session=0*/ )	{
//		 message.subject();
			if( msg.body() == QUIT )
				j->disconnect();
			else if( msg.body() == HALLO )
				m_session->send( "", "AHOJ");
			else if( msg.body() == "remove")
				j->rosterManager()->remove( msg.from() );

//			else if( msg.body() == )


		}






// debugovaci fce
      void Bot::handleLog( LogLevel level, LogArea area, const std::string& message ) {
         printf( "log level :%d, area :%d, %s\n", level, area, message.c_str() );
      }


		void Bot::handleVCard( const JID& jid, const VCard* v) {
			printf("\n\n........tadyyyyyyyyyyyyyyyyyyyy...........................     %s\n\n", jid.bare().c_str());

			++m_count;
// podivat jestli je dobre to V, jestli vubec nekdy nastane ze je prazdne
			if( !v )	//vcard je prazdny
			{	//return;
				//database->insertTableVCard(jid.bare());
			}
			else
			{
//				insertTableVCard();
				database->insertTableVCard(jid.bare(), 
				v->nickname(), v->url(), v->bday(), v->jabberid(), v->title(), v->role(), v->note(), v->mailer(), v->rev(), 
				v->uid(), v->tz(), v->prodid(), v->sortstring(), v->name().family, v->name().given, v->name().middle, 
				v->name().prefix, v->name().suffix);
			}

		}

		void Bot::handleVCardResult( VCardContext context, const JID& jid, StanzaError se = StanzaErrorUndefined) {

		}
