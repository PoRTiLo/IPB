//example from gloox....

#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/disco.h>
#include <string>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <gloox/component.h>
#include <ncurses.h>
#include <gloox/connectionlistener.h>
#include <gloox/rostermanager.h>
using namespace std;
using namespace gloox;

class Bot : public MessageHandler, ConnectionListener  //dedi z MessageHandler
{
   public:
      Bot();
      Bot(string login, string pass)
      {
         JID jid( login );
         j = new Client( jid, pass );
         j->registerConnectionListener( this );
         j->registerMessageHandler( this );
         j->disco()->setVersion("Pokus", "0.0.1", "UBUNTU"); //zaobrazi se v infu, nazev, verze, system
         j->disco()->setIdentity( "client", "bot" );
         j->setPresence( PresenceAvailable, 5 );   //Nastaveni statusu
         roster = new RosterManager(j); 
         cerr<<"item:"<<roster->getRosterItem(jid)<<".."<<endl; 

         
         if( !j->connect() )  //kontrola spojeni se servrem
         {
           cerr << "chyba, zadal jste spatne uzivatelske jmeno" << endl;
         }
      }




     virtual void handleMessage( Stanza* stanza, MessageSession* session = 0 ) {   //reaguje na prisle zpravy
           
           cerr << "ch" << endl;
         JID from = stanza->from().full();
         cerr << "bare "<<from.bare()<<endl;
         cerr << "stanza-from() " << from << endl;
         JID poslat("bot-jeryy@portilo-laptop");
         Stanza *s = Stanza::createMessageStanza(poslat, stanza->body() );  //posle vsem kontaktum......
         j->send( s );

      }
      virtual void onDisconnect( ConnectionError /*e*/ ) {
        cerr << j->authError()<<endl;
         cerr << j->streamErrorText()<<endl;
         printf("chyab spojeni \n"); 
      }
      virtual void onConnect() {

      }

      virtual bool onTLSConnect( const CertInfo& info ) {
         printf( "info %d:\n ",info.status);
         return true;
      }

// debugovaci fce
      virtual void handleLog( LogLevel level, LogArea area, const std::string& message ) {
         printf( "log level :%d, area :%d, %s\n", level, area, message.c_str() );
      }
   


   private:
      Client* j;
      RosterManager* roster;
};

int main( int argc, char* argv[] )
{
//rozparsrovat login
   string login = argv[1];
   char heslo[80];

   initscr();  //rozpozna typ terminalu, inicializuje curses datove struktury, vymaze obrazovku

   printw("Zadejte heslo : ");

   cbreak();   //znaky na vystupu nesou bufrovany, jsou okamzite k dispozice programu
   noecho();   //nepise znaky na terminal

   getstr(heslo); //nacte heslo

   endwin();   //nastavi terminal do puvodniho stavu

   cerr << login << ":" << heslo << endl;

   stringstream ss;  ss << heslo;  string pass;  ss>>pass;   //prevede char na string

   Bot b(login, pass);
} 

