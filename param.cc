#include "param.h"
#include "errors.h"

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
		getErrors( EREGCOMP ); // kompilace reg vyrazu se nepovedla
	}

	res = pcre_exec(reHandle, NULL, argvJid, strlen(argvJid), 0, 0, oVector, VEC_SIZE);
	if(res > 0 )					// spravne JID
	{
		getErrors( CREGFOUND );
		//nasel 
		//rozepsat do struktury
		resultJids.pass = "pes";
	}
	else								// chybne JID
	{
		getErrors( EREGNOTFOUND );
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
		getErrors( CHELP );		// napoveda
	}
	else if( pArgc == 2 )
	{
		regExp(pArgv[1]);
	}
	else
	{
		getErrors( WMOREPAR );	//zadal jset moc parametru
	}

	return 0;
}
