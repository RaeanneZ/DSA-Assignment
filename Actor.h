/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once
#include <string>
#include "List.h"

class Actor
{
private:
    string name;
    int birthYear;
    List<string> movies; // Movies the actor starred in

public:
    Actor(string name, int birthYear) : name(name), birthYear(birthYear) {}
};

