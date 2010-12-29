#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
//#include <assert.h>
//#include <limits.h>

//#include "utf8.h"


#include "bot.h"
#include "param.h"
#include "func.h"


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
