#include "User.h"
#include <iostream>

User::User(const string& username, const string& password)
    : username(username), password(password) {
}

string User::getUsername() const { return username; }

bool User::checkPassword(const string& input) const {
    return password == input;
}

void User::addFavoriteActor(Actor* actor) {
    if (actor) favoriteActors.add(actor);
}

void User::removeFavoriteActor(const string& actorName) {
    bool removed = false;
    auto it = favoriteActors.createIterator();
    while (it->hasNext()) {
        Actor* a = it->next();
        if (a && a->getName() == actorName) {
            favoriteActors.remove(a);
            removed = true;
            break;
        }
    }
    delete it;
    if (!removed) {
        cout << "Actor not found in favorites.\n";
    }
}

void User::addFavoriteMovie(Movie* movie) {
    if (movie) favoriteMovies.add(movie);
}

void User::removeFavoriteMovie(const string& movieTitle) {
    bool removed = false;
    auto it = favoriteMovies.createIterator();
    while (it->hasNext()) {
        Movie* m = it->next();
        if (m && m->getTitle() == movieTitle) {
            favoriteMovies.remove(m);
            removed = true;
            break;
        }
    }
    delete it;
    if (!removed) {
        cout << "Movie not found in favorites.\n";
    }
}

void User::displayFavorites() const {
    std::cout << "\n=== Favorites ===\n";

    // Display favorite actors
    std::cout << "Actors:\n";
    auto actorIt = favoriteActors.createIterator();
    while (actorIt->hasNext()) {
        Actor* a = actorIt->next();
        std::cout << "- " << a->getName() << "\n";
    }
    delete actorIt;

    // Display favorite movies
    std::cout << "\nMovies:\n";
    auto movieIt = favoriteMovies.createIterator();
    while (movieIt->hasNext()) {
        Movie* m = movieIt->next();
        std::cout << "- " << m->getTitle() << "\n";
    }
    delete movieIt;
}