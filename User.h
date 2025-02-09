/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/


#pragma once
#include "List.h"
#include "Movie.h"
#include "Map.h"
#include <string>

using namespace std;

class User {
private:
    string username;
    Map<string, int> movieRatings; // Movie title -> Rating
    Map<string, int> actorRatings; // Actor name -> Rating
    List<string> watchedMovies; // Movies watched by user

public:
    User(const string& name);
    string getUsername() const;
    void rateMovie(const string& movieTitle, int rating);
    void addWatchedMovie(const string& movieTitle);
    List<string> getWatchedMovies() const;
    int getMovieRating(const string& movieTitle) const;
    void displayRatings() const;
};
