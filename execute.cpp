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
			break;

			case SQLITE_ROW:
				//output the row's data
				for (int i = 0; i < sqlite3_column_count(stmt); i++) {
					switch(sqlite3_column_type(stmt, i)) {
						case SQLITE_INTEGER:
							cout << sqlite3_column_int(stmt, i);
						break;

						case SQLITE_FLOAT:
							cout << sqlite3_column_double(stmt, i);
						break;

						case SQLITE_TEXT:
							cout << sqlite3_column_text(stmt, i);
						break;

						case SQLITE_BLOB:
							cout << "[blob]";
						break;

						case SQLITE_NULL:
							cout << "[null]";
						break;
					}
				}
			break;

			case SQLITE_ERROR:
				sqlite3_finalize(stmt);
				return 1;

			default:
				sqlite3_finalize(stmt);
				return 1;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_finalize(stmt);
	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3 *db;

	if (sqlite3_open("db", &db) != SQLITE_OK) {
		cerr << "Failed to open the database" << endl;
		sqlite3_close(db);
		return 1;
	}

	const char *command = "\
	CREATE TABLE IF NOT EXISTS user ('name' TEXT,'age' NUMERIC,'cats' NUMERIC,'programmer' TEXT);\
	INSERT INTO user VALUES('Kayne', 21, 5, 'true');\
	INSERT INTO user VALUES('Chris', 22, 1, 'true');\
	INSERT INTO user VALUES('Logan', 21, 0, 'true');\
	INSERT INTO user VALUES('Jordan', 17, 5, 'false');\
	";

	execute(db, command);

	command = "SELECT * FROM user";

	execute(db, command);

	sqlite3_close(db);
	return 0;
}