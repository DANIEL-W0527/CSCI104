# Homework 1 Programming Part

Name: Jinghao (Daniel) Wang
USC ID: 4237145509
USC Net ID: jinghao

## Contents

- split.h
- split.cpp
- ulliststr.h
- ulliststr.cpp
- ulliststr_test.cpp

## Assignment Description

### Part 1

- Descrption: use recursion to split the linked list into two linked lists, one with even numbers, one with all odd numbers
- Method: 
    1. Base Case: Check if the original linked list is empty, if it is empty then return null LL
    2. In this step, it means the LL is not empty, assign first node in the LL, then use recursion to solve the rest of the LL
    3. When checking the first element in the LL, we have to make sure if evens and odds are NULL, if they are not NULL, we need to update the evens and odds or it will always have only one node and we will of course have memory leak for some nodes in the original LL
    4. Change the pointer to evens or odd and update the head pointer for original LL
    5. Before call next we have to make sure the pointer is not NULL

### Part 2
- Description: write functions to finish the unrolled linked list
- Method:
    1. push_back:
        1) check if the LL is empty, if empty, create a new node and change the corresponding value
        2) If the LL is not empty, divide into two cases: room left in the node or room already tooken
        in the back of the node: 
            room left: change corresponding values
            no room left: create new node and add value to the front of added node and change corresponding values
        4) increase size by 1
    2. push_front:
        1) check if the LL is empty, if empty, create a new node and change the corresponding value
        2) If the LL is not empty, divide into two cases: room left in the node or room already tooken
        at the front of the node: 
            room left: change corresponding values
            no room left: create new node and add value to the back of added node and change corresponding values
        4) increase size by 1
    3. pop_back:
        1) check if LL is empty, if so terminate the program
        2) decrease last by 1
        3) check if it becomes empty node and deallocate it if it's empty(check if the empty node has previous node to set head and tail)
    4. pop_front
        1) check if LL is empty, if so terminate the program
        2) decrease increase by 1
        3) check if it becomes empty node and deallocate it if it's empty(check if the empty node has next node to set head and tail)
    5. front
        Assume ignore the case when LL is empty by instructions in the video
        return the value of index last - 1 in the last node
    6. back
        Assume ignore the case when LL is empty by instructions in the video
        return the value of index first in the first node
    7. getValAtLoc 
        1) check if loc is valid
        2) when LL is empty, it fails the test above
        3) Sum over the number of valued nodes until it's bigger than loc
        4) record the sum before, difference between sum and sumBefore tells us where the value is in the node
        4) update corresponding value
- Test cases:
    test for the functionaliies of the functions above by using different number of lists and some boundary numbers such as empty list, list with 10 elements
