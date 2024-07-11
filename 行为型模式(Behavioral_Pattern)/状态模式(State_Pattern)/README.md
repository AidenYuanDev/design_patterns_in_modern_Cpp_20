@[toc]

# 一、前言

状态模式理解最基本上的我觉得应该也是够用了，实际用的话，也应该用的是`Boost.MSM`状态机。

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、实现

## 一、UML类图

![状态模式](图片(image)/状态模式.png)

## 二、实现
~~~c
#include <iostream>
#include <memory>
using namespace std;

class Light_Switch;
class On_State;
class Off_State;
class State {
public:
    virtual void on(Light_Switch* ls) = 0;
    virtual void off(Light_Switch* ls) = 0;
};

class On_State : public State {
public:
    On_State() { cout << "灯打开了" << endl; }
    void on(Light_Switch* ls) override {}
    void off(Light_Switch* ls) override;
};

class Off_State : public State {
public:
    Off_State() { cout << "灯灭了" << endl; }
    void on(Light_Switch* ls) override;
    void off(Light_Switch* ls) override {}
};

class Light_Switch {
private:
    shared_ptr<State> state_;

public:
    Light_Switch() : state_(make_shared<Off_State>()) {}
    void set_state(shared_ptr<State> state) { state_ = std::move(state); }
    void on() { state_->on(this); }
    void off() { state_->off(this); }
};

void On_State::off(Light_Switch* ls) {
    cout << "按下关灯键" << endl;
    ls->set_state(make_shared<Off_State>());
}

void Off_State::on(Light_Switch* ls) {
    cout << "按下开灯键" << endl;
    ls->set_state(make_shared<On_State>());
}

int main() {
    auto ls = make_shared<Light_Switch>();
    ls->on();
    ls->off();
    ls->on();
    return 0;
}
~~~