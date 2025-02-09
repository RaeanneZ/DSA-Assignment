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
 * Process: Initializes a Movie object with a title, plot, and release year.
 * The initial rating is set to 0.0.
 * Precondition: `title` must be a valid non-empty string. `plot` should be a valid string.`releaseYear` must be a positive integer.
 * Postcondition: A new Movie object is created with the given details.
 */
Movie::Movie(const string& title, string plot, int releaseYear) : title(title), plot(plot), releaseYear(releaseYear), rating(0.0) {}


/**
 * Retrieves the title of the movie.
 * Process: Returns the movie's title as a string.
 * Precondition: The Movie object must be initialized with a title.
 * Postcondition: Returns the title of the movie.
 */
string Movie::getTitle() const {
    return title;
}


/**
 * Updates the title of the movie.
 * Process: Assigns a new title to the movie.
 * Precondition: `title` must be a valid non-empty string.
 * Postcondition: The movie's title is updated.
 */
void Movie::setTitle(const string& title) {
    this->title = title;
}


/**
 * Retrieves the release year of the movie.
 * Process: Returns the movie's release year.
 * Precondition: The Movie object must have been initialized with a release year.
 * Postcondition: Returns the movie's release year as an integer.
 */
int Movie::getReleaseYear() const {
    return releaseYear;
}


/**
 * Updates the release year of the movie.
 * Process: Assigns a new release year to the movie.
 * Precondition: `year` must be a positive integer.
 * Postcondition: The movie's release year is updated.
 */
void Movie::setReleaseYear(int year) {
    releaseYear = year;
}


/**
 * Retrieves the plot of the movie.
 * Process: Returns the movie's plot as a string.
 * Precondition: The Movie object must have been initialized with a plot.
 * Postcondition: Returns the plot description of the movie.
 */
string Movie::getPlot() const {
    return plot;
}


/**
 * Updates the plot of the movie.
 * Process: Assigns a new plot description to the movie.
 * Precondition: `plot` must be a valid string.
 * Postcondition: The movie's plot description is updated.
 */
void Movie::setPlot(string plot) {
    this->plot = plot;
}


/**
 * Retrieves the rating of the movie.
 * Process: Returns the movie's rating as a floating-point number.
 * Precondition: The Movie object must have a valid rating.
 * Postcondition: Returns the movie's rating.
 */
float Movie::getRating() const {
    return rating; 
}


/**
 * Updates the rating of the movie.
 * Process: Assigns a new rating to the movie.
 * Precondition: `rating` must be a floating-point number between 0.0 and 10.0.
 * Postcondition: The movie's rating is updated.
 */
void Movie::setRating(float rating) { 
    this->rating = rating; 
}


/**
 * Retrieves the list of actors in the movie.
 * Process: Returns a deep copy of the list of actors associated with the movie.
 * Precondition: The Movie object must have an actor list.
 * Postcondition: Returns a list of actors in the movie.
 */
const List<Actor*> Movie::getActors() const {
    return actors; // This now returns a deep copy, thanks to the updated List copy constructor
}


/**
 * Adds an actor to the movie.
 * Process: Checks if the actor is valid and then adds the actor to the movie's list of actors.
 * Precondition: `actor` must be a valid Actor object.
 * Postcondition: The actor is added to the movie's actor list.
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
 * Sorts the actors in the movie.
 * Process: Uses the `sort` method to arrange actors alphabetically by name.
 * Precondition: The movie must have a list of actors.
 * Postcondition: The actors are sorted alphabetically.
 */
void Movie::sortActors() {
    actors.sort([](Actor* a, Actor* b) -> bool {
        return a->getName() < b->getName();
        });
}


/**
 * Displays the actors in the movie.
 * Process: Iterates through the list of actors and prints each actor's name and birth year.
 * Precondition: The movie must have an actor list.
 * Postcondition: The list of actors is displayed in the console.
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