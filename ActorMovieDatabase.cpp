#include "ActorMovieDatabase.h"
#include <iostream>

/**
 * Add a new actor to the database.
 * Process: Inserts the actor's name and birth year into the actors map.
 * Precondition: The actor's name and birth year must be valid.
 * Postcondition: A new actor is added to the database, or a message is displayed if the actor already exists.
 */
void ActorMovieDatabase::addActor(string name, int birthYear) {
    if (!actors.contains(name)) {
        actors.insert(name, new Actor(name, birthYear));
    }
    else {
        cout << "Actor already exists.\n";
    }
}

/**
 * Add a new movie to the database.
 * Process: Inserts the movie's title, plot, and release year into the movies map.
 * Precondition: The movie's title, plot, and release year must be valid.
 * Postcondition: A new movie is added to the database, or a message is displayed if the movie already exists.
 */
void ActorMovieDatabase::addMovie(string title, string plot, int releaseYear) {
    if (!movies.contains(title)) {
        movies.insert(title, new Movie(title, plot, releaseYear));
    }
    else {
        cout << "Movie already exists.\n";
    }
}

/**
 * Associate an actor with a movie.
 * Process: Links an actor to a movie and vice versa.
 * Precondition: Both the actor and movie must exist in the database.
 * Postcondition: The actor is added to the movie's actor list, and the movie is added to the actor's movie list.
 */
void ActorMovieDatabase::addActorToMovie(string actorName, string movieTitle) {
    if (actors.contains(actorName) && movies.contains(movieTitle)) {
        actors.get(actorName)->movies.add(movieTitle);
        movies.get(movieTitle)->actors.add(actorName);
    }
    else {
        cout << "Actor or movie not found.\n";
    }
}

/**
 * Display actors by age range.
 * Process: Filters and displays actors whose ages fall within a specified range.
 * Precondition: The current year and the age range must be valid.
 * Postcondition: A sorted list of actors within the age range is displayed.
 */
void ActorMovieDatabase::displayActorsByAge(int minAge, int maxAge, int currentYear) {
    List<Actor*> filteredActors;
    for (auto it = actors.begin(); it != actors.end(); ++it) {
        int age = currentYear - (*it)->value->birthYear;
        if (age >= minAge && age <= maxAge) {
            filteredActors.add((*it)->value);
        }
    }
    filteredActors.sort([](Actor* const& a, Actor* const& b) { return a->birthYear > b->birthYear; });
    for (auto it = filteredActors.begin(); it != filteredActors.end(); ++it) {
        cout << (*it)->name << " (Age: " << (currentYear - (*it)->birthYear) << ")\n";
    }
}

/**
 * Display recent movies.
 * Process: Filters and displays movies released within the last specified number of years.
 * Precondition: The current year and the number of years must be valid.
 * Postcondition: A sorted list of recent movies is displayed.
 */
void ActorMovieDatabase::displayRecentMovies(int years, int currentYear) {
    List<Movie*> recentMovies;
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        if (currentYear - (*it)->value->releaseYear <= years) {
            recentMovies.add((*it)->value);
        }
    }
    recentMovies.sort([](Movie* const& a, Movie* const& b) { return a->releaseYear < b->releaseYear; });
    for (auto it = recentMovies.begin(); it != recentMovies.end(); ++it) {
        cout << (*it)->title << " (" << (*it)->releaseYear << ")\n";
    }
}

/**
 * Display all movies associated with an actor.
 * Process: Lists all movies that the specified actor has appeared in.
 * Precondition: The actor must exist in the database.
 * Postcondition: A sorted list of the actor's movies is displayed, or a message is displayed if the actor is not found.
 */
void ActorMovieDatabase::displayMoviesByActor(string actorName) {
    if (actors.contains(actorName)) {
        List<string> actorMovies = actors.get(actorName)->movies;
        actorMovies.sort(); // Default sorting with '<'
        for (auto it = actorMovies.begin(); it != actorMovies.end(); ++it) {
            cout << *it << endl;
        }
    }
    else {
        cout << "Actor not found.\n";
    }
}

/**
 * Display all actors associated with a movie.
 * Process: Lists all actors who appeared in the specified movie.
 * Precondition: The movie must exist in the database.
 * Postcondition: A sorted list of actors in the movie is displayed, or a message is displayed if the movie is not found.
 */
void ActorMovieDatabase::displayActorsByMovie(string movieTitle) {
    if (movies.contains(movieTitle)) {
        List<string> movieActors = movies.get(movieTitle)->actors;
        movieActors.sort(); // Default sorting with '<'
        for (auto it = movieActors.begin(); it != movieActors.end(); ++it) {
            cout << *it << endl;
        }
    }
    else {
        cout << "Movie not found.\n";
    }
}

/**
 * Destructor
 * Process: Cleans up all dynamically allocated resources.
 * Precondition: None.
 * Postcondition: All memory associated with actors and movies is released.
 */
ActorMovieDatabase::~ActorMovieDatabase() {
    for (auto it = actors.begin(); it != actors.end(); ++it) {
        delete it->value;
    }
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        delete it->value;
    }
}