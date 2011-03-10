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

	bool Bot::run() {

		signalTerm();

		JID jid(this->login);
		j = new Client(jid, pass);
		j->registerConnectionListener(this);
		j->registerMessageHandler(this);
		//j->registerMessageSessionHandler(this, 0);
		j->rosterManager()->registerRosterListener(this);
//		j->rosterManager()->registerPresenceHandler(this);
		j->disco()->registerDiscoHandler(this);
		j->disco()->setVersion("Pokus", "0.0.1", "UBUNTU"); //zaobrazi se v infu, nazev, verze, system
		j->disco()->setIdentity( "client", "bot" );
		j->disco()->addFeature( "http://jabber.org/protocol/tune");
		j->disco()->addFeature( "http://jabber.org/protocol/tune+notify");
		j->disco()->addFeature( "http://jabber.org/protocol/pubsub");
		j->disco()->addFeature( "http://jabber.org/protocol/mood");
		j->disco()->addFeature( "http://jabber.org/protocol/pubsub#event");
		j->disco()->addFeature( "http://jabber.org/protocol/mood+notify");
j->registerStanzaExtension( new ChatState(gloox::ChatStateActive));
j->registerStanzaExtension( new PubSub::Event(NULL) );
		j->setPresence( Presence::Available, 5 );   //Nastaveni statusuvailable
		j->registerPresenceHandler( this );
		j->registerIqHandler(this, ExtVersion);
		j->registerIqHandler(this, ExtDiscoInfo);
	//	j->registerIqHandler(this, ExtCaps);
		j->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);
		TagHandler * tags;
		j->registerTagHandler(tags, "pepe","pepe");
		StringList ca;
		ca.push_back( "/pathto/cacert.crt" );
		j->setCACerts(ca);
		m_vManager = new VCardManager(j);
		database = new Database();
		database->start();

		swVersion = new SwVersion();
		m_pubsub = new PubSub::Manager( j );	
		j->connect(false);  //kontrola spojeni se servrem
		while(true)
		{
			j->recv();
			if( f_global == true )
			{
				end();
				break;
			}

		}
	
		delete(m_vManager);
		delete(j);
		delete(database);
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
	
const PubSub::Event* pse = msg.findExtension<PubSub::Event>( ExtPubSubEvent );
cout<<"ya888888888888888"<<endl;
if(pse)
{

cout<<"...........................ya888888888888888"<<endl;
}
else
{
		database->insertTableMessage( m_session->target().bare().c_str(),  msg.body().c_str(),  msg.subject().c_str(), msg.thread().c_str(), Bot::messageSubtype(msg.subtype()).c_str() );
		if( msg.body() == QUIT && (m_session->target().bare() == "pidgin@localhost" || m_session->target().bare() == "portilo@jabbim.cz") )
			j->disconnect();
		else if( msg.body() == "USER" && (m_session->target().bare() == "pidgin@localhost" || m_session->target().bare() == "portilo@jabbim.cz") )
			m_session->send(database->printUser());
		else if( msg.body() == HALLO )
			m_session->send( "AHOJ");
		else if( msg.body() == "remove")
			j->rosterManager()->remove( msg.from() );
}			
	}
		
	void Bot::handleMessageSession( MessageSession*  session ) {
//ROzebrat kdyz prijde info o pozici, tune, ...........
		if( m_session )
			j->disposeMessageSession( m_session );
		m_session = session;
		m_session->registerMessageHandler( this );



cout << m_session->types() << endl;
m_event = new EventDispatcher();
m_event->registerEventHandler( this, "http://jabber.org/protocol/pubsub#event" );
cout<<"yaddddddddddddddddddddddddd888888888888888888888888888"<<endl;
	m_messageEventFilter = new MessageEventFilter( m_session );
   m_messageEventFilter->registerMessageEventHandler( this );
//	m_session->registerMessageFilter(m_messageEventFilter);
m_chatStateFilter = new ChatStateFilter( m_session );
   m_chatStateFilter->registerChatStateHandler( this );
	}
 void Bot::handleMessageEvent( const JID& from, MessageEventType event ){

cout<<"1111111111111111111111111111111111111111111111111111111111111888888"<<endl;
}
void Bot::handleChatState( const JID& from, ChatStateType state ) {


cout<<"1111111111111111111111111111111111111111111111111111111111111888888"<<endl;
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

		j->disconnect();
		database->exitError();
	}

	  void Bot::handleDiscoInfo( const JID& /*iq*/, const Disco::Info&, int /*context*/ )
	     {
//			        printf( "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmhandleDiscoInfoResult}\n" );
					      }

							    void Bot::handleDiscoItems( const JID& /*iq*/, const Disco::Items&, int /*context*/ )
								     {
										        printf( "handleDiscoItemsResult\n" );
												      }

														  void Bot::handleDiscoError( const JID& /*iq*/, const Error*, int /*context*/ )
															     {
																	        printf( "handleDiscoError\n" );

															}


bool Bot::handleIq( const IQ &iq ) {

	if( (iq.tag()->findChild("query")) && iq.tag()->findAttribute("type") != "error" )
	{
		Tag *queryTag =  (iq.tag()->findChild("query"))->clone();

		JID jidPom( iq.tag()->findAttribute("from") );

		if( queryTag->findAttribute("xmlns") == XMLNS_VERSION )
		{
			if( queryTag->findChild("name") )
				swVersion->setName( queryTag->findChild("name")->cdata() );
			if( queryTag->findChild("version") )
				swVersion->setVersion( queryTag->findChild("version")->cdata() );
			if( queryTag->findChild("os") )
				swVersion->setOs( queryTag->findChild("os")->cdata() );

			database->updateTableResource( jidPom.bare(), jidPom.resource(), swVersion->name(), swVersion->version(), swVersion->os());
		}
		else if( queryTag->findAttribute("xmlns") == XMLNS_DISCO_INFO )
		{
			if(queryTag->findChild("identity") )
			{
				Tag *identTag = queryTag->findChild("identity")->clone();
				swVersion->setCategory(identTag->findAttribute("category") );
				swVersion->setName( identTag->findAttribute("name") );
				swVersion->setType( identTag->findAttribute("type") );
			}

			Tag *xTag =  (iq.tag()->findChild("x"))->clone();
			swVersion->parserTagX( xTag);
			/*if(xTag->findChild("field","var","ip_version") )
			{
				Tag * fieldTag = xTag->findChild("field","var","ip_version")->clone();
//				swVersion->setIP( (fieldTag->findChild("value"))->cdata() );					//dodelat, mozno i IP6
			}
			if(xTag->findChild("field","var","os") )
			{
				Tag * fieldTag = xTag->findChild("field","var","os")->clone();
				swVersion->setOs( (fieldTag->findChild("value"))->cdata() );
			}
			if(xTag->findChild("field","var","os_version") )
			{
				Tag * fieldTag = xTag->findChild("field","var","os_version")->clone();
				swVersion->setOsVersion( (fieldTag->findChild("value"))->cdata() );
			}
			if(xTag->findChild("field","var","software") )
			{
				Tag * fieldTag = xTag->findChild("field","var","software")->clone();
				swVersion->setSoftware( (fieldTag->findChild("value"))->cdata() );
			}
			if(xTag->findChild("field","var","software_version") )
			{
				Tag * fieldTag = xTag->findChild("field","var","software_version")->clone();
				swVersion->setVersion( (fieldTag->findChild("value"))->cdata() );
			}*/
		}
	}
}

		void Bot::handleIqID 	( 	const IQ & 	iq, 
				int 	context
					){

//cout <<"...qwqwqwqw...................................handleIQID............................"<<endl;
		}


	// Reakce na zmenu statusu uzivatele v kontakt listu
void Bot::handlePresence( const Presence& presence) {

	JID jidFull = presence.from();

	Roster* roster =	j->rosterManager()->roster();
	if( roster->find(jidFull.bare()) != roster->end() )	//kontrola ze to poslal nekdo ze seznamu jiaignorace
	{
		if( presence.subtype() != 5 )
		{

			database->insertTablePresence( jidFull.bare(), presence.status(), jidFull.username(), jidFull.resource(), Bot::presenceString(presence.subtype()), presence.priority(),
			                               swVersion->name(), swVersion->version(), swVersion->os() );

			if( (presence.findExtension( ExtCaps )) != 0 )
			{
				bool newResource = true;
				bool update = false;
				Tag * capTag = (presence.findExtension( ExtCaps ))->tag()->clone();
				string ver = capTag->findAttribute("ver");
				map<string, string>::iterator it;
				it = database->listVer.find(jidFull.full());
				if( it != database->listVer.end() )
				{
					if( ver == it->second )	// je vse aktualni
					{
						update = database->updateTableResource( jidFull.bare(), Bot::presenceString(presence.subtype()), presence.status(), jidFull.resource(), presence.priority());
						newResource = false;
					}
				}
				else
					database->listVer.insert(make_pair(string(jidFull.full()), string(ver)));
				if( !update || newResource )
				{
					database->listVer[jidFull.full()] = ver;
					j->send( swVersion->createIqStanza( this->login, jidFull.bare(), jidFull.resource()) );			// poslani dotazi na software verzi XEP-0092
					j->disco()->getDiscoInfo(jidFull.full(),"", this,1,"");
					database->updateTableResource( jidFull.bare(), Bot::presenceString(presence.subtype()), presence.status(), jidFull.resource(), presence.priority(), ver);
				}
			}
		}
		else
		{
			database->insertTablePresence( jidFull.bare(), presence.status(), jidFull.username(), jidFull.resource(), Bot::presenceString(presence.subtype()) );
			database->updateTableResource( jidFull.bare(), Bot::presenceString(presence.subtype()), presence.status(), jidFull.resource());
		}
		database->updateTableStatus(jidFull.bare());					// aktualizace tabulky Status na zakldade tabuly resource
	}
}
	// Reakce na zmenu statusu uzivatele v kontakt listu
	void Bot::handleRosterPresence( const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& msg ) {
		
//item.jid()getDiscoInfo();
//JID jidTo(item.jid()+"/"+resource);
//	j->disco()->getDiscoInfo(jidTo,"", this,1,"");
/*		if( presence != 5 )
		{

			database->insertTablePresence( item.jid(), msg, item.name(), resource, Bot::presenceString(presence), item.resource(resource)->priority(),
			                               swVersion->name(), swVersion->version(), swVersion->os() );
			bool update = database->updateTableResource( item.jid(), Bot::presenceString(presence), msg, resource, item.resource(resource)->priority() );

			if( !update )
			{
				j->send( swVersion->createIqStanza( this->login, item.jid(), resource) );			// poslani dotazi na software verzi XEP-0092
			}
		}
		else
		{
			database->insertTablePresence( item.jid(), msg, item.name(), resource, Bot::presenceString(presence) );
			database->updateTableResource( item.jid(), Bot::presenceString(presence), msg, resource);
		}

		database->updateTableStatus(item.jid());					// aktualizace tabulky Status na zakldade tabuly resource
		*/
	}

      void Bot::handleTune( const JID& from, TuneType state ) {


		}
		void Bot::handleEvent( const Event& event ) {
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
		}
/*
		 void Bot::handleNodeCreationResult( const JID& service,  const std::string& node, const Error& e )
		    {
				       printf( "created node '%s' on '%s'\n", node.c_str(), service.bare().c_str() );
						     }

	void Bot::handleNodeDeletationResult( const JID& service, const std::string& node,  const Error& e ) {
		
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
		}

	void Bot::handleNodePurgeResult( const JID& service, const std::string& node, const Error& e ) {
		
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
		}

 void Bot::handleSubscriptionOptions( const JID& service, const JID& jid, const std::string& node, const DataForm& options ) {
	 
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }
 void Bot::handleSubscriptionOptionsResult( const JID& service, //const JID& jid, 
 	const std::string& node,const Error& e ) {
	 
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }

	void Bot::handleSubscriberList( const JID& service, const std::string& node, const PubSub::SubscriberList& list ) {
		
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
		}

 void Bot::handleSubscriberListResult( const JID& service, const std::string& node, const Error& e ) {
	 
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }
 void Bot::handleAffiliateList( const JID& service, const std::string& node, const PubSub::AffiliateList& list ) {
	 
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }

void Bot::handleAffiliateListResult( const JID& service, const std::string& node, const Error& e ) {
	
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	}
void Bot::handleNodeConfig( const JID& service, const std::string& node, const DataForm& config ) {
	
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	}
 void Bot::handleNodeConfigResult( const JID& service, const std::string& node,const Error& e ) {
	 
cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }
	 */

	 void 	Bot::handleItem (const JID &service, const std::string &node, const Tag *entry) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }
	  void 	Bot::handleItems (const std::string &id, const JID &service, const std::string &node, const PubSub::ItemList &itemList, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	 void 	Bot::handleItemPublication (const std::string &id, const JID &service, const std::string &node, const PubSub::ItemList &itemList, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }
	  void 	Bot::handleItemDeletion (const std::string &id, const JID &service, const std::string &node, const PubSub::ItemList &itemList, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleSubscriptionResult (const std::string &id, const JID &service, const std::string &node, const std::string &sid, const JID &jid, const PubSub::SubscriptionType subType, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleUnsubscriptionResult (const std::string &id, const JID &service, const Error *error){

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleSubscriptionOptions (const std::string &id, const JID &service, const JID &jid, const std::string &node, const DataForm *options, const std::string &str, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	 void 	Bot::handleSubscriptionOptionsResult (const std::string &id, const JID &service, const JID &jid, const std::string &node, const std::string &st, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }
	  void 	Bot::handleSubscribers (const std::string &id, const JID &service, const std::string &node, const PubSub::SubscriberList *list, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	 }
	  void 	Bot::handleSubscribersResult (const std::string &id, const JID &service, const std::string &node, const PubSub::SubscriberList *list, const Error *error) {


cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleAffiliates (const std::string &id, const JID &service, const std::string &node, const PubSub::AffiliateList *list, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleAffiliatesResult (const std::string &id, const JID &service, const std::string &node, const PubSub::AffiliateList *list, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleNodeConfig (const std::string &id, const JID &service, const std::string &node, const DataForm *config, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleNodeConfigResult (const std::string &id, const JID &service, const std::string &node, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;

	  }
	  void 	Bot::handleNodeCreation (const std::string &id, const JID &service, const std::string &node, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleNodeDeletion (const std::string &id, const JID &service, const std::string &node, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleNodePurge (const std::string &id, const JID &service, const std::string &node, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;

	  }
	  void 	Bot::handleSubscriptions (const std::string &id, const JID &service, const PubSub::SubscriptionMap &subMap, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void 	Bot::handleAffiliations (const std::string &id, const JID &service, const PubSub::AffiliationMap &affMap, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
	  void Bot::handleDefaultNodeConfig (const std::string &id, const JID &service, const DataForm *config, const Error *error) {

cout << "//////////////////////////////.................................je to tadyyyyyyyyy"<<endl;
	  }
