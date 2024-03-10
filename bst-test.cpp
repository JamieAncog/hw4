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
    BinarySearchTree<int,int> bst;
    bst.insert(std::make_pair(15,4));
    bst.insert(std::make_pair(-41,4));
    bst.insert(std::make_pair(-32,99));
    bst.insert(std::make_pair(-39,49));
    bst.insert(std::make_pair(73,24));
    bst.insert(std::make_pair(138,34));
    bst.insert(std::make_pair(-117,6));
    bst.insert(std::make_pair(147,4));
    bst.insert(std::make_pair(-1,80));
    bst.insert(std::make_pair(65,90));
    bst.insert(std::make_pair(5,23));
    bst.insert(std::make_pair(31,4));
    bst.insert(std::make_pair(-72,4));
    bst.insert(std::make_pair(-50,4));
    bst.insert(std::make_pair(49,4));
    bst.insert(std::make_pair(35,4));
    bst.insert(std::make_pair(79,4));
    bst.insert(std::make_pair(-60,4));
    bst.insert(std::make_pair(105,4));
    bst.insert(std::make_pair(-149,4));
    bst.insert(std::make_pair(-67,4));
    bst.insert(std::make_pair(-68,4));
    bst.insert(std::make_pair(134,4));
    bst.insert(std::make_pair(119,4));
    bst.insert(std::make_pair(58,4));
    bst.insert(std::make_pair(121,4));
    bst.insert(std::make_pair(-22,4));
    bst.insert(std::make_pair(46,4));
    bst.insert(std::make_pair(36,4));
    bst.insert(std::make_pair(-123,4));
    bst.print();
    bst.remove(-50);
    bst.remove(147);
    bst.remove(105);
    bst.remove(-149);
    bst.remove(31);
    bst.remove(-123);
    bst.remove(-60);
    bst.remove(65);
    bst.remove(46);
    bst.remove(134);
    bst.remove(138);
    bst.remove(-67);
    bst.remove(121);
    bst.remove(15);
    bst.remove(36);
    bst.remove(79);
    bst.remove(-39);
    bst.remove(-41);
    bst.remove(49);
    bst.remove(-68);
    bst.remove(-117);
    bst.remove(73);
    bst.remove(58);
    bst.remove(35);
    bst.remove(5);
    bst.print();

    return 0;
}
