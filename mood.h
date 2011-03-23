#ifndef MOOD_H__
#define MOOD_H__

#include <gloox/tag.h>
#include <gloox/jid.h>

#include <string>
#include "func.h"

using namespace gloox;

/**
 * Trida reprezentujici XEP-0107: User Mood
 */
class Mood
{

	protected:

		static const std::string m_moodTab[];				// tabulka se vsema moodama
		std::string m_mood;										// mood hodnota
		std::string m_text;										// dodatecny text stavu
		std::string m_id;											// id
		JID m_jid;													// jid uzivatele

	public:
      /**
       * Constructs a new object from the given Tag.
       * @param tag A Tag to parse.
       */
      Mood( const Tag* tag );

      /**
       * Virtual destructor.
       */
      virtual ~Mood() {}

		/**
		 * Vrati hodnotu modu.
		 * @return <string>.
		 */
		std::string mood( void );

		/**
		 * Nastaveni hodnoty moodu.
		 * @parama[in]<string> mood hodnota modu.
		 */
		void mood( const std::string mood );

		/**
		 * Vrati hodnotu text.
		 * @return<string> text hodnota textu.
		 */
		std::string text( void );

		/**
		 * Nastavi doplnujici text.
		 * @param[in]<string> text hodnota textu.
		 */
		void text( const std::string text );

		/**
		 * Vrati ID.
		 * @return<string> id.
		 */
		std::string id( void );

		/**
		 * Nastavi Id.
		 * @param[in]<string> id.
		 */
		void id( const std::string id );

		/**
		 * Uzivatelsky login.
		 * @return<JID> jid login uzivatele.
		 */
		JID jid( void );

		/**
		 * Nastaveni uzivatelskeho loginu.
		 * @param<string> jid.
		 */
		void jid( const std::string jid );

		/**
		 * Rozparsrovani prichozi zpravy.
		 * @param<Tag> tag xml zparva.
		 */
		void parserTag( const Tag * tag );
};


#endif // MOOD_H__
