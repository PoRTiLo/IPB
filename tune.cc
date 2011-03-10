#include "tune.h"
#include <gloox/tag.h>
#include <gloox/util.h>

//namespace gloox
//{

  /* chat state type values */
  static const char* stateValues [] = {
    "active",
    "composing",
    "paused",
    "inactive",
    "gone"
  };

  static inline TuneType tuneType( const std::string& type )
  {
    return (TuneType)util::lookup2( type, stateValues );
  }

  Tune::Tune( const Tag* tag )
    : StanzaExtension( ExtChatState ),
      m_state( TuneInvalid )
  {
    if( tag )
      m_state = tuneType( tag->name() );
  }

  const std::string& Tune::filterString() const
  {
    static const std::string filter =
           "/message/active[@xmlns='" + XMLNS_CHAT_STATES + "']"
           "|/message/composing[@xmlns='" + XMLNS_CHAT_STATES + "']"
           "|/message/paused[@xmlns='" + XMLNS_CHAT_STATES + "']"
           "|/message/inactive[@xmlns='" + XMLNS_CHAT_STATES + "']"
           "|/message/gone[@xmlns='" + XMLNS_CHAT_STATES + "']";
    return filter;
  }

  Tag* Tune::tag() const
  {
    if( m_state == TuneInvalid )
      return 0;

    return new Tag( util::lookup2( m_state, stateValues ), XMLNS, XMLNS_CHAT_STATES );
  }

//}
