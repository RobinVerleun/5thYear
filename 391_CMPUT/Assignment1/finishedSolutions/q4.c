#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>

#define AIRLINE_COL 0
#define SRC_AIRPORT_COL 1
#define DEST_AIRPORT_COL 2
#define SRC_LAT_COL 3
#define SRC_LONG_COL 4
#define DEST_LAT_COL 5
#define DEST_LONG_COL 6

typedef struct {
	int airline_ID;
	int source_airport_ID;
	int destination_airport_ID;
	double distance;
} routeInformation;

//Prototyping
double calculateDistance(double, double, double, double);
double degrees_to_radians(double);
void sort_routes(routeInformation *, int);
void print_routes(routeInformation *);

int main(int argc, char ** argv)
{
	sqlite3 *db;
	sqlite3_stmt  *stmt;

		int rc;
		int row_count;
		routeInformation *routeInfo;

		rc = sqlite3_open("assignment1.db", &db);

		if( rc ) 
		{
			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(1);
		}

		char * sql_stmt1 = 	"SELECT count(*) "
							"FROM routes f, airports a1, airports a2, airlines l "
							"WHERE "
								"l.ICAO IS NOT NULL AND l.IATA IS NOT NULL "
								"AND l.callsign IS NOT NULL AND l.country IS NOT NULL "
								"AND l.airline_id = f.airline_id "
								"AND f.source_airport_id = a1.airport_ID "
								"AND f.destination_airport_id = a2.airport_id;";


		char * sql_stmt2 =	"SELECT f.airline_id, f.source_airport_id, f.destination_airport_id, "
								"a1. latitude, a1.longtitude, a2.latitude, a2.longtitude "
							"FROM routes f, airports a1, airports a2, airlines l "
							"WHERE "
								"l.ICAO IS NOT NULL AND l.IATA IS NOT NULL "
								"AND l.callsign IS NOT NULL AND l.country IS NOT NULL "
								"AND l.airline_id = f.airline_id "
								"AND f.source_airport_id = a1.airport_ID "
								"AND f.destination_airport_id = a2.airport_id;";

		rc = sqlite3_prepare_v2(db, sql_stmt1, -1, &stmt, 0);

		if (rc != SQLITE_OK) 
		{
			fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(1);
		}

		//Get the count from the count statement - throw an error if it fails
		//because the count is critical
		if(sqlite3_step(stmt) == SQLITE_ROW) 
		{
			row_count = sqlite3_column_int(stmt, 0);
		} 
		else 
		{
		 	fprintf(stderr, "Reading from result table failed: %s\n", sqlite3_errmsg(db));
		 	sqlite3_close(db);
		 	return(1);
		}

		//Allocate space for reading in the result table
		routeInfo = (routeInformation*) malloc(sizeof(routeInformation) * row_count);

		//Prepare second sql statement
		rc = sqlite3_prepare_v2(db, sql_stmt2, -1, &stmt, 0);

		int row;
		for(row = 0; row < row_count; row++)
		{
			if(sqlite3_step(stmt) == SQLITE_ROW)
			{
				routeInfo[row].airline_ID = sqlite3_column_int(stmt, AIRLINE_COL);
				routeInfo[row].source_airport_ID = sqlite3_column_int(stmt, SRC_AIRPORT_COL);
				routeInfo[row].destination_airport_ID = sqlite3_column_int(stmt, DEST_AIRPORT_COL);
				routeInfo[row].distance = 
					calculateDistance(sqlite3_column_double(stmt, SRC_LAT_COL),
										sqlite3_column_double(stmt, SRC_LONG_COL),
										sqlite3_column_double(stmt, DEST_LAT_COL),
										sqlite3_column_double(stmt, DEST_LONG_COL));
				
			} 
			else 
			{
				fprintf(stderr, "Reading from result table failed: %s\n", sqlite3_errmsg(db));
				return (1);
			}

		}

		sort_routes(routeInfo, row_count);
		print_routes(routeInfo);

		sqlite3_finalize(stmt);
}

double calculateDistance(double lat1, double long1, double lat2, double long2)
{
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

double degrees_to_radians(double degrees) 
{
	return (degrees * M_PI) / 180;
}

void sort_routes(routeInformation * routeInfo, int count) 
{
	int row, j, k;
	routeInformation temp;
	for(j = 0; j < count; j++) 
	{
		for(k = j+1; k < count; k++)
		{
			if(routeInfo[j].distance < routeInfo[k].distance)
			{
				temp = routeInfo[j];
				routeInfo[j]  = routeInfo[k];
				routeInfo[k] = temp;
			} 
		}
	}
}

void print_routes(routeInformation * routeInfo)
{
	int row;
	for(row = 0; row < 10; row++){
		printf("Route Identifier (Airline ID, Source Airport ID, Destination Airport ID): " 
			"%d | %d | %d | Distance (m): %f \n", 
			routeInfo[row].airline_ID, 
			routeInfo[row].source_airport_ID,
			routeInfo[row].destination_airport_ID,
			routeInfo[row].distance);
	}
}




