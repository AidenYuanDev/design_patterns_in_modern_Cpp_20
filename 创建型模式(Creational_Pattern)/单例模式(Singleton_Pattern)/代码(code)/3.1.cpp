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
