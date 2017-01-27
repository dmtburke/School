//Dalton Burke
//Recursion.cpp
//Contains implementation of Recursion class and member functions
//CSCI 2421 HW 3

#include <iostream>
#include <fstream>
#include <string>
#include "Recursion.h"


Recursion::Recursion()
{
  //set a default size, will be overwritten later
  __size = 1;
  __searchArray = new std::string[__size];

  //setting all of the change variables to 0
  __q = 0;
  __d = 0;
  __n = 0;
  __p = 0;
  __iters = 0;
}

Recursion::~Recursion()
{
  delete[] __searchArray;
}

void Recursion::menu()
{
  std::cout << "Welcome to my recursion program!" << std::endl;
  int choice;
  while(true)
  {
    std::cout << "Which function would you like to use?" << std::endl;
    std::cout << "1:\tBinary Search" << std::endl;
    std::cout << "2:\tMake Change" << std::endl;
    std::cout << "3:\tExit" << std::endl;

    std::cin >> choice;

    if(choice == 1)
      runSearch();
    else if(choice == 2)
      runChange();
    else
      break;
  }

  std::cout << "Goodbye!" << std::endl;
}

//Functions for binary search
void Recursion::runSearch()
{
  std::string filename;
  std::cout << "Welcome to the binary search! What is the name of your file?" << std::endl;
  std::cin >> filename;

  std::ifstream fin;
  fin.open(filename);

  while(!fin.good())
  {
    std::cout << "File not found! Please enter valid filename" << std::endl;
    std::cin >> filename;
    fin.open(filename);
  }

  setLength(fin);

  //load it in
  for(int i = 0; i < __size; i++)
    fin >> __searchArray[i];

  fin.close();

  //sort it
  sortArray();

  std::string searchTerm;
  int choice;

  //search it
  while(true)
  {
    std::cout << "What would you like to search for?" << std::endl;
    std::cin >> searchTerm;

    if(searchArray(searchTerm, 0, __size - 1))
      std::cout << "Search term " << searchTerm << " was found in the file!" << std::endl;
    else
      std::cout << "Search term " << searchTerm << " was not found in the file." << std::endl;

    std::cout << "Please make a choice:" << std::endl;
    std::cout << "1:\tDo another search" << std::endl;
    std::cout << "2:\tExit search" << std::endl;
    std::cin >> choice;

    if(choice != 1)
      break;
  }
}

void Recursion::setLength(std::ifstream &fin)
{
  int size = 0;
  std::string buffer;

  while(getline(fin,buffer))
  {
    size++;
  }

  //define the new search array size
  //doing it this way allows for the changing of the dictionary file
  __size = size;
  delete[] __searchArray;
  __searchArray = new std::string[__size];

  //send fin back to the start of the file after having tripped the eof flag
  fin.clear();
  fin.seekg (0, std::ios::beg);
}

//bubble sort
void Recursion::sortArray()
{
  std::string temp;
  bool swapped = true;

  for(int i = 1; i < __size && swapped; i++)
  {
    swapped = false;
    for(int j = 0; j < __size - i; j++)
      if(__searchArray[j] > __searchArray[j + 1])
      {
        temp = __searchArray[j];
        __searchArray[j] = __searchArray[j + 1];
        __searchArray[j+1] = temp;
        swapped = true;
      }
  }
}

//binary search
bool Recursion::searchArray(std::string searchTerm, int lbound, int ubound)
{
  int center = int((lbound + ubound)/2);

  if(__searchArray[center] == searchTerm || __searchArray[ubound] == searchTerm || __searchArray[lbound] == searchTerm)
    return true;

  if( lbound == ubound || lbound == ubound - 1)
    return false;

  if(__searchArray[center] < searchTerm)
    return searchArray(searchTerm, center, ubound);

  if(__searchArray[center] > searchTerm)
    return searchArray(searchTerm, lbound, center);

  return false;
}

//Functions for change making
void Recursion::runChange()
{
  int cents;
  std::cout << "Welcome to the change maker! How many cents do you have?" << std::endl;
  std::cin >> cents;

  std::cout << "   \t{Q, D, N, P}" << std::endl; //formatting, first hold quarters, second holds dimes, etc.
  int numways = ways(cents,4);
  std::cout << "   \t{Q, D, N, P}" << std::endl; //formatting, first hold quarters, second holds dimes, etc.

  std::cout << "There are " << numways << " ways to make " << cents << " cents." << std::endl;
  std::cout << "The most efficient, ";
  dispCurrent();
}

int Recursion::coins(int cointype)
{
  switch(cointype)
  {
    case 1: return 1;
    case 2: return 5;
    case 3: return 10;
    case 4: return 25;
    default: return 0;
  }
}

//don't strictly need this, but it makes life a little easier
void Recursion::dispCurrent()
{
  std::cout << '{' << __q << ", " << __d << ", " << __n << ", " << __p
            << "},\trequires " << __q + __d + __n + __p << " coin(s)" << std::endl;
}

int Recursion::ways(int amount, int denom)
{
  if(amount < 0)
    return 0;
  int cycles = int(amount/coins(denom)), ans = 0;
  for(int i = 0; i <= cycles; i++)
  {
    switch(denom)
    {
      case 1: __p = amount;
          break;
      case 2: __n = i;
          break;
      case 3: __d = i;
          break;
      case 4: __q = i;
          break;
    }
    if(denom == 1) //every time we get to the number of pennies, output it, and we end up starting over
    {
      __iters++;
      std::cout << __iters << ":\t";
      dispCurrent();
      return 1;
    }
    else
      ans += ways(amount - i*coins(denom), denom -1);
  }
  return ans;
}
