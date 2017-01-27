//Dalton Burke
//MyVector.h
//Contains declaration of MyVector class

#ifndef MYVECTOR_
#define MYVECTOR_
/*Defines a MyVector type which mirrors the STL vector class.  It uses templates and dynamic memory allocation*/

namespace HW4
{
typedef int T;
class MyVector
{
private:
    int vsize = 0;
    MyVector* beginPtr = nullptr;
    MyVector* nextPtr = nullptr;
    T tValue;

public:
    MyVector();
    T operator[] (int index);
    void pop_back();
    void push_back(T value);
    int size();
    bool empty();
    int search(T Value);
};

}//namespace
#endif
