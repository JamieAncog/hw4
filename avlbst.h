#ifndef AVLBST_H
#define AVLBST_H
#define DEBUG

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{
}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertHelper(Node<Key,Value>* curr, AVLNode<Key,Value>*& newNode, const std::pair<const Key, Value>& keyValuePair);
    bool removeHelper(AVLNode<Key,Value>* toRem);
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, int diff);
    void checkBalance(AVLNode<Key,Value>* child) const;
    void rotateRight(AVLNode<Key,Value>* origParent);
    void rotateLeft(AVLNode<Key,Value>* origParent);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

template<class Key, class Value>
void AVLTree<Key, Value>::insertHelper(Node<Key,Value>* curr, AVLNode<Key,Value>*& newNode, const std::pair<const Key, Value>& keyValuePair)
{ 
    AVLNode<Key,Value>* current = static_cast<AVLNode<Key, Value>*>(curr);
    if (current->getKey() == keyValuePair.first){
        //overwrite value
        current->setValue(keyValuePair.second);
        newNode = current;
    }
    else if (keyValuePair.first < current->getKey()){
        if (current->getLeft() == NULL){
            newNode = new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second, current);
            //set new node to left
            current->setLeft(newNode);
            cout << newNode->getKey() << endl;
            cout << newNode->getParent()->getKey() << endl;
            cout << newNode->getParent()->getLeft()->getKey() << endl;
        }
        else {
            insertHelper(current->getLeft(), newNode, keyValuePair);
        }
    }
    else {
        if (current->getRight() == NULL){
            //set new node to right
            AVLNode<Key,Value>* temp = new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second, current);
            current->setRight(temp);
            newNode = temp;
        }
        else {
            insertHelper(current->getRight(), newNode, keyValuePair);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    cout << "INSERTING " << new_item.first << endl;
    if (BinarySearchTree<Key,Value>::root_ == NULL){
        AVLNode<Key,Value>* avlroot_ = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
        avlroot_->setBalance(0);
        BinarySearchTree<Key,Value>::root_ = avlroot_;
    }
    else {
        AVLNode<Key,Value>* newNode = NULL;
        cout << "TESTING INSERT" << endl;
        //BinarySearchTree<Key,Value>::printRoot(BinarySearchTree<Key,Value>::root_);
        cout << "AFTER INSERT" << endl;
        insertHelper(BinarySearchTree<Key,Value>::root_, newNode, new_item);
        newNode->setBalance(0);
        //BinarySearchTree<Key,Value>::printRoot(BinarySearchTree<Key,Value>::root_);
        AVLNode<Key,Value>* nodeParent = newNode->getParent();
        //Update temp's balance
        //If left child... 
        if (!nodeParent) {
            return;
        }
        else if (nodeParent->getLeft() == newNode){
            nodeParent->updateBalance(-1);
        }
        //If right child...
        else {
            nodeParent->updateBalance(1);
        }


        #ifdef DEBUG
        cout << endl;
        cout << "BEFORE INSERT FIX: " << endl;
        BinarySearchTree<Key,Value>::printRoot(BinarySearchTree<Key,Value>::root_);
        #endif
        insertFix(nodeParent, newNode);
        #ifdef DEBUG
        cout << endl;
        cout << "AFTER INSERT FIX: " << endl;
        BinarySearchTree<Key,Value>::printRoot(BinarySearchTree<Key,Value>::root_);
        #endif
        #ifdef DEBUG
        cout << "grandparent: ";
        if (nodeParent->getParent()) {checkBalance(nodeParent->getParent());}
        else { cout << "no grandparent" << endl;}
        cout << "parent: ";
        checkBalance(nodeParent);
        cout << "node: ";
        checkBalance(newNode);
        cout << endl;
        cout << "AFTER UPDATE----------" << endl;
        if (nodeParent->getParent()) {
            AVLNode<Key,Value>* gg = nodeParent->getParent();
            checkBalance(gg);
            if (gg->getParent()) {cout << "parent: " << gg->getParent()->getKey() << endl;}
            if (gg->getLeft()){cout << "left: " << gg->getLeft()->getKey() << endl;
                cout << "   parent: " << gg->getLeft()->getParent()->getKey() << endl;}
            if (gg->getRight()){
                cout << "right: " << gg->getRight()->getKey() << endl;
                AVLNode<Key,Value>* r = gg->getRight();
                cout << "   parent: " << r->getParent()->getKey() << endl;
                if (r->getLeft()) {
                    cout << "    left: " << r->getLeft()->getKey() << endl;
                    cout << "       parent: " << r->getLeft()->getParent()->getKey() << endl; 
                    if (r->getLeft()->getLeft()) {cout << "         left: " << r->getLeft()->getLeft()->getKey() << endl;}
                    if (r->getLeft()->getRight()) {cout << "        right: " << r->getLeft()->getRight()->getKey() << endl;}
                }
                if (r->getRight()) {
                    cout << "    right: " << r->getRight()->getKey() << endl;
                    cout << "       parent: " << r->getRight()->getParent()->getKey() << endl;
                    if (r->getRight()->getLeft()) {cout << "         left: " << r->getRight()->getLeft()->getKey() << endl;}
                    if (r->getRight()->getRight()) {cout << "        right: " << r->getRight()->getRight()->getKey() << endl;}
                }
            }
        }
        checkBalance(nodeParent);
        if (nodeParent->getParent()) {cout << "parent: " << nodeParent->getParent()->getKey() << endl;}
        if (nodeParent->getLeft()){
            cout << "left: " << nodeParent->getLeft()->getKey() << endl;
            cout << "   parent: " << nodeParent->getLeft()->getParent()->getKey() << endl;
        }
        if (nodeParent->getRight()){
            cout << "right: " << nodeParent->getRight()->getKey() << endl;
            cout << "   parent: " << nodeParent->getRight()->getParent()->getKey() << endl;
        }
        checkBalance(newNode);
        if (newNode->getLeft()){
            cout << "left: " << newNode->getLeft()->getKey() << endl;
            cout << "   parent: " << newNode->getLeft()->getParent()->getKey() << endl;
        }
        if (newNode->getRight()){
            cout << "right: " << newNode->getRight()->getKey() << endl;
            cout << "   parent: " << newNode->getRight()->getParent()->getKey() << endl;
        }
        if (newNode->getParent()){
            cout << "parent: " << newNode->getParent()->getKey() << endl;
        }
        #endif 
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
    if (!p || !p->getParent()) {return;}
    AVLNode<Key,Value>* g = p->getParent();
    //Assume p is left child of g
    #ifdef DEBUG
    cout << endl;
    cout << "BEFORE UPDATE----------" << endl;
    if (g->getParent()) {
        AVLNode<Key,Value>* gg = g->getParent();
        checkBalance(gg);
        if (gg->getLeft()){cout << "left: " << gg->getLeft()->getKey() << endl;}
        if (gg->getRight()){cout << "right: " << gg->getRight()->getKey() << endl;}
    }
    checkBalance(g);
    if (g->getLeft()){cout << "left: " << g->getLeft()->getKey() << endl;}
    if (g->getRight()){cout << "right: " << g->getRight()->getKey() << endl;}
    checkBalance(p);
    if (p->getLeft()){cout << "left: " << p->getLeft()->getKey() << endl;}
    if (p->getRight()){cout << "right: " << p->getRight()->getKey() << endl;}
    #endif
    if (p == g->getLeft()){
        //b(g) += -1
        if (g) {g->updateBalance(-1);}
        //Case 1: b(g) == 0, return
        if (g->getBalance() == 0){
            return;
        }
        //Case 2: b(g) == -1, insertFix(g,p)
        else if (g->getBalance() == -1){
            insertFix(g, p);
        }
        //Case 3: b(g) == -2
        else if (g->getBalance() == -2){
            //identify zig-zig/zig zag, rotate
            //Zig zig
            if (n == p->getLeft()){
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            //Zig zag
            else if (n == p->getRight()){
                rotateLeft(p);
                rotateRight(g);
                if (n->getBalance() == -1){
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);                    
                }
                else if (n->getBalance() == 1){
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);                    
                }
            }
        }
    }
    //Assume p is a right child of g
    else if (p == g->getRight()){
        if (g) {g->updateBalance(1);}
        //cout << "after update" << endl;
        //checkBalance(g);
        if (g->getBalance() == 0){
            return;
        }
        else if (g->getBalance() == 1){
            insertFix(g, p);
        }
        else if (g->getBalance() == 2){
            //identify zig-zig/zig zag, rotate
            //Zig zig
            if (n == p->getRight()){
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            //Zig zag
            else if (n == p->getLeft()){
                rotateRight(p);
                rotateLeft(g);
                if (n->getBalance() == 1){
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);                    
                }
                else if (n->getBalance() == -1){
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);                    
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* origParent){
    //cout << "Rotate Left " << origParent->getKey() << endl;
    if (origParent->getRight() == NULL || origParent == NULL){ return; }
    //cout << "Successful Rotation" << endl;
    AVLNode<Key,Value>* grand = origParent->getParent();
    AVLNode<Key,Value>* rightChild = origParent->getRight();
    AVLNode<Key,Value>* temp = rightChild->getLeft();

    //If x has a right subtree, assign y as the parent of the right subtree of x
    origParent->setRight(temp);
    if (temp) {temp->setParent(origParent);}

    //If the parent of y is NULL, make x as the root of the tree
    if (grand == NULL){
        BinarySearchTree<Key,Value>::root_ = rightChild;
    }
    //Else if y is the right child of its parent p, make x as the right child of p
    else if (grand->getLeft() == origParent){
        grand->setLeft(rightChild);
    }
    //Else assign x as the left child of p
    else {
        grand->setRight(rightChild);
    }
    rightChild->setParent(grand);

    //Make x as the parent of y
    if (origParent->getKey() < rightChild->getKey()){
        //cout << "first" << endl;
        rightChild->setLeft(origParent);
        origParent->setParent(rightChild);
    }
    else {
        //cout << "second" << endl;
        rightChild->setRight(origParent);
        origParent->setParent(rightChild);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* origParent){
    //cout << "Rotate Right " << origParent->getKey() << endl;
    if (origParent->getLeft() == NULL || origParent == NULL){ return; }
    //cout << "Successful Rotation" << endl;
    AVLNode<Key,Value>* grand = origParent->getParent();
    AVLNode<Key,Value>* leftChild = origParent->getLeft();
    AVLNode<Key,Value>* temp = leftChild->getRight();

    //If x has a right subtree, assign y as the parent of the right subtree of x
    origParent->setLeft(temp);
    if (temp) {temp->setParent(origParent);}

    //If the parent of y is NULL, make x as the root of the tree
    if (grand == NULL){
        BinarySearchTree<Key,Value>::root_ = leftChild;
    }
    //Else if y is the right child of its parent p, make x as the right child of p
    else if (grand->getRight() == origParent){
        grand->setRight(leftChild);
    }
    //Else assign x as the left child of p
    else {
        grand->setLeft(leftChild);
    }
    leftChild->setParent(grand);

    //Make x as the parent of y
    if (origParent->getKey() < leftChild->getKey()){
        leftChild->setLeft(origParent);
        origParent->setParent(leftChild);
    }
    else {
        leftChild->setRight(origParent);
        origParent->setParent(leftChild);
    }

    
}

template<class Key, class Value>
void AVLTree<Key, Value>::checkBalance(AVLNode<Key,Value>* child) const{
    cout << child->getKey() << "'s balance = ";
    if (child->getBalance() == 1){
        cout << 1 << endl;
    }
    else if (child->getBalance() == -1){
        cout << -1 << endl;
    }
    else if (child->getBalance() == 0){
        cout << 0 << endl;
    }
    else if (child->getBalance() == 2){
        cout << 2 << endl;
    }
    else if (child->getBalance() == -2){
        cout << -2 << endl;
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<typename Key, typename Value>
bool AVLTree<Key, Value>::removeHelper(AVLNode<Key,Value>* toRem){
        //Check if both children
        if (toRem->getLeft() != NULL && toRem->getRight() != NULL) {
            return false;
        }
        //Check if left child
        else if (toRem->getLeft() != NULL){
            AVLNode<Key,Value>* child = toRem->getLeft();
            //Promote temp child
            nodeSwap(toRem, child);
            //Update root if needed
            if (child->getParent() == NULL){
                BinarySearchTree<Key,Value>::root_ = child;
            }
            //Set child's left child to temp's left child
            child->setLeft(toRem->getLeft());
            if (child->getLeft()){
                child->getLeft()->setParent(child);
            }
            //Set child's right child to temp's right child
            child->setRight(toRem->getRight());
            if (child->getRight()){
                child->getRight()->setParent(child);
            }
            //Delete temp
            delete toRem;
        }
        //Check if right child
        else if (toRem->getRight() != NULL){
            AVLNode<Key,Value>* child = toRem->getRight();
            //Promote temp child
            nodeSwap(toRem, child);
            //Update root if needed
            if (child->getParent() == NULL){
                BinarySearchTree<Key,Value>::root_ = child;
            }
            //Set child's left child to temp's left child
            child->setLeft(toRem->getLeft());
            if (child->getLeft()){
                child->getLeft()->setParent(child);
            }
            //Set child's right child to temp's right child
            child->setRight(toRem->getRight());
            if (child->getRight()){
                child->getRight()->setParent(child);
            }
            //Delete temp
            delete toRem;
        }
        //Check if no children
        else {
            //If node has no parent or children, simply delete node
            if (!toRem->getParent()){
                BinarySearchTree<Key,Value>::root_ = NULL;
                delete toRem;
            }
            //If node has a parent and is a left child...
            //Set parent's left child to NULL
            //Delete node
            else if (toRem == toRem->getParent()->getLeft()){
                toRem->getParent()->setLeft(NULL);
                delete toRem;
            }
            //If node has a parent and is a right child...
            //Set parent's right child to NULL
            //Delete node
            else {
                toRem->getParent()->setRight(NULL);
                delete toRem;
            }
        }      
        return true;
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    cout << "REMOVING " << key << endl;
    AVLNode<Key, Value>* n = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(key));
    if (n == NULL){
        return;
    }
    else {
        bool removed = removeHelper(n);
        if (removed){ return; }
        AVLNode<Key,Value>* p = n->getParent();
        int diff;
        if (p){
            if (n == p->getLeft()){
                diff = 1;
            }
            else if (n == p->getRight()){
                diff = -1;
            }
        }
        AVLNode<Key, Value>* toRem = n;
        AVLNode<Key,Value>* pred = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(toRem));
        nodeSwap(toRem, pred);
        if (pred->getParent() == NULL) { BinarySearchTree<Key,Value>::root_ = pred; }
        if (toRem->getLeft()){
            AVLNode<Key,Value>* child_ = toRem->getLeft();
            AVLNode<Key,Value>* parent_ = toRem->getParent();
            if (child_->getKey() < parent_->getKey()){
                parent_->setLeft(child_);
            }
            else {
                parent_->setRight(child_);
            }
            child_->setParent(parent_);
        }
        if (toRem->getParent()->getLeft() == toRem){
            toRem->getParent()->setLeft(NULL);
        }
        else if (toRem->getParent()->getRight() == toRem){
            toRem->getParent()->setRight(NULL);
        }
        delete toRem;
        removeFix(p,diff);
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key,Value>* n, int diff){
    //If n is null, return
    if (!n) {return;}
    //Compute next recursive call's arguments now before altering the tree
    AVLNode<Key,Value>* p = n->getParent();
    int ndiff;
    if (p){
        if (n == p->getLeft()){
            ndiff = 1;
        }
        else {
            ndiff = -1;
        }
    }

    if (diff == -1){
        //Case 1
        if (n->getBalance() + diff == -2){
            AVLNode<Key,Value>* c = n->getLeft();
            //Case 1a
            if (c->getBalance() == -1){
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p,ndiff);
            }
            //Case 1b
            else if (c->getBalance() == 0){
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
            }
            //Case 1c
            else if (c->getBalance() == 1){
                AVLNode<Key,Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if (g->getBalance() == 1){
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);  
                }
                else if (g->getBalance() == -1){
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);                   
                }
                removeFix(p,ndiff);
            }
        }
        //Case 2
        else if (n->getBalance() + diff == -1){
            n->setBalance(-1);
        }
        //Case 3
        else if (n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p,ndiff);
        }
    }
    else if (diff == 1){
        //Case 1
        if (n->getBalance() + diff == 2){
            AVLNode<Key,Value>* c = n->getRight();
            //Case 1a
            if (c->getBalance() == 1){
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p,ndiff);
            }
            //Case 1b
            else if (c->getBalance() == 0){
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
            }
            //Case 1c
            else if (c->getBalance() == -1){
                AVLNode<Key,Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                if (g->getBalance() == -1){
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);  
                }
                else if (g->getBalance() == 1){
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);                   
                }
                removeFix(p,ndiff);
            }
        }
        //Case 2
        else if (n->getBalance() + diff == 1){
            n->setBalance(1);
        }
        //Case 3
        else if (n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p,ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
