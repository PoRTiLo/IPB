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

#include "geoloc.h"
#include "tune.h"
#include "mood.h"
#include "activity.h"
#include "swversion.h"
#include "func.h"
#include <gloox/parser.h>

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
		 * Odstraneni tabulky z databaze.
		 * @param[in] <const std::string> nameTable Jmeno tabulky odebirane z databaze.
		 */
		void dropTable( const std::string nameTable );

		/**
		 * Vytvoreni tabulky.
		 * @param[in] <const std::string> nameTable Jmeno tabulky, ktera bude vytvorena.
		 * @param[in] <const std::string> dataTable Data pro vytvoreni tabulky, jmena a typy sloupcu.
		 * @return <bool> true Tabulka vytvorena.
		 *                false Tabulka neni vutvorena, mozna jiz existuje.
		 */
		bool createTable( const std::string nameTable, const std::string dataTable );

		/**
		 * Vlozeni dat do tabulky vcard.
		 * @param[in] <const std::string> sJid 
		 */
//		void insertTableVCard( const std::string sJid, const string name );
		
		/**
		 * Vlozeni dat do tabulky VCARD.
		 * @param[in] <std::string> jidBare
		 * @param[in] <std::string> nickname
		 * @param[in] <std::string> url
		 * @param[in] <std::string> bday
		 * @param[in] <std::string> jabberid
		 * @param[in] <std::string> title
		 * @param[in] <std::string> role
		 * @param[in] <std::string> note
		 * @param[in] <std::string> mailer
		 * @param[in] <std::string> rev
		 * @param[in] <std::string> uid
		 * @param[in] <std::string> tz
		 * @param[in] <std::string> proid
		 * @param[in] <std::string> sortstring
		 * @param[in] <std::string> nFamily
		 * @param[in] <std::string> nGiven
		 * @param[in] <std::string> nMiddle
		 * @param[in] <std::string> nPrefix
		 * @param[in] <std::string> nSuffix
		 */
		void insertTableVCard( std::string jidBare, std::string nickname, std::string url, std::string bday, std::string jabberid, std::string title, std::string role, std::string note, std::string mailer, std::string rev, std::string uid, std::string tz, std::string proid, std::string sortstring, std::string nFamily, std::string nGiven, std::string nMiddle, std::string nPrefix, std::string nSuffix );

		/**
		 * Vlozeni logovych informaci. Id cilso = informace slovy.
		 * @param[in] <std::string> query Data vlozena do tabulky.
		 */
		void insertTableConst( const std::string query );

		/**
		 *	Vlozeni uzivatele do tabulky user.
		 * @param[in] <std::string> user Jmeno uziovatele, JID.
		 */
		void insertTableUser( std::string user );

		/**
		 * Zjisteni zda je uzivatel jiz v databazi, v tabulce user.
		 * @param[in] <std::string> user Jmeno (JID) uzivatele hledaneho v tabulce.
		 */
		bool existUser( std::string user );

		/**
		 *
		 */
		void select();

		/**
		 *
		 */
		void exitError();

		/**
		 * Nastaveni promenne sTime aktualnim casem. Format YYYY-MM-DD HH:MM:SS.
		 */
		void getTime();

		/**
		 *
		 */
		void insertTableDebug( int level, int area, const std::string message );

		/**
		 *
		 *
		 *
		 *
		 */
		void insertTableXML( int level, int area, std::string message );

		/**
		 *
		 *
		 *
		 */
		std::string convertInt( int number );
		std::string convertFloat( float number );


		/**
		 *
		 */
		void dropAll();

		/**
		 *
		 *
		 *
		 */
		std::string convertXML( std::string message );

		/**
		 *
		 *
		 *
		 *
		 *
		 */
		void insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence, const int priority, const std::string nameSW, const std::string versionSW, const std::string osSW );
		void insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence );
		void insertTableMessage( const std::string jid, const std::string msg, const std::string subject, const std::string thread, const std::string subtype );

		std::string printUser() const; 

		void updateTableStatus( const std::string jidBare, const std::string presence, const std::string status, const std::string resource, const std::string nameSW);
		void updateTableStatus( const std::string jidBare);

		bool updateTableResource( const std::string jidBare, const std::string presence, const std::string status, const std::string resource, const int priority );
		bool updateTableResource( const std::string jidBare, const std::string presence, const std::string status, const std::string resource, const int priority, std::string ver );
		void updateTableResource( const std::string jidBare, const std::string presence, const std::string status, const std::string resource);
		void updateTableResource( std::string jidBare, std::string resource, std::string nameSW, std::string versionSW, std::string osSW);
		bool updateTableResource( SwVersion* swversion );

		bool existResource( const std::string user, const std::string resource );
		void insertTableGeoloc( Geoloc* geoloc);
		void clearResourceTable( void );
		void insertTableTune( Tune* tune );
		void insertTableMood( Mood* mood );
		void insertTableActivity( Activity* activity );

		char* timeDatabase();
		void strToTime( std:: string p_time );
		bool insertGeoloc( std::string jid, bool empty);
};

#endif
