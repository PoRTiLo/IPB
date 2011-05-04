#include "errors.h"

const char *ERRORS[] = {

//1	COK
	"Vse v poradku.\n",
//		INFO
	"INFO : ",
//		CHELP
	"NAPOVEDA : ",
//		CREGFOUND
	"Retezec obsahuje pozadovany regularni vyraz\n",
//		WARNING
	"VAROVANI : ",
//		WMOREPAR
	"Zadal jste moc parametru, program bude pracovat jen s prvnim zadanym, zbytek se ignoruje.\n",
//		ERROR
	"CHYBA : ",
//		EREGCOMP
	"Chybna kompilace regularniho vyrazu na detekci korektnosti JID.\n",
//		EREGNOTFOUND
	"Chyben zadane JID, kontrolovano pomoci regularniho vyrazu\nJID musi byt zadano ve tvaru login@server/resource.\n",
//		ENOCONNECT
	"Nespravne heslo nebo prihlasovaci jmeno\n",
//		END
	"KONEC.\n"
//		UNKNOWN
	"Neocekavana chyba.\n",
//
//
//

};

/*
ostream &getTime( ostream &stream) {

	struct tm *localTime;
	time_t t;
	t = time(NULL);
	localTime = localtime(&t);
	stream << asctime(localTime);

	return stream;
}
*/

void getErrors( enum errors N ) {
//	cout << getTime;

	FILE *outstream = stdout;

	if( N < COK || N > END )
	{
		N = UNKNOWN;
		outstream = stderr;
		printErrors(N, UNKNOWN, outstream);
	}
	else if( N < WARNING )
	{
		printErrors(N, INFO);
	}
	else if( N > WARNING && N < ERROR )
	{
		printErrors(N, WARNING);
	}
	else
	{
		outstream = stderr;
		printErrors(N, ERROR, outstream);
	}
}

void printErrors( enum errors N ) {
	fprintf(stdout, "%s", ERRORS[N]);
}

void printErrors( enum errors N, enum errors IN ) {
	fprintf(stdout, "%s%s",ERRORS[IN], ERRORS[N]);
}

void printErrors( enum errors N, enum errors IN, FILE *outstream) {
	fprintf(outstream, "\n%s%s\n", ERRORS[IN], ERRORS[N]);
	exit(-1);
}
