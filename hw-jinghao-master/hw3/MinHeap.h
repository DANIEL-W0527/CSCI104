#include <algorithm>
#include <stdexcept>
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
       This should work for any d >= 2,
      but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true iff there are no elements on the heap. */

private:
    // vector items_ to store elements value
    std::vector<T> items_;
    // vector priority_ to store elements priority
    std::vector<int> priority_;
    // int to store size of the the heap
    int size_;
    // int d_ to store the dimension of the heap
    int d_;
    // helper functions
    // trickle up the last node for both values and priority
    void trickleUp(int loc);
    // trickle down the first node for both values and priority
    void trickleDown(int loc);
};

/* Constructor that builds a d-ary Min Heap
   This should work for any d >= 2,
   but doesn't have to do anything for smaller d.*/
template<class T>
MinHeap<T>::MinHeap(int d) {
    // when d >= 2, assign size_ to be 0 and d_ as d
    if (d >= 2) {
        size_ = 0;
        d_ = d;
    }
}

template<class T>
MinHeap<T>::~MinHeap() {}  // no dynamically allocated memory, don't need to do anything

/* adds the item to the heap, with the given priority. */
template<class T>
void MinHeap<T>::add(T item, int priority) {
    // add the item value and the priority to the end of the vector
    items_.push_back(item);
    priority_.push_back(priority);
    // update the size
    size_++;
    // trickle up the last element's values and priority
    trickleUp(size_ - 1);
}

/* returns the element with smallest priority.
   Break ties however you wish.
   Throws an exception if the heap is empty. */
template<class T>
const T& MinHeap<T>::peek() const {
    // if size is biggern than or equal to 1, return the first element in items_
    if (size_ >= 1) {
        return items_[0];
    }
    // if size is 0, throw an exception
    else {
        throw std::length_error("The heap is empty.");
    }
}

/* removes the element with smallest priority.
   Break ties however you wish.
   Throws an exception if the heap is empty. */
template<class T>
void MinHeap<T>::remove() {
    // if size is equal to 1, then remove the last element(both value and priority)
    if (size_ == 1) {
        items_.pop_back();
        priority_.pop_back();
        // update the size
        size_--;
    }
    // if size is bigger than or equal to 2
    else if (size_ >= 2) {
        // assign the first element to be the last element (both value and priority)
        // remove the last element (both value and priority)
        items_[0] = items_.back();
        items_.pop_back();
        priority_[0] = priority_.back();
        priority_.pop_back();
        // update the size
        size_--;
        // trickle down the first node (both value and priority)
        trickleDown(0);
    }
    // if the size is 0, throw an exception
    else {
        throw std::length_error("The heap is empty.");
    }
}

/* returns true iff there are no elements on the heap. */
template<class T>
bool MinHeap<T>::isEmpty() {
    // if size is 0, then return true, false otherwise
    return !size_;
}

template<class T>
void MinHeap<T>::trickleUp(int loc) {
    // create int parent to store the parent index
    int parent = (loc - 1) / d_;
    // keep swapping if the parent of the element exists and
    // the parent's priority is bigger than the element's priority
    while (parent >= 0 && priority_[loc] < priority_[parent]) {
        // swap both values and priorities
        std::swap(priority_[loc], priority_[parent]);
        std::swap(items_[loc], items_[parent]);
        // update the loc to be its parent's index and update the new parent index
        loc = parent;
        parent = (loc - 1) / d_;
    }
}

template<class T>
void MinHeap<T>::trickleDown(int loc) {
    // if the element doesn't have any child, do nothing
    if ((d_ * loc + 1) >= size_) {
        return;
    }
    // create two variables to store the index for its first child
    // and the index of child with smallest priority, intialize with first child's index
    int smallerChild = d_ * loc + 1;
    int smallestChildren = d_ * loc + 1;
    // if the element exists d children
    if (smallerChild + d_ - 1 < size_) {
        // loop through all children, find the child with smallestChildren
        // when children have same priority would take the first one
        for (int i = 0; i < d_; ++i) {
            if (priority_[smallerChild + i] < priority_[smallestChildren]) {
                smallestChildren = smallerChild + i;
            }
        }
        // if the priority of the child with smallest priority is smaller than the element's priority
        if (priority_[loc] > priority_[smallestChildren]) {
            // swap both value and priority
            std::swap(priority_[loc], priority_[smallestChildren]);
            std::swap(items_[loc], items_[smallestChildren]);
            // recursion to keep swapping between that child and its children if necessary
            trickleDown(smallestChildren);
        }
    }
    // if the element has children but not d children (smaller than d children)
    else if (smallerChild + d_ - 1 >= size_) {
        // loop through all children, find the child with smallestChildren
        // when children have same priority would take the first one
        for (int i = 0; i < size_ - smallerChild; ++i) {
            if (priority_[smallerChild + i] < priority_[smallestChildren]) {
                smallestChildren = smallerChild + i;
            }
        }
        // if the priority of the child with smallest priority is smaller than the element's priority
        if (priority_[loc] > priority_[smallestChildren]) {
            // swap both value and priority
            std::swap(priority_[loc], priority_[smallestChildren]);
            std::swap(items_[loc], items_[smallestChildren]);
            // recursion to keep swapping between that child and its children if necessary
            trickleDown(smallestChildren);
        }
    }
}