#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

#include "connect.h"

#include "transform.h"


#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))



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

void printHead( std::ofstream* myfile ) {

	*myfile << "\"userJID\";";
	int h = 0;
	int s = 0;
	for( int k = 0; k <=  (288*5)-1; k += 5 )
	{
		if( s==60 )
		{
			h++;
			s = 0;
		}
		*myfile << "\""  << h << ":" << s << "\";";
		s += 5;
	}
	*myfile << "\"24:00\"";
	*myfile << "\n";
		
}

void printData( TMatrix* m, std::vector<std::string> vectorUser, std::ofstream* myfile ) {


	//std::string pom = DATE_START;
	//size_t found = pom.find(" ");
	//if( found != std::string::npos )
	//	pom = pom.substr(0,found);
	//for(int k = 0; k < m.rows; k++ )
	int l;
	for(int k = 0; k < m->cols; k++ )
	{
	//	for(int l = 0; l < m.cols; l++)
		//myfile << vectorUser[k]<<";"<<pom<<";";
		*myfile << vectorUser[k] << ";";
		for( l = 0; l < m->rows-1; l++ )
//			myfile << m.matrix[k][l] << ".0;";
			*myfile << m->matrix[l][k] << ";";

		*myfile << m->matrix[l][k];
		*myfile << "\n";
	}

}

typedef std::multimap<std::string,std::string> Tab;
/**
 * Main.
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int>
 */
int main( int argc, char* argv[] ) {

	
	std::string line;
	size_t found;
	size_t found2;
	std::string key;
	std::string value;
	std::cout<<argv[1]<<std::endl;

	std::ifstream in(argv[1], std::ios::in | std::ios::binary); 
	if(!in)
	{ 
		std::cout << "Cannot open file.\n"; 
		return 1; 
   } 

	std::cout<<in<<std::endl;

	Transform* transform = new Transform();
//	std::vector<std::string> vectorUser = transform->printUser();
	std::ifstream inUser("example.txt", std::ios::in | std::ios::binary); 
	std::vector<std::string> vectorUser;
	if(!inUser)
	{ 
		std::cout << "Cannot open file.\n"; 
		return 1; 
	}

	while(std::getline(inUser, line) )
	{
		found = line.find(";");
		found2 = line.find(";", found+1);
		key = line.substr(0,found);

		vectorUser.push_back(key);
	}

	Tab table;
	int countCluster = 0;
	while(std::getline(in,line))
	{
		found = line.find("\"");
		found2 = line.find("\"", found+1);
		key = line.substr(found+1, found2-1-found);

		found = line.find("\"", found2+1);
		found2 = line.find("\"", found+1, 1);
		value = line.substr(found+1, found2-found-1);

		table.insert( std::pair<std::string, std::string>(key, value) );
		countCluster++;
	}

	TMatrix m;
	m.cols = 130;//round(countCluster / vectorUser.size());
	m.rows = vectorUser.size();
	allocMatrix(&m);

	std::multimap<std::string, std::string>::iterator it;
	int i = 0;
  	int num;
	for( it = table.begin() ; it != table.end(); it++ )
	{
		key = (*it).first;
		value = (*it).second;
		found = value.find("_");
		found2 = value.find("\"", found+1);
		value = value.substr(found+1, found2-1-found);

		std::istringstream is(value);
	  	is >> num;
		for( i = 0; vectorUser[i] != key; i++ )
		{
			if(key == "userJID")
				break;
		}
		m.matrix[i][num] = m.matrix[i][num]++;
	}

	//tisk vysledne tabulky
	std::cout << "USER";
/*	for(int num = 0; num < 101; num++ )
		std::cout << " " << num;
	for( int i = 0; i < m.rows; i++ )
	{
		std::cout << std::endl << vectorUser[i];
		for( int num = 0; num < m.cols; num++)
			std::cout << " " << m.matrix[i][num];
	}
*/
std::cout<<MAX(1,3) << "...." <<MIN(1,5);

//kroem posledniho uizvatele
	int max = 0;
	int min = 0;
	double count = 0;
	TMatrix t;
	t.cols = vectorUser.size();;//round(countCluster / vectorUser.size());
	t.rows = vectorUser.size();
	allocMatrix(&t);

	for( int row = 0; row < m.rows-1; row++ )
	{

		for( int usr = row+1; usr < m.rows; usr++, count = 0 )
		{
			for( int col = 0; col < m.cols; col++ )
			{
				max = MAX(m.matrix[row][col], m.matrix[usr][col]);
				min = MIN(m.matrix[row][col], m.matrix[usr][col]);
				count += max - (max - min);
			}
			t.matrix[row][usr] = (int)((count/154)*100 + 0.5);
			t.matrix[usr][row] = (int)((count/154)*100 + 0.5);
		}
	}

	for( int i = 0; i < t.rows; i++ )
	{
		std::cout<<std::endl;
		for( int num = 0; num < t.cols; num++)
			std::cout << " " << t.matrix[i][num];

	}

	for (i = 0; i < m.rows; i++) 
	   	free(m.matrix[i]);

	for (i = 0; i < t.rows; i++) 
	   	free(t.matrix[i]);

	free(m.matrix);
	free(t.matrix);
	in.close();
	inUser.close();

	return 0;
}
