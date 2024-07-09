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
