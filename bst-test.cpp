#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include "bst.h"
#include "avlbst.h"

using namespace std;


/*int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    return 0;
}
*/

void testRemove(int num){
    cout << "REMOVING KEY: " << num << endl;
    AVLTree<int,int> bst3;
    bst3.insert(std::make_pair(1,4));
    bst3.insert(std::make_pair(3,4));
    bst3.insert(std::make_pair(9,4));
    bst3.insert(std::make_pair(11,4));
    bst3.insert(std::make_pair(32,4));
    bst3.insert(std::make_pair(99,4));
    bst3.insert(std::make_pair(105,4));
    bst3.insert(std::make_pair(300,4));
    bst3.insert(std::make_pair(900,4));
    bst3.remove(num);
    if (bst3.isBalanced()){
        cout << "Success!!!" << endl;
    }
    else {
        cout << "Not Balanced" << endl;
    }
    cout << endl;
}


int main(int argc, char *argv[])
{
    // AVL Tree tests
    AVLTree<int,int> at;
    int dat[] = {-53, -144, -22, 56, -147, 75, -128, 123, -89, -117, 50, 2, 114, 21, 147, 45, 16, 28, -64, -77,-73, 71, 105, 144, -20,41, -61, 106, -96, -142};
    for (int i = 0; i < 30; i++){
        at.insert(std::make_pair(dat[i],4));
        if (at.isBalanced()){
            cout <<"is Balanced" << endl;
        }
        else {
            cout <<"is not Balanced" << endl;
        }
    }
    /*
    int rem[] = {-53, 2, 45};
    //{-20, -96,-89,16,56};
    for (int i = 0; i < 3; i++){
        at.remove(rem[i]);
        bool isB = at.isBalanced();
        if (isB){
            cout << rem[i] << " is Balanced" << endl;
        }
        else {
            cout << rem[i] << " is not Balanced" << endl;
        }
    }
    */
    

    return 0;
}
