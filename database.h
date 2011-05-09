/**
 *@file database.h
 *@brief Trida implementujici komunikaci mezi robotem a databazi.
 */

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
#include "connect.h"

using namespace gloox;

/**
 * Poskytuje rozhrani pro praci s databazi POSTGRESQL verze 8.4.
 */
class Database
{
	private:
		PGconn *m_psql;
		PGresult *m_presult;

		/**
		 * Zjisti zda se ma udaj zapisovat do tabulky
		 * @param[in] <Tune*> tune rozsireni XEP-0118
		 * @return <bool> true zapi do db, false nezapisuje se do db
		 */
		bool insertTune( Tune* tune );

		/**
		 * Zjisti zda se ma udaj zapisovat do tabulky
		 * @param[in] <Tune*> tune rozsireni XEP-0107
		 * @return <bool> true zapi do db, false nezapisuje se do db
		 */
		bool insertMood( Mood* mood );

		/**
		 * Zjisti zda se ma udaj zapisovat do tabulky
		 * @param[in] <Tune*> tune rozsireni XEP-0108
		 * @return <bool> true zapi do db, false nezapisuje se do db
		 */
		bool insertActivity( Activity* activity );

		/**
		 * Zjisti zda se ma udaj zapisovat do tabulky
		 * @param[in] <Tune*> tune rozsireni XEP-0060
		 * @return <bool> true zapi do db, false nezapisuje se do db
		 */
		bool insertVCard( const VCard * v, std::string jidBare );

		/**
		 * Zjisti zda se ma udaj zapisovat do tabulky
		 * @param[in] <Tune*> tune rozsireni XEP-0080
		 * @return <bool> true zapi do db, false nezapisuje se do db
		 */
		bool insertGeoloc( std::string jid, bool empty);

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
		 * Vlozeni logovych informaci. Id cilso = informace slovy.
		 * @param[in] <std::string> query Data vlozena do tabulky.
		 */
		void insertTableConst( const std::string query );

		/**
		 * Zjisteni zda je uzivatel jiz v databazi, v tabulce user.
		 * @param[in] <std::string> user Jmeno (JID) uzivatele hledaneho v tabulce.
		 */
		bool existUser( std::string user );
	
		/**
		 * Aktualizuje tabulku status.
		 * @param[in] <string> jidBare uzivatelsky ucet.
		 * @param[in] <string> presence presence.
		 * @param[in] <string> status status.
		 * @param[in] <string> resource resource.
		 * @param[in] <string> nameSw nazev programu klienta
		 * @param[in] <string> jingleVi
		 * @param[in] <string> jingleVo
		 * @param[in] <string> googleVi
		 * @param[in] <string> googleVo
		 */
		void updateTableStatus( const std::string jidBare, const std::string presence, const std::string status, const std::string resource, const std::string nameSW, const std::string jingleVi, std::string jingleVo, std::string googleVo, std::string googleVi);

		/**
		 * Zjisti zda je resource uzivatele v databazi.
		 * @param[in] <string> user jid uzivatele
		 * @param[in] <string> resource rsource uzivatele
		 * @return <bool> true je v databazi, false neni v databazi
		 */
		bool existResource( const std::string user, const std::string resource );

		/**
		 * Odstraneni tabulky z databaze.
		 * @param[in] <const std::string> nameTable Jmeno tabulky odebirane z databaze.
		 */
	//	void dropTable( const std::string nameTable );

		/**
		 * Smazani vsech tabulek.
		 */
	//	void dropAll();

	protected:
		std::string m_hostaddr;
		std::string m_dbname;
		std::string m_user;
		std::string m_password;
		std::string m_connectTimeout;
		std::string m_connInfo;
		std::string m_port;
		char sTime[80];

	public:
		std::map<std::string, std::string> listVer;
		std::multimap<std::string, std::string> mapVer;

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
		 * Nastaveni promenne sTime aktualnim casem. Format YYYY-MM-DD HH:MM:SS.
		 */
		char* getTime();

		/**
		 * Vytvoreni tabulky.
		 * @param[in] <const std::string> nameTable Jmeno tabulky, ktera bude vytvorena.
		 * @param[in] <const std::string> dataTable Data pro vytvoreni tabulky, jmena a typy sloupcu.
		 * @return <bool> true Tabulka vytvorena.
		 *                false Tabulka neni vutvorena, mozna jiz existuje.
		 */
		bool createTable( const std::string nameTable, const std::string dataTable );

		/**
		 * Prevod binarniho obrazku na retezec.
		 *	@param[in] <string> message binarkni data
		 * @return <string> ASCII znaky
		 */
		std::string convertBinary(std::string message );

		/**
		 * Prevod retezec na retezec s escape znaky pro format databaze.
		 *	@param[in] <string> message puvodni retezec
		 * @return <string> retezec s pridanymi znaky pro ulozeni do Db
		 */
		std::string convertXML( std::string message );

////////////////////////////////////////////////////// Vkladaci metody ///////////////////////

		/**
		 * Vlozeni dat do tabulky ACTIVITY.
		 * @param[in] <Activity*> ativity objekt obsahujici dat pro databazi.
		 */
		void insertTableActivity( Activity* activity );

		/**
		 * Vlozeni dat do tabulky TUNE.
		 * @param[in] <Tune*> tune objekt obsahujici dat pro databazi.
		 */
		void insertTableTune( Tune* tune );

		/**
		 * Vlozeni dat do tabulky MOOD.
		 * @param[in] <Mood*> mood objekt obsahujici dat pro databazi.
		 */
		void insertTableMood( Mood* mood );

		/**
		 * Vlozeni dat do tabulky GEOLOC.
		 * @param[in] <Geoloc*> geoloc objekt obsahujici dat pro databazi.
		 */
		void insertTableGeoloc( Geoloc* geoloc);

		/**
		 * Vlozeni dat do tabulky VCARD.
		 * @param[in] <VCard> v
		 */
		void insertTableVCard( const VCard* v, std::string jidBare );

		/**
		 *	Vlozeni uzivatele do tabulky user.
		 * @param[in] <std::string> user Jmeno uziovatele, JID.
		 */
		void insertTableUser( std::string user );

		/**
		 * Vlozeni logovych informaci. Id cilso = informace slovy.
		 * @param[in] <int> level
		 * @param[in] <inta> area
		 * @param[in] <string> message Data vlozena do tabulky.
		 */
		void insertTableDebug( int level, int area, const std::string message );

		/**
		 * Vlozeni logovych informaci. Id cilso = informace slovy.
		 * @param[in] <int> level
		 * @param[in] <inta> area
		 * @param[in] <string> message Data vlozena do tabulky.
		 */
		void insertTableXML( int level, int area, std::string message );

		/**
		 * Vlozeni zprav do tabulky MESSAGE
		 * @param[in] <string> jid uzivatelske jmeno adresata
		 * @param[in] <string> msg text zpravy
		 * @param[in] <string> subject predmet zpravy
		 * @param[in] <string> thread vlakno
		 * @param[in] <string> subtype typ zpravy
		 */
		void insertTableMessage( const std::string jid, const std::string msg, const std::string subject, const std::string thread, const std::string subtype );

		/**
		 * Vlozeni informaci o zmenen statusu uzivatele do tabulky presence.
		 * @param[in] <string> jid uzivatelsek jmeno.
		 * @param[in] <string> msg podrobnejsi popis statusu.
		 * @param[in] <string> name jmeno uzivatele.
		 * @param[in] <string> resource resource uzivatele.
		 * @param[in] <string> presence presence.
		 * @param[in] <int> priority priorita daneho resource.
		 * @param[in] <string> nameSw jmeno programu.
		 * @param[in] <string> versionSw verze software.
		 * @param[in] <string> osSw nazev operacniho systemu, ktery uzivatel pouziva.
		 */
		void insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence, const int priority, const std::string nameSW, const std::string versionSW, const std::string osSW );

		/**
		 * Vlozeni informaci o zmenen statusu uzivatele do tabulky presence. Zmena stavu je na Unavailable.
		 * @param[in] <string> jid uzivatelsek jemno.
		 * @param[in] <string> msg podrobnejsi popis statusu.
		 * @param[in] <string> name jmeno uzivatele.
		 * @param[in] <string> resource resource uzivatele.
		 * @param[in] <string> presence presence.
		 */
		void insertTablePresence( const std::string jid, const std::string msg, const std::string name, const std::string resource, const std::string presence );

/////////////////////////////////////////////// Update metody ///////////////////////////////////////////////////////////////
		

		/**
		 * Akrualizace stavu tabulky status.
		 * @param[in] <string> jidbare uzivatelksy ucet
		 */
		void updateTableStatus( const std::string jidBare);

		/**
		 * Aktualizace tabulky resource.
		 * @param[in] <string> jidBare uzivatelksy ucet.
		 * @param[in] <string> presence presence.
		 * @param[in] <string> status status.
		 * @param[in] <string> resource resource.
		 * @param[in] <int> priority priorita
		 */
		bool updateTableResource( const std::string jidBare, const std::string presence, const std::string status, const std::string resource, const int priority );

		/**
		 * Aktualizace tabulky resource.
		 * @param[in] <string> jidBare uzivatelksy ucet.
		 * @param[in] <string> presence presence.
		 * @param[in] <string> status status.
		 * @param[in] <string> resource resource.
		 * @param[in] <int> priority priorita.
		 * @param[in] <string> ver zakododvane informace o schopnostech klienta, podpore a tak.
		 */
		bool updateTableResource( const std::string jidBare, const std::string presence, const std::string status, const std::string resource, const int priority, std::string ver );

		/**
		 * Aktualizace tabulky resource.
		 * @param[in] <string> jidBare uzivatelksy ucet.
		 * @param[in] <string> presence presence.
		 * @param[in] <string> status status.
		 * @param[in] <string> resource resource.
		 */
		void updateTableResource( const std::string jidBare, const std::string presence, const std::string status, const std::string resource);

		/**
		 * Aktualizace tabulky resource.
		 * @param[in] <string> jidBare uzivatelksy ucet.
		 * @param[in] <string> nameSW nazev programu.
		 * @param[in] <string> versionSw verze programu.
		 * @param[in] <string> resource resource.
		 * @param[in] <string> osSW operacni system.
		 */
		void updateTableResource( std::string jidBare, std::string resource, std::string nameSW, std::string versionSW, std::string osSW);

		/**
		 * Aktualizace tabulky resource.
		 * @param[in] <SwVersion*> swversion informace o software klienta.
		 */
		bool updateTableResource( SwVersion* swversion );

/////////////////////////////////// SELECT METODY////////////////////////////////////////////////////////////////////////////////////

		std::string select( std::string selcect, std::string jid ) const;
		std::string printTune(std::string jid ) const;
		std::string printGeoloc(std::string jid ) const;
		std::string printMood(std::string jid ) const;
		std::string printActivity(std::string jid ) const;
		std::string printVCard(std::string jid ) const;
		std::string printHistory(std::string jid ) const;
		std::string printUser() const; 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		/**
		 *
		 */
		void exitError();




		void clearResourceTable( void );

		std::string listToString(gloox::StringList units);



		/**
		 * Naplneni listu uzivateli
		 */
		void initListVer( void );
};
#endif
