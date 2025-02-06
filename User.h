#pragma once
#include "List.h"
#include "Movie.h"
#include "Map.h"
#include <string>

using namespace std;

class User {
private:
    std::string username;
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
