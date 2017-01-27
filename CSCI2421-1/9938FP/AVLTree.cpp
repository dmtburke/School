//Dalton Burke 102279938
//AVLTree.cpp
//Implementation of AVLTree methods

#include"AVLTree.h"

namespace database
{
    TNode::TNode(Contact c):
        key(c),
        left(nullptr),
        right(nullptr)
    {}

        int height(TNode* node)
    {
        int h = 0;
        if(node)
        {
            int heightL = height(node->left);
            int heightR = height(node->right);
            int heightMax = std::max(heightL, heightR);
            h = heightMax + 1;
        }
        return h;
    }

    int diff(TNode* node)
    {
        int heightL = height(node->left);
        int heightR = height(node->right);
        int bfactor = heightL - heightR;
        return bfactor;
    }

    TNode* rotRR(TNode* node)
    {
        TNode* temp;
        temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

    TNode* rotRL(TNode* node)
    {
        TNode* temp;
        temp = node->right;
        node->right = rotLL(temp);
        return rotRR(node);
    }

    TNode* rotLR(TNode* node)
    {
        TNode* temp;
        temp = node->left;
        node->left = rotRR(temp);
        return rotLL(node);
    }

    TNode* rotLL(TNode* node)
    {
        TNode* temp;
        temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }

    TNode* balance(TNode* node, int field )
    {
        int bfactor = diff(node);

        if(bfactor > 1)
        {
            if(diff(node->left) > 0)
                node = rotLL(node);
            else
                node = rotLR(node);
        }

        else if(bfactor < -1)
        {
            if(diff(node->right) > 0)
                node = rotRL(node);
            else
                node = rotRR(node);
        }
        return node;
    }

    TNode* insert(TNode* node,const Contact& contact, unsigned int f1, unsigned int f2)
    {
        if(f1 == 14)
            f1 = 0;
        if(!node)
            return new TNode(contact);

        if(node->key == contact)
            return node;

        else if(contact[f1] < node->key[f1])
        {
            node->left = insert(node->left, contact, f1, f2);
            node = balance(node);
        }

        else if(contact[f1] > node->key[f1])
        {
            node->right = insert(node->right, contact, f1, f2);
            node = balance(node);
        }

        else if(contact[f1] == node->key[f1])
        {
            //I could probably do something recursive here
            //like node = insert(node, contact, f2)
            //but there would be problems when that one went recurse

            if(contact[f2] < node->key[f2])
            {
                node->left = insert(node->left, contact, f1, f2);
                node = balance(node);
            }

            else if(contact[f2] >= node->key[f2])
            {
                node->right = insert(node->right, contact, f1, f2);
                node = balance(node);
            }

        }

        return node;
    }

    TNode* findMin(TNode* node)
    {
        return node->left?findMin(node->left):node;
    }

    TNode* rmMin(TNode* node)
    {
        if(!node->left)
            return node->right;
        node->left = rmMin(node->left);
        return balance(node);
    }

    TNode* rmNode(TNode* &node, Contact contact)
    {
        if(!node)
            return nullptr;
        if(contact[0] < node->key[0])
            node->left = rmNode(node->left, contact);
        else if(contact[0] > node->key[0])
            node->right = rmNode(node->right, contact);
        else
        {
            TNode* l = node->left;
            TNode* r = node->right;
            delete node;
            if(!r)
                return l;
            TNode* min = findMin(r);
            min->right = rmMin(r);
            min->left = l;
            return balance(min);
        }
        return balance(node);
    }

    void rmTree(TNode* &lhs, TNode* rhs)
    {
        if(!rhs)
            return;
        lhs = rmNode(lhs, rhs->key);
        rmTree(lhs,rhs->right);
        rmTree(lhs,rhs->left);
    }

    TNode* searchID(TNode* &node, std::string id)
    {
        if(id < node->key[0])
            return searchID(node->left, id);
        else if(id > node->key[0])
            return searchID(node->right, id);
        else if(id == node->key[0])
            return node;
        else
            return nullptr;
    }

    //returns the size of a tree given the head node
    int getSize(TNode* node)
    {
        if(!node)
            return 0;

        int size;
        size = 1 + getSize(node->left) + getSize(node->right);

        return size;
    }


    void sendOut(TNode* node, std::ostream &os)
    {
        if(node)
        {
            sendOut(node->left, os);
            os << node->key << '|' << std::endl;
            sendOut(node->right, os);
        }
    }

    void formatPrint(TNode* node, std::ostream &os, int* appear, int* order, std::string* desc, std::string seperator)
    {
        if(node)
        {

            //doing the left side first means that when they come out they will be sorted however the tree was sorted
            formatPrint(node->left, os, appear, order, desc);

            //send out all of the fields for the base contact
            os << seperator << std::endl << std::endl;
            for(int i = 0; i < 14; i++)
                if(appear[order[i]])
                    os << desc[order[i]] << node->key[order[i]] << std::endl;
            os << std::endl;

            //now affiliates
            if(node->key.__affPtr)
            {
                os << "---Affiliates---" << std::endl;

                ANode* cursor = node->key.__affPtr;
                while(cursor)
                {
                    if(appear[1])
                        os << desc[1] << (cursor->__contact)[1] << std::endl;

                    if(appear[3])
                        os << desc[3] << (cursor->__contact)[3] << std::endl;

                    if(appear[order[8]] && (cursor->__contact)[8] != "" && (cursor->__contact)[8] != node->key[8])
                        os << desc[8] << (cursor->__contact)[8] << std::endl;

                    if(appear[7] && (cursor->__contact)[7] != "" && (cursor->__contact)[7] != node->key[7])
                        os << desc[7] << (cursor->__contact)[7] << std::endl;

                    os << std::endl;
                    cursor = cursor->__next;
                }
            }

            //likewise, doing the right after sending the node out means that they come out in the order that they were sorted
            formatPrint(node->right, os, appear, order, desc);
        }
    }

    void searchTree(TNode* node, std::string search, TNode* &retnode, unsigned int f, bool exact)
    {
        if(!node)
            return;

        if(node->key.contains(search, f, exact))
            retnode = insert(retnode, node->key, f);

        searchTree(node->left,  search, retnode, f, exact);
        searchTree(node->right, search, retnode, f, exact);

        return;
    }

    //this just takes an empty tree and uses insert to fill it so that it's in order
    void sortTree(TNode* node, TNode* &destination, unsigned int field1, unsigned int field2)
    {
        if(!node)
            return;

        destination = insert(destination, node->key, field1, field2);

        sortTree(node->left , destination, field1, field2);
        sortTree(node->right, destination, field1, field2);
    }
}
