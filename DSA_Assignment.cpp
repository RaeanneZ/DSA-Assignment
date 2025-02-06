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
#include <filesystem> // C++17
#include <algorithm> // For std::remove_if
#include <direct.h>  // Windows-specific (For _getcwd)
#define GetCurrentDir _getcwd
#include "ActorMovieDatabase.h"

using namespace std;
namespace fs = filesystem;

// Function to clear input buffer and handle invalid inputs
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Helper function to trim leading and trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}
// Helper function to correctly extract CSV fields with quotes
string extractQuotedField(istringstream& ss) {
    string field;
    if (ss.peek() == '"') {  // If field starts with a quote
        ss.get(); // Remove first quote
        getline(ss, field, '"'); // Extract until next quote
        ss.get(); // Remove the comma after closing quote
    }
    else {
        getline(ss, field, ','); // Extract normally
    }
    return trim(field);
}

// Reads all CSV files into the database with improved parsing for quotes and special characters
bool readAllCSV(ActorMovieDatabase& db) {
    Map<string, string> actorIdToName;
    Map<string, string> movieIdToTitle;

    // Read actors.csv
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

        // Extract ID
        getline(ss, id, ',');

        // Extract name (handling quotes)
        name = extractQuotedField(ss);

        // Extract birth year
        getline(ss, birth, ',');

        try {
            db.addActor(name, stoi(birth));
        }
        catch (const exception& e) {
            cerr << "Error adding actor: " << e.what() << endl;
            continue;
        }

        // Store ID-to-Name mapping
        actorIdToName.insert(id, name);
    }
    actorsFile.close();

    // Read movies.csv
    ifstream moviesFile("movies.csv");
    if (!moviesFile.is_open()) {
        cerr << "Error: Could not open movies.csv\n";
        return false;
    }

    getline(moviesFile, line); // Skip the header
    while (getline(moviesFile, line)) {
        istringstream ss(line);
        string id, title, plot, year;

        // Extract fields correctly
        getline(ss, id, ',');       // Read Movie ID
        title = extractQuotedField(ss);  // Read Title (handles commas)
        plot = extractQuotedField(ss);   // Read Plot
        getline(ss, year, ',');      // Read Year
        year = trim(year);

        if (year.empty() || !isdigit(year[0])) {
            cerr << "Error: Invalid year for movie '" << title << "' | Raw input: " << year << "\n";
            continue;
        }

        try {
            db.addMovie(title, plot, stoi(year));
        }
        catch (const exception& e) {
            cerr << "Error adding movie: " << e.what() << " | Raw input: " << year << "\n";
            continue;
        }

        // Store ID-to-Title mapping
        movieIdToTitle.insert(id, title);
    }
    moviesFile.close();

    cout << "Finished reading movies.csv successfully.\n";

    // Read cast.csv
    ifstream castFile("cast.csv");
    if (!castFile.is_open()) {
        cerr << "Error: Could not open cast.csv\n";
        return false;
    }

    getline(castFile, line); // Skip the header
    while (getline(castFile, line)) {
        istringstream ss(line);
        string person_id, movie_id;
        getline(ss, person_id, ',');
        getline(ss, movie_id, ',');

        // Ensure both IDs are mapped correctly
        if (!actorIdToName.contains(person_id) || !movieIdToTitle.contains(movie_id)) {
            cerr << "Error: Could not resolve ID " << person_id << " or " << movie_id << "\n";
            continue;
        }

        string actorName = actorIdToName.get(person_id);
        string movieTitle = movieIdToTitle.get(movie_id);

        // Retrieve actual Actor and Movie objects
        Actor* actor = db.findActor(actorName);
        Movie* movie = db.findMovie(movieTitle);

        if (!actor || !movie) {
            cerr << "Error: Actor or Movie not found in database for association.\n";
            continue;
        }

        // Associate actor with movie
        actor->addMovieToActor(movie);
        movie->addActorToMovie(actor);
    }
    castFile.close();

    cout << "\nFinished reading all CSV files and associating actors with movies.\n";
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
void userMenu(ActorMovieDatabase& db, const string& username) {
    int choice;
    do {
        cout << "\n=== User Menu ===" << endl;
        cout << "1. Display All Actors Between Ages" << endl;
        cout << "2. Display All Movies Within Past 3 Years" << endl;
        cout << "3. Display All Movies Actor Starred In" << endl;
        cout << "4. Display All Actors In Movie" << endl;
        cout << "5. Display Known Actors for Chosen Actor" << endl;
        cout << "6. Advanced Feature: Explore Connections" << endl;
        cout << "7. Get Movie Recommendations By Actor" << endl;
        cout << "8. Rate Movies" << endl;
        cout << "9. Add a Watched Movie" << endl;
        cout << "10. Get Personalised Movie Recommendations" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }

        string name, node;
        int rating;
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
            db.displayMovies();
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
            //db.exploreConnections(node);
            cout << "\n" << endl;

            if (db.getGraph().getConnections(node)) { // Check if the node exists
                db.displayMindMap(node);
            }
            else {
                cout << "Node \"" << node << "\" does not exist in the graph.\n";
            }
            break;
        case 7:
            cout << "Enter actor name for recommendations: ";
            clearInput();
            getline(cin, name);
            db.recommendMovies(name);
            break;
        case 8:
            cout << "Enter movie title: ";
            clearInput();
            getline(cin, name);
            cout << "Enter rating (1-5): ";
            cin >> rating;
            db.rateMovie(username, name, rating);
            break;
        case 9:
            cout << "Enter movie title you have watched: ";
            clearInput();
            getline(cin, name);
            db.addWatchedMovie(username, name);
            cout << "Movie added to watched list.\n";
        case 10:
            db.recommendPersonalisedMovies(username);
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

        string username;
        switch (roleChoice) {
        case 1:
            adminMenu(db);
            break;
        case 2:
            cout << "Enter your username: ";
            cin >> username;
            db.addUser(username);
            userMenu(db, username);
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
