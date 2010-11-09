#include <libpq-fe.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#define DB_SERV "localhost"
#define DB_ADDR "127.0.0.1"
#define DB_PORT ""
#define DB_USER "portilo"
#define DB_PASS "trewq"
#define DB_NAME "portilo"
#define DB_TIME "10"

using namespace std;

/**
 *
 *
 */
static void exitError(PGconn *psql) {
	PQfinish(psql);
	exit(EXIT_FAILURE);
}



/**
 *
 *
 */
const char* makeConnect() {
	
	string hostaddr = "hostaddr = '";
	string port = "' port = '";
	string dbname = "' dbname = '";
	string user = "' user = '";
	string password = "' password = '";
	string connect_timeout = "' connect_timeout = '";
	string connInfo = "";
	connInfo += hostaddr + DB_ADDR + port + DB_PORT + dbname + DB_NAME + user + DB_USER + password + DB_PASS + connect_timeout + DB_TIME +"'";

	return connInfo.c_str();
}

int main() {

	PGconn *psql;
	psql = PQconnectdb(makeConnect());
	if( !psql )
	{
		fprintf(stderr, "Error\n");
		exitError(psql);
	}

	//connect
	if( PQstatus(psql) != CONNECTION_OK )
	{
		fprintf(stderr, "chyba\n");
		exitError(psql);
	}



	//drop table
	PGresult *presult;
	presult = PQexec(psql, "DROP TABLE IF EXISTS pokus;");
	if(PQresultStatus(presult) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "CHYBA MAZANI TABLKY\n");
		exitError(psql);
	}

	//create table
	presult = PQexec(psql,"CREATE TABLE pokus (name text);" );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "CHYNA dotazu\n");
		PQclear(presult);
		exitError(psql);
	}

		PQclear(presult);
	//find out if tabel exists
	presult = PQexec(psql,"INSERT INTO pokus VALUES('josef');");
	if(PQresultStatus(presult) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "CHYNA dotazu2\n");
		exitError(psql);
	}

	//select from table
	presult = PQexec(psql,"SELECT * from pokus;");
	if(PQresultStatus(presult) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "CHYNA dotazu2\n");
		exitError(psql);
	}

	int nFields = PQnfields(presult);
	int nTuples = PQntuples(presult);
	fprintf(stdout, "nFields:%d, nTUples: %d\n", nFields, nTuples);

	//prochazeni tabulky a jeji vypis
	for(int i = 0; i < nTuples; i++)
	{
		for(int j = 0; j < nFields; j++)
			fprintf(stdout, "%s", PQgetvalue(presult, i, j));
		fprintf(stdout, "\n");
	}

	return 0;
}
