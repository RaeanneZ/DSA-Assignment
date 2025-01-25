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
    string plot;
    int releaseYear;
    List<Actor*> actors; // Actors in the movie

public:
    Movie(const string& title, const string& plot, int releaseYear);

    string getTitle() const;
    void setTitle(const std::string& title);

    string getPlot() const;
    void setPlot(const std::string& plot);

    int getReleaseYear() const;
    void setReleaseYear(int year);

    //const List<Actor*>& getActors() const;
    const List<Actor*> getActors() const;

    void addActorToMovie(Actor* actor);
    void sortActors();
    void displayActors() const;
};