#include <iostream>
#include "headers/Tree_B.hpp"

int main() {
    Tree_B<int, 4> tree;
    tree.insert(1);
    tree.insert(7);
    tree.insert(2);
    tree.insert(3);
    tree.print();
    std::cout << "----------------" << std::endl;
    std::cout << "Inserting 0" << std::endl;
    tree.insert(0);
    tree.print();
    std::cout << "----------------" << std::endl;
    std::cout << "Inserting 7" << std::endl;
    tree.insert(7);
    tree.print();
    std::cout << "----------------" << std::endl;
    std::cout << "Inserting 2" << std::endl;
    tree.insert(2);
    tree.print();
    std::cout << "----------------" << std::endl;
    std::cout << "Inserting 3" << std::endl;
    tree.insert(3);
    tree.print();
    std::cout << "----------------" << std::endl;
    std::cout << "Inserting 0" << std::endl;
    tree.insert(0);
    tree.print();
    std::cout << "----------------" << std::endl;
    return 0; 
}
