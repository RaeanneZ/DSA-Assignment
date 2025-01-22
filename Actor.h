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

using namespace std;
class Movie;

class Actor
{
private:
    int id;
    string name;
    int birthYear;
    List<Movie*> movies; // Movies the actor starred in

    static int nextId;

public:

    Actor(const int& id, const string& name, int birthYear);

    int getId() const;
    void setId(const int& newId);

    string getName() const;
    void setName(const string& name);

    int getBirthYear() const;
    void setBirthYear(int year);

    void addMovieToActor(Movie* movie);
    void sortMovies();
    void displayMovies() const;
};

