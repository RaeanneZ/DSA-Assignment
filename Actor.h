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
#include "Iterator.h"
#include DATA_STRUCTURE

using namespace std;

class Actor {
private:
    string name;
    int birthYear;
    DATA_STRUCTURE<class Movie*> movies;  // Now movies list can be any structure!

public:
    Actor(const string& name, int birthYear);

    string getName() const;
    void setName(const string& name);

    int getBirthYear() const;
    void setBirthYear(int year);

    void addMovieToActor(Movie* movie);
    void removeMovie(Movie* movie);
    bool hasMovie(Movie* movie) const;

    DATA_STRUCTURE<Movie*> getMovies() const;

    void displayMovies() const;
};


