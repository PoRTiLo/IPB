//Hlavicka
#pragma once
#ifndef BOT_H__
#define BOT_H__



#include <gloox/lastactivity.h>
#include <gloox/loghandler.h>
#include <gloox/logsink.h>
#include <gloox/connectiontcpclient.h>
#include <gloox/connectionsocks5proxy.h>
#include <gloox/connectionhttpproxy.h>
#include <gloox/messagehandler.h>
#include <gloox/pubsubmanager.h>
#include <gloox/pubsubresulthandler.h>
#include <gloox/gloox.h>

#include <gloox/rostermanager.h>
#include <gloox/connectionlistener.h>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
//#include <gloox/component.h>
#include <gloox/presence.h>
#include <gloox/disco.h>
#include <gloox/discohandler.h>
#include <gloox/loghandler.h>
#include <gloox/logsink.h>
#include <gloox/message.h>
#include <gloox/messagesessionhandler.h>




#include "gloox/messageeventfilter.h"
#include "gloox/chatstatehandler.h"
#include "gloox/chatstatefilter.h"
#include "gloox/gloox.h"
#include "gloox/lastactivity.h"
#include "gloox/connectiontcpclient.h"
#include "gloox/connectionsocks5proxy.h"
#include "gloox/connectionhttpproxy.h"

#include <gloox/vcard.h>
#include <gloox/vcardhandler.h>
#include <gloox/vcardmanager.h>

#include <gloox/stanzaextension.h>
#include <gloox/iqhandler.h>
#include <gloox/eventhandler.h>
#include <gloox/messageeventhandler.h>
#include <gloox/pubsubmanager.h>
#include <gloox/pubsubevent.h>
#include <gloox/chatstate.h>
#include <string>
#include <fstream>
#include "errors.h"
#include "const.h"
#include "database.h"
#include "func.h"
#include "swversion.h"
#include "tune.h"
#include "tunefilter.h"

#include <gloox/pubsubmanager.h>
#include <gloox/pubsub.h>
#include <gloox/macros.h>
#include <unistd.h>
#include <gloox/pubsubresulthandler.h>
//#include "tunehandler.h"
using namespace gloox;
using namespace std;

extern bool g_global;
/**
 * 
 * 
 */
class Bot : public RosterListener, LogHandler, MessageHandler, ConnectionListener, VCardHandler,  DiscoHandler, IqHandler, PresenceHandler, MessageEventHandler, ChatStateHandler, EventHandler, PubSub::ResultHandler
{
	protected:
		string login;										// JID
		string pass;										// heslo pro prihlaseni
	private:
		Client* j;
		RosterManager* roster;
		MessageSession* m_session;
		VCardManager* m_vManager;
		Database* database;
		SwVersion* swVersion;
MessageEventFilter* m_messageEventFilter;
ChatStateFilter*  m_chatStateFilter;
EventDispatcher* m_event;
PubSub::Manager *m_pubsub;
//TuneFilter* m_tuneFilter;
		//StanzaExtension* m_stanzaExtension;
		int m_count;
	public:

virtual void handleChatState( const JID& from, ChatStateType state );
 virtual void handleMessageEvent( const JID& from, MessageEventType event );
		/**
		 * Konstruktor bezparametricky.
		 * Heslo a login budou vyplneny defaultnimi udaji (DEF_LOGIN, DEF_PASS).
		 */
		Bot();

		/**
		 * Konstruktor.
		 * @param[in] <string> login plne jmeno pro prihlaseni se do site
		 * @param[in] <string> pass heslo pro prihlaseni
		 */
		Bot(string login, string pass);

		/**
		 * Destruktor.
		 */
		~Bot();

		/**
		 * Nastaveni prihlasovaciho jmena JID.
		 * @param[in] <String> login prihlasovaci jmeno
		 */
		void setLogin( string login );

		/**
		 * Nastaveni prihlasovaciho hesla.
		 * @param[in] <string> pass helso pro uzivatelsky ucet
		 */
		void setPass( string pass );

		/**
		 *
		 *
		 *
		 */
//		void setToSoftware( string toName, string toVersion, string toOs );

		/**
		 *
		 *
		 */
//		string getToSoftwareName( void );

		/**
		 *
		 */
//		string getToSoftwareVersion( void );

		/**
		 *
		 */
//		string getToSoftwareOs( void );
	
		/**
		 * Vrati prihlasovaci jmeno.
		 * @return <string> vrati prihlasovaci jmeno
		 */
		string getLogin();

		/**
		 * Vrati prihlasovaci heslo.
		 * @return <string> prihlasovaci heslo
		 */
		string getPass();

		/**
		 * Vytvoreni klienta, pripojeni se k servu, prihlasi se k odberu logu. Inicializace a pripojeni k databazi.
		 */
		bool run();

		/**
		 * Odpojeni klienta bota od servu.
		 * @param <ConnectionError>
		 */
		virtual void onDisconnect( ConnectionError );

		/**
		 * Pripojeno.
		 */
		virtual void onConnect();

		/**
		 * Bezpecne pripojeni.
		 * @param[in] <CertInfo> &info Informace o certifikatu.
		 */
		virtual bool onTLSConnect( const CertInfo& info );

		/**
		 * 
		 */
		virtual void onResourceBindError( ResourceBindError );
		/**
		 * 
		 */
		virtual void onSessionCreateError( SessionCreateError error );
		/**
		 * 
		 */
		virtual void handleItemSubscribed( const JID& jid );
		/**
		 * 
		 */
		virtual void handleItemAdded( const JID& jid );
		/**
		 * 
		 */
		virtual void handleItemUnsubscribed( const JID& jid );
		/**
		 * 
		 */
		virtual void handleItemRemoved ( const JID& jid );
		/**
		 * 
		 */
		virtual void handleItemUpdated( const JID& jid );
		/**
		 * 
		 */
		virtual void handleRoster( const Roster& roster );
		/**
		 * 
		 */
		virtual void handleRosterError( const IQ& );
		/**
		 * 
		 */
		virtual void handleRosterPresence( const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& msg);

		/**
		 * Odchytava presenci odesilanou od bota (od nas k nekomu).
		 */
		virtual void handleSelfPresence( const RosterItem& item, const std::string& resources, Presence::PresenceType presence, const std::string& msg);
		/**
		 * 
		 */
		virtual bool handleSubscriptionRequest( const JID& jid, const std::string& );
		/**
		 * 
		 */
		virtual bool handleUnsubscriptionRequest( const JID& jid, const std::string& );
		/**
		 * 
		 */
		virtual void handleNonrosterPresence( const Presence& presence );
		/**
		 * 
		 */
		virtual void handleMessage( const Message& message, MessageSession * /*session=0*/ );
		/**
		 * 
		 */
		virtual void handleLog( LogLevel level, LogArea area, const std::string& message );

		/**
		 *
		 */
		virtual void handleVCard( const JID& jid, const VCard* v );

		/**
		 *
		 */
		virtual void handleVCardResult( VCardContext context, const JID& jid, StanzaError se );

		virtual void handleMessageSession( MessageSession* session );

		/**
		 * Prevod typu zpravy na text.
		 * @param[in] <inst> subtype Typ zpravy.
		 * @return <string> Textova reprezentace typu zpravy.
		 */
		string messageSubtype( const int subtype );

		/**
		 * Prevod typu presence na text.
		 * @param[in] <int> presence Typ presence.
		 * @return <string> Textove reprezentace typu presence.
		 */
		string presenceString( const int presence );

		void end();
	 	virtual void handleDiscoInfo( const JID& /*iq*/, const Disco::Info&, int /*context*/ );
	   virtual void handleDiscoItems( const JID& /*iq*/, const Disco::Items&, int /*context*/ );
		virtual void handleDiscoError( const JID& /*iq*/, const Error*, int /*context*/ );
		virtual bool handleIq 	( 	const IQ & 	iq 	 );
		virtual void handleIqID 	( 	const IQ & 	iq, 
				int 	context
					);

		virtual void handlePresence( const Presence& presence );
      virtual void handleTune( const JID& from, TuneType state );
		virtual void handleEvent( const Event& event );
		/*
		 void handleNodeCreationResult( const JID& service,  const std::string& node, const Error& e );

	virtual void handleNodeDeletationResult( const JID& service, const std::string& node,  const Error& e );

	virtual void handleNodePurgeResult( const JID& service, const std::string& node, const Error& e );

 virtual void handleSubscriptionOptions( const JID& service, const JID& jid, const std::string& node, const DataForm& options );
 virtual void handleSubscriptionOptionsResult( const JID& service, //const JID& jid, 
 	const std::string& node,const Error& e );

	virtual void handleSubscriberList( const JID& service, const std::string& node, const PubSub::SubscriberList& list );

 virtual void handleSubscriberListResult( const JID& service, const std::string& node, const Error& e );
 virtual void handleAffiliateList( const JID& service, const std::string& node, const PubSub::AffiliateList& list );

virtual void handleAffiliateListResult( const JID& service, const std::string& node, const Error& e );
virtual void handleNodeConfig( const JID& service, const std::string& node, const DataForm& config );
 virtual void handleNodeConfigResult( const JID& service, const std::string& node,const Error& e );
 */
 
virtual void 	handleItem (const JID &service, const std::string &node, const Tag *entry);
virtual void 	handleItems (const std::string &id, const JID &service, const std::string &node, const PubSub::ItemList &itemList, const Error *error=0);
virtual void 	handleItemPublication (const std::string &id, const JID &service, const std::string &node, const PubSub::ItemList &itemList, const Error *error=0);
virtual void 	handleItemDeletion (const std::string &id, const JID &service, const std::string &node, const PubSub::ItemList &itemList, const Error *error=0);
virtual void 	handleSubscriptionResult (const std::string &id, const JID &service, const std::string &node, const std::string &sid, const JID &jid, const PubSub::SubscriptionType subType, const Error *error=0);
virtual void 	handleUnsubscriptionResult (const std::string &id, const JID &service, const Error *error=0);
virtual void 	handleSubscriptionOptions (const std::string &id, const JID &service, const JID &jid, const std::string &node, const DataForm *options,const std::string& stri, const Error *error=0);
virtual void 	handleSubscriptionOptionsResult (const std::string &id, const JID &service, const JID &jid, const std::string &node,const std::string& s, const Error *error=0);
virtual void 	handleSubscribers (const std::string &id, const JID &service, const std::string &node, const PubSub::SubscriberList *list, const Error *error=0);
virtual void 	handleSubscribersResult (const std::string &id, const JID &service, const std::string &node, const PubSub::SubscriberList *list, const Error *error=0);
virtual void 	handleAffiliates (const std::string &id, const JID &service, const std::string &node, const PubSub::AffiliateList *list, const Error *error=0);
virtual void 	handleAffiliatesResult (const std::string &id, const JID &service, const std::string &node, const PubSub::AffiliateList *list, const Error *error=0);
virtual void 	handleNodeConfig (const std::string &id, const JID &service, const std::string &node, const DataForm *config, const Error *error=0);
virtual void 	handleNodeConfigResult (const std::string &id, const JID &service, const std::string &node, const Error *error=0);
virtual void 	handleNodeCreation (const std::string &id, const JID &service, const std::string &node, const Error *error=0);
virtual void 	handleNodeDeletion (const std::string &id, const JID &service, const std::string &node, const Error *error=0);
virtual void 	handleNodePurge (const std::string &id, const JID &service, const std::string &node, const Error *error=0);
virtual void 	handleSubscriptions (const std::string &id, const JID &service, const PubSub::SubscriptionMap &subMap, const Error *error=0);
virtual void 	handleAffiliations (const std::string &id, const JID &service, const PubSub::AffiliationMap &affMap, const Error *error=0);
virtual void 	handleDefaultNodeConfig (const std::string &id, const JID &service, const DataForm *config, const Error *error=0);

};
#endif //BOT_H__

