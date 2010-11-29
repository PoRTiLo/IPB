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
		string  port;

	public:

		/**
		 *
		 */
		Database();

		/**
		 *
		 */
		Database( string hostaddr, string dbname, string user, string password, string connectTimeout, string  port );
		
		/**
		 *
		 */
		~Database(){}

		/**
		 *
		 */
		void start();
		/**
		 *
		 */
		void initDb();

		/**
		 *
		 */
		void makeStringConnect();

		/**
		 *
		 */
		void connect();

		/**
		 *
		 */
		void dropTable( const string nameTable );

		/**
		 *
		 */
		void createTable( const string nameTable, const string dataTable );

		/**
		 *
		 */
		void insertTableVCard( const string sJid, const string name );
		
		/**
		 *
		 */
		void insertTableVCard( string jidBare, string nickname, string url, string bday, string jabberid, string title, string role, string note, string mailer, string rev, string uid, string tz, string proid, string sortstring, string nFamily, string nGiven, string nMiddle, string nPrefix, string nSuffix ); 

		/**
		 *
		 */
		void select();

		/**
		 *
		 */
		void exitError(PGconn *psql);

};

#endif
