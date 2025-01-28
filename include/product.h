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
    Product();
    Product(int id, const string& name, int quantity);

    [[nodiscard]] int getId() const;
    [[nodiscard]] const string& getName() const;
    [[nodiscard]] int getQuantity() const;

    static vector<Product> importProducts(const string& filename);

    [[nodiscard]] string toStringComplete() const;
    [[nodiscard]] string toStringId() const;
};

#endif
