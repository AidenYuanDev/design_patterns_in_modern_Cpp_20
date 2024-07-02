#include <iostream>
using namespace std;
class A {
    int a;
public:
    A(int a) : a(a) {}
    void show() {
        cout << "接口A:" << a << endl;
    }
};

class B_Base {
public:
    virtual void showB() = 0;
};

class B : public B_Base {
    int b;
public:
    void showB() {
        cout << "接口B:" << b << endl;
    }
};

class Adapter : public B_Base {
    A* a_instance;
public:
    Adapter(A* a_instance) : a_instance(a_instance) {}
    // 转换成：接口B包裹接口A的形式
    void showB() override {
        cout << "接口B:"; // 转换成 接口B 
        a_instance->show();
    }
};

int main() {
    A* a_instance = new A(5);
    Adapter* adapter = new Adapter(a_instance);
    adapter->showB();
    return 0;
}
