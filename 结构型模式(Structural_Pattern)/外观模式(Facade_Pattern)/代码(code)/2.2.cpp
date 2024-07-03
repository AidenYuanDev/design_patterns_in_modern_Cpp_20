#include <iostream>
#include <memory>
using namespace std;
class A {
public:
    void show() {
        cout << "流程A" << endl;
    }
};
class B {
public:
    void show() {
        cout << "流程B" << endl;
    }
};
class C {
public:
    void show() {
        cout << "流程C" << endl;
    }
};

class Facade {
private:
    shared_ptr<A> a;
    shared_ptr<B> b;
    shared_ptr<C> c;
public:
    Facade(shared_ptr<A> a, shared_ptr<B> b, shared_ptr<C> c) :
        a(a), b(b), c(c){}
    void show() {
        cout << "流程执行:" << endl;
        cout << "完成 -->";
        a->show();
        cout << "完成 -->";
        b->show();
        cout << "完成 -->";
        c->show();
    }
};

int main(){
    shared_ptr<A> a = make_shared<A>();
    shared_ptr<B> b = make_shared<B>();
    shared_ptr<C> c = make_shared<C>();
    unique_ptr<Facade> facade = make_unique<Facade>(a, b, c);
    facade->show();
    return 0;
}
