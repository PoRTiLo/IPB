#ifndef ACTIVITY_H__
#define ACTIVITY_H__

#include <gloox/tag.h>
#include <gloox/jid.h>

#include <string>
#include <list>
#include "func.h"

using namespace std;
using namespace gloox;

class Activity
{

	protected:

		static const string m_activityTab[11][13];
		string m_activity;
		string m_spec;
		string m_text;
		string m_id;
		JID m_jid;

	public:
      /**
       * Constructs a new object from the given Tag.
       * @param tag A Tag to parse.
       */
      Activity( const Tag* tag );

      /**
       * Virtual destructor.
       */
      virtual ~Activity() {}

		
		string activity( void );
		void activity( const string activity );

		string spec( void );
		void spec( const string spec );

		string text( void );
		void text( const string text );

		string id( void );
		void id( const string id );

		JID jid( void );
		void jid( const string jid );

		void parserTag( const Tag * tag );
};


#endif // MOOD_H__
