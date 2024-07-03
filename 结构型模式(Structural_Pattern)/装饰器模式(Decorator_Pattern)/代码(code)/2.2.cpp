#include <iostream>
#include <memory>
using namespace std;

class A {
public:
    void show() {
        cout << "功能A";
    }
};

class B {
public:
    shared_ptr<A> a;
    B(shared_ptr<A> a) : a(a) {}

    void show() {
        a->show();
        cout << '\t' << "扩展功能B" << endl;
    }
};

int main(){
    shared_ptr<A> a = make_shared<A>();
    unique_ptr<B> b = make_unique<B>(a);
    b->show();
    return 0;
}
