[toc]

# 一、前言
在看《C++20设计模式》一书中产生了疑惑，就是经典工厂模式与这一书中的讲解差别很大，在此分享我心中的疑惑。

- 讲解的方式不一样
	- 经典工厂模式分为三类 —— 简单工厂、工厂模式、抽象工厂。
	- 《C++20设计模式》一书是这么讲解的 —— 工厂方法、工厂、抽象工厂
> 这里说一下，其实他们两个讲解的东西都是同一个东西，只不过讲解的侧重点不同，而且《C++20设计模式》讲的东西还少了工厂模式的讲解。如果你仔细看书中的例子就会发现，这里《C++20设计模式》中的工厂指的是经典工厂中的简单工厂。

- 如何统一经典的工厂模式和《C++20设计模式》一书中的工厂模式。
	
	- 他们对于为什么要有工厂模式的目的不同，也其实就是讲解方式的不同。
		
		-  **经典工厂模式的目的：** 使得创建对象的过程与使用对象的过程分离，高代码的可维护性和可扩展性。
		- **《C++20设计模式》工厂模式：** 普通构造函数没法对参数进行验证，所以使用工厂模式。

> 下面是笔者认为，应该正确的讲解方式，可以统一 经典工厂模式的讲解和《C++20设计模式》中的工厂模式的讲解。


相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)
# 二、讲解
## 1、构造函数的弊端
`无法对要进行创建的对象的参数进行验证`
比如说救生员对象要求是八块腹肌，你却创建了六块腹肌，也即是一个不符合要求的对象，我们**正常的需求肯定是不创建这个对象，或者创建一个空对像**，因为它不符合要求嘛！但是构造函数却做不到这一点！

> 因为，构造函数不能返回任意的数据类型，

## 2、工厂方法（解决上述弊端）
`用静态成员方法，来代替构造函数`
很自然的想法嘛，既然构造函数没有返回值，那么我们就用成员函数嘛！成员函数不是有返回值嘛，那么就可以进行参数验证啦！
> 使用静态成员函数，是为了在创建对象之前就可以调用这个方法（因为这个方法就是为了创建对象，肯定要在创建对象之前就能调用嘛！所以用静态！


**实现**
~~~c
#include <iostream>
#include <memory>
using namespace std;

class Product_Base {
protected:
    int a;
    int b;
    Product_Base(int a, int b) : a(a), b(b) {}
};

class Product : public Product_Base {
    int c;

protected:
    Product(int a, int b, int c) : Product_Base(a, b), c(c) {}

public:
    static unique_ptr<Product> new_product(int a, int b, int c) {
        if (a < 0) return nullptr;
        return unique_ptr<Product>(new Product(a, b, c));
    }
    void show() { cout << a << '\t' << b << '\t' << c << endl; }
};

int main() {
    unique_ptr<Product> p1 = Product::new_product(4, 5, 6);
    p1->show();
    return 0;
}
~~~
## 3、简单工厂
现在就是经典工厂模式的内容了，上面的代码看似已经可以很好的解决问题了，为什么还要有简单工厂呢？

1. 使得创建对象的过程与使用对象的过程分离,提高代码的可维护性和可扩展性。(常见的答案)
2. 工厂可以根据需要动态创建不同类型的对象，而不需要客户端了解具体的创建逻辑。
3. 可以在工厂中判断对象与对象之间的关系。


### 3.1 **UML类图**
![简单工厂](.\图片(image)\简单工厂.png)


### 3.2 **实现**
~~~c
#include <iostream>
#include <memory>
using namespace std;

class Product_Base{
protected:
    int a;
    int b;
    Product_Base(int a, int b) : a(a), b(b){}
public:
    virtual void show() = 0;
};

class Product_A : public Product_Base {
    int c;
    Product_A(int a, int b, int c) : Product_Base(a, b), c(c) {}
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_A> create(int a, int b, int c) {
        return unique_ptr<Product_A>(new Product_A(a, b, c));
    }
};

class Product_B : public Product_Base {
    int c;
    Product_B(int a, int b, int c) : Product_Base(a, b), c(c) {}
    
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_B> create(int a, int b, int c) {
        return unique_ptr<Product_B>(new Product_B(a, b, c));
    }

};

class Product_C : public Product_Base {
    int c;
    Product_C(int a, int b, int c) : Product_Base(a, b), c(c) {}
    friend class Simple_Factor;
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_C> create(int a, int b, int c) {
        return unique_ptr<Product_C>(new Product_C(a, b, c));
    }

};

enum class Product_Type {
    A,
    B,
    C
};

class Simple_Factor{
public:
    static unique_ptr<Product_Base> creater_producter(Product_Type type, int a, int b, int c) {
        switch (type) {
        case Product_Type::A:
            if (a < 0) return nullptr;
            return Product_A::create(a, b, c); 
            case Product_Type::B:
            if (b < 0) return nullptr;
            return Product_B::create(a, b, c);
        case Product_Type::C:
            if (c < 0) return nullptr;
            return Product_C::create(a, b, c);
        }
        return nullptr;
    }
};

int main() { 
    unique_ptr<Product_Base> p = Simple_Factor::creater_producter(Product_Type::A, 4, 5, 6);
    p->show();
    return 0; 
}
~~~
## 4、工厂模式
上面的简单工厂模式的缺点是当新增产品的时候就要去修改工厂的类，这就违反了开放封闭原则（对扩展开发，对修改关闭）于是，就出现了工厂方法模式，也就是工厂模式。

> 工厂抽象，有新的产品直接创建新的工厂就可以

### 4.1 **UML类图**
![工厂模式](.\图片(image)\工厂模式.png)

### 4.2 **实现**
~~~c
#include <iostream>
#include <memory>
using namespace std;

class Product_Base{
protected:
    int a;
    int b;
    Product_Base(int a, int b) : a(a), b(b){}
public:
    virtual void show() = 0;
};

class Product_A : public Product_Base {
    int c;
    Product_A(int a, int b, int c) : Product_Base(a, b), c(c) {}
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_A> create(int a, int b, int c) {
        return unique_ptr<Product_A>(new Product_A(a, b, c));
    }
};

class Product_B : public Product_Base {
    int c;
    Product_B(int a, int b, int c) : Product_Base(a, b), c(c) {}
    
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_B> create(int a, int b, int c) {
        return unique_ptr<Product_B>(new Product_B(a, b, c));
    }

};

class Product_C : public Product_Base {
    int c;
    Product_C(int a, int b, int c) : Product_Base(a, b), c(c) {}
    friend class Simple_Factor;
public:
    void show(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
    static unique_ptr<Product_C> create(int a, int b, int c) {
        return unique_ptr<Product_C>(new Product_C(a, b, c));
    }

};


enum class Product_Type {
    A,
    B,
    C
};

class Factor_Base{
public:
    virtual unique_ptr<Product_Base> new_product(int a, int b, int c) = 0;
};

class Factor_A : public Factor_Base {
public:
    unique_ptr<Product_Base> new_product(int a, int b, int c) {
        if (a < 0) return nullptr;
        return Product_A::create(a, b, c);
    }
};

class Factor_B : public Factor_Base {
public:
    unique_ptr<Product_Base> new_product(int a, int b, int c) {
        if (b < 0) return nullptr;
        return Product_B::create(a, b, c);
    }
};

int main() { 
    unique_ptr<Factor_Base> factor_a = make_unique<Factor_A>();
    unique_ptr<Product_Base> product_a = factor_a->new_product(1, 5, 7);
    product_a->show();
    return 0; 
}
~~~

## 5、抽象工厂
这个模式比普通的工厂模式抽象一点。可以做到一个工厂生产多个产品，比如苹果工厂可以生产苹果也就是生产苹果汁。

> N个产品M个工厂。总结：工厂可以灵活的生产商品。

### 5.1 **UML类图**
![抽象工厂](./图片(image)\抽象工厂.png)

### 5.2 **实现**
~~~c
#include <iostream>
#include <memory>
using namespace std;

class Product_Base {
protected:
    int a;
    int b;
    Product_Base(int a, int b) : a(a), b(b) {}

public:
    virtual void show() = 0;
};

class Product_A : public Product_Base {
    int c;
    Product_A(int a, int b, int c) : Product_Base(a, b), c(c) {}

public:
    void show() { cout << a << '\t' << b << '\t' << c << endl; }
    static unique_ptr<Product_A> create(int a, int b, int c) { return unique_ptr<Product_A>(new Product_A(a, b, c)); }
};

class Product_B : public Product_Base {
    int c;
    Product_B(int a, int b, int c) : Product_Base(a, b), c(c) {}

public:
    void show() { cout << a << '\t' << b << '\t' << c << endl; }
    static unique_ptr<Product_B> create(int a, int b, int c) { return unique_ptr<Product_B>(new Product_B(a, b, c)); }
};

class Product_C : public Product_Base {
    int c;
    Product_C(int a, int b, int c) : Product_Base(a, b), c(c) {}
    friend class Simple_Factor;

public:
    void show() { cout << a << '\t' << b << '\t' << c << endl; }
    static unique_ptr<Product_C> create(int a, int b, int c) { return unique_ptr<Product_C>(new Product_C(a, b, c)); }
};

enum class Product_Type { A, B, C };

class Factor_Base {
public:
    virtual unique_ptr<Product_Base> new_product1(int a, int b, int c) = 0;
    virtual unique_ptr<Product_Base> new_product2(int a, int b, int c) = 0;
};

class Factor_A : public Factor_Base {
public:
    unique_ptr<Product_Base> new_product1(int a, int b, int c) {
        if (a < 0) return nullptr;
        return Product_A::create(a, b, c);
    }
    unique_ptr<Product_Base> new_product2(int a, int b, int c) {
        if (a < 0) return nullptr;
        return Product_B::create(a, b, c);
    }
};

class Factor_B : public Factor_Base {
public:
    unique_ptr<Product_Base> new_product1(int a, int b, int c) {
        if (b < 0) return nullptr;
        return Product_B::create(a, b, c);
    }
};

int main() {
    unique_ptr<Factor_Base> factor_a = make_unique<Factor_A>();
    unique_ptr<Product_Base> product_2 = factor_a->new_product2(1, 5, 7);
    product_2->show();
    return 0;
}
~~~

# 三、总结
工厂模式的优点：

1.  使得创建对象的过程与使用对象的过程分离，高代码的可维护性和可扩展性。
2. 使用工厂模式可以对参数进行验证。

最后如果有帮助，麻烦点个赞吧！！！