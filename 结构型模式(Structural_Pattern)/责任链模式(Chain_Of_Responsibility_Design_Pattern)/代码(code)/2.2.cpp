#include <iostream>
#include <memory>
using namespace std;
class Role {
public:
    string name;
    int attack;
    int defense;

    Role(string name, int attack, int defense) : name(name), attack(attack), defense(defense) {}

    friend ostream &operator<<(ostream &os, Role &role) {
        os << "name -->" << role.name << endl;
        os << "attack -->" << role.attack << endl;
        os << "defense -->" << role.defense << endl << endl;
        return os;
    }
};

class Creature_Modifier {
private:
    shared_ptr<Creature_Modifier> next;

protected:
    unique_ptr<Role> &role;

public:
    Creature_Modifier(unique_ptr<Role> &role) : role(role) {}
    shared_ptr<Creature_Modifier> add(shared_ptr<Creature_Modifier> cm) {
        if (next) next->add(cm);
        else next = cm;
        return next;

    }

    virtual void handle() {
        if (next) next->handle();
    }
};

class Double_Attack_Modifier : public Creature_Modifier {
public:
    Double_Attack_Modifier(unique_ptr<Role>& role) : Creature_Modifier(role) {}

    void handle() override {
        role->attack *= 2;
        Creature_Modifier::handle();
    }
};

class Increase_Defense_Modifier : public Creature_Modifier {
public:
    Increase_Defense_Modifier(unique_ptr<Role>& role) : Creature_Modifier(role) {}

    void handle() override {
        if (role->attack <= 2) role->defense++;
        Creature_Modifier::handle();
    }
};

int main() {
    unique_ptr<Role> role = make_unique<Role>("Aiden", 1, 1);
    auto root = make_unique<Creature_Modifier>(role);
    auto double_attack_modifier_1 = make_shared<Double_Attack_Modifier>(role);
    auto double_attack_modifier_2 = make_shared<Double_Attack_Modifier>(role);
    auto increase_defense_modifier = make_shared<Increase_Defense_Modifier>(role);

    root->add(double_attack_modifier_1)
        ->add(increase_defense_modifier)
        ->add(double_attack_modifier_2);
    // 要从根节点开始处理，所以单独拿出来
    root->handle();

    cout << *role << endl;
    return 0;
}
