#include "database.h"
#include "const.h"

Database::Database()
{
	hostaddr = DB_ADDR;
	dbname = DB_NAME;
	user = DB_USER;
	password = DB_PASS;
	connectTimeout = DB_TIME;
	port = DB_PORT;
	connInfo = "";
}

Database::Database( string shostaddr, string sdbname, string suser, string spassword, string sconnectTimeout,  string sport )
{
	hostaddr = shostaddr;
	dbname = sdbname;
	user = suser;
	password = spassword;
	connectTimeout = sconnectTimeout;
	port = sport;
	connInfo = "";
}

void Database::makeStringConnect() {
	
	string shostaddr = "hostaddr = '";
	string sport = "' port = '";
	string sdbname = "' dbname = '";
	string suser = "' user = '";
	string spassword = "' password = '";
	string sconnect_timeout = "' connect_timeout = '";
	string sconnInfo = "";
	connInfo += shostaddr + hostaddr + sport + port + sdbname + dbname + suser + user + spassword + password + sconnect_timeout + connectTimeout +"'";
}


void Database::start() {
	
	Database::connect();
	Database::initDb();
}

void Database::initDb() {

	Database::createTable( "vcard", DB_VCARD );
}


void Database::connect() {
	
	Database::makeStringConnect();
	psql = PQconnectdb(connInfo.c_str());
	if( !psql )
	{
		fprintf(stderr, "Error\n");
		Database::exitError(psql);
	}

	//connect
	if( PQstatus(psql) != CONNECTION_OK )
	{
		fprintf(stderr, "chyba\n");
		Database::exitError(psql);
	}
}

void Database::dropTable( const string nameTable ) {

	string query = DB_D_T_I_E + nameTable + ";";
	presult = PQexec(psql, query.c_str());
	if(PQresultStatus(presult) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "CHYBA MAZANI TABLKY\n");	
		PQclear(presult);
		Database::exitError(psql);
	}
	PQclear(presult);
}

void Database::createTable( const string nameTable, const string structTable ) {

	string query = DB_S_ALL + nameTable + ";"; 
	presult = PQexec(psql, query.c_str());
	if(PQresultStatus(presult) == PGRES_TUPLES_OK)
	{
		printf("exec VCARD existuje");
	}
	else
	{
		query = DB_C_T + nameTable + " (" + structTable + ");";
		presult = PQexec( psql, query.c_str() );
		if(PQresultStatus(presult) != PGRES_COMMAND_OK)
		{
			fprintf(stderr, "CHYNA dotazu\n");
			PQclear(presult);
			Database::exitError(psql);
		}
	}
	PQclear(presult);
}


void Database::insertTableVCard( const string sJid, const string name ) {

	string query = DB_I_VCARD;
	query += "vcard (id, jid, family) VALUES (12, '" + sJid + "', '" + name + "');";
	presult = PQexec( psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError(psql);
	}
	PQclear(presult);
}


void Database::insertTableVCard( string jidBare, string nickname, string url, string bday, string jabberid, string title, string role, string note, string mailer, string rev, string uid, string tz, string prodid, string sortstring, string nFamily, string nGiven, string nMiddle, string nPrefix, string nSuffix ) {

	string query = DB_I_VCARD;
	query += "vcard (id, jid, family, given, middle, prefix, suffix, nickname, url, bday, jabberid, title, role, note, mailer, rev, uid, tz, prodid, sortstring) VALUES (12, '" + jidBare + "', '" + nFamily + "', '" + nFamily + "', '" + nGiven + "', '" + nMiddle + "', '" + nPrefix + "', '" + nSuffix + "', '" + url + "', '" + bday + "', '" + jabberid + "', '" + title + "', '" + role + "', '" + note + "', '" + mailer + "', '" + rev + "', '" + uid + "', '" + tz + "', '" + prodid + "', '" + sortstring + "');";
	printf("////////////////// %s\n", query.c_str());
	presult = PQexec( psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError(psql);
	}
	PQclear(presult);
}


/**
 *
 *
 */
void Database::exitError(PGconn *psql) {
	PQfinish(psql);
	//exit(EXIT_FAILURE);
}


