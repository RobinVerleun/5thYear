#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char ** argv) {

	sqlite3 *db;
	sqlite3_stmt *stmt;

		int rc;

		rc = sqlite3_open("assignment1.db", &db);

		if( rc ) {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return 1;
		}

		char *sql_stmt = 	"WITH RECURSIVE alt(airport_alias, name) AS "
							"( "
								"SELECT r.destination_airport, a.name " 
								"FROM routes r JOIN airports a "
									"ON r.destination_airport_id = a.airport_id "
								"WHERE "
									"r.source_airport = 'YEG' "
								
								"UNION "
								
								"SELECT r2.destination_airport, a2.name "
								"FROM routes r2 JOIN airports a2 "
									"ON r2.destination_airport_id = a2.airport_id, "
									"alt "
								"WHERE "
									"alt.airport_alias = r2.source_airport"
							") "
							"SELECT a.IATA_FAA, a.name, a.altitude "
							"FROM airports a, alt "
							"WHERE "
								"a.IATA_FAA = alt.airport_alias "
								"ORDER BY a.altitude DESC "
								"LIMIT 1;";

		rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(1);
		}

		while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			int col;
			for(col = 0; col < sqlite3_column_count(stmt)-1; col++) {
				printf("%s|", sqlite3_column_text(stmt, col));
			}
			printf("%s", sqlite3_column_text(stmt, col));
			printf("\n");
		}

		sqlite3_finalize(stmt);

		return 0;

}