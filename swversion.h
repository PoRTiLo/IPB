#pragma once
#ifndef VERSION_H__
#define VERSION_H__


#include <gloox/iq.h>
#include <string>
using namespace std;
using namespace gloox;


/**
Trida implementujici rozparsrovani XEP-0092 a XEP-0115.

<iq type='get'
	 from='romeo@montague.net/orchard'
	 to='juliet@capulet.com/balcony'
	 id='version_1'
	 xml:lang="en-US">
	 <query xmlns='jabber:iq:version'/>
</iq>
*/

class SwVersion
{
	private:
		string m_name;
		string m_version;
		string m_os;
		bool m_ip4;
		bool m_ip6;
		string m_osVersion;
		string m_category;
		string m_software;
		string m_type;

	public:
		/**
		 * Nastaveni udaje pro odeslani pozadavku.
		 * @param[in] <string> toJid prihlasovaci udaj prijimaciho klienta.
		 */
		void setName( string name );

		/**
		 * Nastaveni resource prijimaciho klienta.
		 * @param[in] <string> toResource prijimaci resource.
		 */
		void setVersion( string version );

		/**
		 * JID prijemce.
		 * @return <string> jid prijemce.
		 */
		void setOs( string os );

		void setIP4( bool ip4 );
		void setIP6( bool ip6 );
		void setOsVersion( string osVersion );
		void setCategory( string category );
		void setSoftware( string software );
		void setType( string type );

		string name( void );

		string version( void );

		string os( void );

		string osVersion( void );

		bool ip4( void );

		bool ip6( void );

		string category( void );

		string software( void );

		string type( void );
		/**
		 * Resource prijemce.
		 * @return <string> resource prijemce.
		 */
//		string getResource( void );

		/**
		 * Konstruktor.
		 * @param[in] <string> toJid JID prijemce.
		 * @param[in] <string> toResource Resource prijemce.
		 */
		SwVersion( string m_name, string m_version, string m_os );

		SwVersion(){};

		/**
		 * Vytvoreni zpravy IQ. Zadost o poslani informaci o software.
		 * @from[in] <string> from JID odesilatele.
		 * @return <Tag> Kompletni xml zprava.
		 */
		Tag* createIqStanza( string from, string toJid, string toResource );

		virtual const string& filterString () const;
	   virtual StanzaExtension * 	newInstance (const Tag *tag) const ;
		virtual Tag * 	tag () const; 
virtual StanzaExtension * 	clone () const;



void parserTagX( const Tag * tag );
};

#endif //VERSION_H__
