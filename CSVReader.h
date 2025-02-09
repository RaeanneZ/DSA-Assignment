/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/


#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "ActorMovieDatabase.h"

using namespace std;

// Function to trim leading and trailing spaces
string trim(const string& str);

// Function to correctly extract CSV fields with quotes
string extractQuotedField(istringstream& ss);

// Function to read all CSV files into the database
bool readAllCSV(ActorMovieDatabase& db);


#endif // CSVREADER_H