#ifndef RIDE_H
#define RIDE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Ride{
    protected:
        int numTicketsNecessary;
        string name;
        bool heightRestricted;

    public:
        Ride();
        Ride(int, string, bool);
        Ride(const Ride&);

        int getNumTicketsNecessary();
        string getRideName();
        bool getHeightRestricted();

        void setNumTicketsNecessary(int);
        void setRideName(string);
        void setHeightRestricted(bool);
};

#endif