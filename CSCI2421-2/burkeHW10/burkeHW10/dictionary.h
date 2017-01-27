//Dalton Burke 102279938
//dictionary.h
//contains declaration of dictionary class

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <fstream>
#include <string>

//For the linked list out of each bucket
struct SNode
{
  std::string word;
  SNode* next;

  //This constructor will make life easy when filling the buckets
  SNode(std::string word, SNode* next);
  ~SNode();

  bool contains(std::string w);
};

class dictionary
{
 private:
  int words;
  //More generalized number of buckets at users command
  int buckets;
  //Array because we know exactly how many buckets we have
  SNode** table;

 public:
  //to make a dictionary, you'll need the buckets and the file
  //the class might be made better by finding a reasonable number of buckets in the constructor
  //so that we don't need to pass that in
  dictionary(std::string filename, int __buckets);
  ~dictionary();

  //Retrieve number of words
  int getWords();

  //Used to see if a word is in the dictionary
  bool contains(std::string w);
};

#endif //DICTIONARY_H
