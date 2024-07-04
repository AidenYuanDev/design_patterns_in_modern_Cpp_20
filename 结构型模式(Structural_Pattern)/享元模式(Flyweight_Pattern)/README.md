[toc]

# 一、前言
《C++20设计模式》书中对于享元模式个人感觉不是太清晰，就跟逗小孩玩似的。

**享元模式模式是干什么的？** 
答 ：`牺牲性能，换取内存空间的技术。`

相关代码可以在这里，如有帮助给个star
[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、享元模式
简而言之，把成员变量分为经常变化和不经常变化，不经常变化的用工厂模式生成。

> 这次打破以往的惯例，写一个复杂点的类！☠️
## 1、UML类图
![享元模式](.\图片(image)\享元模式.png)

## 2、实现
~~~c
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
using namespace std;
class Tree_Type {
private:
    string name;
    int attack;
    int defense;
public:
    Tree_Type(string name, int attack, int defense) : name(name), attack(attack), defense(defense) {}

    void show(int x, int y) {
        cout << "name -->" << name << endl;
        cout << "x -->" << x << endl;
        cout << "y -->" << y << endl;
        cout << "attack -->" << attack << endl;
        cout << "defense -->" << defense << endl;
    }
};

class Tree {
private:
    int x;
    int y;
    shared_ptr<Tree_Type> tree_type;
public:
    Tree(int x, int y, shared_ptr<Tree_Type> tree_type) :
        x(x), y(y), tree_type(tree_type) {}
    void show() {
        tree_type->show(x, y);
    }
};

class Tree_Factory {
private:
    unordered_map<string, shared_ptr<Tree_Type>> tree_types;
public:
    static shared_ptr<Tree_Factory> get_instance() {
        static shared_ptr<Tree_Factory> tree_factory = make_shared<Tree_Factory>();
        return tree_factory;
    }

    shared_ptr<Tree_Type> get_tree_type(string name, int attack, int  defense) {
        string key = name + to_string(attack) + to_string(defense);
        if (tree_types.find(key) == tree_types.end()) {
            tree_types[key] = make_shared<Tree_Type>(name, attack, defense);
        }
        return tree_types[key];
    }

    
};

class Forest {
private:
    vector<shared_ptr<Tree>> trees;
public:
    Forest* plan_tree(int x, int y, string name, int attack, int defense) {
        shared_ptr<Tree_Factory> tree_factory = Tree_Factory::get_instance();
        shared_ptr<Tree_Type> tree_type = tree_factory->get_tree_type(name, attack, defense);
        shared_ptr<Tree> tree = make_shared<Tree>(x, y, tree_type);
        trees.push_back(tree);
        return this;
    }

    void show() {
        for (auto it : trees) {
            it->show();
            cout << endl;
        }
    }
};

int main(){
    unique_ptr<Forest> forest = make_unique<Forest>();
    forest->plan_tree(1, 5, "魔王", 100, 100)
          ->plan_tree(3, 6, "小弟", 5, 5)
          ->plan_tree(5, 7, "小弟", 5, 5);
    forest->show();
    return 0;
}
~~~