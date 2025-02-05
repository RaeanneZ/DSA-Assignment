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
#include "AVLTree.h"
#include "Actor.h"

class Actor;

using namespace std;

class Movie {
private:
    string title;
    int releaseYear;

#if defined(USE_LIST)
    List<Actor*> actors;
#elif defined(USE_AVL_TREE)
    AVLTree<Actor*> actors;
#endif

public:
    Movie(const string& title, int releaseYear);

    string getTitle() const;
    void setTitle(const string& title);

    int getReleaseYear() const;
    void setReleaseYear(int year);

    void addActorToMovie(Actor* actor);
    void displayActors() const;

    /*void removeActor(Actor* actor);
    bool hasActor(Actor* actor) const;

    DATA_STRUCTURE<Actor*> getActors() const;*/
};

