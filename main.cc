
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
//#include <assert.h>
//#include <limits.h>

//#include "utf8.h"


#include "param.h"
#include "bot.h"
#include "errors.h"
/**
 */
int main( int argc, char* argv[] ) {
	if( argc > 1 )	//jid vlozeno jako argumnet pri spousteni
	{
		Param param(argc, argv);
		param.getParams();
		//ifpovedlo
		//bot(param.jid, param.pass)
		//nepovedlo
		//return error
	}
	else
	{
		Bot bot();
	}

	return 0;
}
