#include <iostream>
#include "BST.hpp"
int main() {
    std::cout << "Hello, World!" << std::endl;
    BST<int> tree;
    tree.insert(3);
    tree.insert(9);
    tree.insert(12);
    tree.insert(12);
    tree.insert(13);
    tree.remove(13);
    BST<int> tree2(tree);
    tree.printInorder();

    return 0;
}