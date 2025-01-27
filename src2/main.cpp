#include "../include/bTree.h"
#include <iostream>
#include "../include/product.h"

//Tem que executar com: g++ -o main main.cpp bTree.cpp product.cpp -I../include
// .\main
int main() {
    std::vector<Product> produtos = Product::importProducts("assets/dadosB.txt");
    if (produtos.empty()) {
        std::cerr << "Nenhum produto foi carregado do arquivo." << std::endl;
        return 1; 
    }

    BTree btree(2);

    for (const auto &p : produtos) {
        btree.insert(p);
    }

    std::cout << "=== Árvore B após inserções ===" << std::endl;
    btree.traverse();

    int idRemocao = 115; 
    std::cout << "\nRemovendo o produto de ID " << idRemocao << "..." << std::endl;
    btree.remove(idRemocao);

    std::cout << "\n=== Árvore B após remoção do ID " << idRemocao << " ===" << std::endl;
    btree.traverse();

    return 0;
}
