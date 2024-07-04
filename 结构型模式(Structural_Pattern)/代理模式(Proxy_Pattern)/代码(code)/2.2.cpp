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
