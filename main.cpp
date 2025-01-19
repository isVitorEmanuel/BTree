#include <iostream>
#include <vector>
#include "product.h"

using namespace std;

int main() {
    vector<Product> products = Product::importProducts("dadosB.txt");
    cout << "Produtos importados: " << products.size() << endl;

    for (const auto& product : products) {
        cout << "ID: " << product.getId()
                  << ", Name:" << product.getName()
                  << ", Quantity: " << product.getQuantity() << endl;
    }

    return 0;
}
