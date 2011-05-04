#include <stdio.h>
#include <string.h>



#include "bot.h"
#include "func.h"


/**
 * Main.
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int>
 */
int main( int argc, char* argv[] ) {

	Bot bot(DEF_LOGIN, DEF_PASS);
	bot.run();

	return 0;
}
