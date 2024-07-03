#include <iostream>
#include <memory>
using namespace std;
class A_Base {
public:
    virtual void show() = 0;
};

class A1 : public A_Base {
public:
    void show() override {
        cout << "A1" << '\t';
    }
};

class A2 : public A_Base {
public:
    void show() override {
        cout << "A2" << '\t';
    }
};

class B_Base {
protected:
    B_Base(shared_ptr<A_Base> a) : p_a(a) {}

public:
    virtual void show() = 0;
    shared_ptr<A_Base> p_a;
};

class B1 : public B_Base {
public:
    B1(shared_ptr<A_Base> a) : B_Base(a) {}
    void show() override {
        p_a->show();
        cout << "B1" << '\t';
    }
};

class B2 : public B_Base {
public:
    B2(shared_ptr<A_Base> a) : B_Base(a) {}
    void show() override {
        p_a->show();
        cout << "B2" << '\t';
    }
};



int main(){
    shared_ptr<A_Base> p_a = make_shared<A1>();
    unique_ptr<B1> b1 = make_unique<B1>(p_a); // 想要A_Base的哪个子类传就可以
    b1->show();
    return 0;
}
