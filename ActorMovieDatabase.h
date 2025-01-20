/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once

#include "Actor.h"
#include "Movie.h"
#include "Map.h"
#include <string>

class ActorMovieDatabase {
private:
    Map<std::string, Actor*> actorMap; // Maps actor names to Actor objects
    Map<std::string, Movie*> movieMap; // Maps movie titles to Movie objects

public:
    ActorMovieDatabase();
    ~ActorMovieDatabase();

    void addActor(const std::string& name, int birthYear);
    void addMovie(const std::string& title, const std::string& plot, int releaseYear);
    void associateActorWithMovie(const std::string& actorName, const std::string& movieTitle);

    Actor* findActor(const std::string& name) const;
    Movie* findMovie(const std::string& title) const;

    void displayActors() const;
    void displayMovies() const;

    void displayMoviesInPast3Years();
    void displayMoviesByActor(const std::string& actorName) const;
    void displayActorsByMovie(const string& movieTitle) const;

    void clearDatabase();
};


