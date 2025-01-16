/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "Movie.h"
#include <iostream>
using namespace std;

/**
 * Constructor
 * Initializes a Movie with a title, plot, and release year.
 */
Movie::Movie(const string& title, const string& plot, int releaseYear) : title(title), plot(plot), releaseYear(releaseYear) {}

/**
 * Get Title Method
 * Returns the movie's title.
 */
string Movie::getTitle() const {
    return title;
}

/**
 * Set Title Method
 * Updates the movie's title.
 */
void Movie::setTitle(const string& title) {
    this->title = title;
}

/**
 * Get Plot Method
 * Returns the movie's plot.
 */
string Movie::getPlot() const {
    return plot;
}

/**
 * Set Plot Method
 * Updates the movie's plot.
 */
void Movie::setPlot(const string& plot) {
    this->plot = plot;
}

/**
 * Get Release Year Method
 * Returns the movie's release year.
 */
int Movie::getReleaseYear() const {
    return releaseYear;
}

/**
 * Set Release Year Method
 * Updates the movie's release year.
 */
void Movie::setReleaseYear(int year) {
    releaseYear = year;
}

/**
 * Add Actor to Movie Method
 * Adds an actor to the movie's list of actors.
 */
void Movie::addActorToMovie(Actor* actor) {
    actors.add(actor);
}

/**
 * Sort Actors Method
 * Sorts the movie's actors alphabetically by name.
 */
void Movie::sortActors() {
    actors.sort([](Actor* a, Actor* b) -> bool {
        return a->getName() < b->getName();
        });
}

/**
 * Display Actors Method
 * Prints the movie's actors to the console.
 */
void Movie::displayActors() const {
    auto iterator = actors.createIterator();
    while (iterator->hasNext()) {
        Actor* actor = iterator->next();
        cout << "Actor: " << actor->getName() << " (" << actor->getBirthYear() << ")" << endl;
    }
    delete iterator;
}