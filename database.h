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

using namespace std;

class Database
{
	private:
		PGconn *psql;
		PGresult *presult;

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
		 * @param[in] <string> hostaddr
		 * @param[in] <string> dbname
		 * @param[in] <string> user
		 * @param[in] <string> password
		 * @param[in] <string> connectTimeout
		 * @param[in] <string> port
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
		 * @param[in] <const string> nameTale Jmeno tabulky odebirane z databaze.
		 */
		void dropTable( const string nameTable );

		/**
		 * Vytvoren itabulky.
		 * @param[in] <const string> nameTable Jmeno tabulky, ktera bude vytvorena.
		 * @param[in] <const string> dataTable Data pro vytvoreni tabulky, jmena a typy sloupcu.
		 * @return <bool> true Tabulka vytvorena.
		 *                false Tabulka neni vutvorena, mozna jiz ezistuje.
		 */
		bool createTable( const string nameTable, const string dataTable );

		/**
		 * Vlozeni dat do tabulky vcard.
		 * @param[in] <const string> sJid 
		 */
		void insertTableVCard( const string sJid, const string name );
		
		/**
		 *
		 */
		void insertTableVCard( string jidBare, string nickname, string url, string bday, string jabberid, string title, string role, string note, string mailer, string rev, string uid, string tz, string proid, string sortstring, string nFamily, string nGiven, string nMiddle, string nPrefix, string nSuffix );

		/**
		 * Vlozeni logovych informaci. Id cilso = informace slovy.
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
		void exitError(PGconn *psql);

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
		void insertTableXML( int level, int area, const string message );

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

};

#endif
