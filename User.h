#pragma once

#include "List.h"
#include "Actor.h"
#include "Movie.h"

class User {
private:
    string username;
    string password;
    List<Actor*> favoriteActors;
    List<Movie*> favoriteMovies;

public:
    User(const string& username, const string& password);
    string getUsername() const;
    bool checkPassword(const string& password) const;
    void addFavoriteActor(Actor* actor);
    void removeFavoriteActor(const string& actorName);
    void addFavoriteMovie(Movie* movie);
    void removeFavoriteMovie(const string& movieTitle);
    void displayFavorites() const;
};
