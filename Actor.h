/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once

#include <string>
#include "Config.h"
#include "List.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Movie.h"

class Movie;

using namespace std;

class Actor {
private:
    string name;
    int birthYear;

    // Swap Between the different Data Structures
#if defined(USE_LIST)
    List<Movie*> movies;
#elif defined(USE_LINKED_LIST)
    LinkedList<Movie*> movies;
#elif defined(USE_QUEUE)
    Queue<Movie*> movies;
#endif

public:
    Actor(const string& name, int birthYear);

    string getName() const;
    void setName(const string& name);

    int getBirthYear() const;
    void setBirthYear(int year);

    void addMovieToActor(Movie* movie);
    void displayMovies() const;
    //void displayMovies() const;
    //void removeMovie(Movie* movie);
    //bool hasMovie(Movie* movie) const;

    //DATA_STRUCTURE<Movie*> getMovies() const;
};


