#ifndef TUNE_H__
#define TUNE_H__

#include <gloox/tag.h>
#include <gloox/jid.h>

#include <string>

#include "func.h"

using namespace gloox;

/**
 * Implementace XEP-0118: User Tune
 */
class Tune
{

	protected:
		std::string m_artist;
		short int m_length;
		unsigned int m_rating;
		std::string m_source;
		std::string m_title;
		std::string m_track;
		std::string m_uri;
		std::string m_id;
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

		
		std::string artist( void );
		void artist( const std::string artist );

		short int length( void );
		void length( const short int length );

		unsigned int rating( void );
		void rating( const unsigned int rating );

		std::string source( void );
		void source( const std::string source );

		std::string title( void );;
		void title( const std::string title );

		std::string track( void );
		void track( const std::string track );

		std::string uri( void );
		void uri( const std::string uri );

		std::string id( void );
		void id( const std::string id );

		JID jid( void );
		void jid( const std::string jid );

		void parserTag( const Tag * tag );

		void clear( void );
};


#endif // TUNE_H__
