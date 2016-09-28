#include <stdio.h>
#include <sqlite3.h>

int main( int argc, char **argv) {

	sqlite3 *db;
	sqlite3_stmt *stmt;

		int rc;

		if(argc != 2) {
			fprintf(stderr, "Usage: %s <Airport IATA Code>\n", argv[0]);
			return 1;
		}

		rc = sqlite3_open("assignment1.db", &db);
		if( rc ) {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return 1;
		}

		char *sql_stmt =	"WITH RECURSIVE alt(alias, name) AS ( "
								"SELECT r.destination_airport, a.name " 
								"FROM routes r JOIN airports a ON r.destination_airport_id = a.airport_id "
								"WHERE r.source_airport = ? "
								"UNION "
								"SELECT r2.destination_airport, a2.name "
								"FROM routes r2 JOIN airports a2 ON r2.destination_airport_id = a2.airport_id, alt "
								"WHERE alt.alias = r2.source_airport) "
							"SELECT DISTINCT a1.IATA_FAA, a1.name "
							"FROM airports a1, airports a2, routes r, airlines l "
							"WHERE "
								"l.country IS NOT NULL AND l.ICAO IS NOT NULL AND "
								"l.IATA IS NOT NULL AND l.callsign IS NOT NULL AND "
								"l.airline_id = r.airline_id "
								"AND "
								"r.source_airport_id = a1.airport_id AND "
								"r.destination_airport_id = a2.airport_id "
							"EXCEPT "
							"SELECT * FROM alt;";



		rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return 1;
		}

		sqlite3_bind_text(stmt, 1, argv[1], 3, SQLITE_STATIC);

		while(sqlite3_step(stmt) == SQLITE_ROW) {
			printf("%s | %s\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1));
		}

		sqlite3_finalize(stmt);

	return 0;
}