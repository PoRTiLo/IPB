#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
//#include <assert.h>
//#include <limits.h>

//#include "utf8.h"


//#include "bot.h"
#include "param.h"
#include "func.h"
#include "database.h"

/**
 * Main.
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int>
 */
int main( int argc, char* argv[] ) {

	Database* database = new Database();
	//JID jid("pidgin@localhost");
	database->start();
	std::vector<std::string> vectorUser = database->printUser();
	std::vector<std::string>::iterator it;
	string dateS = "2010-12-07 12:02:20";
	string dateE = "2010-12-09 13:34:05";
	time_t secS = database->stringToSecFirst( dateS );
	time_t secE = database->stringToSecFirst( dateE );
	char dateStart[80];
	struct tm*  timeS;
	for(; secS <= secE; secS += 86400)
	{
		int i =0;
		timeS = localtime(&secS);
		strftime(dateStart, 79, "%Y-%m-%d %H:%M:%S", timeS);
		printf("date:%s\n",dateStart);
		for( it = vectorUser.begin(); it < vectorUser.end(); it++ )
		{
			std::cout <<""<<*it<<std::endl;
			int *pointerArray = database->userToTab(vectorUser[i], dateStart);
			i++;
			for(int l=0; l < 289; l++)
				printf("%d:%d\n",l,pointerArray[l]);
		}
	}

	return 0;
}
