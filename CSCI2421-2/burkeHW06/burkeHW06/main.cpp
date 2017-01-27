//Dalton Burke
//main.cpp
//contains main()
//burkeHW06

#include <fstream>
#include <iostream>
#include <string>
#include "DictEntry.h"
#include "dictionary.h"



int main()
{
//friends to help us read files into lists later
  std::string wordbuffer;
  DictEntry dictbuffer;

  std::ifstream fin;
  fin.open("dictionary.txt");

//read file into list
  std::list<DictEntry> wordList;
//these while loop works fine unless you open the file with vim, and it
//automatically adds the extra \n at the end of the file, so don't do that
  while(!fin.eof()) 
  {
    fin >> wordbuffer;
    dictbuffer.setWord(wordbuffer);
    wordList.push_front(dictbuffer);
  }
  fin.close();

  wordList.sort();

//use a list to hold the words that we'll search for later
  std::list<DictEntry> findWords;
  fin.open("findwords.txt");
  while(!fin.eof())
  {
    fin >> wordbuffer;
    dictbuffer.setWord(wordbuffer);
    findWords.push_back(dictbuffer);
  }
  fin.close();

  dictionary dict1;
//show searches and length of the searches
  for(list<DictEntry>::iterator wordPtr1 = findWords.begin(); wordPtr1 != findWords.end(); wordPtr1++)
  {
    std::cout << "Forward search for \"" << wordPtr1->getWord() << "\" takes "
              << dict1.searchForward(wordList, wordPtr1->getWord()) << " checks." << std::endl;
    std::cout << "Backward search for \"" << wordPtr1->getWord() << "\" takes "
              << dict1.searchBackward(wordList, wordPtr1->getWord()) << " checks." << std::endl << std::endl;
  }

//use cout to show what's going into the file
  std::cout << "The following is being printed to \"revsorted.txt\" :" << std::endl;
  dict1.revPrintList(std::cout, wordList);
  
  std::ofstream fout;
  fout.open("revsorted.txt");

//ship it
  dict1.revPrintList(fout, wordList);

  fout.close();
}
