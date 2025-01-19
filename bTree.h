#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <iostream>
#include "product.h"

using namespace std;

class BTree {
private:
    struct Node {
        bool isLeaf;
        Product product;
        vector<Node*> children;

        Node(bool isLeaf, Product product);
    };

    Node* root;
    int t; 

public:
    BTree(int t);
    void insert(Product& product);
    Node* search(int id);
    void remove(int id);
    void view();
};

#endif
