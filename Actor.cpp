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
 * Initializes an Actor with a name and birth year.
 */
Actor::Actor(const string& name, int birthYear) {
    this->name = name;
    this->birthYear = birthYear;
}

/**
 * Get Name Method
 * Returns the actor's name.
 */
string Actor::getName() const {
    return name;
}

/**
 * Set Name Method
 * Updates the actor's name.
 */
void Actor::setName(const string& name) {
    this->name = name;
}

/**
 * Get Birth Year Method
 * Returns the actor's birth year.
 */
int Actor::getBirthYear() const {
    return birthYear;
}

/**
 * Set Birth Year Method
 * Updates the actor's birth year.
 */
void Actor::setBirthYear(int year) {
    birthYear = year;
}

//DataStructure<Movie*> Actor::getMovies() const {
//    return movies;
//}

/**
 * Add Movie to Actor Method
 * Adds a movie title to the actor's list of movies.
 */
//void Actor::addMovieToActor(Movie* movie) {
//    movies.add(movie);
//}

/**
 * Sort Movies Method
 * Sorts the actor's movies alphabetically.
 */
//void Actor::sortMovies() {
//    movies.sort([](const Movie* a, const Movie* b) -> bool {
//        return a->getTitle() < b->getTitle();
//        });
//}

/**
 * Display Movies Method
 * Prints the actor's movies to the console.
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
