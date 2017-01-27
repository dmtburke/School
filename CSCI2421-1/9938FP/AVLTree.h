//Dalton Burke 102279938
//AVLTree.h
//Declaration of AVLTree class, the main DS to hold the Contacts

#ifndef DATABASE_AVLTREE_H
#define DATABASE_AVLTREE_H

#include"Contact.h"

namespace database
{
    struct TNode
    {
        //using
        Contact key;
        TNode* left;
        TNode* right;
        TNode(Contact c);

        //TNode(Contact k);
    };

    //height helps with diff, which helps with the rot functions
    //which help with the balance function
    int height(TNode* node);
    int diff(TNode* node);

    //these make balance easier
    TNode* rotRR(TNode* node);
    TNode* rotRL(TNode* node);
    TNode* rotLR(TNode* node);
    TNode* rotLL(TNode* node);

    //balance makes the tree more uniform, and insert inserts a new node at the right spot
    TNode* balance(TNode* node, int field = 0);
    TNode* insert(TNode* node, const Contact& contact, unsigned int f1 = 0, unsigned f2 = 1);

    //functions to facilitate deletion of a node
    TNode* findMin(TNode* node);
    TNode* rmMin(TNode* node);
    TNode* rmNode(TNode* &node, Contact contact);
    //this is going to be like an asymmetric difference, all of the elements which are in lhs, but not in rhs
    void rmTree(TNode* &lhs, TNode* rhs);

    //function to search a Tree for a given ID
    TNode* searchID(TNode* &node, std::string id);

    //this will sort according to a given field
    void sort(TNode* node, int field);

    void sortTree(TNode* node, TNode* &destination, unsigned int field1 = 0, unsigned int field2 = 1);
    void searchTree(TNode* node, std::string search, TNode* &retnode, unsigned int f = 14, bool exact = false);
    int getSize(TNode* node);
    void sendOut(TNode* node, std::ostream &os);
    void formatPrint(TNode* node, std::ostream &os, int* appear, int* order,
            std::string* desc, std::string seperator = "___________________________________________________________");
}
#endif //DATABASE_AVLTREE_H
