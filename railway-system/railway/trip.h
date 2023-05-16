#pragma once
#include <string>
#include <vector>
using namespace std;

class Trip
{
	int train_number;
	string boarding_point;
	string destination_point;
	int seats_available;
	int fare_per_ticket;
	int travel_year;
	int travel_month;
	int travel_day;
	int numOfTickets;

public:

	void set_train_number(int);
	void set_boarding_point(string);
	void set_destination_point(string);
	void set_seats_available(int);
	void set_fare_per_ticket(int);
	void set_travel_year(int);
	void set_travel_month(int);
	void set_travel_day(int);
	void set_num_of_tickets(int);

	int get_train_number();
	string get_boarding_point();
	string get_destination_point();
	int get_seats_available();
	int get_fare_per_ticket();
	int get_travel_year();
	int get_travel_month();
	int get_travel_day();
	int get_num_of_tickets();
	Trip();
	Trip(string, string, int, int, int);
	
};

//Functions

bool DateValidating(int day, int month, int year);
void DisplayTrips();
Trip EnterTripData();
vector<string> SplitTrip(string str, char seperator);
void AddTrip();
void ModifyTrip();
void getTripsVector(vector<Trip> &tripsArray);

void DeleteTrip();
