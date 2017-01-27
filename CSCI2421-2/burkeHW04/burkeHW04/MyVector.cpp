//Dalton Burke
//MyVector.cpp
//Contains implementation of MyVector class

#include <iostream>
using namespace std;

#include "MyVector.h"

namespace HW4 {
MyVector::MyVector()
{
//may be empty since MyVector.h initializes values
}

T MyVector::operator[] (int index)
{
    //Make a temporary vector
    /* Start at beginPtr and from nextPtr to nextPtr, index times*/
    //return the value at the correct object

  //return something crazy if the index is out of bounds
  if(empty() || index >= vsize)
    return -99999999;

  MyVector* current = beginPtr;

  for(int i = 0; i < index; i++)
  {
    if(current->nextPtr) //if nextPtr isn't null, we aren't at the end
      current = current->nextPtr;
  }

  return current->tValue; //return what we found at the ith position
}

void MyVector::pop_back()
{
    //First check if it is empty
  if (empty())
      return;
  // else
  //{
    //    //Start at beginPtr
    //    MyVector *vecPtr = beginPtr;
    //    
    //    //Allocate a new pointer object
    //    MyVector *vecPrevPtr = new MyVector;
    //    
    //    //Allocate a new pointer object
    //    MyVector *vecPrevPrevPtr = new MyVector;
    //    
    //    //If pointing to null, there is nothing to remove
    //    if (vecPtr == nullptr)
    //        return;
    //    else
    //        while (vecPtr != nullptr)
    //        {
    //            /*Think about a linked chain.  We are going to keep track of the last node that points to nullptr, the second last node, and the third last node*/
    //            
    //            
/*Th//e only way we know that we have hit the end of the link is to look for a node that points to nullptr, not another node. As we advance from the nextPtr to the one that is pointing to, we need to keep track of the two previous pointers, so we have a way of getting to the previous node.  Once we delete the last node, we now need to point the previous node to null pointer, which means we need to know where its previous pointer points to.  Keep in mind these are not two-way links, so as we are going forward in the chain we have to keep track of the previous links to go back.*/
    //            vecPrevPrevPtr->nextPtr =  vecPrevPtr;
    //            vecPrevPtr->nextPtr = vecPtr;
    //            vecPtr = vecPtr->nextPtr;
    //        }
    //        /*if you don't delete the pointer, the memory will not be released but you won't be able to get to it...this causes a memory leak*/
    //            delete vecPtr;
    //            //the last one now points to the previous
    //            nextPtr = vecPrevPtr;
    //            //we have to reduce the size since we deleted the last link
    //            vsize--;
    //}
    //return;

    //Previous implementation was useless,
    //Here's how you do it correctly
    MyVector* current = beginPtr;
    MyVector* previous = nullptr;
    while(current->nextPtr) //crawl the list until we can see the end at current->nextPtr
      { 
        previous = current;
        current = current->nextPtr;
      }

    if(previous) //just in case there was only one element
      previous->nextPtr = nullptr; //make sure the new end of the list points to nullptr

    delete current; //delete what current points at, the last element
    vsize--;
}

void MyVector::push_back(T value)
{
    //check if it is empty
    //if so create a new node (using dynamic memory), fill that new node with the value and increase the size
    //otherwise traverse the node until the end, keeping track of the previous and current pointer.
    //When you get to the end point to this newly created node, fill the new node with the value, increase the size and point the last pointer to this new node.
  if(empty())
  {
    beginPtr = new MyVector;
    beginPtr->tValue = value;
    vsize++;
    return;
  }

  else
  {
    MyVector* current = beginPtr;
    while(current->nextPtr) //crawl to the end of the list
      current = current->nextPtr;
    current->nextPtr = new MyVector;
    current->nextPtr->tValue = value;
    vsize++;
    return;
  } 
}

int MyVector::size()
{
  return vsize;
}

bool MyVector::empty()
{
    //Checks to see if empty (meaning beginPtr is pointing to what?)
  return !beginPtr;
}

/*Returns -1 if not found, otherwise returns the index of the value*/
int MyVector::search(T value)
{
    /*traverse the node looking for the value.  A for loop works well here, as return jumps out of the function. Note that you are keeping track of size in another function*/
  MyVector* current = beginPtr;
  int i = 0;
  //I'm not going to use a for loop here because using the subscript operator
  //for a linked list in a loop is an unforgivable offense
  while(current) //while we aren't at the end of the list
  {
    if(current->tValue == value) //if we have a match ship it
      return i;
    current = current->nextPtr;  //otherwise keep crawling
    i++;
  }
  return -1; //went through the entire vector and didn't find what we were looking for
}

}//namespace
