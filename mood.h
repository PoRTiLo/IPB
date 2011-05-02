#ifndef MOOD_H__
#define MOOD_H__

#include "extension.h"

using namespace gloox;

/**
 * Trida reprezentujici XEP-0107: User Mood
 */
class Mood : public Extension
{

	protected:

		static const std::string m_moodTab[];				// tabulka se vsema moodama
		std::string m_mood;										// mood hodnota
		std::string m_text;										// dodatecny text stavu

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
		 * Rozparsrovani prichozi zpravy.
		 * @param<Tag> tag xml zparva.
		 */
		virtual void parserTag( const Tag * tag );

		/**
		 * Vymazani atributu.
		 */
		virtual void clear( void );
};


#endif // MOOD_H__
