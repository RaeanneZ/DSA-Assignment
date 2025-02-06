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