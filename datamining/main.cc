#include <stdio.h>
#include <string.h>

#include "connect.h"

#include "transform.h"

/**
 * Main.
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int>
 */
int main( int argc, char* argv[] ) {

	Transform* transform = new Transform();
	//JID jid("pidgin@localhost");
	transform->start();
	std::vector<std::string> vectorUser = transform->printUser();
	std::vector<std::string>::iterator it;
	time_t secS = transform->stringToSecFirst( DATE_START );
	time_t secE = transform->stringToSecFirst( DATE_END );
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
			int *pointerArray = transform->userToTab(vectorUser[i], dateStart);
			i++;
			for(int l=0; l < 289; l++)
				printf("%d:%d\n",l,pointerArray[l]);
		}
	}

	return 0;
}
