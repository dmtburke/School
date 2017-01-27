// Dalton Burke 102279938
// filecheck.cpp
// contains implementation of file check functions

#include "dictionary.h"
#include "filecheck.h"
#include <fstream>
#include <iostream>
#include <string>



void checkFile(std::string filename, dictionary dict)
{
  std::cout << "Checking " << filename << " for spelling errors..." << std::endl;
  std::ifstream fin(filename);


  SNode* misspelledList = nullptr;
  int total = 0, misspelled = 0;
  std::string w;

  while(fin >> w)
  {
    //If it's not in the dictionary then it must be misspelled
    if(!dict.contains(filter(w)))
    {
      //Keep track of misspelled words in a linked list so we can show the user later
      if(!misspelledList->contains(filter(w)))
         misspelledList = new SNode(filter(w), misspelledList);
      misspelled++;
    }

    //read a word in, count that
    total++;
  }

  std::cout << "Done!" << std::endl;
  std::cout << "Number of words in dictionary:\t" << dict.getWords() << std::endl;
  std::cout << "Total number of words checked:\t" << total << std::endl;
  std::cout << "Number of misspelled words:\t" << misspelled << std::endl;


  //If there were misspelled words, ask if the user wants to see them
  if(misspelled)
  {
    int wantToSee = 0;
    std::cout << "Would you like to see the words you may have misspelled?" << std::endl;
    std::cout << "1.\tYes\n2.\tNo\n";
    std::cin >> wantToSee;
    std::cout << std::endl;
    //Print out the linked list we kept of misspelt words
    if(wantToSee == 1)
    {
      SNode* cursor = misspelledList;
      while(cursor)
      {
        std::cout << cursor->word << std::endl;
        cursor = cursor->next;
      }
    }
  }
}

std::string filter(std::string w)
{
  std::string x = "";

  //convert to all lowercase
  for(unsigned int i = 0; i < w.length(); i++)
    x += tolower(w[i]);

  //If word starts or ends in punctuation, remove it
  while(!isalnum(x.front()) && !x.empty()) // If it was only made of punctuation then stop filtering
    x.erase(0,1);

  while(!isalnum(x.back()) && !x.empty())
    x.pop_back();

  return x;
}
