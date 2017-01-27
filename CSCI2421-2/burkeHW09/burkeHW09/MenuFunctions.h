//Dalton Burke 102279938
//MenuFunctions.h
//contains the declaration of useful functions, mostly functions for Menus

#ifndef DATABASE_MENUFUNCTIONS_H
#define DATABASE_MENUFUNCTIONS_H

#include"Contact.h"
#include"Menu.h"
#include"BSTree.h"

namespace database
{
    //functions for making menu type
    void mainMenu(Node* &db);

    //Managing raw data:

    //opens a menu for managing the raw database
    void rawMenu(Node* &db);

    //opens a menu for reading the database in from file
    void readMenu(Node* &db);

    //opens a menu for writing the current database to a file
    void writeMenu(Node* &db);

    //opens a menu for adding a contact to the main current database
    void addMenu(Node* &db);

    //opens a menu for removing a contact from the main database
    void removeMenu(Node* &db);

    //opens a menu for editting a contact from the main database
    void editMenu(Node* &db);



    //opens a menu for searching the current database
    //db is the tree to be searched, and maindb is a reference to the main database
    //that will be used in case the user changes something in a refined search
    void searchMenu(Node* &db, Node* &maindb);

    //opens a menu for when a search has been complete, but there is more than one resut
    //parameters are, the dataabse that was searched, the results of the search
    //and a reference to the main database, so that they can edit or remove results
    void postsearchMenu(Node* &db, Node* &results, Node* &maindb);

    //opens a menu for when a search is complete, and there is only one result
    //same parameters as the postsearchMenu
    void endsearchMenu(Node* &db, Node* &results, Node* &maindb);

    //opens a menu for sorting the database
    void sortMenu(Node* &db);

    //Managing the formatted output

    //this function is just a menu which gives options for what to do with a formatted output
    //(more in the design doc)
    void refinedMenu(Node* &db);

    //these three are for loading, saving, and editing the current cnfiguration
    //they are passed pointers to arrays where the configuration data is stored
    void configloadMenu(int* appear, int* order, std::string* desc);
    void configsaveMenu(int* appear, int* order, std::string* desc);
    void configeditMenu(int* appear, int* order, std::string* desc);

    //this sends the current formatted output to the display so the user can see if they like it
    void previewMenu(Node* &db);


    //other helpful functions for menus
    //returns a bool based on the users respense to a yes no question
    //the question is passed as a string into the functions
    bool yesnoMenu(std::string title);


    //Other helpful functions

    //opens a menu for creating a new contact, and returns that contact
    Contact createContact();

    //opens a menu for editting a contact, which is done by reference
    void editContact(Contact &contact);

    //opens a menu for editting the affliates of a contact
    //the user can edit add or delete them from here
    void editAff(Contact &contact);

    //these functions check the validity of the files to which they correspond,
    //returning false if they did not pass, and true otherwise

    //this one tests the database file
    bool dbisValid(std::string filename);

    //this one tests the config file for the formatted output
    bool confisValid(std::string filename);

}

#endif //DATABASE_MENUFUNCTIONS_H
