[toc]

# 一、前言
## 1、如何学好访问者模式，前提条件肯定是要知道`访问者模式是干什么的`。
扩展原有类族的功能（形象点来说就是系统升级），符合开闭原则，对一类代码都进行扩展

## 2、访问者模式实现方式
这里介绍两种，为什么是两种而不是一种呢？因为真的各有各的优点，很难取舍！🫠

- 经典访问者模式
- 使用std::variant和std::visit的实现访问者模式

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、经典访问者模式
类族每个类都添加`accept()`函数，传入自身this，调用访问者，然后经由访问者实现新功能。

## 1、UML类图
![经典访问者模式](/图片(image)/经典访问者模式.png)

## 2、实现
~~~c
#include <iostream>
#include <memory>
using namespace std;

class Cpu;
class Memory;

class Visitor {
public:
    virtual void visit_cpu(const Cpu& cpu) const = 0;
    virtual void visit_memory(const Memory& memory) const = 0;
};

class Computer {
public:
    virtual void accept(const Visitor& visitor) const = 0;
    virtual void show() const = 0;
};

class Cpu : public Computer {
public:
    void accept(const Visitor& visitor) const override {
        visitor.visit_cpu(*this);
    }
    void show() const override {
        cout << "老旧Cpu";
    }
};

class Memory : public Computer {
public:
    void accept(const Visitor& visitor) const override {
        visitor.visit_memory(*this);
    }
    void show() const override {
        cout << "老旧Memory";
    }

};

class Visitor_Rog : public Visitor {
public:
    void visit_cpu(const Cpu& cpu) const override {
        cpu.show();   
        cout << "升级为新Rog Cpu" << endl;
    }
    void visit_memory(const Memory& memory) const override {
        memory.show();
        cout << "升级为Rog Memory" << endl;
    }
};

int main(){
    auto cpu = make_unique<Cpu>();
    auto memory = make_unique<Memory>();
    auto visitor_rog = make_unique<Visitor_Rog>();

    cpu->accept(*visitor_rog);
    memory->accept(*visitor_rog);
    return 0;
}
~~~
# 三、使用std::variant和std::visit的实现访问者模式
这种方法利用了 C++17 引入的新特性，可以在某些情况下提供更简洁和高效的实现。所以如果可以支持C++17那么我还是推荐用这个（因为真的简单和方便）

## 1、UML类图
![variant实现访问者模式](/图片(image)/variant实现访问者模式.png)

## 2、实现

~~~c

#include <iostream>
#include <vector>
#include <variant>
#include <string>

// 定义元素类型
class Circle {
public:
    void draw() const { std::cout << "Drawing a circle\n"; }
};

class Square {
public:
    void draw() const { std::cout << "Drawing a square\n"; }
};

class Triangle {
public:
    void draw() const { std::cout << "Drawing a triangle\n"; }
};

// 使用 std::variant 定义可能的元素类型
using Shape = std::variant<Circle, Square, Triangle>;

// 定义访问者
class DrawVisitor {
public:
    void operator()(const Circle& c) const { c.draw(); }
    void operator()(const Square& s) const { s.draw(); }
    void operator()(const Triangle& t) const { t.draw(); }
};

class AreaVisitor {
public:
    double operator()(const Circle&) const { 
        std::cout << "Calculating circle area\n";
        return 3.14; // 简化计算
    }
    double operator()(const Square&) const { 
        std::cout << "Calculating square area\n";
        return 4.0; // 简化计算
    }
    double operator()(const Triangle&) const { 
        std::cout << "Calculating triangle area\n";
        return 1.5; // 简化计算
    }
};

// 使用示例
int main() {
    std::vector<Shape> shapes = {Circle(), Square(), Triangle()};

    // 使用 DrawVisitor
    std::cout << "Drawing shapes:\n";
    for (const auto& shape : shapes) {
        std::visit(DrawVisitor(), shape);
    }

    // 使用 AreaVisitor
    std::cout << "\nCalculating areas:\n";
    for (const auto& shape : shapes) {
        double area = std::visit(AreaVisitor(), shape);
        std::cout << "Area: " << area << "\n";
    }

    return 0;
}
~~~