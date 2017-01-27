// FILE: set1.h
// From Chapter 3 of Data Structures and Other Objects (Second Edition)
// ________________________________________________________________________
//
// This file has been modified to work with Microsoft Visual C++ 6.0,
// as described in www.cs.colorado.edu/~main/vc6.html
// ________________________________________________________________________
//
// CLASS PROVIDED: set (part of the namespace main_savitch_3)
//
// TYPEDEF and MEMBER CONSTANTS for the set class:
//   typedef ____ value_type
//     set::value_type is the data type of the items in the set. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and operators to
//     test for equality (x == y) and non-equality (x != y).
//
//   typedef ____ size_type
//     set::size_type is the data type of any variable that keeps track of how many items
//     are in a set.
//
//   static const size_type CAPACITY = _____
//     set::CAPACITY is the maximum number of items that a set can hold.
//
// CONSTRUCTOR for the set class:
//   set( )
//     Postcondition: The set has been initialized as an empty set.
//
// MODIFICATION MEMBER FUNCTIONS for the set class:
//   size_type erase(const value_type& target);
//     Postcondition: Target is removed from the set.
//
//   void insert(const value_type& entry)
//     Precondition:  size( ) < CAPACITY.
//     Postcondition: New entry added to set if it wasn't there already
//
// CONSTANT MEMBER FUNCTIONS for the set class:
//   size_type size( ) const
//     Postcondition: The return value is the total number of items in the set.
//
//   bool contain(const value_type& target) const
//     Postcondition: The return value is true if the target is in the set
//
// FRIEND FUNCTIONS for the set class:
//   set operator +(const set& b1, const set& b2)
//     Precondition:  answer.size() <= set::CAPACITY.
//     Postcondition: The set returned is the union of b1 and b2.
//
//   set operator -(const set& b1, const set& b2)
//     Postcondition: returns b1 - b2 (all elements in b1, but not b2)
//
// VALUE SEMANTICS for the set class:
//    Assignments and the copy constructor may be used with set objects.

#ifndef MAIN_SAVITCH_set1_H
#define MAIN_SAVITCH_set1_H
#include <cstdlib>  // Provides size_t

namespace main_savitch_3
{
    class set
    {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
	// * For VC++ 6.0 we are using size_t instead of std::size_t. And we
	// * have defined CAPACITY using an enum instead of a static member
	// * constant. See www.cs.colorado.edu/~main/vc6.html for details.
        typedef int value_type;
        typedef size_t size_type; //this seems wasteful and misleading
	enum { CAPACITY = 30 };

        // CONSTRUCTOR
        set( ) { used = 0; }

        // MODIFICATION MEMBER FUNCTIONS
        void erase(const value_type& target);
//        bool erase_one(const value_type& target); //didn't need it
        void insert(const value_type& entry);
//        void operator +=(const set& addend);  //didn't need it

        // CONSTANT MEMBER FUNCTIONS
        int size( ) const { return used; }
	int find( const value_type& target) const;
        bool contains(const value_type& target) const;
	void print() const;

	//FRIEND FUNCTIONS
	friend set operator +(const set& b1, const set& b2);
	friend set operator -(const set& b1, const set& b2);

    private:
        value_type data[CAPACITY];  // The array to store items
        size_type used;             // How much of array is used
    };
}

#endif
