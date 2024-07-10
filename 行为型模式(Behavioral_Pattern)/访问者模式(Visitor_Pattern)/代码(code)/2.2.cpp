#include <iostream>
#include <memory>
using namespace std;

class Cpu;
class Memory;

class Visitor {
public:
    virtual void visit_cpu(const Cpu& cpu) const = 0;
    virtual void visit_memory(const Memory& memory) const = 0;
};

class Computer {
public:
    virtual void accept(const Visitor& visitor) const = 0;
    virtual void show() const = 0;
};

class Cpu : public Computer {
public:
    void accept(const Visitor& visitor) const override {
        visitor.visit_cpu(*this);
    }
    void show() const override {
        cout << "老旧Cpu";
    }
};

class Memory : public Computer {
public:
    void accept(const Visitor& visitor) const override {
        visitor.visit_memory(*this);
    }
    void show() const override {
        cout << "老旧Memory";
    }

};

class Visitor_Rog : public Visitor {
public:
    void visit_cpu(const Cpu& cpu) const override {
        cpu.show();   
        cout << "升级为新Rog Cpu" << endl;
    }
    void visit_memory(const Memory& memory) const override {
        memory.show();
        cout << "升级为Rog Memory" << endl;
    }
};

int main(){
    auto cpu = make_unique<Cpu>();
    auto memory = make_unique<Memory>();
    auto visitor_rog = make_unique<Visitor_Rog>();

    cpu->accept(*visitor_rog);
    memory->accept(*visitor_rog);
    return 0;
}
