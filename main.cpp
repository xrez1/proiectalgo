#include <iostream>
#include <stdlib.h> 
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/*
magazin de cd-uri
se citeste un numarul natural N > 0, 
intr-un magazin sunt n cd-uri de jocuri video cu urmatoarele proprietatii
    cod de identificare in stoc
    numele producator
    numele joc
    dimensiunea ocupata in MB
    pret in lei
informatii stocate in fisierul stoc.txt ce sunt memorate pana la finalul programului
o functie pentru fiecare dintre urmatoarele prob.
    1. gasire cate jocurii in stoc (cautare bazata pe nume)
    2. afisatii jocurile cu dimensiune intre [a,b]
    3. afisatii jocurile cu dimensiune mai mica de n, mai mare de n sau egala cu n
*/

fstream dataFile;

//Defines for table dispaly widths
#define FIELD1W  10
#define FIELD2W  50
#define FIELD3W  75
#define FIELD4W  30
#define FIELD5W  10
#define SPACERW  1
#define OPTFIELD 15
//State defines
#define STATE_MAIN 0
#define STATE_MANIPULATE 1 //addition/removal etc..
#define STATE_SEARCH 2
#define STATE_FILTER 3
int currentState = 0;

/*

            CD OBJ

*/

struct CD {
    int id = -1;
    string prod = "null";
    string name = "null";
    double sizeMB = 0;
    double price = 0;

    CD* head = nullptr;
    CD* prev = nullptr;
    CD* next = nullptr;
};

void addToLinkedList(CD* root, CD* cd) {
    CD* curr = root;
    CD* past = root;

    if (root->head != root) {
        root->head = root;
    }
    if (cd->head != root) {
        cd->head = root;
    }

    while (curr->next != nullptr) {
        past = curr;
        curr = curr->next;
    }

    if (cd->id == -2) { //autoindex
        cd->id = curr->id + 1;
    }

    curr->next = cd;
    curr->prev = past;
    cd->prev = curr;
}

void removeFromLinkedList(CD* root, int id) {
    CD* curr = root;
    CD* past = root;

    while (curr->id != id) {
        past = curr;
        curr = curr->next;
    }
    
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    
    delete curr;
}

/*

            DATA FUNCS

*/


CD* loadData() {
    dataFile.open("data.txt");
    CD* root = new CD;
    string wholeLine;

    while(getline(dataFile, wholeLine)){
        CD* newCD = new CD;
        string currentLine;
        char delimChar = ';';
        size_t lastPos = wholeLine.find_first_of(";");
        // ID
        currentLine = wholeLine.substr(0, lastPos);
        lastPos = wholeLine.find_first_of(";", lastPos);
        newCD->id = stoi(currentLine);

        // PRODUCATOR
        currentLine = wholeLine.substr(lastPos += 1, wholeLine.find_first_of(delimChar, lastPos) - lastPos);
        lastPos = wholeLine.find_first_of(delimChar, lastPos);
        newCD->prod = currentLine;

        // NUME CD
        currentLine = wholeLine.substr(lastPos += 1, wholeLine.find_first_of(delimChar, lastPos) - lastPos);
        lastPos = wholeLine.find_first_of(delimChar, lastPos);
        newCD->name = currentLine;

        // MARIME MB
        currentLine = wholeLine.substr(lastPos += 1, wholeLine.find_first_of(delimChar, lastPos) - lastPos);
        lastPos = wholeLine.find_first_of(delimChar, lastPos);
        newCD->sizeMB = stod(currentLine);

        // PRET
        currentLine = wholeLine.substr(lastPos += 1, wholeLine.find_first_of(delimChar, lastPos) - lastPos);
        lastPos = wholeLine.find_first_of(delimChar, lastPos);
        newCD->price = stod(currentLine);

        addToLinkedList(root, newCD);
    }

    dataFile.close();
    return root;
}

void storeData(CD* cd) {
    dataFile.open("data.txt", ios::app);
    // scrie date la sfarsitul fisierului sub formatul : 0;x;x;1024;50;
    dataFile<< "\n" << cd->id << ";" << cd->prod << ";" << cd->name << ";" << cd->sizeMB << ";" << cd->price;
    dataFile.close();
}

/*

            DISPLAY FUNCS

*/

void dispalyLinkedList(CD* cd) {
    CD* curr = cd->head;
    CD* past = cd->head;


    while (curr->next != nullptr) {
        if (curr->id != -1) {
            cout << left << setw(FIELD1W) << curr->id << setw(SPACERW) << " " << left << setw(FIELD2W) << curr->prod << setw(SPACERW) << " " << left << setw(FIELD3W) << curr->name << setw(SPACERW) << " " << left << setw(FIELD4W) << curr->sizeMB << setw(SPACERW) << " " << right << setw(FIELD5W) << setfill('.') << curr->price << setw(SPACERW) << " " << setfill(' ') << endl;
        }
        past = curr;
        curr = curr->next;
    }
    cout << left << setw(FIELD1W) << curr->id << setw(SPACERW) << " " << left << setw(FIELD2W) << curr->prod << setw(SPACERW) << " " << left << setw(FIELD3W) << curr->name << setw(SPACERW) << " " << left << setw(FIELD4W) << curr->sizeMB << setw(SPACERW) << " " << right << setw(FIELD5W) << setfill('.') << curr->price << setw(SPACERW) << " " << setfill(' ') << endl;
}

void getState() {
    int newstate;
    cout << endl;
    cin >> newstate;
    if (newstate == 0) {
        currentState = STATE_MAIN;
    }
    else if (newstate == 1) {
        currentState = STATE_MANIPULATE;
    }
    else if (newstate == 2) {
        currentState = STATE_SEARCH;
    }
    else if (newstate == 3) {
        currentState = STATE_FILTER;
    }
}

void horizontalLine() {
    cout.fill('-');
    cout.width(180);
    cout << "-" << endl;
    cout << setfill(' ');
}

void displayFieldHeaders() {
    cout << left << setw(FIELD1W) << "ID" << setw(SPACERW) << " " << left << setw(FIELD2W) << "PRODUCATOR" << setw(SPACERW) << " " << left << setw(FIELD3W) << "NUME JOC" << setw(SPACERW) << " " << left << setw(FIELD4W) << "MARIME (MB)" << setw(SPACERW) << " " << left << setw(FIELD5W) << "PRET (LEI)" << setw(SPACERW) << " " << endl;

}
void displayOptions() {
    cout << left << setw(OPTFIELD) << "1. ADD/REMOVE" << setw(SPACERW) << " " << left << setw(OPTFIELD) << "2. SEARCH" << setw(SPACERW) << left << setw(OPTFIELD) << "3. FILTER" << setw(SPACERW) << " " << left << setw(OPTFIELD) << "0. MAIN" << endl;
}

void displayLinkedListCurrent(CD* curr){
    cout << left << setw(FIELD1W) << curr->id << setw(SPACERW) << " " << left << setw(FIELD2W) << curr->prod << setw(SPACERW) << " " << left << setw(FIELD3W) << curr->name << setw(SPACERW) << " " << left << setw(FIELD4W) << curr->sizeMB << setw(SPACERW) << " " << right << setw(FIELD5W) << setfill('.') << curr->price << setw(SPACERW) << " " << setfill(' ') << endl;
}

void displayMain(CD* cdData) {
    system("cls"); // clear screen

    displayFieldHeaders();
    horizontalLine();
    dispalyLinkedList(cdData);
    horizontalLine();
    displayOptions();
    getState();
}

void displaySearch(CD* cdData) {
    system("cls");
    cout << "SEARCH" << endl;
    cout << "Enter string to search or leave empty to return" << endl;
    
    int cdCount = 0;
    string searchString;
    cin.ignore();
    getline(cin, searchString);

    if (searchString == "") {
        displayMain(cdData);
    }
    else{
        displayFieldHeaders();
        horizontalLine();
        CD* curr = cdData->head;
        CD* past = cdData->head;
        while (curr->next != nullptr) {
            if (curr->name == searchString) {
                displayLinkedListCurrent(curr);
                cdCount++;
            }
            past = curr;
            curr = curr->next;
        }
        cout << "Found " << cdCount << "CDs in stock." << endl;
        horizontalLine();
        displayOptions();

        getState();
    }
}

void displayFilter(CD* cdData) {
    system("cls");
    cout << "FILTER" << endl;
    cout << "1. BY SIZE" << endl;

    int choice = 0;
    cin >> choice;
    if (choice == 1) {
        cout << "Enter a comparison sign (<, = or >) and then the size (ex. <200) or enter : between two numbers for a range (ex. 250:600). Leave blank to return" << endl;
        string userFilter;
        string compareSign;
        double size;
        cin >> userFilter;

        displayFieldHeaders();
        horizontalLine();

        // string::npos is the return value of .find if it can't find the string
        if (userFilter.find("<") != string::npos) {
            string substring = userFilter.substr(userFilter.find("<") + 1, userFilter.length());
            size = stod(substring);

            CD* curr = cdData->head;
            CD* past = cdData->head;
            while (curr->next != nullptr) {
                if (curr->sizeMB < size && curr->id != -1) {
                    displayLinkedListCurrent(curr);
                }
                past = curr;
                curr = curr->next;
            }
        }
        else if (userFilter.find("=") != string::npos) {
            string substring = userFilter.substr(userFilter.find("=") + 1, userFilter.length());
            size = stod(substring);

            CD* curr = cdData->head;
            CD* past = cdData->head;
            while (curr->next != nullptr) {
                if (curr->sizeMB == size && curr->id != -1) {
                    displayLinkedListCurrent(curr);
                }
                past = curr;
                curr = curr->next;
            }
        }
        else if (userFilter.find(">") != string::npos){
            string substring = userFilter.substr(userFilter.find(">") + 1, userFilter.length());
            size = stod(substring);

            CD* curr = cdData->head;
            CD* past = cdData->head;
            while (curr->next != nullptr) {
                if (curr->sizeMB > size && curr->id != -1) {
                    displayLinkedListCurrent(curr);
                }
                past = curr;
                curr = curr->next;
            }
        }
        else if (userFilter.find(":") != string::npos) {
            double size2 = 0;
            string substring1 = userFilter.substr(0, userFilter.find(":"));
            string substring2 = userFilter.substr(userFilter.find(":") + 1, userFilter.length());

            size = stod(substring1);
            size2 = stod(substring2);

            if (size > size2) {
                cout << "First number must be lower then second." << endl;
                horizontalLine();
                displayOptions();

                getState();
            }

            CD* curr = cdData->head;
            CD* past = cdData->head;
            while (curr->next != nullptr) {
                if (size <= curr->sizeMB && curr->sizeMB <= size2 && curr->id != -1) {
                    displayLinkedListCurrent(curr);
                }
                past = curr;
                curr = curr->next;
            }
        }
        else {
            displayMain(cdData);
        }

    }
    else {
        displayMain(cdData);
    }

    horizontalLine();
    displayOptions();

    getState();
}

void displayManipulate(CD* cdData) {
    system("cls");
    cout << "MANIPULATION" << endl;
    cout << left << setw(OPTFIELD) << "1. ADD" << left << setw(OPTFIELD) << "2. REMOVE" << endl;

    int choice = 0;
    cin >> choice;

    if (choice == 1) {
        CD* newUserCD = new CD;
        newUserCD->id = -2;

        string prod;
        string name;
        double sizeMB;
        double price;

        cout << "Enter CD producer" << endl;
        cin.ignore();
        getline(cin, prod);
        cout << "Enter CD name" << endl;
        getline(cin, name);
        cout << "Enter CD size" << endl;
        cin >> sizeMB;
        cout << "Enter CD price" << endl;
        cin >> price;
        
        newUserCD->prod = prod;
        newUserCD->name = name;
        newUserCD->sizeMB = sizeMB;
        newUserCD->price = price;

        addToLinkedList(cdData, newUserCD);
        storeData(newUserCD);
    }
    else if (choice == 2) { // does not remove from data file
        cout << "Enter ID of the item to remove" << endl;
        int idToRemove;
        cin >> idToRemove;
        if (idToRemove < 0) {
            cout << "ID must be 0 or above" << endl;
        }
        else {
            removeFromLinkedList(cdData, idToRemove);
        }
    }
    else {
        displayMain(cdData);
    }
    horizontalLine();
    displayOptions();

    getState();
}


int main(){   
    CD* cdData = loadData();

    while (currentState != -1) {
        if (currentState == 0) {
            displayMain(cdData);
        }
        else if (currentState == 1) {
            displayManipulate(cdData);
        }
        else if (currentState == 2) {
            displaySearch(cdData);
        }
        else if (currentState == 3) {
            displayFilter(cdData);
        }
    }
}