#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
using namespace std;
class Receiver {
private:
    int x;
    int y;

public:
    Receiver(int x, int y) : x(x), y(y) {}
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void show_pos() {
        cout << "pos:" << endl;
        cout << "x -->" << x << endl;
        cout << "y ->>" << y << endl << endl;
    }

    int get_x() { return x; }
    int get_y() { return y; }
};

class Command {
public:
    virtual void excute() = 0;
    virtual void undo() = 0;
};

class Move_Command :public Command {
private:
    unique_ptr<Receiver>& receiver;
    int x;
    int y;
    bool flag;

public:
    Move_Command(unique_ptr<Receiver> &receiver, int x, int y) :
        receiver(receiver), x(y), y(y), flag(false) {}

    void excute() override {
        receiver->move(x, y);
        flag = true;
    }

    void undo() override {
        if (flag) {
            flag = false;
            receiver->move(-x, -y);
        }
    }
};

class Invoke {
private:
    vector<shared_ptr<Command>> commands;

public:
    Invoke *push_command(shared_ptr<Command> command) {
        commands.push_back(command);
        return this;
    }
    void excute() {
        for (auto it : commands) it->excute();
    }

    void undo() {
        for (auto it = commands.rbegin(); it != commands.rend(); it++) (*it)->undo();
    }
};

int main() {
    auto invoke = make_unique<Invoke>();
    auto receiver = make_unique<Receiver>(5, 6);
    auto command_1 = make_shared<Move_Command>(receiver, 6, 6);
    auto command_2 = make_shared<Move_Command>(receiver, 1, 6);
    auto command_3 = make_shared<Move_Command>(receiver, 6, 5);

    receiver->show_pos();
    invoke->push_command(command_1)
          ->push_command(command_2)
          ->push_command(command_3)
          ->excute();
    
    receiver->show_pos();
    invoke->undo();
    receiver->show_pos();
    return 0;
}
