#ifndef ACTIVITY_H__
#define ACTIVITY_H__

#include <gloox/tag.h>
#include <gloox/jid.h>

#include <string>
#include "func.h"

using namespace gloox;

/**
 * Implementace rozsireni XEP-108: User Activity
 */
class Activity
{

	protected:

		static const std::string m_activityTab[11][13];
		std::string m_activity;
		std::string m_spec;
		std::string m_text;
		std::string m_id;
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

		
		std::string activity( void );
		void activity( const std::string activity );

		std::string spec( void );
		void spec( const std::string spec );

		std::string text( void );
		void text( const std::string text );

		std::string id( void );
		void id( const std::string id );

		JID jid( void );
		void jid( const std::string jid );

		/**
		 * Rozparsrovani xml zpravy.
		 * @param[in]<Tag> *tag xml zprava.
		 */
		void parserTag( const Tag * tag );
};


#endif // ACTIVITY_H__
