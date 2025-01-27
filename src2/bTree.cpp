#include "../include/btree.h"
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
        // Árvore vazia: cria nó-folha
        root = new TreeNode(t, true);
        root->keys[0] = p;
        root->n = 1;
    } 
    else {
        // Se nó raiz está cheio, split antes de inserir
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
        std::cout << "Árvore B vazia!\n";
        return;
    }
    root->deletion(k);

    // Se a raiz ficar sem chaves, ajusta
    if (root->n == 0) {
        TreeNode *tmp = root;
        // Se não é folha, faz o primeiro filho ser a nova raiz
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

    // A quantidade máxima de chaves é 2*t - 1
    keys.resize(2 * t - 1);
    C = new TreeNode*[2 * t];
    n = 0;
}

// Percorre a árvore por nível
void TreeNode::traverse() {
    // Usando uma fila para percorrer a árvore por nível
    std::queue<TreeNode *> q;
    q.push(this);

    int level = 1; // Variável para acompanhar o nível da árvore

    while (!q.empty()) {
        int size = q.size(); // Número de elementos no nível atual
        std::cout << "Nível " << level << ": ";

        // Processando todos os nós no nível atual
        for (int i = 0; i < size; i++) {
            TreeNode *current = q.front();
            q.pop();

            // Imprime as chaves do nó
            for (int j = 0; j < current->n; j++) {
                std::cout << "[" << current->getKey(j).toStringComplete() << "] ";
            }

            // Se o nó não for folha, adiciona seus filhos à fila
            if (!current->leaf) {
                for (int j = 0; j <= current->n; j++) {
                    q.push(current->C[j]);
                }
            }
        }

        std::cout << std::endl;
        level++; // Incrementa o nível a cada iteração
    }
}

// Busca por ID dentro deste nó ou recursivamente
TreeNode* TreeNode::search(int id) {
    // Acha a primeira chave >= id
    int i = 0;
    while (i < n && id > keys[i].getId())
        i++;

    // Se a chave encontrada for igual, retorna esse nó
    if (i < n && keys[i].getId() == id)
        return this;

    // Se é folha e não encontrou, retorna nullptr
    if (leaf)
        return nullptr;

    // Desce para o filho apropriado
    return C[i]->search(id);
}

// Insere uma chave em um nó não-cheio
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

// Faz split do filho C[i] quando está cheio
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

// Arrumei na net pq precisava para fazer a remoção
int TreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx].getId() < k)
        idx++;
    return idx;
}

// Remove a chave com ID == k na subárvore enraizada neste nó
void TreeNode::deletion(int k) {
    int idx = findKey(k);

    // Se a chave está neste nó
    if (idx < n && keys[idx].getId() == k) {
        if (leaf) {
            // Remove chave de nó-folha
            removeFromLeaf(idx);
        } 
        else {
            removeFromNonLeaf(idx);
        }
    } 
    else {
        // Se é folha e não encontrou, não existe
        if (leaf) {
            std::cout << "A chave " << k << " não existe na árvore.\n";
            return;
        }
        // Decidir qual filho seguir
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

    // Se o filho da esquerda tem >= t chaves
    if (C[idx]->n >= t) {
        Product pred = getPredecessor(idx);
        keys[idx] = pred;
        C[idx]->deletion(pred.getId());
    }
    // Senão, se o filho da direita tem >= t chaves
    else if (C[idx + 1]->n >= t) {
        Product succ = getSuccessor(idx);
        keys[idx] = succ;
        C[idx + 1]->deletion(succ.getId());
    }
    // Caso contrário, mescla os dois filhos
    else {
        merge(idx);
        C[idx]->deletion(p.getId());
    }
}

Product TreeNode::getPredecessor(int idx) {
    // Desce no filho da esquerda até chegar em um nó folha
    TreeNode *cur = C[idx];
    while (!cur->leaf) {
        cur = cur->C[cur->n];
    }
    return cur->keys[cur->n - 1];
}

Product TreeNode::getSuccessor(int idx) {
    // Desce no filho da direita até chegar em um nó folha
    TreeNode *cur = C[idx + 1];
    while (!cur->leaf) {
        cur = cur->C[0];
    }
    return cur->keys[0];
}

void TreeNode::fill(int idx) {
    // Se o filho anterior tem >= t chaves, pega emprestado dele
    if (idx != 0 && C[idx - 1]->n >= t) {
        borrowFromPrev(idx);
    }
    // Senão, se o filho seguinte tem >= t chaves, pega emprestado dele
    else if (idx != n && C[idx + 1]->n >= t) {
        borrowFromNext(idx);
    }
    // Senão mescla com um irmão
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

    // Desloca todas as chaves de 'child' para a direita
    for (int i = child->n - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i) {
            child->C[i + 1] = child->C[i];
        }
    }

    // Sobe a chave do nó atual para child
    child->keys[0] = keys[idx - 1];

    if (!child->leaf) {
        child->C[0] = sibling->C[sibling->n];
    }

    // Desce a última chave do irmão para o nó atual
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

    // Sobe a chave do nó atual para o meio de child
    child->keys[t - 1] = keys[idx];

    // Copia as chaves de sibling para child
    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
    }

    // Copia os filhos se não for folha
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->C[i + t] = sibling->C[i];
        }
    }

    // Move as chaves do nó atual para preencher o buraco
    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
    }
    // Move os ponteiros de filhos
    for (int i = idx + 2; i <= n; ++i) {
        C[i - 1] = C[i];
    }

    child->n += sibling->n + 1;
    n--;

    delete sibling;
}
