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
        cout << "Incorrect Usage!" << endl;
        cout << "Usage: "  << argv[0] << " [argument (file name)]" << endl;
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
            cout << "Enter the number of the patron you'd like to remove" << endl;
            int patronNumberChosen = getPatronOption(patrons, arraysize) - 1;
            removePatron(patrons, patronNumberChosen, &arraysize);
            overwriteFile(patrons, argv[1], arraysize);
            break;
        }

        case 3: // modify patron
        {
            cout << "Enter the number of the patron you'd like to modify" << endl;
            int patronNumberChosen = getPatronOption(patrons, arraysize) - 1;
            modifyPatron(&patrons[patronNumberChosen]);
            overwriteFile(patrons, argv[1], arraysize);
            break;
        }

        case 4: // view patron
        {
            cout << "Enter the number of the patron you'd like to view." << endl;
            int patronNumberChosen = getPatronOption(patrons, arraysize) - 1;
            patrons[patronNumberChosen].displayPatronData();
            break;
        }

        default: // nonstandard input
            cout << "Invalid Input!" << endl;
            break;
        }
    }



    return 0;
}

void displayMenuOption(){
    cout << "Menu Options\n1. Add Patron" << endl;
    cout << "2. Remove Patron" << endl;
    cout << "3. Modify Patron" << endl;
    cout << "4. View Patron" << endl;
    cout << "0. Exit" << endl;
}

int getMenuOption(){
    int userinput;
    cin >> userinput;
    return userinput;
}

void printFileNotFound(){
    cout << "File Not Found!" << endl;
}

void displayModOptions(){
    cout << "Patron Modification Options\n1. Add Tickets" << endl;
    cout << "2. Purchase Ride Admission" << endl;
    cout << "3. Edit Name" << endl;
    cout << "0. Exit to Main Menu" << endl;
}

int getModOption(){
    int userinput;
    displayModOptions();
    cin >> userinput;
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
        cout << i + 1 << ". " << patrons[i].getFirstName() << " " << patrons[i].getLastName() << endl;
    }
}

int getPatronOption(Patron patronList[], int numPatrons){
    displayPatrons(patronList, numPatrons);
    int userinput;
    cin >> userinput;
    return userinput;
}

void addPatron(Patron patrons[], Patron newPatron, int* numPatrons){
    patrons[*numPatrons] = newPatron;
    *numPatrons += 1;
    cout << "Added Patron!" << endl;
}


Patron createNewPatron(){
    string firstname;
    string lastname;
    int idNumber;
    int numRides = 0;
    int numTickets;
    cout << "Let's add a patron to the system!" << endl;
    cout << "Patron First Name:" << endl;
    cin >> firstname;
    cout << "Patron Last Name:" << endl;
    cin >> lastname;
    cout << "Patron ID Number" << endl;
    cin >> idNumber;
    cout << "Number of Tickets" << endl;
    cin >> numTickets;
    Ride rides[numRides]; // keep full of random crap for now
    Patron newPatron = Patron(firstname, lastname, idNumber, numTickets, numRides, rides);
    string buyingOption;
    do{
        cout << "Would they like to purchase ride admittance now?" << endl;
        cout << "N for No" << endl;
        cin >> buyingOption;
        if(buyingOption != "N"){
        addRide(&newPatron);
        }
    }while(buyingOption != "N");
    return newPatron;
}

void removePatron(Patron patrons[], int optPatron, int* numPatrons){
    if(optPatron <= *numPatrons){
        cout << "Removed " << patrons[optPatron].getFirstName() << " " << patrons[optPatron].getLastName() << endl;

        for(int i = optPatron; i < *numPatrons; i++){
            patrons[i] = patrons[i+1];
        }

        *numPatrons -= 1;
    }
    else{
        cout << "Invalid Patron Number!" << endl;
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
            cout << "Invalid Input!" << endl;
            modifyPatron(modifiedPatron);
            break;
    }
}

void addTickets(Patron* patronToAddTo){
    int addedTickets;
    cout << "Enter amount of tickets to be added: " << endl;
    cin >> addedTickets;
    if(addedTickets >= 0){
        int oldTickets = patronToAddTo->getNumTickets();
        patronToAddTo->setNumTickets(oldTickets + addedTickets);
        cout << "Added Tickets!" << endl;
    }else{
        cout << "Tickets cannot be negative!" << endl;
    }

}

void addRide(Patron* patron){
    cout << "Which ride would you like to add?:" << endl;
    cout << "1. World Tour" << endl;
    cout << "2. Magic Carpet" << endl;
    cout << "3. Teacups" << endl;
    int ridechoice;
    Ride newRide;
    cin >> ridechoice;
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
        cout << "Patron doesn't have enough tickets. Do they want to purchase tickets?" << endl;
        cout << "1. Yes \n2. No" << endl;
        cin >> ticketBuyChoice;
        if(ticketBuyChoice == 1){
            addTickets(patron);
        }
    }           //addRide(patron);
}

void editName(Patron* newNamePatron){
    cout << "Would you like to edit the:" << endl;
    cout << "1. First Name" << endl;
    cout << "2. Last Name" << endl;
    cout << "3. Whole Name" << endl;
    int namechoice;
    cin >> namechoice;
    switch(namechoice){
        case 1: // only first name
        {
            cout << "Enter edited first name." << endl;
            string newFirstName;
            cin >> newFirstName;
            newNamePatron->setFirstName(newFirstName);
            cout << "Name Changed!" << endl;
            break;
        }

        case 2: // only last name
        {
            cout << "Enter edited last name." << endl;
            string newLastName;
            cin >> newLastName;
            newNamePatron->setLastName(newLastName);
            cout << "Name Changed!" << endl;
            break;
        }

        case 3: // edit both name
        {
            string newFirstName;
            string newLastName;
            cout << "Enter edited first name." << endl;
            cin >> newFirstName;
            cout << "Enter edited last name." << endl;
            cin >> newLastName;
            newNamePatron->setFirstName(newFirstName);
            newNamePatron->setLastName(newLastName);
            cout << "Name Changed!" << endl;
            break;
        }
        default:
            cout << "Invalid input!" << endl;
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
            outFile << fname << "\t" << lname << "\t" << iD << "\t" << tix << endl;
            //cout << "should work" << endl;
        }
    }

    cout << "\nUpdated Information! \n" << endl;
    outFile.close();
}
