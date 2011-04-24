//TODO:zkontrolovat obsahy tabulky VCARD
//		:pridat ID, kazdy radek jedn ID, pridat CAS, cim novejsi cas tim aktualnijsu VCARD
//		:pridat automatikcy uzivatele kdyz se prida do kontaktu
//		:zmena udaju->vytvoreni stejneho uzivatele ale s vyssim cislem ->historie zmen

//		:vytvorit tabulku lidi v kontaktlistu, pokud neni vytvorena
//		:automaticky pridat lidi co se zaregistruji do kontakt listu
//		:pridali se nekdo znovu, zaregistrovat pod stejnyma udajema ale vyssi cislo
//
//		:predelat listVer na protected a ne public

#ifndef DATABASE_H__
#define DATABASE_H__

#include <libpq-fe.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <cassert>
#include <iostream>
#include <map>
#include <fstream>
#include "geoloc.h"
#include "tune.h"
#include "mood.h"
#include "activity.h"
#include "swversion.h"
#include "func.h"
#include <gloox/parser.h>
#include <gloox/vcard.h>
#include <gloox/base64.h>

#include <math.h>
#include <vector>

#define AVAILABLE 120
#define AWAY 90
#define DND 50
#define CHAT 110
#define XA 70
#define UNAVALIABLE 0


using namespace gloox;

/**
 * Poskytuje rozhrani pro praci s databazi POSTGRESQL verze 8.4.
 */
class Database
{
	private:
		PGconn *psql;
		PGresult *presult;
		bool insertTune( Tune* tune );
		bool insertMood( Mood* mood );
		bool insertActivity( Activity* activity );

	protected:
		std::string hostaddr;
		std::string dbname;
		std::string user;
		std::string password;
		std::string connectTimeout;
		std::string connInfo;
		std::string port;
		char sTime[80];

	public:

		std::map<std::string, std::string> listVer;
		std::multimap<std::string, std::string> mapVer;

		/**
		 * Naplneni listu uzivateli
		 */
		void initListVer( void );

		/**
		 * Konstruktor.
		 */
		Database();

		/**
		 * Konstruktor.
		 * @param[in] <std::string> hostaddr Adresa servru databaze.
		 * @param[in] <std::string> dbname Jmeno databaze.
		 * @param[in] <std::string> user Uzivatelsek jemno vlastnika databaze.
		 * @param[in] <std::string> password Heslo pro pripojeni do databaze.
		 * @param[in] <std::string> connectTimeout Cas pro ukonceni pripojeni pokud se to nepovede.
		 * @param[in] <std::string> port Port pripojeni.
		 */
		Database( std::string hostaddr, std::string dbname, std::string user, std::string password, std::string connectTimeout, std::string  port );
		
		/**
		 * Destruktor.
		 */
		~Database(){}

		/**
		 * Inicializace a pripojeni k databazi.
		 */
		void start();

		/**
		 * Inicializace databaze.
		 */
		void initDb();

		/**
		 * Vytvoreni pripojovaciho retezce.
		 */
		void makeStringConnect();

		/**
		 * Pripojeni k databazi.
		 */
		void connect();


		/**
		 * Zjisteni zda je uzivatel jiz v databazi, v tabulce user.
		 * @param[in] <std::string> user Jmeno (JID) uzivatele hledaneho v tabulce.
		 */
		bool existUser( std::string user );


		/**
		 * Nastaveni promenne sTime aktualnim casem. Format YYYY-MM-DD HH:MM:SS.
		 */
		void getTime();
		std::vector<std::string> printUser() const; 



		char* timeDatabase();
		void strToTime( std:: string p_time );
		bool insertGeoloc( std::string jid, bool empty);
		std::string listToString(gloox::StringList units);
		int * userToTab( JID jid, std::string time );
		int presenceToInt( std::string presence );
		time_t stringToSec( std::string date );
		time_t stringToSecLast( std::string date );
		time_t stringToSecFirst( std::string date );
		int userToTabFirst( JID jid, const time_t timeEnd );
};

#endif
