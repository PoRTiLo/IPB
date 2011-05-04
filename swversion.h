#ifndef SWVERSION_H__
#define SWVERSION_H__


#include <gloox/iq.h>
#include "extension.h"
#include <iostream>
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

class SwVersion : public Extension
{
	protected:
		std::string m_name;
		std::string m_version;
		std::string m_os;
		bool m_ip4;
		bool m_ip6;
		std::string m_osVersion;
		std::string m_category;
		std::string m_type;
		std::string m_jingleVoice;	//	urn:xmpp:jingle:apps:rtp:audio
		std::string m_jingleVideo;	//	urn:xmpp:jingle:apps:rtp:video
		std::string m_googleVoice;	//	http://www.google.com/xmpp/protocol/voice/v1
		std::string m_googleVideo;	//	http://www.google.com/xmpp/protocol/video/v1

	public:
		
		std::string jingleVoice( void );
		std::string jingleVideo( void );
		std::string googleVideo( void );
		std::string googleVoice( void );
		void jingleVoice( std::string voice );
		void jingleVideo( std::string video );
		void googleVoice( std::string voice );
		void googleVideo( std::string video );
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

		void os( std::string os );

		void ip4( bool ip4 );
		void ip6( bool ip6 );
		void osVersion( std::string osVersion );
		void category( std::string category );
		void type( std::string type );

		std::string name( void );

		std::string version( void );

		std::string os( void );

		std::string osVersion( void );

		bool ip4( void );

		bool ip6( void );

		std::string category( void );

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
		SwVersion( );
		SwVersion( const Tag* tag );


		/**
		 * Vytvoreni zpravy IQ. Zadost o poslani informaci o software.
		 * @from[in] <std::string> from JID odesilatele.
		 * @return <Tag> Kompletni xml zprava.
		 */
		Tag* createIqStanza( std::string from, std::string toJid, std::string toResource );


		virtual void parserTag( const Tag* tag );

		virtual void clear( void );

		void parserTagX( const Tag* tag );
		void parserTagI( const Tag* tag );
		void parserTagVer( const Tag* tag );
		void parserTagF( const Tag* tag );

};

#endif //SWVERSION_H__
