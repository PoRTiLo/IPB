//example from gloox....

#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
using namespace gloox;

class Bot : public MessageHandler
{
   public:
      Bot()
      {
         JID jid( "portilo@jabbim.cz/ipb1" );
         cerr << jid << endl;
         j = new Client( jid, "javier" );
         j->registerMessageHandler( this );
         j->setPresence( PresenceAvailable, 5 );
         j->connect();
      }
      virtual void handleMessage( Stanza* stanza,
                                  MessageSession* session = 0 )
      {
         Stanza *s = Stanza::createMessageStanza(
            stanza->from().full(), "hello world" );
         j->send( s );
      }
   private:
      Client* j;
};

int main( int argc, char* argv[] )
{
   Bot b;
   int kocka;
} 

