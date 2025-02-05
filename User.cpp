#include "User.h"
#include "User.h"
#include <iostream>

User::User(const string& name) : username(name) {}

string User::getUsername() const {
    return username;
}

void User::rateMovie(const string& movieTitle, int rating) {
    if (rating >= 1 && rating <= 5) {
        movieRatings.insert(movieTitle, rating);
    }
    else {
        cout << "Invalid rating. Please enter a rating between 1 and 5.\n";
    }
}

void User::rateActor(const string& actorName, int rating) {
    if (rating >= 1 && rating <= 5) {
        actorRatings.insert(actorName, rating);
    }
    else {
        cout << "Invalid rating. Please enter a rating between 1 and 5.\n";
    }
}

void User::addWatchedMovie(const string& movieTitle) {
    watchedMovies.add(movieTitle);
}

List<string> User::getWatchedMovies() const {
    return watchedMovies;
}

int User::getMovieRating(const string& movieTitle) const {
    return movieRatings.contains(movieTitle) ? movieRatings.get(movieTitle) : 0;
}

int User::getActorRating(const string& actorName) const {
    return actorRatings.contains(actorName) ? actorRatings.get(actorName) : 0;
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
