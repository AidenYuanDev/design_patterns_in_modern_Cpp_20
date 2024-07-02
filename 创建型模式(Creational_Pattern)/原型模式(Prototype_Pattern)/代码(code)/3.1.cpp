#include <iostream>
#include <memory>
using namespace std;
class Prototype_Base {
protected:
    virtual Prototype_Base *clone() = 0;
    virtual void show() = 0;
};

class Prototype : public Prototype_Base {
    int a;
    Prototype(int a) : a(a) {}

public:
    void show() override { cout << a << endl; }

    Prototype *clone() override { return new Prototype(*this); }

    static Prototype *creater(int a) { return new Prototype(a); }

    void seta(int c_a) { a = c_a; }
};

unique_ptr<Prototype> p(Prototype::creater(5));
unique_ptr<Prototype> p_clone(p->clone());

void show() {
    cout << "p -->" << endl;
    p->show();
    cout << "p_clone -->" << endl;
    p_clone->show();
}

int main() {
    show();
    p->seta(10);
    show();
    return 0;
}
