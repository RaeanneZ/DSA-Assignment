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

class Movie {
private:
    string title;
    string plot;
    int releaseYear;
    DATA_STRUCTURE<class Actor*> actors;  // Now actors list can be any structure!

public:
    Movie(const string& title, const string& plot, int releaseYear);

    string getTitle() const;
    void setTitle(const string& title);

    int getReleaseYear() const;
    void setReleaseYear(int year);

    void addActorToMovie(Actor* actor);
    void removeActor(Actor* actor);
    bool hasActor(Actor* actor) const;

    DATA_STRUCTURE<Actor*> getActors() const;

    void displayActors() const;
};

