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
#include "Actor.h"

using namespace std;
class Actor;

class Movie
{
private:
    int id;
    string title;
    string plot;
    int releaseYear;
    List<Actor*> actors; // Actors in the movie

    static int nextId;

public:
    Movie(const int& id, const string& title, const string& plot, int releaseYear);

    int getId() const;
    void setId(const int& id);

    string getTitle() const;
    void setTitle(const std::string& title);

    string getPlot() const;
    void setPlot(const std::string& plot);

    int getReleaseYear() const;
    void setReleaseYear(int year);

    void addActorToMovie(Actor* actor);
    void sortActors();
    void displayActors() const;
};

