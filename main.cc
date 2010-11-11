
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
//#include <assert.h>
//#include <limits.h>

//#include "utf8.h"

#include <pcre.h>

#include "bot.h"

//XEP 0029
#define REG_DIG "[0-9]"
#define REG_LET "[a-z] | [A-Z]"
//#define REG_ANY_CHAR "[#x20-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF]"
#define REG_ANY_CHAR "[\u0020-\uD7FF] | [\uE000-\uFFFD] | [\uDBC0\uDC00-\uDBFF\uDBFF]"
//#define REG_CONFORMING_CHAR "#x21 | [#x23-#x25] | [#x28-#x2E] | [#x30-#x39] | #x3B | #x3D | #x3F | [#x41-#x7E] | [#x80-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF]"
#define REG_CONFORMING_CHAR "\u0021 | [\u0023-\u0025] | [\u0028-\u002E] | [\u0030-\u0039] | \u003B | \u003D | \u003F | [\u0041-\u007E] | [\u0080-\uD7FF] | [\uE000-\uFFFD] | [\uDBC0\uDC00-\uDBFF\uDBFF]"
#define REG_HNAME "REG_LET|REG_DIG[[REG_LET|REG_DIG|\"-\"]*REG_LET|REG_DIG]"
#define REG_RESOURCE "REG_ANY_CHAR[REG_ANY_CHAR]*"
#define REG_DOMAIN "REG_HNAME[\".\"REG_HNAME]*"
#define REG_NODE "REG_CONFORMING_CHAR[REG_CONFORMING_CHAR]*"
//#define REG_EXP "[REG_NODE\"@\"]REG_DOMAIN[\"/\"REG_RESOURCE]"
#define REG_EXP "^([a-z]|[A-Z]|[0-9]){1,127}@([[a-z]|[A-Z]|[0-9]]){1,127}/[[a-z]|[A-Z]|[0-9]]{0,127}"

//^([\x29\x23-\x25\x28-\x2E\x30-\x39\x3B\x3D\x3F\x41-\x7E\xA0 \u1680\u202F\u205F\u3000\u2000-\u2009\u200A-\u200B\u06DD \u070F\u180E\u200C-\u200D\u2028-\u2029\u0080-\u009F \u2060-\u2063\u206A-\u206F\uFFF9-\uFFFC\uE000-\uF8FF\uFDD0-\uFDEF \uFFFE-\uFFFF\uD800-\uDFFF\uFFF9-\uFFFD\u2FF0-\u2FFB]{1,1023})


#define VEC_SIZE 100

/**
 * Struktura obsahuji kompletni JID
 */
typedef struct jids {
	string jids;				//cele JID
	string user;				//jmeno uzivatele
	string server;				//servr uctu
	string resource;			//resource, zdroj pripojeni
	string pass;				//heslo
}	TJids;


/**
 * Zpracovani JID pomoci regularnich vyrazu.
 * @param[in] <char*> argvJid cele JID
 * @param[out] <TJids> resultJids struktura obasahuji casti JID
 * @return<int> vysledek zpracovani, konecny stav, chyby...
 */
int regExp( char* argvJid, TJids &resultJids ) {
	pcre* reHandle;
	int errOffset;
	const char *err;
	int res;
	int oVector[VEC_SIZE];
	resultJids.pass = "pes";

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
	}
	else
	{
		printf("NEEEEEEEEEEEEEEEEnasel\n");
		//nenasel chyba
		//napsat v jakem tvaru to musi byt
	}
	pcre_free(reHandle);
}


/**
 * Zpracuje argumenty prikazoveho radku.
 * @param[in] <int> argc Pocet argumentu
 * @param[in] <char*> argv[] Pole textovyxh retezcu s argumenty
 * @return <TJids> paramatery JID
 */
TJids getParams( int argc, char* argv[] ) {
	TJids resultJids;
	resultJids.jids = "";
	resultJids.user = "";
	resultJids.server = "";
	resultJids.resource = "";
	resultJids.pass = "";
	if( argc == 2 && ((strcmp("-h", argv[1]) == 0) | (strcmp("--h", argv[1]) == 0) | (strcmp("-help", argv[1]) == 0) | (strcmp("--help", argv[1]) == 0)) )
	{
		/////print napovedaaaaaaaaaaa
	}
	else if( argc == 2 )
	{
		regExp(argv[1], resultJids);
	}
	else
	{
		//zadal jset moc paramrtru
	}
	return resultJids;
}

/**
 *
 *
 */
int main( int argc, char* argv[] ) {


//	printf("%c\n",argv[1]);
	if( argc > 1 )	//jid vlozeno jako argumnet pri spousteni
	{
		TJids resultJids = getParams(argc, argv);
	}
	else
	{
		Bot bot();
	}


}
