//Dalton Burke 102279938
//Menu.cpp
//implementation of "Menu" class and methods

#include"Menu.h"
#include"AVLTree.h"
#include"Contact.h"
#include<fstream>
namespace database
{
    Menu::Menu(int n, std::string title):
        __size(n),
        __title(title)
    { __options = new std::string[n]; }

    Menu::~Menu()
    {
        delete [] __options;
    }

    //non-const subscript operator, can be used for assigning and retrieving
    std::string& Menu::operator[](unsigned int index)
    {
        //this should never happen in a menu
        if(index >= __size || index < 0)
            return __options[0];
        return __options[index];
    }

    unsigned int Menu::run()
    {
        std::cout << "___________________________________________" << std::endl << std::endl;;
        std::cout << __title << std::endl;

        for(unsigned int i = 0; i < __size; i++)
            std::cout << i + 1 << ": " << __options[i] << std::endl;

        unsigned int choice;

        do
        {
            std::cout << "Please make a valid selection (1-" << __size << "): ";
            //if you do something stupid and give me a string, then I have to deal with that
            if(!(std::cin >> choice))
            {
                std::cin.clear();
                std::cin.ignore(256, '\n');
                choice = 0;
            }
        }while(choice > __size || choice < 1);

        return choice;
    }

}
