#ifndef PATRON_H
#define PATRON_H

#include "ride.h"

using namespace std;

#define MAX_RIDES 100

class Patron{
    string firstname;
    string lastname;
    int id;
    int rides;
    int tickets;
    Ride patronRides[MAX_RIDES];

    public:
        Patron();
        Patron(string, string, int, int, int, Ride*);
        //patronRides not in itemized constructor yet
        Patron(const Patron&);

        string getFirstName();
        string getLastName();
        int getPatronNumber();
        int getNumTickets();
        Ride* getPatronRides();
        void setFirstName(string);
        void setLastName(string);
        void setPatronNumber(int);
        void setNumTickets(int);
        void addPatronRide(Ride);
        void displayName();
        void displayPatronData();
};

#endif