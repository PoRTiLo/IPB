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
	Database::createTable( "geoloc", DB_TABLE_GEOLOC );
	Database::createTable( "tune", DB_TABLE_TUNE );
	Database::createTable( "mood", DB_TABLE_MOOD );
	Database::createTable( "activity", DB_TABLE_ACTIVITY );

	Database::clearResourceTable() ; 
	Database::initListVer();
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
	cout<<query<<endl;
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


void Database::insertTablePresence( const string jid, const string msg, const string name, const string resource, const string presence, const int priority, const string nameSW, const string versionSW, const string osSW ) {

	string query = DB_DEF_PRESENCE;
	Database::getTime();
	query += "timestamp '";
	query += this->sTime;
	query += "', '" + jid + "', 'JabInfo@jabbim.cz', '";
	query += Database::convertXML(msg) + "', '" +  name + "', '" + resource + "', '" + Database::convertXML(presence) + "', " + numToStr( priority )+", '" + nameSW + "', '" + versionSW + "', '" + osSW + "');";
		cout <<query<<endl;
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTablePresence( const string jid, const string msg, const string name, const string resource, const string presence ) {

	string query = DB_DEF_PRESENCE1;
	Database::getTime();
	query += "timestamp '";
	query += this->sTime;
	query += "', '" + jid + "', 'JabInfo@jabbim.cz', '"; 
	query += Database::convertXML(msg) + "', '" +  name + "', '" + resource + "', '" + presence + "', 0 );";
	presult = PQexec( this->psql, query.c_str() );
	cout<<query<<endl;
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
				if( priority <= pomInt && pomS != "Unavaliable" && pomS != "unavaliable")
				{
					priority = pomInt;
					culomn = i;
				}
		}
		if( culomn != -1 )
			updateTableStatus( PQgetvalue(presult,culomn,1), PQgetvalue(presult,culomn,2), PQgetvalue(presult,culomn,3), PQgetvalue(presult,culomn,6), PQgetvalue(presult, culomn, 7));
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
				updateTableStatus( PQgetvalue(presult,culomn,1), PQgetvalue(presult,culomn,2), PQgetvalue(presult,culomn,3), PQgetvalue(presult,culomn,6), PQgetvalue(presult, culomn, 7));
		}
	}
}

void Database::updateTableStatus( string jidBare, string presence, string status, string resource, string nameSW) {

		Database::getTime();
		string query = DB_UPDATE;
		query += "status ";
		query += DB_SET;
		query += "presence = '" + presence + "', status = '" + Database::convertXML(status) + "', date = timestamp '" + this->sTime + "', resource='" + resource + "' , nameSW = '" + nameSW + "' " + DB_WHERE + "jidbare = '" + jidBare +	"';";
		cout <<query<<endl;
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	PQclear(presult);
}

//
void Database::updateTableResource( string jidBare, string resource, string nameSW, string versionSW, string osSW) {

		string query = DB_UPDATE;
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "nameSW = '" + nameSW + "', versionSW = '" + versionSW + "', osSW = '" + osSW +"' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		cout <<query<<endl;
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	PQclear(presult);

}

bool Database::updateTableResource( string jidBare, string presence, string status, string resource, int priority, string ver) {

	bool update = false;
	string query = DB_UPDATE;
	if( existResource(jidBare, resource) ) //uzivatelsky ucet s mistem existuje, aktualizuji
	{
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "', priority=" + numToStr(priority) + ", ver = '" + ver + "' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		cout <<query<<endl;
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		update = true;
	}
	else					// uzivatel s uctem neexistuje, vytvorim
	{
		query = DB_INSERT;
		query += "resource (jidbare, presence, status, date, priority, resource, ver) VALUES ('"+ jidBare + "', '"+ presence +"', '"+Database::convertXML(status)+"', timestamp '" +this->sTime + "', "+ numToStr(priority)+", '"+resource+"', '"+ver+"');";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		update = false;
	}

	PQclear(presult);

	return update;
}


bool Database::updateTableResource( string jidBare, string presence, string status, string resource, int priority) {

	bool update = false;
	string query = DB_UPDATE;
	if( existResource(jidBare, resource) ) //uzivatelsky ucet s mistem existuje, aktualizuji
	{
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "', priority=" + numToStr(priority) + " " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		cout <<query<<endl;
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		update = true;
	}
	else					// uzivatel s uctem neexistuje, vytvorim
	{
		query = DB_INSERT;
		query += "resource (jidbare, presence, status, date, priority, resource) VALUES ('"+ jidBare + "', '"+ presence +"', '"+Database::convertXML(status)+"', timestamp '" +this->sTime + "', "+ numToStr(priority)+", '"+resource+"');";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		update = false;
	}

	PQclear(presult);

	return update;
}


void Database::updateTableResource( string jidBare, string presence, string status, string resource) {

		string query = DB_UPDATE;
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		cout<<query<<endl;
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
	query += "debug ( area, dateAdd, level, message) VALUES ("+ numToStr(area) + ", timestamp '" + this->sTime + "', ";
	query += numToStr( level ) + ", '" + Database::convertXML(message) + "');";
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
	query += "xml ( area, dateAdd, level, message) VALUES ("+ numToStr(area) + ", timestamp '" + this->sTime + "', ";
	query += numToStr( level ) + ", '" + Database::convertXML(message) + "');";
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


void Database::dropAll() {

	//Database::dropTable( "debug" );
	//Database::dropTable( "level" );
	//Database::dropTable( "logarea" );
	//Database::dropTable( "userjid" );
	//Database::dropTable( "vcard" );
	//Database::dropTable( "xml" );
	//Database::dropTable( "presence" );
	//Database::dropTable( "message" );
	//Database::dropTable( "geoloc" );

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
		
		
void Database::clearResourceTable( void ) {

	presult = PQexec(this->psql, "SELECT jidbare, presence, id FROM resource;");
	
	int nFields = PQnfields(presult);
	int nTuples = PQntuples(presult);

				cout<<"ooo1"<<endl;
	string jid;
	string p_str;
	int p_str1;
	for( int i = 0; i < nTuples; i++ )
	{
			jid = PQgetvalue(presult,i , 0);
			mapVer.insert(make_pair(string(jid),	string( PQgetvalue(presult,i , 2) )));
	}
	for( int i = 0; i < nTuples; i++ )
	{
		if( "Unavaliable" == (p_str=PQgetvalue(presult,i,1)) )
		{
			if( (int)mapVer.count(PQgetvalue(presult,i,0)) >= 200)
			{
				multimap<string,string>::iterator it1;
				it1=mapVer.find(PQgetvalue(presult, i,0));
				string s = "DELETE FROM resource where id ='";
				s += PQgetvalue(presult,i,2);
				s += "';";
				PQexec(this->psql, s.c_str());
				mapVer.erase(it1);
			}
		}
	}
}

void Database::initListVer( void ) {

	presult = PQexec(this->psql, "SELECT jidbare, resource, ver FROM resource;");
	
	int nFields = PQnfields(presult);
	int nTuples = PQntuples(presult);

	string jid;
	for( int i = 0; i < nTuples; i++ )
	{
			jid = PQgetvalue(presult,i , 0);
			jid += "/";
			jid += PQgetvalue(presult,i , 1);
			listVer.insert(make_pair(string(jid),	string( PQgetvalue(presult,i , 2) )));
	}
	map<string, string>::iterator it;
	for( it = listVer.begin(); it != listVer.end(); it++ )
	{
		cout << it->first << it->second <<endl;
	}
	
}

void Database::insertTableGeoloc( Geoloc* geoloc ) {

	string query = DB_DEF_GEOLOC;
	Database::getTime();

	string p_str = geoloc->timestamp();
	if( geoloc->timestamp() == "" )
		p_str = this->sTime;

	query += "'";
	query += geoloc->jid().bare() + "', timestamp '";
	query += this->sTime;
	query += "', '" + geoloc->id() + "', " + numToStr( geoloc->accuracy() ) + 
	", " + numToStr(geoloc->alt()) + ", '" + convertXML(geoloc->area()) + "', " 
	+ numToStr( geoloc->bearing() ) + ", '" + convertXML( geoloc->building() ) + "', '" 
	+ convertXML( geoloc->country() ) + "', '" 
	+ convertXML( geoloc->countrycode() ) 
	+ "', '" + convertXML( geoloc->datum() ) + "', '" 
	+ convertXML( geoloc->description() ) + "', " + numToStr( geoloc->error() ) 
	+ ", '" + convertXML( geoloc->floor() ) + "', " + numToStr( geoloc->lat() ) 
	+ ", '" + convertXML( geoloc->locality() ) + "', " + numToStr( geoloc->lon() ) 
	+ ", '" + convertXML( geoloc->postalcode() ) + "', '" + convertXML( geoloc->region() ) 
	+ "', '" + convertXML( geoloc->room() ) + "', " + numToStr( geoloc->speed() ) 
	+ ", '" 	+ convertXML( geoloc->street() ) + "', '" + convertXML( geoloc->text() ) 
	+ "', timestamp '" + convertXML(p_str ) 
	+ "', '" + convertXML( geoloc->uri() ) + "');";
		cout <<query<<endl;
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}


void Database::insertTableTune( Tune* tune ) {

	string query = DB_DEF_TUNE;
	Database::getTime();

	query += "'";
	query += tune->jid().bare() + "', timestamp '";
	query += this->sTime;
	query += "', '" + tune->id() + "', '" + convertXML( tune->artist() ) + "', " + numToStr(tune->length()) + ", " + numToStr(tune->rating()) + ", '" 
	+ convertXML( tune->source() ) + "', '"	+ convertXML( tune->title() )	+ "', '" + convertXML( tune->track() ) + "', '" + convertXML( tune->uri() ) + "');";
		cout <<query<<endl;
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}


void Database::insertTableMood( Mood* mood ) {

	string query = DB_DEF_MOOD;
	Database::getTime();
	query += "'";
	query += mood->jid().bare() + "', timestamp '";
	query += this->sTime;
	query += "', '" + mood->id() + "', '" + convertXML( mood->mood() ) + "', '" + convertXML( mood->text() ) + "');";
		cout <<query<<endl;
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTableActivity( Activity* activity ) {

	string query = DB_DEF_ACTIVITY;
	Database::getTime();
	query += "'";
	query += activity->jid().bare() + "', timestamp '";
	query += this->sTime;
	query += "', '" + activity->id() + "', '" + convertXML( activity->activity() ) + "', '" + convertXML( activity->spec() ) + "', '" + convertXML( activity->text() ) + "');";
		cout <<query<<endl;
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}
