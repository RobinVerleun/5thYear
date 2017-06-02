

class ReservationDA {

	private DBConnection dbConnection;

	public ReservationDA() {
		dbConnection = DatabaseConnector.connect(ADDRESS);
	}


	//Method to addNewReservation
	public void addNewReservation(Reservation R)
				throws DatabaseConnectionException {

		openConnection(dbConnection);

		//Build the SQL Insert statement
		//Final field is null, for eventual expense report statements
		String insert;
		insert  = "INSERT INTO reservations VALUES";
		insert += "(R.getID), (R.getMemberID), (R.getVehicleID), ";
		insert += "(R.timeMade), (R.getPickupTime), (R.getLatitude), ";
		insert += "(R.getLongtitude), (NULL);"; 

		try {
			if(executeStatement(insert)) {
				System.log("Error inserting reservation statement");
			}
		} catch(Exception e) {
			System.log("Issue connecting to database.");
		}	
	}
	
	public void delete(int resID)
				throws DatabaseConnectionException, NotFoundException {

		openConnection(dbConnection);

		String delete;
		delete  = "DELETE FROM reservations "
		delete += "WHERE reservationID = " + resID + ";";

		try {
			if(executeStatement(insert)) {
				System.log("Error deleting reservation");
			}
		} catch(NotFoundException e) {
			System.log("Reservation not found in database.");
		} catch(DatabaseConnectionException) {
			System.log("Issue connecting to database.");
		}
	}

	public Reservation find(int resID)
				throws DatabaseConnectionException, NotFoundException {

		openConnection(dbConnection);

		//Build the SQL Insert statement
		//Final field is null, for eventual expense report statements
		String query;
		query  = "SELECT * FROM reservations ";
		query += "WHERE reservationID = " + resID + ";"; 

		result = executeStatement(query);

		try {
			if(result) {
				System.log("Error finding reservation statement");
			}
		} catch(NotFoundException e) {
			System.log("Reservation not found in database.");
		} catch(DatabaseConnectionException) {
			System.log("Issue connecting to database.");
		}

		Reservation foundRes = new Reservation();

		foundRes.setID(result.column[0]);
		foundRes.setMemberID(result.column[1]);
		foundRes.setVehicleID(result.column[2]);
		foundRes.setTimeMade(result.column[3]);
		foundRes.setPickupTime(result.column[4]);
		foundRes.setLatitude(result.column[5]);
		foundRes.setLongtitude(result.column[6]);
		foundRes.setExpenseReport(result.column[7]);

		return foundRes;
	}
}