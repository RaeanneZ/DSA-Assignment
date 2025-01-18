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
 * Display actors within a specified age range
 * Process: Iterates through actorMap, add actors within age range to a list, sorts the list and displays it
 * Precondition: `x` and `y` must be valid integers where `x <= y` and actorMap must be populated with valid data, including each actor's birth year.
 * Postcondition: Outputs all actors within the specified age range in ascending order of age.
 */
void ActorMovieDatabase::displayActorsByAgeRange(int x, int y) const {
    int currentYear = std::time(nullptr) / (60 * 60 * 24 * 365.25) + 1970; // Approximate current year

    List<Actor*> actorsInRange;
    auto it = actorMap.createIterator();
    while (it->hasNext()) {
        Actor* actor = it->next()->value;
        int age = currentYear - actor->getBirthYear();
        if (age >= x && age <= y) {
            actorsInRange.add(actor);
        }
    }
    delete it;

    // Sort actorsInRange by age
    for (auto i = actorsInRange.createIterator(); i->hasNext();) {
        Actor* a = i->next();
        for (auto j = actorsInRange.createIterator(); j->hasNext();) {
            Actor* b = j->next();
            if ((currentYear - a->getBirthYear()) < (currentYear - b->getBirthYear())) {
                swap(a, b); // Swap actors to sort in ascending order
            }
        }
    }

    // Display sorted actors
    cout << "Actors aged between " << x << " and " << y << ":\n";
    for (auto it = actorsInRange.createIterator(); it->hasNext();) {
        Actor* actor = it->next();
        cout << actor->getName() << " (Age: " << currentYear - actor->getBirthYear() << ")\n";
    }
}

/**
 * Display Known Actors
 * Process: Find actor specificed, iterates through all movies in the database to check if the actor starred in them and identifies 
            all actors that are directly or indirectly connected (one level deep) to the given actor. It then displays all actors 
            that the given actor knows.
 * Precondition: `actorName` must be a valid string representing the name of an actor,`actorMap` and `movieMap` must be populated with 
                  valid data.
 * Postcondition: Outputs all actors that are directly or indirectly connected (one movie level deep) to the given actor.
 */
void ActorMovieDatabase::displayKnownActors(const string& actorName) const {
    Actor* targetActor = findActor(actorName);
    if (!targetActor) {
        cout << "Actor not found.\n";
        return;
    }

    List<Actor*> knownActors; // List to store known actors

    // Traverse all movies
    auto movieIterator = movieMap.createIterator();
    while (movieIterator->hasNext()) {
        Movie* movie = movieIterator->next()->value;

        // Check if the targetActor starred in this movie
        auto actorIterator = movie->getActors().createIterator();
        bool targetInMovie = false;
        while (actorIterator->hasNext()) {
            if (actorIterator->next() == targetActor) {
                targetInMovie = true;
                break;
            }
        }
        delete actorIterator;

        // If targetActor starred in this movie, add other actors to knownActors
        if (targetInMovie) {
            auto coActorIterator = movie->getActors().createIterator();
            while (coActorIterator->hasNext()) {
                Actor* coActor = coActorIterator->next();
                if (coActor != targetActor) {
                    // Check for duplicates in knownActors
                    bool isDuplicate = false;
                    auto knownIt = knownActors.createIterator();
                    while (knownIt->hasNext()) {
                        if (knownIt->next() == coActor) {
                            isDuplicate = true;
                            break;
                        }
                    }
                    delete knownIt;

                    if (!isDuplicate) {
                        knownActors.add(coActor);
                    }
                }
            }
            delete coActorIterator;
        }
    }
    delete movieIterator;

    // Display known actors
    cout << "Actors known by " << actorName << ":\n";
    auto knownIt = knownActors.createIterator();
    while (knownIt->hasNext()) {
        Actor* actor = knownIt->next();
        cout << actor->getName() << "\n";
    }
    delete knownIt;
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

