[toc]

# 一、前言
一句话总结外观模式：简化接口，或者简化流程。🙂

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、实现
原来需要很多个类，很多参数，现在全部集合到一个类中，简化流程。
## 1、UML类图
![外观模式](图片(image)/外观模式.png)
## 2、实现
~~~c
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
![请添加图片描述](https://img-blog.csdnimg.cn/direct/31942f4b71f0448c94e1e215dbf96980.png)
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
~~~