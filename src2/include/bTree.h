#ifndef BTREE_H
#define BTREE_H

#include "product.h"
#include <iostream>
#include <vector>
#include <queue>

class TreeNode;

// Classe principal da Árvore B
class BTree {
private:
    TreeNode *root;  // Ponteiro para o nó raiz
    int t;           // Fator mínimo (ordem) da B-Tree

public:
    // Construtor: recebe o fator mínimo (t)
    BTree(int temp);

    // Percorre a árvore por nível
    void traverse();

    // Procura produto cujo ID == k
    TreeNode* search(int k);

    // Insere um Product
    void insert(const Product &p);

    // Remove um Product pelo id (opcional)
    void remove(int k);
};

// Nó da B-Tree
class TreeNode {
private:
    std::vector<Product> keys; // Vetor de chaves (até 2*t - 1)
    TreeNode **C;              // Array de ponteiros para nós-filhos (até 2*t)
    int n;                     // Quantidade atual de chaves no nó
    bool leaf;                 // Se é nó-folha ou não
    int t;                     // Fator mínimo

public:
    // Construtor
    TreeNode(int t1, bool leaf1);

    // Retorna a chave de índice index
    const Product& getKey(int index) const {
        return keys[index];
    }

    void insertNonFull(const Product &p);
    void splitChild(int i, TreeNode *y);
    void traverse();

    // Busca
    TreeNode* search(int id);

    void deletion(int k);

private:
    // Funções auxiliares de remoção
    int findKey(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    Product getPredecessor(int idx);
    Product getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

#endif // BTREE_H
