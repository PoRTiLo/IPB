#include "tunefilter.h"
#include "tunehandler.h"
#include <gloox/messageeventhandler.h>
#include <gloox/messagesession.h>
#include <gloox/message.h>
#include "tune.h"


  TuneFilter::TuneFilter( MessageSession* parent )
    : MessageFilter( parent ), m_tuneHandler( 0 ), m_lastSent( TuneGone ),
      m_enableTunes( true )
  {
  }

  TuneFilter::~TuneFilter()
  {
  }

  void TuneFilter::filter( Message& msg )
  {
    if( m_enableTunes && m_tuneHandler )
    {
    //  const Tune* state = msg.findExtension<Tune>( ExtTune );

    //  m_enableTunes = state && state->state() != TuneInvalid;
    //  if( m_enableTunes && msg.body().empty() )
    //    m_tuneHandler->handleTune( msg.from(), state->state() );
    }
  }

  void TuneFilter::setTune( TuneType state )
  {
    if( !m_enableTunes || state == m_lastSent || state == TuneInvalid )
      return;

    Message m( Message::Chat, m_parent->target() );
//    m.addExtension( new Tune( state ) );

    m_lastSent = state;

    send( m );
  }

  void TuneFilter::decorate( Message& msg )
  {
    if( m_enableTunes );
 //     msg.addExtension( new Tune( TuneActive ) );
  }

