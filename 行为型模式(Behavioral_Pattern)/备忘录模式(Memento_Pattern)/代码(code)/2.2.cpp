#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Bank_Account;
class Memento {
private:
    int balance;
public:
    Memento(const int balance) : balance(balance) {}

    friend Bank_Account;
};

class Bank_Account {
private:
    int balance = 0;
    vector<shared_ptr<Memento>> memento;
    int current;
public:
    explicit Bank_Account(const int balance) : balance(balance) {
        memento.emplace_back(make_shared<Memento>(balance));
        current = 0;
    }

    shared_ptr<Memento> deposit(int amount) {
        balance += amount;
        auto m = make_shared<Memento>(balance);
        memento.emplace_back(m);
        current++;
        return m;
    }

    void restore(const shared_ptr<Memento>& m) {
        if (m) {
            balance = m->balance;
            memento.emplace_back(m);
            current = memento.size() - 1;
        }
    }

    shared_ptr<Memento> undo() {
        if (current > 0) {
            current--;
            auto m = memento[current];
            balance = m->balance;
            return m;
        }
        return nullptr;
    }

    shared_ptr<Memento> redo() {
       if (current + 1 < memento.size()) {
            current++;
            auto m = memento[current];
            balance = m->balance;
            return m;
        } 
        return nullptr;
    }
    friend ostream& operator << (ostream& os, unique_ptr<Bank_Account>& ba) {
        os << "balance --> " << ba->balance << endl;
        os << "current --> " << ba->current << endl;
        os << "size() --> " << ba->memento.size() << endl;
        return os;
    }
};

int main(){
    unique_ptr<Bank_Account> ba = make_unique<Bank_Account>(100);
    ba->deposit(50);
    ba->deposit(25);
    cout << ba << endl;

    ba->undo();
    cout << "Undo1:" << endl << ba << endl;

    ba->undo();
    cout << "Undo2:" << endl << ba << endl;

    ba->redo();
    cout << "Redo:" << endl << ba << endl;

    ba->undo();
    cout << "Undo3:" << endl << ba << endl;
    return 0;
}
