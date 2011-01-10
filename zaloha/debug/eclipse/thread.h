/*http://www.linuxselfhelp.com/HOWTO/C++Programming-HOWTO-18.html
*/

#ifndef THREAD_H__
#define THREAD_H__

#include <pthread.h>
#include <sys/types.h>

class Thread
{
	private:
		pid_t threadId;								// id vlakna
		void* arg;										// ukazatel na data pro vlakno
		pthread_t vlakno;
	protected:
		int run(void* arg);
		static void * entryPoint(void*);
		virtual void setup();
		virtual void execute(void*);
		void* getArg() const;
		void setArg(void* a);
		/**
		 * Vrati ID vlakna.
		 * @return <pid_t> id vlakna.
		 */
		pid_t getThreadId() const;
	public:
		/**
		 * Konstruktor.
		 */
		Thread();

		/**
		 * Vytvori vlakno a spusti jej.
		 * @param[in]<void *> arg ukazatel na data pro vlakno
		 * @return <int>
		 */
		int start(void* arg);
};

#endif //THREAD_H__
