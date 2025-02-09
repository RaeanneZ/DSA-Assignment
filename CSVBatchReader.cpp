/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "CSVBatchReader.h"
#include <algorithm>
#include <fstream>
#include <sstream>

/**
 * Trims leading and trailing whitespace from a string.
 * Process: Finds the first and last non-whitespace characters and extracts the substring.
 * Precondition: `str` must be a valid string.
 * Postcondition: Returns a new string with whitespace removed.
 */
string trimWhitespace(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}


/**
 * Extracts a CSV field, handling quoted values properly.
 * Process: If the field starts with a quote, it extracts until the next quote; otherwise, it extracts normally.
 * Precondition: `ss` must be a valid input string stream.
 * Postcondition: Returns the extracted and trimmed field.
 */
string extractQuotes(istringstream& ss) {
    string field;
    if (ss.peek() == '"') {  // If field starts with a quote
        ss.get(); // Remove first quote
        getline(ss, field, '"'); // Extract until next quote
        ss.get(); // Remove the comma after closing quote
    }
    else {
        getline(ss, field, ','); // Extract normally
    }
    return trimWhitespace(field);
}


/**
 * Reads the entire contents of a file into a string.
 * Process: Opens the file, reads its contents, and stores them in a string.
 * Precondition: `filename` must be a valid file path.
 * Postcondition: Returns the file content as a string. If the file cannot be opened, returns an empty string.
 */
string readFileIntoString(const string& filename) {
    ifstream file(filename, ios::in | ios::ate); // Open at the end for fast size check
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return "";
    }

    size_t fileSize = file.tellg(); // Get file size
    file.seekg(0, ios::beg);        // Go back to the start
    string content(fileSize, '\0'); // Allocate enough space
    file.read(&content[0], fileSize);
    file.close();
    return content;
}


/**
 * Reads actor, movie, and cast data from CSV files and stores them in the database.
 * Process: Reads actors.csv, movies.csv, and cast.csv. Maps actor and movie IDs to their respective names/titles and then 
            associates actors with movies based on cast.csv.
 * Precondition: The CSV files must be present in the working directory.
 * Postcondition: The database is populated with actors, movies, and their associations.
 */
// ActorMovieDatabase_Tree& db for Tree, ActorMovieDatabase& db for List
bool readBatchCSV(ActorMovieDatabase_Tree& db) {
    Map<string, string> actorIdToName;  // Custom AVL-based map for actor ID -> name
    Map<string, string> movieIdToTitle; // Custom AVL-based map for movie ID -> title


    // === Read actors.csv ===
    /**
    * Reads actors from actors.csv and stores them in the database.
    * Process: Reads the entire file into memory, then parses each line to extract actor ID, name, and birth year. The input 
               data is then validated and trimmed before storing it. Then maps actor ID to name for later use in cast.csv.
    * Precondition: actors.csv must be available in the correct format.
    * Postcondition: Actors are added to the database, and their IDs are stored in a map.
    */
    string actorData = readFileIntoString("actors.csv");
    if (actorData.empty()) return false; // Ensure file was read

    istringstream actorStream(actorData);
    string line;
    getline(actorStream, line); // Skip header

    while (getline(actorStream, line)) {
        line = trimWhitespace(line); // Trim any leading/trailing whitespace from the line

        // Skip completely empty lines
        if (line.empty()) {
            /*cerr << "Skipping empty line in actors.csv\n";*/
            continue;
        }

        istringstream ss(line);
        string id, name, birth;

        getline(ss, id, ',');        // Extract ID
        name = extractQuotes(ss);    // Extract Name
        getline(ss, birth, ',');     // Extract Birth Year

        // Trim individual fields
        id = trimWhitespace(id);
        name = trimWhitespace(name);
        birth = trimWhitespace(birth);

        // Skip if any of the fields are empty or invalid
        if (id.empty() || name.empty() || birth.empty() || !all_of(birth.begin(), birth.end(), ::isdigit)) {
            /*cerr << "Skipping invalid actor entry: " << line << "\n";*/
            continue;
        }

        try {
            db.addActor(name, stoi(birth)); // Add valid actor
        }
        catch (const exception& e) {
            cerr << "Error adding actor: " << e.what() << " | Raw input: " << birth << "\n";
            continue;
        }

        actorIdToName.insert(id, name); // Map ID to Name for cast.csv processing
    }


    // === Read movies.csv ===
    /**
    * Reads movies from movies.csv and stores them in the database.
    * Process: Reads the entire file into memory, then parses each line to extract movie ID, title, plot, and release year.
               The input data are then validated and trimmed before storing it. Maps movie ID to title for later use in cast.csv.
    * Precondition: movies.csv must be available in the correct format.
    * Postcondition: Movies are added to the database, and their IDs are stored in a map.
    */
    string movieData = readFileIntoString("movies.csv");
    if (movieData.empty()) return false;

    istringstream movieStream(movieData);
    getline(movieStream, line); // Skip header

    while (getline(movieStream, line)) {
        line = trimWhitespace(line); // Trim line

        // Skip completely empty lines
        if (line.empty()) {
            cerr << "Skipping empty line in movies.csv\n";
            continue;
        }

        istringstream ss(line);
        string id, title, plot, year;

        getline(ss, id, ',');        // Extract Movie ID
        title = extractQuotes(ss);   // Extract Title
        plot = extractQuotes(ss);    // Extract Plot
        getline(ss, year, ',');      // Extract Year

        // Trim individual fields
        id = trimWhitespace(id);
        title = trimWhitespace(title);
        plot = trimWhitespace(plot);
        year = trimWhitespace(year);

        // Skip if any of the fields are empty or invalid
        if (id.empty() || title.empty() || year.empty() || !all_of(year.begin(), year.end(), ::isdigit)) {
            /*cerr << "Skipping invalid movie entry: " << line << "\n";*/
            continue;
        }

        try {
            db.addMovie(title, plot, stoi(year)); // Add valid movie
        }
        catch (const exception& e) {
            cerr << "Error adding movie: " << e.what() << " | Raw input: " << year << "\n";
            continue;
        }

        movieIdToTitle.insert(id, title); // Map ID to Title for cast.csv processing
    }


    // === Read cast.csv ===
    /**
    * Reads cast information from cast.csv and associates actors with movies.
    * Process: Reads the entire file into memory, matches actor and movie IDs to previously stored names and titles, then
               associates each actor with their respective movies.
    * Precondition: cast.csv must be available, and actor and movie mappings must be loaded.
    * Postcondition: Actors are correctly linked to their movies in the database.
    */
    string castData = readFileIntoString("cast.csv");
    if (castData.empty()) return false;

    istringstream castStream(castData);
    getline(castStream, line); // Skip header

    while (getline(castStream, line)) {
        istringstream ss(line);
        string person_id, movie_id;
        getline(ss, person_id, ',');
        getline(ss, movie_id, ',');

        if (!actorIdToName.contains(person_id) || !movieIdToTitle.contains(movie_id)) {
            if (!actorIdToName.contains(person_id)) {
                /*cerr << "Error: Could not resolve Actor ID " << person_id << endl;*/
            }
            if (!movieIdToTitle.contains(movie_id)) {
                /*cerr << "Error: Could not resolve Movie ID " << movie_id << endl;*/
            }
            
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

        // Associate actor with movie
        actor->addMovieToActor(movie);
        movie->addActorToMovie(actor);
    }

    cout << "\nFinished reading all CSV files and associating actors with movies.\n";
    return true;
}