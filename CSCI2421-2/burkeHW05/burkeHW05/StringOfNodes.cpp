//Dalton Burke
//StringOfNodes.cpp
//contains implementation of member functions for "StringOfNodes" class
//burkeHW05 CSCI2421

#include "StringOfNodes.h"

namespace burke
{
  CNode::CNode(char data, CNode* next)
  {
    __data = data;
    __next = next;
  }

  CNode::CNode(char data)
  {
    __data = data;
    __next = nullptr;
  }

  CNode::~CNode()
  {
    delete __next;
  }

  StringOfNodes::StringOfNodes()
  {
    __headptr = nullptr;
    __size = 0;
  }

  StringOfNodes::StringOfNodes(const StringOfNodes& copy)
  {
    //copy constructor helpful when we do the + operator
    //also could be useful if the code needs to be expanded for
    //some other functionality
    __headptr = nullptr;
    __size = copy.__size;

    CNode* copyptr = copy.__headptr;

    while(copyptr)
    {
      insertBack(copyptr->__data);
      copyptr = copyptr->__next;
    }
  }

  StringOfNodes::~StringOfNodes()
  {
    delete __headptr;
  }

  int StringOfNodes::size()
  {
    return __size;
  }

  CNode* StringOfNodes::begin()
  {
    //return pointer to the first element in the list
    return __headptr;
  }

  CNode* StringOfNodes::end()
  {
    if(!__headptr) //if it's empty then just send back nullptr
      return nullptr;

    CNode* current = __headptr;
    while(current->__next) //go to the end of the list
      current = current->__next;

    return current; //return the pointer to the last element of the list
  }

  CNode* StringOfNodes::operator[](int index)
  {
    //if out of bounds send back nullptr
    if(index < 0 || index >= __size)
      return nullptr;

    CNode* current = __headptr;

    //crawl til you get the ith node
    for(int i = 0; i < index; i++)
        current = current->__next;

    //send back a pointer to the ith node
    return current;
  }

  void StringOfNodes::insertFront(char data)
  {
    CNode* newHead = new CNode(data, __headptr);
    __headptr = newHead;
    __size++;
  }

  void StringOfNodes::insertBack(char data)
  {
    //if it's empty just add it to the front instead
    if(!__headptr)
    {
      insertFront(data);
      return;
    }

    //otherwise get to the end, and add the last one in at the end
    //using the data constructor so the final pointer is now nullptr
    //with little effort.
    CNode* currEnd = end();
    CNode* newEnd = new CNode(data);

    currEnd->__next = newEnd;
    __size++;
  }

  bool StringOfNodes::insert(char data, int pos)
  {
    //check special cases
    if(pos < 0 || pos > __size)
      return false;

    if(!__headptr && pos != 0)
      return false;

    if(pos == 0)
    {
      insertFront(data);
      return true;
    }

    if(pos == __size - 1)
    {
      insertBack(data);
      return true;
    }

    //no special cases, grab the node at the position right before
    //our index and insert it after that, using the constructor which
    //copies the __next field of the next node

    CNode* newNode = new CNode(data, operator[](pos));
    CNode* current = operator[](pos-1);
    current->__next = newNode;
    __size++;
    return true;
  }

  StringOfNodes operator+(StringOfNodes lhs, StringOfNodes rhs)
  {
    //if we are adding an empty, just send back the first arg
    if(!rhs.__headptr)
      return lhs;

    //use copy constructor because we're smart
    StringOfNodes stringSum(lhs);

    //add each element of rhs to the back of the new sum
    CNode* current = rhs.__headptr;
    while(current)
    {
      stringSum.insertBack(current->__data);
      current = current->__next;
    }

    //send the sum back
    return stringSum;
  }

  std::ostream& operator<<(std::ostream& os, StringOfNodes str)
  {
    //send each piece of data out one at a time
    CNode* current = str.__headptr;
    while(current)
      {
        os << current->__data;
        current = current->__next;
      }
    return os;
  }

}
