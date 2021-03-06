#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sqlite3.h"

#define AIRLINE_COL 0
#define SRC_AIRPORT_COL 1
#define DEST_AIRPORT_COL 2
#define SRC_LAT_COL 3
#define SRC_LONG_COL 4
#define DEST_LAT_COL 5
#define DEST_LONG_COL 6
#define OPERATION_SUCCESS 0
#define OPERATION_FAIL 1

typedef struct {
	int airline_ID;
	int source_airport_ID;
	int destination_airport_ID;
	double distance;
} routeInformation;

//Prototyping
double calculateDistance(double, double, double, double);
double degrees_to_radians(double);
int q4_query_GetCount(sqlite3 *, sqlite3_stmt *, int *);
int q4_query_DistanceInfo(sqlite3 *, sqlite3_stmt *, routeInformation *, int);
int q5_create_DistanceTable(sqlite3 *, sqlite3_stmt *);
int q5_insert_LongestFlights(sqlite3 *, sqlite3_stmt *, routeInformation *, int);
int q5_query_Equipment(sqlite3 *, sqlite3_stmt *);
int q5_drop_tempTable(sqlite3 *, sqlite3_stmt *);

int main(int argc, char ** argv) {
	sqlite3 *db;
	sqlite3_stmt  *stmt;

		int rc;
		int row_count;
		routeInformation *routeInfo;


		rc = sqlite3_open("assignment1.db", &db);
		if( rc != OPERATION_SUCCESS ) {
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return 1;
		}

		//Clear the database in case temp exists.
		rc = q5_drop_tempTable(db, stmt);
		if (rc != OPERATION_SUCCESS ) {
			return 1;
		}

		//Query the amount of rows in the return set
		rc = q4_query_GetCount(db, stmt, &row_count);
		if( rc != OPERATION_SUCCESS ) {
			return 1;
		}

		//Allocate space in memory to store query results
		routeInfo = (routeInformation*) malloc(sizeof(routeInformation) * row_count);

		//Create the temp table to hold results
		rc = q5_create_DistanceTable(db, stmt);
		if( rc != OPERATION_SUCCESS ) {
			return 1;
		}

		//Query for calculation information, store in memory
		rc = q4_query_DistanceInfo(db, stmt, routeInfo, row_count);
		if( rc != OPERATION_SUCCESS ) {
			return 1;
		}

		//Insert values into the temp table
		rc = q5_insert_LongestFlights(db, stmt, routeInfo, row_count);
		if( rc != OPERATION_SUCCESS ) {
			return 1;
		}

		//Query against the temp table
		rc = q5_query_Equipment(db, stmt);
		if (rc != OPERATION_SUCCESS ) {
			return 1;
		}
		
		//Drop the table at the end
		rc = q5_drop_tempTable(db, stmt);
		if (rc != OPERATION_SUCCESS ) {
			return 1;
		}

		return 0;
}


double calculateDistance(double lat1, double long1, double lat2, double long2) {
	double lat1_rad = degrees_to_radians(lat1);
	double lat2_rad = degrees_to_radians(lat2);
	double delta_lat = lat2_rad - lat1_rad;
	double delta_lon = degrees_to_radians(long2) - degrees_to_radians(long1);
	double R = 6371 * 1000; //Earths radius in m
	
	double a = 	pow(sin(delta_lat / 2), 2) +
			   	cos(lat1_rad) * cos(lat2_rad) *
				pow(sin(delta_lon / 2), 2);

	double c = 2 * atan2(sqrt(a), sqrt(1-a));

	return R * c;
}

double degrees_to_radians(double degrees) {
	return (degrees * M_PI) / 180;
}

int q4_query_GetCount(sqlite3 *db, sqlite3_stmt *stmt, int *row_count) {	
	char * sql_stmt = 	"SELECT count(*) "
						"FROM routes f, airports a1, airports a2, airlines l "
							"WHERE "
							"l.ICAO IS NOT NULL AND l.IATA IS NOT NULL "
							"AND l.callsign IS NOT NULL AND l.country IS NOT NULL "
							"AND l.airline_id = f.airline_id "
							"AND f.source_airport_id = a1.airport_ID "
							"AND f.destination_airport_id = a2.airport_id;";

	if (sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0) != SQLITE_OK) {
		fprintf(stderr, "Preparation failed (get count): %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return OPERATION_FAIL;
	}

	if(sqlite3_step(stmt) == SQLITE_ROW) {
		*row_count = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		return OPERATION_SUCCESS;
	} else {
	 	fprintf(stderr, "Reading from result table failed (get count): %s\n", sqlite3_errmsg(db));
	 	sqlite3_close(db);
	 	return OPERATION_FAIL;
	}
}

int q4_query_DistanceInfo(sqlite3 *db, sqlite3_stmt *stmt, routeInformation *routeInfo, int row_count) {
	char * sql_stmt =	"SELECT f.airline_id, f.source_airport_id, f.destination_airport_id, "
							"a1. latitude, a1.longtitude, a2.latitude, a2.longtitude "
						"FROM routes f, airports a1, airports a2, airlines l "
						"WHERE "
							"l.ICAO IS NOT NULL AND l.IATA IS NOT NULL "
							"AND l.callsign IS NOT NULL AND l.country IS NOT NULL "
							"AND l.airline_id = f.airline_id "
							"AND f.source_airport_id = a1.airport_ID "
							"AND f.destination_airport_id = a2.airport_id;";

	int rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Preparation failed (Distance Info): %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(OPERATION_FAIL);
	}

	int row;
	for(row = 0; row < row_count; row++) {
		if(sqlite3_step(stmt) == SQLITE_ROW) {
			routeInfo[row].airline_ID = sqlite3_column_int(stmt, AIRLINE_COL);
			routeInfo[row].source_airport_ID = sqlite3_column_int(stmt, SRC_AIRPORT_COL);
			routeInfo[row].destination_airport_ID = sqlite3_column_int(stmt, DEST_AIRPORT_COL);
			routeInfo[row].distance = 
				calculateDistance(sqlite3_column_double(stmt, SRC_LAT_COL),
									sqlite3_column_double(stmt, SRC_LONG_COL),
									sqlite3_column_double(stmt, DEST_LAT_COL),
									sqlite3_column_double(stmt, DEST_LONG_COL));	
		} else {
			fprintf(stderr, "Reading from result table failed (Distance Info): %s\n", sqlite3_errmsg(db));
			return (OPERATION_FAIL);
		}
	}
	sqlite3_finalize(stmt);
	return OPERATION_SUCCESS;
}

int q5_create_DistanceTable(sqlite3 *db, sqlite3_stmt *stmt) {
	char* sql_stmt =  "CREATE TABLE temp("
						"airline_id int, "
						"source_airport_id int, "
						"destination_airport_id int, "
						"distance double);";

	int rc;
	rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0); 
	if(rc != SQLITE_OK) {
		fprintf(stderr, "Preparation failed (make table): %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return OPERATION_FAIL;
	}

	rc = sqlite3_step(stmt);
	if(rc != SQLITE_DONE) {
		fprintf(stderr, "Table creation failed: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return OPERATION_FAIL;
	}

	sqlite3_finalize(stmt);
	return OPERATION_SUCCESS;	
}

int q5_insert_LongestFlights(sqlite3 *db, sqlite3_stmt *stmt, routeInformation *routeInfo, int row_count) {

	char insert_stmt[100];
	int rc;
	int row;

	char * sql_stmt = "INSERT INTO temp VALUES(?,?,?,?);";
	rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
	if (rc != SQLITE_OK) 
	{
		fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(OPERATION_FAIL);
	}

	for(row = 0; row < row_count; row++) {
		if(routeInfo[row].distance >= 10000000) {

			sqlite3_bind_int(stmt, 1, routeInfo[row].airline_ID);
			sqlite3_bind_int(stmt, 2, routeInfo[row].source_airport_ID);
			sqlite3_bind_int(stmt, 3, routeInfo[row].destination_airport_ID);
			sqlite3_bind_double(stmt, 4, routeInfo[row].distance);
		
			sqlite3_step(stmt);
			sqlite3_reset(stmt);
			sqlite3_clear_bindings(stmt);
		}
	}
	sqlite3_finalize(stmt);
	return OPERATION_SUCCESS;
}

int q5_query_Equipment(sqlite3 *db, sqlite3_stmt *stmt) {
	char * sql_stmt = 	"SELECT DISTINCT substr(r.equipment, 1, 3) "
						"FROM routes r, temp t "
						"WHERE "
							"r.airline_id = t.airline_id AND "
							"r.source_airport_id = t.source_airport_id AND "
							"r.destination_airport_id = t.destination_airport_id;";


	if(sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0) != SQLITE_OK) {
		fprintf(stderr, "Preparation failed (get equipment): %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return OPERATION_FAIL;		
	}	

	while(sqlite3_step(stmt) == SQLITE_ROW){
		printf("Equipment: %.3s\n", sqlite3_column_text(stmt, 0));
	}

	sqlite3_finalize(stmt);
	return OPERATION_SUCCESS;
}

int q5_drop_tempTable(sqlite3 *db, sqlite3_stmt *stmt) {
	char * sql_stmt = "DROP TABLE IF EXISTS temp;";

	int rc;

	rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "Preparation failed (drop temp): %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return OPERATION_FAIL;		
	}

	rc = sqlite3_step(stmt);
	if(rc != SQLITE_DONE) {
		fprintf(stderr, "Table drop failed: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return OPERATION_FAIL;
	}

	sqlite3_finalize(stmt);
	return OPERATION_SUCCESS;
}




