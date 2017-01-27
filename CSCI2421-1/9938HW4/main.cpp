//Dalton Burke
//do the thing

#include<iostream>
#include<fstream>
#include"node1.h"
#include<string>

using namespace main_savitch_5;

int main()
{
    std::string filename;
    std::ifstream fin;
    std::cout << "Hello, I will be using the file \"data.txt\" to retrieve the list of words"  << std::endl;
    fin.open("data.txt");

    node item;
    item.set_data("::Begin List::");

    node* head;

    head = &item;

    std::string buffer;
    size_t i =1 ;
    while(true)
    {
         fin >> buffer;         //takes in a "word"

         while(buffer.find_first_of(",.\'-?") != std::string::npos)
         {//removes "',.'-?" chars from the word
             buffer.erase(buffer.find_first_of(".,\'-?"), 1);
         }

         if(fin.eof())
             break;

         //add word to the  end of the current list
         list_insert(list_locate(head, i), buffer);
         i++;

    }
    fin.close();


    node* tail;
    tail = list_locate(head,i);

    std::cout << "Data is in, time to spit it out" << std::endl;

    list_print(head);


    std::cout << "Which word do you want the sublist to start at?" << std::endl;
    std::cin >> buffer;

    node* start;
    start = list_search(head, buffer);
    if(start == NULL)
    {
    std::cout << "ERROR: The word you entered was not in the list" << std::endl;
    return 1;
    }

    std::cout << "Which word do you want the sublist to end at?" << std::endl;
    std::cin >> buffer;

    node* end;
    end = list_search(start, buffer);
    if(end == NULL)
    {
        std::cout << "ERROR: The word you entered was not in the list" << std::endl;
        return 2;
    }

    node* subhead;
    node* subtail;
    list_piece(start, end, subhead, subtail);

    std::cout << std::endl <<  "Here is what your sublist looks like:" << std::endl;
    list_print(subhead);

    std::cout << std::endl << "I will now sort it..." << std::endl << std::endl;

    list_sort(subhead);

    std::cout << "Sorting complete, here is the sorted sublist:" << std::endl;

    list_print(subhead);

    return 0;

}
