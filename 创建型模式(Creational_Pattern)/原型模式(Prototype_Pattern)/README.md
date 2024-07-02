[toc]

# 一、前言
原型模式相较前面的构造器模式及工厂模式就会简单很多！
主要讨论的内容也就是 —— 如何正确、优雅的进行拷贝构造！

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、深拷贝浅拷贝
这个是学C++语法的时候老师必说的事，在这里留下我的理解。
- **浅拷贝**：浅拷贝是指将一个对象的值复制到另一个对象，如果对象包含指向动态分配内存的指针，仅复制指针而不复制指针指向的内容。这意味着两个指针将指向相同的内存地址，如果其中一个对象修改了该内存地址的内容，另一个对象也会受到影响。
- **深拷贝**：深拷贝是指创建一个新的对象，同时复制对象的所有内容，包括动态分配的内存。这样，即使两个对象共享相同类型的资源，也会分别拥有自己的一份拷贝，修改其中一个对象的数据不会影响另一个对象。

# 三、深拷贝实现方式（使用clone()函数）
**使用clone()实现深拷贝的好处**

- 当基类指针指向派生类对象时，如果直接使用拷贝构造函数进行复制，通常只会复制基类部分的内容，这可能导致对象切片（object slicing）问题。 
- 总体而言，使用 clone() 函数实现深拷贝有助于解决对象切片问题，提高代码的灵活性和可维护性，封装复制过程并支持多态行为，适合于面向对象设计中需要对象克隆的场景。
这里也就是实现以下`clone()`也不是太难，直接看代码把！

### 3.1实现

~~~c
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
~~~
# 四、最后
如有帮助，点点赞吧！