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