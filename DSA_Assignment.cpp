/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include <iostream>
#include "ActorMovieDatabase.h"
using namespace std;

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

        switch (choice) {
        case 1:
            db.displayActors();
            break;
        case 2:
            db.displayMovies();
            break;
        case 3:
            /* Put Function Here */
            break;
        case 4:
            /* Put Function Here */
            break;
        case 5:
            /* Put Function Here */
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