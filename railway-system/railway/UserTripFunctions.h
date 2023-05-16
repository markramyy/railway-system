#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "trip.h"
#include "login.h"

using namespace std;
struct Passenger {
	string name;
	string email;
	string password;
	vector<Trip> reservedTrips;

};
void displayReservations(Passenger *passenger);
void displayPassengerOptions(Passenger *passenger, vector<Trip> &tripsArray);
int isTripAvailableInTrips(Trip tempTrip, vector<Trip> &tripsArray);
void ReserveTrip(Trip tempTrip, Passenger *passenger, int numOfTickets, vector<Trip> &tripsArray);
void cancelReservation(int indexOfTrip, Passenger *passenger, vector<Trip>& tripsArray);
void editReservation(int indexOfTrip, Passenger *passenger, int newNumOfTickets, vector<Trip>& tripsArray);
void updateTripsFile(vector<Trip>& tripsarray);

void displayPassengerOptions(Passenger *passenger, vector<Trip> &tripsArray) {
	int choice, numOfTickets, day, month, year, indexOfTrip, newNumOfTickets;
	string BoardingPoint, DestinationPoint;
	cout << "Enter 1 to diplay reservations" << endl;
	cout << "Enter 2 to reserve a trip" << endl;
	cout << "Enter 3 to edit a reservation" << endl;
	cout << "Enter 4 to cancel a reservation" << endl;
	cout << "Your choice: ";
	cin >> choice;
	if (choice == 1) {
		displayReservations(passenger);
	}
	else if (choice == 2) {
		DisplayTrips();
		cout << "Enter Boarding Point: ";
		cin >> BoardingPoint;
		cout << "Enter Destination Point: ";
		cin >> DestinationPoint;
		cout << "Enter Travel day: ";
		cin >> day;
		cout << "Enter Tavel month: ";
		cin >> month;
		cout << "Enter Travel year: ";
		cin >> year;
		cout << "Enter number of tickets: ";
		cin >> numOfTickets;
		Trip tempTrip(BoardingPoint, DestinationPoint, day, month, year);
		ReserveTrip(tempTrip, passenger, numOfTickets, tripsArray);
	}
	else if (choice == 3) {
		displayReservations(passenger);
		cout << "Enter The number of the trip you wish to edit: ";
		cin >> indexOfTrip;
		indexOfTrip--;
		cout << "Enter the new number of tickets (Negative number to remove tickets and Positive number to add tickets): ";
		cin >> newNumOfTickets;
		editReservation(indexOfTrip, passenger, newNumOfTickets, tripsArray);
	}
	else if (choice == 4) {
		displayReservations(passenger);
		cout << "Enter The number of trip you wish to cancel your reservation from: ";
		cin >> indexOfTrip;
		indexOfTrip--;
		cancelReservation(indexOfTrip, passenger, tripsArray);
	}
	
}
int isTripAvailableInTrips(Trip tempTrip, vector<Trip> &tripsArray) {
	//cout << tripsArray.size()<<endl;

	for (int i = 0; i < tripsArray.size(); i++) 
	{
		if (tempTrip.get_boarding_point() == tripsArray[i].get_boarding_point()
			&& tempTrip.get_destination_point() == tripsArray[i].get_destination_point()
			&& tempTrip.get_travel_day() == tripsArray[i].get_travel_day()
			&& tempTrip.get_travel_month() == tripsArray[i].get_travel_month()
			&& tempTrip.get_travel_year() == tripsArray[i].get_travel_year())
		{
			return i;
		}
		
		}
	cout << "Trip not available in trips";
	return -1;
}
void ReserveTrip(Trip tempTrip, Passenger *passenger, int numOfTickets, vector<Trip> &tripsArray) {
	
	int indexOfTripInTrips = isTripAvailableInTrips(tempTrip, tripsArray);

	if (indexOfTripInTrips != -1) {
		Trip trip = tripsArray[indexOfTripInTrips];
		int numOfSeatsAvailable = trip.get_seats_available();

		if (numOfTickets <= numOfSeatsAvailable) {
			
			numOfSeatsAvailable = numOfSeatsAvailable - numOfTickets;
			trip.set_seats_available(numOfSeatsAvailable);
			passenger->reservedTrips.push_back(trip);
			
			passenger->reservedTrips.back().set_num_of_tickets(numOfTickets);
			cout << "Reservation was successful!" << endl;
			tripsArray[indexOfTripInTrips] = trip;
			cout << passenger->reservedTrips.size()<<endl;
		}
		else
			cout << "Trip has no seats avilable" << endl;

	}
	else
		cout << "invalid trip" << endl;
	cout << passenger->reservedTrips.size() << endl;

}
void cancelReservation(int indexOfTrip, Passenger *passenger, vector<Trip> &tripsArray) {
	
	Trip passengerTrip = passenger->reservedTrips[indexOfTrip];
	int indexOfTripInTrips = isTripAvailableInTrips(passengerTrip, tripsArray);
	Trip trip = tripsArray[indexOfTripInTrips];
	int numOfSeatsAvailable = trip.get_seats_available();
	if (indexOfTrip != NULL) {
		numOfSeatsAvailable = numOfSeatsAvailable + passenger->reservedTrips[indexOfTrip].get_num_of_tickets();
		trip.set_seats_available(numOfSeatsAvailable);
		passenger->reservedTrips.erase(passenger->reservedTrips.begin() + indexOfTrip);
		cout << "Reservation Canceled Successfully!" << endl;
	}
	else
		cout << "Invalid Trip";
}
void editReservation(int indexOfTrip, Passenger *passenger, int newNumOfTickets, vector<Trip> &tripsArray) {
	
	Trip passengerTrip = passenger->reservedTrips[indexOfTrip];
	int indexOfTripInTrips = isTripAvailableInTrips(passengerTrip, tripsArray);
	int totalSeatsToBeReserved = passengerTrip.get_num_of_tickets() + newNumOfTickets;
	Trip trip = tripsArray[indexOfTripInTrips];
	//new number of tickets could be positive for adding tickets or negative for removing tickets from reservation
	if (indexOfTrip != NULL) {
		if (totalSeatsToBeReserved <= trip.get_seats_available() && totalSeatsToBeReserved > 0)
		{
			cancelReservation(indexOfTrip, passenger, tripsArray);
			ReserveTrip(passengerTrip, passenger, totalSeatsToBeReserved, tripsArray);
			cout << "Reservation Updated Successfully" << endl;
		}
		else if (totalSeatsToBeReserved == 0) 
		{
			cancelReservation(indexOfTrip, passenger, tripsArray);
			cout << "Your reservation has been canceled" << endl;
		}
		else
			cout << "invalid number of seats";

	}
	else
		cout << "invalid trip";
}
void displayReservations(Passenger *passenger) {
	cout << passenger->reservedTrips.size() << endl;

	for (int i = 0; i < passenger->reservedTrips.size(); i++) {
		cout << "Trip Number " << i + 1 << endl;
		cout << "Boarding Point: " << passenger->reservedTrips[i].get_boarding_point() << endl;
		cout << "Destination Point: " << passenger->reservedTrips[i].get_destination_point() << endl;
		cout << "Date Of Travel: "
			<< passenger->reservedTrips[i].get_travel_day() << "/"
			<< passenger->reservedTrips[i].get_travel_month() << "/"
			<< passenger->reservedTrips[i].get_travel_year() << endl;
		cout << "Number Of Reserved Tickets: " << passenger->reservedTrips[i].get_num_of_tickets() << endl;
		cout << "Train Number: " << passenger->reservedTrips[i].get_train_number() << endl;
	}
}
void updateTripsFile(vector<Trip>& tripsarray) {
	fstream f("trips.txt");
	for (int i = 0; i < tripsarray.size(); i++) {
		f << tripsarray[i].get_travel_day() <<
			" " << tripsarray[i].get_travel_month() <<
			" " << tripsarray[i].get_travel_year() <<
			" " << tripsarray[i].get_boarding_point() <<
			" " << tripsarray[i].get_destination_point() <<
			" " << tripsarray[i].get_train_number() <<
			" " << tripsarray[i].get_seats_available() <<
			" " << tripsarray[i].get_fare_per_ticket()<<endl;
	}


}
