#include <iostream>
#include <string>
#include <fstream>
#include <format>
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

void loadData() {
    dataFile.open("data.txt");
    
    char ch;

    int id;
    string prod;
    string name;
    double sizeMB;
    double price;

    while (dataFile){
        for (int i = 0; i < 6; i++) {
            vector<char> word;
            switch (i){
            case 0:                         // ID
                ch = dataFile.get();
                while (ch != ';') {
                    word.push_back(ch);
                }
            case 1:                         // PRODUCATOR
                ch = dataFile.get();
                while (ch != ';') {
                    word.push_back(ch);
                }
            case 2:                         // NUME CD
                ch = dataFile.get();
                while (ch != ';') {
                    word.push_back(ch);
                }
            case 3:                         // MARIME MB
                ch = dataFile.get();
                while (ch != ';') {
                    word.push_back(ch);
                }
            case 4:                         // PRET
                ch = dataFile.get();
                while (ch != ';') {
                    word.push_back(ch);
                }
            case 5:                         // CREAZA OBIECT
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

void display() {

}

int main()
{



}

