#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <vector>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define TRANS 288


typedef struct tmatrix
{
	int rows, cols;
	int **matrix;

} TMatrix;


void allocMatrix( TMatrix *m ) {

	m->matrix = NULL;
	int **tempMatrix;
	int r, s;
	if((tempMatrix = (int **)malloc(m->rows*sizeof(int*))) == NULL)  //alokace radku
	{
		std::cout << "Chyba alokace pameti\n" << std::endl;
		exit(1);
	}

	for(r = 0; r < m->rows; r++)
	{
		if((tempMatrix[r] = (int*) malloc(m->cols*sizeof(int))) == NULL)  //alokace sloupcu
		{
			std::cout << "Chyba alokace pameti\n" << std::endl;
			exit(1);
		}
	}

	m->matrix = tempMatrix;

	for(r = 0; r < m->rows; r++)
	{
   		for(s = 0; s < m->cols; s++)
   			m->matrix[r][s] = 0;
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

	std::ifstream in("resource.csv", std::ios::in | std::ios::binary); 	// vstpuni soubor pro
	if(!in)
	{ 
		std::cout << "Cannot open file.\n"; 
		exit(1); 
   } 

	std::ifstream inUser("user.csv", std::ios::in | std::ios::binary); 
	std::vector<std::string> vectorUser;
	if(!inUser)
	{ 
		std::cout << "Cannot open file.\n"; 
		exit(1); 
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
	m.rows = (int)vectorUser.size();
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
/*	for(int num = 0; num < 101; num++ )
		std::cout << " " << num;
	for( int i = 0; i < m.rows; i++ )
	{
		std::cout << std::endl << vectorUser[i];
		for( int num = 0; num < m.cols; num++)
			std::cout << " " << m.matrix[i][num];
	}
*/

//kroem posledniho uizvatele
	int max = 0;
	int min = 0;
	double count = 0;
	TMatrix t;
	t.cols = (int)vectorUser.size();;//round(countCluster / vectorUser.size());
	t.rows = (int)vectorUser.size();
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

	for( i = 0; i < t.rows; i++ )
	{
		std::cout<<std::endl;
		for( int num1 = 0; num1 < t.cols; num1++)
			std::cout << " " << t.matrix[i][num1];
	}

	for( i = 0; i < m.rows; i++ ) 
	   	free(m.matrix[i]);

	for( i = 0; i < t.rows; i++ ) 
	   	free(t.matrix[i]);

	free(m.matrix);
	free(t.matrix);
	in.close();
	inUser.close();

	return 0;
}
