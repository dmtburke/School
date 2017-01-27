//Dalton Burke
//SetFunctions.h
//Contains declaration of "Set" class, which is made around an "ArrayBag"
//CSCI 2421 HW2

#include<iostream>
#include<fstream>
#include"ArrayBag.h"

class Set
{
 private:
  ArrayBag __set;

 public:
  Set();
  //add new member to the set
  bool add(const int newValue);
  //remove member from the set
  bool remove(const int rmValue);

  //read sets in from a file
  bool fileIn(std::ifstream& fin);

  //Union operator for sets
  friend Set operator+(const Set lhs, const Set rhs);
  //Asymmetrical difference of sets
  friend Set operator-(const Set lhs, const Set rhs);

  //Display the set on the console
  friend std::ostream& operator<<(std::ostream &os, const Set output);
};

Set operator+(const Set lhs, const Set rhs);
Set operator-(const Set lhs, const Set rhs);

std::ostream& operator<<(std::ostream &os, const Set output);
