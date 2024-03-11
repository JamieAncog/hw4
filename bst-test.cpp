#include <iostream>
#include <map>
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
    BinarySearchTree<int,int> bst2;
    bst2.insert(std::make_pair(7,4));
    bst2.insert(std::make_pair(9,4));
    bst2.insert(std::make_pair(15,4));
    bst2.insert(std::make_pair(2,4));
    bst2.insert(std::make_pair(1,4));
    bst2.insert(std::make_pair(3,4));
    bst2.remove(num);
    bst2.print();
    cout << endl;
}

int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    AVLTree<int,int> bst2;
    bst2.insert(std::make_pair(17,4));
    bst2.insert(std::make_pair(16,4));
    bst2.insert(std::make_pair(12,4));
    cout << "AFTER INSERT-FIX" << endl;
    bst2.print();
    bst2.insert(std::make_pair(10,4));
    cout << "AFTER INSERT-FIX" << endl;
    bst2.print();
    bst2.insert(std::make_pair(9,4));
    cout << "AFTER INSERT-FIX" << endl;
    bst2.print();
    bst2.insert(std::make_pair(6,4));
    cout << "AFTER INSERT-FIX" << endl;
    bst2.print();
    //bst2.insert(std::make_pair(5,4));
    //cout << "AFTER INSERT-FIX" << endl;
    //bst2.print();
    //bst2.insert(std::make_pair(3,4));
    //cout << "AFTER INSERT-FIX" << endl;
    //bst2.print();
    //bst2.insert(std::make_pair(2,4));
    //cout << "AFTER INSERT-FIX" << endl;
    //bst2.print();

    /*AVLTree<int,int> bst3;
    bst3.insert(std::make_pair(1,4));
    bst3.insert(std::make_pair(3,4));
    bst3.insert(std::make_pair(9,4));
    bst3.insert(std::make_pair(11,4));
    bst3.insert(std::make_pair(32,4));
    bst3.insert(std::make_pair(99,4));
    bst3.insert(std::make_pair(105,4));
    bst3.insert(std::make_pair(300,4));
    bst3.insert(std::make_pair(900,4));
    bst3.print();
    */

    return 0;
}
