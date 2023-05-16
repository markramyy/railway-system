#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include "UserTripFunctions.h"


using namespace std;





bool isValidEmail(const string& email) {
    // Regular expression pattern for email validation
    const regex emailPattern(R"([A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,})");
    return regex_match(email, emailPattern);
}

// Function to signup a new user
void signUp(map<string, Passenger*>& passengers) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if the username already exists
    if (passengers.find(username) != passengers.end()) {
        cout << "Username already exists! Please choose a different username.\n";
        return;
    }

    Passenger *newPassenger= new Passenger;
    newPassenger->name = username;

    bool validEmail = false;
    while (!validEmail) {
        cout << "Enter email: ";
        getline(cin, newPassenger->email);
        validEmail = isValidEmail(newPassenger->email);

        if (!validEmail) {
            cout << "Invalid email format. Please enter a valid email {name@example.com}. " << endl;
        }
    }

    cout << "Enter password: ";
    cin >> newPassenger->password;

    // Add the new passenger to the map
    passengers[username] = newPassenger;
    cout << "Signup successful!\n";
}


// Function to login an existing user
void login( map<string, Passenger*> passengers, vector<Trip>& tripsArray) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if the username exists
    auto it = passengers.find(username);
    if (it == passengers.end()) {
        cout << "Username not found! Please sign up first.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Check if the password is correct
    if (it->second->password == password) {
         Passenger *passenger = it->second;
        cout << "Login successful!\n";
        //cout << passenger->reservedTrips.size() << endl;
        displayPassengerOptions(passenger, tripsArray);

    }
    else {
        cout << "Incorrect password! Please try again.\n";
    }
}

// Function to save the passenger map to a file
void savePassengerData(map<string, Passenger*>& passengers) {
    ofstream file("passenger_data.txt");
    if (file.is_open()) {
        for (auto& passenger : passengers) {
            file << passenger.first << " " << passenger.second->email << " " << passenger.second->password<<" "<< passenger.second->reservedTrips.size() << endl;
            for (int i = 0; i < passenger.second->reservedTrips.size(); i++) {
                file << passenger.second->reservedTrips[i].get_travel_day() <<
                    " " << passenger.second->reservedTrips[i].get_travel_month() <<
                    " " << passenger.second->reservedTrips[i].get_travel_year() <<
                    " " << passenger.second->reservedTrips[i].get_boarding_point() <<
                    " " << passenger.second->reservedTrips[i].get_destination_point() <<
                    " " << passenger.second->reservedTrips[i].get_train_number() <<
                    " " << passenger.second->reservedTrips[i].get_seats_available() <<
                    " " << passenger.second->reservedTrips[i].get_fare_per_ticket() <<
                    " " << passenger.second->reservedTrips[i].get_num_of_tickets()<< endl;


            }
        }
        file.close();
        cout << "Passenger data saved to file.\n";
    }
    else {
        cout << "Unable to open file for saving passenger data.\n";
    }
}

// Function to load passenger data from a file
void loadPassengerData(map<string, Passenger*>& passengers) {
    ifstream file("passenger_data.txt");
    if (file.is_open()) {
        string username, email, password;
        int tripSize;
        while (file >> username >> email >> password>> tripSize) {
            Passenger* passenger= new Passenger;
            passenger->name = username;
            passenger->email = email;
            passenger->password = password;

            for (int i = 0; i < tripSize; i++) {
                Trip trip;
                int train_number;
                string boarding_point;
                string destination_point;
                int seats_available;
                int fare_per_ticket;
                int travel_year;
                int travel_month;
                int travel_day;
                int numOfTickets;

                file >> travel_day >> travel_month >> travel_year >> boarding_point >> destination_point >> train_number >> seats_available >> fare_per_ticket >> numOfTickets;
                trip.set_travel_day(travel_day);
                trip.set_travel_month(travel_month);
                trip.set_travel_year(travel_year);
                trip.set_boarding_point(boarding_point);
                trip.set_destination_point(destination_point);
                trip.set_train_number(train_number);
                trip.set_seats_available(seats_available);
                trip.set_fare_per_ticket(fare_per_ticket);
                trip.set_num_of_tickets(numOfTickets);
                passenger->reservedTrips.push_back(trip);
            }
            passengers[username] = passenger;

        }
        file.close();

        cout << "Passenger data loaded from file.\n";
    }
    else {
        cout << "No existing passenger data found.\n";
    }
}

