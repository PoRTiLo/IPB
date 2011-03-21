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
string getPassTerminal() {
	char pass[LENGTH_PASS];
	
//	initscr();		//rozpozna typ terminalu, inicializuje curses datove struktury, vymaze terminal
//	printw("zadejte heslo:");
//	cbreak();		//znaky v terminalu nejspu buffrovany, okamzite predany programu
//	noecho();		//nepise znaky na terminal
//	getstr(pass);	//nacte heslo
//	endwin();		//nastaveni terminalu do puvodniho stavu

	return  pass;
}


string numToStr( const int number ) {

	stringstream ss;
	ss << number;
	return ss.str();
}

string numToStr( const float number ) {

	stringstream ss;
	ss << number;
	return ss.str();
}

string numToStr( const unsigned int number ) {

	stringstream ss;
	ss << number;
	return ss.str();
}

string numToStr( const short int number ) {

	stringstream ss;
	ss << number;
	return ss.str();
}

float stringToFloat( const string str ) {

	istringstream is(str);
	float num;
	is >> num;
	return num;
}

int stringToInt( const string str ) {

	istringstream is(str);
	int num;
	is >> num;
	return num;
}

unsigned int stringToUnsignedInt( const string str ) {

	istringstream is(str);
	unsigned int num;
	is >> num;
	return num;
}

short int stringToShortInt( const string str ) {

	istringstream is(str);
	short int num;
	is >> num;
	return num;
}

