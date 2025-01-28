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
#include <limits>
#include "ActorMovieDatabase.h"
using namespace std;

// Function to clear input buffer and handle invalid inputs
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads all CSV files into the database
bool readAllCSV(ActorMovieDatabase& db) {
    Map<string, string> actorIdToName;   // Maps actor ID to actor name
    Map<string, string> movieIdToTitle; // Maps movie ID to movie title

    // Reading actors.csv
    ifstream actorsFile("actors.csv");
    if (!actorsFile.is_open()) {
        cerr << "Error: Could not open actors.csv\n";
        return false;
    }

    string line;
    getline(actorsFile, line); // Skip the header

    while (getline(actorsFile, line)) {
        istringstream ss(line);
        string id, name, birth;

        getline(ss, id, ',');
        getline(ss, name, ',');
        if (name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.size() - 2); // Remove quotes
        }
        getline(ss, birth, ',');

        try {
            db.addActor(name, stoi(birth));
        }
        catch (const exception& e) {
            cerr << "Error adding actor: " << e.what() << endl;
            continue;
        }

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
        if (title.front() == '"' && title.back() == '"') {
            title = title.substr(1, title.size() - 2); // Remove quotes
        }
        getline(ss, year, ',');

        try {
            db.addMovie(title, "", stoi(year));
        }
        catch (const exception& e) {
            cerr << "Error adding movie: " << e.what() << endl;
            continue;
        }

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

            try {
                db.associateActorWithMovie(actorName, movieTitle);
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

    cout << "\nFinished reading all CSV files.\n";
    return true;
}

// Admin menu with validation and improvements
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

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }

        string name, title, plot, modifiedName;
        int year, modifiedYear;
        switch (choice) {
        case 1:
            cout << "Enter actor name: ";
            clearInput();
            getline(cin, name);
            cout << "Enter actor birth year: ";
            cin >> year;
            db.addActor(name, year);
            cout << "Actor added successfully." << endl;
            break;
        case 2:
            cout << "Enter movie title: ";
            clearInput();
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
            clearInput();
            getline(cin, name);
            cout << "Enter movie title: ";
            getline(cin, title);
            db.associateActorWithMovie(name, title);
            cout << "Actor and movie associated successfully." << endl;
            break;
        case 4:
            db.displayActors();
            cout << "Please enter the actor name you would like to modify: ";
            clearInput();
            getline(cin, name);

            cout << "Please enter new name (Press Enter to skip): ";
            getline(cin, modifiedName);

            cout << "Please enter new birth year (Press 0 to skip): ";
            cin >> modifiedYear;
            clearInput(); // Clear buffer after numeric input

            db.updateActorDetails(name, modifiedName.empty() ? name : modifiedName, modifiedYear);
            cout << "Actor details updated successfully.\n";
            break;
        case 5:
            db.displayMovies();
            cout << "Please enter the movie title you would like to modify: ";
            clearInput();
            getline(cin, title);

            cout << "Please enter new title (Press Enter to skip): ";
            getline(cin, modifiedName);

            cout << "Please enter new release year (Press 0 to skip): ";
            cin >> modifiedYear;
            db.updateMovieDetails(title, modifiedName.empty() ? title : modifiedName, modifiedYear);
            cout << "Movie details updated successfully.\n";
            break;
        case 0:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// User menu with validation and improvements
void userMenu(ActorMovieDatabase& db) {
    int choice;
    do {
        cout << "\n=== User Menu ===" << endl;
        cout << "1. Display All Actors Between Ages" << endl;
        cout << "2. Display All Movies Within Past 3 Years" << endl;
        cout << "3. Display All Movies Actor Starred In" << endl;
        cout << "4. Display All Actors In Movie" << endl;
        cout << "5. Display Known Actors for Chosen Actor" << endl;
        cout << "6. Explore Connections (Graph)" << endl;
        cout << "7. Get Movie Recommendations" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }

        string name, node;
        switch (choice) {
        case 1:
            int minAge, maxAge;
            cout << "Enter minimum age: ";
            cin >> minAge;
            cout << "Enter maximum age: ";
            cin >> maxAge;
            db.displayActorsByAgeRange(minAge, maxAge);
            break;
        case 2:
            db.displayRecentMovies();
            break;
        case 3:
            db.displayActors();
            cout << "Enter actor name: ";
            clearInput();
            getline(cin, name);
            db.displayMoviesForActor(name);
            break;
        case 4:
            db.displayMovies();
            cout << "Enter movie title: ";
            clearInput();
            getline(cin, name);
            db.displayActorsInMovie(name);
            break;
        case 5:
            cout << "Enter actor name: ";
            clearInput();
            getline(cin, name);
            db.displayKnownActors(name);
            break;
        case 6:
            cout << "Enter an actor or movie to explore: ";
            clearInput();
            getline(cin, node);
            db.exploreConnections(node);
            break;
        case 7:
            cout << "Enter actor name for recommendations: ";
            clearInput();
            getline(cin, name);
            db.recommendMovies(name);
            break;
        case 0:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}


// Main function
int main() {
    ActorMovieDatabase db;
    int roleChoice;

    if (!readAllCSV(db)) {
        cerr << "Error loading CSV files. Exiting program.\n";
        return 1;
    }

    db.buildGraph(); // Build graph for advanced feature

    do {
        cout << "\n=== Welcome to the Actor-Movie Database ===" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as User" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> roleChoice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }

        switch (roleChoice) {
        case 1:
            adminMenu(db);
            break;
        case 2:
            userMenu(db);
            break;
        case 0:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (roleChoice != 0);

    return 0;
}
