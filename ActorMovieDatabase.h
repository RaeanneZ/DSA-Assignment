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
#include "Graph.h"
#include <string>
#include <iostream>

using namespace std;

class ActorMovieDatabase {
private:
    Map<string, Actor*> actorMap; // Maps actor names to Actor objects
    Map<string, Movie*> movieMap; // Maps movie titles to Movie objects
    Graph actorMovieGraph; // Graph for actor-movie relationships

public:
    ActorMovieDatabase();
    ~ActorMovieDatabase();

    void addActor(const string& name, int birthYear);
    void addMovie(const string& title, const string& plot, int releaseYear);
    void updateActorDetails(const string& actorName, const string& newName, int newBirthYear);
    void updateMovieDetails(const string& movieTitle, const string& newTitle, int newYear);
    void displayRecentMovies() const;
    void displayMoviesForActor(const string& actorName) const;
    void displayActorsInMovie(const string& movieTitle) const;
    void associateActorWithMovie(const string& actorName, const string& movieTitle);

    Actor* findActor(const string& name) const;
    Movie* findMovie(const string& title) const;

    void displayActors() const;
    void displayActorsByAgeRange(int x, int y) const;
    void displayKnownActors(const string& actorName) const;
    void findIndirectRelations(Actor* targetActor, List<Actor*>& knownActors) const;
    bool addUniqueActor(List<Actor*>& knownActors, Actor* actor) const;
    void displayActorList(const List<Actor*>& actorList) const;
    void addDirectCoActors(Actor* targetActor, List<Actor*>& knownActors) const;
    void displayMovies() const;

    void clearDatabase();



    // Advanced Features ---------------------------------------------
    void buildGraph();
    void exploreConnections(const string& node);
    void recommendMovies(const string& actorName);
};


