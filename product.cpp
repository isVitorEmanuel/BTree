#include "product.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 

using namespace std;

Product::Product(int id, const string& name, int quantity)
    : id(id), name(name), quantity(quantity) {}

int Product::getId() const {
    return id;
}

const string& Product::getName() const {
    return name;
}

int Product::getQuantity() const {
    return quantity;
}

vector<Product> Product::importProducts(const string& filename) {
    vector<Product> products; 
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return products;
    }

    string line;
    while (getline(file, line)) {
        line.erase(remove(line.begin(), line.end(), '{'), line.end());
        line.erase(remove(line.begin(), line.end(), '}'), line.end());

        istringstream iss(line);
        int id, quantity;
        string name;

        if (iss >> id) { 
            iss.ignore(1, ',');
            getline(iss, name, ',');

            name.erase(0, name.find_first_not_of(' '));
            if (!name.empty() && name.front() == '"') {
                name.erase(name.begin());
            }

            name.erase(name.find_last_not_of(' '), string::npos);
            if (!name.empty() && name.back() == '"') {
                name.erase(name.end() - 1); 
            }

            if (iss >> quantity) {
                Product product(id, name, quantity);
                products.push_back(product); 
            }
        }
    }

    file.close();
    return products;
}