#ifndef BTREE_H
#define BTREE_H

#include "product.h"
#include <iostream>
#include <vector>
#include <queue>

class TreeNode;

class BTree {
private:
    TreeNode *root;
    int t;

public:
    BTree(int temp);

    void traverse();
    TreeNode* search(int k);
    void insert(const Product &p);
    void remove(int k);
};

class TreeNode {
private:
    std::vector<Product> keys;
    TreeNode **C;
    int n;
    bool leaf;
    int t;
public:
    TreeNode(int t1, bool leaf1);

    const Product& getKey(int index) const {
        return keys[index];
    }

    void insertNonFull(const Product &p);
    void splitChild(int i, TreeNode *y);
    void traverse();
    TreeNode* search(int id);
    void deletion(int k);

private:
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
