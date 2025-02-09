/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "ActorMovieDatabase_Tree.h"
#include <iostream>
#include <ctime>

using namespace std;

/**
 * Constructor
 * Process: Initializes an empty AVLTree-based database for actors, movies, and users.
 * Precondition: None.
 * Postcondition: A new ActorMovieDatabase_Tree object is created with empty AVL trees.
 */
ActorMovieDatabase_Tree::ActorMovieDatabase_Tree() {}

/**
 * Destructor
 * Process: Clears all dynamically allocated memory by calling `clearDatabase()`.
 * Precondition: None.
 * Postcondition: All allocated objects are deleted, and the AVL trees are emptied.
 */
ActorMovieDatabase_Tree::~ActorMovieDatabase_Tree() { clearDatabase(); }

// Admin Menu ------------------------------------------------------------------------------------------------------------------------
/**
 * Adds an actor to the AVLTree.
 * Process: Checks if the actor does not already exist. If not, creates a new Actor object and inserts it into the `actorMap`.
 * Precondition: `name` must be a valid, non-empty string, and `birthYear` must be a positive integer.
 * Postcondition: A new Actor object is added to the `actorMap`, unless the actor already exists.
 */
void ActorMovieDatabase_Tree::addActor(const string& name, int birthYear) {
    if (!actorMap.contains(name)) {
        actorMap.insert(name, new Actor(name, birthYear));
    }
}

/**
 * Adds a movie to the AVLTree.
 * Process: Checks if the movie does not already exist. If not, creates a new Movie object and inserts it into the `movieMap`.
 * Precondition: `title` must be a valid, non-empty string, `plot` must be a valid string, and `releaseYear` must be a positive integer.
 * Postcondition: A new Movie object is added to the `movieMap`, unless the movie already exists.
 */
void ActorMovieDatabase_Tree::addMovie(const string& title, const string& plot, int releaseYear) {
    if (!movieMap.contains(title)) {
        movieMap.insert(title, new Movie(title, plot, releaseYear));
    }
}

/**
 * Updates an actor's details.
 * Process: Checks if the actor exists. If found, removes the old entry, updates the details, and reinserts the actor.
 * Precondition: `actorName` must exist in `actorMap`. `newName` must be a valid string. `newBirthYear` must be a positive integer.
 * Postcondition: The actor's details are updated, and the `actorMap` reflects the new details.
 */
void ActorMovieDatabase_Tree::updateActorDetails(const string& actorName, const string& newName, int newBirthYear) {
    if (!actorMap.contains(actorName)) {
        cout << "Actor not found.\n";
        return;
    }

    Actor* actor = actorMap.get(actorName);
    actorMap.remove(actorName);

    actor->setName(newName);
    if (newBirthYear > 0) actor->setBirthYear(newBirthYear);

    actorMap.insert(newName, actor);
}

/**
 * Updates a movie's details.
 * Process: Checks if the movie exists. If found, removes the old entry, updates the details, and reinserts the movie.
 * Precondition: `movieTitle` must exist in `movieMap`. `newTitle` must be a valid string. `newYear` must be a positive integer.
 * Postcondition: The movie's details are updated, and the `movieMap` reflects the new details.
 */
void ActorMovieDatabase_Tree::updateMovieDetails(const string& movieTitle, const string& newTitle, int newYear) {
    if (!movieMap.contains(movieTitle)) {
        cout << "Movie not found.\n";
        return;
    }

    Movie* movie = movieMap.get(movieTitle);
    movieMap.remove(movieTitle);

    movie->setTitle(newTitle);
    if (newYear > 0) movie->setReleaseYear(newYear);

    movieMap.insert(newTitle, movie);
}

/**
 * Displays movies from the last 3 years in ascending order.
 * Process: Iterates through `movieMap`, filters movies based on release year, sorts them, and prints the results.
 * Precondition: The database must be populated with movies.
 * Postcondition: Movies from the past 3 years are displayed in ascending order.
 */
void ActorMovieDatabase_Tree::displayRecentMovies() const {
    int currentYear = time(nullptr) / (60 * 60 * 24 * 365.25) + 1970;

    List<Movie*> recentMovies;
    auto it = movieMap.createIterator();
    while (it->hasNext()) {
        auto pair = it->next();
        if (pair.second->getReleaseYear() >= currentYear - 3) {
            recentMovies.add(pair.second);
        }
    }
    delete it;

    // Sort movies by release year
    recentMovies.sort([](Movie* a, Movie* b) { return a->getReleaseYear() < b->getReleaseYear(); });

    // Display movies
    auto movieIt = recentMovies.createIterator();
    while (movieIt->hasNext()) {
        Movie* movie = movieIt->next();
        cout << movie->getTitle() << " (" << movie->getReleaseYear() << ")\n";
    }
    delete movieIt;
}

/**
 * Displays all movies an actor has starred in (alphabetical order).
 * Process: Retrieves the actor's movie list, sorts it alphabetically, and prints it.
 * Precondition: `actorName` must exist in `actorMap`.
 * Postcondition: The actor's movies are displayed in alphabetical order.
 */
void ActorMovieDatabase_Tree::displayMoviesForActor(const string& actorName) const {
    if (!actorMap.contains(actorName)) {
        cout << "Actor not found.\n";
        return;
    }

    Actor* actor = actorMap.get(actorName);
    List<Movie*> movies = actor->getMovies();

    // Sort alphabetically
    movies.sort([](Movie* a, Movie* b) { return a->getTitle() < b->getTitle(); });

    auto it = movies.createIterator();
    while (it->hasNext()) {
        cout << it->next()->getTitle() << endl;
    }
    delete it;
}

/**
 * Displays all actors in a movie (alphabetical order).
 * Process: Retrieves the movie's actor list, sorts it alphabetically, and prints it.
 * Precondition: `movieTitle` must exist in `movieMap`.
 * Postcondition: The movie's actors are displayed in alphabetical order.
 */
void ActorMovieDatabase_Tree::displayActorsInMovie(const string& movieTitle) const {
    if (!movieMap.contains(movieTitle)) {
        cout << "Movie not found.\n";
        return;
    }

    Movie* movie = movieMap.get(movieTitle);
    List<Actor*> actors = movie->getActors();

    // Sort alphabetically
    actors.sort([](Actor* a, Actor* b) { return a->getName() < b->getName(); });

    auto it = actors.createIterator();
    while (it->hasNext()) {
        cout << it->next()->getName() << endl;
    }
    delete it;
}

/**
 * Associates an actor with a movie.
 * Process: Checks if both actor and movie exist, then links them in both directions.
 * Precondition: `actorName` and `movieTitle` must exist in `actorMap` and `movieMap`, respectively.
 * Postcondition: The actor is linked to the movie, and vice versa.
 */
void ActorMovieDatabase_Tree::associateActorWithMovie(const string& actorName, const string& movieTitle) {
    if (!actorMap.contains(actorName) || !movieMap.contains(movieTitle)) {
        cout << "Actor or Movie not found.\n";
        return;
    }

    Actor* actor = actorMap.get(actorName);
    Movie* movie = movieMap.get(movieTitle);

    actor->addMovieToActor(movie);
    movie->addActorToMovie(actor);
}

/**
 * Displays all actors in the database.
 * Process: Iterates through `actorMap` and prints each actor's name.
 * Precondition: None.
 * Postcondition: All actor names are displayed.
 */
void ActorMovieDatabase_Tree::displayActors() const {
    auto it = actorMap.createIterator();
    while (it->hasNext()) {
        cout << it->next().first << endl;
    }
    delete it;
}

// User Menu ----------------------------------------------------------------------------------------------------------------------
/**
 * Displays actors within a specified age range (sorted by age).
 * Process: Filters actors by birth year, sorts them by age, and prints them.
 * Precondition: `x` and `y` must be valid integers where `x <= y`.
 * Postcondition: Actors within the specified age range are displayed in ascending order of age.
 */
void ActorMovieDatabase_Tree::displayActorsByAgeRange(int x, int y) const {
    int currentYear = time(nullptr) / (60 * 60 * 24 * 365.25) + 1970;

    List<Actor*> actorsInRange;
    auto it = actorMap.createIterator();
    while (it->hasNext()) {
        Actor* actor = it->next().second;
        int age = currentYear - actor->getBirthYear();
        if (age >= x && age <= y) {
            actorsInRange.add(actor);
        }
    }
    delete it;

    // Sort actors by age
    actorsInRange.sort([currentYear](Actor* a, Actor* b) {
        return (currentYear - a->getBirthYear()) < (currentYear - b->getBirthYear());
        });

    // Display sorted actors
    auto actorIt = actorsInRange.createIterator();
    while (actorIt->hasNext()) {
        Actor* actor = actorIt->next();
        cout << actor->getName() << " (Age: " << (currentYear - actor->getBirthYear()) << ")\n";
    }
    delete actorIt;
}

/**
 * Displays all known actors of a particular actor.
 * Process: Finds the target actor's co-actors and co-actors of co-actors, then prints them.
 * Precondition: `actorName` must exist in `actorMap`.
 * Postcondition: The known actors are displayed.
 */
void ActorMovieDatabase_Tree::displayKnownActors(const string& actorName) const {
    if (!actorMap.contains(actorName)) {
        cout << "Actor not found.\n";
        return;
    }

    Actor* targetActor = actorMap.get(actorName);
    List<Actor*> knownActors;

    addDirectCoActors(targetActor, knownActors);
    findIndirectRelations(targetActor, knownActors);

    cout << "Actors known by " << actorName << ":\n";
    displayActorList(knownActors);
}

/**
 * Finds indirect co-actors (co-actors of co-actors).
 * Process: Iterates through the movies of known co-actors to find new co-actors and adds them to `knownActors`.
 * Precondition: `targetActor` must be a valid `Actor` object, and `knownActors` must already contain direct co-actors.
 * Postcondition: `knownActors` is updated with all indirect connections (one level deep).
 */
void ActorMovieDatabase_Tree::findIndirectRelations(Actor* targetActor, List<Actor*>& knownActors) const {
    bool addedNewActor;
    do {
        addedNewActor = false;
        auto knownActorIt = knownActors.createIterator();
        while (knownActorIt->hasNext()) {
            Actor* knownActor = knownActorIt->next();
            List<Movie*> knownMovies = knownActor->getMovies();
            auto movieIt = knownMovies.createIterator();
            while (movieIt->hasNext()) {
                Movie* movie = movieIt->next();
                List<Actor*> coActors = movie->getActors();
                auto coActorIt = coActors.createIterator();
                while (coActorIt->hasNext()) {
                    Actor* coActor = coActorIt->next();
                    if (coActor != targetActor && addUniqueActor(knownActors, coActor)) {
                        addedNewActor = true;
                    }
                }
                delete coActorIt;
            }
            delete movieIt;
        }
        delete knownActorIt;
    } while (addedNewActor);
}

/**
 * Adds an actor to a list if they are not already present.
 * Process: Iterates through `knownActors` to check for duplicates before adding a new actor.
 * Precondition: `actor` must be a valid `Actor` object, and `knownActors` must be an initialized list.
 * Postcondition: If `actor` was not already in `knownActors`, it is added.
 */
bool ActorMovieDatabase_Tree::addUniqueActor(List<Actor*>& knownActors, Actor* actor) const {
    auto it = knownActors.createIterator();
    while (it->hasNext()) {
        if (it->next() == actor) {
            delete it;
            return false;
        }
    }
    delete it;
    knownActors.add(actor);
    return true;
}

/**
 * Displays all actors in a given list.
 * Process: Iterates through `actorList` and prints each actor's name.
 * Precondition: `actorList` must be an initialized list containing valid `Actor` objects.
 * Postcondition: The names of all actors in `actorList` are printed.
 */
void ActorMovieDatabase_Tree::displayActorList(const List<Actor*>& actorList) const {
    auto it = actorList.createIterator();
    while (it->hasNext()) {
        cout << it->next()->getName() << endl;
    }
    delete it;
}

/**
 * Adds direct co-actors of an actor to a list.
 * Process: Retrieves movies associated with `targetActor`, finds co-actors, and adds them to `knownActors`.
 * Precondition: `targetActor` must be a valid `Actor` object, and `knownActors` must be an initialized list.
 * Postcondition: All direct co-actors of `targetActor` are added to `knownActors`.
 */
void ActorMovieDatabase_Tree::addDirectCoActors(Actor* targetActor, List<Actor*>& knownActors) const {
    List<Movie*> movies = targetActor->getMovies();
    auto movieIt = movies.createIterator();
    while (movieIt->hasNext()) {
        Movie* movie = movieIt->next();
        List<Actor*> coActors = movie->getActors();
        auto actorIt = coActors.createIterator();
        while (actorIt->hasNext()) {
            Actor* coActor = actorIt->next();
            if (coActor != targetActor) {
                addUniqueActor(knownActors, coActor);
            }
        }
        delete actorIt;
    }
    delete movieIt;
}

/**
 * Displays all movies in the database.
 * Process: Iterates through `movieMap` and prints each movie title.
 * Precondition: The database must contain at least one movie.
 * Postcondition: All movie titles are printed to the console.
 */
void ActorMovieDatabase_Tree::displayMovies() const {
    auto it = movieMap.createIterator();
    while (it->hasNext()) {
        cout << it->next().first << endl;
    }
    delete it;
}

/**
 * Finds an actor in the AVLTree.
 * Process: Searches for the actor in `actorMap` and returns a pointer if found.
 * Precondition: `name` must be a valid string.
 * Postcondition: Returns the actor if found, otherwise returns `nullptr`.
 */
Actor* ActorMovieDatabase_Tree::findActor(const string& name) const {
    return actorMap.contains(name) ? actorMap.get(name) : nullptr;
}

/**
 * Finds a movie in the AVLTree.
 * Process: Searches for the movie in `movieMap` and returns a pointer if found.
 * Precondition: `title` must be a valid string.
 * Postcondition: Returns the movie if found, otherwise returns `nullptr`.
 */
Movie* ActorMovieDatabase_Tree::findMovie(const string& title) const {
    return movieMap.contains(title) ? movieMap.get(title) : nullptr;
}

/**
 * Clears the database.
 * Process: Deletes all dynamically allocated actors, movies, and users, and clears the AVL trees.
 * Precondition: None.
 * Postcondition: The database is emptied.
 */
void ActorMovieDatabase_Tree::clearDatabase() {
    actorMap.clear();
    movieMap.clear();
    userMap.clear();
}

// Advanced Feature --------------------------------------------------------------------------------------------------------
/**
 * Constructs a bidirectional graph for actors and movies.
 * Process: Iterates through actors and movies, establishing edges between them.
 * Precondition: `actorMap` and `movieMap` must be populated.
 * Postcondition: `actorMovieGraph` is populated with connections.
 */
void ActorMovieDatabase_Tree::buildGraph() {
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        auto pair = actorIt->next();  // Get pair<string, Actor*>
        Actor* actor = pair.second;   // Extract Actor* correctly
        List<Movie*> movies = actor->getMovies();


        auto movieIt = movies.createIterator();
        while (movieIt->hasNext()) {
            Movie* movie = movieIt->next();
            actorMovieGraph.addEdge("Actor:" + actor->getName(), "Movie:" + movie->getTitle());
            actorMovieGraph.addEdge("Movie:" + movie->getTitle(), "Actor:" + actor->getName());
        }
        delete movieIt;
    }
    delete actorIt;
}

/**
 * Recommends movies based on an actor's co-actors.
 * Process: Finds all movies the actor starred in, retrieves co-actors, and counts the number of shared movies.
 * Precondition: `actorName` must exist in `actorMap`.
 * Postcondition: A list of recommended movies is displayed based on actor relationships.
 */
void ActorMovieDatabase_Tree::recommendMovies(const string& actorName) {
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

/**
 * Retrieves the actor-movie graph.
 * Process: Returns a reference to the `actorMovieGraph`.
 * Precondition: The graph must be initialized.
 * Postcondition: A reference to `actorMovieGraph` is returned.
 */
Graph& ActorMovieDatabase_Tree::getGraph() {
    return actorMovieGraph;
}

/**
 * Displays a mind map of actor-movie connections.
 * Process: Determines whether the `startNode` is an actor or movie, then calls `renderBranches` to visualize relationships.
 * Precondition: `startNode` must exist in `actorMap` or `movieMap`.
 * Postcondition: A hierarchical view of actor-movie relationships is printed.
 */
void ActorMovieDatabase_Tree::displayMindMap(const string& startNode) {
    // Add prefix to match how nodes are stored in the graph
    string prefixedNode;
    if (actorMap.contains(startNode)) {
        prefixedNode = "Actor:" + startNode;
    }
    else if (movieMap.contains(startNode)) {
        prefixedNode = "Movie:" + startNode;
    }
    else {
        cout << "No such actor or movie found.\n";
        return;
    }

    List<string> visited;
    cout << "Mind Map for \"" << startNode << "\":\n";
    renderBranches(prefixedNode, actorMovieGraph, visited, "");
    cout << endl;
}

// Helper function
/**
 * Checks if a node has already been visited.
 * Process: Iterates through the `visited` list to determine if the node is present.
 * Precondition: `node` must be a valid string, and `visited` must be an initialized `List<string>`.
 * Postcondition: Returns `true` if the node has been visited; otherwise, returns `false`.
 */
static bool isVisited(const string& node, List<string>& visited) {
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

/**
 * Recursively renders the branches of the mind map.
 * Process: Uses recursive traversal to display actor-movie relationships in a hierarchical format.
 * Precondition: The `graph` should contain valid connections, and `visited` should track visited nodes.
 * Postcondition: The hierarchical structure is printed, showing relationships between actors and movies.
 */
void ActorMovieDatabase_Tree::renderBranches(const string& node, Graph& graph, List<string>& visited, const string& prefix) {
    // Check if the node has already been visited
    if (isVisited(node, visited)) {
        return;
    }
    visited.add(node); // Mark the node as visited

    // Determine if it's an actor or movie based on prefix
    bool isActor = node.find("Actor:") == 0;
    string cleanNodeName = isActor ? node.substr(6) : node.substr(6);

    // Print the current node with proper indentation
    cout << prefix << (isActor ? "[Actor] " : "[Movie] ") << cleanNodeName << endl;

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
        renderBranches(connection, graph, visited, prefix + branch);
    }
    delete it;
}


// Advanced Feature: Find Most Popular Actor ----------------------------------------------------------------------------------------------
/**
 * Displays the most influential actor based on the number of movie connections.
 * Process: Uses the `findMostInfluentialActor` function of the `actorMovieGraph` to determine and print the actor.
 * Precondition: The graph should be built with actor-movie connections.
 * Postcondition: Prints the most influential actor.
 */
void ActorMovieDatabase_Tree::displayMostInfluentialActor() {
    string actor = actorMovieGraph.findMostInfluentialActor();
    cout << "The Most Influential Actor is: " << actor << endl;
}


// Advanced Feature: Personalized Movie Recommendation & Rating System --------------------------------------------------
/**
 * Adds a new user to the database.
 * Process: Checks if the user does not already exist in `userMap`. If not, a new User object is created and inserted.
 * Precondition: `username` must be a valid, non-empty string.
 * Postcondition: A new User object is added to `userMap`, unless the user already exists.
 */
void ActorMovieDatabase_Tree::addUser(const string& username) {
    if (!userMap.contains(username)) {
        userMap.insert(username, new User(username));
    }
}

/**
 * Allows a user to rate a movie.
 * Process: Stores the rating in the user's record and updates the movie's average rating.
 * Precondition: `username` and `movieTitle` must exist in `userMap` and `movieMap`, respectively.
 * Postcondition: The user's rating is recorded, and the movie's average rating is updated.
 */
void ActorMovieDatabase_Tree::rateMovie(const string& username, const string& movieTitle, int rating) {
    if (userMap.contains(username) && movieMap.contains(movieTitle)) {
        userMap.get(username)->rateMovie(movieTitle, rating);
    }
}

/**
 * Adds a watched movie to a user's record.
 * Process: Checks if both the user and movie exist in the database. If valid, the movie is added to the user's watched list.
 * Precondition: `username` must exist in `userMap`, and `movieTitle` must exist in `movieMap`.
 * Postcondition: The specified movie is added to the user's watched movie list.
 */
void ActorMovieDatabase_Tree::addWatchedMovie(const string& username, const string& movieTitle) {
    if (userMap.contains(username) && movieMap.contains(movieTitle)) {
        userMap.get(username)->addWatchedMovie(movieTitle);
    }
}

/**
 * Updates the average rating of a movie based on user ratings.
 * Process: Iterates through all users, calculates the average rating, and updates the movie record.
 * Precondition: The movie must exist in `movieMap`.
 * Postcondition: The movie's rating is updated based on user feedback.
 */
void ActorMovieDatabase_Tree::updateMovieRating(const string& movieTitle) {
    if (!movieMap.contains(movieTitle)) return;
    auto movie = movieMap.get(movieTitle);
    float totalRating = 0;
    int count = 0;
    auto userIt = userMap.createIterator();
    while (userIt->hasNext()) {
        auto user = userIt->next().second;
        int rating = user->getMovieRating(movieTitle);
        if (rating > 0) {
            totalRating += rating;
            count++;
        }
    }
    delete userIt;
    movie->setRating(count > 0 ? totalRating / count : 0.0);
}

/**
 * Recommends personalized movies for a user based on watched history.
 * Process: Analyzes watched movies, finds associated actors, and recommends movies based on those actors.
 * Precondition: `username` must exist in `userMap`, and the user must have watched at least one movie.
 * Postcondition: Prints a list of recommended movies sorted by relevance.
 */
void ActorMovieDatabase_Tree::recommendPersonalisedMovies(const string& username) {
    if (!userMap.contains(username)) {
        cout << "User not found.\n";
        return;
    }
    User* user = userMap.get(username);
    List<string> watchedMovies = user->getWatchedMovies();
    AVLTree<string, float> movieScores;

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
        sortedMovies.add({ pair.first, pair.second }); // Use std::pair
    }
    delete scoreIt;

    // Sort movies by score in descending order
    sortedMovies.quickSort([](const pair<string, float>& a, const pair<string, float>& b) {
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