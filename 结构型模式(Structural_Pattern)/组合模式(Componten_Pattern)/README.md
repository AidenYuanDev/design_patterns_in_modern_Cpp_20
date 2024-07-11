[toc]

# 一、前言

**组合模式解决的问题是什么？** 

1. 组合成员变量 —— map
2. 组合相同的子类 —— vector

> 与传统的模式不同，C++种有STL库，直接用STL库了

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、支持数组形式的组合
简单来讲就是组合属性。
为什么要组合属性呢？
答：方便计算，直接使用STL库函数就可以了。

## 1、实现

~~~c
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>
#include <ostream>
using namespace std;

class A{
private:
    enum Ability {
        attack,
        defense,
        agile
    };
    map<int, int> abilitys;
public:
    // 数学统计类的函数：求和、平均值、最大值等
    int sum() const {
        int res = 0;
        for (auto [id, val] : abilitys) res += val;
        return res;
    }

    double average() const {
        return 1. * sum() / abilitys.size();
    }

    int max() {
        auto it = max_element(abilitys.begin(), abilitys.end(),
                            [](const auto& a, const auto& b){
                                return a.second < b.second;
                            });
        return it->second;
    }

    // 常规set()，get()方法
    A* set_attack(int val) {
        abilitys[Ability::attack] = val;
        return this;
    }
    A* set_defense(int val) {
        abilitys[Ability::defense] = val;
        return this;
    }
    A* set_agile(int val) {
        abilitys[Ability::agile] = val;
        return this;
    }

    int get_attack() {
        return abilitys[Ability::agile];
    }
    int get_defense() {
        return abilitys[Ability::defense];
    }
    int get_agile() {
        return abilitys[Ability::agile];
    }
};

int main(){
    shared_ptr<A> a = make_shared<A>();
    a->set_attack(5)->set_defense(6)->set_agile(7);

    cout << "a: " << endl;
    cout << "sum --> " << a->sum() << endl;
    cout << "average --> " << a->average() << endl;
    cout << "max --> " << a->max() << endl;
    return 0;
}
~~~
# 三、组合对象
这个和经典的组合模式就很像了，就像经典的组合模式一样，分为`根——叶子`。
场景就是，需要管理很多相同的子类（叶子）。怎么管理呢？用根。

## 1、UML类图

![组合模式](图片(image)/组合模式.png)
## 2、实现
~~~c
#include <cstdlib>
#include <memory>
#include <iostream>
#include <vector>
using namespace std;

class Componten {
public:
    virtual void show() = 0;
};

class Leaf : public Componten {
public:
    void show() override {
        cout << "Leaf" << endl;
    }
};

class Root : public Componten {
public:
    vector<shared_ptr<Componten>> leaf;

    void show() override {
        int id = 0;
        for (auto& componten : leaf) {
            cout << "id:" << id++ << "-->";
            componten->show();
        }
    }
    Root* insert_componten(shared_ptr<Componten> componten) {
        leaf.push_back(componten);
        return this;
    }
};

int main(){
    shared_ptr<Leaf> l1 = make_shared<Leaf>();
    shared_ptr<Leaf> l2 = make_shared<Leaf>();
    shared_ptr<Leaf> l3 = make_shared<Leaf>();
    unique_ptr<Root> root = make_unique<Root>();
    
    root->insert_componten(l1)->insert_componten(l2)->insert_componten(l3);
    root->show();
    return 0;
}
~~~