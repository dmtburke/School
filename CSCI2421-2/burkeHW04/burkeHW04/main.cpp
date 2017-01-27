//Dalton Burke

/*Dr. Augustine
Last Updated: 09/09/2016
This program is a driver demonstrating the member functions of MyVector.h*/

#include <iostream>
#include "MyVector.h"
using namespace std;

int main()
{
    HW4::MyVector vec1;
    cout << "Searching an empty MyVector returns index " << vec1.search(1) << endl<<endl;
    
    for (int i = 1; i<=10; i++)
        vec1.push_back(i);
    
    cout << "After 10 pushbacks vector contains: ";
    
    for (int i = 0; i<vec1.size(); i++)
        cout << vec1[i] << " ";
    cout << endl<<endl;
    
    cout << "Searching for 5 returns index "<< vec1.search(5) << endl;
    
    cout << "Searching for 10 returns index "<< vec1.search(10) << endl;

    
    cout << "Searching for 11 returns index " << vec1.search(11) << endl << endl;
    
    vec1.pop_back();
    
    
    cout << "After pop_back searching for 10 returns index " << vec1.search(10) << endl;

    for (int i = 0; i<vec1.size(); i++)
        cout << vec1[i] << " ";
    cout << endl << endl;
    
    cout << "Current Size of the vector is: " << vec1.size() << std::endl;
    int tempSize = vec1.size();

    for (int i = 0; i < tempSize; i++)
    {
        vec1.pop_back();
        cout << "After pop_back: ";
        for (int j = 0; j < vec1.size(); j++)
            cout << vec1[j] << " ";
        cout << endl;
    }
    

    return 0;
}
