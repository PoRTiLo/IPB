#ifndef PARAM_H__
#define PARAM_H__

#include <pcre.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstring>


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
#define REG_EXP "^([a-zA-Z0-9]){1,127}+@([a-zA-Z0-9]){1,127}+/([a-zA-Z]){0,127}$"

#define VEC_SIZE 100

//^([\x29\x23-\x25\x28-\x2E\x30-\x39\x3B\x3D\x3F\x41-\x7E\xA0 \u1680\u202F\u205F\u3000\u2000-\u2009\u200A-\u200B\u06DD \u070F\u180E\u200C-\u200D\u2028-\u2029\u0080-\u009F \u2060-\u2063\u206A-\u206F\uFFF9-\uFFFC\uE000-\uF8FF\uFDD0-\uFDEF \uFFFE-\uFFFF\uD800-\uDFFF\uFFF9-\uFFFD\u2FF0-\u2FFB]{1,1023})


using namespace std;

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


class Param
{
	protected:
		TJids resultJids;
		int pArgc;
		char** pArgv;

	public:
		/**
		 * Konstruktor
		 * @param[in] <int> argc pocet argumentu
		 * @param[in] <char*> argv pole retezcu vstupnich parametru
		 */
		Param( int argc, char* argv[] );

		/**
		 * Destruktor.
		 */
		~Param(){};

		/**
		 * Zpracovani JID pomoci regularnich vyrazu.
		 * @param[in] <char*> argvJid cele JID
		 * @return<int> vysledek zpracovani, konecny stav, chyby...
		 */
		int regExp( char* argvJid );

		/**
		 * Zpracuje argumenty prikazoveho radku.
		 * @return <int> Uspech x neuspech
		 */
		int getParams();

		/**
		 * Inicializace struktury (vymazani).
		 * @param[out] <TJids> &resultJids struktura bude vymazana
		 */
		void initTJids( TJids &resultJids );
};
#endif //PARAM_H__
