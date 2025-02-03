/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once
#include <string>
#include "List.h"
#include "Movie.h"
#include "Config.h"

using namespace std;
class Movie;

class Actor
{
private:
    string name;
    int birthYear;
    DataStructure<Movie*> movies; // Movies the actor starred in

public:
    Actor(const string& name, int birthYear);

    string getName() const;
    void setName(const string& name);

    int getBirthYear() const;
    void setBirthYear(int year);

    DataStructure<Movie*> getMovies() const;

    void addMovieToActor(Movie* movie);
    void sortMovies();
    void displayMovies() const;
};

