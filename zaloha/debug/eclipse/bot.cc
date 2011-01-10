/*TODO
PRESENCE - dodelat delayTime, neco o zpozdeni
			- SHOW - podle RFC podporuje - away, chat, dnd, normal, xa
			- ID
			- ERRORS
         - jinak kompletni
MESSAGE -
IQ -
VLASTNI - poznamky do databaze
*/
#include "bot.h"

	Bot::Bot()
	{
		this->login = DEF_LOGIN;
		this->pass = DEF_PASS;
	}

	Bot::Bot(string log, string password)
	{
		this->login = log;
		this->pass = password;
	}

	Bot::~Bot()
	{
		cout<<"ooooooooooooooooooooooooooooooooooo"<<endl;
end();
		delete(m_vManager);
		delete(j);
		delete(database);
	}
	void Bot::setLogin( string log ) {
		this->login = log;
	}

	void Bot::setPass( string password ) {
		this->pass = password;
	}

	string Bot::getLogin() {
		return this->login;
	}

	string Bot::getPass() {
		return this->pass;
	}
bool thread() 
{ 
	 // for (int i = 0; i < 5; ++i) 
	//	    { 
			//	     wait(1); 
	//				      std::cout << i << std::endl; 
		while(true)
		{
							sleep(1);
							  } 
							  return true;
						
} 
	bool Bot::run() {
 boost::thread t(thread); 
 t.join();
//if( thread == true )
//cout <<"pepa"<<endl;
		JID jid(this->login);
		j = new Client(jid, pass);
		j->registerConnectionListener(this);
		//j->registerMessageHandler(this);
		j->registerMessageSessionHandler(this, 0);
//		j->registerIqHandler(this, 1);
		j->rosterManager()->registerRosterListener(this);
//		j->rosterManager()->registerPresenceHandler(this);
		j->disco()->setVersion("Pokus", "0.0.1", "UBUNTU"); //zaobrazi se v infu, nazev, verze, system
		j->disco()->setIdentity( "client", "bot" );
//		j->disco()->addFeature( XMLNS_CHAT_STATES );
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
		//delete(j);
	}

	void Bot::onDisconnect( ConnectionError ) {
		printf("onDisconecct \n"); 
	}

	void Bot::onConnect() {
	}

 	bool Bot::onTLSConnect( const CertInfo& info ) {
//		printf( "info %d:\n ",info.status);
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
		database->insertTableUser(jid.bare());
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

		Roster::const_iterator it = roster.begin();
		for( ; it != roster.end(); ++it )
		{
			m_vManager->fetchVCard((*it).second->jid(), this);
			database->insertTableUser((*it).second->jid());
		}
				
	}

		void Bot::handleRosterError( const IQ& ) {
		}
		
	string Bot::presenceString( const int presence ) {

		if( presence == 0 )
			return "Available";
		else if( presence == 1 )
			return "Chat";
		else if( presence == 2 )
			return "Away";
		else if( presence == 3 )
			return "DND";
		else if( presence == 4 )
			return "XA";
		else if( presence == 5 )
			return "Unavaliable";
		else if( presence == 6 )
			return "Probe";
		else if( presence == 7 )
			return "Error";
		else if( presence == 8 )
			return "Invalid";
		else
			return "Unknown presence";
	}

	void Bot::handleRosterPresence( const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& msg ) {

		if( presence != 5 )
			database->insertTablePresence( item.jid(), msg, item.name(), resource, Bot::presenceString(presence), item.resource(resource)->priority() );
		else
			database->insertTablePresence( item.jid(), msg, item.name(), resource, Bot::presenceString(presence) );
	}
	
		void Bot::handleSelfPresence( const RosterItem& item, const std::string& resources, Presence::PresenceType presence, const std::string& msg ) {
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

		
	
	string Bot::messageSubtype( const int subtype ) {

		if( subtype == 1 )
			return "chat";
		else if( subtype == 2 )
			return "error";
		else if( subtype == 4 )
			return "groupchat";
		else if( subtype == 8 )
			return "headline";
		else if( subtype == 16 )
			return "normal";
		else if( subtype == 32 )
			return "invalid";
		else
			return "unknow";
	}

	void Bot::handleMessage( const Message& msg, MessageSession * /*session=0*/ )	{
			
		database->insertTableMessage( m_session->target().bare().c_str(),  msg.body().c_str(),  msg.subject().c_str(), msg.thread().c_str(), Bot::messageSubtype(msg.subtype()).c_str() );
		if( msg.body() == QUIT && (m_session->target().bare() == "pidgin@localhost" || m_session->target().bare() == "portilo@jabbim.cz") )
			j->disconnect();
		else if( msg.body() == HALLO )
			m_session->send( "AHOJ");
		else if( msg.body() == "remove")
			j->rosterManager()->remove( msg.from() );
	}
		
	void Bot::handleMessageSession( MessageSession*  session ) {

		if( m_session )
			j->disposeMessageSession( m_session );
		m_session = session;
		m_session->registerMessageHandler( this );

	//	m_messageEventFilter = new MessageEventFilter( m_session );
	//	m_messageEventFilter->registerMessageEventHandler( this );
	//	m_chatStateFilter = new ChatStateFilter( m_session );
	//	m_chatStateFilter->registerChatStateHandler( this );
	}

	void Bot::handleLog( LogLevel level, LogArea area, const std::string& message ) {

		printf( "log level :%d, area :%d, %s\n", level, area, message.c_str() );
		if( area == LogAreaXmlIncoming || area == LogAreaXmlOutgoing )
			database->insertTableXML( level, area, message );
		else// if( area == LogAreaClassDns )      	//Debagovaci zprava
			database->insertTableDebug( level, area, message );
	}


	void Bot::handleVCard( const JID& jid, const VCard* v) {
//			++m_count;
// podivat jestli je dobre to V, jestli vubec nekdy nastane ze je prazdne
		if( !v )	//vcard je prazdny
		{	
			database->insertTableUser(jid.bare());
		}
		else
		{
			database->insertTableVCard(jid.bare(), v->nickname(), v->url(), v->bday(), v->jabberid(), v->title(), v->role(), v->note(), v->mailer(), v->rev(), v->uid(), v->tz(), v->prodid(), v->sortstring(), v->name().family, v->name().given, v->name().middle, v->name().prefix, v->name().suffix);
			database->insertTableUser(jid.bare());
		}

	}

		void Bot::handleVCardResult( VCardContext context, const JID& jid, StanzaError se = StanzaErrorUndefined) {

		}

	void Bot::end() {
cout<<"ukoncuji"<<endl;
		j->disconnect();
		exit(8);
	}
/*	void Bot::handleMessageEvent( const JID& from, MessageEventType event ) {
		printf("\n\n\n...event.......%d\n\n\n", event);
	}

	void Bot::handleChatState( const JID& from, ChatStateType state) {
		printf("\n\n\n.....state.....%d\n\n\n", state);
	}
	*/
