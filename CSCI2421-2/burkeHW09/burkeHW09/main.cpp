//Dalton Burke 102279938
//main.cpp
//contains main, the implementation of the database

#include<fstream>
#include"MenuFunctions.h"
#include"Menu.h"
#include"Contact.h"
#include"BSTree.h"
using namespace database;
int main()
{
    Node* db = nullptr;
    std::cout << std::endl << std::endl << "Welcome to your Address Book." << std::endl;

    mainMenu(db);

    return 0;
}
