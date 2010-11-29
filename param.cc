#include "param.h"
#include "errors.h"

Param::Param( int argc, char * argv[] )
{
	pArgc = argc;
	pArgv = argv;
	initTJids();
}

int Param::regExp( char* argvJid ) {
	pcre* reHandle;
	int errOffset;
	const char *err;
	int res;
	int oVector[VEC_SIZE];
	memset(oVector,'\0', sizeof(oVector));

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
//		getErrors( CREGFOUND );

		resultJids.jids = argvJid;
		resultJids.user = cpString(oVector[2], oVector[3]);
		resultJids.server = cpString(oVector[4], oVector[5]);
		resultJids.resource = cpString(oVector[6], oVector[7]);

//		printStructJids();
	}
	else								// chybne JID
	{
		getErrors( EREGNOTFOUND );
	}
	pcre_free(reHandle);
}

string Param::cpString( int start, int end ) {
	string pomString;
	for( int i = start; i < end; i++ )
		pomString += resultJids.jids[i];
	return pomString;
}

void Param::printStructJids() {
	fprintf(stdout, "result.jids : %s\nresult.user : %s\nresult.server : %s\nresult.resource : %s\nresulJids.pass : %s\n",resultJids.jids.c_str(), resultJids.user.c_str(), resultJids.server.c_str(), resultJids.resource.c_str(), resultJids.pass.c_str() );
}

void Param::initTJids() {
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

TJids Param::getTJids() {
	return resultJids;
}

int Param::getPArgc() {
	return pArgc;
}

char** Param::getPArgv() {
	return pArgv;
}

void Param::setTJidsPass( string pass ) {
	resultJids.pass = pass;
}
