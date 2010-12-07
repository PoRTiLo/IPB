#include "database.h"
#include "const.h"

Database::Database()
{
	this->hostaddr = DB_ADDR;
	this->dbname = DB_NAME;
	this->user = DB_USER;
	this->password = DB_PASS;
	this->connectTimeout = DB_TIME;
	this->port = DB_PORT;
	this->connInfo = "";
}

Database::Database( string shostaddr, string sdbname, string suser, string spassword, string sconnectTimeout,  string sport )
{
	this->hostaddr = shostaddr;
	this->dbname = sdbname;
	this->user = suser;
	this->password = spassword;
	this->connectTimeout = sconnectTimeout;
	this->port = sport;
	this->connInfo = "";
}

void Database::makeStringConnect() {
	
	string shostaddr = "hostaddr = '";
	string sport = "' port = '";
	string sdbname = "' dbname = '";
	string suser = "' user = '";
	string spassword = "' password = '";
	string sconnect_timeout = "' connect_timeout = '";
	string sconnInfo = "";
	this->connInfo += shostaddr + hostaddr + sport + port + sdbname + dbname + suser + user + spassword + password + sconnect_timeout + connectTimeout +"'";
}


void Database::start() {
	
	Database::connect();

	Database::dropAll();

	Database::initDb();
}

void Database::initDb() {

	if( Database::createTable( "logarea", DB_TABLE_LOGAREA ) )
	{
		Database::insertTableConst( DB_DATA_LOGAREA );
	}

	if( Database::createTable( "level", DB_TABLE_LOGAREA ) )
	{
		Database::insertTableConst( DB_DATA_LEVEL );
	}

	Database::createTable( "xml", DB_TABLE_XML );

	Database::createTable( "debug", DB_TABLE_DEBUG );

	Database::createTable( "vcard", DB_TABLE_VCARD );
	Database::createTable( "userjid", DB_TABLE_USER );
}


void Database::connect() {
	
	Database::makeStringConnect();
	this->psql = PQconnectdb(connInfo.c_str());
	if( !this->psql )
	{
		fprintf(stderr, "Error\n");
		Database::exitError();
	}

	//connect
	if( PQstatus(this->psql) != CONNECTION_OK )
	{
		fprintf(stderr, "chyba\n");
		Database::exitError();
	}
}

void Database::dropTable( const string nameTable ) {

	string query = DB_D_T_I_E + nameTable + "CASCADE;";
	presult = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "CHYBA MAZANI TABLKY\n");	
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

bool Database::createTable( const string nameTable, const string structTable ) {

	string query = DB_SELECT_ALL + nameTable + ";"; 
	presult = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult) == PGRES_TUPLES_OK)
	{
		printf("exec %s existuje", nameTable.c_str());
		return false;
	}
	else
	{
		query = DB_C_T + nameTable + " (" + structTable + ");";
		presult = PQexec( this->psql, query.c_str() );
		if(PQresultStatus(presult) != PGRES_COMMAND_OK)
		{
			fprintf(stderr, "CHYNA dotazu\n");
			PQclear(presult);
			Database::exitError();
			return false;
		}
	}
	PQclear(presult);
	return true;
}

/*
void Database::insertTableVCard( const string sJid, const string name ) {

	string query = DB_INSERT;
	query += "vcard (id, jid, family) VALUES (12, '" + sJid + "', '" + name + "');";
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}
*/

void Database::insertTableVCard( string jidBare, string nickname, string url, string bday, string jabberid, string title, string role, string note, string mailer, string rev, string uid, string tz, string prodid, string sortstring, string nFamily, string nGiven, string nMiddle, string nPrefix, string nSuffix ) {

	Database::getTime();
	string query = DB_INSERT;
	query += "vcard ( jid, dateAdd, family, given, middle, prefix, suffix, nickname, url, bday, jabberid, title, role, note, mailer, rev, uid, tz, prodid, sortstring) VALUES ( '" + jidBare + "', timestamp '" + sTime + "', '" + nFamily + "', '" + nFamily + "', '" + nGiven + "', '" + nMiddle + "', '" + nPrefix + "', '" + nSuffix + "', '" + url + "', '" + bday + "', '" + jabberid + "', '" + title + "', '" + role + "', '" + note + "', '" + mailer + "', '" + rev + "', '" + uid + "', '" + tz + "', '" + prodid + "', '" + sortstring + "');";
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTableConst( const string query ) {
	
	presult = PQexec( this->psql, query.c_str() );
	if( PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTableUser( string jidBare) {

	if( !existUser(jidBare) )
	{
		//vlozeni noveho uzivatele

		Database::getTime();
		string query = DB_INSERT;
		query += "userjid (jidbare, date) VALUES ('"+ jidBare + "', timestamp '" + this->sTime + "');";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	}
	PQclear(presult);
}

bool Database::existUser( const string user ) {

	string query = "Select jidbare from userjid where jidbare = '";
	query += user + "';";

	presult = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult) == PGRES_TUPLES_OK)
	{

		if( PQntuples(presult) == 0 )
			return false;
		else
			return true;
	}
	else
		return false;
}

void Database::insertTableDebug( int level, int area, const string message ) {

	Database::getTime();
	string query = DB_INSERT;
	query += "debug ( area, dateAdd, level, message) VALUES ("+ Database::convertInt(area) + ", timestamp '" + this->sTime + "', ";
	query += Database::convertInt( level ) + ", '" + Database::convertXML(message) + "');";
	presult = PQexec( this->psql, query.c_str() );
	if( PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	else
	{

		PQclear(presult);
	}
}

void Database::insertTableXML( int level, int area, const string message ) {
//	string parserMes = message;
//	parser->feed(parserMes);
	Database::getTime();
	string query = DB_INSERT;
	query += "xml ( area, dateAdd, level, message) VALUES ("+ Database::convertInt(area) + ", timestamp '" + this->sTime + "', ";
	query += Database::convertInt( level ) + ", '" + Database::convertXML(message) + "');";
	presult = PQexec( this->psql, query.c_str() );
	if( PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	else
	{
		PQclear(presult);
	}

}

string Database::convertXML( string message ) {

	int lenght = message.length();
	char mess[lenght];
	PQescapeString( mess, message.c_str(), lenght );
	string back(mess);
	return back;
}

/**
 *
 *
 */
void Database::exitError() {
	PQfinish(this->psql);
	//exit(EXIT_FAILURE);
}


void Database::getTime() {

	time_t times;
	times = time(NULL);
	struct tm *ltmtime = localtime(&times);
  	strftime(this->sTime, 80 - 1, "%Y-%m-%d %H:%M:%S ", ltmtime);
}

string Database::convertInt( int number ) {

	stringstream ss;
	ss << number;;
	return ss.str();
}


void Database::dropAll() {

	Database::dropTable( "debug");
	Database::dropTable( "level");
	Database::dropTable( "logarea");
	Database::dropTable( "userjid");
	Database::dropTable( "vcard");
	Database::dropTable( "xml");

}
