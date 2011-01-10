#include <mysql/mysql.h>
#include <my_global.g>
#include <stdio.h>
#include <string>
#include <iostream>


#define DB_SERV "localhost"
#define DB_USER "rt"
#define DB_PASS "javier"
#define DB_NAME "demo"


using namespace std;

int main() {

	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL_RES *result;

	unsigned int num_fields;
	unsigned int i;

	mysql_init(&mysql);

	// pripojeni k databazi
	if( !mysql_real_connect(&mysql, DB_SERV, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) )
	{
		fprintf(stderr, "CHYBAAAAAAAA");
		return 1;
	}
	else	// pripojeno k databazi
	{
		fprintf(stderr, "Connect");
	}

	// tvorba nove tabulky
	if( mysql_query(&mysql, "CREATE TABLE demo (name VARCHAR(25))") )
	{
		fprintf(stderr, "Tabulka nebyl avytvorena\n");
	}

	// insert in the table
	if( mysql_query(&mysql, "INSERT INTO demo VALUES('pepik')") )
	{
		fprintf(stderr, "nevlozeno\n");
	}

//////////////////////////////////////////////////////
	// zobrazeni tabulek
	MYSQL_RES *table;
	MYSQL_ROW row;
	int num_field;
	
	//mysql_free_result(table);
	if( table = mysql_list_tables(&mysql, NULL))
	{
		
	}
	cerr<<"table"<<table->field_count<<endl;
	mysql_free_result(table);
//	mysql_query(&mysql, "INSERT INTO " + table + " VALUES(' )

	return 0;
}
