#include "User.h"
#include <iostream>


/**
 * Constructor
 * Process: Initializes a User with a given username.
 * Precondition: The username must be a valid non-empty string.
 * Postcondition: A User object is created with an empty movie and actor rating list.
 */
User::User(const string& name) : username(name) {}

/**
 * Get Username
 * Process: Retrieves the username of the user.
 * Precondition: None.
 * Postcondition: Returns the username as a string.
 */
string User::getUsername() const {
    return username;
}

/**
 * Rate Movie
 * Process: Allows a user to rate a movie with a value between 1 and 5.
 * Precondition: `rating` must be between 1 and 5 inclusive.
 * Postcondition: The rating is stored in `movieRatings`, or an error message is displayed for invalid values.
 */
void User::rateMovie(const string& movieTitle, int rating) {
    if (rating >= 1 && rating <= 5) {
        movieRatings.insert(movieTitle, rating);
    }
    else {
        cout << "Invalid rating. Please enter a rating between 1 and 5.\n";
    }
}

/**
 * Add Watched Movie
 * Process: Adds a movie to the user's watched list.
 * Precondition: `movieTitle` must be a valid non-empty string.
 * Postcondition: The movie title is stored in `watchedMovies`.
 */
void User::addWatchedMovie(const string& movieTitle) {
    watchedMovies.add(movieTitle);
}

/**
 * Get Watched Movies
 * Process: Retrieves the list of movies watched by the user.
 * Precondition: None.
 * Postcondition: Returns a `List<string>` containing movie titles.
 */
List<string> User::getWatchedMovies() const {
    return watchedMovies;
}

/**
 * Get Movie Rating
 * Process: Retrieves the rating of a specific movie by the user.
 * Precondition: The movie title must exist in `movieRatings`.
 * Postcondition: Returns the rating of the movie, or 0 if not found.
 */
int User::getMovieRating(const string& movieTitle) const {
    return movieRatings.contains(movieTitle) ? movieRatings.get(movieTitle) : 0;
}


void User::displayRatings() const {
    cout << "Ratings by " << username << ":\n";
    cout << "Movies:\n";
    auto movieIt = movieRatings.createIterator();
    while (movieIt->hasNext()) {
        auto pair = movieIt->next();
        cout << " - " << pair->key << ": " << pair->value << "\n";
    }
    delete movieIt;
    cout << "Actors:\n";
    auto actorIt = actorRatings.createIterator();
    while (actorIt->hasNext()) {
        auto pair = actorIt->next();
        cout << " - " << pair->key << ": " << pair->value << "\n";
    }
    delete actorIt;
}
