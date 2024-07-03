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
