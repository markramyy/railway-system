#pragma once
#include<iostream>
#include <vector>


using namespace std;
class Trains {
private:
    string name;
    string dest;
    string board;
    int number;
    int year;
    int month;
    int day;
    int fare;
    int seats;
public:
    //constructors
    Trains(int, int, int, string, string, int, int, int);
    Trains(string, int);


    //setters
    void setName(string);
    void setMonth(int);
    void setYear(int);
    void setDay(int);
    void setDest(string);
    void setBoard(string);
    void setFare(int);
    void setSeats(int);
    void setNumber(int);


    //getters
    int getYear();
    int getMonth();
    int getDay();
    int getFare();
    int getSeats();
    int getNumber();
    string getName();
    string getDest();
    string getBoard();


};

//Functions
void writeTrainToFile(vector<Trains>& trains, string filename);
void fillTrain();
void readTrainFromFile(vector<Trains>& trains, string filename);


vector<string> SplitTrain(string str, char seperator);


void readTripFromFile(vector<Trains>& tripsArray, string filename);
void writeTripToFile(vector<Trains>& trips, string filename);
void deleteTrainFromVector();
void displayTrains();
