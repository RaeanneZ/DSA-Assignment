/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once
#include <string>
#include "Map.h"
#include "Actor.h"
#include "Movie.h"

using namespace std;

class ActorMovieDatabase
{
private:
    Map<string, Actor*> actorMap; // Maps actor names to Actor objects
    Map<string, Movie*> movieMap; // Maps movie titles to Movie objects

public:
    ActorMovieDatabase();
    ~ActorMovieDatabase();

    void addActor(const string& name, int birthYear);
    void addMovie(const string& title, const string& plot, int releaseYear);
    void associateActorWithMovie(const string& actorName, const string& movieTitle);

    Actor* findActor(const string& name) const;
    Movie* findMovie(const string& title) const;

    void displayActors() const;
    void displayMovies() const;

    void sortActorsByName();
    void sortMoviesByReleaseYear();

    void clearDatabase();
};

