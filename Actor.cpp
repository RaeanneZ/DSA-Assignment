/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "Actor.h"
#include <iostream>
using namespace std;

/**
 * Constructor
 * Process: Initializes an Actor object with a name and birth year.
 * Precondition: `name` must be a valid non-empty string. `birthYear` must be a positive integer.
 * Postcondition: A new Actor object is created with the given details.
 */
Actor::Actor(const string& name, int birthYear) {
    this->name = name;
    this->birthYear = birthYear;
}


/**
 * Retrieves the name of the actor.
 * Process: Returns the actor's name as a string.
 * Precondition: The Actor object must be initialized with a name.
 * Postcondition: Returns the name of the actor.
 */
string Actor::getName() const {
    return name;
}


/**
 * Updates the name of the actor.
 * Process: Assigns a new name to the actor.
 * Precondition: `name` must be a valid non-empty string.
 * Postcondition: The actor's name is updated.
 */
void Actor::setName(const string& name) {
    this->name = name;
}


/**
 * Retrieves the birth year of the actor.
 * Process: Returns the actor's birth year as an integer.
 * Precondition: The Actor object must have been initialized with a birth year.
 * Postcondition: Returns the actor's birth year.
 */
int Actor::getBirthYear() const {
    return birthYear;
}


/**
 * Updates the birth year of the actor.
 * Process: Assigns a new birth year to the actor.
 * Precondition: `year` must be a positive integer.
 * Postcondition: The actor's birth year is updated.
 */
void Actor::setBirthYear(int year) {
    birthYear = year;
}


/**
 * Retrieves the list of movies the actor has starred in.
 * Process: Returns a deep copy of the list of movies associated with the actor.
 * Precondition: The Actor object must have a movie list.
 * Postcondition: Returns a list of movies in which the actor has appeared.
 */
List<Movie*> Actor::getMovies() const {
    return movies;
}


/**
 * Adds a movie to the actor's list of movies.
 * Process: Adds a `Movie*` to the `movies` list of the actor.
 * Precondition: `movie` must be a valid `Movie*` object.
 * Postcondition: The movie is added to the actor's list of movies.
 */
void Actor::addMovieToActor(Movie* movie) {
    movies.add(movie);
}


/**
 * Sorts the movies associated with the actor.
 * Process: Uses the `sort` method to arrange movies alphabetically by title.
 * Precondition: The actor must have a list of movies.
 * Postcondition: The movies are sorted alphabetically.
 */
void Actor::sortMovies() {
    movies.sort([](const Movie* a, const Movie* b) -> bool {
        return a->getTitle() < b->getTitle();
        });
}


/**
 * Displays the movies in which the actor has appeared.
 * Process: Iterates through the list of movies and prints each movie's title and release year.
 * Precondition: The actor must have a movie list.
 * Postcondition: The list of movies is displayed in the console.
 */
void Actor::displayMovies() const {

    if (movies.isEmpty()) {
        cout << "No Movies found" << endl;
        return;
    }

    auto iterator = movies.createIterator();
    while (iterator->hasNext()) {
        Movie* movie = iterator->next();
        cout << "Movie: " << movie->getTitle() << " (" << movie->getReleaseYear() << ")" << endl;
    }
    delete iterator;
}
