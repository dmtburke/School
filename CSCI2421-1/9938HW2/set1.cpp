// FILE: set1.cpp
// From Chapter 3 of Data Structures and Other Objects (Second Edition)
// ________________________________________________________________________
//
// This file has been modified to work with Microsoft Visual C++ 6.0,
// as described in www.cs.colorado.edu/~main/vc6.html
// ________________________________________________________________________
//
// CLASS IMPLEMENTED: set (see set1.h for documentation)
// INVARIANT for the set class:
//   1. The number of items in the set is in the member variable used;
//   2. For an empty set, we do not care what is stored in any of data; for a
//      non-empty set the items in the set are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.

//#include <algorithm> // Provides copy function //I don't need copy the way that I redefined it for sets
#include <cassert>   // Provides assert function
#include "set1.h"
#include <iostream>

using namespace std;

namespace main_savitch_3
{
    // (Omitted for VC++ 6.0) const set::size_type set::CAPACITY;

    void set::erase(const value_type& target)
    {
	int found;
	found = find(target);
	if ( found != -1)//if it was found shift it all over
	{
		for(size_type i = found; i < used; i++) //overwriting the entry that was erased
			data[i] = data[i+1];
		used--;//data[] is one smaller than it was
	}
	//this function runs through "used" number of operations everytime
    }


	//don't need erase_one for a set, it's the same as erase

//    bool set::erase_one(const value_type& target)
//    {
//	size_type index; // The location of target in the data array
//
//	// First, set index to the location of target in the data array,
//	// which could be as small as 0 or as large as used-1. If target is not
//	// in the array, then index will be set equal to used.
//	index = 0;
//	while ((index < used) && (data[index] != target))
//	    ++index;
//
//	if (index == used)
//	    return false; // target isn't in the set, so no work to do.
//
//	// When execution reaches here, target is in the set at data[index].
//	// So, reduce used by 1 and copy the last item onto data[index].
//	--used;
//	data[index] = data[used];
//	return true;
//    }


    void set::insert(const value_type& entry)
    // Library facilities used: cassert
    {
        assert(size( ) < CAPACITY);

	//make sure not to add an entry that's already in the set
	if (!contains(entry))
	{
        	data[used] = entry;
		++used;
	}
	//runs as long as "find" runs
    }

	//I defined it a different way with sets, don't need +=, or copy()

//    void set::operator +=(const set& addend)
//    // Library facilities used: algorithm, cassert
//    {
//	assert(size( ) + addend.size( ) <= CAPACITY);
//
//	copy(addend.data, addend.data + addend.used, data + used);
//	used += addend.used;
//    }

	//returns where the value was found. If it returns "-1" then it wasn't found
	int set::find(const value_type& target) const
	{
		size_type index = 0;
		while ((index < used) && (data[index] != target))
		    ++index;
		if(index == used)
			return -1;
		else
			return index;

	}


    bool set::contains(const value_type& target) const
    {
	if (find(target) == -1)
		return false; // target isn't in the set
	else
		return true; //target is in the set
    }


    set operator +(const set& b1, const set& b2)
    // Library facilities used: cassert
    {
        set answer;


	for( size_t i = 0; i < b1.used; i++)
		answer.insert(b1.data[i]);

	for(size_t i = 0; i < b2.used; i++)
		answer.insert(b2.data[i]);

	assert(answer.size() <= set::CAPACITY); //checks after the new set is made, since some might cancel

        return answer;
    }

    set operator -(const set& b1, const set& b2)
    {
	    set answer;

	    for( size_t i = 0; i < b1.used; i++) //add all elements from b1
	    	answer.insert(b1.data[i]);

	    for( size_t i = 0; i < b2.used; i ++) //erase all elements that are in b2
	    	answer.erase(b2.data[i]);

	    return answer;
    }

	void set::print() const
	{
		cout << '{';
		for(size_type i = 0; i < used -1; i++)
			cout << data[i] << ", ";
		cout << data[used -1] << '}';
	}
}
