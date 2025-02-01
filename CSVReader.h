#pragma once
#include "ActorMovieDatabase.h"

class CSVReader {
private:
    ActorMovieDatabase& database;
    Map<string, string> actorIdToName;   // Maps actor ID to actor name
    Map<string, string> movieIdToTitle;  // Maps movie ID to movie title

    void readActorsCSV();
    void readMoviesCSV();
    void readCastCSV();

public:
    explicit CSVReader(ActorMovieDatabase& db);
    bool loadCSVData();
};
