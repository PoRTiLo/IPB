#pragma once

#define QUIT "quit"
#define HALLO "caok"



//database.H
#define DB_SERV "localhost"
#define DB_ADDR "127.0.0.1"
#define DB_PORT "" 
#define DB_USER "portilo"
#define DB_PASS "trewq"
#define DB_NAME "portilo"
#define DB_TIME "10"

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
							" sortstring text"
#define DB_INSERT "Insert into "
#define DB_TABLE_USER " jidBare text PRIMARY KEY,"\
					 		 " date timestamp"
#define DB_SELECT_USER "Select jid from user where jid = '"
#define DB_TABLE_LOGAREA " num integer PRIMARY KEY,"\
								 " name text,"\
								 " description text,"\
								 " descriptionCz text"
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
							 " priority integer"
#define DB_DEF_PRESENCE "INSERT INTO presence ( date, fromJ, toJ, message, name, resource, presence, priority) VALUES ("
#define DB_TABLE_MESSAGE "id serial PRIMARY KEY,"\
							 " date timestamp,"\
							 " fromJ text,"\
							 " toJ text,"\
							 " message text,"\
							 " subject text,"\
							 " thread text,"\
							 " subtype text"
#define DB_DEF_MESSAGE "INSERT INTO message ( date, fromJ, toJ, message, subject, thread, subtype) VALUES ("
