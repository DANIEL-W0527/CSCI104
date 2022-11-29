#include "ulliststr.h"

#include <cstddef>
#include <stdexcept>

ULListStr::ULListStr() {
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

ULListStr::~ULListStr() { clear(); }

bool ULListStr::empty() const { return size_ == 0; }

size_t ULListStr::size() const { return size_; }

// Adds a new value to the back of the list in O(1)
void ULListStr::push_back(const std::string& val) {
    // check if the list is empty
    if (empty()) {
        // if the list is empty, add one item
        Item* newItem = new Item();
        // update head_, tail_, val, last
        head_ = newItem;
        tail_ = newItem;
        // add val in the front of new node
        head_->val[head_->first] = val;
        head_->last++;
    }
    // if the list is not empty
    else {
        // if the tail_ node has no room in the back
        if (tail_->last == ARRSIZE) {
            // create a new node to the end
            Item* newItem = new Item();
            // update prev of new node, next of old tail_ node, tail_ and tail_->last
            newItem->prev = tail_;
            tail_->next = newItem;
            tail_ = newItem;
            tail_->val[tail_->first] = val;
            tail_->last++;
        }
        // if the tail_ node has room in the back
        else {
            tail_->val[tail_->last] = val;
            tail_->last++;
        }
    }
    // increase size_ by 1
    size_++;
}

// Removes a value from the back of the list
void ULListStr::pop_back() {
    // check if list is empty
    if (empty()) {
        return;
    }

    // decrement tail_->last if it's bigger than 0
    if (tail_->last > 0) {
        // update last of the last node and size_
        tail_->last--;
        size_--;
    }
    // check if the last node is empty after pop_back
    if (tail_->first == tail_->last) {
        // deallocate the node if it's empty
        Item* temp = tail_;
        // check if the node before last node exists
        if (tail_->prev != NULL) {
            // update next of previous node and tail_ if exists
            tail_->prev->next = NULL;
            tail_ = tail_->prev;
        } else {
            // update head_ and tail_ if not existed
            head_ = NULL;
            tail_ = NULL;
        }
        // deallocate the last node
        delete temp;
    }
}

// Adds a new value to the front of the list in O(1)
void ULListStr::push_front(const std::string& val) {
    // check if the list is empty
    if (empty()) {
        // if the list is empty, add one item
        Item* newItem = new Item();
        // update head_, tail_, val, first, last
        head_ = newItem;
        tail_ = newItem;
        // add val in the front of new node
        head_->val[ARRSIZE - 1] = val;
        head_->first = ARRSIZE - 1;
        head_->last = ARRSIZE;
    }
    // if the list is not empty
    else {
        // if the head_ node has no room in the front
        if (head_->first == 0) {
            // create a new node to the front
            Item* newItem = new Item();
            // update next of new node, prev of old head_ node, head_
            newItem->next = head_;
            head_->prev = newItem;
            head_ = newItem;
            head_->val[ARRSIZE - 1] = val;
            head_->last = ARRSIZE;
            head_->first = ARRSIZE - 1;
        }
        // if the head_ node has room in the front
        else {
            head_->val[head_->first - 1] = val;
            head_->first--;
        }
    }
    // increase size_ by 1
    size_++;
}

// Removes a value from the front of the list in O(1)
void ULListStr::pop_front() {
    // check if list is empty
    if (empty()) {
        return;
    }

    // increment head_->first if it's less than ARRSIZE
    if (head_->first < ARRSIZE) {
        // update first of the first node and size_
        head_->first++;
        size_--;
    }
    // check if the first node is empty after pop_back
    if (head_->first == head_->last) {
        // deallocate the node if it's empty
        Item* temp = head_;
        // check if the node after first node exists
        if (head_->next != NULL) {
            // update prev of latter node and head_ if exists
            head_->next->prev = NULL;
            head_ = head_->next;
        } else {
            // update head_ and tail_ if not existed
            head_ = NULL;
            tail_ = NULL;
        }
        // deallocate the last node
        delete temp;
    }
}

// Returns a const reference to the back element in O(1)
std::string const& ULListStr::back() const {
    // Assume not empty list
    // return the last string
    // since we deallocate the node if the node is empty in pop_back and pop_front
    // then the node must have some value
    return tail_->val[tail_->last - 1];
}

// Returns a const reference to the front element in O(1)
std::string const& ULListStr::front() const {
    // Assume not empty list
    // return the first string
    // since we deallocate the node if the node is empty in pop_back and pop_front
    // then the node must have some value
    return head_->val[head_->first];
}

void ULListStr::set(size_t loc, const std::string& val) {
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");
    }
    *ptr = val;
}

std::string& ULListStr::get(size_t loc) {
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

std::string const& ULListStr::get(size_t loc) const {
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

void ULListStr::clear() {
    while (head_ != NULL) {
        Item* temp = head_->next;
        delete head_;
        head_ = temp;
    }
    tail_ = NULL;
    size_ = 0;
}

/**
 * Returns a pointer to the item at index, loc,
 * if loc is valid and NULL otherwise
 * in O(n)
 */
std::string* ULListStr::getValAtLoc(size_t loc) const {
    // check if loc is valid, empty list won't pass this check
    if (loc < 0 || loc >= size_) {
        // if loc is not valid
        return NULL;
    } else {
        // if loc is valid
        Item* temp = head_;
        size_t sumBefore = 0;
        size_t sum = 0;
        while (sum < loc + 1) {
            sumBefore = sum;
            sum += (temp->last - temp->first);
            // check if the next node exists
            // if next node doesn't exits, it must be true that sum >= loc
            if (temp->next != NULL) {
                // if next node exists, update temp
                temp = temp->next;
            } else {
                temp = NULL;
            }
        }
        // check if temp is NULL
        if (temp == NULL) {
            // it means the element is in the last node of LL
            return &(tail_->val[tail_->last - size_ + loc]);
        }
        // when temp is not NULL
        else {
            // prev exits for temp because we checked above, or it will be NULL
            temp = temp->prev;
            // get the value
            return &(temp->val[temp->first + loc - sumBefore]);
        }
    }
}