#pragma once
#ifndef VERSION_H__
#define VERSION_H__


#include <gloox/iq.h>
#include <string>
using namespace std;
using namespace gloox;


/**
Trida implementujici XEP-0092.

<iq type='get'
	 from='romeo@montague.net/orchard'
	 to='juliet@capulet.com/balcony'
	 id='version_1'
	 xml:lang="en-US">
	 <query xmlns='jabber:iq:version'/>
</iq>
*/

class Version 
{
	private:
		string jid;									// JID prijemce
		string resource;							// resource prijemece
	protected:

		/**
		 * Nastaveni udaje pro odeslani pozadavku.
		 * @param[in] <string> toJid prihlasovaci udaj prijimaciho klienta.
		 */
		void setJid( string toJid );

		/**
		 * Nastaveni resource prijimaciho klienta.
		 * @param[in] <string> toResource prijimaci resource.
		 */
		void setResource( string toResource );

		/**
		 * JID prijemce.
		 * @return <string> jid prijemce.
		 */
		string getJid( void );

		/**
		 * Resource prijemce.
		 * @return <string> resource prijemce.
		 */
		string getResource( void );

	public:
		/**
		 * Konstruktor.
		 * @param[in] <string> toJid JID prijemce.
		 * @param[in] <string> toResource Resource prijemce.
		 */
		Version( string toJid, string toResource );

		/**
		 * Vytvoreni zpravy IQ. Zadost o poslani informaci o software.
		 * @from[in] <string> from JID odesilatele.
		 * @return <Tag> Kompletni xml zprava.
		 */
		Tag* createIqStanza( string from );
};

#endif //VERSION_H__
