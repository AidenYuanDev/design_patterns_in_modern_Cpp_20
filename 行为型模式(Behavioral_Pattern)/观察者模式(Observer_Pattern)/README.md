# 一、前言
观察者模式感觉真的很难，我这里就实现书上差不多的例子，供大家学习吧！

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、实现

1. 这里说一下观察者模式是干什么的。

 在实际中很有用，比如以下的例子。
- 当股票价格变化时，自动通知所有关注该股票的观察者
- 当有新闻发布时，自动向所有订阅用户推送通知

2. 大概是怎么实现的
> 如果一个类中的属性发生变化了，他将通知观察者，然后让观察者来通知。

## 1、UML类图
![观察者模式](.\图片(image)\观察者模式.png)

## 2、实现
~~~c
#include <algorithm>
#include <any>
#include <iostream>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>
using namespace std;

enum class Event { NameChanged, AgeChanged, ScoreChanged, StatusChanged };

class Observer_Base {
protected:
  string observer_name;
  shared_mutex mutex;

public:
    Observer_Base(const string &observer_name) : observer_name(observer_name) {}
    virtual void update(Event event, const any &value) = 0;
};

class Person : public enable_shared_from_this<Person> {
private:
    string name;
    int age;
    double score;
    bool active;

    shared_mutex mutex;
    unordered_map<Event, vector<weak_ptr<Observer_Base>>> observers;

private:
    void notify(Event event, const any &value) {
        shared_lock lock(mutex);
        auto it = observers.find(event);
        if (it != observers.end()) {
            auto observers_copy = it->second;
            lock.unlock();
            for (auto &weak_obs : observers_copy) {
                if (auto obs = weak_obs.lock()) obs->update(event, value);
            }
        }
    }

public:
    Person(const string &name, const int &age, const double &score, const bool active) : name(name), age(age), score(score), active(active) {}

    auto subscribe(Event event, shared_ptr<Observer_Base> observer) {
        unique_lock lock(mutex);
        observers[event].push_back(observer);
        return shared_from_this();
    }

    auto unsubscribe(Event event, shared_ptr<Observer_Base> observer) {
        unique_lock lock(mutex);
        auto &obs = observers[event];
        obs.erase(remove_if(obs.begin(), obs.end(), [&](const weak_ptr<Observer_Base> &wp) { return wp.lock() == observer; }), obs.end());
        return shared_from_this();
    }

    auto set_name(const string &name_new) {
        unique_lock lock(mutex);
        if (name != name_new) {
            name = name_new;
            lock.unlock();
            notify(Event::NameChanged, name);
        }
        return shared_from_this();
    }

    auto set_age(const int &age_new) {
        unique_lock lock(mutex);
        if (age != age_new) {
            age = age_new;
            lock.unlock();
            notify(Event::AgeChanged, age);
        }
        return shared_from_this();
    }

    auto set_score(const double &score_new) {
        unique_lock lock(mutex);
        if (score != score_new) {
            score = score_new;
            lock.unlock();
            notify(Event::ScoreChanged, score);
        }
        return shared_from_this();
    }

    auto set_Active(const bool &status_new) {
        unique_lock lock(mutex);
        if (active != status_new) {
            active = status_new;
            lock.unlock();
            notify(Event::StatusChanged, active);
        }
        return shared_from_this();
    }
};

// 具体观察者类
class Person_Oberver : public Observer_Base {
public:
    Person_Oberver(const string &name) : Observer_Base(name) {}

    void update(Event event, const any &value) override {
        unique_lock lock(mutex);
        switch (event) {
            case Event::NameChanged:
                cout << observer_name << " observed name change to: " << any_cast<string>(value) << endl;
                break;
            case Event::AgeChanged:
                std::cout << observer_name << " observed age change to: " << any_cast<int>(value) << endl;
                break;
            case Event::ScoreChanged:
                std::cout << observer_name << " observed score change to: " << any_cast<double>(value) << endl;
                break;
            case Event::StatusChanged:
                std::cout << observer_name << " observed status change to: " << (any_cast<bool>(value) ? "active" : "inactive") << endl;
                break;
        }
    }
};

int main() {
    auto person = make_shared<Person>("Starry Decade", 18, 98, false);
    auto observer_1 = make_shared<Person_Oberver>("observer 1");
    auto observer_2 = make_shared<Person_Oberver>("observer 2");

    person->subscribe(Event::NameChanged, observer_1)
          ->subscribe(Event::AgeChanged, observer_1)
          ->subscribe(Event::ScoreChanged, observer_2)
          ->subscribe(Event::StatusChanged, observer_2);
    
    person->set_name("Aiden")
          ->set_age(19)
          ->set_score(100.)
          ->set_Active(true);

    return 0;
}
~~~