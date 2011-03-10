#ifndef CHATSTATEHANDLER_H__
#define CHATSTATEHANDLER_H__

#include <gloox/gloox.h>
#include <gloox/jid.h>
#include "const.h"

using namespace gloox;

class gloox::JID;

class TuneHandler
{
	public:
		virtual ~TuneHandler() {}

		virtual void handleTune( const JID& from, TuneType state ) = 0;

};


#endif // TUNEHANDLER_H__
