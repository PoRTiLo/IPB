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

//	Database::initDb();
}



void Database::connect() {
	
	Database::makeStringConnect();
	this->psql = PQconnectdb(this->connInfo.c_str());
	if( !this->psql )
	{
		fprintf(stderr, "Error\n");
		//Database::exitError();
	}

	//connect
	if( PQstatus(this->psql) != CONNECTION_OK )
	{
		fprintf(stderr, "chyba PRIPOJENI\n");
		//Database::exitError();
	}
}


std::vector<std::string> Database::printUser() const {

	PGresult* presult;
	presult = PQexec(this->psql, "SELECT jidbare FROM userjid;");
	

	int nTuples = PQntuples(presult);

	std::vector<std::string> vectorUser;
	for( int i = 0; i < nTuples; i++ )
	{
		vectorUser.push_back( PQgetvalue(presult, i, 0));
	}

	PQclear(presult);
	return vectorUser;
}
		

int Database::userToTabFirst(JID jid, const time_t timeLast) {

	int presence = 0;
	const time_t timeStart = timeLast - 86400;
	struct tm*  timeS = localtime(&timeStart);
	char dateS[80];
	strftime(dateS, 79, "%Y-%m-%d %H:%M:%S", timeS);

	const time_t timeEnd = timeLast - 1;
	struct tm*  timeE = localtime(&timeEnd);
	char dateE[80];
	strftime(dateE, 79, "%Y-%m-%d %H:%M:%S", timeE);

	std::string query = "Select date, presence from presence where fromj = '";
	query += jid.bare() + "' and date between '" + dateS + "' and '" + dateE + "';";
	PGresult *presult1;
	presult1 = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult1) == PGRES_TUPLES_OK)
	{

		int nTuples = PQntuples(presult1);	//radek
		if(nTuples != 0)
			presence = presenceToInt(PQgetvalue(presult1, nTuples-1,1));
	}

	PQclear(presult1);
	return presence;
}

int* Database::userToTab( JID jid, std::string date ) {

	const time_t timeStart =  stringToSecFirst(date);
	struct tm*  timeS = localtime(&timeStart);
	char dateS[80];
	strftime(dateS, 79, "%Y-%m-%d %H:%M:%S", timeS);

	const time_t timeEnd =  stringToSecLast(date);
	struct tm*  timeE = localtime(&timeEnd);
	char dateE[80];
	strftime(dateE, 79, "%Y-%m-%d %H:%M:%S", timeE);

	int *vectorPresence = (int *) malloc(sizeof(int) * 289);
	std::string query = "Select date, presence, resource, priority from presence where fromj = '";
	query += jid.bare() + "' and date between '" + dateS + "' and '" + dateE + "';";
	printf("%s\n",query.c_str());
	presult = PQexec(this->psql, query.c_str());
	if(PQresultStatus(presult) == PGRES_TUPLES_OK)
	{
		int nFields = PQnfields(presult);	//sloupec
		int nTuples = PQntuples(presult);	//radek
		if(nTuples != 0)
		{
			int count = 0;
			double sek = 0.0;
			int time = 0;
			int pozicion = 0;
			int timePozicion = timeStart;
			int procent[2][50];

			int timeStart = stringToSecFirst(date);
			int timeEnd = stringToSecLast(date);
			int firstPresence = userToTabFirst(jid, stringToSecFirst(PQgetvalue(presult,0,0) ));
//printf("cisloooooopredchoziho statusu :%d\n",		userToTabFirst(jid, stringToSecFirst(PQgetvalue(presult,0,0) )) );

			if(( difftime( stringToSec(PQgetvalue(presult,0,0)), timePozicion ))/300 < 1)
			{

			}
			//posunot , prvni krpk udelat zvlast
			bool last = false;
			//poresit kdyz je ntuples prazdny;
			for(int i = 0;  i < nTuples; i++)//misto 0 ->1
			{
				if(last == true)
					break;
				if(i== nTuples-1)
				{
//				sek = difftime( timeEnd,stringToSec(PQgetvalue(presult,i,0)) );
//				printf("..................%f\n",sek);
					last = true;
				}
				sek = abs(difftime( stringToSec(PQgetvalue(presult,i,0)), timePozicion ));
				time = floor(sek/60/5);
//printf("datum :%s, rozdil sekund datumu :%d ,a predhcoziho casu: %f\n",PQgetvalue(presult,i,0), timePozicion, sek);
				if( time >= 1)						// status trva dele nebo pet minut
				{
					for( int k = 0; k < time; k++ )
					{
						if(i-1>=0)
							vectorPresence[pozicion++] = presenceToInt(PQgetvalue(presult, i-1,1));
						else
						{
							vectorPresence[pozicion++] = firstPresence;
						}
//printf("hodnota stausu:%d   , v pozici : %d\n",vectorPresence[pozicion-1], pozicion-1);
					}
					timePozicion += time * 300;		// posunuti casove pozice o pocet mist zapsanych do pole, dochazi k zaokrouhleni, pokud je reprezentace daneho statu vetsi jak polovocni
					i--;
				}
				else if( time >= 0)									// status neztrva ani 5 minut, potreba pocitat % zastoupeni v petiminutovce
				{
					int timeNow = timePozicion;
					int procentPozicion = 0;
					for(int c=0;c<2;c++)
					{
						for(int v=0;v<50;v++)
							procent[c][v]='\0';
					}
					for(int k = i; timeNow < timePozicion +300 && k <nTuples; k++)//+ (floor(timePozicion/300)*300+300-timePozicion); k++)
					{
//	printf("ELSE -- datum :%s\n",PQgetvalue(presult,k,0));
						if(k == nTuples-1)
							sek = difftime( stringToSec(PQgetvalue(presult,k,0)), timeEnd );

						sek = difftime( stringToSec(PQgetvalue(presult,k,0)), timeNow );
						timeNow += sek;
						if( timeNow >= timePozicion + 300)
						{
							if(i-1>=0)
							{
								procent[0][procentPozicion] = (sek - (  (timeNow) - (timePozicion+300) ) ) * 3;	//%zastoupeni daneho statuc v 5 minutovce
								procent[1][procentPozicion++] = presenceToInt(PQgetvalue(presult, k-1,1));
							}
						}
						else
						{
							if(i-1>=0)
							{
								procent[0][procentPozicion] = 3 * sek;	// 3 je 1% z 300 sekund a sek je pocet sekund, vypocet % zastoupeni
								procent[1][procentPozicion++] = presenceToInt(PQgetvalue(presult, k-1,1));
							}
						}
						i = k ;
					}
					i = i-1 ;
					int array[2][6]={0,0,0,0,0,0,AVAILABLE,CHAT,AWAY,XA,DND,UNAVALIABLE};
				
					for(int l = 0; l < 6; l++)
					{
						if(procent[1][l] == AVAILABLE)
							array[0][0] += procent[0][l];
						else if(procent[1][l] == UNAVALIABLE)
							array[0][5] += procent[0][l];
						else if(procent[1][l] == AWAY)
							array[0][2] += procent[0][l];
						else if(procent[1][l] == XA)
							array[0][3] += procent[0][l];
						else if(procent[1][l] == CHAT)
							array[0][1] += procent[0][l];
						else if(procent[1][l] == DND)
							array[0][4] += procent[0][l];
					}
//	for(int m=0;m<6;m++)
//		printf("//////////:%d\n",array[0][m]);
					int sizePresence = 0;
					int namePresence = 0;
					for(int l = 5; l >= 0; l--)
					{
						if(sizePresence < array[0][l])
						{
							sizePresence = array[0][l];
							namePresence = array[1][l];
						}
//	printf("size:%d\n",sizePresence);
					}
//	printf("jmenooooooooooooooooooooooo:%d\n",namePresence);
					vectorPresence[pozicion++] = namePresence;
				
//	printf("hodnota stausu:%d   , v pozici : %d\n",vectorPresence[pozicion-1], pozicion-1);
					timePozicion += 60 * 5;		// posunuti casove pozice o pocet mist zapsanych do pole
				}
//	printf("stav promenne I: %d, po jednom cyklu z:%d\n",i, nTuples);
//	for(int l=0;l<pozicion;l++)
//	{
//		printf("%d:%d\n",l,vectorPresence[l]);
//	}
			}

			while(pozicion < 289)
			{
				vectorPresence[pozicion++] = presenceToInt(PQgetvalue(presult, nTuples-1,1));
//	printf("hodnota stausu:%d   , v pozici : %d\n",vectorPresence[pozicion-1], pozicion-1);
			}
		}
		else //neni v databazi
		{
			for(int l=0; l < 289; l++)
				vectorPresence[l] = 0;
		}
	}

// kontorlni tisk udaju presence prevedenych na interval po 5 minutach do vektoru
//	for(int l=0; l < 289; l++)
//		printf("%d:%d\n",l,vectorPresence[l]);

	return vectorPresence;

}

int Database::presenceToInt( std::string presence ) {

	if( presence == "Available" )
		return AVAILABLE; //120;
	else if( presence == "Away" )
		return AWAY;//90;
	else if( presence == "DND" )
		return DND;//50;
	else if( presence == "Chat" )
		return CHAT;//110;
	else if( presence == "XA" )
		return XA;//70;
	else if( presence == "Unavaliable" )
		return UNAVALIABLE;//0;
}

time_t Database::stringToSec( std::string date ) {

	int year, month, day, hour, min, sec;
	sscanf(date.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec);

	struct tm  time;
	time.tm_sec = sec;
	time.tm_min = min;
	time.tm_hour = hour;
	time.tm_mday = day;
	time.tm_mon = month-1;
	time.tm_year = year-1900;
	time.tm_isdst = -1;

	time_t timeSec; 
	//if( mktime(&time) == (time_t)-1)
	//	printf("divne\n");

	timeSec= mktime(&time);
	return timeSec;
}

time_t Database::stringToSecFirst( std::string date ) {

	int year, month, day, hour, min, sec;
	sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

	struct tm  time;
	time.tm_sec = 0;
	time.tm_min = 0;
	time.tm_hour = 0;
	time.tm_mday = day;
	time.tm_mon = month-1;
	time.tm_year = year-1900;
	time.tm_isdst = -1;

	time_t timeSec; 
	if( mktime(&time) == (time_t)-1)
		printf("divne\n");

	timeSec= mktime(&time);
	return timeSec;
}

time_t Database::stringToSecLast( std::string date ) {

	int year, month, day, hour, min, sec;
	sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

	struct tm  time;
	time.tm_sec = 59;
	time.tm_min = 59;
	time.tm_hour = 23;
	time.tm_mday = day;
	time.tm_mon = month-1;
	time.tm_year = year-1900;
	time.tm_isdst = -1;

	time_t timeSec; 
	if( mktime(&time) == (time_t)-1)
		printf("divne\n");

	timeSec= mktime(&time);
	return timeSec;
}
