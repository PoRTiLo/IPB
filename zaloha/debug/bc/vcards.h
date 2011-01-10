#pragma once

#ifndef VCARD_H__
#define VCARD_H__

#include <gloox/gloox.h>
#include <gloox/vcard.h>
#include <gloox/client.h>
#include <gloox/vcardmanager.h>
#include <gloox/vcardhandler.h>

#include <fstream>

using namespace std;
using namespace gloox;

/**
 *
 *
 */
class VCards: public VCardHandler
{
	private:
		VCardManager *m_vManager;
		int m_count;
		Client *j;
		JID jid;

	public:
		/**
		 *
		 */
		VCards( JID jid, Client* j);
		/**
		 *
		 */
		virtual ~VCards(){}

		/**
		 *
		 */
		void start( const char*  jid ); 
		/**
		 *
		 */
		virtual void handleVCard( const JID& jid, const VCard* v );

		/**
		 *
		 */
		virtual void handleVCardResult( VCardContext context, const JID& jid, StanzaError se );

};

#endif //VCARD_H__
