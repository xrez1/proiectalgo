#include <iostream>
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
#define FIELD3W  50
#define FIELD4W  10
#define FIELD5W  10

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

    curr->next = cd;
    curr->prev = past;
   
}

void readLinkedList(CD* cd) {

}

/*

            DATA FUNCS

*/


CD* loadData() {
    dataFile.open("data.txt");
    CD* root = new CD;

    while(!dataFile.eof()){
        CD* newCD = new CD;
        streamsize maxChar = 256; 
        char* line = new char[maxChar];
        char delimChar = ';';

        // ID
        dataFile.getline(line, maxChar, delimChar);
        // eof este declarat doar in urma unui get sau getline
        if (dataFile.eof()) {
            break;
        }
        newCD->id = stoi(line);

        // PRODUCATOR
        dataFile.getline(line, maxChar, delimChar);
        newCD->prod = line;

        // NUME CD
        dataFile.getline(line, maxChar, delimChar);
        newCD->name = line;

        // MARIME MB
        dataFile.getline(line, maxChar, delimChar);
        newCD->sizeMB = stof(line);

        // PRET
        dataFile.getline(line, maxChar, delimChar);
        newCD->price = stof(line);

        addToLinkedList(root, newCD);
        delete[] line;
    }

    cout << "Done loading data" << endl;
    dataFile.close();
    return root;
}

void storeData(CD cd) {
    dataFile.open("data.txt", ios::app);
    // scrie date la sfarsitul fisierului sub formatul : 0;x;x;1024;50;
    dataFile << ";" << cd.id << ";" << cd.prod << ";" << cd.name << ";" << cd.sizeMB << ";" << cd.price;
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
            cout << left << setw(FIELD1W) << curr->id << left << setw(FIELD2W) << curr->prod << left << setw(FIELD3W) << curr->name << left << setw(FIELD4W) << curr->sizeMB << left << setw(FIELD5W) << curr->price << endl;
        }
        past = curr;
        curr = curr->next;
    }
}

void displayMain(CD* cdData) {
    //cout.fill('#');
    //cout.width(120);
   // cout << '#' << endl;

    cout << left << setw(FIELD1W) << "ID" << left << setw(FIELD2W) << "PRODUCATOR" << left << setw(FIELD3W) << "NUME JOC" << left << setw(FIELD4W) << "MARIME (MB)" << left << setw(FIELD5W) << "PRET" << endl;
    cout.fill('-');
    cout.width(180);
    cout << "-" << endl;
    cout << setfill(' ');
    dispalyLinkedList(cdData);



    //cout.fill('#');
   // cout.width(120);
    //cout << '#';
}

int main()
{
    CD* cdData = loadData();
    displayMain(cdData);
}

