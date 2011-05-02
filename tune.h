#ifndef TUNE_H__
#define TUNE_H__

#include "extension.h"

using namespace gloox;

/**
 * Implementace XEP-0118: User Tune
 */
class Tune : public Extension
{

	protected:
		std::string m_artist;
		short int m_length;
		unsigned int m_rating;
		std::string m_source;
		std::string m_title;
		std::string m_track;
		std::string m_uri;

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

		std::string title( void );
		void title( const std::string title );

		std::string track( void );
		void track( const std::string track );

		std::string uri( void );
		void uri( const std::string uri );

		virtual void parserTag( const Tag * tag );

		virtual void clear( void );
};

#endif // TUNE_H__
