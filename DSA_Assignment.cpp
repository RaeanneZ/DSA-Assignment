/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include <iostream>
#include <string>
#include <limits>
#include "ActorMovieDatabase.h"
#include "ActorMovieDatabase_Tree.h"
#include "CSVReader.h"
#include "CSVBatchReader.h"

using namespace std;

/**
 * Gets a valid integer input from the user.
 * Process: Repeatedly prompts the user until a valid integer is entered.
 * Precondition: The input must be an integer.
 * Postcondition: Returns a valid integer input.
 */
int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer only after a valid integer input
            break;
        }
    }
    return value;
}


/**
 * Gets a valid string input from the user.
 * Process: Prompts the user for input and ensures it is not empty.
 * Precondition: None.
 * Postcondition: Returns a valid non-empty string.
 */
string getValidStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);

    while (value.empty()) {
        cout << "Input cannot be empty. Please try again: ";
        getline(cin, value);
    }
    return value;
}


/**
 * Displays the admin menu and handles administrative operations.
 * Process: Allows the admin to add actors, add movies, update details, and associate actors with movies.
 * Precondition: The `db` object must be initialized and contain valid movie and actor data.
 * Postcondition: The database is updated based on the admin's choices.
 */
void adminMenu(ActorMovieDatabase_Tree& db) {
    int choice;
    do {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Add New Actor" << endl;
        cout << "2. Add New Movie" << endl;
        cout << "3. Add Actor to Movie" << endl;
        cout << "4. Update Actor Details" << endl;
        cout << "5. Update Movie Details" << endl;
        cout << "0. Logout" << endl;
        choice = getValidIntInput("Enter your choice: ");

        string name, title, plot, modifiedName;
        int year, modifiedYear;
        switch (choice) {
        case 1:
            name = getValidStringInput("Enter actor name: ");
            year = getValidIntInput("Enter actor birth year: ");
            db.addActor(name, year);
            cout << "Actor added successfully." << endl;
            break;
        case 2:
            title = getValidStringInput("Enter movie title: ");
            plot = getValidStringInput("Enter movie plot: ");
            year = getValidIntInput("Enter movie release year: ");
            db.addMovie(title, plot, year);
            cout << "Movie added successfully." << endl;
            break;
        case 3:
            name = getValidStringInput("Enter actor name: ");
            title = getValidStringInput("Enter movie title: ");
            db.associateActorWithMovie(name, title);
            cout << "Actor and movie associated successfully." << endl;
            break;
        case 4:
            db.displayActors();
            name = getValidStringInput("Please enter the actor name you would like to modify: ");
            modifiedName = getValidStringInput("Please enter new name (Press Enter to skip): ");
            modifiedYear = getValidIntInput("Please enter new birth year (Press 0 to skip): ");
            db.updateActorDetails(name, modifiedName.empty() ? name : modifiedName, modifiedYear);
            cout << "Actor details updated successfully.\n";
            break;
        case 5:
            db.displayMovies();
            title = getValidStringInput("Please enter the movie title you would like to modify: ");
            modifiedName = getValidStringInput("Please enter new title (Press Enter to skip): ");
            modifiedYear = getValidIntInput("Please enter new release year (Press 0 to skip): ");
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


/**
 * Displays the user menu and handles user interactions.
 * Process: Allows users to explore actors, movies, connections, and get recommendations.
 * Precondition: The `db` object must be initialized, and the user must be logged in.
 * Postcondition: Displays requested information or updates user-specific data.
 */
void userMenu(ActorMovieDatabase_Tree& db, const string& username) {
    int choice;
    do {
        cout << "\n=== User Menu ===" << endl;
        cout << "1. Display All Actors Between Ages" << endl;
        cout << "2. Display All Movies Within Past 3 Years" << endl;
        cout << "3. Display All Movies Actor Starred In" << endl;
        cout << "4. Display All Actors In Movie" << endl;
        cout << "5. Display Known Actors for Chosen Actor" << endl;
        cout << "6. Explore Actor/Movie Connections" << endl;
        cout << "7. Get Movie Recommendations By Actor" << endl;
        cout << "8. Find Most Influential Actor" << endl;
        cout << "9. Rate Movies" << endl;
        cout << "10. Add a Watched Movie" << endl;
        cout << "11. Get Personalized Movie Recommendations" << endl;
        cout << "0. Logout" << endl;
        choice = getValidIntInput("Enter your choice: ");

        string name;
        int minAge, maxAge;
        switch (choice) {
        case 1:
            minAge = getValidIntInput("Enter minimum age: ");
            maxAge = getValidIntInput("Enter maximum age: ");
            db.displayActorsByAgeRange(minAge, maxAge);
            break;
        case 2:
            db.displayRecentMovies();
            break;
        case 3:
            name = getValidStringInput("Enter actor name: ");
            db.displayMoviesForActor(name);
            break;
        case 4:
            name = getValidStringInput("Enter movie title: ");
            db.displayActorsInMovie(name);
            break;
        case 5:
            db.displayKnownActors(getValidStringInput("Enter actor name: "));
            break;
        case 6:
            db.displayMindMap(getValidStringInput("Enter an actor or movie to explore by graph: "));
            break;
        case 7:
            db.recommendMovies(getValidStringInput("Enter actor name for recommendations: "));
            break;
        case 8:
            db.displayMostInfluentialActor();
            break;
        case 9:
            db.rateMovie(username, getValidStringInput("Enter movie title: "), getValidIntInput("Enter rating (1-5): "));
            break;
        case 10:
            db.addWatchedMovie(username, getValidStringInput("Enter movie title you have watched: "));
            break;
        case 11:
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


/**
 * Main function - Entry point of the program.
 * Process: Loads CSV data, initializes the graph, and provides a menu for Admin or User login.
 * Precondition: CSV files must be present for batch processing.
 * Postcondition: Runs the application until the user exits.
 */
int main() {
    ActorMovieDatabase_Tree db;
    int roleChoice;

    if (!readBatchCSV(db)) {
        cerr << "Error loading CSV files. Exiting program.\n";
        return 1;
    }

    db.buildGraph();
  
    do {
        cout << "\n=== Welcome to the Actor-Movie Database ===" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as User" << endl;
        cout << "0. Exit" << endl;
        roleChoice = getValidIntInput("Enter your choice: ");

        string username;
        switch (roleChoice) {
        case 1:
            adminMenu(db);
            break;
        case 2:
            username = getValidStringInput("Enter your username: ");
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
