#include "sqlite3.h"

#include <iostream>
#include <cstring>

using namespace std;

int charcount(char* str, const char c) {
	int count = 0;
	while(*str) {
		if (*str == c) {
			count++;
		}
		str++;
	}
	return count;
}

int execute(sqlite3* db, const char* command) {
	sqlite3_stmt *stmt;

	while(charcount((char*)command, ';') > 0) {
		sqlite3_prepare_v2(db, command, strlen(command), &stmt, &command);

		switch(sqlite3_step(stmt)) {
			case SQLITE_DONE:
				cout << "done" << endl;
			break;

			case SQLITE_ROW:
				do {
					cout << "row: ";
					//output the row's data
					for (int i = 0; i < sqlite3_column_count(stmt); i++) {
						switch(sqlite3_column_type(stmt, i)) {
							case SQLITE_INTEGER:
								cout << "integer: ";
								cout << sqlite3_column_int(stmt, i);
							break;

							case SQLITE_FLOAT:
								cout << "float: ";
								cout << sqlite3_column_double(stmt, i);
							break;

							case SQLITE_TEXT:
								cout << "text: ";
								cout << sqlite3_column_text(stmt, i);
							break;

							case SQLITE_BLOB:
								cout << "blob";
							break;

							case SQLITE_NULL:
								cout << "null";
							break;

							default:
								cerr << "unknown type";
							break;
						}
					}
					cout << endl;
				}
				while(sqlite3_step(stmt) == SQLITE_ROW);
			break;

			case SQLITE_ERROR:
				cerr << "error" << endl;
				sqlite3_finalize(stmt);
				return 1;

			default:
				cerr << "default error" << endl;
				sqlite3_finalize(stmt);
				return 1;
		}
		cout << "command compete" << endl;
		sqlite3_reset(stmt);
	}

	cout << "input complete" << endl;
	sqlite3_finalize(stmt);
	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3 *db;

	if (sqlite3_open("file.db", &db) != SQLITE_OK) {
		cerr << "Failed to open the database" << endl;
		sqlite3_close(db);
		return 1;
	}

	const char *command = "\
	CREATE TABLE IF NOT EXISTS user ('name' TEXT,'age' NUMERIC,'cats' NUMERIC,'programmer' TEXT);\
	INSERT OR REPLACE INTO user VALUES('Kayne', 21, 5, 'true');\
	INSERT OR REPLACE INTO user VALUES('Chris', 23, 1, 'true');\
	INSERT OR REPLACE INTO user VALUES('Logan', 21, 0, 'true');\
	INSERT OR REPLACE INTO user VALUES('Jordan', 17, 5, 'false');\
	";

	execute(db, command);

	command = "SELECT * FROM user;";

	execute(db, command);

	sqlite3_close(db);
	return 0;
}