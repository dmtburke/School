// FILE: node1.cxx
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
// INVARIANT for the node class:
//   The data of a node is stored in data_field, and the link in link_field.

#include "node1.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>
#include<string>

using namespace std;

namespace main_savitch_5
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
	node *insert_ptr;

	insert_ptr = new node(entry, previous_ptr->link( ));
	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
	node *cursor;

	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    if (target == cursor->data( ))
		return cursor;
	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
	const node *cursor;

	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    if (target == cursor->data( ))
		return cursor;
	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
	node *cursor;
	size_t i;

	assert (0 < position);
	cursor = head_ptr;
	for (i = 1; (i < position) && (cursor != NULL); i++)
	    cursor = cursor->link( );
	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
	const node *cursor;
	size_t i;

	assert (0 < position);
	cursor = head_ptr;
	for (i = 1; (i < position) && (cursor != NULL); i++)
	    cursor = cursor->link( );
	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
	node *remove_ptr;

	remove_ptr = head_ptr;
	head_ptr = head_ptr->link( );
	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
	node *remove_ptr;

	remove_ptr = previous_ptr->link( );
	previous_ptr->set_link( remove_ptr->link( ) );
	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
	while (head_ptr != NULL)
	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
	head_ptr = NULL;
	tail_ptr = NULL;

	// Handle the case of the empty list.
	if (source_ptr == NULL)
	    return;

	// Make the head node for the newly created list, and put data in it.
	list_head_insert(head_ptr, source_ptr->data( ));
	tail_ptr = head_ptr;

	// Copy the rest of the nodes one at a time, adding at the tail of new list.
	source_ptr = source_ptr->link( );
	while (source_ptr != NULL)
	{
	    list_insert(tail_ptr, source_ptr->data( ));
	    tail_ptr = tail_ptr->link( );
	    source_ptr = source_ptr->link( );
	}
    }

    void list_piece(
             const node *start_ptr, const node* end_ptr,
             node*& head_ptr, node*& tail_ptr
            )
    {
        //copy everything after the new start
        list_copy(start_ptr, head_ptr, tail_ptr);
        if(tail_ptr == list_search(head_ptr, end_ptr->data()))
                ;//do nothing and leave the program
        //get rid of everything after the new end
        //first, find out where the end of the list is with the tail_ptr
        else
        {
            tail_ptr = list_search(head_ptr, (end_ptr->link())->data());
            list_clear(tail_ptr);
             //the clear set the tail_ptr = NULL, so we need to set it back to the last element.
             tail_ptr = list_search(head_ptr, end_ptr->data());
             tail_ptr->set_link(NULL);
        }
    }


    void list_swap(node*& ptr1, node*& ptr2)
    {

    }

    void list_sort(node*& head_ptr)
    {
        size_t j;//inner index for the loop coming up
        node* ptr1;
        node* ptr2;
        node* ptr3;
        node* swapper;
        for(size_t i = 2; i <= list_length(head_ptr); i++)
        {
            j = i;
             while((j != 1) && ((list_locate(head_ptr, j-1)->data()).compare(list_locate(head_ptr, j)->data()) > 0))
             {//so far the insert sort algorithm is identical to the example website
                //I need to have these because swapping the pointers around changes what j refers to in the locate funciton
                ptr2 = list_locate(head_ptr, j-1);
                ptr3 = list_locate(head_ptr, j);
                if(j-2 != 0)
                    ptr1 = list_locate(head_ptr, j-2);

                swapper = ptr3->link(); //save what the jth object was pointing at
                ptr3->set_link(ptr2); //point the jth object at the j-1th object
                ptr2->set_link(swapper); //point the j-1th object at the j+1th
                if(j-2 != 0)
                    ptr1->set_link(ptr3); //point the j-2th object at the jth object
                else
                     head_ptr = ptr3; //if we are at the bottom of the list trying to swap with header
                j--;
             }
        }
    }

    void list_print(node* head_ptr)
    {
        node* printer = head_ptr;
        while(printer!=NULL)
        {
            std::cout << printer->data() << std::endl;
            printer = printer->link();
        }
    }
}
