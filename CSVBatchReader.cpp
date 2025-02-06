#include "CSVBatchReader.h"
#include <fstream>
#include <sstream>

// Function to trim leading and trailing spaces
string trimWhitespace(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to correctly extract CSV fields with quotes
std::string extractQuotes(std::istringstream& ss) {
    std::string field;
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

// Function to read the entire file into a string for batch processing
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

// Optimized readAllCSV function using custom Map and List
bool readBatchCSV(ActorMovieDatabase_Tree& db) {
    Map<string, string> actorIdToName;  // Custom AVL-based map for actor ID -> name
    Map<string, string> movieIdToTitle; // Custom AVL-based map for movie ID -> title

    // === Read actors.csv ===
    string actorData = readFileIntoString("actors.csv");
    if (actorData.empty()) return false; // Ensure file was read

    istringstream actorStream(actorData);
    string line;
    getline(actorStream, line); // Skip header

    while (getline(actorStream, line)) {
        istringstream ss(line);
        string id, name, birth;

        getline(ss, id, ','); // Extract ID
        name = extractQuotes(ss); // Extract name (handles commas)
        getline(ss, birth, ','); // Extract birth year

        try {
            db.addActor(name, stoi(birth)); // Add actor to AVL tree
        }
        catch (const exception& e) {
            cerr << "Error adding actor: " << e.what() << endl;
            continue;
        }
        actorIdToName.insert(id, name); // Store mapping for cast.csv
    }

    // === Read movies.csv ===
    string movieData = readFileIntoString("movies.csv");
    if (movieData.empty()) return false;

    istringstream movieStream(movieData);
    getline(movieStream, line); // Skip header

    while (getline(movieStream, line)) {
        istringstream ss(line);
        string id, title, plot, year;

        getline(ss, id, ','); // Read Movie ID
        title = extractQuotes(ss);
        plot = extractQuotes(ss);
        getline(ss, year, ','); // Read Year
        year = trimWhitespace(year);

        if (year.empty() || !isdigit(year[0])) {
            cerr << "Error: Invalid year for movie '" << title << "' | Raw input: " << year << "\n";
            continue;
        }

        try {
            db.addMovie(title, plot, stoi(year)); // Add movie to AVL tree
        }
        catch (const exception& e) {
            cerr << "Error adding movie: " << e.what() << " | Raw input: " << year << "\n";
            continue;
        }

        movieIdToTitle.insert(id, title); // Store mapping for cast.csv
    }

    cout << "Finished reading movies.csv successfully.\n";

    // === Read cast.csv ===
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
            cerr << "Error: Could not resolve ID " << person_id << " or " << movie_id << "\n";
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

