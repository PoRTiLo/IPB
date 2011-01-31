//TODO:zkontrolovat obsahy tabulky VCARD
//		:pridat ID, kazdy radek jedn ID, pridat CAS, cim novejsi cas tim aktualnijsu VCARD
//		:pridat automatikcy uzivatele kdyz se prida do kontaktu
//		:zmena udaju->vytvoreni stejneho uzivatele ale s vyssim cislem ->historie zmen

//		:vytvorit tabulku lidi v kontaktlistu, pokud neni vytvorena
//		:automaticky pridat lidi co se zaregistruji do kontakt listu
//		:pridali se nekdo znovu, zaregistrovat pod stejnyma udajema ale vyssi cislo
//


#pragma once

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

#include <gloox/parser.h>

using namespace std;
using namespace gloox;

/**
 * Poskytuje rozhrani pro praci s databazi POSTGRESQL verze 8.4.
 */
class Database
{
	private:
		PGconn *psql;
		PGresult *presult;
//		Parser* parser;

	protected:
		string hostaddr;
		string dbname;
		string user;
		string password;
		string connectTimeout;
		string connInfo;
		string port;
		char sTime[80];

	public:

		/**
		 * Konstruktor.
		 */
		Database();

		/**
		 * Konstruktor.
		 * @param[in] <string> hostaddr Adresa servru databaze.
		 * @param[in] <string> dbname Jmeno databaze.
		 * @param[in] <string> user Uzivatelsek jemno vlastnika databaze.
		 * @param[in] <string> password Heslo pro pripojeni do databaze.
		 * @param[in] <string> connectTimeout Cas pro ukonceni pripojeni pokud se to nepovede.
		 * @param[in] <string> port Port pripojeni.
		 */
		Database( string hostaddr, string dbname, string user, string password, string connectTimeout, string  port );
		
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
		 * @param[in] <const string> nameTable Jmeno tabulky odebirane z databaze.
		 */
		void dropTable( const string nameTable );

		/**
		 * Vytvoreni tabulky.
		 * @param[in] <const string> nameTable Jmeno tabulky, ktera bude vytvorena.
		 * @param[in] <const string> dataTable Data pro vytvoreni tabulky, jmena a typy sloupcu.
		 * @return <bool> true Tabulka vytvorena.
		 *                false Tabulka neni vutvorena, mozna jiz existuje.
		 */
		bool createTable( const string nameTable, const string dataTable );

		/**
		 * Vlozeni dat do tabulky vcard.
		 * @param[in] <const string> sJid 
		 */
//		void insertTableVCard( const string sJid, const string name );
		
		/**
		 * Vlozeni dat do tabulky VCARD.
		 * @param[in] <string> jidBare
		 * @param[in] <string> nickname
		 * @param[in] <string> url
		 * @param[in] <string> bday
		 * @param[in] <string> jabberid
		 * @param[in] <string> title
		 * @param[in] <string> role
		 * @param[in] <string> note
		 * @param[in] <string> mailer
		 * @param[in] <string> rev
		 * @prama[in] <string> uid
		 * @param[in] <string> tz
		 * @param[in] <string> proid
		 * @param[in] <string> sortstring
		 * @param[in] <string> nFamily
		 * @param[in] <string> nGiven
		 * @param[in] <string> nMiddle
		 * @param[in] <string> nPrefix
		 * @param[in] <string> nSuffix
		 */
		void insertTableVCard( string jidBare, string nickname, string url, string bday, string jabberid, string title, string role, string note, string mailer, string rev, string uid, string tz, string proid, string sortstring, string nFamily, string nGiven, string nMiddle, string nPrefix, string nSuffix );

		/**
		 * Vlozeni logovych informaci. Id cilso = informace slovy.
		 * @param[in] <string> query Data vlozena do tabulky.
		 */
		void insertTableConst( const string query );

		/**
		 *	Vlozeni uzivatele do tabulky user.
		 * @param[in] <string> user Jmeno uziovatele, JID.
		 */
		void insertTableUser( string user );

		/**
		 * Zjisteni zda je uzivatel jiz v databazi, v tabulce user.
		 * @param[in] <string> user Jmeno (JID) uzivatele hledaneho v tabulce.
		 */
		bool existUser( string user );

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
		void insertTableDebug( int level, int area, const string message );

		/**
		 *
		 *
		 *
		 *
		 */
		void insertTableXML( int level, int area, string message );

		/**
		 *
		 *
		 *
		 */
		string convertInt( int number );


		/**
		 *
		 */
		void dropAll();

		/**
		 *
		 *
		 *
		 */
		string convertXML( string message );

		/**
		 *
		 *
		 *
		 *
		 *
		 */
		void insertTablePresence( const string jid, const string msg, const string name, const string resource, const string presence, const int priority );
		void insertTablePresence( const string jid, const string msg, const string name, const string resource, const string presence );
		void insertTableMessage( const string jid, const string msg, const string subject, const string thread, const string subtype );

		string printUser() const; 

		void updateTableStatus( string jidBare, string presence, string status, string resource);
};

#endif
