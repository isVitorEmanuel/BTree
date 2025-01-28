#include "../include/bTree.h"
#include "../include/product.h"
#include <iostream>
#include <queue>

BTree::BTree(int temp) {
    root = nullptr;
    t = temp;
}

void BTree::traverse() {
    if (root != nullptr)
        root->traverse();
}

TreeNode* BTree::search(int k) {
    return (root == nullptr) ? nullptr : root->search(k);
}

void BTree::insert(const Product &p) {
    if (root == nullptr) {
        root = new TreeNode(t, true);
        root->keys[0] = p;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            TreeNode *s = new TreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0].getId() < p.getId())
                i++;
            s->C[i]->insertNonFull(p);

            root = s;
        }
        else {
            root->insertNonFull(p);
        }
    }
}

void BTree::remove(int k) {
    if (!root) {
        std::cout << "B-Tree is empty!\n";
        return;
    }
    root->deletion(k);

    if (root->n == 0) {
        TreeNode *tmp = root;

        if (!root->leaf) {
            root = root->C[0];
        } else {
            root = nullptr;
        }
        delete tmp;
    }
}

TreeNode::TreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys.resize(2 * t - 1);
    C = new TreeNode*[2 * t];
    n = 0;
}

void TreeNode::traverse() {
    std::queue<TreeNode *> q;
    q.push(this);

    int level = 1;

    while (!q.empty()) {
        int size = q.size();
        std::cout << "Level " << level << ": ";

        for (int i = 0; i < size; ++i) {
            TreeNode *current = q.front();
            q.pop();

            std::cout << "[";
            for (int j = 0; j < current->n; ++j) {
                if (j > 0) std::cout << ", ";
                std::cout << current->keys[j].getId();
            }
            std::cout << "] ";

            if (!current->leaf) {
                for (int j = 0; j <= current->n; ++j) {
                    q.push(current->C[j]);
                }
            }
        }

        std::cout << std::endl;
        ++level;
    }
}

TreeNode* TreeNode::search(int id){
    int i=0;

    while (i < n && keys[i].getId() < id) {
        i++;
    }
    if (i < n && keys[i].getId() == id) {
        std::cout << "Product: " << keys[i].toStringComplete() << std::endl;
        return this;
    }
    if (leaf){
        return NULL;
    }
    return C[i]->search(id);
}

void TreeNode::insertNonFull(const Product &p) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i].getId() > p.getId()) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = p;
        n++;
    }
    else {
        while (i >= 0 && keys[i].getId() > p.getId())
            i--;

        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1].getId() < p.getId())
                i++;
        }
        C[i + 1]->insertNonFull(p);
    }
}

void TreeNode::splitChild(int i, TreeNode *y) {
    TreeNode *z = new TreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
        }
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) {
        C[j + 1] = C[j];
    }

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }

    keys[i] = y->keys[t - 1];
    n++;
}

int TreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx].getId() < k)
        idx++;
    return idx;
}

void TreeNode::deletion(int k) {
    int idx = findKey(k);

    if (idx < n && keys[idx].getId() == k) {
        if (leaf) {
            removeFromLeaf(idx);
        }
        else {
            removeFromNonLeaf(idx);
        }
    }
    else {
        if (leaf) {
            std::cout << "The key " << k << " not exist in B-Tree.\n";
            return;
        }

        bool flag = ( (idx == n) ? true : false );

        if (C[idx]->n < t) {
            fill(idx);
        }

        if (flag && idx > n) {
            C[idx - 1]->deletion(k);
        } else {
            C[idx]->deletion(k);
        }
    }
}

void TreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    n--;
}

void TreeNode::removeFromNonLeaf(int idx) {
    Product p = keys[idx];

    if (C[idx]->n >= t) {
        Product pred = getPredecessor(idx);
        keys[idx] = pred;
        C[idx]->deletion(pred.getId());
    }
    else if (C[idx + 1]->n >= t) {
        Product succ = getSuccessor(idx);
        keys[idx] = succ;
        C[idx + 1]->deletion(succ.getId());
    }
    else {
        merge(idx);
        C[idx]->deletion(p.getId());
    }
}

Product TreeNode::getPredecessor(int idx) {
    TreeNode *cur = C[idx];
    while (!cur->leaf) {
        cur = cur->C[cur->n];
    }
    return cur->keys[cur->n - 1];
}

Product TreeNode::getSuccessor(int idx) {
    TreeNode *cur = C[idx + 1];
    while (!cur->leaf) {
        cur = cur->C[0];
    }
    return cur->keys[0];
}

void TreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t) {
        borrowFromPrev(idx);
    }
    else if (idx != n && C[idx + 1]->n >= t) {
        borrowFromNext(idx);
    }
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

void TreeNode::borrowFromPrev(int idx) {
    TreeNode *child = C[idx];
    TreeNode *sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i) {
            child->C[i + 1] = child->C[i];
        }
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf) {
        child->C[0] = sibling->C[sibling->n];
    }

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void TreeNode::borrowFromNext(int idx) {
    TreeNode *child = C[idx];
    TreeNode *sibling = C[idx + 1];

    child->keys[child->n] = keys[idx];

    if (!child->leaf) {
        child->C[child->n + 1] = sibling->C[0];
    }

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i) {
            sibling->C[i - 1] = sibling->C[i];
        }
    }

    child->n += 1;
    sibling->n -= 1;
}

void TreeNode::merge(int idx) {
    TreeNode *child = C[idx];
    TreeNode *sibling = C[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->C[i + t] = sibling->C[i];
        }
    }

    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
    }

    for (int i = idx + 2; i <= n; ++i) {
        C[i - 1] = C[i];
    }

    child->n += sibling->n + 1;
    n--;

    delete sibling;
}
