//Hlavicka
#pragma once
#ifndef BOT_H__
#define BOT_H__

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






#include "gloox/messagesessionhandler.h"
#include "gloox/messageeventhandler.h"
#include "gloox/messageeventfilter.h"
#include "gloox/chatstatehandler.h"
#include "gloox/chatstatefilter.h"
#include "gloox/connectionlistener.h"
#include "gloox/disco.h"
#include "gloox/message.h"
#include "gloox/gloox.h"
#include "gloox/lastactivity.h"
#include "gloox/loghandler.h"
#include "gloox/logsink.h"
#include "gloox/connectiontcpclient.h"
#include "gloox/connectionsocks5proxy.h"
#include "gloox/connectionhttpproxy.h"
#include "gloox/messagehandler.h"

#include <gloox/vcard.h>
#include <gloox/vcardhandler.h>
#include <gloox/vcardmanager.h>



#include <string>
#include <fstream>

#include "errors.h"
#include "const.h"
#include "database.h"

#define DEF_LOGIN "konsole@localhost"
#define DEF_PASS "javier"


using namespace gloox;
using namespace std;

/**
 * 
 * 
 */
class Bot : public RosterListener, LogHandler, MessageHandler, ConnectionListener, VCardHandler
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
		int m_count;
	public:
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
		~Bot(){}

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
		 *
		 */
		bool run();
		/**
		 * 
		 */
		virtual void onDisconnect( ConnectionError );
		/**
		 * 
		 */
		virtual void onConnect();
		/**
		 * 
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
		virtual void handleRosterPresence( const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& );
		/**
		 * 
		 */
		virtual void handleSelfPresence( const RosterItem& item, const std::string& resources, Presence::PresenceType presence, const std::string& );
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
};	

#endif //BOT_H__
