#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

using namespace std;

class Product {
private:
    int id;
    string name;
    int quantity;

public:
    Product(int id, const string& name, int quantity);

    int getId() const;
    const string& getName() const;
    int getQuantity() const;

    static vector<Product> importProducts(const string& filename);
};

#endif
