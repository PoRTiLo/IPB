/*TODO
//napoveda-mozno implementvat XHTML tagy:)
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

Bot::~Bot()	{}

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
	j->rosterManager()->registerRosterListener(this);
	j->disco()->registerDiscoHandler(this);
	j->disco()->setVersion("JabInfo", "0.1.2", "UBUNTU"); //zaobrazi se v infu, nazev, verze, system
	j->disco()->setIdentity( "client", "bot" );
	j->disco()->addFeature( "http://jabber.org/protocol/tune+notify");
	j->disco()->addFeature( "http://jabber.org/protocol/pubsub");
	j->disco()->addFeature( "http://jabber.org/protocol/pubsub#event");
	j->disco()->addFeature( "http://jabber.org/protocol/mood+notify");
	j->disco()->addFeature( "http://jabber.org/protocol/geoloc+notify");
	j->disco()->addFeature( "http://jabber.org/protocol/activity+notify");

	j->registerStanzaExtension( new PubSub::Event(NULL) );
	j->setPresence( Presence::Available, 5 );   //Nastaveni statusuvailable
	j->registerPresenceHandler( this );
	j->registerIqHandler(this, ExtVersion);
	j->registerIqHandler(this, ExtDiscoItems );
	j->registerIqHandler(this, ExtDiscoInfo);
	j->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);
	StringList ca;
	ca.push_back( "/pathto/cacert.crt" );
	j->setCACerts(ca);
	m_vManager = new VCardManager(j);
	database = new Database();
	database->start();

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
	run();	// opetovne pripojeni pri odhlaseni
}

void Bot::onConnect() {
}

bool Bot::onTLSConnect( const CertInfo& info ) {
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

	j->disco()->getDiscoInfo(jid,"", this,1,"");
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
		
void Bot::handleSelfPresence( const RosterItem& item, const std::string& resources, Presence::PresenceType presence, const std::string& msg ) {
}

bool Bot::handleSubscriptionRequest( const JID& jid, const std::string& ) {

	StringList groups;
	JID id(jid);
	j->rosterManager()->subscribe(id, "", groups, "" );
	return true;
}

bool Bot::handleUnsubscriptionRequest( const JID& jid, const std::string& ) {

	return true;
}

void Bot::handleNonrosterPresence( const Presence& presence ) {
}

void Bot::handleMessage( const Message& msg, MessageSession * /*session=0*/ )	{
	
	const PubSub::Event* pse = msg.findExtension<PubSub::Event>( ExtPubSubEvent );
	JID jid(msg.from());
	if( pse )
	{
		if(pse->type() == gloox::PubSub::EventItems)
		{
			Tag* p_tag = (pse->tag()->findChild("items"))->clone();
			string p_str = p_tag->findAttribute( "node" );
			if( p_str == "http://jabber.org/protocol/geoloc" )
			{
				Geoloc* geoloc = new Geoloc( p_tag );
				geoloc->jid(jid.full());
				database->insertTableGeoloc(geoloc);
			}
			else if( p_str == "http://jabber.org/protocol/tune" )
			{
				Tune* tune = new Tune( p_tag );
				tune->jid(jid.full());
				database->insertTableTune(tune);
			}
			else if( p_str == "http://jabber.org/protocol/mood" )
			{
				Mood* mood = new Mood( p_tag );
				mood->jid(jid.full());
				database->insertTableMood(mood);
			}
			else if( p_str == "http://jabber.org/protocol/activity" )
			{
				Activity* activity = new Activity( p_tag );
				activity->jid(jid.full());
				database->insertTableActivity(activity);
			}
		}
	}
	else if( !msg.body().empty() )
	{
		database->insertTableMessage( jid.bare().c_str(),  msg.body().c_str(),  msg.subject().c_str(), msg.thread().c_str(), messageSubtype(msg.subtype()).c_str() );
		int comm = command( msg.body(), jid.bare());
		if( comm == 1 )
		{
			if( msg.body() == COMMAND_USER )
			{
				Message mess( gloox::Message::Chat, msg.from(), database->printUser() );
				j->send( mess );
			}
			else if( msg.body() == COMMAND_RECONNECT )
				end();
		}
		else if( comm == 2)
		{
			Message mess( gloox::Message::Chat, msg.from(), NO_RIGHT);
			j->send( mess );
		}
		else if( comm == 3 )
		{
			Message mess( gloox::Message::Chat, msg.from(), database->select(msg.body(), msg.from().bare()));
			j->send( mess );
		}
	}
}
		
void Bot::handleLog( LogLevel level, LogArea area, const std::string& message ) {

	printf( "log level :%d, area :%d, %s\n", level, area, message.c_str() );
	if( area == LogAreaXmlIncoming || area == LogAreaXmlOutgoing )
		database->insertTableXML( level, area, message );
	else// if( area == LogAreaClassDns )      	//Debagovaci zprava
		database->insertTableDebug( level, area, message );
}


void Bot::handleVCard( const JID& jid, const VCard* v) {
// podivat jestli je dobre to V, jestli vubec nekdy nastane ze je prazdne
	if( !v )	//vcard je prazdny
		database->insertTableUser(jid.bare());
	else
	{
		database->insertTableVCard( v, jid.bare() );
		database->insertTableUser(jid.bare());
	}
}

void Bot::handleVCardResult( VCardContext context, const JID& jid, StanzaError se = StanzaErrorUndefined) {
}

void Bot::end() {

	j->disconnect();
	database->exitError();
}

void Bot::handleDiscoInfo( const JID& jidPom/*iq*/, const Disco::Info& info, int /*context*/ ) {

	Tag *queryTag = info.tag()->clone();
	SwVersion * swVersion = new SwVersion();
	swVersion->jid(jidPom.full());
 	if( queryTag->findAttribute("xmlns") == "http://jabber.org/protocol/disco#info" )
	{
		bool update = false;
		if(queryTag->hasChild("identity") )
		{
			update = true;
			Tag *identTag = queryTag->findChild("identity")->clone();
			swVersion->parserTagI( identTag );
		}
		if( queryTag->hasChild("x") )
		{
			update = true;
			Tag *xTag =  (queryTag->findChild("x"))->clone();
			swVersion->parserTagX( xTag );
		}

		if( queryTag->hasChild("feature") )
		{
			update = true;
			swVersion->parserTagF( queryTag );
		}

		if( update )
		{
			database->updateTableResource( swVersion );
			swVersion->clear();
		}
	}
}

void Bot::handleDiscoItems( const JID& /*iq*/, const Disco::Items&, int /*context*/ ) {
}

void Bot::handleDiscoError( const JID& /*iq*/, const Error*, int /*context*/ ) {
}


bool Bot::handleIq( const IQ &iq ) {

	if( (iq.tag()->findChild("query")))// && iq.tag()->findAttribute("type") != "error" )
	{
		Tag *queryTag = (iq.tag()->findChild("query"))->clone();

		SwVersion * swVersion = new SwVersion();
		JID jidPom( iq.tag()->findAttribute("from") );
		swVersion->jid(jidPom.full());
		if( queryTag->findAttribute("xmlns") == XMLNS_VERSION )
		{
			swVersion->parserTagVer( queryTag );
			database->updateTableResource( jidPom.bare(), jidPom.resource(), swVersion->name(), swVersion->version(), swVersion->os());
			swVersion->clear();
		}
	}
}

void Bot::handleIqID( const IQ &iq, int context  ) {

}


// Reakce na zmenu statusu uzivatele v kontakt listu
void Bot::handlePresence( const Presence& presence) {

	JID jidFull = presence.from();

	Roster* roster = j->rosterManager()->roster();
	if( roster->find(jidFull.bare()) != roster->end() )	//kontrola ze to poslal nekdo ze seznamu jiaignorace
	{
		if( presence.subtype() != 5 )
		{

			SwVersion * swVersion = new SwVersion();
			swVersion->jid(jidFull.full());
			database->insertTablePresence( jidFull.bare(), presence.status(), jidFull.username(), jidFull.resource(), presenceString(presence.subtype()), presence.priority(),
			                               swVersion->name(), swVersion->version(), swVersion->os() );
			swVersion->clear();
			if( (presence.findExtension( ExtCaps )) != 0 )
			{
				bool newResource = true;
				bool update = false;
				
				Tag * capTag = (presence.findExtension( ExtCaps ))->tag()->clone();
				if( capTag->hasAttribute("ver") )
				{
					string ver = capTag->findAttribute("ver");
					map<string, string>::iterator it;
					it = database->listVer.find(jidFull.full());
					if( it != database->listVer.end() )
					{
						if( ver == it->second )	// je vse aktualni
						{
							update = database->updateTableResource( jidFull.bare(), presenceString(presence.subtype()), presence.status(), jidFull.resource(), presence.priority());
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
						database->updateTableResource( jidFull.bare(), presenceString(presence.subtype()), presence.status(), jidFull.resource(), presence.priority(), ver);
					}
				}
			}
		}
		else
		{
			database->insertTablePresence( jidFull.bare(), presence.status(), jidFull.username(), jidFull.resource(), presenceString(presence.subtype()) );
			database->updateTableResource( jidFull.bare(), presenceString(presence.subtype()), presence.status(), jidFull.resource());
		}
		database->updateTableStatus(jidFull.bare());					// aktualizace tabulky Status na zakldade tabuly resource
	}
}

// Reakce na zmenu statusu uzivatele v kontakt listu
void Bot::handleRosterPresence( const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& msg ) {
		
}
