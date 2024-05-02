#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <format>
#include <vector>
#include <display.h>
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

#define FIELD1W  10
#define FIELD2W  256
#define FIELD3W  256
#define FIELD4W  10
#define FIELD5W  10

struct CD {
    int id = -1;
    string prod = NULL;
    string name = NULL;
    double sizeMB = 0;
    double price = 0;

    CD* head = nullptr;
    CD* prev = nullptr;
    CD* next = nullptr;
};

void addToLinkedList(CD* cd) {
    if (cd->head == nullptr) {
        cd->head = cd;
    }
    else {
        CD* curr = cd->head;
        CD* past = cd->head;
        while (curr->next != nullptr) {
            past = curr;
            curr = curr->next;
        }
        curr->next = cd;
        curr->prev = past;
    }
}

void readLinkedList(CD* cd) {

}

void dispalyLinkedList(CD* cd) {
    CD* curr = cd->head;
    CD* past = cd->head;


    while (curr->next != nullptr) {
        past = curr;
        curr = curr->next;
    }
}


void loadData() {
    dataFile.open("data.txt");
    
    string stg;

    int id;
    string prod;
    string name;
    float sizeMB;
    float price;

    while (dataFile){
        for (int i = 0; i < 6; i++) {
            CD* newCD = new CD;

            streamsize maxChar = 256; 
            char* line = new char[maxChar];
            char delimChar = ';';

            switch (i){
            case 0:                         // ID
                dataFile.getline(line, maxChar, delimChar);
                id = stoi(line);
            case 1:                         // PRODUCATOR
                dataFile.getline(line, maxChar, delimChar);
                prod = line;
            case 2:                         // NUME CD
                dataFile.getline(line, maxChar, delimChar);
                name = line;
            case 3:                         // MARIME MB
                dataFile.getline(line, maxChar, delimChar);
                sizeMB = stof(line);
            case 4:                         // PRET
                dataFile.getline(line, maxChar, delimChar);
                price = stof(line);
            case 5:                         // CREAZA OBIECT
                newCD->id = id;
                newCD->prod = prod;
                newCD->name = name;
                newCD->sizeMB = sizeMB;
                newCD->price = price;

                addToLinkedList(newCD);
                delete[] line;
                dataFile.close();
            default:
                break;
            }
        }
    }
}

void storeData(CD cd) {
    dataFile.open("data.txt", ios::app);
    // scrie date la sfarsitul fisierului sub formatul : 0;x;x;1024;50;
    dataFile << cd.id << ";" << cd.prod << ";" << cd.name << ";" << cd.sizeMB << ";" << cd.price << ";";
    dataFile.close();
}

void displayMain() {
    cout.fill('#');
    cout.width(120);
    cout << '#' << endl;







    cout.fill('#');
    cout.width(120);
    cout << '#';
}

int main()
{
    displayMain();
}

