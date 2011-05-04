#include "database.h"
#include "const.h"

// konstruktor
Database::Database()
{
	this->m_hostaddr = DB_ADDR;
	this->m_dbname = DB_NAME;
	this->m_user = DB_USER;
	this->m_password = DB_PASS;
	this->m_connectTimeout = DB_TIME;
	this->m_port = DB_PORT;
	this->m_connInfo = "";
}

// konstruktor
Database::Database( std::string shostaddr, std::string sdbname, std::string suser, std::string spassword, std::string sconnectTimeout,  std::string sport )
{
	this->m_hostaddr = shostaddr;
	this->m_dbname = sdbname;
	this->m_user = suser;
	this->m_password = spassword;
	this->m_connectTimeout = sconnectTimeout;
	this->m_port = sport;
	this->m_connInfo = "";
}

/////////////////////////////////////////////////////////////// PRIVATE METODY ///////////////////////////////////////////////////////////////

// vytvori retezec s udaji pro spojeni s databazi
void Database::makeStringConnect() {
	
	std::string shostaddr = "hostaddr = '";
	std::string sport = "' port = '";
	std::string sdbname = "' dbname = '";
	std::string suser = "' user = '";
	std::string spassword = "' password = '";
	std::string sconnect_timeout = "' connect_timeout = '";
	std::string sconnInfo = "";
	this->m_connInfo += shostaddr + this->m_hostaddr + sport + this->m_port + sdbname + this->m_dbname + suser + this->m_user + spassword + this->m_password + sconnect_timeout + this->m_connectTimeout +"'";
}


// inicializace databaze (tvorba tabulek)
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

// navazani spojeni s databazi
void Database::connect() {
	
	Database::makeStringConnect();
	this->m_psql = PQconnectdb(this->m_connInfo.c_str());
	if( !this->m_psql )
	{
		fprintf(stderr, "Error\n");
		Database::exitError();
	}

	//connect
	if( PQstatus(this->m_psql) != CONNECTION_OK )
	{
		fprintf(stderr, "chyba PRIPOJENI\n");
		Database::exitError();
	}

}

// tvorba vsech tabulek v databazi
bool Database::createTable( const std::string nameTable, const std::string structTable ) {

	std::string query = DB_SELECT_ALL + nameTable + ";";
	this->m_presult = PQexec(this->m_psql, query.c_str());
	if(PQresultStatus(this->m_presult) == PGRES_TUPLES_OK)
	{
		//printf("exec %s existuje", nameTable.c_str());
		PQclear(this->m_presult);
		return false;
	}
	else
	{
		query = DB_C_T + nameTable + " (" + structTable + ");";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK)
		{
			fprintf(stderr, "CHYNA dotazu\n");
			PQclear(this->m_presult);
			Database::exitError();
			return false;
		}
	}
	PQclear(this->m_presult);
	return true;
}

// existuje uzivatel v databazi?
bool Database::existUser( const std::string user ) {

	std::string query = "Select jidbare from userjid where jidbare = '";
	query += user + "';";

	this->m_presult = PQexec(this->m_psql, query.c_str());
	if(PQresultStatus(this->m_presult) == PGRES_TUPLES_OK)
	{
		if( PQntuples(this->m_presult) == 0 )
			return false;
		else
			return true;
	}
	else
		return false;
}

// je dane resource uzivatele v dattabazi?
bool Database::existResource( const std::string user, const std::string resource ) {

	std::string query = "Select jidbare from resource where jidbare = '";
	query += user + "' and resource = '";
	query += resource + "';";
	this->m_presult = PQexec(this->m_psql, query.c_str());
	if(PQresultStatus(this->m_presult) == PGRES_TUPLES_OK)
	{

		if( PQntuples(this->m_presult) == 0 )
			return false;
		else
			return true;
	}
	else
		return false;
}

////////////////////////////////////////////////// vkladaci metody //////////////////////

// vlozeni data do tabulky const
void Database::insertTableConst( const std::string query ) {
	
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}

//vrati true vkladam do DB
bool Database::insertGeoloc( std::string jid, bool empty) {

	
	this->sTime[17] = '0';
	this->sTime[18] = '0';
	std::string p_pom = "SELECT id, lon, lat FROM geoloc WHERE jidbare = '" +jid+"' AND time >= timestamp '";
	p_pom += this->sTime;
	p_pom += "';";
	this->m_presult = PQexec(this->m_psql, p_pom.c_str());
	
	int nFields = PQnfields(this->m_presult);
	int nTuples = PQntuples(this->m_presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

	if( !empty )				// v databazi je udaj, chci vkladat ale novejsi neprazdny udaj, smazu stary z db
	{
		std::string s = "DELETE FROM geoloc where id ='";
		s += PQgetvalue(this->m_presult,nTuples-1,0);
		s += "';";
		PQexec(this->m_psql, s.c_str());
		return true;
	}

	return false;
}


bool Database::insertTune( Tune* tune ) {

	
	this->sTime[17] = '0';
	this->sTime[18] = '0';
	std::string p_pom = "SELECT id, artist, source, title FROM tune WHERE jidbare = '" +tune->jid().bare()+"' AND time >= timestamp '";
	p_pom += this->sTime;
	p_pom += "';";
	this->m_presult = PQexec(this->m_psql, p_pom.c_str());
	
	int nTuples = PQntuples(this->m_presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;


	if( PQgetvalue(this->m_presult,nTuples-1,1) == tune->artist() && PQgetvalue(this->m_presult,nTuples-1,2) == tune->title() && PQgetvalue(this->m_presult,nTuples-1,3) == tune->title() )
		return false;
	else if( PQgetvalue(this->m_presult,nTuples-1,1) == "" && PQgetvalue(m_presult,nTuples-1,2) == "" && PQgetvalue(m_presult,nTuples-1,3) == "" )
	{
		std::string s = "DELETE FROM tune where id ='";
		s += PQgetvalue(this->m_presult,nTuples-1,0);
		s += "';";
		PQexec(this->m_psql, s.c_str());
		return true;
	}
	else
		return true;
}



bool Database::insertMood( Mood* mood ) {

	
	this->sTime[17] = '0';
	this->sTime[18] = '0';
	std::string p_pom = "SELECT id, mood, text FROM mood WHERE jidbare = '" + mood->jid().bare() + "' AND time >= timestamp '";
	p_pom += this->sTime;
	p_pom += "';";
	this->m_presult = PQexec(this->m_psql, p_pom.c_str());
	
	int nTuples = PQntuples(this->m_presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

	if( PQgetvalue(this->m_presult,nTuples-1,1) == mood->mood() && PQgetvalue(this->m_presult,nTuples-1,2) == mood->text() )
		return false;
	else if( PQgetvalue(this->m_presult,nTuples-1,1) == "" && PQgetvalue(this->m_presult,nTuples-1,2) == "" )
	{
		std::string s = "DELETE FROM mood where id ='";
		s += PQgetvalue(this->m_presult,nTuples-1,0);
		s += "';";
		PQexec(this->m_psql, s.c_str());
		return true;
	}
	else
		return true;
}


bool Database::insertActivity( Activity* activity ) {

	this->sTime[17] = '0';
	this->sTime[18] = '0';
	std::string p_pom = "SELECT id, activity, spec, text FROM activity WHERE jidbare = '" + activity->jid().bare() + "' AND time >= timestamp '";
	p_pom += this->sTime;
	p_pom += "';";
	this->m_presult = PQexec(this->m_psql, p_pom.c_str());
	
	int nTuples = PQntuples(this->m_presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

	if( PQgetvalue(this->m_presult,nTuples-1,1) == activity->activity() && PQgetvalue(this->m_presult,nTuples-1,2) == activity->spec() && PQgetvalue(this->m_presult,nTuples-1,3) == activity->text() )
		return false;
	else if( PQgetvalue(this->m_presult,nTuples-1,1) == "" && PQgetvalue(this->m_presult,nTuples-1,2) == "" && PQgetvalue(this->m_presult,nTuples-1,3) == "" )
	{
		std::string s = "DELETE FROM activity where id ='";
		s += PQgetvalue(this->m_presult,nTuples-1,0);
		s += "';";
		PQexec(this->m_psql, s.c_str());
		return true;
	}
	else
		return true;
}

// aktualizuje tabulku status
void Database::updateTableStatus( std::string jidBare,std::string presence,std::string status,std::string resource,std::string nameSW, std::string jingleVi, std::string jingleVo, std::string googleVo, std::string googleVi) {

	std::string query = DB_UPDATE;
	query += "status ";
	query += DB_SET;
	query += "presence = '" + presence + "', status = '" + Database::convertXML(status) + "', date = timestamp '" + getTime() + "', resource='" + resource + "' , nameSW = '" + nameSW + "', jingleVideo ="+boolToString(jingleVi) +", jingleVoice ="+boolToString(jingleVo)+ ", googleVoice = "+boolToString(googleVo) +", googleVideo ="+boolToString(googleVi) + " "+ DB_WHERE + "jidbare = '" + jidBare +"';";
std::cout<<query<<std::endl;
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void Database::dropTable( const std::string nameTable ) {

	std::string query = DB_D_T_I_E + nameTable + "CASCADE;";
	this->m_presult = PQexec(this->m_psql, query.c_str());
	if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "CHYBA MAZANI TABLKY\n");	
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}
*/




bool Database::insertVCard( const VCard * v, std::string jidBare ) {


	std::string p_pom = "SELECT family, given, middle, prefix, suffix, nickname, url, bday, jabberid, title, role, note, mailer, rev, uid, tz, prodid, sortstring, photoExtval, photoBinval, photoType, logoExtval, logoBinval, logoType, geoLat, geoLon, orgName	FROM vcard WHERE dateadd= (SELECT MAX(dateadd) FROM vcard where jid = '" + jidBare+"');";
	
	this->m_presult = PQexec(this->m_psql, p_pom.c_str());
	
	int nTuples = PQntuples(this->m_presult);

	if( nTuples == 0 )					// zaznam jesete neni v databazi
		return true;

// nekontroluje polozku orgUnits
	if( PQgetvalue(this->m_presult,0,0) == v->name().family &&	 PQgetvalue(m_presult,0,1) == v->name().given && PQgetvalue(m_presult,0,2) == v->name().middle && PQgetvalue(m_presult,0,3) == v->name().prefix &&
	 PQgetvalue(this->m_presult,0,4) == v->name().suffix && PQgetvalue(m_presult,0,5) == v->nickname() && PQgetvalue(m_presult,0,6) == v->url() && PQgetvalue(m_presult,0,7) == v->bday() &&
	 PQgetvalue(this->m_presult,0,8) == v->jabberid() &&	 PQgetvalue(m_presult,0,9) == v->title() &&	 PQgetvalue(m_presult,0,10) == v->role() &&	 PQgetvalue(m_presult,0,11) == v->note() &&
	 PQgetvalue(this->m_presult,0,12) == v->mailer() && PQgetvalue(m_presult,0,13) == v->rev() && PQgetvalue(m_presult,0,14) == v->uid() && PQgetvalue(m_presult,0,15) == v->tz() &&
	 PQgetvalue(this->m_presult,0,16) == v->prodid() && PQgetvalue(m_presult,0,17) == v->sortstring() && PQgetvalue(m_presult,0,18) == v->photo().extval  && 
	 PQgetvalue(this->m_presult,0,19) == convertXML(Base64::encode64(v->photo().binval))  &&  PQgetvalue(m_presult,0,20) == v->photo().type && 
	 PQgetvalue(this->m_presult,0,21) == v->logo().extval &&  PQgetvalue(m_presult,0,22) == convertXML(Base64::encode64(v->logo().binval) ) && PQgetvalue(m_presult,0,23) == v->logo().type &&
	 PQgetvalue(this->m_presult,0,24) == v->geo().latitude &&  PQgetvalue(m_presult,0,25) == v->geo().longitude  &&  PQgetvalue(m_presult,0,26) == v->org().name  )
	{
		return false;
	}
	else
		return true;
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


/**
 *
 *
 */
void Database::exitError() {
	PQfinish(this->m_psql);
	//exit(EXIT_FAILURE);
}






/*
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
*/

std::string Database::printUser() const {

	
	PGresult* presult;
	presult = PQexec(this->m_psql, "SELECT jidbare FROM userjid;");
	

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

	PQclear(presult);

	return result;
}
		
		
void Database::clearResourceTable( void ) {

	this->m_presult = PQexec(this->m_psql, "SELECT jidbare, presence, id FROM resource;");
	
	int nFields = PQnfields(this->m_presult);
	int nTuples = PQntuples(this->m_presult);

	std::string jid;
	std::string p_str;
	int p_str1;
	for( int i = 0; i < nTuples; i++ )
	{
			jid = PQgetvalue(this->m_presult,i , 0);
			mapVer.insert(make_pair(std::string(jid),	std::string( PQgetvalue(this->m_presult,i , 2) )));
	}
	for( int i = 0; i < nTuples; i++ )
	{
		if( "Unavaliable" == (p_str=PQgetvalue(this->m_presult,i,1)) )
		{
			if( (int)mapVer.count(PQgetvalue(this->m_presult,i,0)) >= 200)
			{
				std::multimap<std::string,std::string>::iterator it1;
				it1 = mapVer.find(PQgetvalue(this->m_presult, i,0));
				std::string s = "DELETE FROM resource where id ='";
				s += PQgetvalue(this->m_presult,i,2);
				s += "';";
				PQexec(this->m_psql, s.c_str());
				mapVer.erase(it1);
			}
		}
	}
}

void Database::initListVer( void ) {

	this->m_presult = PQexec(this->m_psql, "SELECT jidbare, resource, ver FROM resource;");
	
	int nFields = PQnfields(this->m_presult);
	int nTuples = PQntuples(this->m_presult);

	std::string jid;
	for( int i = 0; i < nTuples; i++ )
	{
			jid = PQgetvalue(this->m_presult,i , 0);
			jid += "/";
			jid += PQgetvalue(this->m_presult,i , 1);
			listVer.insert(make_pair(std::string(jid), std::string( PQgetvalue(this->m_presult,i , 2) )));
	}
//	std::map<std::string,std::string>::iterator it;
//	for( it = listVer.begin(); it != listVer.end(); it++ )
//	{
//		cout << it->first << it->second <<endl;
//	}
	
}




////////////////////////////////////////////////////////////// PUBLIC METODY ///////////////////////////////////////////////////////

// zahaji spojeni s databazi a inicializaci
void Database::start() {
	
	Database::connect();

	Database::initDb();
}

// ziskani aktualniho casu
char* Database::getTime() {

	time_t times;
	times = time(NULL);
	struct tm *ltmtime = localtime(&times);
  	strftime(this->sTime, 80 - 1, "%Y-%m-%d %H:%M:%S ", ltmtime);

	return this->sTime;
}

/////////////////////////////////////////////// Konvertovaci metody ///////////////////////////////////////////////////////////////

// prevod obrazku z binarni podoby na retezec ASCII znaku
std::string Database::convertBinary(std::string message ) {

	size_t lenght = message.length();
	unsigned char* mess;
	const unsigned char* y;
	y = (unsigned char* ) message.c_str();
	size_t len1 = 3*lenght+1;
	size_t* len = &len1;
	mess = PQescapeByteaConn( this->m_psql,y, 	lenght,	len );
	std::string blah = reinterpret_cast < const char* >( mess );
	return blah;
}

// prevede znaky retezce pomoci ecape znaku, ktere je mozne ulozit do db
std::string Database::convertXML(std::string message ) {

	size_t lenght = message.length();
	char mess[2*lenght+1];
	const char* pom = message.c_str();
	PQescapeString( mess, pom, lenght );
	std::string back(mess);
	return back;
}


/////////////////////////////////////////////// Vkladaci metody ///////////////////////////////////////////////////////////////

// vlozeni dat to tabulky activity
void Database::insertTableActivity( Activity* activity ) {

	Database::getTime();
	std::string query = DB_DEF_ACTIVITY;
	if( insertActivity( activity ) )
	{
		query += "'";
		query += activity->jid().bare() + "', timestamp '";
		query += getTime();
		query += "', '" + activity->id() + "', '" + convertXML( activity->activity() ) + "', '" + convertXML( activity->spec() ) + "', '" + convertXML( activity->text() ) + "');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		PQclear(this->m_presult);
	}
}

// vlozeni dat to tabulky mood
void Database::insertTableMood( Mood* mood ) {

	std::string query = DB_DEF_MOOD;
	Database::getTime();

	if( insertMood( mood ) )
	{
		query += "'";
		query += mood->jid().bare() + "', timestamp '";
		query += getTime();
		query += "', '" + mood->id() + "', '" + convertXML( mood->mood() ) + "', '" + convertXML( mood->text() ) + "');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		PQclear(this->m_presult);
	}
}

// vlozeni dat to tabulky tune
void Database::insertTableTune( Tune* tune ) {

	Database::getTime();
	std::string query = DB_DEF_TUNE;

	if( insertTune(tune))
	{
		query += "'";
		query += tune->jid().bare() + "', timestamp '";
		query += getTime();
		query += "', '" + tune->id() + "', '" + convertXML( tune->artist() ) + "', " + numToStr(tune->length()) + ", " + numToStr(tune->rating()) + ", '" 
		+ convertXML( tune->source() ) + "', '"	+ convertXML( tune->title() )	+ "', '" + convertXML( tune->track() ) + "', '" + convertXML( tune->uri() ) + "');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		PQclear(this->m_presult);
	}
}

// vlozeni dat to tabulky geoloc
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

	if( cont )
	{
		std::string p_str = geoloc->timestamp();
		if( geoloc->timestamp() == "" )
			p_str = getTime();

		query += "'";
		query += geoloc->jid().bare() + "', timestamp '";
		query += getTime();
		query += "', '" + geoloc->id() + "', " + numToStr( geoloc->accuracy() ) + ", " + numToStr(geoloc->alt()) + ", '" + convertXML(geoloc->area()) + "', " 
		+ numToStr( geoloc->bearing() ) + ", '" + convertXML( geoloc->building() ) + "', '"	+ convertXML( geoloc->country() ) + "', '" 
		+ convertXML( geoloc->countrycode() ) + "', '" + convertXML( geoloc->datum() ) + "', '" + convertXML( geoloc->description() ) + "', " + numToStr( geoloc->error() ) 
		+ ", '" + convertXML( geoloc->floor() ) + "', " + numToStr( geoloc->lat() ) + ", '" + convertXML( geoloc->locality() ) + "', " + numToStr( geoloc->lon() ) 
		+ ", '" + convertXML( geoloc->postalcode() ) + "', '" + convertXML( geoloc->region() ) + "', '" + convertXML( geoloc->room() ) + "', " + numToStr( geoloc->speed() ) 
		+ ", '" 	+ convertXML( geoloc->street() ) + "', '" + convertXML( geoloc->text() ) + "', timestamp '" + convertXML(p_str ) + "', '" + convertXML( geoloc->uri() ) + "');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		PQclear(this->m_presult);
	}
}

// vlozeni dat to tabulky vcard
void Database::insertTableVCard( const VCard* v , std::string jidBare) {

	if( insertVCard( v, jidBare ) )
	{
		std::string query = DB_INSERT;
		query += "vcard ( jid, dateAdd, family, given, middle, prefix, suffix, nickname, url, bday, jabberid, title, role, note, mailer, rev, uid, tz, prodid, sortstring, photoExtval, photoBinval, photoType, logoExtval, logoBinval, logoType, geoLat, geoLon, orgName, orgUnits) VALUES ( '";
		query += jidBare + "', timestamp '" + getTime() + "', '" + v->name().family + "', '" + v->name().given + "', '" + v->name().middle + "', '" + v->name().prefix + "', '" + v->name().suffix + "', '" + v->nickname() + "', '" + v->url() + "', '";
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

		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		PQclear(this->m_presult);
	}
}

// vlozeni dat to tabulky user
void Database::insertTableUser( std::string jidBare) {

	if( !existUser(jidBare) )//vlozeni noveho uzivatele
	{
		std::string query = DB_INSERT;
		query += "userjid (jidbare, date) VALUES ('"+ jidBare + "', timestamp '" + getTime() + "');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}

		//status insert user
		query = DB_INSERT;
		query += "status (jidbare) VALUES ('"+ jidBare + "');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
	}
	PQclear(this->m_presult);
}

// vlozeni dat to tabulky debug
void Database::insertTableDebug( int level, int area, const std::string message ) {

	std::string query = DB_INSERT;
	query += "debug ( area, dateAdd, level, message) VALUES ("+ numToStr(area) + ", timestamp '" + getTime() + "', ";
	query += numToStr( level ) + ", '" + Database::convertXML(message) + "');";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	else
	{

		PQclear(this->m_presult);
	}
}

// vlozeni dat to tabulky xml
void Database::insertTableXML( int level, int area, const std::string message ) {

	std::string query = DB_INSERT;
	query += "xml ( area, dateAdd, level, message) VALUES ("+ numToStr(area) + ", timestamp '" + getTime() + "', ";
	query += numToStr( level ) + ", '" + Database::convertXML(message) + "');";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	else
	{
		PQclear(this->m_presult);
	}

}

// vlozeni dat to tabulky message
void Database::insertTableMessage( const std::string jid, const std::string msg, const std::string subject, const std::string thread, const std::string subtype ) {

	std::string query = DB_DEF_MESSAGE;
	query += "timestamp '";
	query += getTime();
	query += "', '" + jid + "', 'JabInfo@jabbim.com', '";
	query += Database::convertXML(msg) + "', '" + subject + "', '" + thread + "', '" + subtype + "');";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}


// vlozeni dat to tabulky presence
void Database::insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence, const int priority, const std::string nameSW, const std::string versionSW, const std::string osSW ) {

	std::string query = DB_DEF_PRESENCE;
	query += "timestamp '";
	query += getTime();
	query += "', '" + jid + "', 'JabInfo@jabbim.com', '";
	query += Database::convertXML(msg) + "', '" +  name + "', '" + resource + "', '" + Database::convertXML(presence) + "', " + numToStr( priority )+", '" + nameSW + "', '" + versionSW + "', '" + osSW + "');";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}

// vlozeni dat to tabulky presence
void Database::insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence ) {

	std::string query = DB_DEF_PRESENCE1;
	query += "timestamp '";
	query += getTime();
	query += "', '" + jid + "', 'JabInfo@jabbim.com', '"; 
	query += Database::convertXML(msg) + "', '" +  name + "', '" + resource + "', '" + presence + "', 0 );";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if(PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}
/////////////////////////////////////////////// Update metody ///////////////////////////////////////////////////////////////

// aktualizauje stav tabulky STATUS
void Database::updateTableStatus( std::string user ) {

	std::string query = "Select * from resource where jidbare = '";
	query += user + "';";
	this->m_presult = PQexec(this->m_psql, query.c_str());
	if(PQresultStatus(this->m_presult) == PGRES_TUPLES_OK)
	{
		int nFields = PQnfields(this->m_presult);	//sloupec
		int nTuples = PQntuples(this->m_presult);	//radek
		int priority = -127;
		std::string pom, pomS;
		int pomInt = 0;
		int culomn = -1;
		for( int i = 0; i < nTuples; i++ )
		{
				pom = PQgetvalue(this->m_presult,i,5);
				pomS = PQgetvalue(this->m_presult,i,2);
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
			updateTableStatus( PQgetvalue(this->m_presult,culomn,1), PQgetvalue(m_presult,culomn,2), PQgetvalue(m_presult,culomn,3), PQgetvalue(m_presult,culomn,6), PQgetvalue(m_presult, culomn, 7), PQgetvalue(m_presult,culomn,14), PQgetvalue(m_presult,culomn,13), PQgetvalue(m_presult,culomn,15), PQgetvalue(m_presult, culomn, 16) );
		else
		{
			for( int i = 0; i < nTuples; i++ )
			{
				pom = PQgetvalue(this->m_presult,i,5);
				pomS = PQgetvalue(this->m_presult,i,2);
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
				updateTableStatus( PQgetvalue(this->m_presult,culomn,1), PQgetvalue(m_presult,culomn,2), PQgetvalue(m_presult,culomn,3), PQgetvalue(m_presult,culomn,6), PQgetvalue(m_presult, culomn, 7), PQgetvalue(m_presult, culomn, 14), PQgetvalue(m_presult, culomn, 13), PQgetvalue(m_presult, culomn, 15), PQgetvalue(m_presult, culomn, 16) );
		}
	}
}

// aktualizauje stav tabulky RESOURCE
void Database::updateTableResource( std::string jidBare,std::string resource,std::string nameSW,std::string versionSW,std::string osSW) {

	std::string query = DB_UPDATE;
	query += "resource ";
	query += DB_SET;
	query += "nameSW = '" + convertXML(nameSW) + "', versionSW = '" + convertXML(versionSW) + "', osSW = '" + convertXML(osSW) +"' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}

// aktualizauje stav tabulky RESOURCE
bool Database::updateTableResource( SwVersion* swVersion ) {

	std::string query = DB_UPDATE;
	query += "resource ";
	query += DB_SET;
	if( (swVersion->version() != "") && (swVersion->osVersion() != "") )
		query += "nameSW = '" + convertXML( swVersion->name() ) + "', versionSW = '" + convertXML( swVersion->version() )+ "', osSW = '" +convertXML(swVersion->os() ) + "', 'osVersion = '" + convertXML( swVersion->osVersion() ) + "', category = '" + swVersion->category() + "',type = '" + swVersion->type() + "', jingleVoice = " +swVersion->jingleVoice() + ", jingleVideo = " + swVersion->jingleVideo() + ", googleVideo = " + swVersion->googleVideo() + ", googleVoice = " + swVersion->googleVoice() + " "+  DB_WHERE + "jidbare = '" + swVersion->jid().bare()+"' AND resource = '"+swVersion->jid().resource()+"';";
	else if( (swVersion->version() == "") && (swVersion->osVersion() == "") )
		query += "nameSW = '" + convertXML( swVersion->name() ) + "', category = '" + swVersion->category() + "',type = '" + convertXML( swVersion->type() ) + "', jingleVoice = " +swVersion->jingleVoice() + ", jingleVideo = " + swVersion->jingleVideo() + ", googleVideo = " + swVersion->googleVideo() + ", googleVoice = " + swVersion->googleVoice() + " "+  DB_WHERE + "jidbare = '" + swVersion->jid().bare()+"' AND resource = '"+swVersion->jid().resource()+"';";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}

// aktualizauje stav tabulky RESOURCE
bool Database::updateTableResource( std::string jidBare,std::string presence,std::string status,std::string resource, int priority,std::string ver) {

	bool update = false;
	std::string query = DB_UPDATE;
	if( existResource(jidBare, resource) ) //uzivatelsky ucet s mistem existuje, aktualizuji
	{
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + getTime() + "', priority=" + numToStr(priority) + ", ver = '" + ver + "' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		update = true;
	}
	else					// uzivatel s uctem neexistuje, vytvorim
	{
		query = DB_INSERT;
		query += "resource (jidbare, presence, status, date, priority, resource, ver) VALUES ('"+ jidBare + "', '"+ presence +"', '"+Database::convertXML(status)+"', timestamp '" +getTime() + "', "+ numToStr(priority)+", '"+resource+"', '"+ver+"');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		update = false;
	}

	PQclear(this->m_presult);

	return update;
}

// aktualizauje stav tabulky RESOURCE
bool Database::updateTableResource( std::string jidBare,std::string presence,std::string status,std::string resource, int priority) {

	bool update = false;
	std::string query = DB_UPDATE;
	if( existResource(jidBare, resource) ) //uzivatelsky ucet s mistem existuje, aktualizuji
	{
		query += "resource ";
		query += DB_SET;
		query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + getTime() + "', priority=" + numToStr(priority) + " " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		update = true;
	}
	else					// uzivatel s uctem neexistuje, vytvorim
	{
		query = DB_INSERT;
		query += "resource (jidbare, presence, status, date, priority, resource) VALUES ('"+ jidBare + "', '"+ presence +"', '"+Database::convertXML(status)+"', timestamp '" +getTime() + "', "+ numToStr(priority)+", '"+resource+"');";
		this->m_presult = PQexec( this->m_psql, query.c_str() );
		if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
		{
			PQclear(this->m_presult);
			Database::exitError();
		}
		update = false;
	}

	PQclear(this->m_presult);

	return update;
}

// aktualizauje stav tabulky RESOURCE
void Database::updateTableResource( std::string jidBare,std::string presence,std::string status,std::string resource) {

	std::string query = DB_UPDATE;
	query += "resource ";
	query += DB_SET;
	query += "presence = '"+presence+"', status = '"+Database::convertXML(status)+"', date = timestamp '" + getTime() + "' " + DB_WHERE + "jidbare = '" +jidBare+"' AND resource = '"+resource+"';";
	this->m_presult = PQexec( this->m_psql, query.c_str() );
	if( PQresultStatus(this->m_presult) != PGRES_COMMAND_OK )
	{
		PQclear(this->m_presult);
		Database::exitError();
	}
	PQclear(this->m_presult);
}
