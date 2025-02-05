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
#include "Map.h"
#include "Dictionary.h"
#include "Graph.h"

using namespace std;

class ActorMovieDatabase {
private:
    // Allow for picking between map and dictionary for testing
#if defined(USE_MAP)
    Map<std::string, Actor*>* actorMap;
    Map<std::string, Movie*>* movieMap;
#elif defined(USE_DICTIONARY)
    Dictionary<std::string, Actor*>* actorMap;
    Dictionary<std::string, Movie*>* movieMap;
#endif

    Graph actorMovieGraph; // Graph for actor-movie relationships

public:
    ActorMovieDatabase();
    ~ActorMovieDatabase();

    void addActor(const string& name, int birthYear);
    void addMovie(const string& title, int releaseYear);
    void associateActorWithMovie(const string& actorName, const string& movieTitle);

    // Update Actor/Movie Details
    void updateActorDetails(const string& actorName, const string& newName, int newBirthYear);
    void updateMovieDetails(const string& movieTitle, const string& newTitle, int newYear);

    // Display Functions
    void displayActorsByAgeRange(int x, int y) const;
    void displayRecentMovies(int currentYear) const;
    void displayMoviesForActor(const string& actorName) const;
    void displayActorsInMovie(const string& movieTitle) const;
    void displayKnownActors(const string& actorName) const;

    void displayActors() const;
    void displayMovies() const;

    /*void displayMoviesForActor(const string& actorName) const;
    void displayActorsInMovie(const string& movieTitle) const;*/
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


