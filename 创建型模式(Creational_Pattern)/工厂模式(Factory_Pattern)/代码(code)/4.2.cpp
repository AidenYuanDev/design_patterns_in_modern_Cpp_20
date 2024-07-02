#include <iostream>
#include <memory>
using namespace std;

class Product_Base{
protected:
    int a;
    int b;
    Product_Base(int a, int b) : a(a), b(b){}
public:
    virtual void show() = 0;
};

class Product_A : public Product_Base {
    int c;
    Product_A(int a, int b, int c) : Product_Base(a, b), c(c) {}
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_A> create(int a, int b, int c) {
        return unique_ptr<Product_A>(new Product_A(a, b, c));
    }
};

class Product_B : public Product_Base {
    int c;
    Product_B(int a, int b, int c) : Product_Base(a, b), c(c) {}
    
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_B> create(int a, int b, int c) {
        return unique_ptr<Product_B>(new Product_B(a, b, c));
    }

};

class Product_C : public Product_Base {
    int c;
    Product_C(int a, int b, int c) : Product_Base(a, b), c(c) {}
    friend class Simple_Factor;
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_C> create(int a, int b, int c) {
        return unique_ptr<Product_C>(new Product_C(a, b, c));
    }

};


enum class Product_Type {
    A,
    B,
    C
};

class Factor_Base{
public:
    virtual unique_ptr<Product_Base> new_product(int a, int b, int c) = 0;
};

class Factor_A : public Factor_Base {
public:
    unique_ptr<Product_Base> new_product(int a, int b, int c) {
        if (a < 0) return nullptr;
        return Product_A::create(a, b, c);
    }
};

class Factor_B : public Factor_Base {
public:
    unique_ptr<Product_Base> new_product(int a, int b, int c) {
        if (b < 0) return nullptr;
        return Product_B::create(a, b, c);
    }
};

int main() { 
    unique_ptr<Factor_Base> factor_a = make_unique<Factor_A>();
    unique_ptr<Product_Base> product_a = factor_a->new_product(1, 5, 7);
    product_a->show();
    return 0; 
}
