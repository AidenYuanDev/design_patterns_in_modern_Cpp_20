[toc]

# 一、前言
怎么判断你是否理解桥接模式了呢？🧐
试着回答下面这个问题吧！😋
桥接模式到底解决的是什么问题？
`当一个类有两个或多个抽象父类，把继承抽象父类变成组合（耦合）抽象类，降低系统复杂度的操作`

相关代码可以在这里，如有帮助给个star
[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、探讨一个类有多个抽象父类的情况（为什么会有桥接）
这里的C要求继承一个A类一个B类，实际上可以的组合6种不同的C。（如果再多点A、B子类，C的数量级将是指数级增长）😵
怎么解决这个问题呢！！！🤩
答案当然是桥接！🥳
![桥接模式继承问题](图片(image)/桥接模式继承问题.png)

# 三、桥接模式
桥接模式高明的点就是把原来需要继承的父类，组合起来。这里可能过于抽象，先看看下面的类图和代码吧！

> 被组合的类，需要不同的子类，传给他进行初始化就可以了。

## 3.1 UML类图
![桥接模式](图片(image)/桥接模式.png)

## 3.2 实现
~~~c
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
~~~

# 四、最后
创作不易，如有帮助，点个赞吧！😚