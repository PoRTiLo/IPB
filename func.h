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

extern bool f_global;
/**
 * Ukonci beh programu.
 */

void checkSignal( int numSignal );

void initSignal();

void signalTerm();

void initThread();

void *thread(void *mThread);


//std::string getPassTerminal();

std::string numToStr( const int number ); 
std::string numToStr( const unsigned int number ); 
std::string numToStr( const short int number ); 
std::string numToStr( const float number ); 
float stringToFloat( const std::string str );
int stringToInt( const std::string str );
short int stringToShortInt( const std::string str );
unsigned int stringToUnsignedInt( const std::string str );

/**
 * Prevod typu presence na text.
 * @param[in] <int> presence Typ presence.
 * @return <string> Textove reprezentace typu presence.
*/
std::string presenceString( const int presence );
	
/**
 * Prevod typu zpravy na text.
 * @param[in] <inst> subtype Typ zpravy.
 * @return <string> Textova reprezentace typu zpravy.
*/
std::string messageSubtype( const int subtype );

std::string boolToString( std::string str );
#endif //FUNC_H__
