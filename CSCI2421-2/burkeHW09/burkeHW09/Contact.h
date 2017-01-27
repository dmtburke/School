//Dalton Burke
//102279938
//Declaration of "Contact" class
//a contact holds all of the relevant information for an "address book"

#ifndef DATABASE_CONTACT_H
#define DATABASE_CONTACT_H



#include<iostream>
#include<string>

namespace database
{
    class Node;
    struct ANode;

    class Contact
    {
        std::string* __fields;
        //__fields holds a dynamic array of strings which contains all of the fields
        //in the order that they appear, this is a little abstract, but saves a lot
        //for reference:
        //__fields[0]  -> id
        //__fields[1]  -> First Name
        //__fields[2]  -> Middle Name/Initial
        //__fields[3]  -> Last Name
        //__fields[4]  -> Company Name
        //__fields[5]  -> Home Phone
        //__fields[6]  -> Office Phone
        //__fields[7]  -> Email
        //__fields[8]  -> Mobile Number
        //__fields[9]  -> Street Address
        //__fields[10] -> City
        //__fields[11] -> State
        //__fields[12] -> Zip Code
        //__fields[13] -> Country

        // an Affiliate is a contact, made as a copy, and with some select fields modified
        ANode* __affPtr;

    public:
        //constructors, etc
        Contact();
        ~Contact();
        //copy constructor has an option for disabling the copy of the affiliates,
        //useful for making affiliates from a contact.
        Contact(const Contact& cont, bool affiliates = true);

        //assignment operator
        Contact& operator=(const Contact& c);

        //subscript for getting and setting __fields
        std::string& operator[](unsigned int index);
        const std::string& operator[](unsigned int index) const;

        //this functions tells you if the selected string is in the Contact
        //using the second parameter will tell you if the string is in there exactly
        bool contains(std::string search, int field = 14, bool exact = false);

        //Affiliate management

        //to simplify the copy constructor and the assignment operator
        //makes a copy of a linked list of affiliates
        ANode* cpyAff() const;

        //add and remove affiliates, add will be used when reading in from file and by the user when in menu
        void mkAff(std::string firstName, std::string lastName, std::string phone = "", std::string email = "");

        //rmAff will primarily be used by a user looking at a menu
        //the input is the position in the menu corresponding to the desired affiliate to be removed
        void rmAff(unsigned int choice);

        //gives the number of affiliates corresponding to the given contact
        unsigned int numAff();


        //friends
        friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
        friend std::istream& operator>>(std::istream& is, Contact& contact);
        friend void formatPrint(TNode* node, std::ostream &os, int* appear, int* order, std::string* desc, std::string seperator);
        friend bool operator==(const Contact& c1, const Contact& c2);
        friend void editAff(Contact &contact);

    };

    //ANodes will be used to store a linked list of Affiliates for each contact.
    struct ANode
    {
        //members
        Contact __contact; //need dynamic allocation for copyability
        ANode* __next;

        //functions
        ANode(Contact contact, ANode* next);
    };


}
#endif //DATABASE_CONTACT_H
