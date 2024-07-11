@[toc]
# 一、前言
从适配器模式开始就是类的组合聚合，类与类之间结构性的问题了。
-  **适配器模式解决的问题：** 适配器模式能够在不破坏现有系统结构的情况下，使得不兼容的接口可以协同工作
相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、对于接口的讨论
可能会有以下两种情况：

1. 两个接口都有抽象父类
![接口情况1](/图片(image)/接口情况1.png)
2. 没有抽象父类
![接口情况2](.\图片(image)\接口情况2.png)
不知道大家怎么样，我当时从网上看实现方案真是千奇百怪，当然现在才发现是有没有抽象父类的问题！🥸

哪这个影响嘛？🤔
答案嘛不影响。
知道适配器怎么加上的你就明白了！
适配器：`是B_Base的子类，关联A(成员函数)`

>具体的A转化为B的接口，所以A有没有抽象都无所谓，最后适配器的工作是把具体的A转换成B_Base

# 三、实现
由于上面两种情况都一样，所以作者实现第二种，简单点。🫠
## 1、对象适配器
对象适配器通过组合被适配者对象来实现适配器模式,适配器类实现目标接口，并在内部持有一个被适配者对象的实例

**优点：** 
1. **灵活性：** 对象适配器使用组合关系，因此可以适配多个不同的被适配者对象，且可以在运行时动态改变适配者对象。

**缺点**

1. **更多的对象间交互：** 可能会导致系统中对象数量增加，复杂度增加。

### 1.1 UML类图
![对象适配器](/图片(image)/对象适配器.png)


### 1.2 实现
~~~c
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
~~~

## 2、类适配器
不推荐用这个。偶然间看到了，而且《C++20设计模式》中没有写这个。可能是缺点太明显了把！😑

**缺点：** 

1.**会出现二义性：**  由于继承多个类，可能会出现**二义性**
2. **无法适配被适配者类的子类：** 如果被适配者类有子类，且希望适配器也能适配这些子类，类适配器不太适合，因为它固定了适配器与被适配者类的继承关系。
3. **需求不灵活：** 由于适配器与被适配者类的绑定关系是静态的，无法在运行时动态改变适配器的行为。

> 这里就不写了，困啦，而且也不常用。具体就是适配器同时继承接口A及接口B

# 四、最后
如有帮助，点个赞把！创作不易！！！😭