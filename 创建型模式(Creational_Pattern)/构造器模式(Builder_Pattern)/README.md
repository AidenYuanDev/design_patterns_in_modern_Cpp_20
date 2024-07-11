[TOC]



# 一、前言
笔者时刚学习`Builder Pattern`，遇到了很多问题，在此汇总一下，也希望能帮到你，如有错误请指正。

- 为什么需要`Builder Pattern`,`Builder Pattern`到底解决了什么实际问题？为什么不用set()方法？
- 《C++20：设计模式》流式构造器到底怎么实现的？`friend`关键字的使用是否必要？
- 常规的构造器怎么实现？他能解决的问题？
- 组合构造器的实现？

相关代码可以在这里，如有帮助给个star！[AidenYuanDev/design_patterns_in_modern_Cpp_20](https://github.com/AidenYuanDev/design_patterns_in_modern_Cpp_20)

# 二、为什么需要`Builder Pattern`,`Builder Pattern`到底解决了什么实际问题？为什么不用set()方法？
首先明确一个点，`Builder Pattern`主要是对于**对象的属性初始化**的研究，也就是我们怎么样的方式创建对象才能高内聚，低耦合，实现更优雅。

## 2.1 初学者有那些对象的属性初始化方法呢？

1. 使用构造函数 —— 属性的初始化只能是固定的顺序
2.  创建set()函数初始化函数 —— 类属性太多，类的可读性太差

### 2.1.1 构造函数的弊端
#### 2.1.1.1 对于属性的初始化只能是固定的顺序
重载的特性：如果一个构造函数的参数个数，参数类型，参数顺序一致的话就说他是同一个构造函数

举个例子：
~~~c
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
~~~
所以说要想按任意顺序初始化类的属性，该怎么办呢？没错可以用set()方法

### 2.1.2 用set()函数初始化类的弊端
#### 2.1.2.1 类属性太多，类的可读性太差
注：这里用了流式（也就是返回类自己的指针，主要简化main中初始化过程）
举个例子：
~~~c
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>

class Vehicle {
private:
    // 基本属性
    std::string make;
    std::string model;
    int year;
    double price;

    // 动力属性
    double engineSize;
    int horsepower;
    std::string fuelType;

    // 尺寸和重量
    double length;
    double width;
    double height;
    double curbWeight;

    // 车辆特征
    std::vector<std::string> features;
    std::map<std::string, std::string> specifications;
    std::set<std::string> safetyFeatures;

    // 拥有者信息
    std::list<std::string> previousOwners;
    std::map<std::string, std::string> ownerDetails;

public:
    // 构造函数
    Vehicle(std::string make, std::string model, int year, double price)
        : make(make), model(model), year(year), price(price) {}

    // 流式设置方法
    Vehicle& setMake(const std::string &make) { this->make = make; return *this; }
    Vehicle& setModel(const std::string &model) { this->model = model; return *this; }
    Vehicle& setYear(int year) { this->year = year; return *this; }
    Vehicle& setPrice(double price) { this->price = price; return *this; }
    Vehicle& setEngineSize(double engineSize) { this->engineSize = engineSize; return *this; }
    Vehicle& setHorsepower(int horsepower) { this->horsepower = horsepower; return *this; }
    Vehicle& setFuelType(const std::string &fuelType) { this->fuelType = fuelType; return *this; }
    Vehicle& setLength(double length) { this->length = length; return *this; }
    Vehicle& setWidth(double width) { this->width = width; return *this; }
    Vehicle& setHeight(double height) { this->height = height; return *this; }
    Vehicle& setCurbWeight(double curbWeight) { this->curbWeight = curbWeight; return *this; }

    Vehicle& addFeature(const std::string &feature) { features.push_back(feature); return *this; }
    Vehicle& addSpecification(const std::string &key, const std::string &value) { specifications[key] = value; return *this; }
    Vehicle& addSafetyFeature(const std::string &feature) { safetyFeatures.insert(feature); return *this; }

    Vehicle& addPreviousOwner(const std::string &owner) { previousOwners.push_back(owner); return *this; }
    Vehicle& addOwnerDetail(const std::string &key, const std::string &value) { ownerDetails[key] = value; return *this; }

    // 获取属性的方法
    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    double getEngineSize() const { return engineSize; }
    int getHorsepower() const { return horsepower; }
    std::string getFuelType() const { return fuelType; }
    double getLength() const { return length; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double getCurbWeight() const { return curbWeight; }
    std::vector<std::string> getFeatures() const { return features; }
    std::map<std::string, std::string> getSpecifications() const { return specifications; }
    std::set<std::string> getSafetyFeatures() const { return safetyFeatures; }
    std::list<std::string> getPreviousOwners() const { return previousOwners; }
    std::map<std::string, std::string> getOwnerDetails() const { return ownerDetails; }

    // 打印车辆信息的方法
    void printVehicleInfo() const {
        std::cout << "Make: " << make << "\nModel: " << model << "\nYear: " << year << "\nPrice: $" << price << "\n";
        std::cout << "Engine Size: " << engineSize << "L\nHorsepower: " << horsepower << "\nFuel Type: " << fuelType << "\n";
        std::cout << "Dimensions (LxWxH): " << length << " x " << width << " x " << height << " meters\n";
        std::cout << "Curb Weight: " << curbWeight << " kg\n";
        
        std::cout << "Features:\n";
        for (const auto &feature : features) {
            std::cout << "- " << feature << "\n";
        }

        std::cout << "Specifications:\n";
        for (const auto &spec : specifications) {
            std::cout << spec.first << ": " << spec.second << "\n";
        }

        std::cout << "Safety Features:\n";
        for (const auto &safety : safetyFeatures) {
            std::cout << "- " << safety << "\n";
        }

        std::cout << "Previous Owners:\n";
        for (const auto &owner : previousOwners) {
            std::cout << "- " << owner << "\n";
        }

        std::cout << "Owner Details:\n";
        for (const auto &detail : ownerDetails) {
            std::cout << detail.first << ": " << detail.second << "\n";
        }
    }
};

int main() {
    Vehicle car("Toyota", "Camry", 2021, 24000);
    car.setEngineSize(2.5)
       .setHorsepower(203)
       .setFuelType("Gasoline")
       .setLength(4.88)
       .setWidth(1.84)
       .setHeight(1.45)
       .setCurbWeight(1495)
       .addFeature("Air Conditioning")
       .addFeature("Navigation System")
       .addSpecification("Transmission", "8-speed automatic")
       .addSpecification("Drivetrain", "FWD")
       .addSafetyFeature("ABS")
       .addSafetyFeature("Airbags")
       .addPreviousOwner("John Doe")
       .addOwnerDetail("Current Owner", "Jane Smith");

    car.printVehicleInfo();

    return 0;
}

~~~

# 三、`Builder Pattern`各种写法的对比
## 3.1 《C++20设计模式》中的流式构造器
流式构造器要明白他的意思要把它分成两部分：

- **构造器**：就是把set方法从原有的类中拿出来，建立一个新类，用这个新类构造原来的类，实现解耦。
- **流式**：`set()`返回值不再是`void`，现在`返回类的指针`
### 3.1.1 流式构造器
- 流式构造器重载`Vehicle()`，就可以省去返回`build()`步骤
- 这里注意要把流式构造器设置为（友元），不然访问不了被造的类的私有成员函数。
	> 是否应该使用friend关键字，后面讨论（friend破坏类的封装，到底要不要用，应不应该用？）

#### 3.1.1.1 UML类图
![流式构造器UML类图](图片(image)/流式构造器.png)

#### 3.1.1.2 实现

~~~c
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <memory>

class Vehicle {
private:
    // 基本属性
    std::string make;
    std::string model;
    int year;
    double price;

    // 动力属性
    double engineSize;
    int horsepower;
    std::string fuelType;

    // 尺寸和重量
    double length;
    double width;
    double height;
    double curbWeight;

    // 车辆特征
    std::vector<std::string> features;
    std::map<std::string, std::string> specifications;
    std::set<std::string> safetyFeatures;

    // 拥有者信息
    std::list<std::string> previousOwners;
    std::map<std::string, std::string> ownerDetails;

public:
    // 构造函数
    Vehicle(const std::string& make, const std::string& model, int year, double price)
        : make(make), model(model), year(year), price(price), engineSize(0), horsepower(0), length(0), width(0), height(0), curbWeight(0) {}

    // 打印车辆信息的方法
    void printVehicleInfo() const {
        std::cout << "Make: " << make << "\nModel: " << model << "\nYear: " << year << "\nPrice: $" << price << "\n";
        std::cout << "Engine Size: " << engineSize << "L\nHorsepower: " << horsepower << "\nFuel Type: " << fuelType << "\n";
        std::cout << "Dimensions (LxWxH): " << length << " x " << width << " x " << height << " meters\n";
        std::cout << "Curb Weight: " << curbWeight << " kg\n";
        
        std::cout << "Features:\n";
        for (const auto &feature : features) {
            std::cout << "- " << feature << "\n";
        }

        std::cout << "Specifications:\n";
        for (const auto &spec : specifications) {
            std::cout << spec.first << ": " << spec.second << "\n";
        }

        std::cout << "Safety Features:\n";
        for (const auto &safety : safetyFeatures) {
            std::cout << "- " << safety << "\n";
        }

        std::cout << "Previous Owners:\n";
        for (const auto &owner : previousOwners) {
            std::cout << "- " << owner << "\n";
        }

        std::cout << "Owner Details:\n";
        for (const auto &detail : ownerDetails) {
            std::cout << detail.first << ": " << detail.second << "\n";
        }
    }

    // 友元声明，允许构建器访问私有成员
    friend class VehicleBuilder;
};

class VehicleBuilder {
private:
    std::unique_ptr<Vehicle> vehicle;

public:
    // 构造函数
    VehicleBuilder(const std::string& make, const std::string& model, int year, double price)
        : vehicle(std::make_unique<Vehicle>(make, model, year, price)) {}

    // 流式设置方法
    VehicleBuilder& setEngineSize(double engineSize) { vehicle->engineSize = engineSize; return *this; }
    VehicleBuilder& setHorsepower(int horsepower) { vehicle->horsepower = horsepower; return *this; }
    VehicleBuilder& setFuelType(const std::string &fuelType) { vehicle->fuelType = fuelType; return *this; }
    VehicleBuilder& setLength(double length) { vehicle->length = length; return *this; }
    VehicleBuilder& setWidth(double width) { vehicle->width = width; return *this; }
    VehicleBuilder& setHeight(double height) { vehicle->height = height; return *this; }
    VehicleBuilder& setCurbWeight(double curbWeight) { vehicle->curbWeight = curbWeight; return *this; }

    VehicleBuilder& addFeature(const std::string &feature) { vehicle->features.push_back(feature); return *this; }
    VehicleBuilder& addSpecification(const std::string &key, const std::string &value) { vehicle->specifications[key] = value; return *this; }
    VehicleBuilder& addSafetyFeature(const std::string &feature) { vehicle->safetyFeatures.insert(feature); return *this; }

    VehicleBuilder& addPreviousOwner(const std::string &owner) { vehicle->previousOwners.push_back(owner); return *this; }
    VehicleBuilder& addOwnerDetail(const std::string &key, const std::string &value) { vehicle->ownerDetails[key] = value; return *this; }

    // 类型转换运算符重载
    operator std::unique_ptr<Vehicle>() { return std::move(vehicle); }
};

int main() {
    std::unique_ptr<Vehicle> car = VehicleBuilder("Toyota", "Camry", 2021, 24000)
        .setEngineSize(2.5)
        .setHorsepower(203)
        .setFuelType("Gasoline")
        .setLength(4.88)
        .setWidth(1.84)
        .setHeight(1.45)
        .setCurbWeight(1495)
        .addFeature("Air Conditioning")
        .addFeature("Navigation System")
        .addSpecification("Transmission", "8-speed automatic")
        .addSpecification("Drivetrain", "FWD")
        .addSafetyFeature("ABS")
        .addSafetyFeature("Airbags")
        .addPreviousOwner("John Doe")
        .addOwnerDetail("Current Owner", "Jane Smith");

    car->printVehicleInfo();

    return 0;
}

~~~

## 3.2 传统构造器
传统构造器是怎么实现的？他的优点是什么？
> 虽然说上一个流式构造器，已经非常优秀了，但是经典构造器依旧有优点（这点见仁见智）！

方式：要创建新的对象，就写一个具体的类实现抽象类。
优点 ：

- 创建一个具体的类，后下次就不用创建了，直接用就可以，提高复用性 。
- 我们可以选择不同的类，实现选配的效果

### 3.2.1 UML类图
![经典构造器UML类图](图片(image)/经典构造器.png)
### 3.2.2实现
~~~c
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <memory>

// 产品类
class Vehicle {
private:
    // 基本属性
    std::string make;
    std::string model;
    int year;
    double price;

    // 动力属性
    double engineSize;
    int horsepower;
    std::string fuelType;

    // 尺寸和重量
    double length;
    double width;
    double height;
    double curbWeight;

    // 车辆特征
    std::vector<std::string> features;
    std::map<std::string, std::string> specifications;
    std::set<std::string> safetyFeatures;

    // 拥有者信息
    std::list<std::string> previousOwners;
    std::map<std::string, std::string> ownerDetails;

public:
    // 设置各属性的方法
    void setMake(const std::string& make) { this->make = make; }
    void setModel(const std::string& model) { this->model = model; }
    void setYear(int year) { this->year = year; }
    void setPrice(double price) { this->price = price; }
    void setEngineSize(double engineSize) { this->engineSize = engineSize; }
    void setHorsepower(int horsepower) { this->horsepower = horsepower; }
    void setFuelType(const std::string& fuelType) { this->fuelType = fuelType; }
    void setLength(double length) { this->length = length; }
    void setWidth(double width) { this->width = width; }
    void setHeight(double height) { this->height = height; }
    void setCurbWeight(double curbWeight) { this->curbWeight = curbWeight; }
    void addFeature(const std::string& feature) { features.push_back(feature); }
    void addSpecification(const std::string& key, const std::string& value) { specifications[key] = value; }
    void addSafetyFeature(const std::string& feature) { safetyFeatures.insert(feature); }
    void addPreviousOwner(const std::string& owner) { previousOwners.push_back(owner); }
    void addOwnerDetail(const std::string& key, const std::string& value) { ownerDetails[key] = value; }

    // 打印车辆信息的方法
    void printVehicleInfo() const {
        std::cout << "Make: " << make << "\nModel: " << model << "\nYear: " << year << "\nPrice: $" << price << "\n";
        std::cout << "Engine Size: " << engineSize << "L\nHorsepower: " << horsepower << "\nFuel Type: " << fuelType << "\n";
        std::cout << "Dimensions (LxWxH): " << length << " x " << width << " x " << height << " meters\n";
        std::cout << "Curb Weight: " << curbWeight << " kg\n";
        
        std::cout << "Features:\n";
        for (const auto &feature : features) {
            std::cout << "- " << feature << "\n";
        }

        std::cout << "Specifications:\n";
        for (const auto &spec : specifications) {
            std::cout << spec.first << ": " << spec.second << "\n";
        }

        std::cout << "Safety Features:\n";
        for (const auto &safety : safetyFeatures) {
            std::cout << "- " << safety << "\n";
        }

        std::cout << "Previous Owners:\n";
        for (const auto &owner : previousOwners) {
            std::cout << "- " << owner << "\n";
        }

        std::cout << "Owner Details:\n";
        for (const auto &detail : ownerDetails) {
            std::cout << detail.first << ": " << detail.second << "\n";
        }
    }
};

// 抽象建造者
class VehicleBuilder {
public:
    virtual ~VehicleBuilder() = default;

    virtual void setMake() = 0;
    virtual void setModel() = 0;
    virtual void setYear() = 0;
    virtual void setPrice() = 0;
    virtual void setEngineSize() = 0;
    virtual void setHorsepower() = 0;
    virtual void setFuelType() = 0;
    virtual void setDimensions() = 0;
    virtual void setCurbWeight() = 0;
    virtual void addFeatures() = 0;
    virtual void addSpecifications() = 0;
    virtual void addSafetyFeatures() = 0;
    virtual void addPreviousOwners() = 0;
    virtual void addOwnerDetails() = 0;

    virtual std::unique_ptr<Vehicle> getVehicle() = 0;
};

// 具体建造者
class ConcreteVehicleBuilder : public VehicleBuilder {
private:
    std::unique_ptr<Vehicle> vehicle;

public:
    ConcreteVehicleBuilder() {
        vehicle = std::make_unique<Vehicle>();
    }

    void setMake() override {
        vehicle->setMake("Toyota");
    }

    void setModel() override {
        vehicle->setModel("Camry");
    }

    void setYear() override {
        vehicle->setYear(2021);
    }

    void setPrice() override {
        vehicle->setPrice(24000);
    }

    void setEngineSize() override {
        vehicle->setEngineSize(2.5);
    }

    void setHorsepower() override {
        vehicle->setHorsepower(203);
    }

    void setFuelType() override {
        vehicle->setFuelType("Gasoline");
    }

    void setDimensions() override {
        vehicle->setLength(4.88);
        vehicle->setWidth(1.84);
        vehicle->setHeight(1.45);
    }

    void setCurbWeight() override {
        vehicle->setCurbWeight(1495);
    }

    void addFeatures() override {
        vehicle->addFeature("Air Conditioning");
        vehicle->addFeature("Navigation System");
    }

    void addSpecifications() override {
        vehicle->addSpecification("Transmission", "8-speed automatic");
        vehicle->addSpecification("Drivetrain", "FWD");
    }

    void addSafetyFeatures() override {
        vehicle->addSafetyFeature("ABS");
        vehicle->addSafetyFeature("Airbags");
    }

    void addPreviousOwners() override {
        vehicle->addPreviousOwner("John Doe");
    }

    void addOwnerDetails() override {
        vehicle->addOwnerDetail("Current Owner", "Jane Smith");
    }

    std::unique_ptr<Vehicle> getVehicle() override {
        return std::move(vehicle);
    }
};

// 指挥者类
class Director {
private:
    VehicleBuilder* builder;

public:
    void setBuilder(VehicleBuilder* builder) {
        this->builder = builder;
    }

    std::unique_ptr<Vehicle> construct() {
        builder->setMake();
        builder->setModel();
        builder->setYear();
        builder->setPrice();
        builder->setEngineSize();
        builder->setHorsepower();
        builder->setFuelType();
        builder->setDimensions();
        builder->setCurbWeight();
        builder->addFeatures();
        builder->addSpecifications();
        builder->addSafetyFeatures();
        builder->addPreviousOwners();
        builder->addOwnerDetails();
        return builder->getVehicle();
    }
};

// 主函数
int main() {
    Director director;
    ConcreteVehicleBuilder builder;

    director.setBuilder(&builder);
    std::unique_ptr<Vehicle> car = director.construct();

    car->printVehicleInfo();

    return 0;
}

~~~
## 3.3 组合构造器
个人觉得这个依然是巅峰了，当时第一次看到这个实现方式真的是惊为天人！

优点：可以选配（特定一类属性进行初始化，再也不用担心到不到要初始化的类了！）

### 3.3.1UML类图

![组合构造器UML类图](图片(image)/组合构造器.png)


### 3.3.2实现

~~~c
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <memory>
using namespace std;

class Vehicle_Builder;
class V_Basic_Properties_Builder;
class V_Dynamic_Properties_Builder;
class V_Size_And_Weight_Builder;
class V_Vehicle_Features_Builder;
class V_Owner_Information_Builder;

class Vehicle {
private:
    // 基本属性
    std::string make;
    std::string model;
    int year;
    double price;

    // 动力属性
    double engineSize;
    int horsepower;
    std::string fuelType;

    // 尺寸和重量
    double length;
    double width;
    double height;
    double curbWeight;

    // 车辆特征
    std::vector<std::string> features;
    std::map<std::string, std::string> specifications;
    std::set<std::string> safetyFeatures;

    // 拥有者信息
    std::list<std::string> previousOwners;
    std::map<std::string, std::string> ownerDetails;

public:
    static Vehicle_Builder create();
    Vehicle(){}

    // 打印车辆信息的方法
    void printVehicleInfo() const {
        std::cout << "制造商: " << make << "\n型号: " << model << "\n年份: " << year << "\n价格: $" << price << "\n";
        std::cout << "发动机大小: " << engineSize << "L\n马力: " << horsepower << "\n燃料类型: " << fuelType << "\n";
        std::cout << "尺寸 (长x宽x高): " << length << " x " << width << " x " << height << " 米\n";
        std::cout << "整备质量: " << curbWeight << " 千克\n";
        
        std::cout << "特征:\n";
        for (const auto &feature : features) {
            std::cout << "- " << feature << "\n";
        }

        std::cout << "规格:\n";
        for (const auto &spec : specifications) {
            std::cout << spec.first << ": " << spec.second << "\n";
        }

        std::cout << "安全特征:\n";
        for (const auto &safety : safetyFeatures) {
            std::cout << "- " << safety << "\n";
        }

        std::cout << "之前的车主:\n";
        for (const auto &owner : previousOwners) {
            std::cout << "- " << owner << "\n";
        }

        std::cout << "车主详细信息:\n";
        for (const auto &detail : ownerDetails) {
            std::cout << detail.first << ": " << detail.second << "\n";
        }
    }

    // 友元声明，允许构建器访问私有成员
    friend class Vehicle_Builder;
    friend class V_Basic_Properties_Builder;
    friend class V_Dynamic_Properties_Builder;
    friend class V_Size_And_Weight_Builder;
    friend class V_Vehicle_Features_Builder;
    friend class V_Owner_Information_Builder;
};

class Vehicle_Builder_Base {
protected:
    Vehicle& vehicle;
    explicit Vehicle_Builder_Base(Vehicle& vehicle) : vehicle(vehicle) {}

public:
    operator Vehicle() { return std::move(vehicle); }
    V_Basic_Properties_Builder basic_properties() const;
    V_Dynamic_Properties_Builder dynamic_properties() const;
    V_Size_And_Weight_Builder size_and_weight() const;
    V_Vehicle_Features_Builder vehicle_features() const;
    V_Owner_Information_Builder owner_information() const;
};

class Vehicle_Builder : public Vehicle_Builder_Base {
protected:
    Vehicle vehicle;
public:
    Vehicle_Builder() : Vehicle_Builder_Base(vehicle) {}
};

class V_Basic_Properties_Builder : public Vehicle_Builder_Base {
public:
    explicit V_Basic_Properties_Builder(Vehicle& vehicle) : Vehicle_Builder_Base(vehicle) {}

    V_Basic_Properties_Builder& make(const std::string& make) {
        vehicle.make = make;
        return *this;
    }

    V_Basic_Properties_Builder& model(const std::string& model) {
        vehicle.model = model;
        return *this;
    }

    V_Basic_Properties_Builder& year(int year) {
        vehicle.year = year;
        return *this;
    }

    V_Basic_Properties_Builder& price(double price) {
        vehicle.price = price;
        return *this;
    }
};

class V_Dynamic_Properties_Builder : public Vehicle_Builder_Base {
public:
    explicit V_Dynamic_Properties_Builder(Vehicle& vehicle) : Vehicle_Builder_Base(vehicle) {}

    V_Dynamic_Properties_Builder& engineSize(double engineSize) {
        vehicle.engineSize = engineSize;
        return *this;
    }

    V_Dynamic_Properties_Builder& horsepower(int horsepower) {
        vehicle.horsepower = horsepower;
        return *this;
    }

    V_Dynamic_Properties_Builder& fuelType(const std::string& fuelType) {
        vehicle.fuelType = fuelType;
        return *this;
    }
};

class V_Size_And_Weight_Builder : public Vehicle_Builder_Base {
public:
    explicit V_Size_And_Weight_Builder(Vehicle& vehicle) : Vehicle_Builder_Base(vehicle) {}

    V_Size_And_Weight_Builder& length(double length) {
        vehicle.length = length;
        return *this;
    }

    V_Size_And_Weight_Builder& width(double width) {
        vehicle.width = width;
        return *this;
    }

    V_Size_And_Weight_Builder& height(double height) {
        vehicle.height = height;
        return *this;
    }

    V_Size_And_Weight_Builder& curbWeight(double curbWeight) {
        vehicle.curbWeight = curbWeight;
        return *this;
    }
};

class V_Vehicle_Features_Builder : public Vehicle_Builder_Base {
public:
    explicit V_Vehicle_Features_Builder(Vehicle& vehicle) : Vehicle_Builder_Base(vehicle) {}

    V_Vehicle_Features_Builder& addFeature(const std::string& feature) {
        vehicle.features.push_back(feature);
        return *this;
    }

    V_Vehicle_Features_Builder& addSpecification(const std::string& key, const std::string& value) {
        vehicle.specifications[key] = value;
        return *this;
    }

    V_Vehicle_Features_Builder& addSafetyFeature(const std::string& safetyFeature) {
        vehicle.safetyFeatures.insert(safetyFeature);
        return *this;
    }
};

class V_Owner_Information_Builder : public Vehicle_Builder_Base {
public:
    explicit V_Owner_Information_Builder(Vehicle& vehicle) : Vehicle_Builder_Base(vehicle) {}

    V_Owner_Information_Builder& addPreviousOwner(const std::string& owner) {
        vehicle.previousOwners.push_back(owner);
        return *this;
    }

    V_Owner_Information_Builder& addOwnerDetail(const std::string& key, const std::string& value) {
        vehicle.ownerDetails[key] = value;
        return *this;
    }
};

Vehicle_Builder Vehicle::create() {
    return Vehicle_Builder();
}

V_Basic_Properties_Builder Vehicle_Builder_Base::basic_properties() const {
    return V_Basic_Properties_Builder(vehicle);
}

V_Dynamic_Properties_Builder Vehicle_Builder_Base::dynamic_properties() const {
    return V_Dynamic_Properties_Builder(vehicle);
}

V_Size_And_Weight_Builder Vehicle_Builder_Base::size_and_weight() const {
    return V_Size_And_Weight_Builder(vehicle);
}

V_Vehicle_Features_Builder Vehicle_Builder_Base::vehicle_features() const {
    return V_Vehicle_Features_Builder(vehicle);
}

V_Owner_Information_Builder Vehicle_Builder_Base::owner_information() const {
    return V_Owner_Information_Builder(vehicle);
}

int main() {
    Vehicle vehicle = Vehicle::create()
        .basic_properties().make("丰田").model("凯美瑞").year(2020).price(30000.0)
        .dynamic_properties().engineSize(2.5).horsepower(203).fuelType("汽油")
        .size_and_weight().length(4.8).width(1.8).height(1.4).curbWeight(1500)
        .vehicle_features().addFeature("天窗").addSpecification("变速器", "自动").addSafetyFeature("ABS")
        .owner_information().addPreviousOwner("约翰·多伊").addOwnerDetail("当前车主", "简·多伊");

    vehicle.printVehicleInfo();

    return 0;
}

~~~

# 四、总结
对于这三种构造器，我还是喜欢组合和流式，因为个人觉得他是真正做到把对象的创建和对象的使用分离开来的！

对于friend关键字，我平时也是可以用的，不过要更加深思熟虑，破坏封装性也是真的，但也不是不用这个C++存在的特性。

最后！作者也是刚学，写下对此设计模式的疑惑，如有错误，请指正！
点个赞吧！