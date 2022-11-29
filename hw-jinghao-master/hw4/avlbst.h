#ifndef RBBST_H
#define RBBST_H

#include "bst.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError {};

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
        : Node<Key, Value>(key, value, parent), height_(1) {}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode() {}

/**
 * A getter for the height of a AVLNode.
 */
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const {
    return height_;
}

/**
 * A setter for the height of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height) {
    height_ = height;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
    virtual void insert(const std::pair<const Key, Value>& new_item);  // TODO
    virtual void remove(const Key& key);                               // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key, Value>* g);
    void rotateRight(AVLNode<Key, Value>* g);
    bool isLeftChild(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p) const;
    bool isRightChild(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p) const;
    bool isZigZig(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p, AVLNode<Key, Value>* g) const;
    bool isZigZag(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p, AVLNode<Key, Value>* g) const;
    void insertFix(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p);
    void removeFix(AVLNode<Key, Value>* n);
    int calculateHeight(AVLNode<Key, Value>* n);
    AVLNode<Key, Value>* getTallerChild(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p);
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item) {
    // check if the AVLTree is empty
    if (this->root_ == NULL) {
        // create a new AVL node with same value and key, with NULL as parent
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        // set height of this node to be 1
        newNode->setHeight(1);
        // change the root pointer to be newNode
        this->root_ = newNode;
    }
    // if the AVLTree is not empty
    else {
        // create an AVLNode temp the same as root_
        AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
        // while loop to insert it as a leaf node
        while (temp != NULL) {
            // insert the node like bst, then call insertFix
            if (temp->getKey() == new_item.first) {  // if the temp has same key
                // update the value of that key
                temp->setValue(new_item.second);
                return;
            } else if (temp->getKey() > new_item.first) {  // if temp has bigger key than new_item's key
                // go to the left subtree
                // check if temp has left child
                if (temp->getLeft() == NULL) {  // if temp doesn't have left child
                    // insert the node to temp's left
                    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
                    // set height for newNode
                    newNode->setHeight(1);
                    // set temp's left child
                    temp->setLeft(newNode);
                    // check if temp has right child
                    if (temp->getRight() == NULL) {  // if temp doesn't have right child
                        // need to fix height of Node temp and above
                        temp->setHeight(calculateHeight(temp));
                        insertFix(newNode, temp);
                    }
                    // else since temp has right child, and tree are balanced, which means height could only be 1
                    // for right subtree of temp, it's still balanced, doesn't need to do anything
                    return;
                }
                // else update temp to be its left child
                temp = temp->getLeft();
            } else {  // if temp has smaller key than new_item's key
                // go to the right subtree
                // check if temp has right child
                if (temp->getRight() == NULL) {  // if temp doesn't have right child
                    // insert the node to temp's right
                    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
                    // set height for newNode
                    newNode->setHeight(1);
                    // set temp's right child
                    temp->setRight(newNode);
                    // check if temp has left child
                    if (temp->getLeft() == NULL) {  // if temp doesn't have left child
                        // need to fix height of Node temp and above
                        temp->setHeight(calculateHeight(temp));
                        insertFix(newNode, temp);
                    }
                    // else since temp has left child, and tree are balanced, which means height could only be 1
                    // for left subtree of temp, it's still balanced, doesn't need to do anything
                    return;
                }
                // else update temp to be its right child
                temp = temp->getRight();
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key) {
    // Find node with specific key and store it as AVLNode
    AVLNode<Key, Value>* loc = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    // check if loc is NULL
    if (loc == NULL) {
        // if loc is NULL, the key does not exits in AVLTree, do nothing
        return;
    }

    // if loc is not NULL
    AVLNode<Key, Value>* parentNode = loc->getParent();

    // if loc has two children
    if (loc->getLeft() != NULL && loc->getRight() != NULL) {
        // swap the node with its predecessor
        AVLNode<Key, Value>* predNode = static_cast<AVLNode<Key, Value>*>(this->predecessor(loc));
        nodeSwap(loc, predNode);
        if (loc != NULL) {
            loc->setHeight(calculateHeight(loc));
        }
        if (predNode != NULL) {
            predNode->setHeight(calculateHeight(predNode));
        }
        parentNode = loc->getParent();
    }

    // if loc has no children
    if (loc->getLeft() == NULL && loc->getRight() == NULL) {
        // check if loc has parent
        if (loc->getParent() == NULL) {  // loc has no parent
            // it is root node, change root_ to be NULL
            this->root_ = NULL;
        } else {  // loc has parent
            // check if loc is a left child or right child of its parent
            if (isLeftChild(loc, loc->getParent())) {
                // if the loc is left child of its parent
                // change its parent's left children to be NULL
                loc->getParent()->setLeft(NULL);
                loc->getParent()->setHeight(calculateHeight(loc->getParent()));
            } else if (isRightChild(loc, loc->getParent())) {
                // if the loc is right child of its parent
                // change its parent's right children to be NULL
                loc->getParent()->setRight(NULL);
                loc->getParent()->setHeight(calculateHeight(loc->getParent()));
            }
        }
    }
    // if loc has only one left child
    else if (loc->getLeft() != NULL && loc->getRight() == NULL) {
        // check if loc has parent
        if (loc->getParent() == NULL) {  // loc has no parent
            // it is root node, change parent of left child and root_ to be its left child
            loc->getLeft()->setParent(NULL);
            this->root_ = loc->getLeft();
            // update the height
            loc->getLeft()->setHeight(calculateHeight(loc->getLeft()));
        } else {  // loc has parent
            // check if loc is a left child or right child of its parent
            if (isLeftChild(loc, loc->getParent())) {
                // if the loc is left child of its parent
                // change its left child's parent to be its parent
                // and its parent's left children to be loc's left child
                loc->getLeft()->setParent(loc->getParent());
                loc->getParent()->setLeft(loc->getLeft());
                // update the height
                loc->getLeft()->setHeight(calculateHeight(loc->getLeft()));
                loc->getParent()->setHeight(calculateHeight(loc->getParent()));
            } else if (isRightChild(loc, loc->getParent())) {
                // if the loc is right child of its parent
                // change its left child's parent to be its parent
                // and its parent's right children to be loc's left child
                loc->getLeft()->setParent(loc->getParent());
                loc->getParent()->setRight(loc->getLeft());
                // update the height
                loc->getLeft()->setHeight(calculateHeight(loc->getLeft()));
                loc->getParent()->setHeight(calculateHeight(loc->getParent()));
            }
        }
    }
    // if loc has only one right child
    else if (loc->getLeft() == NULL && loc->getRight() != NULL) {
        // check if loc has parent
        if (loc->getParent() == NULL) {  // loc has no parent
            // it is root node, change parent of right child and root_ to be its right child
            loc->getRight()->setParent(NULL);
            this->root_ = loc->getRight();
            // update the height
            loc->getRight()->setHeight(calculateHeight(loc->getRight()));
        } else {  // loc has parent
            // check if loc is a left child or right child of its parent
            if (isLeftChild(loc, loc->getParent())) {
                // if the loc is left child of its parent
                // change its right child's parent to be its parent
                // and its parent's left children to be loc's right child
                loc->getRight()->setParent(loc->getParent());
                loc->getParent()->setLeft(loc->getRight());
                // update the height
                loc->getRight()->setHeight(calculateHeight(loc->getRight()));
                loc->getParent()->setHeight(calculateHeight(loc->getParent()));
            } else if (isRightChild(loc, loc->getParent())) {
                // if the loc is right child of its parent
                // change its right child's parent to be its parent
                // and its parent's right children to be loc's right child
                loc->getRight()->setParent(loc->getParent());
                loc->getParent()->setRight(loc->getRight());
                // update the height
                loc->getRight()->setHeight(calculateHeight(loc->getRight()));
                loc->getParent()->setHeight(calculateHeight(loc->getParent()));
            }
        }
    }
    // deallocate memory for loc
    delete loc;

    if (parentNode != NULL) {
        parentNode->setHeight(calculateHeight(parentNode));
    }
    // call removeFix()
    removeFix(parentNode);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2) {
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* g) {
    // check if n is NULL
    if (g == NULL) {  // if n is NULL
        // Do nothing
        return;
    }

    // if n is not NULL
    // check if n has right child
    if (g->getRight() == NULL) {  // if n's right child is NULL
        // Do nothing
        return;
    }
    // change g's parent to be g's  right child's parent
    g->getRight()->setParent(g->getParent());

    // change g's parent's child to be g's right child
    // check if g's parent is NULL
    if (g->getParent() != NULL) {
        if (isLeftChild(g, g->getParent())) {
            g->getParent()->setLeft(g->getRight());
        } else {
            g->getParent()->setRight(g->getRight());
        }
    }

    // change g's right child as g's parent
    g->setParent(g->getRight());

    // check if g's right child has left child
    if (g->getRight()->getLeft() != NULL) {
        // change g's right child's left child's parent to be g
        g->getRight()->getLeft()->setParent(g);
    }

    // set g's right child to be g's right child's left child
    g->setRight(g->getRight()->getLeft());

    // set g's right child's left child to be g
    g->getParent()->setLeft(g);

    // if g is root node original, then change the root_ pointer to be g's original right child
    if (g->getParent()->getParent() == NULL) {
        this->root_ = g->getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* g) {
    // check if n is NULL
    if (g == NULL) {  // if n is NULL
        // Do nothing
        return;
    }

    // if n is not NULL
    // check if n has left child
    if (g->getLeft() == NULL) {  // if n's left child is NULL
        // Do nothing
        return;
    }
    // change g's parent to be g's left child's parent
    g->getLeft()->setParent(g->getParent());

    // change g's parent's child to be g's left child
    // check if g's parent is NULL
    if (g->getParent() != NULL) {
        if (isLeftChild(g, g->getParent())) {
            g->getParent()->setLeft(g->getLeft());
        } else {
            g->getParent()->setRight(g->getLeft());
        }
    }

    // change g's left child as g's parent
    g->setParent(g->getLeft());

    // check if g's left child has right child
    if (g->getLeft()->getRight() != NULL) {
        // change g's right child's left child's parent to be g
        g->getLeft()->getRight()->setParent(g);
    }

    // set g's left child to be g's left child's right child
    g->setLeft(g->getLeft()->getRight());

    // set g's left child's right child to be g
    g->getParent()->setRight(g);

    // if g is root node original, then change the root_ pointer to be g's original left child
    if (g->getParent()->getParent() == NULL) {
        this->root_ = g->getParent();
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p) const {
    return (p->getLeft() == n);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p) const {
    return (p->getRight() == n);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZig(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p, AVLNode<Key, Value>* g) const {
    return ((isLeftChild(n, p) && isLeftChild(p, g)) || (isRightChild(n, p) && isRightChild(p, g)));
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZag(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p, AVLNode<Key, Value>* g) const {
    return ((isRightChild(n, p) && isLeftChild(p, g)) || (isLeftChild(n, p) && isRightChild(p, g)));
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p) {
    // check if p has parent
    if (p == NULL || p->getParent() == NULL) {  // if p has no parent
        // done, doesn't need to do anything
        return;
    }
    // if p has parent
    AVLNode<Key, Value>* g = p->getParent();
    // check if p is left child or right child of g
    if (isLeftChild(p, g)) {
        int gRightHeight = calculateHeight(g->getRight());
        // if height of g doesn't change
        if (gRightHeight - p->getHeight() == 0) {
            // done, do nothing
            return;
        }
        // if g is balanced but height changes
        else if (gRightHeight - p->getHeight() == -1 || gRightHeight - p->getHeight() == 1) {
            // update g's height
            g->setHeight(calculateHeight(g));
            insertFix(p, g);
        }
        // if g is not balanced
        else {
            // need to do rotations since it is unbalanced
            if (isZigZig(n, p, g)) {
                rotateRight(g);
                // update the height
                n->setHeight(calculateHeight(n));
                p->setHeight(calculateHeight(p));
                g->setHeight(calculateHeight(g));
            } else if (isZigZag(n, p, g)) {
                rotateLeft(p);
                rotateRight(g);
                // update the height
                n->setHeight(calculateHeight(n));
                p->setHeight(calculateHeight(p));
                g->setHeight(calculateHeight(g));
            }
        }
    } else if (isRightChild(p, g)) {
        int gLeftHeight = calculateHeight(g->getLeft());
        // if height of g doesn't change
        if (gLeftHeight - p->getHeight() == 0) {
            // done, do nothing
            return;
        }
        // if g is balanced but height changes
        else if (gLeftHeight - p->getHeight() == -1 || gLeftHeight - p->getHeight() == 1) {
            g->setHeight(calculateHeight(g));
            insertFix(p, g);
        }
        // if g is not balanced
        else {
            // need to do rotations since it is unbalanced
            if (isZigZig(n, p, g)) {
                rotateLeft(g);
                // update the height
                n->setHeight(calculateHeight(n));
                p->setHeight(calculateHeight(p));
                g->setHeight(calculateHeight(g));
            } else if (isZigZag(n, p, g)) {
                rotateRight(p);
                rotateLeft(g);
                // update the height
                n->setHeight(calculateHeight(n));
                p->setHeight(calculateHeight(p));
                g->setHeight(calculateHeight(g));
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n) {
    // check if n is NULL
    if (n == NULL) {  // if n is NULL
        return;
    }
    AVLNode<Key, Value>* p = n->getParent();
    // if n is not NULL
    // check if n is out of balance
    if (calculateHeight(n->getLeft()) - calculateHeight(n->getRight()) > 1
        || calculateHeight(n->getLeft()) - calculateHeight(n->getRight()) < -1) {
        // c, g must exist since the avl tree is not blanced when the difference is greater than 1
        // then it means the taller subtree has at least height of 2
        AVLNode<Key, Value>* c = getTallerChild(n, n->getParent());
        AVLNode<Key, Value>* g = getTallerChild(c, n);
        // check it's Zig-Zig or Zig-Zag with its direction
        if (isZigZig(g, c, n) && isLeftChild(c, n)) {
            rotateRight(n);
            // update the height
            g->setHeight(calculateHeight(g));
            c->setHeight(calculateHeight(c));
            n->setHeight(calculateHeight(n));
        } else if (isZigZig(g, c, n) && isRightChild(c, n)) {
            rotateLeft(n);
            // update the height
            g->setHeight(calculateHeight(g));
            c->setHeight(calculateHeight(c));
            n->setHeight(calculateHeight(n));
        } else if (isZigZag(g, c, n) && isLeftChild(c, n)) {
            rotateLeft(c);
            rotateRight(n);
            // update the height
            g->setHeight(calculateHeight(g));
            c->setHeight(calculateHeight(c));
            n->setHeight(calculateHeight(n));
        } else if (isZigZag(g, c, n) && isRightChild(c, n)) {
            rotateRight(c);
            rotateLeft(n);
            // update the height
            g->setHeight(calculateHeight(g));
            c->setHeight(calculateHeight(c));
            n->setHeight(calculateHeight(n));
        }
        // call removeFix again
        removeFix(p);
    }
    // if the height doesn't change
    else if (
            calculateHeight(n->getLeft()) - calculateHeight(n->getRight()) == 1
            || calculateHeight(n->getLeft()) - calculateHeight(n->getRight()) == -1) {
        return;
    }
    // else
    else {
        // update the height
        if (p != NULL) {
            p->setHeight(calculateHeight(p));
        }
        // call removeFix Again
        removeFix(p);
    }
}

template<class Key, class Value>
int AVLTree<Key, Value>::calculateHeight(AVLNode<Key, Value>* n) {
    // if node n is NULL, return 0
    if (n == NULL) {
        return 0;
    }
    // initialize height to be 0
    int leftHeight = 0;
    int rightHeight = 0;
    // check if left child is NULL, if not calculate height
    if (n->getLeft() != NULL) {
        leftHeight = calculateHeight(n->getLeft());
    }
    // check if right child is NULL, if not calculate height
    if (n->getRight() != NULL) {
        rightHeight = calculateHeight(n->getRight());
    }
    // return the max height of two children + 1
    if (leftHeight >= rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getTallerChild(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p) {
    // If node is unbalanced, it guarantees has one child with at least height of 2
    // get child with higher height
    if (calculateHeight(n->getLeft()) > calculateHeight(n->getRight())) {
        return n->getLeft();
    } else if (calculateHeight(n->getLeft()) < calculateHeight(n->getRight())) {
        return n->getRight();
    }
    // if height of two child are equal, take the one gives you Zig-Zig
    else {
        if (isLeftChild(n, p)) {
            return n->getLeft();
        } else {
            return n->getRight();
        }
    }
}

#endif
