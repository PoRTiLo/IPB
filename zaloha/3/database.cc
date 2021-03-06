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

Database::Database( std::string shostaddr, std::string sdbname, std::string suser, std::string spassword, std::string sconnectTimeout,  std::string sport )
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
	
	std::string shostaddr = "hostaddr = '";
	std::string sport = "' port = '";
	std::string sdbname = "' dbname = '";
	std::string suser = "' user = '";
	std::string spassword = "' password = '";
	std::string sconnect_timeout = "' connect_timeout = '";
	std::string sconnInfo = "";
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

void Database::dropTable( const std::string nameTable ) {

	std::string query = DB_D_T_I_E + nameTable + "CASCADE;";
	presult = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "CHYBA MAZANI TABLKY\n");	
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

bool Database::createTable( const std::string nameTable, const std::string structTable ) {

	std::string query = DB_SELECT_ALL + nameTable + ";";
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


void Database::insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence, const int priority, const std::string nameSW, const std::string versionSW, const std::string osSW ) {

	std::string query = DB_DEF_PRESENCE;
	Database::getTime();
	query += "timestamp '";
	query += this->sTime;
	query += "', '" + jid + "', 'JabInfo@jabbim.cz', '";
	query += Database::convertXML(msg) + "', '" +  name + "', '" + resource + "', '" + Database::convertXML(presence) + "', " + numToStr( priority )+", '" + nameSW + "', '" + versionSW + "', '" + osSW + "');";
	presult = PQexec( this->psql, query.c_str() );
	if(PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence ) {

	std::string query = DB_DEF_PRESENCE1;
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

bool Database::insertVCard( const VCard * v, std::string jidBare ) {


	std::string p_pom = "SELECT family, given, middle, prefix, suffix, nickname, url, bday, jabberid, title, role, note, mailer, rev, uid, tz, prodid, sortstring, photoExtval, photoBinval, photoType, logoExtval, logoBinval, logoType, geoLat, geoLon, orgName	FROM vcard WHERE dateadd= (SELECT MAX(dateadd) FROM vcard where jid = '" + jidBare+"');";
	
	presult = PQexec(this->psql, p_pom.c_str());
	
	int nTuples = PQntuples(presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

// nekontroluje polozku orgUnits
	if( PQgetvalue(presult,0,0) == v->name().family &&	 PQgetvalue(presult,0,1) == v->name().given && PQgetvalue(presult,0,2) == v->name().middle && PQgetvalue(presult,0,3) == v->name().prefix &&
	 PQgetvalue(presult,0,4) == v->name().suffix && PQgetvalue(presult,0,5) == v->nickname() && PQgetvalue(presult,0,6) == v->url() && PQgetvalue(presult,0,7) == v->bday() &&
	 PQgetvalue(presult,0,8) == v->jabberid() &&	 PQgetvalue(presult,0,9) == v->title() &&	 PQgetvalue(presult,0,10) == v->role() &&	 PQgetvalue(presult,0,11) == v->note() &&
	 PQgetvalue(presult,0,12) == v->mailer() && PQgetvalue(presult,0,13) == v->rev() && PQgetvalue(presult,0,14) == v->uid() && PQgetvalue(presult,0,15) == v->tz() &&
	 PQgetvalue(presult,0,16) == v->prodid() && PQgetvalue(presult,0,17) == v->sortstring() && PQgetvalue(presult,0,18) == v->photo().extval  && 
	 PQgetvalue(presult,0,19) == convertXML(Base64::encode64(v->photo().binval))  &&  PQgetvalue(presult,0,20) == v->photo().type && 
	 PQgetvalue(presult,0,21) == v->logo().extval &&  PQgetvalue(presult,0,22) == convertXML(Base64::encode64(v->logo().binval) ) && PQgetvalue(presult,0,23) == v->logo().type &&
	 PQgetvalue(presult,0,24) == v->geo().latitude &&  PQgetvalue(presult,0,25) == v->geo().longitude  &&  PQgetvalue(presult,0,26) == v->org().name  )
	{
		return false;
	}
	else
		return true;
}

void Database::insertTableVCard( const VCard* v , std::string jidBare) {

	Database::getTime();
	if( insertVCard( v, jidBare ) )
	{
		std::string query = DB_INSERT;
		query += "vcard ( jid, dateAdd, family, given, middle, prefix, suffix, nickname, url, bday, jabberid, title, role, note, mailer, rev, uid, tz, prodid, sortstring, photoExtval, photoBinval, photoType, logoExtval, logoBinval, logoType, geoLat, geoLon, orgName, orgUnits) VALUES ( '";
		query += jidBare + "', timestamp '" + this->sTime + "', '" + v->name().family + "', '" + v->name().given + "', '" + v->name().middle + "', '" + v->name().prefix + "', '" + v->name().suffix + "', '" + v->nickname() + "', '" + v->url() + "', '";
		query += v->bday() + "', '" + v->jabberid() + "', '" + v->title() + "', '" + v->role() + "', '" + v->note() + "', '" + v->mailer() + "', '" + v->rev() + "', '" + v->uid() + "', '" + v->tz() + "', '" + v->prodid() + "', '"; 
		query += v->sortstring() + "','" + v->photo().extval + "', '" + convertXML(Base64::encode64(v->photo().binval)) + "', '" + v->photo().type + "', '" + v->logo().extval + "', '" + convertXML(Base64::encode64(v->logo().binval)) + "', '" + convertXML(v->logo().type) + "',";
		if( v->geo().latitude == "")
			query +=  "0, ";
		else
			query += v->geo().latitude + ", ";
		if( v->geo().longitude == "" )
			query += "0, '";
		else
			query +=  v->geo().longitude + ", '";
			
		query += v->org().name + "', '"+listToString(v->org().units)+"');";

//std::cout<<query<<std::endl;

		presult = PQexec( this->psql, query.c_str() );
		if(PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		PQclear(presult);
	}
}

std::string Database::listToString( gloox::StringList units ) {

	std::string p_pom;
	std::list<std::string>::iterator it;
	for( it = units.begin() ; it != units.end(); it++ )
	{
		p_pom += *it + ", ";
	}
	return p_pom;
}

void Database::insertTableMessage( const std::string jid, const std::string msg, const std::string subject, const std::string thread, const std::string subtype ) {

	Database::getTime();
	std::string query = DB_DEF_MESSAGE;
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

void Database::insertTableConst( const std::string query ) {
	
	presult = PQexec( this->psql, query.c_str() );
	if( PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

void Database::insertTableUser( std::string jidBare) {

	if( !existUser(jidBare) )
	{
		//vlozeni noveho uzivatele

		Database::getTime();
		std::string query = DB_INSERT;
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

void Database::updateTableStatus( std::string user ) {

	std::string query = "Select * from resource where jidbare = '";
	query += user + "';";
	presult = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult) == PGRES_TUPLES_OK)
	{
		int nFields = PQnfields(presult);	//sloupec
		int nTuples = PQntuples(presult);	//radek
		int priority = -127;
		std::string pom, pomS;
		int pomInt = 0;
		int culomn = -1;
		for( int i = 0; i < nTuples; i++ )
		{
				pom = PQgetvalue(presult,i,5);
				pomS = PQgetvalue(presult,i,2);
				std::string some_string;
				std::istringstream buffer(pom);
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
				std::string some_string;
				std::istringstream buffer(pom);
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

void Database::updateTableStatus( std::string jidBare,std::string presence,std::string status,std::string resource,std::string nameSW) {

		Database::getTime();
		std::string query = DB_UPDATE;
		query += "status ";
		query += DB_SET;
		query += "presence = '" + presence + "', status = '" + Database::convertXML(status) + "', date = timestamp '" + this->sTime + "', resource='" + resource + "' , nameSW = '" + nameSW + "' " + DB_WHERE + "jidbare = '" + jidBare +	"';";
		presult = PQexec( this->psql, query.c_str() );
		if( PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
	PQclear(presult);
}

//
void Database::updateTableResource( std::string jidBare,std::string resource,std::string nameSW,std::string versionSW,std::string osSW) {

	std::string query = DB_UPDATE;
	Database::getTime();
	query += "resource ";
	query += DB_SET;
	query += "nameSW = '" + nameSW + "', versionSW = '" + versionSW + "', osSW = '" + osSW +"' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
	presult = PQexec( this->psql, query.c_str() );
	if( PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

bool Database::updateTableResource( SwVersion* swVersion ) {

	std::string query = DB_UPDATE;
	Database::getTime();
	query += "resource ";
	query += DB_SET;
	if( (swVersion->version() != "") && (swVersion->osVersion() != "") )
		query += "nameSW = '" + swVersion->name() + "', versionSW = '" + swVersion->version() + "', osSW = '" + swVersion->osVersion() + "', category = '" + swVersion->category() + "',type = '" + swVersion->type() + "', jingleVoice = " +swVersion->jingleVoice() + ", jingleVideo = " + swVersion->jingleVideo() + ", googleVideo = " + swVersion->googleVideo() + ", googleVoice = " + swVersion->googleVoice() + " "+  DB_WHERE + "jidbare = '" + swVersion->jid().bare()+"' AND resource = '"+swVersion->jid().resource()+"';";
	else if( (swVersion->version() == "") && (swVersion->osVersion() == "") )
		query += "nameSW = '" + swVersion->name() + "', category = '" + swVersion->category() + "',type = '" + swVersion->type() + "', jingleVoice = " +swVersion->jingleVoice() + ", jingleVideo = " + swVersion->jingleVideo() + ", googleVideo = " + swVersion->googleVideo() + ", googleVoice = " + swVersion->googleVoice() + " "+  DB_WHERE + "jidbare = '" + swVersion->jid().bare()+"' AND resource = '"+swVersion->jid().resource()+"';";
	presult = PQexec( this->psql, query.c_str() );
	if( PQresultStatus(presult) != PGRES_COMMAND_OK )
	{
		PQclear(presult);
		Database::exitError();
	}
	PQclear(presult);
}

bool Database::updateTableResource( std::string jidBare,std::string presence,std::string status,std::string resource, int priority,std::string ver) {

	bool update = false;
	std::string query = DB_UPDATE;
	if( existResource(jidBare, resource) ) //uzivatelsky ucet s mistem existuje, aktualizuji
	{
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "', priority=" + numToStr(priority) + ", ver = '" + ver + "' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
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


bool Database::updateTableResource( std::string jidBare,std::string presence,std::string status,std::string resource, int priority) {

	bool update = false;
	std::string query = DB_UPDATE;
	if( existResource(jidBare, resource) ) //uzivatelsky ucet s mistem existuje, aktualizuji
	{
		Database::getTime();
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + this->sTime + "', priority=" + numToStr(priority) + " " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
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


void Database::updateTableResource( std::string jidBare,std::string presence,std::string status,std::string resource) {

		std::string query = DB_UPDATE;
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
bool Database::existResource( const std::string user, const std::string resource ) {

	std::string query = "Select jidbare from resource where jidbare = '";
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

bool Database::existUser( const std::string user ) {

	std::string query = "Select jidbare from userjid where jidbare = '";
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

void Database::insertTableDebug( int level, int area, const std::string message ) {

	Database::getTime();
	std::string query = DB_INSERT;
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

void Database::insertTableXML( int level, int area, const std::string message ) {
//	std::string parserMes = message;
//	parser->feed(parserMes);
	Database::getTime();
	std::string query = DB_INSERT;
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

std::string Database::convertXML(std::string message ) {

	size_t lenght = message.length();
	char mess[2*lenght+1];
	const char* pom = message.c_str();
	PQescapeString( mess, pom, lenght );
	std::string back(mess);
	return back;
}

std::string Database::convertBinary(std::string message ) {

	size_t lenght = message.length();
	unsigned char* mess;
	const unsigned char* y;
	y = (unsigned char* ) message.c_str();
	size_t len1 = 3*lenght+1;
	size_t* len = &len1;
	mess = PQescapeByteaConn( this->psql,y, 	lenght,	len );
	std::string blah = reinterpret_cast < const char* >( mess );
	return blah;
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

void Database::strToTime( std:: string p_time ) {

	struct tm * lt_time;
	std::string p_pom = "timestamp 2011-03-22 10:37:23";
	lt_time->tm_year = stringToInt(p_pom.substr(10,4))-1900;
	lt_time->tm_mon = stringToInt(p_pom.substr(15,2)) - 1;
	lt_time->tm_mday = stringToInt(p_pom.substr(18,2));
	lt_time->tm_hour = stringToInt(p_pom.substr(21,2));
	lt_time->tm_min = stringToInt(p_pom.substr(24,2));
	lt_time->tm_sec = stringToInt(p_pom.substr(27,2));

	time_t times;
	times = time(NULL);
	//if( difftime(times, mktime(lt_time)) > 60 )

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

std::string Database::printUser() const {

	PGresult* presult;
	presult = PQexec(this->psql, "SELECT jidbare FROM userjid;");
	

	int nFields = PQnfields(presult);
	int nTuples = PQntuples(presult);

	std::string result;
	std::stringstream ss;
	std::string back;
	for( int i = 0; i < nTuples; i++ )
	{
		ss << PQgetvalue(presult,i , 0);
		ss >> back;
		result += " - " + std::string( PQgetvalue(presult,i , 0)) + "\n";
	}
	return result;
}
		
		
void Database::clearResourceTable( void ) {

	presult = PQexec(this->psql, "SELECT jidbare, presence, id FROM resource;");
	
	int nFields = PQnfields(presult);
	int nTuples = PQntuples(presult);

	std::string jid;
	std::string p_str;
	int p_str1;
	for( int i = 0; i < nTuples; i++ )
	{
			jid = PQgetvalue(presult,i , 0);
			mapVer.insert(make_pair(std::string(jid),	std::string( PQgetvalue(presult,i , 2) )));
	}
	for( int i = 0; i < nTuples; i++ )
	{
		if( "Unavaliable" == (p_str=PQgetvalue(presult,i,1)) )
		{
			if( (int)mapVer.count(PQgetvalue(presult,i,0)) >= 200)
			{
				std::multimap<std::string,std::string>::iterator it1;
				it1 = mapVer.find(PQgetvalue(presult, i,0));
				std::string s = "DELETE FROM resource where id ='";
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

	std::string jid;
	for( int i = 0; i < nTuples; i++ )
	{
			jid = PQgetvalue(presult,i , 0);
			jid += "/";
			jid += PQgetvalue(presult,i , 1);
			listVer.insert(make_pair(std::string(jid), std::string( PQgetvalue(presult,i , 2) )));
	}
//	std::map<std::string,std::string>::iterator it;
//	for( it = listVer.begin(); it != listVer.end(); it++ )
//	{
//		cout << it->first << it->second <<endl;
//	}
	
}

//vrati true vkladam do DB
bool Database::insertGeoloc( std::string jid, bool empty) {

	
	sTime[17] = '0';
	sTime[18] = '0';
	std::string p_pom = "SELECT id, lon, lat FROM geoloc WHERE jidbare = '" +jid+"' AND time >= timestamp '";
	p_pom +=this->sTime;
	p_pom +="';";
	presult = PQexec(this->psql, p_pom.c_str());
	
	int nFields = PQnfields(presult);
	int nTuples = PQntuples(presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

	if( !empty )				// v databazi je udaj, chci vkladat ale novejsi neprazdny udaj, smazu stary z db
	{
		std::string s = "DELETE FROM geoloc where id ='";
		s += PQgetvalue(presult,nTuples-1,0);
		s += "';";
		PQexec(this->psql, s.c_str());
		return true;
	}

	return false;
}

void Database::insertTableGeoloc( Geoloc* geoloc ) {

	std::string query = DB_DEF_GEOLOC;
	Database::getTime();

	bool cont = true;
	if( geoloc->lon() == 0 && geoloc->lat() == 0 )
	{
		cont = insertGeoloc( geoloc->jid().bare(), true );
	}
	else
		cont = insertGeoloc( geoloc->jid().bare(), false );

	Database::getTime();
	if( cont )
	{
		std::string p_str = geoloc->timestamp();
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
		presult = PQexec( this->psql, query.c_str() );
		if(PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		PQclear(presult);
	}
}


bool Database::insertTune( Tune* tune ) {

	
	sTime[17] = '0';
	sTime[18] = '0';
	std::string p_pom = "SELECT id, artist, source, title FROM tune WHERE jidbare = '" +tune->jid().bare()+"' AND time >= timestamp '";
	p_pom +=this->sTime;
	p_pom +="';";
	presult = PQexec(this->psql, p_pom.c_str());
	
	int nTuples = PQntuples(presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;


	if( PQgetvalue(presult,nTuples-1,1) == tune->artist() && PQgetvalue(presult,nTuples-1,2) == tune->title() && PQgetvalue(presult,nTuples-1,3) == tune->title() )
		return false;
	else if( PQgetvalue(presult,nTuples-1,1) == "" && PQgetvalue(presult,nTuples-1,2) == "" && PQgetvalue(presult,nTuples-1,3) == "" )
	{
		std::string s = "DELETE FROM tune where id ='";
		s += PQgetvalue(presult,nTuples-1,0);
		s += "';";
		PQexec(this->psql, s.c_str());
		return true;
	}
	else
		return true;
}

void Database::insertTableTune( Tune* tune ) {

	std::string query = DB_DEF_TUNE;
	Database::getTime();

	if( insertTune(tune))
	{
		query += "'";
		query += tune->jid().bare() + "', timestamp '";
		query += this->sTime;
		query += "', '" + tune->id() + "', '" + convertXML( tune->artist() ) + "', " + numToStr(tune->length()) + ", " + numToStr(tune->rating()) + ", '" 
		+ convertXML( tune->source() ) + "', '"	+ convertXML( tune->title() )	+ "', '" + convertXML( tune->track() ) + "', '" + convertXML( tune->uri() ) + "');";
		presult = PQexec( this->psql, query.c_str() );
		if(PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		PQclear(presult);
	}
}


bool Database::insertMood( Mood* mood ) {

	
	sTime[17] = '0';
	sTime[18] = '0';
	std::string p_pom = "SELECT id, mood, text FROM mood WHERE jidbare = '" + mood->jid().bare() + "' AND time >= timestamp '";
	p_pom +=this->sTime;
	p_pom +="';";
	presult = PQexec(this->psql, p_pom.c_str());
	
	int nTuples = PQntuples(presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

	if( PQgetvalue(presult,nTuples-1,1) == mood->mood() && PQgetvalue(presult,nTuples-1,2) == mood->text() )
		return false;
	else if( PQgetvalue(presult,nTuples-1,1) == "" && PQgetvalue(presult,nTuples-1,2) == "" )
	{
		std::string s = "DELETE FROM mood where id ='";
		s += PQgetvalue(presult,nTuples-1,0);
		s += "';";
		PQexec(this->psql, s.c_str());
		return true;
	}
	else
		return true;
}

void Database::insertTableMood( Mood* mood ) {

	std::string query = DB_DEF_MOOD;
	Database::getTime();

	if( insertMood( mood ) )
	{
		query += "'";
		query += mood->jid().bare() + "', timestamp '";
		query += this->sTime;
		query += "', '" + mood->id() + "', '" + convertXML( mood->mood() ) + "', '" + convertXML( mood->text() ) + "');";
		presult = PQexec( this->psql, query.c_str() );
		if(PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		PQclear(presult);
	}
}

bool Database::insertActivity( Activity* activity ) {

	
	sTime[17] = '0';
	sTime[18] = '0';
	std::string p_pom = "SELECT id, activity, spec, text FROM activity WHERE jidbare = '" + activity->jid().bare() + "' AND time >= timestamp '";
	p_pom +=this->sTime;
	p_pom +="';";
	presult = PQexec(this->psql, p_pom.c_str());
	
	int nTuples = PQntuples(presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

	if( PQgetvalue(presult,nTuples-1,1) == activity->activity() && PQgetvalue(presult,nTuples-1,2) == activity->spec() && PQgetvalue(presult,nTuples-1,3) == activity->text() )
		return false;
	else if( PQgetvalue(presult,nTuples-1,1) == "" && PQgetvalue(presult,nTuples-1,2) == "" && PQgetvalue(presult,nTuples-1,3) == "" )
	{
		std::string s = "DELETE FROM activity where id ='";
		s += PQgetvalue(presult,nTuples-1,0);
		s += "';";
		PQexec(this->psql, s.c_str());
		return true;
	}
	else
		return true;
}

void Database::insertTableActivity( Activity* activity ) {

	std::string query = DB_DEF_ACTIVITY;
	Database::getTime();
	if( insertActivity( activity ) )
	{
		query += "'";
		query += activity->jid().bare() + "', timestamp '";
		query += this->sTime;
		query += "', '" + activity->id() + "', '" + convertXML( activity->activity() ) + "', '" + convertXML( activity->spec() ) + "', '" + convertXML( activity->text() ) + "');";
		presult = PQexec( this->psql, query.c_str() );
		if(PQresultStatus(presult) != PGRES_COMMAND_OK )
		{
			PQclear(presult);
			Database::exitError();
		}
		PQclear(presult);
	}
}
char* Database::timeDatabase() {

	return this->sTime;
}
