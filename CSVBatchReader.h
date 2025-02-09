#ifndef CSVBATCHREADER_H
#define CSVBATCHREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "ActorMovieDatabase_Tree.h"
#include "ActorMovieDatabase.h"

using namespace std;

// Function to trim leading and trailing spaces
string trimWhitespace(const string& str);

// Function to correctly extract CSV fields with quotes
string extractQuotes(istringstream& ss);

// Function to read the entire file into a string for batch processing
string readFileIntoString(const string& filename);

// Function to read all CSV files into the database
bool readBatchCSV(ActorMovieDatabase_Tree& db);

#endif