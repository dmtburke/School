//Dalton Burke 102279938
//Contact.cpp
//Implementation of the Contact class, and ANode struct

#include"Contact.h"
#include"Menu.h"
#include"MenuFunctions.h"
#include"AVLTree.h"
#include<fstream>
#include<cassert>

namespace database
{
    //Contact stuff
    Contact::Contact()
    {
        __fields = new std::string[14];
        for(int i = 0; i < 14; i++)
            __fields[i] = "------";
        //assume num affiliates = 0
        __affPtr = nullptr;
    } //there are 14 different fields, check Contact.h for details

    //copy constructor, primarily used for making affiliates
    Contact::Contact(const Contact& contact, bool affiliates)
    {
        __fields = new std::string[14];
        for(int i = 0; i < 14; i++)
            __fields[i] = contact[i];

        //only copy the affiliates if they exist, and if you want to do that
        if(affiliates && contact.__affPtr)
            __affPtr = contact.cpyAff();

        else
            __affPtr = nullptr;
    }

    //assignment operator
    Contact& Contact::operator=(const Contact& c)
    {
        if(*this == c)
            return *this;

        //overwrite old fields
        for(int i = 0; i < 14; i++)
            this->__fields[i] = c[i];

        //clear out the old affiliates, and copy the new ones
        if(__affPtr)
        {
            ANode* deleter = __affPtr;
            ANode* holder;
            while(deleter)
            {
                holder = deleter;
                deleter = deleter->__next;
                delete holder;
            }
        }

        if(c.__affPtr)
            __affPtr = c.cpyAff();

        return *this;
    }

    //destructor clears all dynamically allocated memory
    Contact::~Contact()
    {
        delete [] __fields;
        ANode* deleter = __affPtr;
        ANode* holder;
        while(deleter)
        {
            holder = deleter;
            deleter = deleter->__next;
            delete holder;
        }
    }

    //const and non-const subscript operators for getting and setting __fields element
    std::string& Contact::operator[](unsigned int index)
    {
         assert(!(index >= 14 || index < 0));
         return __fields[index];
    }

    const std::string& Contact::operator[](unsigned int index) const
    {
        assert(!(index >= 14 || index < 0)); //outofbounds
        return __fields[index];
    }

    bool Contact::contains(std::string search, int field, bool exact)
    {
        //checking the fields first
        if(exact)
        {
            //field == 14 means we search all fields
            if(field == 14)
            {
                for(int i = 0; i < 14; i++)
                    if(search == __fields[i])
                        return true;

                ANode* cursor = __affPtr;
                while(cursor)
                {
                    if(search == (cursor->__contact)[1] ||
                       search == (cursor->__contact)[3] ||
                       search == (cursor->__contact)[8] ||
                       search == (cursor->__contact)[7]  )
                       return true;
                    cursor = cursor->__next;
                }
            }

            else
            {
                if(search == __fields[field])
                    return true;
                //checking the affiliates
                if(field == 1 || field == 3 || field == 8 || field == 7)
                {
                    ANode* cursor = __affPtr;
                    while(cursor)
                    {
                        if(search == (cursor->__contact)[field])
                           return true;
                        cursor = cursor->__next;
                    }
                }
            }
            return false;
        }

        if(!exact)
        {            //field == 14 means we search all fields
            if(field == 14)
            {
                for(int i = 0; i < 14; i++)
                    if(__fields[i].find(search) != std::string::npos)
                        return true;

                ANode* cursor = __affPtr;
                while(cursor)
                {
                    if((cursor->__contact)[1].find(search) != std::string::npos ||
                       (cursor->__contact)[3].find(search) != std::string::npos ||
                       (cursor->__contact)[8].find(search) != std::string::npos ||
                       (cursor->__contact)[7].find(search) != std::string::npos  )
                        return true;
                    cursor = cursor->__next;
                }
            }


            else
            {
                if(__fields[field].find(search) != std::string::npos)
                    return true;

                //checking the affiliates
                if(field == 1 || field == 3 || field == 8 || field == 7)
                {
                    ANode* cursor = __affPtr;
                    while(cursor)
                    {
                        if(cursor->__contact[field].find(search) != std::string::npos)
                            return true;
                        cursor = cursor->__next;
                    }
                }
            }
        }
        return false;
    }

    //For copying the list of Affiliates
    ANode* Contact::cpyAff() const
    {
        if(!__affPtr)
            return nullptr;

        ANode* copy, * head;
        ANode* original = __affPtr;

        copy = new ANode(original->__contact, nullptr);
        head = copy;//this is what we will return

        while(original->__next)
        {
            copy->__next = new ANode(original->__next->__contact, nullptr);

            copy = copy->__next;
            original = original->__next;
        }

        return head;
    }

    //mkAffiliate for adding affiliates to a Contact
    void Contact::mkAff(std::string firstName, std::string lastName,
                        std::string phone,     std::string email    )
    {
        ANode* newAff =  new ANode(Contact(*this, false), nullptr);

        if(!__affPtr)
            __affPtr = newAff;

        else
        {
            ANode* cursor = __affPtr;
            while(cursor->__next)
                cursor = cursor->__next;
            cursor->__next = newAff;
        }

        (newAff->__contact)[1] = firstName;
        (newAff->__contact)[3] = lastName;

        //__fields[8] is the mobile phone field
        if(phone != "")
            (newAff->__contact)[8] = phone;

        //__fields[7] is the email field
        if(email != "")
            (newAff->__contact)[7] = email;

    }

    void Contact::rmAff(unsigned int rm)
    {
        //if we only ever use this function from a menu, we should never need this
        if(rm > numAff() || rm < 1)
        {
            std::cout << "ERROR: BAD INDEX, NO CHANGES MADE" << std::endl;
            return;
        }

        ANode* deleter = __affPtr;
        if(rm == 1) //gotta kill the first node
        {
            __affPtr = __affPtr->__next;
            delete deleter;
            return;
        }

        //shift to the one right before what we seek to delete
        for(unsigned int i = 1; i < rm-1; i++)
            deleter = deleter->__next;

        //we are assuming that deleter->next is not the nullptr
        //we checked for this at the start by requiring 0 < index < size of the linked list
        ANode* holder = deleter->__next;
        deleter->__next = (deleter->__next)->__next;
        delete holder;
    }

    unsigned int Contact::numAff()
    {
        ANode* counter = __affPtr;
        unsigned int size = 0;
        while(counter)
        {
             counter = counter->__next;
             size++;
        }
        return size;
    }


    std::ostream& operator<<(std::ostream& os, const Contact& contact)
    {
        for(int i = 0; i < 14; i++)
            os << contact.__fields[i] << std::endl;

        //also output affiliates
        if(contact.__affPtr)
        {
            int i = 1;
            ANode* printer = contact.__affPtr;
            while(printer)
            {
                os << "Affiliate " << i << ": "
                   << (printer->__contact)[1] << " " << (printer->__contact)[3];

                //if the affiliate has their own phone number, print that
                if((printer->__contact)[8] != contact[8])
                    os << ", " << (printer->__contact)[8];

                //if the affiliate has their own email, print that
                if((printer->__contact)[7] != contact[7])
                    os << ", " << (printer->__contact)[7];

                os << ';' << std::endl;

                printer = printer->__next;
                i++;
            }
        }

        return os;
    }

    std::istream& operator>>(std::istream &is, Contact& contact)
    {
        for(int i = 0; i < 14; i++)
            std::getline(is, contact[i]);

        std::string firstName, lastName, phone = "", email = "";
        while(is.peek() == 'A')
        {
            is.ignore(256, ':');
            is >> firstName;
            is >> lastName;

            if(lastName[lastName.length() - 1] != ';')
            {
                is >> phone;
                if(phone[phone.length() - 1] != ';')
                     is>>email;
                     //std::getline(is, email, ';');
            }

            //get rid of the comma, or the ;
            lastName = lastName.substr(0, lastName.length() -1);

            if(phone != "")
                phone = phone.substr(0,phone.length() -1);

            if(email != "")
                email = email.substr(0,email.length() -1);

            contact.mkAff(firstName, lastName, phone, email);

            is.ignore(); //ignore the '\n'

            //reset the variables
            firstName = lastName = phone = email = "";
        }
        return is;
    }

    //== operator
    bool operator==(const Contact& c1, const Contact& c2)
    {
        for(int i = 0; i < 14; i++)
            if(c1[i] != c2[i])
                return false;

        //if one is nu
        ANode* a1 = c1.__affPtr, *a2 = c2.__affPtr;

        //if either is null, we just move on
        while(a1 && a2)
        {
            //recursive call here is fine, affiliates don't have affiliates, just relax
            if(!(a1->__contact == a2->__contact))
                return false;

            a1 = a1->__next;
            a2 = a2->__next;
        }

        //if they are not both null, then they are not equal
        if(a1 || a2)
            return false;

        return true;
    }

    void editAff(Contact &contact)
    {
        Menu menu(4, "Modify Affiliates:");
        menu[0] = "Add an Affiliate";
        menu[1] = "Remove an Affiliate";
        menu[2] = "Edit an Affiliate";
        menu[3] = "Exit";

        while(true)
        {
            std::cout << "Current Contact: "<< std::endl << std::endl;
            std::cout << contact << std::endl;
            int input = menu.run();
            if(input == 4)
                break;

            else if(input == 1)
            {
                //firstname, last name, mobile phone, email
                std::string fn, ln, mp = "", em = "";
                std::cout << "Affiliates first name: ";
                std::cin >> fn;
                std::cout << "Affiliates last name: ";
                std::cin >> ln;
                if(yesnoMenu("Does the affiliate have a seperate mobile phone?"))
                {
                    std::cout << "Affiliates mobile phone: ";
                    std::cin >> mp;

                    if(yesnoMenu("Does the affiliate have a seperate email address?"))
                    {
                        std::cout << "Affiliates email address: ";
                        std::cin >> em;
                    }
                }
                contact.mkAff(fn,ln,mp,em);
                std::cout << std::endl << "Affiliate added." << std::endl;
            }

            else if(input == 2)
            {
                if(contact.numAff() == 0)
                    std::cout << "There are no affiliates to be removed." << std::endl;

                else
                {
                    Menu rmMenu(contact.numAff(), "Which affiliate would you like to remove?");
                    ANode* cursor = contact.__affPtr;
                    int i = 0;
                    while(cursor)
                    {
                        rmMenu[i] = cursor->__contact[1] + " " + cursor->__contact[3];
                        cursor = cursor->__next;
                        i++;
                    }
                    int selection = rmMenu.run();
                    if(yesnoMenu("Are you sure you want to delete " + rmMenu[selection-1]))
                    {
                        contact.rmAff(selection);
                        std::cout << "Affiliate removed." << std::endl << std::endl;
                    }
                }
            }

            else if(input == 3)
            {
                if(contact.numAff() == 0)
                    std::cout << "There are no affiliates to be editted." << std::endl;

                else
                {
                    Menu editMenu(contact.numAff(), "Which affiliate would you like to edit?");
                    ANode* cursor = contact.__affPtr;
                    int i = 0;
                    while(cursor)
                    {
                        editMenu[i] = cursor->__contact[1] + " " + cursor->__contact[3];
                        cursor = cursor->__next;
                        i++;
                    }
                    int selection = editMenu.run();
                    cursor = contact.__affPtr;
                    //move to the affiliate we want to edit
                    for(int k = 0; k < selection -1; k++)
                        cursor = cursor->__next;

                    std::string bfr;
                    if(yesnoMenu("Edit first name?"))
                    {
                        std::cout << "New first name: ";
                        std::cin >> bfr;
                        cursor->__contact[1] = bfr;
                    }

                    if(yesnoMenu("Edit last name?"))
                    {
                        std::cout << "New last name: ";
                        std::cin >> bfr;
                        cursor->__contact[3] = bfr;
                    }

                    if(yesnoMenu("Edit mobile phone number?"))
                    {
                        std::cout << "New mobile phone number (leaving this blank removes the field): ";
                        std::cin.ignore();
                        getline(std::cin, bfr);
                        cursor->__contact[8] = bfr;
                    }

                    if(cursor->__contact[8] == "")
                    {
                        cursor->__contact[7] = contact[7];
                        cursor->__contact[8] = contact[8];
                    }

                    //can't have an affiliate email without already having a phone number. I didn't make the rules here.
                    //also, short circuiting saves the day here
                    if(cursor->__contact[8] != contact[8] && yesnoMenu("Edit email address?"))
                    {
                        std::cout << "New email address (leaving this blank removes the field): ";
                        std::cin.ignore();
                        getline(std::cin,bfr);
                        cursor->__contact[7] = bfr;
                    }
                }
            }
        }
    }


    //end contact stuff

    //ANode stuff
    ANode::ANode(Contact contact, ANode* next)
    {
        __contact = Contact(contact, false); //this is for an affiliate, do not copy other affiliates
        __next= next;
    }

    //end ANode stuff

    //Nonmembers
}
