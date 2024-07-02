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
