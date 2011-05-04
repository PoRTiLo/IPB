/**
 *@file extension.h
 *@brief Trida implementujici rozsireni.
 */

#ifndef EXTENSION_H__
#define EXTENSION_H__

#include <gloox/tag.h>
#include <gloox/jid.h>

#include <string>

#include "func.h"

using namespace gloox;

/**
 * Implementace rozsireni. Trida z ktere vechna implementovana rozsireni dedi.
 */
class Extension
{

	protected:
		std::string m_id;
		JID m_jid;

	public:

      /**
       * Konstruktor.
		 * @param[in]<Tag*> tag k rozparsrovani.
       */
      Extension( const Tag* tag ) {}
      Extension( ) {}

      /**
       * Virtualni destructor.
       */
      virtual ~Extension() {}

		/**
		 * Vraci id rozsireni.
		 * @return <string> identifikace elementu.
		 */
		std::string id( void ) { return m_id; }

		/**
		 * Nastaveni id.
		 * @param[in]<string> id identifikace elementu.
		 */
		void id( const std::string id ) { m_id = id; }

		/**
		 * Vraci uzivatelske jmeno klienta.
		 * @return <JID> jid uzivatele.
		 */
		JID jid( void ) const { return m_jid;}

		/**
		 * Nastaveni JID uzivatele.
		 * @param[in] <string> jid uzivatele.
		 */
		void jid( const std::string jid ) { m_jid.setJID(jid); }

		/**
		 * Rozparsrovani xml tagu
		 * @param[in] <Tag*> tag xml element.
		 */
		virtual void parserTag( const Tag* tag ) = 0;

		/**
		 * Vymazani elementu m_id a m_jid.
		 */
		virtual void clear( void ) = 0;
};

#endif // EXTENSION_H__
