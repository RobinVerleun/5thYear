#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char ** argv)
{
	sqlite3 *db;
	sqlite3_stmt *stmt;

		//Return code
		int rc; 

		//Database name, address to db pointer
		rc = sqlite3_open("assignment1.db", &db); 

		//Check the value of the return code and verify operation
		//Utilize sqlite3 errmsg function to get error from current db object
		//Close the db object, and return a value showing error from the program.
		if( rc ) {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(1);
		}

		//Create a sql_statement as a char * (a string)
		//First block gets all active, commerical airports with international travel
		char *sql_stmt = 	"SELECT f.airline_id, f.source_airport_id, f.destination_airport_id "
							"FROM routes f, airports a1, airports a2, airlines l "
							"WHERE f.source_airport_id = a1.airport_id AND f.destination_airport_id = a2.airport_id "
								"AND a1.country != a2.country AND l.active = 'Y' AND l.IATA IS NOT NULL "
								"AND l.ICAO IS NOT NULL AND l.callsign IS NOT NULL AND l.country IS NOT NULL "
								"AND l.airline_id = f.airline_id "
							"EXCEPT "
							//Removes all reciprocal flights from the result
								"SELECT r1.airline_id, r1.source_airport_id, r1.destination_airport_id "
								"FROM routes r1 JOIN routes r2 ON r1.airline_id = r2.airline_id "
								"WHERE r1.source_airport = r2.destination_airport AND r2.source_airport = r1.destination_airport;";

		//Check return code for preparation of sql stmt
		rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);

		//Print error in case statement prepare fails
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(1);
		}

		//sqlite3 step aquires the next row of the statement
		//Column count return number of columns, column text prints col #
		while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			int col;
			for(col = 0; col < sqlite3_column_count(stmt)-1; col++) {
				printf("%s|", sqlite3_column_text(stmt, col));
			}
			printf("%s", sqlite3_column_text(stmt, col));
			printf("\n");
		}

		sqlite3_finalize(stmt);
}