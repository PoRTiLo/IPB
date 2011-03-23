#ifndef SWVERSION_H__
#define SWVERSION_H__


#include <gloox/iq.h>
#include <string>
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
	protected:
		std::string m_name;
		std::string m_version;
		std::string m_os;
		bool m_ip4;
		bool m_ip6;
		std::string m_osVersion;
		std::string m_category;
		std::string m_software;
		std::string m_type;

	public:
		/**
		 * Nastaveni udaje pro odeslani pozadavku.
		 * @param[in] <std::string> toJid prihlasovaci udaj prijimaciho klienta.
		 */
		void name( std::string name );

		/**
		 * Nastaveni resource prijimaciho klienta.
		 * @param[in] <std::string> toResource prijimaci resource.
		 */
		void version( std::string version );

		/**
		 * JID prijemce.
		 * @return <std::string> jid prijemce.
		 */
		void os( std::string os );

		void ip4( bool ip4 );
		void ip6( bool ip6 );
		void osVersion( std::string osVersion );
		void category( std::string category );
		void software( std::string software );
		void type( std::string type );

		std::string name( void );

		std::string version( void );

		std::string os( void );

		std::string osVersion( void );

		bool ip4( void );

		bool ip6( void );

		std::string category( void );

		std::string software( void );

		std::string type( void );
		/**
		 * Resource prijemce.
		 * @return <std::string> resource prijemce.
		 */
//		std::string getResource( void );

		/**
		 * Konstruktor.
		 * @param[in] <std::string> toJid JID prijemce.
		 * @param[in] <std::string> toResource Resource prijemce.
		 */
		SwVersion( std::string m_name, std::string m_version, std::string m_os );

		SwVersion(){};

		/**
		 * Vytvoreni zpravy IQ. Zadost o poslani informaci o software.
		 * @from[in] <std::string> from JID odesilatele.
		 * @return <Tag> Kompletni xml zprava.
		 */
		Tag* createIqStanza( std::string from, std::string toJid, std::string toResource );

		void parserTag( const Tag * tag );
};

#endif //SWVERSION_H__
