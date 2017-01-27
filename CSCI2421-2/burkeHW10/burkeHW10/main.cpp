//Dalton Burke 102279938
//main.cpp
//contains drivers for burkeHW10

#include <iostream>
#include <string>
#include "dictionary.h"
#include "filecheck.h"

int main()
{
  std::string filetoCheck;
  std::string dictFile = "dict.dat";

  std::cout << "Please enter a filename to check for spelling errors: ";
  std::cin >> filetoCheck;

  std::cout << "Using " << dictFile << " for dictionary..." << std::endl;
  //Using the spec given by the homework, you could use anything though
  checkFile(filetoCheck, dictionary(dictFile,1373));

  std::cout << std::endl << "Goodbye!" << std::endl;
  return 0;
}
