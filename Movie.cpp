/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "Movie.h"

Movie::Movie(string title, string plot, int releaseYear) : title(title), plot(plot), releaseYear(releaseYear) {}

string Movie::getTitle() {
	return title;
}

void Movie::setTitle(string title) {
	this->title = title;
}

string Movie::getPlot() {
	return plot;
}

void Movie::setPlot(string plot) {
	this->plot = plot;
}

int Movie::getReleaseYear() {
	return releaseYear;
}

void Movie::setReleaseYear(int year) {
	this->releaseYear = year;
}

void Movie::addActorToMovie(Actor actor) {
	actors.add(actor);
}

void Movie::sortActors() {
	// This needs to have multiple sorting algorithms
}

void Movie::displayActors() {
	
}