#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "backend.h"
#include "display.h"

using namespace std;

void loadData() {
    fstream dataFile;
    dataFile.open("data.txt");

    string stg;

    int id;
    string prod;
    string name;
    string sizeMB;
    string price;

    while (!dataFile.eof()) {
        for (int i = 0; i < 6; i++) {
            CD* newCD = new CD;

            streamsize maxChar = 256;
            char* line = new char[maxChar];
            char delimChar = ';';

            switch (i) {
            case 0:                         // ID
                dataFile.getline(line, maxChar, delimChar);
                cout << line << endl;
                id = stoi(line);
                cout << id << endl;
            case 1:                         // PRODUCATOR
                dataFile.getline(line, maxChar, delimChar);
                cout << line << endl;

                prod = line;
                cout << prod << endl;
            case 2:                         // NUME CD
                dataFile.getline(line, maxChar, delimChar);
                cout << line << endl;

                name = line;
                cout << name << endl;
            case 3:                         // MARIME MB
                dataFile.getline(line, maxChar, delimChar);
                cout << line << endl;

                sizeMB = line;
                cout << sizeMB << endl;
            case 4:                         // PRET
                dataFile.getline(line, maxChar, delimChar);
                cout << line << endl;

                price = line;
                cout << price << endl;
            case 5:                         // CREAZA OBIECT
                newCD->id = id;
                newCD->prod = prod;
                newCD->name = name;
                newCD->sizeMB = sizeMB;
                newCD->price = price;

                addToLinkedList(newCD);
                delete[] line;
            default:
                break;
            }
        }
    }
    dataFile.close();
}

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

void storeData(CD cd) {
    fstream dataFile;
    dataFile.open("data.txt", ios::app);
    // scrie date la sfarsitul fisierului sub formatul : 0;x;x;1024;50;
    dataFile << cd.id << ";" << cd.prod << ";" << cd.name << ";" << cd.sizeMB << ";" << cd.price << ";";
    dataFile.close();
}
