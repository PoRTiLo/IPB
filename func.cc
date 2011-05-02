#include "func.h"

#define LENGTH_PASS 100
using namespace std;
bool f_global = false;

void initSignal() {

	cout << endl<< endl<< getpid()<<endl;
	(void)signal(SIGTERM, checkSignal);
}

void checkSignal( int signalNum ) {

	f_global = true;
}

void *thread( void *mThread ) {

	while(true)
	{
		sleep(5);
		if(f_global == true)
			break;
	}
}

void initThread() {

	pthread_t mThread;
	pthread_create(&mThread, NULL, thread, NULL);
}

void signalTerm() {

	initSignal();
	initThread();
}

/**
 *
 */
std::string getPassTerminal() {
	char pass[LENGTH_PASS];
	
//	initscr();		//rozpozna typ terminalu, inicializuje curses datove struktury, vymaze terminal
//	printw("zadejte heslo:");
//	cbreak();		//znaky v terminalu nejspu buffrovany, okamzite predany programu
//	noecho();		//nepise znaky na terminal
//	getstr(pass);	//nacte heslo
//	endwin();		//nastaveni terminalu do puvodniho stavu

	return  pass;
}


std::string numToStr( const int number ) {

	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::string numToStr( const float number ) {

	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::string numToStr( const unsigned int number ) {

	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::string numToStr( const short int number ) {

	std::stringstream ss;
	ss << number;
	return ss.str();
}

float stringToFloat( const std::string str ) {

	std::istringstream is(str);
	float num;
	is >> num;
	return num;
}

int stringToInt( const std::string str ) {

	std::istringstream is(str);
	int num;
	is >> num;
	return num;
}

unsigned int stringToUnsignedInt( const std::string str ) {

	std::istringstream is(str);
	unsigned int num;
	is >> num;
	return num;
}

short int stringToShortInt( const std::string str ) {

	std::istringstream is(str);
	short int num;
	is >> num;
	return num;
}

std::string messageSubtype( const int subtype ) {

	if( subtype == 1 )
		return "chat";
	else if( subtype == 2 )
		return "error";
	else if( subtype == 4 )
		return "groupchat";
	else if( subtype == 8 )
		return "headline";
	else if( subtype == 16 )
		return "normal";
	else if( subtype == 32 )
		return "invalid";
	else
		return "unknow";
}

std::string presenceString( const int presence ) {

	if( presence == 0 )
		return "Available";
	else if( presence == 1 )
		return "Chat";
	else if( presence == 2 )
		return "Away";
	else if( presence == 3 )
		return "DND";
	else if( presence == 4 )
		return "XA";
	else if( presence == 5 )
		return "Unavaliable";
	else if( presence == 6 )
		return "Probe";
	else if( presence == 7 )
		return "Error";
	else if( presence == 8 )
		return "Invalid";
	else
		return "Unknown presence";
}

std::string boolToString( std::string str ) {

	if( str == "t")
		return "TRUE";
	else
		return "FALSE";
}
