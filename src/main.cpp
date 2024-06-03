#include <iostream>
#include "headers/Tree_B.hpp"
#include <time.h>
int main() {
    Tree_B<int, 6> tree;
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 1" << std::endl;
    // tree.insert(1);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 7" << std::endl;
    // tree.insert(7);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 2" << std::endl;
    // tree.insert(2);
    // tree.print();
    // std::cout <<  "----------------" << std::endl;
    // std::cout << "Inserting 3" << std::endl;
    // tree.insert(3);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 0" << std::endl;
    //  tree.insert(0);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 7" << std::endl;
    // tree.insert(7);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 8" << std::endl;
    // tree.insert(8);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 1" << std::endl;
    // tree.insert(1);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 0" << std::endl;
    // tree.insert(0);
    // tree.print();
    // std::cout << "----------------" << std::endl;

    // for(int i = 0; i < 3; ++i){
    //     std::cout << "----------------" << std::endl;
    //     std::cout << "Inserting " << i + 1 << std::endl;
    //     tree.insert(i+1);
    //     tree.print();
    // }
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 5" << std::endl;
    //  tree.insert(5);
    // tree.print();
    // for(int i = 9; i < 13; ++i){
    //     std::cout << "----------------" << std::endl;
    //     std::cout << "Inserting " << i << std::endl;
    //     tree.insert(i);
    //     tree.print();
    // } 
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 14" << std::endl;
    // tree.insert(14);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 6" << std::endl;
    // tree.insert(6);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 8" << std::endl;
    // tree.insert(8);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 7" << std::endl;
    // tree.insert(7);
    // tree.print();
    // // std::cout << "----------------" << std::endl;
    // // std::cout << "Inserting 4" << std::endl;
    // // tree.insert(4);
    // // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 10" << std::endl;
    // tree.insert(10);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 11" << std::endl;
    // tree.insert(11);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 12" << std::endl;
    // tree.insert(12);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 13" << std::endl;
    // tree.insert(13);
    // tree.print();
    // std::cout << "----------------" << std::endl;
    // std::cout << "Inserting 15" << std::endl;
    // tree.insert(15);
    // tree.print();

    // srand(time(NULL));
    // int aux = 0;
    // for(int i = 0; aux != -4; ++i){
    //     std::cout << "----------------" << std::endl;
    //     std::cout << "Dame un numero " << std::endl;
    //     std::cin >> aux;
    //     std::cout << "----------------" << std::endl;
    //     std::cout << "Insertando " << aux << std::endl;
    //     tree.insert(aux);
    //     tree.print();        
    // }
    
    srand(time(NULL));
    int aux = 0;
    for(int i = 0; i < 20; ++i){
        aux = rand() % 100;
        std::cout << "----------------" << std::endl;
        std::cout << "Insertando " << aux << std::endl;
        tree.insert(aux);
        tree.print();
        
    }
    std::cout << "Terminado" << std::endl; 
    return 0; 
}
