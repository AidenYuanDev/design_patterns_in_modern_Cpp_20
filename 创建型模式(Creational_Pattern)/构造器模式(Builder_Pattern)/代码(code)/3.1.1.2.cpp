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
