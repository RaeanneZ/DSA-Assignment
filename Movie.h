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

class Movie
{
private:
    string title;
    string plot;
    int releaseYear;
    List<string> actors; // Actors in the movie

public:
    Movie(string title, string plot, int releaseYear) : title(title), plot(plot), releaseYear(releaseYear) {}
};

