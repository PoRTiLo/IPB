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
	END,
	UNKNOWN,
};

extern void printErrors( enum errors N );
extern void printErrors( enum errors N, enum errors IN );
extern void printErrors( enum errors N, enum errors IN, FILE *outstream );
extern void getErrors( enum errors N );
#endif //ERRORS_H__
