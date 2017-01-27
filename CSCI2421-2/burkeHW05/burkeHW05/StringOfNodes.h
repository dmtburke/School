//Dalton Burke
//StringOfNodes.h
//contains declaration of "StringOfNodes" and "CNode" classes and member functions
//burkeHW05 CSCI2421

#include <iostream>

namespace burke
{

  struct CNode
  {
    char __data;
    CNode* __next;

    //Take data and __next field
    CNode(char data, CNode* next);

    //Take data and assume next is nullptr
    CNode(char data);

    ~CNode();
  };

  class StringOfNodes
  {
  private:
    CNode* __headptr;
    int __size;

  public:
    StringOfNodes();
    StringOfNodes(const StringOfNodes& copy);
    ~StringOfNodes();

    //returns __size
    int size();

    //returns pointers to first and last nodes in the list
    CNode* begin();
    CNode* end();

    //returns pointer to given node in ith position in the list
    CNode* operator[](int index);

    //insert at the front of the list, at the end, or somewhere inbetween.
    //return on insert is the success of the insert
    void insertFront(char value);
    bool insert(char value, int pos);
    void insertBack(char value);

    //functions for adding two strings and outputting them to the console
    friend StringOfNodes operator+(StringOfNodes lhs, StringOfNodes rhs);
    friend std::ostream& operator<<(std::ostream& os, StringOfNodes str);
  };

  StringOfNodes operator+(StringOfNodes lhs, StringOfNodes rhs);
  std::ostream& operator<<(std::ostream& os, StringOfNodes str);
}
