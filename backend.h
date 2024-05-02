#pragma once

#ifndef BACKEND_H_INCLUDED
#define BACKEND_H_INCLUDED

    #include <iostream>
    #include <iomanip>
    #include <string>
    #include <fstream>
    #include <vector>

    using namespace std;



    struct CD {
        int id = -1;
        string prod = "null";
        string name = "null";
        string sizeMB = 0;
        string price = 0;

        CD* head = nullptr;
        CD* prev = nullptr;
        CD* next = nullptr;
    };

    void loadData();

    void addToLinkedList(CD* cd);

    void readLinkedList(CD* cd);

    void storeData(CD cd);

#endif