/**
 *@file const.h
 *@brief Soubor konstant pro dotazy v jazyce SQL.
 */


#pragma once

#define ADMIN_JID "pidgin@localhost, portilo@jabbim.cz"
#define COMMAND_RECONNECT "RECONNECT"
#define COMMAND_HALLO "caok"
#define COMMAND_INFO "INFO"
#define COMMAND_HELP "HELP"
#define COMMAND_USER "USER"
#define COMMAND_TUNE "TUNE"
#define COMMAND_GEOLOC "GEOLOC"
#define COMMAND_MOOD "MOOD"
#define COMMAND_ACTIVITY "ACTIVITY"
#define COMMAND_VCARD "VCARD"
#define COMMAND_HISTORY "HISTORY"
#define COMMAND "USER, RECONNECT"

//dotazy
#define DB_C_T "Create table "
#define DB_D_T_I_E "Drop table if exists "
#define DB_SELECT_ALL "Select * from "
#define DB_TABLE_VCARD " id serial PRIMARY KEY,"\
	                  " jid text,"\
							" dateAdd timestamp,"\
				   		" family text,"\
					   	" given text,"\
							" middle text,"\
							" prefix text,"\
							" suffix text,"\
							" nickname text,"\
							" url text,"\
							" bday text,"\
							" jabberid text,"\
							" title text,"\
							" role text,"\
							" note text,"\
							" mailer text,"\
							" rev text,"\
							" uid text,"\
							" tz text,"\
							" prodid text,"\
							" sortstring text,"\
							" photoExtval text,"\
							" photoBinval text,"\
							" photoType text,"\
							" logoExtval text,"\
							" logoBinval text,"\
							" logoType text,"\
							" geoLat real,"\
							" geoLon real,"\
							" orgName text,"\
							" orgUnits text"
#define DB_INSERT "Insert into "
#define DB_UPDATE "UPDATE "
#define DB_SET "SET "
#define DB_WHERE "WHERE "
#define DB_TABLE_USER " jidBare text PRIMARY KEY,"\
					 		 " date timestamp"
#define DB_SELECT_USER "Select jid from user where jid = '"
#define DB_TABLE_LOGAREA " num integer PRIMARY KEY,"\
								 " name text,"\
								 " description text,"\
								 " descriptionCz text"
#define DB_TABLE_STATUS " jidBare text PRIMARY KEY,"\
								 "presence text,"\
								 "status text,"\
					 		   " date timestamp,"\
								" resource text," \
								" nameSw text,"\
								" jingleVideo boolean,"\
								" jingleVoice boolean,"\
								" googleVideo boolean,"\
								" googleVoice boolean"
#define DB_SELECT_STATUS "Select * from status"
#define DB_TABLE_RESOURCE " id serial PRIMARY KEY,"\
								" jidBare text,"\
								" presence text,"\
								" status text,"\
					 		   " date timestamp,"\
								" priority integer,"\
								" resource text,"\
								" nameSW text," \
								" versionSW text," \
								" osSW text,"\
								" osVersion text,"\
								" ver text,"\
								" category text,"\
								" type text,"\
								" jingleVoice boolean,"\
								" jingleVideo boolean,"\
								" googleVoice boolean,"\
								" googleVideo boolean"

#define DB_SELECT_RESOURCE "Select * from resource"
#define DB_DATA_LOGAREA "Insert into logarea ( num, name, description, descriptionCz ) VALUES "\
								 "( 1, 'LogAreaClassParser', 'Log message from Parser', 'Zprava z parsru'),"\
								  "( 2, 'LogAreaClassConnectionTCBase', 'Log message from ConnectionTCPBase', ''),"\
								 "( 4, 'LogAreaClassClient', 'Log messages from Client', ''),"\
								 "( 8, 'LogAreaClassClientbase', 'Log messages from ClientBase', ''),"\
								 "( 16, 'LogAreaClassComponent', 'Log messages from Component', ''),"\
								 "( 32, 'LogAreaClassDns', 'Log messages from DNS', ''),"\
								 "( 64, 'LogAreaClassConnectionHTTPProxy', 'Log messages from ConnectionHTTPProxy', ''),"\
								 "( 128, 'LogAreaClassConnectionSOCKS5Proxy', 'Log messages from ConnectionSOCKS5Proxy', ''),"\
								 "( 256, 'LogAreaClassConnectionTCPClient', 'Log messages from ConnectionTCPClient', ''),"\
								 "( 521, 'LogAreaClassConnectionTCPServer', 'Log messages from ConnectionTCPServer', ''),"\
								 "( 1024, 'LogAreaClassS5BManager', 'Log messages from SOCKS5BytestreamManager', ''),"\
								 "( 2048, 'LogAreaClassSOCKS5Bytestream', 'Log messages from SOCKS5Bytestream', ''),"\
								 "( 4096, 'LogAreaClassConnectionBOSH', 'Log messages from ConnectionBOSH', ''),"\
								 "( 8192, 'LogAreaClassConnectionTLS', 'Log messages from ConnectionTLS', ''),"\
								 "( 131071, 'LogAreaAllClasses', 'All log messages from all the classes', ''),"\
								 "( 131072, 'LogAreaXmlIncoming', 'Incoming XML', ''),"\
								 "( 262144, 'LogAreaXmlOutgoing', 'Outgoing XML', ''),"\
								 "( 8388608, 'LogAreaUser', 'User-defined sources', ''),"\
								 "( 16777215, 'LogAreaAll', 'All log sources', '');"
#define DB_TABLE_DEBUG " id serial PRIMARY KEY,"\
							  " area integer REFERENCES logarea (num),"\
							  " dateAdd timestamp,"\
							  " level integer REFERENCES level (num),"\
							  " message text"
#define DB_TABLE_XML " id serial PRIMARY KEY,"\
							  " area integer REFERENCES logarea (num),"\
							  " dateAdd timestamp,"\
							  " level integer REFERENCES level (num),"\
							  " message text"
#define DB_TABLE_LEVEL " num integer PRIMARY KEY,"\
							 " name text,"\
							 " description text,"\
							 " descriptionCz text"
#define DB_DATA_LEVEL "Insert into level ( num, name, description, descriptionCz ) VALUES "\
							 "(0, 'LogLevelDebug', 'Debug messages', ''),"\
							 "(1, 'LogLevelWarning', 'Non-critical warning messages', ''),"\
							 "(2, 'LogLevelError', 'Critical, unrecoverable errors', '')"
#define DB_TABLE_PRESENCE " id serial PRIMARY KEY,"\
							 " date timestamp,"\
							 " fromJ text,"\
							 " toJ text,"\
							 " message text,"\
							 " name text,"\
							 " resource text,"\
							 " presence text,"\
							 " priority integer,"\
							 " nameSW text,"\
							 " versionSW text,"\
							 " osSW text"
							 
#define DB_DEF_PRESENCE "INSERT INTO presence ( date, fromJ, toJ, message, name, resource, presence, priority, nameSW, versionSW, osSW) VALUES ("
#define DB_DEF_PRESENCE "INSERT INTO presence ( date, fromJ, toJ, message, name, resource, presence, priority, nameSW, versionSW, osSW) VALUES ("
#define DB_DEF_PRESENCE1 "INSERT INTO presence ( date, fromJ, toJ, message, name, resource, presence, priority) VALUES ("
#define DB_TABLE_MESSAGE "id serial PRIMARY KEY,"\
							 " date timestamp,"\
							 " fromJ text,"\
							 " toJ text,"\
							 " message text,"\
							 " subject text,"\
							 " thread text,"\
							 " subtype text"
#define DB_DEF_MESSAGE "INSERT INTO message ( date, fromJ, toJ, message, subject, thread, subtype) VALUES ("

#define DB_TABLE_GEOLOC " id serial PRIMARY KEY,"\
								" jidBare text,"\
								" time timestamp,"\
								" nodeId text,"\
								" accuracy real,"\
					 		   " alt real,"\
								" area text,"\
								" bearing real,"\
								" building text," \
								" country text," \
								" countrycode text,"\
								" datum text,"\
								" description text,"\
					 		   " error real,"\
								" floor text,"\
								" lat integer,"\
								" locality text," \
								" lon integer,"\
								" postalcode text,"\
								" region text,"\
					 		   " room text,"\
								" speed real,"\
								" street text,"\
								" text text," \
								" timestamp timestamp," \
								" uri text"

#define DB_DEF_GEOLOC "INSERT INTO geoloc ( jidBare, time, nodeId, accuracy, alt, area, bearing, building, country, countrycode, datum, description, error, floor, lat, locality, lon, postalcode, region, room, speed, street, text, timestamp, uri) VALUES ("

#define DB_TABLE_TUNE " id serial PRIMARY KEY,"\
								" jidBare text,"\
								" time timestamp,"\
								" nodeId text,"\
								" artist text,"\
					 		   " length integer,"\
								" rating integer,"\
								" source text,"\
								" title text," \
								" track text," \
								" uri text"

#define DB_DEF_TUNE "INSERT INTO tune ( jidBare, time, nodeId, artist, length, rating, source, title, track, uri) VALUES ("

#define DB_TABLE_MOOD " id serial PRIMARY KEY,"\
								" jidBare text,"\
								" time timestamp,"\
								" nodeId text,"\
								" mood text,"\
								" text text"

#define DB_DEF_MOOD "INSERT INTO mood ( jidBare, time, nodeId, mood, text) VALUES ("

#define DB_TABLE_ACTIVITY " id serial PRIMARY KEY,"\
								" jidBare text,"\
								" time timestamp,"\
								" nodeId text,"\
								" activity text,"\
								" spec text,"\
								" text text"

#define DB_DEF_ACTIVITY "INSERT INTO activity ( jidBare, time, nodeId, activity, spec, text) VALUES ("

#define HELP_ECHO " \n"\
			" Jednoltive prikazy vraci udaje na zaklade nasbiranych informaci, tedy co je od Vas prijimano. Pokud existuji data v databazi je vypsano poslednic 10 zaznamu.\n"\
			" Zakladni prikazy : \n"\
			"                  : INFO		- zakladni informace\n"\
			"                  : VCARD   	- vcard \n"\
			"                  : GEOLOC	- geolokace \n"\
			"                  : TUNE		- co prave poslouchate \n"\
			"                  : MOOD    	- aktualni nadala \n"\
			"                  : ACTIVITY	- aktualni cinnost \n"\
			"                  : HISTORY	- historie statusu \n"\
			"                  : HELP   	- tato napoveda \n"\
			"\n"\
			" To jsou vsechny volne dostupne prikazy :)"

#define INFO " Program vznika jako soucast bakalarska prace. Pro jakekoliv dotazy piste na portilo@jabbim.cz\n"

#define NO_SUPPORT "Zadna data z pozadovaneho rozsireni nejsou ulozena v databazi."

#define NO_RIGHT "Nemate dostatecna prava pro provedeni tohoto prikazu!"
