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

#define FIELD1W  10
#define FIELD2W  256
#define FIELD3W  256
#define FIELD4W  10
#define FIELD5W  10

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



CD* loadData() {
    dataFile.open("data.txt");
    CD* newCD = new CD;
    
    string stg;

    int id;
    string prod;
    string name;
    float sizeMB;
    float price;

    while (!dataFile.eof()){
        streamsize maxChar = 256; 
        char* line = new char[maxChar];
        char delimChar = ';';

        // ID
        dataFile.getline(line, maxChar, delimChar);
        cout << line << endl;
        id = stoi(line);

        // PRODUCATOR
        dataFile.getline(line, maxChar, delimChar);
        cout << line << endl;
        prod = line;

        // NUME CD
        dataFile.getline(line, maxChar, delimChar);
        cout << line << endl;
        name = line;

        // MARIME MB
        dataFile.getline(line, maxChar, delimChar);
        cout << line << endl;
        sizeMB = stof(line);

        // PRET
        dataFile.getline(line, maxChar, delimChar);
        cout << line << endl;
        price = stof(line);

        // CREAZA OBIECT
        newCD->id = id;
        newCD->prod = prod;
        newCD->name = name;
        newCD->sizeMB = sizeMB;
        newCD->price = price;

        addToLinkedList(newCD);
        delete[] line;
    }

    dataFile.close();
    return newCD;
}

void storeData(CD cd) {
    dataFile.open("data.txt", ios::app);
    // scrie date la sfarsitul fisierului sub formatul : 0;x;x;1024;50;
    dataFile << cd.id << ";" << cd.prod << ";" << cd.name << ";" << cd.sizeMB << ";" << cd.price << ";";
    dataFile.close();
}

void dispalyLinkedList(CD* cd) {
    CD* curr = cd->head;
    CD* past = cd->head;


    while (curr->next != nullptr) {
        past = curr;
        curr = curr->next;
    }
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
    CD* cdData = loadData();
    displayMain();
}

