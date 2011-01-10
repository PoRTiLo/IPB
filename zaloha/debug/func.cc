#include "func.h"
#include "bot.h"
using namespace std;
bool f_global = false;
void initSignal() {

	cout << endl<< endl<< getpid()<<endl;
		//void (*uFci) (int);
		//uFci = 
		(void)signal(SIGTERM, checkSignal);
	}

	void checkSignal( int signalNum ) {

cout << "peppikkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;
//		if( signalNum == SIGTERM )
			f_global = true;
	}

void *funkce( void *vlakno ) {

	while(true)
	{
		sleep(5);
		cout << f_global<<endl;
		if(f_global == true)
		{
			//Bot::end();
			return(0);

		}
	}
}

void initThread() {
Bot *p = new Bot();
	pthread_t vlakno;
	char * mes= "aaa";
//	pthread_create(&vlakno, p, funkce, mes);
}

bool signalTerm() {

	initSignal();
	initThread();

	return f_global;
}
