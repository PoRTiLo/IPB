#pragma once

#ifndef FUNC_H__
#define FUNC_H__

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>

//#include <ncurses.h>
#include <pthread.h>

using namespace std;
extern bool f_global;
/**
 * Ukonci beh programu.
 */

void checkSignal( int numSignal );

void initSignal();

void signalTerm();

void initThread();

void *thread(void *mThread);


//string getPassTerminal();

string numToStr( const int number ); 
string numToStr( const unsigned int number ); 
string numToStr( const short int number ); 
string numToStr( const float number ); 
float stringToFloat( const string str );
int stringToInt( const string str );
short int stringToShortInt( const string str );
unsigned int stringToUnsignedInt( const string str );

#endif //FUNC_H__
