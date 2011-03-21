#ifndef MOOD_H__
#define MOOD_H__

#include <gloox/tag.h>
#include <gloox/jid.h>

#include <string>
#include <list>
#include "func.h"

using namespace std;
using namespace gloox;

class Mood
{

	protected:

		static const string m_moodTab[];
		string m_mood;
		string m_text;
		string m_id;
		JID m_jid;

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

		
		string mood( void );
		void mood( const string mood );

		string text( void );
		void text( const string text );

		string id( void );
		void id( const string id );

		JID jid( void );
		void jid( const string jid );

		void parserTag( const Tag * tag );
};


#endif // MOOD_H__
