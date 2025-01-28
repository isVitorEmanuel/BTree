#include "./include/product.h"
#include "./include/bTree.h"
#include <iostream>
#include <vector>
#include <string>

void showMenu() {
    std::cout << "- View all products (--v)\n"
              << "- Search for a product (--s <id>)\n"
              << "- Delete a product (--d <id>)\n"
              << "- Exit (exit)\n";
}

int main() {
    std::vector<Product> products = Product::importProducts("assets/dadosB.txt");

    if (products.empty()) {
        std::cerr << "Products not found." << std::endl;
        return 1;
    }

    BTree btree(3);

    for (const auto &p : products) {
        btree.insert(p);
    }

    std::cout << "[Products loaded successfully!]\n";

    while (true) {
        std::cout << ">> ";

        std::string command;
        std::getline(std::cin, command);

        if (command == "--h") {
            showMenu();
        } else if (command == "--v") {
            btree.traverse();
        } else if (command.rfind("--s", 0) == 0) {
            std::string idStr = command.substr(4);
            const int searchId = std::stoi(idStr);

            if (const auto node = btree.search(searchId)) {
                // nothing...
            } else {
                std::cout << "ERROR: product with ID " << searchId << " not found.\n";
            }
        } else if (command.rfind("--d", 0) == 0) {
            std::string idStr = command.substr(4);
            const int deleteId = std::stoi(idStr);
            std::cout << "removing product with ID " << deleteId << "...\n";
            btree.remove(deleteId);
        } else if (command == "4" || command == "exit") {
            std::cout << ">> exiting program. Goodbye!\n";
            break;
        } else {
            std::cout << "ERROR: unknown command. Please try again.\n";
        }
    }

    return 0;
}
