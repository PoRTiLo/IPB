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

//	Database::dropAll();

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
	Database::createTable( "presence", DB_TABLE_PRESENCE );
	Database::createTable( "debug", DB_TABLE_DEBUG );
	Database::createTable( "vcard", DB_TABLE_VCARD );
	Database::createTable( "userjid", DB_TABLE_USER );
	Database::createTable( "message", DB_TABLE_MESSAGE );
	Database::createTable( "status", DB_TABLE_STATUS );
	Database::createTable( "resource", DB_TABLE_RESOURCE );

}


void Database::connect() {
	
	Database::makeStringConnect();
	this->psql = PQconnectdb(this->connInfo.c_str());
	if( !this->psql )
	{
		fprintf(stderr, "Error\n");
		Database::exitError();
	}

	//connect
	if( PQstatus(this->psql) != CONNECTION_OK )
	{
		fprintf(stderr, "chyba PRIPOJENI\n");
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
		PQclear(presult);
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


void Database::insertTablePresence( const string jid, const string msg, const string name, const string resource, const string presence, const int priority ) {

	string query = DB_DEF_PRESENCE;
	Database::getTime();
	query += "timestamp '";
	query += this->sTime;
	query += "', '" + jid + "', 'JabInfo@jabbim.cz', '";
	query += Database::convertXML(msg) + "', '" +  name + "', '" + resource + "', '" + Database::convertXML(presence) + "', " + Database::convertInt( priority )+ ");";
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTablePresence( const string jid, const string msg, const string name, const string resource, const string presence ) {

	string query = DB_DEF_PRESENCE;
	Database::getTime();
	query += "timestamp '";
	query += this->sTime;
	query += "', '" + jid + "', 'JabInfo@jabbim.cz', '"; 
	query += Database::convertXML(msg) + "', '" +  name + "', '" + resource + "', '" + presence + "', 0 );";
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTableVCard( string jidBare, string nickname, string url, string bday, string jabberid, string title, string role, string note, string mailer, string rev, string uid, string tz, string prodid, string sortstring, string nFamily, string nGiven, string nMiddle, string nPrefix, string nSuffix ) {

	Database::getTime();
	string query = DB_INSERT;
	query += "vcard ( jid, dateAdd, family, given, middle, prefix, suffix, nickname, url, bday, jabberid, title, role, note, mailer, rev, uid, tz, prodid, sortstring) VALUES ( '" + jidBare + "', timestamp '" + this->sTime + "', '" + nFamily + "', '" + nFamily + "', '" + nGiven + "', '" + nMiddle + "', '" + nPrefix + "', '" + nSuffix + "', '" + url + "', '" + bday + "', '" + jabberid + "', '" + title + "', '" + role + "', '" + note + "', '" + mailer + "', '" + rev + "', '" + uid + "', '" + tz + "', '" + prodid + "', '" + sortstring + "');";
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTableMessage( const string jid, const string msg, const string subject, const string thread, const string subtype ) {

	Database::getTime();
	string query = DB_DEF_MESSAGE;
	query += "timestamp '";
	query += this->sTime;
	query += "', '" + jid + "', 'JabIndo@jabbim.cz', '";
	query += Database::convertXML(msg) + "', '" + subject + "', '" + thread + "', '" + subtype + "');";
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
		//status insert user
		query = DB_INSERT;
		query += "status (jidbare) VALUES ('"+ jidBare + "');";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	}
	PQclear(presult);
}

void Database::updateTableStatus( string user ) {

	string query = "Select * from resource where jidbare = '";
	query += user + "';";
	presult = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult) == PGRES_TUPLES_OK)
	{
		int nFields = PQnfields(presult);	//sloupec
		int nTuples = PQntuples(presult);	//radek
		int priority = -127;
		string pom, pomS;
		int pomInt = 0;
		int culomn = -1;
		for( int i = 0; i < nTuples; i++ )
		{
				pom = PQgetvalue(presult,i,5);
				pomS = PQgetvalue(presult,i,2);
				string some_string;
				istringstream buffer(pom);
				buffer >> pomInt;
				if( priority <= pomInt && pomS != "Unavaliable" && pomS != "unavaliable" )
				{
					priority = pomInt;
					culomn = i;
				}
		}
		if( culomn != -1 )
			updateTableStatus( PQgetvalue(presult,culomn,1), PQgetvalue(presult,culomn,2), PQgetvalue(presult,culomn,3), PQgetvalue(presult,culomn,6));
		else
		{
			for( int i = 0; i < nTuples; i++ )
			{
				pom = PQgetvalue(presult,i,5);
				pomS = PQgetvalue(presult,i,2);
				string some_string;
				istringstream buffer(pom);
				buffer >> pomInt;
				if( priority <= pomInt )
				{
					priority = pomInt;
					culomn = i;
				}
			}
			if( culomn != -1 )
				updateTableStatus( PQgetvalue(presult,culomn,1), PQgetvalue(presult,culomn,2), PQgetvalue(presult,culomn,3), PQgetvalue(presult,culomn,6));
		}
	}
}

void Database::updateTableStatus( string jidBare, string presence, string status, string resource) {

		Database::getTime();
		string query = DB_UPDATE;
		query += "status ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "', resource='" + resource + "' " + DB_WHERE + "jidbare = '" +jidBare+"';";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	PQclear(presult);
}

//
void Database::updateTableResource( string jidBare, string presence, string status, string resource, int priority) {

	string query = DB_UPDATE;
	if( existResource(jidBare, resource) ) //uzivatelsky ucet s mistem existuje, aktualizuji
	{
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "', priority=" + Database::convertInt(priority) + " " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	}
	else					// uzivatel s uctem neexistuje, vytvorim
	{
		query = DB_INSERT;
		query += "resource (jidbare, presence, status, date, priority, resource) VALUES ('"+ jidBare + "', '"+ presence +"', '"+Database::convertXML(status)+"', timestamp '" +this->sTime + "', "+ Database::convertInt(priority)+", '"+resource+"');";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	}
	PQclear(presult);
}

void Database::updateTableResource( string jidBare, string presence, string status, string resource) {

	string query = DB_UPDATE;
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	PQclear(presult);
}
//
bool Database::existResource( const string user, const string resource ) {

	string query = "Select jidbare from resource where jidbare = '";
	query += user + "' and resource = '";
	query += resource + "';";
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

	size_t lenght = message.length();
	char mess[2*lenght+1];
	const char* pepa= message.c_str();
	PQescapeString( mess, pepa, lenght );
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

	Database::dropTable( "debug" );
	Database::dropTable( "level" );
	Database::dropTable( "logarea" );
	Database::dropTable( "userjid" );
	Database::dropTable( "vcard" );
	Database::dropTable( "xml" );
	Database::dropTable( "presence" );
	Database::dropTable( "message" );

}

string Database::printUser() const {

	PGresult* presult;
	presult = PQexec(this->psql, "SELECT jidbare FROM userjid;");
	

	int nFields = PQnfields(presult);
	int nTuples = PQntuples(presult);

	string result;
	stringstream ss;
	string back;
	for( int i = 0; i < nTuples; i++ )
	{
		ss << PQgetvalue(presult,i , 0);

		cout << PQgetvalue(presult,i , 0)<<endl;
		ss >> back;
		result += " - " + string( PQgetvalue(presult,i , 0)) + "\n";
	}
	return result;
}
