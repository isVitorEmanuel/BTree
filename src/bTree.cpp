#include <queue>
#include <iostream>
#include "../include/product.h"

using namespace std;

class TreeNode {
    vector<Product> keys;
    int t;
    TreeNode **C;
    int n;
    bool leaf;

public:
    TreeNode(int temp, bool leaf1);

    const Product& getKey(int index) const {
        return keys[index];
    }

    void insertNonFull(const Product& p);
    void splitChild(int i, TreeNode *y);
    void traverse();

    TreeNode *search(int id);

    friend class BTree;
};

class BTree {
    TreeNode *root;
    int t;

public:
    BTree(int temp) {
        root = NULL;
        t = temp;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }

    TreeNode *search(int k) {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(const Product& p);
};

TreeNode::TreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys.resize(2 * t - 1);
    C = new TreeNode *[2 * t];

    n = 0;
}

void TreeNode::traverse() {
    // Usando uma fila para percorrer a árvore por nível
    queue<TreeNode*> q;
    q.push(this);

    int level = 1; // Variável para acompanhar o nível da árvore

    while (!q.empty()) {
        int size = q.size();  // Número de elementos no nível atual
        cout << "Nível " << level << ": ";

        // Processando todos os nós no nível atual
        for (int i = 0; i < size; i++) {
            TreeNode* current = q.front();
            q.pop();

            // Imprime as chaves do nó
            for (int j = 0; j < current->n; j++) {
                cout << "[" << current->getKey(j).toStringComplete() << "] ";
            }

            // Se o nó não for folha, adiciona seus filhos à fila
            if (!current->leaf) {
                for (int j = 0; j <= current->n; j++) {
                    q.push(current->C[j]);
                }
            }
        }

        cout << endl;
        level++; // Incrementa o nível a cada iteração
    }
}

// Adicionando a lógica de inserção (não alterada)
void BTree::insert(const Product& p) {
    if (root == NULL) {
        root = new TreeNode(t, true);
        root->keys[0] = p;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            TreeNode *s = new TreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0].getId() < p.getId())
                i++;
            s->C[i]->insertNonFull(p);

            root = s;
        } else {
            root->insertNonFull(p);
        }
    }
}

void TreeNode::insertNonFull(const Product& p) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i].getId() > p.getId()) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = p;
        n++;
    } else {
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

TreeNode* TreeNode::search(int id){
    int i=0;

    //Procura o primeiro valor maior ou igual a id
    while (i < n && keys[i].getId() < id) {
        i++;
    }
    // Se o valor é igual ao id, retorna o nó 
    if (i < n && keys[i].getId() == id) {
        return this;
    }
    // Se o valor não foi achado e é uma folha
    if(leaf){
        return NULL;
    }
    //Vai para o nó apropriado
    return C[i]->search(id);
    

}


int main() {
    BTree t(2);
    t.insert(Product(50, "Product A", 10));
    t.insert(Product(116, "Product B", 20));
    t.insert(Product(150, "Product C", 30));
    t.insert(Product(203, "Product D", 40));
    t.insert(Product(60, "Product E", 5));
    t.insert(Product(180, "Product F", 15));
    t.insert(Product(115, "Product F", 15));
    t.insert(Product(117, "Product F", 15));
    t.insert(Product(111, "Product F", 15));
    t.insert(Product(12, "Product F", 15));
    t.insert(Product(2, "Product F", 15));
    t.insert(Product(32, "Product F", 15));
    t.insert(Product(41, "Product F", 15));
    t.insert(Product(18, "Product F", 15));
    t.insert(Product(11, "Product F", 15));
    t.insert(Product(1, "Product F", 15));
    t.insert(Product(3, "Product F", 15));
    t.insert(Product(5, "Product F", 15));
    t.insert(Product(110, "Product F", 15));
    t.insert(Product(6, "Product F", 15));
    t.insert(Product(7, "Product F", 15));
    t.insert(Product(8, "Product F", 15));
    t.insert(Product(9, "Product F", 15));
    t.insert(Product(12, "Product F", 15));
    t.insert(Product(19, "Product F", 15));
    t.insert(Product(21, "Product F", 15));

    cout << "A árvore B é: " << endl;
    t.traverse();  // Imprimindo por nível

    return 0;
}
