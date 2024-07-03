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
