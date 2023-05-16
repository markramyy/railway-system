#pragma once
#include "trip.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>

//setters
void Trip::set_train_number(int trainNumber)
{
	this->train_number = trainNumber;
}
void Trip::set_boarding_point(string boardingPoint)
{
	this->boarding_point = boardingPoint;
}
void Trip::set_destination_point(string destinationPoint)
{
	this->destination_point = destinationPoint;
}
void Trip::set_seats_available(int seatsAvailable)
{
	this->seats_available = seatsAvailable;
}
void Trip::set_fare_per_ticket(int farePerTicket)
{
	this->fare_per_ticket = farePerTicket;
}
void Trip::set_travel_year(int travelYear)
{
	this->travel_year = travelYear;
}
void Trip::set_travel_month(int travelMonth)
{
	this->travel_month = travelMonth;
}
void Trip::set_travel_day(int travelDay)
{
	this->travel_day = travelDay;
}
void Trip::set_num_of_tickets(int numOfTickets)
{
	this->numOfTickets = numOfTickets;
}

// getters
int Trip::get_travel_year()
{
	return this->travel_year;
}
int Trip::get_travel_month()
{
	return this->travel_month;
}
int Trip::get_travel_day()
{
	return this->travel_day;
}
string Trip::get_boarding_point()
{
	return this->boarding_point;
}
string Trip::get_destination_point()
{
	return this->destination_point;
}
int Trip::get_fare_per_ticket()
{
	return this->fare_per_ticket;
}
int Trip::get_train_number()
{
	return this->train_number;
}
int Trip::get_seats_available()
{
	return this->seats_available;
}
int Trip::get_num_of_tickets()
{
	return this->numOfTickets;
}


Trip::Trip() {
	// Implementation of the default constructor
}

Trip::Trip(string BoardingPoint, string DestinationPoint, int day, int month, int year) {
	this->boarding_point = BoardingPoint;
	this->destination_point = DestinationPoint;
	this->travel_day = day;
	this->travel_month = month;
	this->travel_year = year;
}



vector<string> SplitTrip(string str, char seperator)
{
	int startIndex = 0, endIndex = 0;
	vector<string> strings;
	for (unsigned long int i = 0; i <= str.size(); i++)
	{
		if (str[i] == seperator || i == str.size())
		{
			endIndex = i;
			string temp;
			temp.append(str, startIndex, endIndex - startIndex);
			strings.push_back(temp);
			startIndex = endIndex + 1;
		}
	}
	return strings;
}

void getTripsVector(vector<Trip> &tripsArray) {
	fstream readTrips("trips.txt", ios::in);
	string line;
	//vector<Trip> tripsArray;
	//Reading data from trips' file
	if (readTrips.is_open())
	{
		while (getline(readTrips, line))
		{
			Trip trip;
			vector<string> Splitted = SplitTrip(line, ' ');
			trip.set_travel_day(stoi(Splitted[0]));
			trip.set_travel_month(stoi(Splitted[1]));
			trip.set_travel_year(stoi(Splitted[2]));
			trip.set_boarding_point(Splitted[3]);
			trip.set_destination_point(Splitted[4]);
			trip.set_train_number(stoi(Splitted[5]));
			trip.set_seats_available(stoi(Splitted[6]));
			trip.set_fare_per_ticket(stoi(Splitted[7]));
			tripsArray.push_back(trip);
		}
	}
	/*return tripsArray;*/
};



bool DateValidating(int day, int month, int year) {
	//Calculating seconds of the months passed in the year entered before the last month
	long long tripMonthInSeconds = 0;
	switch (month) {
	case 2:
		tripMonthInSeconds = 86400 * 31;
		break;
	case 3:
		tripMonthInSeconds = 86400 * 59;
		break;
	case 4:
		tripMonthInSeconds = 86400 * 90;
		break;
	case 5:
		tripMonthInSeconds = 86400 * 120;
		break;
	case 6:
		tripMonthInSeconds = 86400 * 151;
		break;
	case 7:
		tripMonthInSeconds = 86400 * 181;
		break;
	case 8:
		tripMonthInSeconds = 86400 * 212;
		break;
	case 9:
		tripMonthInSeconds = 86400 * 243;
		break;
	case 10:
		tripMonthInSeconds = 86400 * 273;
		break;
	case 11:
		tripMonthInSeconds = 86400 * 304;
		break;
	case 12:
		tripMonthInSeconds = 86400 * 334;
		break;
	default:
		break;
	}

	// Calculating seconds the years before the last year entered from year 1970
	long long tripYearInSeconds = (static_cast<long long>(year) - 1970);
	tripYearInSeconds *= 31536000;

	// Calculating total seconds from 1970 till the entered date
	long long tripDateInSeconds = tripYearInSeconds + tripMonthInSeconds + (static_cast<long long>(day) * 86400);
	tripDateInSeconds += 1036800;
	time_t currentTime = time(0);
	if (tripDateInSeconds >= static_cast<long long>(currentTime))
		return true;
	else
		return false;
}


void DisplayTrips()
{
	fstream readTrips("trips.txt", ios::in);
	string line;
	vector<Trip> tripsArray;
	cout << "Travel day - month - year - Boarding - Destination - Train number - Fare/ticket - Seats available\n";
	if (readTrips.is_open())
	{
		int counter = 1;
		while (getline(readTrips, line))
		{
			cout << to_string(counter) << "- " << line << endl;
			counter++;
		}

	}
	else
		cout << "file is not open, error in DisplayTrips\n";
}

Trip EnterTripData()
{
	Trip trip;
	int num;
	string word;
	cout << "Enter train number:\n";
	cin >> num;
	trip.set_train_number(num);
	cin.ignore(1, '\n');

	cout << "Enter boarding point:\n";
	getline(cin, word);
	trip.set_boarding_point(word);

	cout << "Enter destination point:\n";
	getline(cin, word);
	trip.set_destination_point(word);

	cout << "Enter number of seats available:\n";
	cin >> num;
	trip.set_seats_available(num);

	cout << "Enter fare per ticket:\n";
	cin >> num;
	trip.set_fare_per_ticket(num);

	cout << "Enter travel day \n";
	cin >> num;
	if (num > 31 || num < 1) {
		cout << "Day entered was invalid\n";
		exit(1);
	}
	else
		trip.set_travel_day(num);

	cout << "Enter travel month \n";
	cin >> num;
	if (num > 12 || num < 1) {
		cout << "Month entered was invalid\n";
		exit(1);
	}
	else
		trip.set_travel_month(num);

	cout << "Enter travel year \n";
	cin >> num;
	trip.set_travel_year(num);


	if (DateValidating(trip.get_travel_day(), trip.get_travel_month(), trip.get_travel_year()))
		return trip;
	else {
		cout << "Error: The date you have entered is before or equivalent to today's date \n";
		exit(1);
	}
}


void AddTrip()
{
	bool isRepeat = true;
	do {
		Trip trip = EnterTripData();
		
		// Declaring file and opening it and second parameter for appending to file and to prevent overwriting
		ofstream outdata;
		outdata.open("trips.txt", ios::out | ios::app);

		if (!outdata) {
			cout << "Error: file could not be opened" << endl;
			exit(1);
		}

		// Checking that train number exists in trains' file;
		fstream readTrains("trains.txt", ios::in);
		string line;
		bool trainExists = false, trainNotAvailable = false;
		if (readTrains.is_open())
		{

			while (getline(readTrains, line))
			{

				vector<string> Splitted = SplitTrip(line, ' ');
				if (trip.get_train_number() == stoi(Splitted[1]))
					trainExists = true;
			}
		}
		// Checking that this train doesn't have another trip on that date
		fstream readTrips("trips.txt", ios::in);
		vector<Trip> tripsArray;

		if (readTrips.is_open())
		{
			while (getline(readTrips, line))
			{

				vector<string> Splitted = SplitTrip(line, ' ');
				if (to_string(trip.get_travel_day()) == Splitted[0] &&
					to_string(trip.get_travel_month()) == Splitted[1] &&
					to_string(trip.get_travel_year()) == Splitted[2] &&
					trip.get_train_number() == stoi(Splitted[5]))
				{
					trainNotAvailable = true;
					break;
				}
			}
		}

		// Adding trip data into the file if it passed the conditions above
		if (trainExists && (!trainNotAvailable))
		{
			outdata << to_string(trip.get_travel_day()) << ' '
				<< to_string(trip.get_travel_month()) << ' '
				<< to_string(trip.get_travel_year()) << ' '
				<< trip.get_boarding_point() << ' '
				<< trip.get_destination_point() << ' '
				<< to_string(trip.get_train_number()) << ' '
				<< to_string(trip.get_seats_available()) << ' '
				<< to_string(trip.get_fare_per_ticket()) << endl;
		}
		else
			cout << "this train number does not exist\n";

		outdata.close();
		cout << "Do you want to add another trip? (y/n)\n";
		string repeat;
		cin >> repeat;
		if (repeat == "y" || repeat == "yes" || repeat == "YES" || repeat == "Y" || repeat == "YS" || repeat == "ys")
			isRepeat = true;
		else
			isRepeat = false;

	} while (isRepeat == true);
}


void ModifyTrip()
{
	DisplayTrips();
	fstream readTrips("trips.txt", ios::in);
	string line;
	vector<Trip> tripsArray;

	// Reading data of the trips file
	if (readTrips.is_open())
	{
		while (getline(readTrips, line))
		{
			Trip trip;
			vector<string> Splitted = SplitTrip(line, ' ');
			trip.set_travel_day(stoi(Splitted[0]));
			trip.set_travel_month(stoi(Splitted[1]));
			trip.set_travel_year(stoi(Splitted[2]));
			trip.set_boarding_point(Splitted[3]);
			trip.set_destination_point(Splitted[4]);
			trip.set_train_number(stoi(Splitted[5]));
			trip.set_seats_available(stoi(Splitted[6]));
			trip.set_fare_per_ticket(stoi(Splitted[7]));
			tripsArray.push_back(trip);
		}
	}

	// Get the trip number that the admin wants to edit
	int tripNumber;
	cout << "Please enter the trip number that you want to edit" << endl;
	cin >> tripNumber;
	tripNumber--;

	cout << "Please enter the number of the property that you want to do edit.\n";
	cout << "1- train number\n2- boarding point, destination point\n3- travel date\n4- seats available\n5- fare\n";

	// Choosing the property that the amdin wants to do
	int propertyNumber;
	cin >> propertyNumber;
	switch (propertyNumber)
	{
	case 1:
	{
		cout << "Enter the new train number\n";
		int newTrainNumber;
		cin >> newTrainNumber;

		// Checking that train number exists in trains' file;
		fstream readTrains("trains.txt", ios::in);
		string line;
		bool trainExists = false;
		if (readTrains.is_open())
		{

			while (getline(readTrains, line))
			{

				vector<string> Splitted = SplitTrip(line, ' ');
				if (newTrainNumber == stoi(Splitted[1]))
					trainExists = true;
			}
		}

		// Condition to check that this train is available at this date 
		bool isTrainAvailable = true;
		for (unsigned long int counter = 0; counter < tripsArray.size(); counter++)
		{
			if (tripNumber != counter)
			{
				if (tripsArray[counter].get_travel_day() == tripsArray[tripNumber].get_travel_day()
					&& tripsArray[counter].get_travel_month() == tripsArray[tripNumber].get_travel_month()
					&& tripsArray[counter].get_travel_year() == tripsArray[tripNumber].get_travel_year()
					&& tripsArray[counter].get_train_number() == tripsArray[tripNumber].get_train_number())
				{
					isTrainAvailable = false;
					break;
				}
			}
		}

		if (isTrainAvailable && trainExists)
			tripsArray[tripNumber].set_train_number(newTrainNumber);
		else
			cout << "Modification cancelled because this train is either not available at this date or doesn't exist\n";
		break;
	}
	case 2:
	{
		cout << "Enter the new boarding point\n";
		string newBoardingPoint;
		cin >> newBoardingPoint;
		cout << "Enter the new destination point\n";
		string newDestinationPoint;
		cin >> newDestinationPoint;

		transform(newBoardingPoint.begin(), newBoardingPoint.end(), newBoardingPoint.begin(), ::tolower);
		transform(newDestinationPoint.begin(), newDestinationPoint.end(), newDestinationPoint.begin(), ::tolower);

		if (newBoardingPoint == newDestinationPoint)
			cout << "Boarding and destination points cannot be the same as each other";
		else
		{
			tripsArray[tripNumber].set_boarding_point(newBoardingPoint);
			tripsArray[tripNumber].set_destination_point(newDestinationPoint);
		}

		break;
	}
	case 3:
	{
		cout << "The New Date:\n";
		cout << "Enter the day:\n";
		int newTravelDay;
		cin >> newTravelDay;
		cout << "Enter the month:\n";
		int newTravelMonth;
		cin >> newTravelMonth;
		cout << "Enter the year:\n";
		int newTravelYear;
		cin >> newTravelYear;

		// Condition to check that this train is available at this date 
		bool isDateAvailable = true;
		for (unsigned long int counter = 0; counter < tripsArray.size(); counter++)
		{
			if (tripNumber != counter)
			{
				if (tripsArray[counter].get_train_number() == tripsArray[tripNumber].get_train_number()
					&& tripsArray[counter].get_travel_day() == newTravelDay
					&& tripsArray[counter].get_travel_month() == newTravelMonth
					&& tripsArray[counter].get_travel_year() == newTravelYear)
				{
					isDateAvailable = false;
					break;
				}
			}
		}

		bool isDateValid = DateValidating(newTravelDay, newTravelMonth, newTravelYear);


		if (isDateAvailable && isDateValid) {
			tripsArray[tripNumber].set_travel_day(newTravelDay);
			tripsArray[tripNumber].set_travel_month(newTravelMonth);
			tripsArray[tripNumber].set_travel_year(newTravelYear);
		}
		else {
			if (!isDateAvailable)
				cout << "Modification cancelled because this train has another trip on this date\n";
			else if (!isDateValid)
				cout << "Modification cancelled because the entered date was invalid\n";
		}
		break;
	}
	case 4:
	{
		cout << "Enter the new number of seats (You cannot enter \n";
		int newNumberOfSeatsAvailable;
		cin >> newNumberOfSeatsAvailable;
		if (newNumberOfSeatsAvailable >= 0)
			tripsArray[tripNumber].set_seats_available(newNumberOfSeatsAvailable - tripsArray[tripNumber].get_seats_available());
		else
			cout << "Negative number entered and that's refused number of seats available\n";

		break;
	}
	case 5:
	{
		cout << "Enter the new fare per ticket\n";
		int newFarePerTicket;
		cin >> newFarePerTicket;
		if (newFarePerTicket >= 0)
			tripsArray[tripNumber].set_fare_per_ticket(newFarePerTicket);
		else
			cout << "Negative number entered and that's a refused fare\n";

		break;
	}
	default:
	{
		break;
	}
	}

	// Entering the modified data into the file
	ofstream file("trips.txt");
	for (unsigned long int i = 0; i < tripsArray.size(); i++)
	{
		file << to_string(tripsArray[i].get_travel_day()) << ' '
			<< to_string(tripsArray[i].get_travel_month()) << ' '
			<< to_string(tripsArray[i].get_travel_year()) << ' '
			<< tripsArray[i].get_boarding_point() << ' '
			<< tripsArray[i].get_destination_point() << ' '
			<< to_string(tripsArray[i].get_train_number()) << ' '
			<< to_string(tripsArray[i].get_seats_available()) << ' '
			<< to_string(tripsArray[i].get_fare_per_ticket()) << endl;
	}
}


void DeleteTrip()
{
	DisplayTrips();
	
	vector<Trip> tripsArray;
	getTripsVector(tripsArray);
	fstream readTrips("trips.txt", ios::out);
	// Get the trip number that the admin wants to edit
	unsigned int tripNumber;
	cout << "Please enter the trip number that you want to delete" << endl;
	cin >> tripNumber;
	tripNumber--;

	if (tripNumber < tripsArray.size() && tripNumber >= 0)
	{
		// Deleting trip from the vector then writing the data into the file
		tripsArray.erase(tripsArray.begin() + tripNumber);
		ofstream file("trips.txt");
		for (unsigned long int i = 0; i < tripsArray.size(); i++)
		{
			file << to_string(tripsArray[i].get_travel_day()) << ' '
				<< to_string(tripsArray[i].get_travel_month()) << ' '
				<< to_string(tripsArray[i].get_travel_year()) << ' '
				<< tripsArray[i].get_boarding_point() << ' '
				<< tripsArray[i].get_destination_point() << ' '
				<< to_string(tripsArray[i].get_train_number()) << ' '
				<< to_string(tripsArray[i].get_seats_available()) << ' '
				<< to_string(tripsArray[i].get_fare_per_ticket()) << endl;
		}
		cout << "Trip deleted Successfully\n";
		file.close();
	}
	else
		cout << "This trip does not exist\n";

	readTrips.close();
}
