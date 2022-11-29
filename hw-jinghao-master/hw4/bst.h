#ifndef BST_H
#define BST_H

#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template<typename Key, typename Value>
class Node {
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value& value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
 * Explicit constructor for a node.
 */
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
        : item_(key, value), parent_(parent), left_(NULL), right_(NULL) {}

/**
 * Destructor, which does not need to do anything since the pointers inside of a node
 * are only used as references to existing nodes. The nodes pointed to by parent/left/right
 * are freed within the deleteAll() helper method in the BinarySearchTree.
 */
template<typename Key, typename Value>
Node<Key, Value>::~Node() {}

/**
 * A const getter for the item.
 */
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const {
    return item_;
}

/**
 * A non-const getter for the item.
 */
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() {
    return item_;
}

/**
 * A const getter for the key.
 */
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const {
    return item_.first;
}

/**
 * A const getter for the value.
 */
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const {
    return item_.second;
}

/**
 * A non-const getter for the value.
 */
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue() {
    return item_.second;
}

/**
 * An implementation of the virtual function for retreiving the parent.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const {
    return parent_;
}

/**
 * An implementation of the virtual function for retreiving the left child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const {
    return left_;
}

/**
 * An implementation of the virtual function for retreiving the right child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const {
    return right_;
}

/**
 * A setter for setting the parent of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) {
    parent_ = parent;
}

/**
 * A setter for setting the left child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) {
    left_ = left;
}

/**
 * A setter for setting the right child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) {
    right_ = right;
}

/**
 * A setter for the value of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) {
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
 * A templated unbalanced binary search tree.
 */
template<typename Key, typename Value>
class BinarySearchTree {
public:
    BinarySearchTree();                                                    // TODO
    virtual ~BinarySearchTree();                                           // TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair);  // TODO
    virtual void remove(const Key& key);                                   // TODO
    void clear();                                                          // TODO
    bool isBalanced() const;                                               // TODO
    void print() const;
    bool empty() const;

public:
    /**
     * An internal iterator class for traversing the contents of the BST.
     */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key, Value>& operator*() const;
        std::pair<const Key, Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key, Value>* ptr);
        Node<Key, Value>* current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const;               // TODO
    Node<Key, Value>* getSmallestNode() const;                        // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current);  // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot(Node<Key, Value>* r) const;
    virtual void nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2);

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void clearHelper(Node<Key, Value>* loc);
    int isBalancedHelper(Node<Key, Value>* loc) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
 * Explicit constructor that initializes an iterator with a given node pointer.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value>* ptr) {
    // assign the pointer or the node to current
    current_ = ptr;
}

/**
 * A default constructor that initializes the iterator to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() {
    // assign the pointer current to NULL pointer
    current_ = NULL;
}

/**
 * Provides access to the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const {
    return current_->getItem();
}

/**
 * Provides access to the address of the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const {
    return &(current_->getItem());
}

/**
 * Checks if 'this' iterator's internals have the same value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    // check if the memory address of two pointers are the same
    if (this->current_ == rhs.current_) {
        // if the same, return true
        return true;
    } else {
        // else return false
        return false;
    }
}

/**
 * Checks if 'this' iterator's internals have a different value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    // check if the memory address of two pointers are the same
    if (this->current_ != rhs.current_) {
        // if not the same, return true
        return true;
    } else {
        // if the same, return false
        return false;
    }
}

/**
 * Advances the iterator's location using an in-order sequencing
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++() {
    // Find the next element in order, which is successor of current_
    current_ = successor(current_);
    return *this;
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
 * Default constructor for a BinarySearchTree, which sets the root to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() {
    // initialize the pointer root_ be NULL pointer
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
    // call clear function to deallocate the memory for all nodes
    clear();
}

/**
 * Returns true if tree is empty
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const {
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const {
    printRoot(root_);
    std::cout << "\n";
}

/**
 * Returns an iterator to the "smallest" item in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const {
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
 * Returns an iterator whose value means INVALID
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const {
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& k) const {
    Node<Key, Value>* curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * An insert method to insert into a Binary Search Tree.
 * The tree will not remain balanced when inserting.
 */
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair) {
    // check if the bst is empty
    if (root_ == NULL) {
        // create a newNode with KeyValuePair's key and value, with NULL as parent
        Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        // if bst is empty, just change the root_ pointer to the new node
        root_ = newNode;
    } else {
        // if the bst is not empty，then place the new node at correct place
        // create a pointer temp to store value of root_ without changing root_pointer
        Node<Key, Value>* temp = root_;
        while (temp != NULL) {
            // check where the newNode should be placed
            // key is the same as key of temp, key is in the tree, then update its value to new value
            if (temp->getKey() == keyValuePair.first) {
                temp->setValue(keyValuePair.second);
                return;
            }
            // new node is to the left of the temp
            else if (temp->getKey() > keyValuePair.first) {
                // if temp has no left children, then change the parent and insert new node to temp
                if (temp->getLeft() == NULL) {
                    // create a newNode with KeyValuePair's key and value, with temp as parent
                    Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
                    temp->setLeft(newNode);
                    return;
                }
                // if temp has left children, then keep searching until node without left child shows
                // set temp to be its left child
                temp = temp->getLeft();
            }
            // new node is to the right of the temp
            else if (temp->getKey() < keyValuePair.first) {
                // if temp has no right children, then change the parent and insert new node to temp
                if (temp->getRight() == NULL) {
                    // create a newNode with KeyValuePair's key and value, with temp as parent
                    Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
                    temp->setRight(newNode);
                    return;
                }
                // if temp has right children, then keep searching until node without right child shows
                // set temp to be its right child
                temp = temp->getRight();
            }
        }
    }
}

/**
 * A remove method to remove a specific key from a Binary Search Tree.
 * The tree may not remain balanced after removal.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key) {
    // check if key exists in the bst
    // create a pointer loc to point to the node with specific key
    Node<Key, Value>* loc = internalFind(key);
    // if loc is NULL, it means the key does not exit in the bst
    if (loc == NULL) {
        // do nothing
        return;
    }

    // if loc is not NULL, it means the key exits in the bst
    // check if the node has children
    // if loc has two children
    if (loc->getLeft() != NULL && loc->getRight() != NULL) {
        // swap the node with its predecessor
        Node<Key, Value>* predNode = predecessor(loc);
        nodeSwap(loc, predNode);
    }

    // After swapping with predecessor, we go back to the case the node has 1 or 0 children
    // or the node has 1 or 0 children at the first place will skip if statment above
    // if loc has no children
    if (loc->getLeft() == NULL && loc->getRight() == NULL) {
        // check if loc has parent
        if (loc->getParent() == NULL) {  // loc has no parent
            // it is root node, change root_ to be NULL
            root_ = NULL;
        } else {  // loc has parent
            // check if loc is a left child or right child of its parent
            if (loc->getParent()->getLeft() == loc) {
                // if the loc is left child of its parent
                // change its parent's left children to be NULL
                loc->getParent()->setLeft(NULL);
            } else if (loc->getParent()->getRight() == loc) {
                // if the loc is right child of its parent
                // change its parent's right children to be NULL
                loc->getParent()->setRight(NULL);
            }
        }
    }
    // if loc has only one left child
    else if (loc->getLeft() != NULL && loc->getRight() == NULL) {
        // check if loc has parent
        if (loc->getParent() == NULL) {  // loc has no parent
            // it is root node, change parent of left child and root_ to be its left child
            loc->getLeft()->setParent(NULL);
            root_ = loc->getLeft();
        } else {  // loc has parent
            // check if loc is a left child or right child of its parent
            if (loc->getParent()->getLeft() == loc) {
                // if the loc is left child of its parent
                // change its left child's parent to be its parent
                // and its parent's left children to be loc's left child
                loc->getLeft()->setParent(loc->getParent());
                loc->getParent()->setLeft(loc->getLeft());
            } else if (loc->getParent()->getRight() == loc) {
                // if the loc is right child of its parent
                // change its left child's parent to be its parent
                // and its parent's right children to be loc's left child
                loc->getLeft()->setParent(loc->getParent());
                loc->getParent()->setRight(loc->getLeft());
            }
        }
    }
    // if loc has only one right child
    else if (loc->getLeft() == NULL && loc->getRight() != NULL) {
        // check if loc has parent
        if (loc->getParent() == NULL) {  // loc has no parent
            // it is root node, change parent of right child and root_ to be its right child
            loc->getRight()->setParent(NULL);
            root_ = loc->getRight();
        } else {  // loc has parent
            // check if loc is a left child or right child of its parent
            if (loc->getParent()->getLeft() == loc) {
                // if the loc is left child of its parent
                // change its right child's parent to be its parent
                // and its parent's left children to be loc's right child
                loc->getRight()->setParent(loc->getParent());
                loc->getParent()->setLeft(loc->getRight());
            } else if (loc->getParent()->getRight() == loc) {
                // if the loc is right child of its parent
                // change its right child's parent to be its parent
                // and its parent's right children to be loc's right child
                loc->getRight()->setParent(loc->getParent());
                loc->getParent()->setRight(loc->getRight());
            }
        }
    }
    // deallocate the memory for loc
    delete loc;
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) {
    // create a temp node pointer without changing values of current
    Node<Key, Value>* temp;
    // check if current has left child
    if (current->getLeft() == NULL) {  // if current has no left child
        temp = current;
        // go through ancestor nodes until found a node's parent has right node of that node
        while (temp->getParent() != NULL && temp->getParent()->getRight() != temp) {
            temp = temp->getParent();
        }
        return temp->getParent();
    } else {  // if current has left child
        temp = current->getLeft();
        // go through right subtree of its left child until a leaf node found
        while (temp->getRight() != NULL) {
            temp = temp->getRight();
        }
        return temp;
    }
}

/**
 * A method to remove all contents of the tree and
 * reset the values in the tree for use again.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() {
    // call helper function clearHelper
    clearHelper(root_);
    // change the root_ to be NULL
    root_ = NULL;
}

/**
 * A helper function to find the smallest node in the tree.
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const {
    // check if the bst is empty
    if (root_ == NULL) {  // if the bst is empty
        // do nothing, return NULL
        return NULL;
    }
    // if the bst is not empty
    else {
        // find the left most bottom leaf node
        // creata a pointer temp to store the value of root_ without changing it
        Node<Key, Value>* temp = root_;
        // while loop to find smallest node
        while (temp->getLeft() != NULL) {
            temp = temp->getLeft();
        }
        return temp;
    }
}

/**
 * Helper function to find a node with given key, k and
 * return a pointer to it or NULL if no item with that key
 * exists
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const {
    // creata a pointer temp to store the value of root_ without changing it
    Node<Key, Value>* temp = root_;
    // while loop to find the node with input key
    while (temp != NULL) {
        if (temp->getKey() == key) {
            return temp;
        } else if (temp->getKey() > key) {
            temp = temp->getLeft();
        } else {
            temp = temp->getRight();
        }
    }
    // if not returned in while loop, which means it does not exit in the tree
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const {
    // call helper function isBalancedHelper
    return (isBalancedHelper(root_) != -1);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2) {
    if ((n1 == n2) || (n1 == NULL) || (n2 == NULL)) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if (n1p != NULL && (n1 == n1p->getLeft()))
        n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if (n2p != NULL && (n2 == n2p->getLeft()))
        n2isLeft = true;

    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if ((n1r != NULL && n1r == n2)) {
        n2->setRight(n1);
        n1->setParent(n2);
    } else if (n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    } else if (n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    } else if (n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);
    }

    if (n1p != NULL && n1p != n2) {
        if (n1isLeft)
            n1p->setLeft(n2);
        else
            n1p->setRight(n2);
    }
    if (n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if (n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if (n2p != NULL && n2p != n1) {
        if (n2isLeft)
            n2p->setLeft(n1);
        else
            n2p->setRight(n1);
    }
    if (n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if (n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }

    if (this->root_ == n1) {
        this->root_ = n2;
    } else if (this->root_ == n2) {
        this->root_ = n1;
    }
}

/**
 * A helper function to find successor of specific node
 */
template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current) {
    // check if current is NULL;
    if (current == NULL) {
        return NULL;
    }
    // create a temp node pointer without changing values of current
    Node<Key, Value>* temp;
    // check if current has right child
    if (current->getRight() == NULL) {  // if current has no right child
        temp = current;
        // go through ancestor nodes until found a node's parent has left node of that node
        while (temp->getParent() != NULL && temp->getParent()->getLeft() != temp) {
            temp = temp->getParent();
        }
        return temp->getParent();
    } else {  // if current has right child
        temp = current->getRight();
        // go through left subtree of its right child until a leaf node found
        while (temp->getLeft() != NULL) {
            temp = temp->getLeft();
        }
        return temp;
    }
}

/**
 * A helper function to clear the bst tree rooted at loc
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* loc) {
    // check if loc is NULL
    if (loc == NULL) {
        // if the bst is empty do nothing
        return;
    }
    // if loc is not NULL
    // recursively call clearHelper
    clearHelper(loc->getLeft());

    // recursively call clearHelper
    clearHelper(loc->getRight());

    // deallocate the memory for loc
    delete loc;
}

/**
 * A helper function to get the height of bst tree rooted at loc
 */
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* loc) const {
    // check if loc is NULL
    if (loc == NULL) {  // if loc is NULL, do nothing
        return 0;
    }

    // if loc is not NULL, recursively call isBalancedHelper
    int lBalance = isBalancedHelper(loc->getLeft());
    int rBalance = isBalancedHelper(loc->getRight());
    // if left tree or right tree is not balanced or the difference between two trees are bigger than 1
    // then the tree is not balanced
    if (lBalance == -1 || rBalance == -1 || (lBalance - rBalance) > 1 || (lBalance - rBalance) < -1) {
        return -1;
    }
    // if the subtrees are balanced, then give the root node of value maximum of the subtrees + 1
    else {
        if (lBalance >= rBalance) {
            return lBalance + 1;
        } else {
            return rBalance + 1;
        }
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
