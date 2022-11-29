# Homework 3 Programming Part
Name: Jinghao (Daniel) Wang
USC ID: 4237145509
USC Net ID: jinghao

## Contents
- coloring.cpp
- MinHeap.h
- Makefile
- README.md

## Compile Method
Simply by typing make or make coloring as indicated in Makefile

## Assignment Expected Behavior
### Problem 1
- Read input file
    1. Report error message if no input file given at command and terminate the program
    2. Report error message if the given input file does not exist and terminate the program
    
- Helper functions
    1. getNeighborMatrix
    2. checkColors
    3. assignColors
    
- Behavior of the Program
    1. Do nothing if countriesNum = 0, if columns or row is 0, then assign all countries with same color (1)
    2. Run within 1 minute as instructed even with countriesNum = 15, rows = columns = 80 without using Valgrind
    3. It would give the answer minimized the use of colors, would always output with the minimum coloring, explore each country starting from 1 to 4, the output will always be the output that is the first one coming up during exploration. If both A = 1, B = 2, C = 1 and A = 2 , B = 1, C =2 are valid coloring, it will output the first option since it is the first one we found as valid coloring
    4. Applied to only valid mapping as indicated by professor on Piazza
    
### Problem 2
- Style
    1. Implemented the class functions in .h file as instructed in the instructions
    2. Use one vector to store the value of elements, another vector to store the priorities of elements, both have same index and size, which mean the i-th element(order determined by priorities in general) in values vector and priorities vector correspond to the i-th element's value and priority in the heap, just storing those separately
    3. When swapping elements, it is determined by priorities if two elements needs be swapped, whenever two elements are swaped, both element's value and priority get swapped
    4. Use private variable size_, d_, trickleUp function, trickleDown function and two vectors as indicated above
- Constructor
    1. Works for any d >= 2 as instructed
    2. Do nothing if d <= 1
    3. Assign size_ = 0; d_ = d 
    
- Destructor
    1. Did not use any dynamic allocated memory here, so there is no implementations for destructor
    
- Add function
    1. Add elements's value and priority separately into the end of values vector and priorities vector, then use trickleUp function to update its location in the heap
    2. TrickleUp function would only swap the element and its parent if the priority of the parent(only when it exists) is strictly larger than the priority of the element, if having equal priority, remain the same. When swapped, both values and priorities get swapped
    3. Update private variable size_
    4. When size_ is 1, while loop in trickleUp function would not execute, just the same as pushing back an element(both value and priority) to corresponding vector
    
- Peek function
    1. If the heap is empty, throw an exception with message
    2. If the heap is not empty, return the first elemnt's value in the vector array, that element is guaranteed to have minimum priority value in the heap; If two elements both have smallest priority, return the first one showed up in the values vector

- Remove function:
    1. If the heap has size of 1, no need to call trickleDown function, just simply pop_back its value and priority in corresponding vector
    2. If the heap has size greater than 1, assign the last element's value and priority to the first element in both vectors, decrease the size_ and call trickleDown function to update the first node's location in heap
    3. If the heap has size of 0, throw an exception with error message
    4. TrickleDown function:
        (1) If  the element does not have children, then do nothing since it is a leaf node
        (2) If the element has d children, then loop through all its children to find the child with smallest priority, compared with the element's priority. If the element's priority is strictly greater than that child's priority, swap two elements (both value and priority in correpsonding vectors). When priorities are the same, do not swap. If some children share the same minimum priority among its siblings, then take the first(left-most for these childrens with same priority) children that has that minimum priority.
        (3) If the element has children but not less than d children, then loop through all its existing children to find the child with smallest priority, compared with the element's priority. If the element's priority is strictly greater than that child's priority, swap two elements (both value and priority in correpsonding vectors). When priorities are the same, do not swap. If some children share the same minimum priority among its siblings, then take the first(left-most for these childrens with same priority)) children that has that minimum priority.
        
- isEmpty fuction
    1. Simply just compare if size_ is zero, if it is zero, then return true, else return false
