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

