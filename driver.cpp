/*
Name(s): Brandon Ramirez and Adam Davis
Project: Amusement Park System
Class: CS202
*/

#include "patron.h"
#include "Teacups.h"
#include "MagicCarpet.h"
#include "WorldTour.h"

#define MAX_PATRONS 300
#define MAX_RIDES 100
#define NUM_ARGS 2

using namespace std;

// menu declarations
void displayPatrons(Patron[], int);
int getPatronOption(Patron[], int numPatrons);
void displayMenuOption();
int getMenuOption();
void displayModOptions();
int getModOption();


//patron declarations
void addPatron(Patron[], Patron, int*);
void removePatron(Patron[], int, int*);
void modifyPatron(Patron*);
Patron createNewPatron();

//patron modifier declarations
void addTickets(Patron*);
void addRide(Patron*);
void editName(Patron*);


//file declarations
void overwriteFile(Patron[], string, int);
int readExistingPatrons(Patron[], string);
void printFileNotFound();

//initialize input variable to value not found in menu to maintain while loop functionality
int main(int argc, char* argv[]){
    if(argc < NUM_ARGS){ // Check File Input
        std::cout << "Incorrect Usage!" << std::endl;
        std::cout << "Usage: "  << argv[0] << " [argument (file name)]" << std::endl;
        return -1;
    }
    else{
        fstream inFile;
        inFile.open(argv[1]);
        if(!inFile){
            printFileNotFound();
            return 0;
        }
        inFile.close();
    }

    Patron patrons[MAX_PATRONS];
    Ride rides[MAX_RIDES];
    int arraysize = readExistingPatrons(patrons, argv[1]);


bool menu = true;
while(menu){

    displayMenuOption();

    int input = getMenuOption();

    switch(input){
        case 0: // exit break case
        {
            menu = false;
            break;
        }

        case 1: // add patron
        {
            addPatron(patrons, createNewPatron(), &arraysize);
            overwriteFile(patrons, argv[1], arraysize);
            break;
        }

        case 2: // remove patron
        {
            std::cout << "Enter the number of the patron you'd like to remove" << std::endl;
            int patronNumberChosen = getPatronOption(patrons, arraysize) - 1;
            removePatron(patrons, patronNumberChosen, &arraysize);
            overwriteFile(patrons, argv[1], arraysize);
            break;
        }

        case 3: // modify patron
        {
            std::cout << "Enter the number of the patron you'd like to modify" << std::endl;
            int patronNumberChosen = getPatronOption(patrons, arraysize) - 1;
            modifyPatron(&patrons[patronNumberChosen]);
            overwriteFile(patrons, argv[1], arraysize);
            break;
        }

        case 4: // view patron
        {
            std::cout << "Enter the number of the patron you'd like to view." << std::endl;
            int patronNumberChosen = getPatronOption(patrons, arraysize) - 1;
            patrons[patronNumberChosen].displayPatronData();
            break;
        }

        default: // nonstandard input
            std::cout << "Invalid Input!" << std::endl;
            break;
        }
    }



    return 0;
}

void displayMenuOption(){
    std::cout << "Menu Options\n1. Add Patron" << std::endl;
    std::cout << "2. Remove Patron" << std::endl;
    std::cout << "3. Modify Patron" << std::endl;
    std::cout << "4. View Patron" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

int getMenuOption(){
    int userinput;
    std::cin >> userinput;
    return userinput;
}

void printFileNotFound(){
    std::cout << "File Not Found!" << std::endl;
}

void displayModOptions(){
    std::cout << "Patron Modification Options\n1. Add Tickets" << std::endl;
    std::cout << "2. Purchase Ride Admission" << std::endl;
    std::cout << "3. Edit Name" << std::endl;
    std::cout << "0. Exit to Main Menu" << std::endl;
}

int getModOption(){
    int userinput;
    displayModOptions();
    std::cin >> userinput;
    return userinput;
}

int readExistingPatrons(Patron patrons[], string filename){
    string fname, lname;
    int iD;
    int tix;
    int index = 0;
    int numberofrides = 0; // Assume everyone has no rides at the start
    Ride rides[MAX_RIDES];


    ifstream inFile(filename.c_str());

    if (!inFile)// covers a miss spelling of a file name
    {
      printFileNotFound();
      return 0;
    }
    else {
        do{
		    inFile >> fname >> lname >> iD >> tix;
			if(inFile){
				patrons[index].setFirstName(fname);
                patrons[index].setLastName(lname);
                patrons[index].setPatronNumber(tix);
                patrons[index].setNumTickets(tix);
				index++;
			}
		}while(inFile && index < MAX_PATRONS);
		inFile.close();
    }

    return index;

}


void displayPatrons(Patron patrons[], int numPatrons){

    for(int i = 0; i < numPatrons; i++){
        // std::cout << i + 1 << ". " << patrons[i].getFirstName() << " " << patrons[i].getLastName() << std::endl;
        patrons[i].displayName();
    }
}

int getPatronOption(Patron patronList[], int numPatrons){
    displayPatrons(patronList, numPatrons);
    int userinput;
    std::cin >> userinput;
    return userinput;
}

void addPatron(Patron patrons[], Patron newPatron, int* numPatrons){
    patrons[*numPatrons] = newPatron;
    *numPatrons += 1;
    std::cout << "Added Patron!" << std::endl;
}


Patron createNewPatron(){
    string firstname;
    string lastname;
    int idNumber;
    int numRides = 0;
    int numTickets;
    std::cout << "Let's add a patron to the system!" << std::endl;
    std::cout << "Patron First Name:" << std::endl;
    std::cin >> firstname;
    std::cout << "Patron Last Name:" << std::endl;
    std::cin >> lastname;
    std::cout << "Patron ID Number" << std::endl;
    std::cin >> idNumber;
    std::cout << "Number of Tickets" << std::endl;
    std::cin >> numTickets;
    Ride rides[numRides]; // keep full of random crap for now
    Patron newPatron = Patron(firstname, lastname, idNumber, numTickets, numRides, rides);
    string buyingOption;
    do{
        std::cout << "Would they like to purchase ride admittance now?" << std::endl;
        std::cout << "N for No" << std::endl;
        std::cin >> buyingOption;
        if(buyingOption != "N"){
        addRide(&newPatron);
        }
    }while(buyingOption != "N");
    return newPatron;
}

void removePatron(Patron patrons[], int optPatron, int* numPatrons){
    if(optPatron <= *numPatrons){
        std::cout << "Removed " << patrons[optPatron].getFirstName() << " " << patrons[optPatron].getLastName() << std::endl;

        for(int i = optPatron; i < *numPatrons; i++){
            patrons[i] = patrons[i+1];
        }

        *numPatrons -= 1;
    }
    else{
        std::cout << "Invalid Patron Number!" << std::endl;
    }
}

void modifyPatron(Patron* modifiedPatron){
    //displayModOptions();
    int choice = getModOption();
    switch(choice)
    {
        case 0: // exit break case
            break;

        case 1: // add tickets
            addTickets(modifiedPatron);
            break;

        case 2: // purchase admittance to ride
            addRide(modifiedPatron);

            break;

        case 3: // edit name
            editName(modifiedPatron);
            break;

        default: // nonstandard input
            std::cout << "Invalid Input!" << std::endl;
            modifyPatron(modifiedPatron);
            break;
    }
}

void addTickets(Patron* patronToAddTo){
    int addedTickets;
    std::cout << "Enter amount of tickets to be added: " << std::endl;
    std::cin >> addedTickets;
    if(addedTickets >= 0){
        int oldTickets = patronToAddTo->getNumTickets();
        patronToAddTo->setNumTickets(oldTickets + addedTickets);
        std::cout << "Added Tickets!" << std::endl;
    }else{
        std::cout << "Tickets cannot be negative!" << std::endl;
    }

}

void addRide(Patron* patron){
    std::cout << "Which ride would you like to add?:" << std::endl;
    std::cout << "1. World Tour" << std::endl;
    std::cout << "2. Magic Carpet" << std::endl;
    std::cout << "3. Teacups" << std::endl;
    int ridechoice;
    Ride newRide;
    std::cin >> ridechoice;
    switch (ridechoice)
    {
    case 1:
        newRide = WorldTour();
        break;
    case 2:
        newRide = MagicCarpet();
        break;
    case 3:
        newRide = Teacups();
        break;
    default:
        break;
    }
    if(patron->getNumTickets() >= ridechoice){
        patron->addPatronRide(newRide);
        patron->setNumTickets(patron->getNumTickets() - ridechoice);
    }
    else{
        int ticketBuyChoice;
        std::cout << "Patron doesn't have enough tickets. Do they want to purchase tickets?" << std::endl;
        std::cout << "1. Yes \n2. No" << std::endl;
        std::cin >> ticketBuyChoice;
        if(ticketBuyChoice == 1){
            addTickets(patron);
        }
    }           //addRide(patron);
}

void editName(Patron* newNamePatron){
    std::cout << "Would you like to edit the:" << std::endl;
    std::cout << "1. First Name" << std::endl;
    std::cout << "2. Last Name" << std::endl;
    std::cout << "3. Whole Name" << std::endl;
    int namechoice;
    std::cin >> namechoice;
    switch(namechoice){
        case 1: // only first name
        {
            std::cout << "Enter edited first name." << std::endl;
            string newFirstName;
            std::cin >> newFirstName;
            newNamePatron->setFirstName(newFirstName);
            std::cout << "Name Changed!" << std::endl;
            break;
        }

        case 2: // only last name
        {
            std::cout << "Enter edited last name." << std::endl;
            string newLastName;
            std::cin >> newLastName;
            newNamePatron->setLastName(newLastName);
            std::cout << "Name Changed!" << std::endl;
            break;
        }

        case 3: // edit both name
        {
            string newFirstName;
            string newLastName;
            std::cout << "Enter edited first name." << std::endl;
            std::cin >> newFirstName;
            std::cout << "Enter edited last name." << std::endl;
            std::cin >> newLastName;
            newNamePatron->setFirstName(newFirstName);
            newNamePatron->setLastName(newLastName);
            std::cout << "Name Changed!" << std::endl;
            break;
        }
        default:
            std::cout << "Invalid input!" << std::endl;
            break;
    }
}


void overwriteFile(Patron patronArray[], string fileName, int numPatron){
    ofstream outFile(fileName.c_str());

    if (!outFile)// covers a miss spelling of a file name
    {
      printFileNotFound();
    }
    else{
        for(int i = 0; i < numPatron; i++)
        {
            string fname = patronArray[i].getFirstName();
            string lname = patronArray[i].getLastName();
            int iD = patronArray[i].getPatronNumber();
            int tix = patronArray[i].getNumTickets();
            outFile << fname << "\t" << lname << "\t" << iD << "\t" << tix << std::endl;
            //std::cout << "should work" << std::endl;
        }
    }

    std::cout << "\nUpdated Information! \n" << std::endl;
    outFile.close();
}
