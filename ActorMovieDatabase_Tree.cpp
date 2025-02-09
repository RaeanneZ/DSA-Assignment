#include "ActorMovieDatabase_Tree.h"
#include <iostream>
#include <ctime>

using namespace std;

/**
 * Constructor
 * Initializes an empty AVLTree-based database.
 */
ActorMovieDatabase_Tree::ActorMovieDatabase_Tree() {}

/**
 * Destructor
 * Clears all dynamically allocated memory.
 */
ActorMovieDatabase_Tree::~ActorMovieDatabase_Tree() { clearDatabase(); }

/**
 * Adds an actor to the AVLTree.
 */
void ActorMovieDatabase_Tree::addActor(const string& name, int birthYear) {
    if (!actorMap.contains(name)) {
        actorMap.insert(name, new Actor(name, birthYear));
    }
}

/**
 * Adds a movie to the AVLTree.
 */
void ActorMovieDatabase_Tree::addMovie(const string& title, const string& plot, int releaseYear) {
    if (!movieMap.contains(title)) {
        movieMap.insert(title, new Movie(title, plot, releaseYear));
    }
}

/**
 * Removes an actor from the database.
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
 * Removes a movie from the database.
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
 * Displays all actors.
 */
void ActorMovieDatabase_Tree::displayActors() const {
    auto it = actorMap.createIterator();
    while (it->hasNext()) {
        cout << it->next().first << endl;
    }
    delete it;
}

/**
 * Displays actors within a specified age range (sorted by age).
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
 * Finds indirect relations (co-actors of co-actors).
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
 * Adds an actor to the list if not already present.
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
 * Displays all actors in a list.
 */
void ActorMovieDatabase_Tree::displayActorList(const List<Actor*>& actorList) const {
    auto it = actorList.createIterator();
    while (it->hasNext()) {
        cout << it->next()->getName() << endl;
    }
    delete it;
}

/**
 * Adds direct co-actors of an actor to the knownActors list.
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
 * Displays all movies.
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
 */
Actor* ActorMovieDatabase_Tree::findActor(const string& name) const {
    return actorMap.contains(name) ? actorMap.get(name) : nullptr;
}

/**
 * Finds a movie in the AVLTree.
 */
Movie* ActorMovieDatabase_Tree::findMovie(const string& title) const {
    return movieMap.contains(title) ? movieMap.get(title) : nullptr;
}

/**
 * Clears the database.
 */
void ActorMovieDatabase_Tree::clearDatabase() {
    actorMap.clear();
    movieMap.clear();
    userMap.clear();
}

// Advanced Test Feature ---------------------------------------------------------------------------------------------------
bool testIsVisited(const string& node, AVLTree<string, bool>& visited) {
    return visited.contains(node);
}

void ActorMovieDatabase_Tree::buildConnections() {
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        Actor* actor = actorIt->next().second;
        List<Movie*> movies = actor->getMovies();
        auto movieIt = movies.createIterator();

        while (movieIt->hasNext()) {
            Movie* movie = movieIt->next();

            // Ensure actor entry exists
            if (!actorMovieConnections.contains(actor->getName())) {
                actorMovieConnections.insert(actor->getName(), new AVLTree<string, bool>());
            }
            actorMovieConnections.get(actor->getName())->insert(movie->getTitle(), true);

            // Ensure movie entry exists
            if (!actorMovieConnections.contains(movie->getTitle())) {
                actorMovieConnections.insert(movie->getTitle(), new AVLTree<string, bool>());
            }
            actorMovieConnections.get(movie->getTitle())->insert(actor->getName(), true);
        }
        delete movieIt;
    }
    delete actorIt;
}
void ActorMovieDatabase_Tree::testRenderBranches(const string& node,
    AVLTree<string, AVLTree<string, bool>*>& connections,
    AVLTree<string, bool>& visited,
    const string& prefix,
    bool isActor) {
    if (testIsVisited(node, visited)) return;

    visited.insert(node, true); // Mark node as visited
    cout << prefix << (isActor ? "[Actor] " : "[Movie] ") << node << endl;

    if (!connections.contains(node)) return;

    AVLTree<string, bool>* relatedNodes = connections.get(node);
    auto it = relatedNodes->createIterator();
    int count = 0;
    int totalConnections = relatedNodes->getSize();

    while (it->hasNext()) {
        string connection = it->next().first;
        bool isLast = (++count == totalConnections);

        string newPrefix = prefix + (isLast ? "    " : "|   ");
        string branch = isLast ? "|__ " : "|-- ";

        testRenderBranches(connection, connections, visited, prefix + branch, !isActor);
    }
    delete it;
}

void ActorMovieDatabase_Tree::testDisplayMindMap(const string& startNode) {
    AVLTree<string, bool> visited; // Custom AVLTree to track visited nodes
    cout << "Mind Map for \"" << startNode << "\":\n";
    testRenderBranches(startNode, actorMovieConnections, visited, "", true);
    cout << endl;
}


// Advanced Feature --------------------------------------------------------------------------------------------------------
void ActorMovieDatabase_Tree::buildGraph() {
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        auto pair = actorIt->next();  // Get pair<string, Actor*>
        Actor* actor = pair.second;   // Extract Actor* correctly
        List<Movie*> movies = actor->getMovies();


        auto movieIt = movies.createIterator();
        while (movieIt->hasNext()) {
            Movie* movie = movieIt->next();
            cout << "Adding edge: " << actor->getName() << " -> " << movie->getTitle() << endl;
            actorMovieGraph.addEdge("Actor:" + actor->getName(), "Movie:" + movie->getTitle());
            actorMovieGraph.addEdge("Movie:" + movie->getTitle(), "Actor:" + actor->getName());
        }
        delete movieIt;
    }
    delete actorIt;
}

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

Graph& ActorMovieDatabase_Tree::getGraph() {
    return actorMovieGraph;
}

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
void ActorMovieDatabase_Tree::displayMostInfluentialActor() {
    string actor = actorMovieGraph.findMostInfluentialActor();
    cout << "The Most Influential Actor is: " << actor << endl;
}

// Testing
string ActorMovieDatabase_Tree::findMostInfluentialActorWithMap() {
    Map<string, int> actorConnections;

    // Populate map with degree centrality (connections)
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        auto actorPair = actorIt->next();
        Actor* actor = actorPair.second;
        string actorName = actor->getName();

        actorConnections.insert(actorName, actor->getMovies().getSize());
    }
    delete actorIt;

    // Find the actor with the highest connections
    string mostInfluentialActor;
    int maxConnections = -1;
    auto connIt = actorConnections.createIterator();
    while (connIt->hasNext()) {
        auto pair = connIt->next();
        if (pair->value > maxConnections) {
            maxConnections = pair->value;
            mostInfluentialActor = pair->key;
        }
    }
    delete connIt;

    return mostInfluentialActor;
}

string ActorMovieDatabase_Tree::findMostInfluentialActorWithList() {
    List<pair<string, int>> actorConnections;

    // Populate list with degree centrality (connections)
    auto actorIt = actorMap.createIterator();
    while (actorIt->hasNext()) {
        auto actorPair = actorIt->next();
        Actor* actor = actorPair.second;
        string actorName = actor->getName();

        // Add actor and their connection count to the list
        actorConnections.add(make_pair(actorName, actor->getMovies().getSize()));
    }
    delete actorIt;

    // Find the actor with the highest connections
    string mostInfluentialActor;
    int maxConnections = -1;

    auto connIt = actorConnections.createIterator();
    while (connIt->hasNext()) {
        auto pair = connIt->next();
        if (pair.second > maxConnections) {
            maxConnections = pair.second;
            mostInfluentialActor = pair.first;
        }
    }
    delete connIt;

    return mostInfluentialActor;
}

// Advanced Feature: Personalized Movie Recommendation & Rating System --------------------------------------------------
/**
 * Adds a user.
 */
void ActorMovieDatabase_Tree::addUser(const string& username) {
    if (!userMap.contains(username)) {
        userMap.insert(username, new User(username));
    }
}

/**
 * Rates a movie.
 */
void ActorMovieDatabase_Tree::rateMovie(const string& username, const string& movieTitle, int rating) {
    if (userMap.contains(username) && movieMap.contains(movieTitle)) {
        userMap.get(username)->rateMovie(movieTitle, rating);
    }
}

/**
 * Adds a watched movie.
 */
void ActorMovieDatabase_Tree::addWatchedMovie(const string& username, const string& movieTitle) {
    if (userMap.contains(username) && movieMap.contains(movieTitle)) {
        userMap.get(username)->addWatchedMovie(movieTitle);
    }
}

/**
 * Updates a movie's average rating.
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
 * Recommends personalized movies based on watched history.
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