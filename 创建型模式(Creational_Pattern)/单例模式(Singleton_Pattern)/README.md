[toc]

# 一、前言
**单例模式定义：** 单例模式（Singleton Pattern）是一种创建型设计模式，其主要目的是确保一个类只有一个实例，并提供全局访问点来访问这个实例。
单例模式，较简单（容易理解）分为两种懒汉式和饿汉式。
C++11之前
- **懒汉式：**有线程安全问题，但是节约资源。
- **饿汉式：**没有线程安全问题，但是浪费资源

C++11之后懒汉式通过优化就没有线程安全问题了。

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、饿汉式
在类中直接提供类的静态对象。

## 1、实现
~~~c
#include <iostream>
using namespace std;
class Eager_Singleton {
private:
    static Eager_Singleton* instance;
protected:
    Eager_Singleton(){}
public:
    static Eager_Singleton* get_instance() {
        return instance;
    }
private:
    Eager_Singleton(Eager_Singleton&&) = delete;
    Eager_Singleton& operator=(Eager_Singleton const&) = delete;
    Eager_Singleton& operator=(Eager_Singleton &&) = delete;
};

Eager_Singleton* Eager_Singleton::instance = new Eager_Singleton();

int main(){
    Eager_Singleton* instance = Eager_Singleton::get_instance();
    return 0;
}
~~~
# 三、懒汉式
在创建时实例化对象

## 1、实现
~~~c
#include <iostream>
using namespace std;
class Lazy_Singleton {
protected:
    Lazy_Singleton(){}
public:
    static Lazy_Singleton* get_instance() {
       static Lazy_Singleton* instance = new Lazy_Singleton();
        return instance;
    }
private:
    Lazy_Singleton(Lazy_Singleton&&) = delete;
    Lazy_Singleton& operator=(Lazy_Singleton const&) = delete;
    Lazy_Singleton& operator=(Lazy_Singleton &&) = delete;
};

int main(){
    Lazy_Singleton* instance = Lazy_Singleton::get_instance();
    return 0;
}
~~~
# 四、最后
如有帮助点个赞把！