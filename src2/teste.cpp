#include "../include/bTree.h"
#include <iostream>

// executar com g++ -o btree_test a.cpp btree.cpp product.cpp
// .\btree_test
int main() {
    BTree tree(2);

    Product p1(1, "Produto A", 10.0);
    Product p2(2, "Produto B", 20.0);
    Product p3(3, "Produto C", 15.0);
    Product p4(4, "Produto D", 25.0);
    Product p5(5, "Produto E", 30.0);

    tree.insert(p1);
    tree.insert(p2);
    tree.insert(p3);
    tree.insert(p4);
    tree.insert(p5);

    std::cout << "\nTravessia da B-Tree: \n";
    tree.traverse();

    std::cout << "\n\nBusca pelo ID 3: \n";
    TreeNode *result = tree.search(3);
    if (result != nullptr) {
        std::cout << "Produto encontrado: " << result->getKey(0).getName() << "\n";
    } else {
        std::cout << "Produto nao encontrado!\n";
    }

    std::cout << "\nBusca pelo ID 6: \n";
    result = tree.search(6);
    if (result != nullptr) {
        std::cout << "Produto encontrado: " << result->getKey(0).getName() << "\n";
    } else {
        std::cout << "Produto nao encontrado!\n";
    }

    std::cout << "\nRemovendo o produto com ID 3.\n";
    tree.remove(3);
    std::cout << "Travessia apos remocao: \n";
    tree.traverse(); 

    return 0;
}
