//
// Created by flobp on 08/05/2021.
//

#ifndef BANKMANAGMENTSYSTEM_CLASSFUN_H
#define BANKMANAGMENTSYSTEM_CLASSFUN_H
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>

using namespace std;

typedef struct account{
    float deposit;
    std::string name;
    float interest;
    float sum;
    std:: string currency;
    bool active;
}ACCOUNT;

class bank{
    std::vector<ACCOUNT*> clients;
    int numberOfClients = 0;
    char option{};
    string name;
    string owner;
    fstream file;
    string filename;

private:
    void bankInfo();
    void addClient();
    void removeClient();
    void bankrupt();
    void createBank();
    void loadBank();
    void fileBank(const string& bank);

public:
    explicit bank(const string& name);
    bank();
    int menu();
    int findClient(const string& name);
};

bool checkInput();
template <typename T> void askForInput(const string& what, T& variable);
void cls();

#endif //BANKMANAGMENTSYSTEM_CLASSFUN_H
