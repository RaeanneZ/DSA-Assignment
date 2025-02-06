/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include <iostream>
#include <string>
#include "ActorMovieDatabase.h"
#include "CSVReader.h"

using namespace std;

// Function to clear input buffer and handle invalid inputs
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            break;
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
