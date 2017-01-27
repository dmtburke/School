#ifndef NODE_
#define NODE_
#include <iostream>
using namespace std;

// A generic tree node class

//Placeholder for a composite data type
class Datatype{
private:
    int number;
    

};

//Binary Tree Node
class Node {
private:
    int key;
    Datatype data;
    Node* left;
    Node* right;
    Node* parent;
public:
    Node() { key=-1; left=nullptr; right=nullptr; parent = nullptr;};
    void setKey(int aKey) { key = aKey; };
    void setLeft(Node* aLeft) { left = aLeft; };
    void setRight(Node* aRight) { right = aRight; };
    void setParent(Node* aParent) { parent = aParent; };
    int Key() { return key; };
    Node* Left() { return left; };
    Node* Right() { return right; };
    Node* Parent() { return parent; };
};



#endif
