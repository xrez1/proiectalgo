#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "backend.h"
#include "display.h"

using namespace std;

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