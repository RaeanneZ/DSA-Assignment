/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "ActorMovieDatabase.h"
#include "List.h"
#include "Graph.h"
#include "Actor.h"
#include "Movie.h"
#include <iostream>
#include <ctime>
using namespace std;

/**
 * Constructor
 * Initializes the ActorMovieDatabase.
 * Precondition: None.
 * Postcondition: A new database is created with no actors or movies.
 */
ActorMovieDatabase::ActorMovieDatabase() {}

/**
 * Destructor
 * Frees all dynamically allocated memory.
 * Precondition: None.
 * Postcondition: All actor and movie objects are deleted, and the database is cleared.
 */
ActorMovieDatabase::~ActorMovieDatabase() {
    clearDatabase();
}

/**
 * Add an actor to the database.
 * Process: Creates a new Actor object and adds it to the actorMap.
 * Precondition: The actor's name and birth year must be provided.
 * Postcondition: A new Actor is added to the database, or existing Actor is updated if already present.
 */
void ActorMovieDatabase::addActor(const string& name, int birthYear) {

    if (name.empty() || birthYear <= 0) {
        cout << "Error: Invalid actor data." << endl;
        return;
    }
    Actor* newActor = new Actor(name, birthYear);
    if (!newActor) {
        cout << "Error : Failed to allocate memory for actor." << endl;
        return;
    }

    if (!actorMap.contains(name)) {
        actorMap.insert(name, newActor);
    }
}


/**
 * Add a movie to the database.
 * Process: Creates a new Movie object and adds it to the movieMap.
 * Precondition: The movie's title, plot, and release year must be provided.
 * Postcondition: A new Movie is added to the database, or existing Movie is updated if already present.
 */
void ActorMovieDatabase::addMovie(const string& title, const string& plot, int releaseYear) {

    Movie* movie = new Movie(title, plot, releaseYear);
    if (!movieMap.contains(title)) {
        movieMap.insert(title, movie);
    }
}

/**
 * Updates the details of an actor.
 * @param actorName The name of the actor to update.
 * @param newName The new name for the actor.
 * @param newBirthYear The new birth year for the actor.
 * Process: Finds the actor in the database, updates their details, and ensures the changes propagate in related movies.
 * Precondition: The actor must exist in the database.
 * Postcondition: The actor's details are updated, and the references in related movies remain valid.
 */
void ActorMovieDatabase::updateActorDetails(const string& actorName, const string& newName, int newBirthYear) {
    Actor* actor = findActor(actorName);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    actorMap.remove(actorName); // Remove old reference
    actor->setName(newName);
    if (newBirthYear > 0) {
        actor->setBirthYear(newBirthYear);
    }
    actorMap.insert(newName, actor); // Reinsert with the updated name
}

/**
 * Updates the details of a movie.
 * @param movieTitle The title of the movie to update.
 * @param newTitle The new title for the movie.
 * @param newYear The new release year for the movie.
 * Process: Finds the movie in the database, updates its details, and ensures references in related actors remain valid.
 * Precondition: The movie must exist in the database.
 * Postcondition: The movie's details are updated, and the references in related actors remain valid.
 */
void ActorMovieDatabase::updateMovieDetails(const string& movieTitle, const string& newTitle, int newYear) {
    Movie* movie = findMovie(movieTitle);
    if (!movie) {
        cout << "Movie not found.\n";
        return;
    }

    movieMap.remove(movieTitle); // Remove old reference
    movie->setTitle(newTitle);
    if (newYear > 0) {
        movie->setReleaseYear(newYear);
    }
    movieMap.insert(newTitle, movie); // Reinsert with the updated title
}

/**
 * Displays movies made within the past 3 years in ascending order.
 * Process: Iterates through all movies, checks their release year, and displays those within the past 3 years.
 * Precondition: The database must be populated with movies and the current year must be available.
 * Postcondition: Movies from the past 3 years are displayed in ascending order of year.
 */
void ActorMovieDatabase::displayRecentMovies() const {
    int currentYear = time(nullptr) / (60 * 60 * 24 * 365.25) + 1970; // Approximate current year

    List<Movie*> recentMovies;
    auto it = movieMap.createIterator();
    while (it->hasNext()) {
        Movie* movie = it->next()->value;
        if (movie->getReleaseYear() >= currentYear - 3) {
            recentMovies.add(movie);
        }
    }
    delete it;

    // Sort movies by release year
    recentMovies.sort([](Movie* a, Movie* b) {
        return a->getReleaseYear() < b->getReleaseYear();
        });

    cout << "Movies from the past 3 years:\n";
    auto recentIt = recentMovies.createIterator();
    while (recentIt->hasNext()) {
        Movie* movie = recentIt->next();
        cout << movie->getTitle() << " (" << movie->getReleaseYear() << ")\n";
    }
    delete recentIt;
}

/**
 * Displays all movies an actor starred in, sorted alphabetically.
 * @param actorName The name of the actor.
 * Process: Retrieves the movies associated with the actor and displays them in alphabetical order.
 * Precondition: The actor must exist in the database.
 * Postcondition: Movies the actor starred in are displayed alphabetically.
 */
void ActorMovieDatabase::displayMoviesForActor(const string& actorName) const {
    Actor* actor = findActor(actorName);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    List<Movie*> movies = actor->getMovies();
    movies.sort([](Movie* a, Movie* b) {
        return a->getTitle() < b->getTitle();
        });

    cout << "Movies starring " << actor->getName() << ":\n";
    auto movieIt = movies.createIterator();
    while (movieIt->hasNext()) {
        Movie* movie = movieIt->next();
        cout << movie->getTitle() << " (" << movie->getReleaseYear() << ")\n";
    }
    delete movieIt;
}

/**
 * Displays all actors in a particular movie, sorted alphabetically.
 * @param movieTitle The title of the movie.
 * Process: Retrieves the actors associated with the movie and displays them in alphabetical order.
 * Precondition: The movie must exist in the database.
 * Postcondition: Actors in the movie are displayed alphabetically.
 */
void ActorMovieDatabase::displayActorsInMovie(const string& movieTitle) const {
    Movie* movie = findMovie(movieTitle);
    if (!movie) {
        cout << "Movie not found.\n";
        return;
    }

    List<Actor*> actors = movie->getActors();
    actors.sort([](Actor* a, Actor* b) {
        return a->getName() < b->getName();
        });

    cout << "Actors in \"" << movie->getTitle() << "\":\n";
    auto actorIt = actors.createIterator();
    while (actorIt->hasNext()) {
        Actor* actor = actorIt->next();
        cout << actor->getName() << " (" << actor->getBirthYear() << ")\n";
    }
    delete actorIt;
}



/**
 * Associate an actor with a movie.
 * Process: Finds the actor and movie in the database and links them.
 * Precondition: Both the actor and movie must already exist in the database.
 * Postcondition: The actor is added to the movie's actor list, and the movie is added to the actor's movie list.
 */
void ActorMovieDatabase::associateActorWithMovie(const string& actorName, const string& movieTitle) {

    Actor* actor = findActor(actorName);
    Movie* movie = findMovie(movieTitle);

    if (!actor || !movie) {
        cerr << "Error: Cannot associate \"" << actorName << "\" with \"" << movieTitle
            << "\". Actor or Movie not found.\n";
        return;
    }
 
    actor->addMovieToActor(movie);
    movie->addActorToMovie(actor);
    
}


/**
 * Find an actor by name.
 * Process: Searches for the actor in the actorMap.
 * Precondition: The actor's name must be provided.
 * Postcondition: Returns a pointer to the Actor if found, or nullptr otherwise.
 */
Actor* ActorMovieDatabase::findActor(const string& name) const {
    // Check if the actor exists in the map
    if (!actorMap.contains(name)) {
        cerr << "Error: Actor \"" << name << "\" not found in actorMap.\n";
        return nullptr;
    }

    // Retrieve the actor from the map
    Actor* actor = actorMap.get(name);
    if (!actor) {
        cerr << "Error: Retrieved actor for \"" << name << "\" is nullptr.\n";
        return nullptr;
    }

    return actor;
}


/**
 * Find a movie by title.
 * Process: Searches for the movie in the movieMap.
 * Precondition: The movie's title must be provided.
 * Postcondition: Returns a pointer to the Movie if found, or nullptr otherwise.
 */
Movie* ActorMovieDatabase::findMovie(const string& title) const {
    return movieMap.contains(title) ? movieMap.get(title) : nullptr;
}


/**
 * Display all actors in the database.
 * Process: Iterates through the actorMap and prints actor details.
 * Precondition: None.
 * Postcondition: All actor details are printed to the console.
 */
void ActorMovieDatabase::displayActors() const {
   
    auto it = actorMap.createIterator();
    while (it->hasNext()) {
        Actor* actor = it->next()->value;
        cout << "Actor: " << actor->getName() << endl;
        actor->displayMovies();
    }
    delete it;
}


/**
 * Display actors within a specified age range
 * Process: Iterates through actorMap, add actors within age range to a list, sorts the list and displays it
 * Precondition: `x` and `y` must be valid integers where `x <= y` and actorMap must be populated with valid data, including each actor's birth year.
 * Postcondition: Outputs all actors within the specified age range in ascending order of age.
 */
void ActorMovieDatabase::displayActorsByAgeRange(int x, int y) const {
    int currentYear = time(nullptr) / (60 * 60 * 24 * 365.25) + 1970; // Approximate current year

    List<Actor*> actorsInRange;
    auto it = actorMap.createIterator();
    while (it->hasNext()) {
        Actor* actor = it->next()->value;
        int age = currentYear - actor->getBirthYear();
        if (age >= x && age <= y) {
            actorsInRange.add(actor);
        }
    }
    delete it;

    // Sort actorsInRange by age
    for (auto i = actorsInRange.createIterator(); i->hasNext();) {
        Actor* a = i->next();
        for (auto j = actorsInRange.createIterator(); j->hasNext();) {
            Actor* b = j->next();
            if ((currentYear - a->getBirthYear()) < (currentYear - b->getBirthYear())) {
                swap(a, b); // Swap actors to sort in ascending order
            }
        }
    }

    // Display sorted actors
    cout << "Actors aged between " << x << " and " << y << ":\n";
    for (auto it = actorsInRange.createIterator(); it->hasNext();) {
        Actor* actor = it->next();
        cout << actor->getName() << " (Age: " << currentYear - actor->getBirthYear() << ")\n";
    }
}

/**
 * Display Known Actors
 * Process: Find actor specificed, iterates through all movies in the database to check if the actor starred in them and identifies 
            all actors that are directly or indirectly connected (one level deep) to the given actor. It then displays all actors 
            that the given actor knows.
 * Precondition: `actorName` must be a valid string representing the name of an actor,`actorMap` and `movieMap` must be populated with 
                  valid data.
 * Postcondition: Outputs all actors that are directly or indirectly connected (one movie level deep) to the given actor.
 */
void ActorMovieDatabase::displayKnownActors(const string& actorName) const {
    Actor* targetActor = findActor(actorName);
    if (!targetActor) {
        cout << "Actor not found.\n";
        return;
    }
    cout << "Actor name is: " << targetActor->getName() << endl;

    List<Actor*> knownActors;

    // Add direct co-actors of the target actor
    addDirectCoActors(targetActor, knownActors);

    // Find indirect relations iteratively
    findIndirectRelations(targetActor, knownActors);

    // Display all known actors
    cout << "Actors known by " << actorName << ":\n";
    displayActorList(knownActors);
}


/**
 * Helper function to add direct co-actors of an actor to the knownActors list
 * Process: Iterates through all movies associated with the target actor, and for each movie, retrieves the list of co-actors and adds 
            them to the `knownActors` list.
 * Precondition: `targetActor` must be a valid `Actor` object with a non-empty list of associated movies and `knownActors` must be initialized
 * Postcondition: All direct co-actors of the target actor are added to the `knownActors` list with no duplicates
 */
void ActorMovieDatabase::addDirectCoActors(Actor* targetActor, List<Actor*>& knownActors) const {
    List<Movie*> movieList = targetActor->getMovies();
    auto movieIterator = movieList.createIterator();

    while (movieIterator->hasNext()) {
        Movie* movie = movieIterator->next();
        if (!movie) continue;

        List<Actor*> actorList = movie->getActors();
        auto actorIterator = actorList.createIterator();

        while (actorIterator->hasNext()) {
            Actor* coActor = actorIterator->next();
            if (!coActor || coActor == targetActor) continue;

            addUniqueActor(knownActors, coActor);
        }
        delete actorIterator;
    }
    delete movieIterator;
}


/**
 * Helper function to find indirect relations for a target actor
 * Process: Iteratively finds indirect relations of the target actor by retrieving associated movies each actor in the `knownActors` list.
            Then Checks each movie's list of actors and adds any new actors not already in the `knownActors` list.
 * Precondition: `targetActor` must be a valid `Actor` object and `knownActors` must already contain the target actor's direct co-actors (done by `addDirectCoActors`).
 * Postcondition: `knownActors` list contains all actors directly or indirectly related to the target actor.
 */
void ActorMovieDatabase::findIndirectRelations(Actor* targetActor, List<Actor*>& knownActors) const {
    bool addedNewActor;
    do {
        addedNewActor = false;

        auto knownActorIterator = knownActors.createIterator();
        while (knownActorIterator->hasNext()) {
            Actor* knownActor = knownActorIterator->next();
            if (!knownActor) continue;

            List<Movie*> knownActorMovies = knownActor->getMovies();
            auto movieIterator = knownActorMovies.createIterator();

            while (movieIterator->hasNext()) {
                Movie* movie = movieIterator->next();
                if (!movie) continue;

                List<Actor*> coActors = movie->getActors();
                auto coActorIterator = coActors.createIterator();

                while (coActorIterator->hasNext()) {
                    Actor* coActor = coActorIterator->next();
                    if (!coActor || coActor == targetActor || coActor == knownActor) continue;

                    if (addUniqueActor(knownActors, coActor)) {
                        addedNewActor = true;
                    }
                }
                delete coActorIterator;
            }
            delete movieIterator;
        }
        delete knownActorIterator;
    } while (addedNewActor);
}


/**
 * Helper function to add an actor to the list if it's not already present
 * Process: Checks if the given actor is already in the `knownActors` list and if the actor is not present, adds the actor to the list.
 * Precondition: `actor` must be a valid `Actor` object and `knownActors` must be initialized
 * Postcondition: If the actor was not already in the list, it is added to `knownActors`. Returns `true` if the actor was added, `false` otherwise.
 */
bool ActorMovieDatabase::addUniqueActor(List<Actor*>& knownActors, Actor* actor) const {
    auto iterator = knownActors.createIterator();
    while (iterator->hasNext()) {
        if (iterator->next() == actor) {
            delete iterator;
            return false; // Actor already exists in the list
        }
    }
    delete iterator;

    knownActors.add(actor);
    return true; // New actor added
}


/**
 * Helper function to display all actors in a list
 * Process: Iterates through the given list of actors and prints their names to the console.\
 * Precondition: `actorList` must be a valid `List<Actor*>` object and each actor in the list must be a valid `Actor` object with a valid name.
 * Postcondition: Outputs the names of all actors in the given list to the console.
 */
void ActorMovieDatabase::displayActorList(const List<Actor*>& actorList) const {
    auto iterator = actorList.createIterator();
    while (iterator->hasNext()) {
        Actor* actor = iterator->next();
        if (actor) {
            cout << actor->getName() << "\n";
        }
    }
    delete iterator;
}



/**
 * Display all movies in the database.
 * Process: Iterates through the movieMap and prints movie details.
 * Precondition: None.
 * Postcondition: All movie details are printed to the console.
 */
void ActorMovieDatabase::displayMovies() const {
    auto it = movieMap.createIterator();
    while (it->hasNext()) {
        Movie* movie = it->next()->value;
        cout << "Movie: " << movie->getTitle() << endl;
        /*movie->displayActors();*/
    }
    delete it;
}


/**
 * Clear the database.
 * Process: Deletes all dynamically allocated actors and movies and clears the maps.
 * Precondition: None.
 * Postcondition: The database is empty.
 */
void ActorMovieDatabase::clearDatabase() {
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        delete actorIt->next()->value;
    }
    delete actorIt;
    actorMap.clear();

    auto movieIt = movieMap.createIterator();
    while (movieIt->hasNext()) {
        delete movieIt->next()->value;
    }
    delete movieIt;
    movieMap.clear();
}




// Advanced Feature --------------------------------------------------------------------------------------------------------
void ActorMovieDatabase::buildGraph() {
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        Actor* actor = actorIt->next()->value;
        List<Movie*> movies = actor->getMovies();
        auto movieIt = movies.createIterator();
        while (movieIt->hasNext()) {
            Movie* movie = movieIt->next();
            actorMovieGraph.addEdge(actor->getName(), movie->getTitle());
        }
        delete movieIt;
    }
    delete actorIt;
}

void ActorMovieDatabase::exploreConnections(const string& node) {
    List<string>* connections = actorMovieGraph.getConnections(node);
    if (connections) {
        cout << "Connections for " << node << ":\n";
        auto it = connections->createIterator();
        while (it->hasNext()) {
            cout << "- " << it->next() << endl;
        }
        delete it;
    }
    else {
        cout << "No connections found for " << node << ".\n";
    }
}

void ActorMovieDatabase::recommendMovies(const string& actorName) {
    Actor* actor = findActor(actorName);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    List<Movie*> movies = actor->getMovies();
    Map<string, int> movieFrequency;

    auto movieIt = movies.createIterator();
    while (movieIt->hasNext()) {
        Movie* movie = movieIt->next();
        List<Actor*> actors = movie->getActors();
        auto actorIt = actors.createIterator();
        while (actorIt->hasNext()) {
            Actor* coActor = actorIt->next();
            if (coActor != actor) {
                List<Movie*> coActorMovies = coActor->getMovies();
                auto coMovieIt = coActorMovies.createIterator();
                while (coMovieIt->hasNext()) {
                    string title = coMovieIt->next()->getTitle();
                    if (!movieFrequency.contains(title)) {
                        movieFrequency.insert(title, 0);
                    }
                    movieFrequency.get(title)++;
                }
                delete coMovieIt;
            }
        }
        delete actorIt;
    }
    delete movieIt;

    cout << "Recommended Movies:\n";
    auto freqIt = movieFrequency.createIterator();
    while (freqIt->hasNext()) {
        auto pair = freqIt->next();
        cout << pair->key << " (" << pair->value << " co-actor connections)\n";
    }
    delete freqIt;
}

Graph& ActorMovieDatabase::getGraph() {
    return actorMovieGraph;
}

void ActorMovieDatabase::displayMindMap(const string& startNode) {
    List<string> visited; // Custom list to track visited nodes
    cout << "Mind Map for \"" << startNode << "\":\n";
    renderBranches(startNode, actorMovieGraph, visited, "", true); // Assume starting node is an actor
    cout << endl;
}
// Helper function
bool isVisited(const string& node, List<string>& visited) {
    auto it = visited.createIterator();
    while (it->hasNext()) {
        if (it->next() == node) {
            delete it;
            return true; // Node already visited
        }
    }
    delete it;
    return false; // Node not found in visited list
}
void ActorMovieDatabase::renderBranches(const string& node, Graph& graph, List<string>& visited, const string& prefix, bool isActor) {
    // Check if the node has already been visited
    if (isVisited(node, visited)) {
        return;
    }
    visited.add(node); // Mark the node as visited

    // Print the current node with proper indentation
    cout << prefix << (isActor ? "[Actor] " : "[Movie] ") << node << endl;

    // Get connections for the current node
    List<string>* connections = graph.getConnections(node);
    if (!connections) return;

    // Prepare for rendering children
    auto it = connections->createIterator();
    int count = 0;
    int totalConnections = connections->getSize();
    while (it->hasNext()) {
        string connection = it->next();
        bool isLast = (++count == totalConnections);

        // Branch formatting
        string newPrefix = prefix + (isLast ? "    " : "|   ");
        string branch = isLast ? " |__ " : "|-- ";

        // Recursive call
        renderBranches(connection, graph, visited, prefix + branch, !isActor);
    }
    delete it;
}

// Advanced Feature 2 ------------------------------------------------------------------------------------------------------
void ActorMovieDatabase::addUser(const string& username) {
    if (!userMap.contains(username)) {
        userMap.insert(username, new User(username));
    }
}

void ActorMovieDatabase::rateMovie(const string& username, const string& movieTitle, int rating) {
    if (userMap.contains(username) && movieMap.contains(movieTitle)) {
        userMap.get(username)->rateMovie(movieTitle, rating);
        updateMovieRating(movieTitle);
    }
}

void ActorMovieDatabase::updateMovieRating(const string& movieTitle) {
    auto movie = movieMap.get(movieTitle);
    float totalRating = 0;
    int count = 0;
    auto userIt = userMap.createIterator();
    while (userIt->hasNext()) {
        auto user = userIt->next()->value;
        int rating = user->getMovieRating(movieTitle);
        if (rating > 0) {
            totalRating += rating;
            count++;
        }
    }
    delete userIt;
    movie->setRating(count > 0 ? totalRating / count : 0.0);
}

void ActorMovieDatabase::addWatchedMovie(const string& username, const string& movieTitle) {
    if (!userMap.contains(username)) {
        cout << "User not found.\n";
        return;
    }
    if (!movieMap.contains(movieTitle)) {
        cout << "Movie not found.\n";
        return;
    }
    userMap.get(username)->addWatchedMovie(movieTitle);
    cout << "Movie \"" << movieTitle << "\" added to watched list for " << username << ".\n";
}

void ActorMovieDatabase::recommendPersonalisedMovies(const string& username) {
    if (!userMap.contains(username)) {
        cout << "User not found.\n";
        return;
    }
    User* user = userMap.get(username);
    List<string> watchedMovies = user->getWatchedMovies();
    Map<string, float> movieScores;

    auto movieIt = watchedMovies.createIterator();
    while (movieIt->hasNext()) {
        string watchedMovie = movieIt->next();
        if (!movieMap.contains(watchedMovie)) continue;
        auto movie = movieMap.get(watchedMovie);
        auto actors = movie->getActors();
        auto actorIt = actors.createIterator();
        while (actorIt->hasNext()) {
            string actorName = actorIt->next()->getName();
            if (!actorMap.contains(actorName)) continue;
            auto allMovies = actorMap.get(actorName)->getMovies();
            auto relatedMovieIt = allMovies.createIterator();
            while (relatedMovieIt->hasNext()) {
                string relatedMovie = relatedMovieIt->next()->getTitle();
                if (!watchedMovies.contains(relatedMovie) && movieMap.contains(relatedMovie)) {
                    if (!movieScores.contains(relatedMovie)) {
                        movieScores.insert(relatedMovie, 0.0);
                    }
                    movieScores.get(relatedMovie) += movieMap.get(relatedMovie)->getRating();
                }
            }
            delete relatedMovieIt;
        }
        delete actorIt;
    }
    delete movieIt;

    cout << "Recommended Movies for " << username << ":\n";
    if (movieScores.getSize() == 0) {
        cout << "No related movies found based on your watched list.\n";
        return;
    }

    // Store movie scores in a list for sorting
    List<pair<string, float>> sortedMovies;
    auto scoreIt = movieScores.createIterator();
    while (scoreIt->hasNext()) {
        auto pair = scoreIt->next();
        sortedMovies.add({ pair->key, pair->value });
    }
    delete scoreIt;

    // Sort movies by score in descending order
    sortedMovies.sort([](const pair<string, float>& a, const pair<string, float>& b) {
        return a.second > b.second;
        });

    // Print sorted movies
    auto sortedIt = sortedMovies.createIterator();
    while (sortedIt->hasNext()) {
        auto movie = sortedIt->next();
        cout << movie.first << " (Score: " << movie.second << ")\n";
    }
    delete sortedIt;
}

