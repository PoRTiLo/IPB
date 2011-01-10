#include <pqxx/pqxx>

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#define DB_SERV "localhost"
#define DB_USER "portilo"
#define DB_PASS "javier"
#define DB_NAME "demo"
#define POSTGRE_DBNAME "dbname="

using namespace std;
using namespace pqxx;

int main() {

	try {
		string db_name = POSTGRE_DBNAME;
		db_name += DB_USER;
		connection C(db_name);
cout << "dbname " << C.dbname() << endl;
cout << "username " << C.username() << endl;
cout << "port " << C.port() << endl; 
cout << "is open?" << C.is_open() << endl;

		//C.activate();:
		work W(C);
		result R = W.exec("SELECT * from *");

	} catch(const runtime_error& e) {
		cerr << "Runtime errror:" << e.what() << endl;
		exit(EXIT_FAILURE);
	} catch(const exception& e) {
		cerr << "Exception error:" << e.what() << endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
