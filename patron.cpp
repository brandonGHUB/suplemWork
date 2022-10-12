#include "patron.h"

#define MAX_RIDES 100

using namespace std;

Patron::Patron(){
    firstname = "";
    lastname = "";
    id = 0;
    tickets = 0;
    rides = 0;
    patronRides[MAX_RIDES];
}

Patron::Patron(string newfirstName, string newlastName, int newId, int numTickets, int numRides, Ride* newPatronRides){
    firstname = newfirstName;
    lastname = newlastName;
    id = newId;
    tickets = numTickets;
    rides = numRides;

    //rides array not implemented yet
    for(int i = 0; i < numRides; i++){
        patronRides[i] = newPatronRides[i];
    }
}

Patron::Patron(const Patron& old){
    firstname = old.firstname;
    lastname = old.lastname;
    id = old.id;
    tickets = old.tickets;
    rides = old.rides;
    for(int i = 0; i < old.rides; i++){
        patronRides[i] = old.patronRides[i];
    }
}

string Patron::getFirstName(){
    return firstname;
}

string Patron::getLastName(){
    return lastname;
}

int Patron::getPatronNumber(){
    return id;
}

int Patron::getNumTickets(){
    return tickets;
}

Ride* Patron::getPatronRides(){
    return patronRides;
}

void Patron::setFirstName(string newfirstName){
    firstname = newfirstName;
}

void Patron::setLastName(string newlastName){
    lastname = newlastName;
}

void Patron::setPatronNumber(int newId){
    id = newId;
}

void Patron::setNumTickets(int numtix){
    tickets = numtix;
}

void Patron::addPatronRide(Ride newRide){
    patronRides[rides] = newRide;
    rides++;
}

void Patron::displayName(){
    cout << firstname << " " << lastname << endl;
}

void Patron::displayPatronData(){
    cout << "Patron Data\nPatron Number: " << id << endl;
    cout << "Number of Tickets: " << tickets << endl;
    cout << "Number of Rides: " << rides << endl;
}
