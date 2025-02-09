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
#include "User.h"
#include "AVLTree.h"
#include "Graph.h"
#include <string>
#include <iostream>

using namespace std;

class ActorMovieDatabase_Tree
{
private:
    AVLTree<string, Actor*> actorMap;
    AVLTree<string, Movie*> movieMap;
    AVLTree<string, User*> userMap;

    // For advanced feature
    Graph actorMovieGraph;
    AVLTree<string, AVLTree<string, bool>*> actorMovieConnections; // Replaces Graph

public:
    ActorMovieDatabase_Tree();
    ~ActorMovieDatabase_Tree();

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
    Graph& getGraph();
    void buildGraph();
    void recommendMovies(const string& actorName);
    void displayMindMap(const string& startNode);
    void renderBranches(const string& node, Graph& graph, List<string>& visited, const string& prefix);

    // Advanced Function 2 ---------------------------------------------------------------------------
    void addUser(const string& username);
    void rateMovie(const string& username, const string& movieTitle, int rating);
    void updateMovieRating(const string& movieTitle);
    void addWatchedMovie(const string& username, const string& movieTitle);
    void recommendPersonalisedMovies(const string& username);

    // Advanced Function 3 ---------------------------------------------------------------------------
    void displayMostInfluentialActor();
};

