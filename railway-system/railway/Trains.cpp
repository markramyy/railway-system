#include "Trains.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;


Trains::Trains(string name, int number)
{
    this->name = name;
    this->number = number;
}

Trains::Trains(int year, int month, int day, string dest, string board, int number, int fare, int seats)
{
    this->year = year;
    this->month = month;
    this->day = day;
    this->dest = dest;
    this->board = board;
    this->number = number;
    this->fare = fare;
    this->seats = seats;
}

void Trains::setName(string name)
{
    this->name = name;
}

void Trains::setMonth(int month)
{
    this->month = month;
}

void Trains::setYear(int year)
{
    this->year = year;
}

void Trains::setDay(int day)
{
    this->day = day;
}

void Trains::setDest(string dest)
{
    this->dest = dest;
}

void Trains::setBoard(string board)
{
    this->board = board;
}

void Trains::setFare(int fare)
{
    this->fare = fare;
}

void Trains::setSeats(int seats)
{
    this->seats = seats;
}

void Trains::setNumber(int number)
{
    this->number = number;
}

string Trains::getName()
{
    return name;
}

string Trains::getDest()
{
    return dest;
}

string Trains::getBoard()
{
    return board;
}

int Trains::getYear()
{
    return year;
}

int Trains::getMonth()
{
    return month;
}

int Trains::getDay()
{
    return day;
}

int Trains::getFare()
{
    return fare;
}

int Trains::getSeats()
{
    return seats;
}

int Trains::getNumber()
{
    return number;
}

void writeTrainToFile(vector<Trains>& trains, string filename) {
    ofstream file(filename);

    for (int i = 0; i < trains.size(); i++) {
        file << trains[i].getName() << ' ' << trains[i].getNumber() << endl;
    }

    file.close();
}


vector<string> SplitTrain(string str, char seperator)
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

void fillTrain() {
    vector<Trains> myclass;
    string name;
    int number;
    cout << "how many trains do you want to add : " << endl;
    int trainsize;
    cout << "Enter the number of trains you want to add: ";
    cin >> trainsize;

    for (int i = 0; i < trainsize; i++)
    {
        cout << "Enter train name: ";
        cin >> name;
        cout << "Enter train number: ";
        cin >> number;
        Trains tr(name, number);

        bool trainExists = false;
        ifstream file("trains.txt");
        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string trainName;
            int trainNumber;
            iss >> trainName >> trainNumber;

            if (trainName == name && trainNumber == number) {
                trainExists = true;
                break;
            }
        }

        file.close();

        if (trainExists) {
            cout << "Train already exists!" << endl;
            i--; // Decrement i to ask the user to enter the same train again
        }
        else {
            myclass.push_back(tr);
        }

        cout << endl;
    }

    ofstream file("trains.txt", ios_base::app);

    for (int i = 0; i < myclass.size(); i++)
    {
        file << myclass[i].getName() << ' ' << myclass[i].getNumber() << endl;
    }

    file.close();
}

void readTrainFromFile(vector<Trains>& trains, string filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        string name;
        int number;
        stringstream ss(line);
        ss >> name >> number;

        Trains train(name, number);
        trains.push_back(train);
    }

    file.close();
}

void writeTripToFile(vector<Trains>& trips, string filename) {
    ofstream file(filename);


    for (int i = 0; i < trips.size(); i++) {
        file << trips[i].getYear() << ' ' << trips[i].getMonth() << ' ' << trips[i].getDay() << ' ' << trips[i].getBoard() << ' ' << trips[i].getDest()
            << ' ' << trips[i].getNumber() << ' ' << trips[i].getSeats() << ' ' << trips[i].getFare() << endl;
    }

    file.close();
}

void readTripFromFile(vector<Trains>& tripsArray, string filename)
{

    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        string dest, board;
        int trainNumber, fare, seats, year, month, day;
        vector<string> Splitted = SplitTrain(line, ' ');
        year = stoi(Splitted[0]);
        month = stoi(Splitted[1]);
        day = stoi(Splitted[2]);
        board = Splitted[3];
        dest = Splitted[4];
        trainNumber = stoi(Splitted[5]);
        seats = stoi(Splitted[6]);
        fare = stoi(Splitted[7]);
        Trains trip(year, month, day, dest, board, trainNumber, fare, seats);
        tripsArray.push_back(trip);

    }
    file.close();
}

void deleteTrainFromVector() {
    bool isRepeat = true;

    do {
        vector<Trains> trips;
        vector<Trains> trains;
        readTrainFromFile(trains, "trains.txt");
        readTripFromFile(trips, "trips.txt");

        int number;
        int trainDeleted = 1;

        cout << "Enter train number: ";
        cin >> number;

        bool trainFound = false;

        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].getNumber() == number) {
                trains.erase(trains.begin() + i);
                trainDeleted = number;
                i--;
                trainFound = true;
            }
        }

        if (!trainFound) {
            cout << "This train does not exist!" << endl;
            continue;
        }

        writeTrainToFile(trains, "trains.txt");

        for (int i = 0; i < trips.size(); i++) {
            if (trips[i].getNumber() == trainDeleted) {
                trips.erase(trips.begin() + i);
                i--;
            }
        }

        writeTripToFile(trips, "trips.txt");

        cout << "Do you want to delete another train? (y/n): ";
        string repeat;
        cin >> repeat;

        if (repeat != "y" && repeat != "yes" && repeat != "YES" && repeat != "Y" && repeat != "YS" && repeat != "ys") {
            isRepeat = false;
        }

    } while (isRepeat);
}

void displayTrains() {
    vector<Trains> trains;
    readTrainFromFile(trains, "trains.txt");

    for (int i = 0; i < trains.size(); i++) {
        cout << "Train " << i + 1 << " name: " << trains[i].getName() << " number: " << trains[i].getNumber() << endl;
    }
}
