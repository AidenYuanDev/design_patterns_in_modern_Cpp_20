[toc]

# 一、前言
装饰器模式存在的原因就是扩展类的功能。
**用法：** 套一层类，这个类起名叫装饰器。
> 很像套娃，不是嘛？

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、实现
## 1、UML类图
![装饰器模式](.\图片(image)\装饰器模式.png)

## 2、实现
~~~c
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
~~~