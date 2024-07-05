#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class User;

class Mediator_Base {
public:
    virtual void send_message(const string &message, User *sender) = 0;
};

class User {
protected:
    string name;
    weak_ptr<Mediator_Base> mediator;

public:
    explicit User(const string &name, shared_ptr<Mediator_Base> mediator) : name(name), mediator(mediator) {}
    virtual void send(const string &message) = 0;
    virtual void receive(const string &message) = 0;
};

class User_A : public User {
public:
    explicit User_A(const string &name, shared_ptr<Mediator_Base> mediator) : User(name, mediator) {}

    void send(const string &message) override {
        cout << "用户" << name << ": 发送消息: " << message << endl;
        if (auto med = mediator.lock()) med->send_message(message, this);
    }

    void receive(const string &message) override { cout << "用户" << name << ": 收到消息" << endl; }
};

class User_B : public User {
public:
    explicit User_B(const string &name, shared_ptr<Mediator_Base> mediator) : User(name, mediator) {}

    void send(const string &message) override {
        cout << "用户" << name << ": 发送消息: " << message << endl;
        if (auto med = mediator.lock()) med->send_message(message, this);
    }

    void receive(const string &message) override { cout << "用户" << name << ": 收到消息" << endl; }
};

class Mediator : public Mediator_Base, public enable_shared_from_this<Mediator> {
private:
    vector<shared_ptr<User>> users;

public:
    void send_message(const string &message, User *sender) {
        for (const auto &user : users) {
            if (user.get() == sender) continue;
            user->receive(message);
        }
    }

    shared_ptr<Mediator> add_user(shared_ptr<User> user) { 
        users.push_back(user);
        return shared_from_this();
    }
};

int main() { 
    auto mediator = make_shared<Mediator>();
    auto user_a = make_shared<User_A>("A", mediator);
    auto user_b = make_shared<User_B>("B", mediator);

    mediator->add_user(user_a)
            ->add_user(user_b);
    
    user_a->send("你好，叫我小a就可以");
    user_b->send("你也好呀，你可以叫我小b");

    return 0;
}
