#include <iostream>
#include <vector>
#include <variant>
#include <string>

// 定义元素类型
class Circle {
public:
    void draw() const { std::cout << "Drawing a circle\n"; }
};

class Square {
public:
    void draw() const { std::cout << "Drawing a square\n"; }
};

class Triangle {
public:
    void draw() const { std::cout << "Drawing a triangle\n"; }
};

// 使用 std::variant 定义可能的元素类型
using Shape = std::variant<Circle, Square, Triangle>;

// 定义访问者
class DrawVisitor {
public:
    void operator()(const Circle& c) const { c.draw(); }
    void operator()(const Square& s) const { s.draw(); }
    void operator()(const Triangle& t) const { t.draw(); }
};

class AreaVisitor {
public:
    double operator()(const Circle&) const { 
        std::cout << "Calculating circle area\n";
        return 3.14; // 简化计算
    }
    double operator()(const Square&) const { 
        std::cout << "Calculating square area\n";
        return 4.0; // 简化计算
    }
    double operator()(const Triangle&) const { 
        std::cout << "Calculating triangle area\n";
        return 1.5; // 简化计算
    }
};

// 使用示例
int main() {
    std::vector<Shape> shapes = {Circle(), Square(), Triangle()};

    // 使用 DrawVisitor
    std::cout << "Drawing shapes:\n";
    for (const auto& shape : shapes) {
        std::visit(DrawVisitor(), shape);
    }

    // 使用 AreaVisitor
    std::cout << "\nCalculating areas:\n";
    for (const auto& shape : shapes) {
        double area = std::visit(AreaVisitor(), shape);
        std::cout << "Area: " << area << "\n";
    }

    return 0;
}
