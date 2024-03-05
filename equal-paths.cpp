#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool isLeaf(Node* node);

bool equalPaths(Node * root)
{
    // Add your code below
    if (root == NULL){
        return true;
    }
    else if (root->left == NULL && root->right == NULL){
        return true;
    }
    else if (root->left == NULL) {
        equalPaths(root->right);
    }
    else if (root->right == NULL){
        equalPaths(root->left);
    }
    else if (isLeaf(root->left) && isLeaf(root->right)){
        return true;
    }
    else if (isLeaf(root->left) || isLeaf(root->right)){
        return false;
    }
    else if (isLeaf(root->left->left) && isLeaf(root->left->left) && !isLeaf(root->right->left) && !isLeaf(root->right->right)){
        return false;
    }
    else if (!isLeaf(root->left->left) && !isLeaf(root->left->left) && isLeaf(root->right->left) && isLeaf(root->right->right)){
        return false;
    }
    else {
        equalPaths(root->left);
        equalPaths(root->right);
    }
    return true;

}

bool isLeaf(Node* node){
    if (node == NULL){
        return true;
    }
    else if (node->left == NULL && node->right == NULL){
        return true;
    }
    else { 
        return false; 
    }
}


