#include "thread.h"
//#include "smtlib.h"

// konstruktor
Thread::Thread()
{
}

// vrati ID vlakna
pid_t Thread::getThreadId() const {

	return this->threadId;
}

// vytvori a psusti vlakno
int Thread::start( void* arg ) {

	setArg(arg);
//	int code = pthread_create(Thread::entryPoint, this, &threadId);
//	return code;
//	pthread_create(&vlakno, NULL, funkce, mes);
return 1;
}

int Thread::run( void* arg) {

	setup();
	execute(arg);
}

void* Thread::entryPoint(void* pthis) {

//	Thread* pt = (Thread*)pthis;
//	pthis->run(getArg());
}

void Thread::setup() {


}

void Thread::execute( void* arg ) {

}

void* Thread::getArg() const {

	return arg;
}

void Thread::setArg( void * a ) {

	arg = a;
}
