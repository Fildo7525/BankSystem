//
// Created by flobp on 08/05/2021.
//

#include "classFun.h"

#include <utility>

void cls(){
    system("cls");
}

bank::bank()= default;

bank::bank(const string& name){
    this->name = name;
    numberOfClients = 0;
}

int bank::menu() {
    cls();
    cout << "--------- Welcome to the Bank Management System ---------\n\n"
         << "Choose form one of the options below:\n"
         << "\tA) Bank Info\n"
         << "\tB) Add a new client\n"
         << "\tC) Remove a client\n"
         << "\tD) Bankrupting\n"
         << "\tE) Register a Bank\n"
         << "\tF) Load a Bank\n"
         << "\tG) Exit\n\n";

    cin >> option;

    if(cin.fail()){
        cin.clear();
        cin.ignore(10000000,'\n');
    }

    switch(option){
        case 'A':
            bankInfo();
            break;
        case 'B':
            addClient();
            break;
        case 'C':
            removeClient();
            break;
        case 'D':
            bankrupt();
            break;
        case 'E':
            createBank();
            break;
        case 'F':
            loadBank();
            break;
        case 'G':
            for(auto &o: clients)
                delete o;
            clients.clear();
            return 1;
        default:
            cout << "The option has no defined action\b";
    }
    return 0;
}

void bank::createBank(){
    cls();
    askForInput("Enter the bank name: ",this->name);
    askForInput("Enter the owner: ", this->owner);
    filename = this->name + ".txt";
    file.open(this->filename,ios::out);
    file << this->name << endl;
    file << this->owner << endl;
    file.close();
}

void bank::bankInfo(){
    cls();
    if(clients.empty()){
        cout << "The bank does not exist or has bankrupted\n";
    }
    else {
        cout << "Bank name: " << name << endl
             << "Number of clients: " << numberOfClients << endl << endl;

        for (int i = 0; i < clients.size(); i++) {
            cout << "Client No." << i + 1 << endl
                 << "\tName: " << clients[i]->name << endl
                 << "\tAccount currency: " << clients[i]->currency << endl
                 << "\tDeposit Sum: " << clients[i]->deposit << endl
                 << "\tInterest rate: " << clients[i]->interest << endl
                 << "\tSum of money: " << clients[i]->sum
                 << "\n\n";
        }
    }
    cout << "To continue press any key...\n";
    getchar();
    getchar();
}

void bank::addClient() {
    auto newClient = new ACCOUNT;
    cls();
    askForInput("Enter the name of account creator: ",newClient->name);
    askForInput("What is the account currency: ", newClient->currency);
    askForInput("Enter the deposit sum: ", newClient->deposit);
    askForInput("Enter the interest rate: ", newClient->interest);

    this->file.open(this->filename, ios::app);

    newClient->active = true;
    newClient->sum = newClient->deposit;

    file << newClient->name << endl;
    file << newClient->currency << endl;
    file << newClient->deposit << endl;
    file << newClient->interest << endl;
    file << newClient->sum << endl;
    file << newClient->active << endl;

    file.close();
    newClient->sum = 0;
    clients.push_back(newClient);
    this->numberOfClients++;

    cout << "Client added successfully...\n";
    Sleep(3000);
}

void bank::loadBank() {
    string bname;
    askForInput("What is the bank name: ", bname);
    bname+=".txt";
    fileBank(bname);
}

void bank::fileBank(const string& bank){
    fstream f(bank,ios::in);
    int i = 0;
    if(!f.is_open()){
        cout << "The bank is not in our records or something went wrong\n";
    }
    else {
        f >> this->name;
        f >> this->owner;

        while (f) {
            i++;
            auto client = new ACCOUNT;
            f >> client->name;
            f >> client->currency;
            f >> client->deposit;
            f >> client->interest;
            f >> client->sum;
            f >> client->active;
            f >> client->active;
            clients.push_back(client);
        }
        this->numberOfClients = i;
        f.close();
    }
}

void bank::removeClient(){
    string localName;
    int position;

    cls();
    askForInput("Enter the name of client to remove: ", localName);
    if((position = findClient(localName)) != -1){
        delete clients[position];
        clients.erase(clients.begin()+position);
    }
}

void bank::bankrupt(){
    cls();
    for(auto &o: clients){
        delete o;
    }
    clients.clear();
    cout << "The bank has bankrupted all the money are lost\n";
    getchar();
    getchar();
}

int bank::findClient(const string& localName){
    for(int i = 0; i < clients.size(); i++){
        if (clients[i]->name == localName){
            return i;
        }
    }
    cout << "The client is not registered\n";
    return -1;
}

template <typename T> void askForInput(const string& what, T& variable){
    do{
        cout << what;
        cin >> variable;
    }while(!checkInput());
}

bool checkInput(){
    if(cin.fail()){
        cin.clear();
        cin.ignore(100000,'\n');
        return false;
    }
    return true;
}