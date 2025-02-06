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
    recentMovies.bubbleSort([](Movie* a, Movie* b) { return a->getReleaseYear() < b->getReleaseYear(); });

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
    movies.bubbleSort([](Movie* a, Movie* b) { return a->getTitle() < b->getTitle(); });

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
    actors.bubbleSort([](Actor* a, Actor* b) { return a->getName() < b->getName(); });

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
    actorsInRange.bubbleSort([currentYear](Actor* a, Actor* b) {
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

