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
    string title;
    int releaseYear;
    string plot;
    float rating;
    List<Actor*> actors; // Actors in the movie

public:
    Movie(const string& title, string plot, int releaseYear);

    string getTitle() const;
    void setTitle(const string& title);

    int getReleaseYear() const;
    void setReleaseYear(int year);

    string getPlot() const;
    void setPlot(string plot);

    float getRating() const;
    void setRating(float rating);

    const List<Actor*> getActors() const;

    void addActorToMovie(Actor* actor);
    void sortActors();
    void displayActors() const;
};

