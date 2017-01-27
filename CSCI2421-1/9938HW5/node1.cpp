// FILE: node1.cxx
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
// INVARIANT for the node class:
//   The data of a node is stored in data_field, and the link in link_field.

#include "node1.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

#include <iostream>

using namespace std;

namespace main_savitch_5
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

//    if(head_ptr->fwd_link() == head_ptr)//if headpointer is the only one in the list then the size is 1.
//        return 1;
	answer = 1;
	for (cursor = head_ptr->fwd_link(); cursor != head_ptr; cursor = cursor->fwd_link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
	head_ptr = new node(entry, head_ptr, list_locate(head_ptr, list_length(head_ptr)));
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
	node *insert_ptr;

	insert_ptr = new node(entry, previous_ptr->fwd_link( ), previous_ptr);
	previous_ptr->set_fwd_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
	node *cursor;
    if(head_ptr->data() == target)
        return head_ptr;
	for (cursor = head_ptr; cursor != head_ptr; cursor = cursor->fwd_link( ))
	    if (target == cursor->data( ))
		return cursor;
	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
	const node *cursor;

    if(head_ptr->data() == target)
        return head_ptr;
	for (cursor = head_ptr->fwd_link(); cursor != head_ptr; cursor = cursor->fwd_link( ))//headptr is the end of a circular list.
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
    if(position == 1)
        return cursor;
    cursor = cursor->fwd_link();
	for (i = 1; (i < position) && (cursor != NULL); i++)
	    cursor = cursor->fwd_link( );
	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
	const node *cursor;
	size_t i;

	assert (0 < position);
	cursor = head_ptr;
    if(position == 1)
        return cursor;
    cursor = cursor->fwd_link();

	for (i = 2; (i < position) && (cursor != head_ptr); i++)//stop counting if you get back to the head pointer
	    cursor = cursor->fwd_link( );
	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
        node* remove_ptr;
        remove_ptr = head_ptr;
	    head_ptr = head_ptr->fwd_link( );

        list_remove(remove_ptr->bk_link());

    }

    void list_remove(node* previous_ptr)
    {
	node *remove_ptr;
	remove_ptr = previous_ptr->fwd_link( );
	previous_ptr->set_fwd_link( remove_ptr->fwd_link( ) );
    (previous_ptr->fwd_link())->set_bk_link(previous_ptr);
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
    	source_ptr = source_ptr->fwd_link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->fwd_link( );
    	    source_ptr = source_ptr->fwd_link( );
    	}
    }

}
