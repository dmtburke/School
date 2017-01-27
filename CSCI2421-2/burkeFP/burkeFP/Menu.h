//Dalton Burke 102279938
//Menu.h
//Declaration of "Menu" class
//a menu just makes it easy for me to display a menu with options
//it contains an array of menu options, the number of which is given as an
//argument to the constructor, I also overload the << operator to put it into an ostream

#ifndef DATABASE_MENU_H
#define DATABASE_MENU_H

#include<string>

namespace database
{
    class Menu
    {
    private:
        unsigned int __size;
        std::string __title;
        std::string* __options;

    public:
        //constructor takes the number of choices and the title of the menu as arguments
        Menu(int n, std::string title);
        ~Menu();

        //subscript operator to set and get items of the options array
        std::string& operator[](unsigned int index);

        //run outputs the menu to the console, and retrieves the users choice
        unsigned int run();
    };

}

#endif //DATABASE_MENU_H
