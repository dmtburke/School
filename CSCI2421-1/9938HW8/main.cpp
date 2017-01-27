//Dalton Burke
//102279938
//Data Structures and Program Design HW 8

#include<string>
#include<fstream>
#include<iostream>
#include<functional>

using namespace std;

//String nodes for a linked list
struct SNode
{
    string word;
    SNode* next;
    SNode(string word, SNode* next);
};

//function for bringing words in from an ifstream
//will be used for loading dictionary and for checking the input document
string getWord(string w);

int main()
{

    cout << "Loading Dictionary..." << endl;
    ifstream fin;
    fin.open("dict.dat");


    //Array of String Node pointers for the hash table
    SNode* table[1373];
    for(int i =0; i < 1373; i++)
        table[i] = nullptr;

    //make a hash function for the hash table
    std::hash<std::string> hashFn;

    //placeholders to bring in the data
    string w;               //this one is to hold the input from the file
    unsigned int pos;       //this one is so that I only need compute the hash once

    //prime the read
    fin >> w;

    while(!fin.eof())
    {
        pos = hashFn(w) % 1373; //only want to compute this once
        table[pos] = new SNode(w, table[pos]);
        fin >> w;
    }

    fin.close();
    cout << "Done" << endl;

    //  testing the input of the dictionary
    //SNode* ctr;
    //for(int i = 0; i < 1373; i++)
    //{
    //    ctr = table[i];
    //    cout << i << endl;
    //    while(ctr != nullptr)
    //    {
    //        cout << ctr->word << ", ";
    //        ctr = ctr->next;
    //    }
    //    cout << endl;
    //}



    string fname;
    cout << "What is the name of your document?" << endl;
    getline(cin, fname);
    fin.open(fname);

    if(!fin.is_open())
    {
        cout << "There was a problem opening your file \"" << fname << "\" please try again" << endl;
        return 1;
    }

    cout << "File \"" << fname << "\" successfully opened." << endl;

    cout << "Spell-checking..." << endl;

    //I'm going to store the misspelled words in a linked list, since I already have the SNode struct

    w = ""; //using same string variable as before
    bool inDict; //used when a word is in the dictionary
    SNode* cursor, *misspelled = nullptr;
    fin >> w; //prime the read
    while(!fin.eof())
    {
        w = getWord(w);
        pos = hashFn(w) % 1373;
        cursor = table[pos];
        inDict = false; //assume the word isn't in the dictionary until you find it
        while(cursor != nullptr)
        {
            if(w == cursor->word)
            {
                inDict = true;
                break;
            }
            cursor = cursor->next;
        }
        if(!inDict) //if the word is not in the dictionary, add it to the misspelled list
            misspelled = new SNode(w, misspelled);
        fin>>w;
    }

    fin.close();

    if(misspelled == nullptr)
        cout << "No misspelled words were found" << endl;
    else
    {
        cout << "These words weren't found in the dictionary, are you sure they are spelled correctly? " << endl;
        while(misspelled != nullptr)
        {
             cout << misspelled->word << endl;
             misspelled = misspelled->next;
        }
    }
    cout << "Thank you for using the spell-checker" << endl;

    return 0;
}


string getWord(string w)
{
    string x = "";
    for(int i = 0; i < w.length(); i++)
        if(isalpha(w[i]))
            x += tolower(w[i]);
    return x;



}

SNode::SNode(string word, SNode* next) : //constructor because it's convenient
    word(word),
    next(next)
{}
