#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "connect.h"

#include "transform.h"






typedef struct tmatrix
{
	int rows, cols;;
	int **matrix;

} TMatrix;


void allocMatrix( TMatrix *m ) {

	m->matrix = NULL;
	int **tempMatrix;
	int r, s;
	if((tempMatrix = (int **)malloc(m->rows*sizeof(int*))) == NULL)  //alokace radku
		printf("chyba alokace\n");

   for(r = 0; r < m->rows; r++)
   {
		if((tempMatrix[r] = (int*) malloc(m->cols*sizeof(int))) == NULL)  //alokace sloupcu
			printf("chyba aokace\n");
	}

	m->matrix = tempMatrix;
   for(r = 0; r < m->rows; r++)
   {
   	for(s = 0; s < m->cols; s++)
   		m->matrix[r][s] = 0;
   }
}



/**
 * Main.
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int>
 */
int main( int argc, char* argv[] ) {

	std::ofstream myfile("example.txt", std::ios::out);


	Transform* transform = new Transform();
	transform->start();
	std::vector<std::string> vectorUser = transform->printUser();
	std::vector<std::string>::iterator it;
	time_t secS = transform->stringToSecFirst( DATE_START );
	time_t secE = transform->stringToSecFirst( DATE_END );
	time_t secPom = secS;
	char dateStart[80];
	struct tm*  timeS;

	TMatrix m;
	m.rows = 289;
	m.cols = vectorUser.size();
	allocMatrix(&m);
	int *vec = (int *) malloc(sizeof(int) * 289);

	int k,i =0;
	for( it = vectorUser.begin(); it < vectorUser.end(); it++, i++ )
	{
		for( secS = secPom; secS <= secE; secS += 86400)
		{
			timeS = localtime(&secS);
			strftime(dateStart, 79, "%Y-%m-%d %H:%M:%S", timeS);
			transform->userToTab(vec, vectorUser[i], dateStart);
			for( int l = 0; l < 289; l++ )
				m.matrix[l][i] = vec[l];
		}
		printf("\n");
	}


	myfile << "userJID;date;";
	int h = 0;
	int s = 0;
	for(int k = 0; k <=  288*5; k += 5 )
	{
		if( s==60 )
		{
			h++;
			s = 0;
		}
		myfile << h << ":" << s <<";";
		s += 5;
	}
	myfile << "\n";
		
	std::string pom = DATE_START;
	size_t found = pom.find(" ");
	if( found != std::string::npos )
		pom = pom.substr(0,found);
		
		;
	//for(int k = 0; k < m.rows; k++ )
	for(int k = 0; k < m.cols; k++ )
	{
	//	for(int l = 0; l < m.cols; l++)
		myfile << vectorUser[k]<<";"<<pom<<";";
		for(int l = 0; l < m.rows; l++)
//			myfile << m.matrix[k][l] << ".0;";
			myfile << m.matrix[l][k] << ";";

		myfile << "\n";
	}

	for (i = 0; i < m.rows; i++) 
   	free(m.matrix[i]);

   free(m.matrix);
	free(vec);
   myfile.close();

	return 0;
}
