#include "param.h"

Param::Param( int argc, char * argv[] )
{
	pArgc = argc;
	pArgv = argv;
	initTJids(resultJids);
}

int Param::regExp( char* argvJid ) {
	pcre* reHandle;
	int errOffset;
	const char *err;
	int res;
	int oVector[VEC_SIZE];

	// 0 - kodovani retezce (default)
	// err - pointer s textem pripadne chyby
	// errOffset - cislo pozice, kde se vyskytla chyba
	//
	reHandle = pcre_compile(REG_EXP, PCRE_UTF8, &err, &errOffset, NULL);	//kompila regulatni vyrazu
	if( !reHandle )
	{
		printf("chyba\n");
		//printf error;
		//return ERROR;
	}

	res = pcre_exec(reHandle, NULL, argvJid, strlen(argvJid), 0, 0, oVector, VEC_SIZE);
	if(res > 0 )
	{
		printf("nasel\n");
		//nasel 
		//rozepsat do struktury
		resultJids.pass = "pes";
	}
	else
	{
		printf("NEEEEEEEEEEEEEEEEnasel\n");
		//nenasel chyba
		//napsat v jakem tvaru to musi byt
	}
	pcre_free(reHandle);
}

void Param::initTJids( TJids &resultJids) {
	resultJids.jids = "";
	resultJids.user = "";
	resultJids.server = "";
	resultJids.resource = "";
	resultJids.pass = "";
}

int Param::getParams( ) {

	if( pArgc == 2 && ((strcmp("-h", pArgv[1]) == 0) | (strcmp("--h", pArgv[1]) == 0) | (strcmp("-help", pArgv[1]) == 0) | (strcmp("--help", pArgv[1]) == 0)) )
	{
		/////print napovedaaaaaaaaaaa
		return 0; //OK-HELP
	}
	else if( pArgc == 2 )
	{
		regExp(pArgv[1]);
		//return povedlo nepovedlo
	}
	else
	{
		//zadal jset moc paramrtru
	}

	return 0;
}
