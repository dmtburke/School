//Dalton Burke
//SetFunctions.cpp
//Contains implementation of member and friend functions of the "Set" class
//CSCI 2421 HW 2

#include <fstream> //file input
#include <sstream> //stringstream
#include <string>  //read from file to string
#include "ArrayBag.h"
#include "SetFunctions.h"

Set::Set()
{
  __set = ArrayBag();
}

bool Set::add(int newValue)
{
  if(!__set.contains(newValue))
    return __set.add(newValue);

  //this is to keep consistent with the return value of the ArrayBag class
  if( __set.getCurrentSize() < __set.getMaxSize() )
    return true;

  else
    return false;
}

bool Set::remove(int rmValue)
{
  return __set.remove(rmValue);
}

bool Set::fileIn(std::ifstream& fin)
{
  std::stringstream ss;
  int buffer;
  std::string reader;

  getline(fin, reader);
  ss << reader;

  while(!ss.eof())
  {
    ss >> buffer;
    //if we run into an error that's not the end of the line, quit
    if(!ss.eof() && ss.fail())
    {
      std::cout << "Input contains non-integer data!" << std::endl;
      ss.clear();
      return false;
    }
    //otherwise, add the newly extracted int to the Set
    add(buffer);

  }
  return true;
}

Set operator+(const Set lhs, const Set rhs)
{
  Set sum;
  //add all elements from both sets. the "add" for sets assures that
  //only one copy of any given int will be added
  for(int i = 0; i < lhs.__set.getCurrentSize(); i++)
    sum.add(lhs.__set[i]);
  for(int i = 0; i < rhs.__set.getCurrentSize(); i++)
    sum.add(rhs.__set[i]);

  return sum;
}

Set operator-(const Set lhs, const Set rhs)
{
  Set diff;
  //add all the elements of the first set
  for(int i = 0; i < lhs.__set.getCurrentSize(); i++)
    diff.add(lhs.__set[i]);
  //then remove all of the elements from the second
  for(int i = 0; i < rhs.__set.getCurrentSize(); i++)
    diff.remove(rhs.__set[i]);

  return diff;
}

std::ostream& operator<<(std::ostream &os, const Set output)
{
  for(int i = 0; i < output.__set.getCurrentSize(); i++)
    os << output.__set[i] << '\t';

  return os;
}
