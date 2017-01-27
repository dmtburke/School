//Dalton Burke
//Recursion.h
//Contains declaration of Recursion class, which will make change and search a dictionary file
//CSCI 2421 HW 3

#include <iostream>
#include <fstream>
#include <string>

class Recursion
{
 private:
  //variables for binary search
  int __size;
  std::string* __searchArray;

  //variables for the change making
  int __q, __d, __n, __p, __iters;

 public:
  Recursion();
  ~Recursion();

  //choosing if you would like to use search or change making functionality
  void menu();

  //functions for binary search
  void runSearch(); //handles menu and driving of the search function
  void setLength(std::ifstream &fin); //determines length of the dictionary and sets the length of the array
  void sortArray(); //bubble sort
  bool searchArray(std::string searchTerm, int lbound, int ubound); //binary search

  //functions for change making
  void runChange(); //handles menu and driving of change functions
  int coins(int cointype); //returns the worth of a coin type
  void dispCurrent(); //displays the current coin configuration
  int ways(int amount, int denom); //calculates and displays the change configurations
};
