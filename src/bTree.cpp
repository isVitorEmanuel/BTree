#include <vector>
#include <memory>
#include <variant>

template <typename T>
class BTreeNode {
public:
    // pode ser um valor ou pode ser um ponteiro prum filho. 
    // quem vai cuidar de alternar certinho pra ficar conforme o professor 
    // indicou vai ser qm implementar as funcoes. (deixei conforme ele sugeriu)
    using Element = std::variant<T, std::shared_ptr<BTreeNode>>;

    std::vector<Element> elements;
    bool isLeaf;                   

    BTreeNode(bool isLeaf) : isLeaf(isLeaf) {}
};

template <typename T>
class BTree {
public:
    std::shared_ptr<BTreeNode<T>> root; 

    BTree() : root(nullptr) {}
};

// um exemplo gerado pelo gpt (com erros) pra exemplificar uso:
// Definição da estrutura da árvore B
/*template <typename T>*/
/*class BTree {*/
/*public:*/
/*    std::shared_ptr<BTreeNode<T>> root; // Ponteiro para a raiz da árvore*/
/*    int order;                          // Ordem da árvore (d)*/
/**/
/*    BTree(int order) : root(nullptr), order(order) {}*/
/**/
/*    // Insere uma chave na árvore*/
/*    void insert(const T& key) {*/
/*        if (!root) {*/
/*            root = std::make_shared<BTreeNode<T>>(true); // Cria um nó raiz se não existir*/
/*            root->elements.push_back(key);*/
/*        } else {*/
/*            if (root->elements.size() == 2 * order) {*/
/*                auto newRoot = std::make_shared<BTreeNode<T>>(false); // Cria um novo nó raiz*/
/*                newRoot->elements.push_back(root); // O antigo root se torna o primeiro filho*/
/*                splitNode(newRoot, 0); // Divide o antigo root*/
/*                root = newRoot; // Atualiza a raiz*/
/*            }*/
/*            insertNonFull(root, key);*/
/*        }*/
/*    }*/
/**/
/*private:*/
/*    // Insere em um nó não cheio*/
/*    void insertNonFull(std::shared_ptr<BTreeNode<T>> node, const T& key) {*/
/*        if (node->isLeaf) {*/
/*            // Insere a chave no nó folha*/
/*            auto it = std::find_if(node->elements.begin(), node->elements.end(),*/
/*                [&](const auto& elem) {*/
/*                    return std::holds_alternative<T>(elem) && std::get<T>(elem) > key;*/
/*                });*/
/*            node->elements.insert(it, key);*/
/*        } else {*/
/*            // Encontra o filho apropriado*/
/*            int i = 0;*/
/*            while (i < node->elements.size() && (!std::holds_alternative<T>(node->elements[i]) || std::get<T>(node->elements[i]) < key)) {*/
/*                i++;*/
/*            }*/
/*            i = i / 2; // Converte índice de elemento para índice de filho*/
/**/
/*            auto childNode = std::get<std::shared_ptr<BTreeNode<T>>>(node->elements[2 * i + 1]);*/
/*            if (childNode->elements.size() == 2 * order) {*/
/*                splitNode(node, i);*/
/*                if (std::get<T>(node->elements[2 * i]) < key) {*/
/*                    i++;*/
/*                }*/
/*            }*/
/*            insertNonFull(std::get<std::shared_ptr<BTreeNode<T>>>(node->elements[2 * i + 1]), key);*/
/*        }*/
/*    }*/
/**/
/*    // Divide um nó cheio*/
/*    void splitNode(std::shared_ptr<BTreeNode<T>> parent, int i) {*/
/*        auto fullNode = std::get<std::shared_ptr<BTreeNode<T>>>(parent->elements[2 * i + 1]);*/
/*        int mid = fullNode->elements.size() / 2;*/
/**/
/*        auto newNode = std::make_shared<BTreeNode<T>>(fullNode->isLeaf);*/
/*        newNode->elements.assign(fullNode->elements.begin() + mid + 1, fullNode->elements.end());*/
/*        fullNode->elements.resize(mid);*/
/**/
/*        parent->elements.insert(parent->elements.begin() + 2 * i, std::get<T>(fullNode->elements[mid]));*/
/*        parent->elements.insert(parent->elements.begin() + 2 * i + 1, newNode);*/
/*    }*/
/*};*/
/**/
/*// Função para imprimir a árvore B*/
/*template <typename T>*/
/*void printTree(const std::shared_ptr<BTreeNode<T>>& node, int depth = 0) {*/
/*    if (!node) return;*/
/**/
/*    std::string prefix(depth * 4, ' '); // Indenta para exibir a profundidade*/
/*    std::cout << prefix << (node->isLeaf ? "Leaf: " : "Internal: ");*/
/**/
/*    for (const auto& elem : node->elements) {*/
/*        if (std::holds_alternative<T>(elem)) {*/
/*            std::cout << std::get<T>(elem) << " ";*/
/*        } else {*/
/*            std::cout << "[Child] ";*/
/*        }*/
/*    }*/
/*    std::cout << "\n";*/
/**/
/*    for (const auto& elem : node->elements) {*/
/*        if (std::holds_alternative<std::shared_ptr<BTreeNode<T>>>(elem)) {*/
/*            printTree(std::get<std::shared_ptr<BTreeNode<T>>>(elem), depth + 1);*/
/*        }*/
/*    }*/
/*}*/
/**/
/*// Testa a implementação da árvore B*/
/*int main() {*/
/*    BTree<int> tree(2); // Árvore B de ordem 2*/
/**/
/*    std::vector<int> keys = {10, 20, 5, 6, 12, 30, 7, 17};*/
/*    for (const auto& key : keys) {*/
/*        tree.insert(key);*/
/*    }*/
/**/
/*    std::cout << "Árvore B:\n";*/
/*    printTree(tree.root);*/
/**/
/*    return 0;*/
/*}*/




// AQUI TEM OQ TAVA NO ARQUIVO ANTES DE EU BULIR NELE!!

/**/
/*BTree::Node::Node(bool isLeaf, Product product) : isLeaf(isLeaf), product(product) {}*/
/**/
/*// Função para inserir um produto na árvore B*/
/*void BTree::insert(Product& product) {*/
/**/
/*}*/
/**/
/*// Função para procurar um produto pela chave (ID)*/
/*BTree::Node* BTree::search(int id) {*/
/**/
/*}*/
/**/
/*// Função para remover um produto da árvore B*/
/*void BTree::remove(int id) {*/
/**/
/*}*/
/**/
/*// Função para visualizar a árvore B*/
/*void BTree::view() {*/
/**/
/*}*/
