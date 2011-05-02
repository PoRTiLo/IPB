#ifndef ACTIVITY_H__
#define ACTIVITY_H__

#include "extension.h"

using namespace gloox;

/**
 * Implementace rozsireni XEP-108: User Activity
 */
class Activity : public Extension
{

	protected:

		static const std::string m_activityTab[11][13];
		std::string m_activity;
		std::string m_spec;
		std::string m_text;

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

		
		std::string activity( void );
		void activity( const std::string activity );

		std::string spec( void );
		void spec( const std::string spec );

		std::string text( void );
		void text( const std::string text );

		/**
		 * Rozparsrovani xml zpravy.
		 * @param[in]<Tag> *tag xml zprava.
		 */
		virtual void parserTag( const Tag * tag );
	
		virtual void clear( void);
};


#endif // ACTIVITY_H__
