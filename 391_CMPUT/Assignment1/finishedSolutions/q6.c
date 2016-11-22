#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


int main(int argc, char ** argv) {

	sqlite3 *db;
	sqlite3_stmt *stmt;

		int rc;
		
		rc = sqlite3_open("assignment1.db", &db);
		if( rc ) {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
			return 1;
		}

		char * sql_stmt = 	"SELECT DISTINCT r.destination_airport "
							"FROM routes r "
							"WHERE "
								"r.source_airport = 'YEG' "
							"UNION "
							"SELECT DISTINCT r2.destination_airport "
							"FROM routes r1, routes r2 "
							"WHERE "
								"r1.source_airport = 'YEG' AND "
								"r1.destination_airport = r2.source_airport "
							"UNION "
							"SELECT DISTINCT r3.destination_airport "
							"FROM routes r1, routes r2, routes r3 "
							"WHERE "
								"r1.source_airport = 'YEG' AND "
								"r1.destination_airport = r2.source_airport AND "
								"r2.destination_airport = r3.source_airport;";

		rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Preperation failed: %s\n", sqlite3_errmsg(db));
			return 1;
		}

		while(sqlite3_step(stmt) == SQLITE_ROW) {
			printf("Airport: %s\n", sqlite3_column_text(stmt,0));
		}

		sqlite3_finalize(stmt);
		return 0;
}