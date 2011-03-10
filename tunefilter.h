#ifndef TUNEFILTER_H__
#define TUNEFILTER_H__

#include <gloox/messagefilter.h>
#include <gloox/gloox.h>
#include <gloox/tag.h>
#include "const.h"

#include "tunehandler.h"
using namespace gloox;

  class gloox::Tag;
  class TuneHandler;
  class gloox::MessageSession;
  class gloox::Message;

  class TuneFilter : public MessageFilter
  {
    public:

      TuneFilter( MessageSession* parent );

      virtual ~TuneFilter();

      void setTune( TuneType state );

      void registerTuneHandler( TuneHandler* csh )
        { m_tuneHandler = csh; }

      void removeTuneHandler()
        { m_tuneHandler = 0; }

      // reimplemented from MessageFilter
      virtual void decorate( gloox::Message& msg );

      // reimplemented from MessageFilter
      virtual void filter( gloox::Message& msg );

    protected:
      /** A handler for incoming chat state changes. */
      TuneHandler* m_tuneHandler;

      /** Holds the state sent last. */
      TuneType m_lastSent;

      /** Indicates whether or not chat states are currently enabled. */
      bool m_enableTunes;

  };

#endif // CHATSTATEFILTER_H__
