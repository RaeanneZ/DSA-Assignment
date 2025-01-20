/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "ActorMovieDatabase.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Constructor
 * Initializes the ActorMovieDatabase.
 * Precondition: None.
 * Postcondition: A new database is created with no actors or movies.
 */
ActorMovieDatabase::ActorMovieDatabase() {}

/**
 * Destructor
 * Frees all dynamically allocated memory.
 * Precondition: None.
 * Postcondition: All actor and movie objects are deleted, and the database is cleared.
 */
ActorMovieDatabase::~ActorMovieDatabase() {
    clearDatabase();
}

/**
 * Add an actor to the database.
 * Process: Creates a new Actor object and adds it to the actorMap.
 * Precondition: The actor's name and birth year must be provided.
 * Postcondition: A new Actor is added to the database, or existing Actor is updated if already present.
 */
void ActorMovieDatabase::addActor(const string& name, int birthYear) {
    if (!actorMap.contains(name)) {
        actorMap.insert(name, new Actor(name, birthYear));
    }
}


/**
 * Add a movie to the database.
 * Process: Creates a new Movie object and adds it to the movieMap.
 * Precondition: The movie's title, plot, and release year must be provided.
 * Postcondition: A new Movie is added to the database, or existing Movie is updated if already present.
 */
void ActorMovieDatabase::addMovie(const string& title, const string& plot, int releaseYear) {
    if (!movieMap.contains(title)) {
        movieMap.insert(title, new Movie(title, plot, releaseYear));
    }
}


/**
 * Associate an actor with a movie.
 * Process: Finds the actor and movie in the database and links them.
 * Precondition: Both the actor and movie must already exist in the database.
 * Postcondition: The actor is added to the movie's actor list, and the movie is added to the actor's movie list.
 */
void ActorMovieDatabase::associateActorWithMovie(const string& actorName, const string& movieTitle) {
    Actor* actor = findActor(actorName);
    Movie* movie = findMovie(movieTitle);
    if (actor && movie) {
        actor->addMovieToActor(movie);
        movie->addActorToMovie(actor);
    }
}


/**
 * Find an actor by name.
 * Process: Searches for the actor in the actorMap.
 * Precondition: The actor's name must be provided.
 * Postcondition: Returns a pointer to the Actor if found, or nullptr otherwise.
 */
Actor* ActorMovieDatabase::findActor(const string& name) const {
    return actorMap.contains(name) ? actorMap.get(name) : nullptr;
}


/**
 * Find a movie by title.
 * Process: Searches for the movie in the movieMap.
 * Precondition: The movie's title must be provided.
 * Postcondition: Returns a pointer to the Movie if found, or nullptr otherwise.
 */
Movie* ActorMovieDatabase::findMovie(const string& title) const {
    return movieMap.contains(title) ? movieMap.get(title) : nullptr;
}


/**
 * Display all actors in the database.
 * Process: Iterates through the actorMap and prints actor details.
 * Precondition: None.
 * Postcondition: All actor details are printed to the console.
 */
void ActorMovieDatabase::displayActors() const {
    auto it = actorMap.createIterator();
    while (it->hasNext()) {
        Actor* actor = it->next()->value;
        cout << "Actor: " << actor->getName() << endl;
    }
    delete it;
}

/**
 * Update actor details
 * Process: Iterates through the actorMap and get actor details.
 * Precondition: Actor name.
 * Postcondition: All actor details are updated.
 */
void ActorMovieDatabase::updateActorDetails(const string& actorName) {
    Actor* actor = findActor(actorName);
    if (actor == nullptr) {
        cout << "Actor not found." << endl;
        return;
    }

    cout << "Updating details for: " << actor->getName() << endl;

    string newName;
    cout << "Enter new name (or press Enter to keep current: " << actor->getName() << "): ";
    getline(cin, newName);
    if (!newName.empty()) {
        actor->setName(newName);
    }

    int newBirthYear;
    cout << "Enter new birth year (or press 0 to keep current: " << actor->getBirthYear() << "): ";
    cin >> newBirthYear;
    if (newBirthYear > 0) {
        actor->setBirthYear(newBirthYear);
    }

    cout << "Actor details updated successfully!" << endl;
}

/**
 * Update movie details
 * Process: Iterates through the movieMap and get movie details.
 * Precondition: Movie title
 * Postcondition: All movie details are updated.
 */
void ActorMovieDatabase::updateMovieDetails(const string& movieTitle) {
    Movie* movie = findMovie(movieTitle);
    if (movie == nullptr) {
        cout << "Movie not found." << endl;
        return;
    }

    cout << "Updating details for: " << movie->getTitle() << endl;

    string newTitle;
    cout << "Enter new title (or press Enter to keep current: " << movie->getTitle() << "): ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newTitle);
    if (!newTitle.empty()) {
        movie->setTitle(newTitle);
    }

    string newPlot;
    cout << "Enter new plot (or press Enter to keep current): ";
    getline(cin, newPlot);
    if (!newPlot.empty()) {
        movie->setPlot(newPlot);
    }

    int newReleaseYear;
    cout << "Enter new release year (or press 0 to keep current: " << movie->getReleaseYear() << "): ";
    cin >> newReleaseYear;
    if (newReleaseYear > 0) {
        movie->setReleaseYear(newReleaseYear);
    }

    cout << "Movie details updated successfully!" << endl;
}


/**
 * Display all movies in the database.
 * Process: Iterates through the movieMap and prints movie details.
 * Precondition: None.
 * Postcondition: All movie details are printed to the console.
 */
void ActorMovieDatabase::displayMovies() const {
    auto it = movieMap.createIterator();
    while (it->hasNext()) {
        Movie* movie = it->next()->value;
        cout << "Movie: " << movie->getTitle() << endl;
    }
    delete it;
}

/**
 * Display movies made within the past 3 years (in ascending order of year) 
 * Process: Iterates through the movieMap and prints actor details.
 * Precondition: None.
 * Postcondition: Movie name and release year are printed to the console.
 */
void ActorMovieDatabase::displayMoviesInPast3Years() {

    // Approximate current year
    int currentYear = time(nullptr) / (60 * 60 * 24 * 365.25) + 1970;

    // Vector to store recent movies
    vector<Movie*> recentMovies;

    // Iterate through the movieMap
    auto it = movieMap.createIterator();
    while (it->hasNext()) {
        Movie* movie = it->next()->value;
        if (currentYear - movie->getReleaseYear() <= 3) {
            recentMovies.push_back(movie);
        }
    }
    delete it;

    // Sort the recent movies by release year in ascending order
    sort(recentMovies.begin(), recentMovies.end(), [](Movie* a, Movie* b) {
        return a->getReleaseYear() < b->getReleaseYear();
        });

    // Display the recent movies
    if (recentMovies.empty()) {
        cout << "No movies made within the past 3 years." << endl;
    }
    else {
        cout << "Movies made within the past 3 years (in ascending order of year):\n";
        for (const auto& movie : recentMovies) {
            cout << movie->getTitle() << " (" << movie->getReleaseYear() << ")" << endl;
        }
    }
}

/**
 * Display all movies an actor starred in (in alphabetical order)
 * Process: Searches for the actor in the actorMap and sorts all the movies the actor starred in.
 * Precondition: Actor name.
 * Postcondition: Movie name and release year are printed to the console.
 */
void ActorMovieDatabase::displayMoviesByActor(const string& actorName) const {

    // Find the actor in the database
    Actor* actor = findActor(actorName);
    if (!actor) {
        cout << "Actor \"" << actorName << "\" not found in the database." << endl;
        return;
    }

    // Sort the movies the actor starred in
    const_cast<Actor*>(actor)->sortMovies();

    // Display movies
    cout << "Movies featuring \"" << actorName << "\":\n";
    actor->displayMovies();
}

/**
 * Display all the actors in a particular movie (in alphabetical order)
 * Process: Find the movie and sort all actors accordingly
 * Precondition: Movie name.
 * Postcondition: Actor names are printed to the console.
 */
void ActorMovieDatabase::displayActorsByMovie(const string& movieTitle) const {
    // Find the movie in the database
    Movie* movie = findMovie(movieTitle);
    if (!movie) {
        cout << "Movie \"" << movieTitle << "\" not found in the database." << endl;
        return;
    }

    // Sort the actors in the movie
    movie->sortActors();

    // Display the actors
    cout << "Actors in \"" << movieTitle << "\":\n";
    movie->displayActors();
}

/**
 * Clear the database.
 * Process: Deletes all dynamically allocated actors and movies and clears the maps.
 * Precondition: None.
 * Postcondition: The database is empty.
 */
void ActorMovieDatabase::clearDatabase() {
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        delete actorIt->next()->value;
    }
    delete actorIt;
    actorMap.clear();

    auto movieIt = movieMap.createIterator();
    while (movieIt->hasNext()) {
        delete movieIt->next()->value;
    }
    delete movieIt;
    movieMap.clear();
}

