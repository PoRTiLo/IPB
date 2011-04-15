<?php
/*
 * Inicializacni soubor k pripojeni k databazi
 */
/*
DEFINE('DB_USER','user=xsendl00 ');
DEFINE('DB_PASS','password=e5bd224e6d ');
DEFINE('DB_SOURCE','host=localhost ');
DEFINE('DB_DATABASE','dbname=xsendl00 ');
DEFINE('DB_PORT','port=5432 ');
*/

DEFINE('DB_USER','user=portilo ');
DEFINE('DB_PASS','password=trewq ');
DEFINE('DB_SOURCE','host=localhost ');
DEFINE('DB_DATABASE','dbname=portilo ');
DEFINE('DB_PORT','port=5432 ');
DEFINE('DB_TIMEOUT', 'connect_timeout=5 ');


	$connectStr = DB_SOURCE . DB_PORT . DB_DATABASE . DB_USER . DB_PASS;

	$conn = pg_connect($connectStr);

	if (!$conn) 
		die('Nelze se pripojit k databazi PostgreSQL');

?>

