//Dalton Burke
//102279938
//main.cpp for HW5

#include<iostream>
#include<cassert>
#include<cstdlib>
#include"node1.h"

using namespace main_savitch_5;


int main()
{
    size_t m, n;
    std::cout << "How many contestants are there?" << std::endl;
    std::cin >> n;

    assert(n > 0);

    if(n == 1)
    {
        std::cout << "Congratulations to the winner, our only contestant, contestant #1!" << std::endl;
        return 0;
    }
    std::cout << "What is the magic number that we will use to determine the winner?" << std::endl;
    std::cin >> m;

    assert(m > 0 && m <= n);

    node* head ;
    head = new node(1,NULL,NULL);

    //make the list of contestants
    node* tracker; //tracker keeps track of the node we will be working with throughout various operations
    tracker = head;

    for(size_t i = 2; i <= n; i++)
    {
        list_insert(tracker, i);
        tracker = tracker->fwd_link();
    }
    tracker->set_fwd_link(head);//make it circular
    head->set_bk_link(tracker);

    tracker = head;
    int helper; //this helps to do mod operations later, and keep track of the size
    for(size_t round = 1; round < n; round++)
    {
        std::cout << "Round #" << round << std::endl;
        helper = m % list_length(head); //reduces the amount of shifting later when m is bigger than the size of the loop

        if(round % 2 == 1) //going forward
        {
            for(int i = 0; i < helper; i++)
                tracker = tracker->fwd_link();//shift it to  the space after the contestant
            std::cout << "Eliminated: #" << tracker->bk_link()->data() << std::endl;
            if(tracker->bk_link()== head )//we may need to delete whatever the head points to
                head = head->fwd_link();//in that case, shift the head over one

            list_remove(tracker->bk_link()->bk_link());//remove deletes whatever is ahead of the pointer you gave it
        }

        else if(round %2 == 0) //going backwards
        {
            for(int i = 0; i < helper; i++)//shift back until we are where we want to be
                tracker = tracker->bk_link();
            std::cout << "Eliminated: #" << tracker->fwd_link()->data() << std::endl;
            if(tracker->fwd_link() == head) //we are going to delete the head
                head = head->fwd_link();
            list_remove(tracker);
        }
    }
    std::cout << "Congratulations to our winner, contestant #" << head->data() << ", you have beaten the odds!" << std:: endl;
    return 0;
}

