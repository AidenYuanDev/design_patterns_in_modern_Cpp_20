[toc]

# 一、前言
这代理模式和装饰器模式很像啊。都是套一层类。😰
**主要就是功能`差别`**

- **装饰器：** 为了强化原有类的功能。
- **代理模式：** 不改变原有功能，只是强化原有类的潜在行为。

> 我觉的书上有一个很好的例子就是`智能指针` ，它完美替代裸指针，代理了裸指针的所有操作，几乎在能使用裸指针的地方都可以用智能指针替代，

# 二、实现

## 1、UML类图
![代理模式](.\图片(image)\代理模式.png)

## 2、实现

~~~c
#include <iostream>
#include <memory>
using namespace std;
class Image {
private:
    string file_name;
public:
    Image(string file_name) : file_name(file_name) {}
    void show() {
        cout << file_name << endl;
    }
};

class Image_Proxy {
private:
    shared_ptr<Image> image;
    string file_name;
public:
    Image_Proxy(string file_name) : image(nullptr), file_name(file_name) {}

    void show() {
        if (image == nullptr) {
            cout << "延迟加载" << endl;
            image = make_shared<Image>(file_name);
        }
        image->show();
    }
};

int main(){
    auto image_proxy = make_unique<Image_Proxy>("雷姆老婆.png");
    image_proxy->show();
    image_proxy->show();
    return 0;
}
~~~