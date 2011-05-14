//TODO:zkontrolovat obsahy tabulky VCARD
//		:pridat ID, kazdy radek jedn ID, pridat CAS, cim novejsi cas tim aktualnijsu VCARD
//		:pridat automatikcy uzivatele kdyz se prida do kontaktu
//		:zmena udaju->vytvoreni stejneho uzivatele ale s vyssim cislem ->historie zmen

//		:vytvorit tabulku lidi v kontaktlistu, pokud neni vytvorena
//		:automaticky pridat lidi co se zaregistruji do kontakt listu
//		:pridali se nekdo znovu, zaregistrovat pod stejnyma udajema ale vyssi cislo
//
//		:predelat listVer na protected a ne public

#ifndef TRANSFORM_H__
#define TRANSFORM_H__

#include <libpq-fe.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <gloox/jid.h>

#include <math.h>
#include <vector>

using namespace gloox;

/**
 * Poskytuje rozhrani pro praci s databazi POSTGRESQL verze 8.4.
 */
class Transform
{
	private:
		PGconn *psql;
		PGresult *presult;

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

		/**
		 * Konstruktor.
		 */
		Transform();

		/**
		 * Destruktor.
		 */
		~Transform(){}

		/**
		 * Inicializace a pripojeni k databazi.
		 */
		void start();

		/**
		 * Vytvoreni pripojovaciho retezce.
		 */
		void makeStringConnect();

		/**
		 * Pripojeni k databazi.
		 */
		void connect();


		/**
		 * Nastaveni promenne sTime aktualnim casem. Format YYYY-MM-DD HH:MM:SS.
		 */
		void getTime();
		std::vector<std::string> printUser() const; 



		int * userToTab( int* vector, JID jid, std::string time );
		int presenceToInt( std::string presence );
		time_t stringToSec( std::string date );
		time_t stringToSecLast( std::string date );
		time_t stringToSecFirst( std::string date );
		int userToTabFirst( JID jid, const time_t timeEnd );
};

#endif
