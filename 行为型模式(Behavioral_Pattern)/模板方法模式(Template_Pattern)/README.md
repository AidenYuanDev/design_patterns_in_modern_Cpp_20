[toc]

# 一、前言

简单来说，编写一个虚基类，把可复用的函数写进去，这个虚基类就被称为模板。

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、实现

## 1、UML类图
![模板方法模式](图片(image)/模板方法模式.png)

## 2、实现

~~~c
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
~~~