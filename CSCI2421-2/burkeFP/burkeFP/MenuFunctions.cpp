//Dalton Burke 102279938
//MenuFunctions.cpp
//contains the implementation for the functions declared in MenuFunctions.h

#include"MenuFunctions.h"
#include<fstream>

namespace database
{

    //menu type functions
    //main
    void mainMenu(TNode* &db)
    {
        Menu menu(3, "Main Menu:");
        menu[0] = "Manage Raw Database";
        menu[1] = "Manage Formatted output";
        menu[2] = "Exit the program";

        int input;
        do
        {
            input = menu.run();

            switch(input)
            {
                case 1:
                    rawMenu(db);
                    break;
                case 2:
                    refinedMenu(db);
                    break;
                case 3:
                    std::cout << "Goodbye!" <<std::endl;
                    break;
            };
        }while(input != 3);

    }

    //Raw database tools
    void rawMenu(TNode* &db)
    {
        Menu menu(9, "Raw Database Management Menu: ");
        menu[0] = "Read Database from file";
        menu[1] = "Write Database to file";
        menu[2] = "Add a Contact to the Database";
        menu[3] = "Remove a contact from the Database";
        menu[4] = "Edit a contact from the Database";
        menu[5] = "Search the Database";
        menu[6] = "Sort the Database";
        menu[7] = "Display Raw Database (could be very large)";
        menu[8] = "Exit Raw Database Menu";

        int input;
        do
        {
            std::cout << std::endl << "Size of database: " << getSize(db) << std::endl;
            input = menu.run();
            if(input == 9)
                break;

            switch(input)
            {
                case 1:
                    readMenu(db);
                    break;
                case 2:
                    writeMenu(db);
                    break;
                case 3:
                    addMenu(db);
                    break;
                case 4:
                    removeMenu(db);
                    break;
                case 5:
                    editMenu(db);
                    break;
                case 6:
                    searchMenu(db, db);
                    break;
                case 7:
                    sortMenu(db);
                    break;
                case 8:
                    sendOut(db, std::cout);
                    break;
            };

        }while(true);




    }

    void readMenu(TNode* &db)
    {
        Menu menu(3, "Read Database from file");
        menu[0] = "Specify file name";
        menu[1] = "Use the default file name (databaselarge0.txt)";
        menu[2] = "Exit Read menu";

        int input = menu.run();

        //exit
        if(input == 3)
        {
            std::cout << std::endl << "Leaving..." << std::endl;
            return;

        }

        std::string filename;
        if(input == 2)
            filename = "databaselarge0.txt";

        else
        {
            std::cout << "File name: ";
            std::cin >> filename;
        }
        //test the file here
        if(!dbisValid(filename))
        {
            std::cout << "ERROR: FILE ERROR" << std::endl;
            return;
        }

        std::ifstream fin;
        fin.open(filename);

        //we need dynamic stuff here so that the affiliates don't get carried over between loops
        Contact* holder;

        while(!fin.eof())
        {
            holder = new Contact;
            fin >> *holder;

            //fin.ignore(); //skip \n after delimiter
            db = insert(db, *holder, 0);

            delete holder;
            fin.ignore(256, '\n');

            //if we are at the end of the file, this is to throw the eof bit so that we can end the loop on time
            fin.peek();
        }
        fin.close();
    }

    void writeMenu(TNode* &db)
    {
        Menu menu(3, "Write Database to file");
        menu[0] = "Specify file name";
        menu[1] = "Use default file name database.txt (not recommended)";
        menu[2] = "Exit Write menu";

        int input = menu.run();

        if(input == 3)
        {
            std::cout << std::endl << "Leaving..." << std::endl;
            return;
        }

        std::string filename;

        if(input == 2)
            filename = "database.txt";

        else
        {
            std::cout << "File name: ";
            std::cin >> filename;
        }

        std::ofstream fout;
        fout.open(filename);

        sendOut(db, fout);//sends all of the nodes to fout

        fout.close();
    }

    void addMenu(TNode* &db)
    {
        db = insert(db, createContact(), 0);
    }

    void removeMenu(TNode* &db)
    {
        Menu menu(3, "Remove Menu: ");
        menu[0] = "Remove by using ID";
        menu[1] = "Switch to search to find what you want to remove";
        menu[2] = "Exit Remove Menu";

        while(true)
        {
            int input = menu.run();

            if(input == 3)
                break;

            if(input == 2)
                searchMenu(db, db);

            if(input == 1)
            {
                std::string id;
                std::cout << "Enter a 9 digit ID: ";
                std::cin.ignore();
                getline(std::cin, id);
                if(id.length() != 9)
                    std::cout << "Invalid ID (not 9 digits)" << std::endl;
                else
                {
                    TNode* result;
                    searchTree(db, id, result, 0, 1);

                    if(!result)
                        std::cout << "ERROR: ID NOT FOUND" << std::endl;
                    else
                    {
                        std::cout << std::endl << std::endl << result->key << std::endl;
                        if(yesnoMenu("Are you sure you want to delete this contact?"))
                        {
                            db = rmNode(db, result->key);
                            std::cout << std::endl << "Contact deleted from database" << std::endl << std::endl;
                        }
                    }

                }

            }
        }

    }

    void editMenu(TNode* &db)
    {
        Menu menu(3, "Contact Edit Menu");
        menu[0] = "Edit by ID";
        menu[1] = "Switch to search to find what you want to edit";
        menu[2] = "Exit Contact Edit Menu";

        while(true)
        {
            int input = menu.run();
            if(input == 3)
                break;

            if(input == 1)
            {
                std::string id;
                std::cout << "Enter a 9 digit ID: ";
                std::cin.ignore();
                getline(std::cin, id);
                if(id.length() != 9)
                    std::cout << "Invalid ID (not 9 digits)" << std::endl;
                else
                {
                    TNode* result = nullptr;
                    searchTree(db, id, result, 0, 1);
                    if(!result)
                        std::cout << "ID not found in database" << std::endl;
                    else
                    {
                        //I have to get rid of the version of the key that's in the
                        //main database, then add it back once I have editted it
                        db = rmNode(db, result->key);
                        editContact(result->key);
                        db = insert(db, result->key);

                    }
                }
            }

            if(input == 2)
                searchMenu(db,db);
        }
    }

    //
    void searchMenu(TNode* &db, TNode* &maindb)
    {
        Menu menu(16, "What would you like to search for? (search by ID is the fastest)");
        menu[0] = " ID";
        menu[1] = " First Name";
        menu[2] = " Middle Name/Initial";
        menu[3] = " Last Name";
        menu[4] = " Company";
        menu[5] = " Home Phone";
        menu[6] = " Office Phone";
        menu[7] = " Email";
        menu[8] = " Mobile Phone";
        menu[9] = "Street Address";
        menu[10] = "City";
        menu[11] = "State";
        menu[12] = "Zip Code";
        menu[13] = "Country";
        menu[14] = "Check all fields";
        menu[15] = "Exit search";



        while(true)
        {
            int input = menu.run();

            if(input == 16)
                return;

            TNode* results = nullptr;
            std::string search;
            bool exact;

            if(input == 15)
            {
                std::cout << "Enter search term: ";
                std::cin.ignore();
                getline(std::cin, search);
                exact = yesnoMenu("Search for exact match? (as opposed to a contains search)");
                searchTree(db, search, results, 14, exact);
            }

            else
            {
                std::cout << "Enter desired ";
                std::cout << menu[input -1] << ": ";
                std::cin.ignore();
                getline(std::cin, search);
                exact = yesnoMenu("Search for exact match? (as opposed to a contains search)");
                searchTree(db, search, results, input -1, exact);
            }

            std::cout << std::endl << "Results:" << std::endl << std::endl;
            int returnsize = getSize(results);
            sendOut(results, std::cout);
            std::cout << std::endl << returnsize << " result(s) found" << std::endl;

            if(returnsize == 1)
            {
                //show a menu for deletion or editing
                endsearchMenu(db, results, maindb);
                //this is so that the user doesn't have to exit through 15 search result menus
                //they already have what they want
                break;
            }

            else if(returnsize)//more than one result remains
                postsearchMenu(db, results, maindb);

                //this is so the user does'nt have to exit all of the searches manually
                break;
        }
    }

    void endsearchMenu(TNode* &db, TNode* &results, TNode* &maindb)
    {
        Menu menu(3, "Your search returned one result. What would you like to do with it?");
        menu[0] = "Edit it";
        menu[1] = "Delete it";
        menu[2] = "Exit search";

        while(true)
        {
        int input = menu.run();
        if(input == 3)
            return;

        if(input == 1)
        {
            //have to remove it and add it back after it's been edited
            maindb = rmNode(maindb, results->key);
            editContact(results->key);
            maindb = insert(maindb, results->key);
        }

        if(input == 2 && yesnoMenu("Are you sure you want to delete this contact?"))
            maindb = rmNode(maindb, results->key);
        }
    }

    void postsearchMenu(TNode* &db, TNode* &results, TNode* &maindb)
    {
        Menu menu(5, "What would you like to do with these results? ");
        menu[0] = "Sort them";
        menu[1] = "Refine them (search them again)";
        menu[2] = "Replace current database with this search";
        menu[3] = "Remove all results from the current Database";
        menu[4] = "Exit search";

        while(true)
        {
            int input = menu.run();
            if(input == 5)
                break;

            switch(input)
            {
                case 1:
                    sortMenu(results);
                    break;
                case 2:
                    searchMenu(results, maindb);
                    return;
                case 3:
                  delete maindb;
                    maindb = results;
                    break;
                case 4:
                    rmTree(maindb, results);
                    break;
            }
        }

    }

    //sorts the database, what else is there to say man
    void sortMenu(TNode* &db)
    {
        Menu menu(15, "What would you like to sort by?");
        menu[0] = " ID";
        menu[1] = " First Name";
        menu[2] = " Middle Name/Initial";
        menu[3] = " Last Name";
        menu[4] = " Company";
        menu[5] = " Home Phone";
        menu[6] = " Office Phone";
        menu[7] = " Email";
        menu[8] = " Mobile Phone";
        menu[9] = "Street Address";
        menu[10] = "City";
        menu[11] = "State";
        menu[12] = "Zip Code";
        menu[13] = "Country";
        menu[14] = "Cancel";

        int input = menu.run();
        if(input == 15)
            return;

        else
        {
            int selection = 0;
            if(yesnoMenu("Would you like to add a secondary sort parameter to that?"))
                selection = menu.run();
            //if they put "cancel" into the menu
            if(selection == 15)
                selection = 0;

            TNode* sorted = nullptr;
            std::cout << "Sorting..." << std::endl;

            //selection is by default 0, so the secondary sort would be the ID
            //if the user decided not to have the secondary sort
            sortTree(db, sorted, input-1, selection);
            db = sorted;

            std::cout << "Database sorted."<<std::endl << std::endl;
            //sendOut(sorted, std::cout);
        }
}

    //this is the menu where you can change the formatting of the output
    void refinedMenu(TNode* &db)
    {
        //the configuration is simple, there are three arrays
        //"appear" determines if the item shows up at all
        //"order" determines if the order is changed
        //"desc" determines what words are used to describe each category
        //they are stored in a txt file, three lines of 14 items
        //(I choose arrays for this since we know exactly how big they will always be)
        Menu menu(6, "Formatted output Menu:");
        menu[0] = "Load a format configuration";
        menu[1] = "Save current format to file";
        menu[2] = "Edit current format";
        menu[3] = "Preview formatted output";
        menu[4] = "Send formatted output to file";
        menu[5] = "Exit format Customization";

        int appear[14];
        int order[14];
        std::string desc[14];

        //this is a flag I'll use later to tell if a config is loaded
        appear[0] = -1;


       // //default configuration (in defconf.txt)
       // int appear[14], order[14];
       // std::string desc[14];
       // for(int i = 0; i < 14; i++)
       // {
       //     appear[i] = 1; //all elements appear by default
       //     order[i] = i;  //the order of the elements is from 0-13 by default
       // }

        ///These are just the names that I chose arbitrarily, for each field
       // desc[0] = "ID:\t\t\t";
       // desc[1] = "First Name:\t\t";
       // desc[2] = "Middle Name/Initial:\t";
       // desc[3] = "Last Name:\t\t";
       // desc[4] = "Company:\t\t";
       // desc[5] = "Home Phone:\t\t";
       // desc[6] = "Office Phone:\t\t";
       // desc[7] = "Email:\t\t\t";
       // desc[8] = "Mobile Phone:\t\t";
       // desc[9] = "Street Address:\t\t";
       // desc[10] = "City:\t\t\t";
       // desc[12] = "Zip Code:\t\t";
       // desc[11] = "State:\t\t\t";
       // desc[13] = "Country:\t\t";

        int index;

        while(true)
        {
            if(appear[0] == -1)
                std::cout << "WARNING: NO CONFIG FILE IS LOADED, LOAD A CONFIG FILE BEFORE ANYTHING ELSE" << std::endl;
            index = menu.run();

            if(index == 6)
                break;

            switch(index)
            {
                case 1:
                    configloadMenu(appear, order, desc);
                    break;
                case 2:
                    if(appear[0] == -1)
                    {
                        std::cout << "ERROR: NO CONFIG FILE LOADED" << std::endl;
                        break;
                    }

                    configsaveMenu(appear, order, desc);
                    break;
                case 3:
                    if(appear[0] == -1)
                    {
                        std::cout << "ERROR: NO CONFIG FILE LOADED" << std::endl;
                        break;
                    }

                    configeditMenu(appear, order, desc);
                    break;
                case 4:
                    if(appear[0] == -1)
                    {
                        std::cout << "ERROR: NO CONFIG FILE LOADED" << std::endl;
                        break;
                    }
                    formatPrint(db, std::cout, appear, order, desc);
                    break;
                case 5:
                    if(appear[0] == -1)
                    {
                        std::cout << "ERROR: NO CONFIG FILE LOADED" << std::endl;
                        break;
                    }
                    Menu printMenu(2, "Write formatted output to file");
                    printMenu[0] = "Specify file name";
                    printMenu[1] = "Exit";
                    int k = printMenu.run();
                    if(k == 2)
                        break;
                    std::string filename;
                    std::cout << "Specify file name: ";
                    std::cin >> filename;

                    std::ofstream fout;
                    fout.open(filename);

                    formatPrint(db, fout, appear, order, desc);
                    fout.close();
                    break;

            }
        }
    }


    void configloadMenu(int* appear, int* order, std::string* desc)
    {
        Menu configloadMenu(3, "Load config:");
        configloadMenu[0] = "Specify file name";
        configloadMenu[1] = "Use default config";
        configloadMenu[2] = "Exit Load config menu";

        int input = configloadMenu.run();

        if(input == 3)
            return;

        std::string filename;

        if(input == 1)
        {
            std::cin.ignore();
            std::cout << "File name for config file: ";
            getline(std::cin, filename);
        }

        if(input == 2)
            filename = "defConf.txt";

        if(!confisValid(filename))
        {
            std::cout << "FILE CHECK FAILED, EXITING..." << std::endl;
            return;
        }

        std::ifstream fin;
        fin.open(filename);

        std::string buffer;
        for(int i = 0; i < 14; i++)
        {
            getline(fin, buffer, '`');
            appear[i] = std::stoi(buffer);
        }
        for(int i = 0; i < 14; i++)
        {
            getline(fin, buffer, '`');
            order[i] = std::stoi(buffer);
        }

        for(int i = 0; i < 14; i++)
            getline(fin, desc[i], '`');

        return;
    }

    void configsaveMenu(int* appear, int* order, std::string* desc)
    {
        Menu menu(3, "Save config:");
        menu[0] = "Specify file name";
        menu[1] = "Use default config file defConf.txt (not recommended)";
        menu[2] = "Exit Save config menu";

        int input = menu.run();
        if(input == 3)
            return;

        std::string filename;

        if(input == 2)
            filename = "defConf.txt";

        if(input == 1)
        {
            std::cin.ignore();
            std::cout << "File name for config file: ";
            getline(std::cin, filename);
        }

        std::ofstream fout;
        fout.open(filename);

        for(int i = 0; i < 14; i++)
            fout << appear[i] << "` ";
        fout << std::endl;

        for(int i = 0; i < 14; i++)
            fout << order[i] << "` ";
        fout << std::endl;

        for(int i = 0; i < 14; i++)
            fout << desc[i] << "`";

        return;

    }

    void configeditMenu(int* appear, int* order, std::string* desc)
    {
       if(yesnoMenu("Do you wish to change which fields appear?"))
           for(int i = 0; i < 14; i++)
           {
               if(!yesnoMenu(desc[i]))
                   appear[i] = 0;
               else
                   appear[i] = 1;
           }
       if(yesnoMenu("Do you wish to change the order in which the fields appear?"))
       {
           Menu swapmenu(14,"Which one next?");
           for(int i = 0; i < 14; i++)
               swapmenu[i] = desc[i];

           int num;
           for(int i = 0; i < 14; i++)
           {
               std::cout << "Choose the next field to appear (field must be nonempty):" << std::endl;
               do
               {
                   num = swapmenu.run();
               }while(swapmenu[num-1] == "" && (num > 14 || num < 1));
               order[i] = num -1;
               swapmenu[num -1] = "";
           }
       }
       if(yesnoMenu("Do you wish to change the names of each field?"))
       {
           std::cout << "If you don't want to change a certain field, leave it blank" << std::endl;
           std::cout << "Be aware of the alignment and whitespace! (do not use the backtick symbol '`')" << std::endl;
           std::string holder = "";
           std::cin.ignore();
           for(int i = 0; i < 14; i++)
           {
               std::cout << "New name for:" << std::endl;
               std::cout << desc[order[i]] << std::endl;
               getline(std::cin, holder);
               if(holder  != "")
                   desc[order[i]] = holder;
           }
       }


    }
    //other useful ones
    bool yesnoMenu(std::string title)
    {
        Menu menu(2, title);
        menu[0] = "Yes";
        menu[1] = "No";

        int holder = menu.run();

        if(holder == 1)
            return true;
        if(holder == 2)
            return false;
    return false;
    }

    Contact createContact()
    {
        std::cout << "Creating a new contact..." << std::endl;
        Contact contact;
        std::string holder;
        std::cin.ignore();

        do
        {
            std::cout << "Enter 9 digit ID:\t\t";
            getline(std::cin, holder);
        }while(holder.length() != 9);
        contact[0] = holder;

        std::cout << "Enter first name:\t\t";
        getline(std::cin, holder);
        contact[1] = holder;

        std::cout << "Enter middle name/initial:\t";
        getline(std::cin, holder);
        contact[2] = holder;

        std::cout << "Enter last name:\t\t";
        getline(std::cin, holder);
        contact[3] = holder;

        std::cout << "Enter Company Name:\t\t";
        getline(std::cin, holder);
        contact[4] = holder;

        std::cout << "Enter Home Phone:\t\t";
        getline(std::cin, holder);
        contact[5] = holder;

        std::cout << "Enter Office Phone:\t\t";
        getline(std::cin, holder);
        contact[6] = holder;

        std::cout << "Enter Email:\t\t\t";
        getline(std::cin, holder);
        contact[7] = holder;

        std::cout << "Enter Mobile Phone:\t\t";
        getline(std::cin, holder);
        contact[8] = holder;

        std::cout << "Enter Street Address:\t\t";
        getline(std::cin, holder);
        contact[9] = holder;

        std::cout << "Enter City:\t\t\t";
        getline(std::cin, holder);
        contact[10] = holder;

        std::cout << "Enter State:\t\t\t";
        getline(std::cin, holder);
        contact[11] = holder;

        std::cout << "Enter Zip Code:\t\t\t";
        getline(std::cin, holder);
        contact[12] = holder;

        std::cout << "Enter Country:\t\t\t";
        getline(std::cin, holder);
        contact[13] = holder;

        std::cout << std::endl;

        std::string firstName, lastName, phone, email;

        while(yesnoMenu("Add an affiliate?"))
        {
            phone = email = "";

            std::cout << "Affiliate first name: ";
            std::cin >> firstName;

            std::cout << "Affiliate last name: ";
            std::cin >> lastName;

            if(yesnoMenu("Does the Affiliate have a seperate phone?"))
            {
                std::cout << "Affiliate phone: ";
                std::cin >> phone;

                if(yesnoMenu("Does the Affiliate have a seperate email?"))
                {
                    std::cout << "Affiliate email: ";
                    std::cin >> email;
                }
            }
            contact.mkAff(firstName, lastName, phone, email);
        }
        std::cout << std::endl <<  "Contact created." << std::endl;
        return contact;
    }


    //CHECK VALIDITY OF THE FILE AT filename (for databases)
    bool dbisValid(std::string filename)
    {
        std::cout << std::endl << "CHECKING FILE: " << filename << std::endl;
        std::ifstream fin;
        fin.open(filename);
        if(!fin.is_open())
        {
            std::cout << "ERROR: COULD NOT OPEN FILE" << std::endl;
            return false;
        }

        //trigger eof bit if it's the end of the file
        fin.peek();
        if(fin.eof())
        {
            std::cout << "ERROR: EMPTY FILE" << std::endl;
            return false;
        }

        std::string tests;

        //current helps to tell the user which contact the error occurred at (if there was one)
        int current = 1;
        while(fin.good())
        {
            //CHECK ID
            //////////////////////////////////////
            getline(fin, tests);
            if(tests.length() != 9)
            {
                std::cout << "ERROR: BAD ID \"" << tests << "\" (Contact #" << current << ")" << std::endl;
                return false;
            }
            //////////////////////////////////////



            //CHECK THE NUMBER OF FIELDS, AND THAT THE FIELDS HAVE ENDED PROPERLY
            //////////////////////////////////////
            //there must be 13 fields here
            for(int i = 0; i < 13; i++)
              {
                getline(fin, tests);
                if(tests[0] == '|')
                  {
                    std::cout << "ERROR: NOT ENOUGH FIELDS FOR CONTACT #" << current << std::endl;
                    return false;
                  }
              }


            //CHECK FOR PROBLEMS WITH AFFILIATES
            ///////////////////////////////////
            //i used to report the affiliate where the error occurred (if there was one)
            int i = 1;
            while(fin.peek() != '|')
            {
              fin >> tests;                        //First name in
              getline(fin, tests);
              if(tests[tests.length()-1] != ';')
                {
                    std::cout << "ERROR: BAD AFFILIATE DELIMITER (Contact #" << current << ", Affiliate #" << i << ')' << std::endl;
                    std::cout << "Expected: ';' at affiliate no. " << i << ", Got: " << tests[tests.length()-1] << std::endl;
                    return false;
                }
                i++;
            }
            ///////////////////////////////////

            //ignore the '|' and '\n', and start looking at the next contacts ID
            fin.ignore();
            fin.ignore();

            //flip eof if we're there
            fin.peek();
            //iterate the current contact being worked with, this is for error reporting
            current++;
        }

        fin.close();

        std::cout << "FILE OK..." << std::endl;
        return true;
    }

    //checks to see if "filename" is a valid config file
    bool confisValid(std::string filename)
    {
        std::cout << std::endl << "CHECKING FILE: " << filename << std::endl;
        std::ifstream fin;
        fin.open(filename);
        if(!(fin.is_open()))
        {
            std::cout << "ERROR: COULD NOT OPEN FILE" << std::endl;
            return false;
        }

        //trigger eof bit if the file is empty
        fin.peek();

        if(fin.eof())
        {
            std::cout << "ERROR: FILE IS EMPTY" << std::endl;
            return false;
        }

        std::string str;

        for(int i = 0; i < 14; i++)
        {
            getline(fin, str, '`');
            if(std::stoi(str) != 1 && std::stoi(str) != 0)
            {
                std::cout << "ERROR: INVALID ENTRY FOR \"appear\" (must be 0 or 1, got " << str << ")" << std::endl;
                return false;
            }
        }

        if(fin.peek() != ' ')
        {
            std::cout << fin.peek();
            std::cout << "ERROR: TOO MANY ELEMENTS IN \"appear\" (works for exactly 14)" << std::endl;
            return false;
        }

        int array[14];
        int j;
        for(int i = 0; i < 14; i++)
        {
            getline(fin, str, '`');
            j = std::stoi(str);
            if(j > 13 || j < 0 )
            {
                std::cout << "ERROR: OUT OF RANGE (0-13 expected, got " << str << ")" << std::endl;
                return false;
            }

            array[i] = j;

            for(int k = 0; k < i; k++)
                if(j == array[k])
                {
                   std::cout << "ERROR: REPEATED INDEX IN \"order\" (got " << j << " twice)" << std::endl;
                   return false;
                }

        }

        if(fin.peek() != ' ')
        {
            std::cout << "ERROR: TOO MANY ELEMENTS IN \"order\"" << std::endl;
            return false;
        }
        fin.ignore(256, '\n');

        for(int i = 0; i < 14; i++)
            getline(fin, str, '`');

        //provoke the eof bit, if there is any more after this the file is not right
        fin.peek();
        if(!fin.eof())
        {
            std::cout << "ERROR: INCORRECT NUMBER OF ELEMENTS IN \"desc\"" << std::endl;
            return false;
        }

        //to get here is to pass all of the tests
        std::cout << "FILE OK" << std::endl;
        return true;
    }

    //editContact is here, and editAff is in the Contact.cpp file (this is because it requires friendship)
    void editContact(Contact& contact)
    {
        Menu menu(16, "Choose a field to modify:");
        menu[0] = " ID";
        menu[1] = " First Name";
        menu[2] = " Middle Name/Initial";
        menu[3] = " Last Name";
        menu[4] = " Company";
        menu[5] = " Home Phone";
        menu[6] = " Office Phone";
        menu[7] = " Email";
        menu[8] = " Mobile Phone";
        menu[9] = "Street Address";
        menu[10] = "City";
        menu[11] = "State";
        menu[12] = "Zip Code";
        menu[13] = "Country";
        menu[14] = "Modify Affiliates";
        menu[15] = "Exit";

        while(true)
        {
            std::cout << std::endl <<  "Current contact: " << std::endl << std::endl;
            std::cout << contact << std::endl;

            int input = menu.run();
            if(input == 16)
                break;

            if(input == 1)
            {
                std::string id;
                std::cout << "Enter a 9 digit ID: ";
                std::cin.ignore();
                getline(std::cin, id);
                if(id.length() != 9)
                    std::cout << "Invalid ID (not 9 digits). No changes made." << std::endl;
                else
                    contact[0] = id;
            }

            else if(input < 15)
            {
                std::string in;
                std::cout << "Enter new " << menu[input-1] << ": ";
                std::cin.ignore();
                getline(std::cin, in);
                contact[input-1] = in;
                std::cout << menu[input-1] << " changed to " << in << std::endl;
            }

            if(input == 15)
                editAff(contact);
        }
    }
}
