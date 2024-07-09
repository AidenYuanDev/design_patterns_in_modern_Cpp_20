[toc]

# 一、前言

策略模式和状态模式实现方式一样，只是目的不同，如果会状态模式的这个也就可以随便看看啦。

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、实现
## 1、UML类图
![策略模式](.\图片(image)\策略模式.png)

### 2、实现
~~~c
#include <iostream>
#include <memory>
using namespace std;
enum class Fly_Strategy {
    Fly_With_Wings,
    Fly_No_Way
};

class Fly_Behavior {
public:
    virtual void fly() const = 0;
};

class Fly_With_Wings : public Fly_Behavior{
public:
    void fly() const override {
        cout << "我可以飞" << endl;
    }
};

class Fly_No_Way : public Fly_Behavior {
public:
    void fly() const override {
        cout << "我不会飞" << endl;
    }
};

class Duck {
protected:
    unique_ptr<Fly_Behavior> fly_behavior;
    string name;
public:
    Duck(string name) : name(name) {}
    virtual void show() const = 0;
    void set_fly_strategy(Fly_Strategy strategy) {
        switch (strategy) {
            case Fly_Strategy::Fly_With_Wings:
                fly_behavior = make_unique<Fly_With_Wings>();
                break;
            case Fly_Strategy::Fly_No_Way:
                fly_behavior = make_unique<Fly_No_Way>();
                break;
        }
    }
};

class Duck_Red : public Duck {
public:
    Duck_Red(string name) : Duck(name) {}
    void show() const override {
        cout << "我是红鸭" << name;
        fly_behavior->fly();
    }
};

class Duck_Green : public Duck {
public:
    Duck_Green(string name) : Duck(name) {}
    void show() const override {
        cout << "我是绿鸭" << name;
        fly_behavior->fly();
    }
};


int main(){
    auto duck_red = make_unique<Duck_Red>("小红");
    auto duck_green = make_unique<Duck_Green>("小绿");
    duck_red->set_fly_strategy(Fly_Strategy::Fly_With_Wings);
    duck_green->set_fly_strategy(Fly_Strategy::Fly_No_Way);

    duck_red->show();
    duck_green->show();
    return 0;
}
~~~