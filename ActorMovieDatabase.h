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
    Map<string, Actor*> actors; // Dictionary for actors by name
    Map<string, Movie*> movies; // Dictionary for movies by title

public:
    // Add a new actor
    void addActor(string name, int birthYear);

    // Add a new movie
    void addMovie(string title, string plot, int releaseYear);

    // Associate an actor with a movie
    void addActorToMovie(string actorName, string movieTitle);

    // Display actors by age range
    void displayActorsByAge(int minAge, int maxAge, int currentYear);

    // Display recent movies
    void displayRecentMovies(int years, int currentYear);

    // Display all movies of an actor
    void displayMoviesByActor(string actorName);

    // Display all actors in a movie
    void displayActorsByMovie(string movieTitle);

    // Cleanup resources
    ~ActorMovieDatabase();
};

