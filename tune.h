#ifndef TUNE_H__
#define TUNE_H__

#include <gloox/tag.h>
#include <gloox/jid.h>

#include <string>

#include "func.h"

using namespace std;
using namespace gloox;

class Tune
{

	protected:
		string m_artist;
		short int m_length;
		unsigned int m_rating;
		string m_source;
		string m_title;
		string m_track;
		string m_uri;
		string m_id;
		JID m_jid;

	public:
      /**
       * Constructs a new object from the given Tag.
       * @param tag A Tag to parse.
       */
      Tune( const Tag* tag );

      /**
       * Virtual destructor.
       */
      virtual ~Tune() {}

		
		string artist( void );
		void artist( const string artist );

		short int length( void );
		void length( const short int length );

		unsigned int rating( void );
		void rating( const unsigned int rating );

		string source( void );
		void source( const string source );

		string title( void );;
		void title( const string title );

		string track( void );
		void track( const string track );

		string uri( void );
		void uri( const string uri );

		string id( void );
		void id( const string id );

		JID jid( void );
		void jid( const string jid );

		void parserTag( const Tag * tag );

		void clear( void );
};


#endif // TUNE_H__
