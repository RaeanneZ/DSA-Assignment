#include "Actor.h"

Actor::Actor(string name, int birthYear) : name(name), birthYear(birthYear) {}

string Actor::getName() {
	return name;
}
void Actor::setName(string name) {
	this->name = name;
}

int Actor::getBirthYear() {
	return birthYear;
}
void Actor::setBirthYear(int year) {
	this->birthYear = year;
}