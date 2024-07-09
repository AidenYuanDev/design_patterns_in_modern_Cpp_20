#include <iostream>
#include <memory>
using namespace std;

class Template {
public:
    virtual void step_1() const = 0;
    virtual void step_2() const = 0;
    virtual void step_3() const {} // 钩子函数，提供默认实现
};

class Concrete_1 : public Template {
public:
    void step_1() const override {
        cout << "步骤1" << endl;
    }

    void step_2() const override {
        cout << "步骤2" << endl;
    }
};

int main(){
    unique_ptr<Template> concrete_1 = make_unique<Concrete_1>();

    concrete_1->step_1();
    concrete_1->step_2();
    return 0;
}
