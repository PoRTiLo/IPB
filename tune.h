#ifndef TUNE_H__
#define TUNE_H__

#include <gloox/gloox.h>
#include <gloox/stanzaextension.h>
#include <gloox/tag.h>

#include <string>

#include "const.h"

using namespace gloox;
  class gloox::Tag;

  class Tune : public StanzaExtension
  {
    public:
      /**
       * Constructs a new object from the given Tag.
       * @param tag A Tag to parse.
       */
      Tune( const Tag* tag );

      /**
       * Constructs a new object of the given type.
       * @param state The chat state.
       */
      Tune( TuneType state )
        : StanzaExtension( ExtChatState ), m_state( state )
      {}

      /**
       * Virtual destructor.
       */
      virtual ~Tune() {}

      /**
       * Returns the object's state.
       * @return The object's state.
       */
      TuneType state() const { return m_state; }

      // reimplemented from StanzaExtension
      virtual const std::string& filterString() const;

      // reimplemented from StanzaExtension
      virtual StanzaExtension* newInstance( const gloox::Tag* tag ) const
      {
        return new Tune( tag );
      }

      // reimplemented from StanzaExtension
      Tag* tag() const;

      // reimplemented from StanzaExtension
      virtual StanzaExtension* clone() const
      {
        return new Tune( *this );
      }

    private:
      TuneType m_state;

  };

//}

#endif // CHATSTATE_H__
