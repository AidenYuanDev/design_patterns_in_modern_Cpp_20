#include <iostream>
using namespace std;
class monster {
public:
	// 这两个构造函数是不能同时出现的，编译器会认为他们是同一个函数。
	monster(string name, int attack_damage, int defense) {
		_name = name;
		_attack_damage = attack_damage;
		_defense = defense;
	}
	
/*
	monster(string name, int defense, int attack_damage) {
		_name = name;
		_attack_damage = attack_damage;
		_defense = defense;
	}
*/
	
private:
	string _name;
	int _attack_damage;		// 攻击力
	int _defense;			// 防御力
};

int main(){
    
    return 0;
}
