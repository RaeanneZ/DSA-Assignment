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
Movie::Movie(const string& title, string plot, int releaseYear) : title(title), plot(plot), releaseYear(releaseYear), rating(0.0) {}

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

string Movie::getPlot() const {
    return plot;
}
void Movie::setPlot(string plot) {
    this->plot = plot;
}

float Movie::getRating() const {
    return rating; 
}

void Movie::setRating(float rating) { 
    this->rating = rating; 
}

//const List<Actor*>& Movie::getActors() const {
const List<Actor*> Movie::getActors() const {
    return actors; // This now returns a deep copy, thanks to the updated List copy constructor
}

/**
 * Add Actor to Movie Method
 * Adds an actor to the movie's list of actors.
 */
void Movie::addActorToMovie(Actor* actor) {
    //Validate actor before adding to movie
    if (!actor) {
        cerr << "Error: Attempted to add null actor to movie \"" << title << "\".\n";
        return;
    }

    //cout << "Adding actor \"" << actor->getName() << "\" to movie \"" << title << "\".\n";

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
    if (actors.isEmpty()) {
        cout << "No actors for this movie" << endl;
        return;
    }

    auto iterator = actors.createIterator();
    while (iterator->hasNext()) {
        Actor* actor = iterator->next();
        //cout << "Movie::printActors -" << actor << endl;
        cout << "Actor: " << actor->getName() << " (" << actor->getBirthYear() << ")" << endl;
    }
    delete iterator;
}