#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

using namespace std;


struct admin {
    string name;
    string email;
    string password;
};


// Function to login an existing user
void loginadmin(const map<string, admin>& admins) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if the username exists
    auto it = admins.find(username);
    if (it == admins.end()) {
        cout << "Username not found! Please sign up first.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Check if the password is correct
    if (it->second.password == password) {
        cout << "Admin Login successful!\n";
    }
    else {
        cout << "Incorrect password! Please try again.\n";
    }
}

// Function to save the admin map to a file
void saveadminData(const map<string, admin>& admins) {
    ofstream file("admin_data.txt");
    if (file.is_open()) {
        for (const auto& admin : admins) {
            file << admin.first << " " << admin.second.email << " " << admin.second.password << "\n";
        }
        file.close();
        cout << "admin data saved to file.\n";
    }
    else {
        cout << "Unable to open file for saving admin data.\n";
    }
}

// Function to load admin data from a file
void loadadminData(map<string, admin>& admins) {
    ifstream file("admin_data.txt");
    if (file.is_open()) {
        string username, email, password;
        while (file >> username >> email >> password) {
            admin admin;
            admin.name = username;
            admin.email = email;
            admin.password = password;
            admins[username] = admin;
        }
        file.close();
        cout << "admin data loaded from file.\n";
        cout << "------------------------------------------" << endl;

    }
    else {
        cout << "No existing admin data found.\n";
    }
}

