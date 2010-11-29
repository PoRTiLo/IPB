
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
//#include <assert.h>
//#include <limits.h>

//#include "utf8.h"

#include <ncurses.h>

#include "param.h"
#include "bot.h"
//#include "errors.h"

#define LENGTH_PASS 100

#define JABBER "JabInfo@jabbim.com"
#define PASSWORD "xse20IPB10"

/**
 *
 */
string getPassTerminal() {
	char pass[LENGTH_PASS];
	
	initscr();		//rozpozna typ terminalu, inicializuje curses datove struktury, vymaze terminal
	printw("zadejte heslo:");
	cbreak();		//znaky v terminalu nejspu buffrovany, okamzite predany programu
	noecho();		//nepise znaky na terminal
	getstr(pass);	//nacte heslo
	endwin();		//nastaveni terminalu do puvodniho stavu

	return  pass;
}
/**
 * Main.
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int>
 */
int main( int argc, char* argv[] ) {

	if( argc > 1 )	//jid vlozeno jako argumnet pri spousteni
	{
		Param param(argc, argv);
		param.setTJidsPass(getPassTerminal());
		param.getParams();
		Bot bot(param.getTJids().jids, param.getTJids().pass);
		bot.run();
	}
	else
	{
		Bot bot(DEF_LOGIN, DEF_PASS);
		bot.run();
	}
	return 0;
}
