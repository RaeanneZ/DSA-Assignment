/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ActorMovieDatabase.h"
using namespace std;

bool readAllCSV(ActorMovieDatabase& db) {

    Map<string, string> actorIdToName;   // Maps actor ID to actor name
    Map<string, string> movieIdToTitle; // Maps movie ID to movie title

    // Reading actors.csv
    ifstream actorsFile("actors.csv");
    if (!actorsFile.is_open()) {
        cerr << "Error: Could not open actors.csv\n";
        return false;
    }

    std::string line;
    getline(actorsFile, line); // Skip the header

    while (getline(actorsFile, line)) {
        istringstream ss(line);
        string id, name, birth;

        getline(ss, id, ',');
        getline(ss, name, ',');
        name = name.substr(1, name.size() - 2); // Remove quotes
        getline(ss, birth, ',');


        //DEBUG STATEMENT
        cout << "Actor Added: ID=" << id << ", Name=" << name << ", BirthYear=" << birth << endl;


        db.addActor(name, stoi(birth));

        // Insert into map
        actorIdToName.insert(id, name);
    }

    actorsFile.close();

    // Reading movies.csv
    ifstream moviesFile("movies.csv");
    if (!moviesFile.is_open()) {
        cerr << "Error: Could not open movies.csv\n";
        return false;
    }

    getline(moviesFile, line); // Skip the header

    while (getline(moviesFile, line)) {
        istringstream ss(line);
        string id, title, year;

        getline(ss, id, ',');
        getline(ss, title, ',');
        title = title.substr(1, title.size() - 2); // Remove quotes
        getline(ss, year, ',');


        //DEBUG STATEMENT
        cout << "Movie Added: ID=" << id << ", Title=" << title << ", Year=" << year << endl;

        db.addMovie(title, "", stoi(year));

        // Insert into map
        movieIdToTitle.insert(id, title);
    }

    moviesFile.close();

    // Reading cast.csv
    ifstream castFile("cast.csv");
    if (!castFile.is_open()) {
        cerr << "Error: Could not open cast.csv\n";
        return false;
    }

    string line1;
    getline(castFile, line1); // Skip header

    while (getline(castFile, line1)) {
        istringstream ss(line1);
        string person_id, movie_id;
        getline(ss, person_id, ',');
        getline(ss, movie_id, ',');

        if (actorIdToName.contains(person_id) && movieIdToTitle.contains(movie_id)) {
            string actorName = actorIdToName.get(person_id);
            string movieTitle = movieIdToTitle.get(movie_id);

            Actor* actor = db.findActor(actorName); // Validate existence
            if (!actor) {
                cerr << "Error: Actor \"" << actorName << "\" not found.\n";
                continue;
            }
            // Associate actor with movie in the database
            db.associateActorWithMovie(actorName, movieTitle);
        }
        else {
            cerr << "Error: Could not resolve ID " << person_id << " or " << movie_id << "\n";
        }
    }
    castFile.close();

    cout << "\nFinished reading all CSV files.\n";
    return true;
}


void adminMenu(ActorMovieDatabase& db) {
    int choice;
    do {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Add New Actor" << endl;
        cout << "2. Add New Movie" << endl;
        cout << "3. Add Actor to Movie" << endl;
        cout << "4. Update Actor Details" << endl;
        cout << "5. Update Movie Details" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string name, title, plot;
        int year;
        switch (choice) {
        case 1:
            cout << "Enter actor name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter actor birth year: ";
            cin >> year;
            db.addActor(name, year);
            cout << "Actor added successfully." << endl;
            break;
        case 2:
            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter movie plot: ";
            getline(cin, plot);
            cout << "Enter movie release year: ";
            cin >> year;
            db.addMovie(title, plot, year);
            cout << "Movie added successfully." << endl;
            break;
        case 3:
            cout << "Enter actor name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter movie title: ";
            getline(cin, title);
            db.associateActorWithMovie(name, title);
            cout << "Actor and movie associated successfully." << endl;
            break;
        case 4:
            /* Put Your Method Here */
            break;
        case 5:
            /* Put Your Method Here */
            break;
        case 0:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void userMenu(ActorMovieDatabase& db) {
    int choice;
    do {
        cout << "\n=== User Menu ===" << endl;
        cout << "1. Display All Actors Between Ages" << endl;
        cout << "2. Display All Movies Within Past 3 Years" << endl;
        cout << "3. Display All Movies Actor Starred In" << endl;
        cout << "4. Display All Actors In Movie" << endl;
        cout << "5. Display All Actors That Chosen Actor Knows" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string name;
        switch (choice) {
        case 1:
            int minAge, maxAge;
            cout << "Please enter minimum age: ";
            cin >> minAge;
            cout << "Please enter maximum age: ";
            cin >> maxAge;
            db.displayActorsByAgeRange(minAge, maxAge);
            break;
        case 2:
            /*db.displayMovies();*/
            break;
        case 3:
            /* Put Function Here */
            break;
        case 4:
            /* Put Function Here */
            break;
        case 5:
            /* Put Function Here */
            cout << "Enter actor name: ";
            cin.ignore();
            getline(cin, name);
            db.displayKnownActors(name);
            break;
        case 0:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}


int main()
{
    ActorMovieDatabase db;
    int roleChoice;

    readAllCSV(db);


    do {
        cout << "\n=== Welcome to the Actor-Movie Database ===" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as User" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> roleChoice;

        switch (roleChoice) {
        case 1:
            adminMenu(db);
            break;
        case 2:
            userMenu(db);
            break;
        case 0:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (roleChoice != 0);

    return 0;
}