#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

CSVReader::CSVReader(ActorMovieDatabase& db) : database(db) {}

void CSVReader::readActorsCSV() {
    ifstream actorsFile("actors.csv");
    if (!actorsFile.is_open()) {
        cerr << "Error: Could not open actors.csv\n";
        return;
    }

    string line, id, name, birth;
    getline(actorsFile, line); // Skip the header

    while (getline(actorsFile, line)) {
        istringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, birth, ',');

        if (name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.size() - 2); // Remove quotes
        }

        try {
            int birthYear = stoi(birth);
            database.addActor(name, birthYear);
            actorIdToName.insert(id, name);
        }
        catch (const exception& e) {
            cerr << "Error adding actor: " << e.what() << endl;
        }
    }
    actorsFile.close();
}

void CSVReader::readMoviesCSV() {
    ifstream moviesFile("movies.csv");
    if (!moviesFile.is_open()) {
        cerr << "Error: Could not open movies.csv\n";
        return;
    }

    string line, id, title, year;
    getline(moviesFile, line); // Skip the header

    while (getline(moviesFile, line)) {
        istringstream ss(line);
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, year, ',');

        if (title.front() == '"' && title.back() == '"') {
            title = title.substr(1, title.size() - 2); // Remove quotes
        }

        try {
            int releaseYear = stoi(year);
            database.addMovie(title, "", releaseYear);
            movieIdToTitle.insert(id, title);
        }
        catch (const exception& e) {
            cerr << "Error adding movie: " << e.what() << endl;
        }
    }
    moviesFile.close();
}

void CSVReader::readCastCSV() {
    ifstream castFile("cast.csv");
    if (!castFile.is_open()) {
        cerr << "Error: Could not open cast.csv\n";
        return;
    }

    string line, person_id, movie_id;
    getline(castFile, line); // Skip header

    while (getline(castFile, line)) {
        istringstream ss(line);
        getline(ss, person_id, ',');
        getline(ss, movie_id, ',');

        if (actorIdToName.contains(person_id) && movieIdToTitle.contains(movie_id)) {
            string actorName = actorIdToName.get(person_id);
            string movieTitle = movieIdToTitle.get(movie_id);

            try {
                database.associateActorWithMovie(actorName, movieTitle);
            }
            catch (const exception& e) {
                cerr << "Error associating actor and movie: " << e.what() << endl;
            }
        }
        else {
            cerr << "Error: Could not resolve ID " << person_id << " or " << movie_id << "\n";
        }
    }
    castFile.close();
}

bool CSVReader::loadCSVData() {
    readActorsCSV();
    readMoviesCSV();
    readCastCSV();
    return true;
}