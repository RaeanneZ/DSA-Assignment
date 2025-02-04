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
#include "Config.h"
#include "List.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "Map.h"
#include "Dictionary.h"
#include "Tree.h"
#include "AVLTree.h"
#include "Graph.h"
#include "SearchingAlgorithms.h"
#include "SortingAlgorithms.h"

using namespace std;

class ActorMovieDatabase {
private:
    DATA_STRUCTURE<Actor*> actors;
    DATA_STRUCTURE<Movie*> movies;

    Graph actorMovieGraph; // Graph for actor-movie relationships

public:
    void addActor(const string& name, int birthYear);
    void addMovie(const string& title, const string& plot, int releaseYear);
    void associateActorWithMovie(const string& actorName, const string& movieTitle);

    void updateActorDetails(const string& oldName, const string& newName, int newBirthYear);
    void updateMovieDetails(const string& oldTitle, const string& newTitle, int newYear);

    void displayActors() const;
    void displayMovies() const;

    void displayMoviesForActor(const string& actorName) const;
    void displayActorsInMovie(const string& movieTitle) const;

    void displayKnownActors(const string& actorName) const;

    /*void addActor(const string& name, int birthYear);
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
    void displayMovies() const;*/

    void clearDatabase();



    // Advanced Features ---------------------------------------------
    Graph& getGraph();
    void buildGraph();
    void exploreConnections(const string& node);
    void recommendMovies(const string& actorName);
    void displayMindMap(const string& startNode);
    void renderBranches(const string& node, Graph& graph, List<string>& visited, const string& prefix, bool isActor);
};


