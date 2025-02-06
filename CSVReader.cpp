#include "CSVReader.h"

// Function to trim leading and trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to correctly extract CSV fields with quotes
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

// Function to read all CSV files into the database
bool readAllCSV(ActorMovieDatabase& db) {
    Map<string, string> actorIdToName;
    Map<string, string> movieIdToTitle;

    // Read actors.csv
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

        try {
            db.addActor(name, stoi(birth));
        }
        catch (const exception& e) {
            cerr << "Error adding actor: " << e.what() << endl;
            continue;
        }

        actorIdToName.insert(id, name); // Store mapping
    }
    actorsFile.close();

    // Read movies.csv
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
            cerr << "Error: Invalid year for movie '" << title << "' | Raw input: " << year << "\n";
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

    // Read cast.csv
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

        actor->addMovieToActor(movie);
        movie->addActorToMovie(actor);
    }
    castFile.close();

    cout << "\nFinished reading all CSV files and associating actors with movies.\n";
    return true;
}
