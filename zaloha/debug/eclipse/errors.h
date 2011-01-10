#ifndef ERORRS_H__
#define ERRORS_H__

#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

enum errors {
	COK = 0,
	INFO,
	CHELP,
	CREGFOUND,	//nasel regularni vyraz v retezci "param.c"
	WARNING,
	WMOREPAR,
	ERROR,
	EREGCOMP,
	EREGNOTFOUND,
	ENOCONNECT,
	END,
	UNKNOWN,
};

/**
 * Vytiskne chybove hlaseni.
 * @param[in] <enum errors> N
 */
extern void printErrors( enum errors N );

/**
 * Vytiskne chybova hlaseni.
 * @parm[in] <enum errors> N
 * @param[in] <enum errors> IN
 */
extern void printErrors( enum errors N, enum errors IN );

/**
 * Vytiskne chybove hlaseni.
 * @param[in] <enum errors> N
 * @param[in] <enum errors> IN
 * @param[in] <FILE> oustream
 */
extern void printErrors( enum errors N, enum errors IN, FILE *outstream );

/**
 * Rozhodne o typu chyby.
 * @param[in] <enum errors> N
 */
extern void getErrors( enum errors N );
#endif //ERRORS_H__
