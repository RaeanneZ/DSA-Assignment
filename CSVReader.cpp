/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "CSVReader.h"

/**
 * Trims leading and trailing whitespace from a string.
 * Process: Finds the first and last non-whitespace characters and extracts the substring.
 * Precondition: `str` must be a valid string.
 * Postcondition: Returns a new string with whitespace removed.
 */
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

/**
 * Extracts a CSV field, handling quoted values properly.
 * Process: If the field starts with a quote, extracts until the next quote; otherwise, extracts normally.
 * Precondition: `ss` must be a valid input string stream.
 * Postcondition: Returns the extracted and trimmed field.
 */
string extractQuotedField(istringstream& ss) {
    string field;
    if (ss.peek() == '"') {  // If field starts with a quote
        ss.get(); // Remove first quote
        getline(ss, field, '"'); // Extract until next quote
        ss.get(); // Remove the comma after closing quote
    }
    else {
        getline(ss, field, ','); // Extract normally
    }
    return trim(field);
}

/**
 * Reads actor, movie, and cast data from CSV files and stores them in the database.
 * Process: Reads actors.csv, movies.csv, and cast.csv. Maps actor and movie IDs to their respective names/titles.
            Associates actors with movies based on cast.csv.
 * Precondition: The CSV files must be present in the working directory.
 * Postcondition: The database is populated with actors, movies, and their associations.
 */
bool readAllCSV(ActorMovieDatabase& db) {
    Map<string, string> actorIdToName;
    Map<string, string> movieIdToTitle;

    // ======================= Read actors.csv ======================= 
    /**
    * Reads actors from actors.csv and stores them in the database.
    * Process: Reads the file line by line, extract actor ID, name, and birth year.
               Validates input before adding it to the database and maps actor ID to name for later use in cast.csv.
    * Precondition: actors.csv must be available in the correct format.
    * Postcondition: Actors are added to the database, and their IDs are stored in a map.
    */

    ifstream actorsFile("actors.csv");
    if (!actorsFile.is_open()) {
        cerr << "Error: Could not open actors.csv\n";
        return false;
    }

    string line;
    getline(actorsFile, line); // Skip the header
    while (getline(actorsFile, line)) {
        istringstream ss(line);
        string id, name, birth;

        getline(ss, id, ','); // Extract ID
        name = extractQuotedField(ss); // Extract name
        getline(ss, birth, ','); // Extract birth year

        // Ensure values are valid
        id = trim(id);
        name = trim(name);
        birth = trim(birth);

        if (id.empty() || name.empty() || birth.empty()) {
            cerr << "Skipping invalid actor entry: " << line << "\n";
            continue;
        }

        try {
            int birthYear = stoi(birth);
            db.addActor(name, birthYear);
        }
        catch (const exception& e) {
            cerr << "Error adding actor: " << e.what() << " | Raw input: " << birth << "\n";
            continue;
        }

        actorIdToName.insert(id, name); // Store mapping
    }
    actorsFile.close();


    // ======================= Read movies.csv ======================= 
    /**
    * Reads movies from movies.csv and stores them in the database.
    * Process: Reads the file line by line,then extracts movie ID, title, plot, and release year.
               Validates input before adding it to the database and maps movie ID to title for later use in cast.csv.
    * Precondition: movies.csv must be available in the correct format.
    * Postcondition: Movies are added to the database, and their IDs are stored in a map.
    */

    ifstream moviesFile("movies.csv");
    if (!moviesFile.is_open()) {
        cerr << "Error: Could not open movies.csv\n";
        return false;
    }

    getline(moviesFile, line); // Skip the header
    while (getline(moviesFile, line)) {
        istringstream ss(line);
        string id, title, plot, year;

        getline(ss, id, ','); // Read Movie ID
        title = extractQuotedField(ss);
        plot = extractQuotedField(ss);
        getline(ss, year, ','); // Read Year
        year = trim(year);

        if (year.empty() || !isdigit(year[0])) {
            cerr << "Skipping invalid movie entry: " << line << "\n";
            continue;
        }

        try {
            db.addMovie(title, plot, stoi(year));
        }
        catch (const exception& e) {
            cerr << "Error adding movie: " << e.what() << " | Raw input: " << year << "\n";
            continue;
        }

        movieIdToTitle.insert(id, title);
    }
    moviesFile.close();
    cout << "Finished reading movies.csv successfully.\n";


    // ======================= Read cast.csv ======================= 
    /**
    * Reads cast information from cast.csv and associates actors with movies.
    * Process: Reads the file line by line, matches actor and movie IDs to previously stored names and titles, then
               associates each actor with their respective movies.
    * Precondition: cast.csv must be available, and actor and movie mappings must be loaded.
    * Postcondition: Actors are correctly linked to their movies in the database.
    */

    ifstream castFile("cast.csv");
    if (!castFile.is_open()) {
        cerr << "Error: Could not open cast.csv\n";
        return false;
    }

    getline(castFile, line); // Skip the header
    while (getline(castFile, line)) {
        istringstream ss(line);
        string person_id, movie_id;
        getline(ss, person_id, ',');
        getline(ss, movie_id, ',');

        if (!actorIdToName.contains(person_id) || !movieIdToTitle.contains(movie_id)) {
            cerr << "Skipping unresolved cast entry: " << person_id << ", " << movie_id << "\n";
            continue;
        }

        string actorName = actorIdToName.get(person_id);
        string movieTitle = movieIdToTitle.get(movie_id);

        Actor* actor = db.findActor(actorName);
        Movie* movie = db.findMovie(movieTitle);

        if (!actor || !movie) {
            cerr << "Error: Actor or Movie not found in database for association.\n";
            continue;
        }

        actor->addMovieToActor(movie);
        movie->addActorToMovie(actor);
    }
    castFile.close();

    cout << "\nFinished reading all CSV files and associating actors with movies.\n";
    return true;
}

