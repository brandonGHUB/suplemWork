#include "ride.h"

//not used in driver functionality yet

Ride::Ride(){
    numTicketsNecessary = 0;
    name = "";
    heightRestricted = false;
}

Ride::Ride(int numRideTickets, string newName, bool height){
    numTicketsNecessary = numRideTickets;
    name = newName;
    heightRestricted = height;
}

Ride::Ride(const Ride& old){
    numTicketsNecessary = old.numTicketsNecessary;
    name = old.name;
    heightRestricted = old.heightRestricted;
}

int Ride::getNumTicketsNecessary(){
    return numTicketsNecessary;
}

string Ride::getRideName(){
    return name;
}

bool Ride::getHeightRestricted(){
    return heightRestricted;
}

void Ride::setNumTicketsNecessary(int tix){
    numTicketsNecessary = tix;
}

void Ride::setRideName(string newrideName){
    name = newrideName;
}

void Ride::setHeightRestricted(bool height){
    heightRestricted = height;
}