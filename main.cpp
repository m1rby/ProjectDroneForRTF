#include <iostream>
#include <string>

using namespace std;

class Drone {
protected:
    string model;
    int weight;
    float maxSpeed;
    int batteryLife;
    int currentBattery;

public:
    Drone(string model, int weight, float maxSpeed, int batteryLife)
        : model(model), weight(weight), maxSpeed(maxSpeed), batteryLife(batteryLife), currentBattery(batteryLife) {}

    virtual void printInfo() {
        cout << "Модель: " << model << endl;
        cout << "Вес: " << weight << " кг" << endl;
        cout << "Максимальная скорость: " << maxSpeed << " м/с" << endl;
        cout << "Максимальный заряд батареи: " << batteryLife << "процентов" << endl;
        cout << "Заряд батареи: " << currentBattery << " процентов" << endl;
    }

    virtual void fly() {
        if (currentBattery > 0) {
            cout << "Дрон взлетел." << endl;
        } else {
            cout << "Дрон не может взлететь. Батарея разряжена." << endl;
        }
    }

    virtual void chargeBattery() {
        currentBattery = batteryLife;
        cout << "Батарея дрона полностью заряжена." << endl;
    }

    virtual ~Drone() {} // Виртуальный деструктор
};

class ScoutDrone : public Drone {
private:
    int cameraResolution;

public:
    ScoutDrone(string model, int weight, float maxSpeed, int batteryLife, int cameraResolution)
        : Drone(model, weight, maxSpeed, batteryLife), cameraResolution(cameraResolution) {
        currentBattery = 20;
        }

    void printInfo() override {
        Drone::printInfo();
        cout << "Разрешение камеры: " << cameraResolution << " МП" << endl;
    }

    void fly() override {
        if (currentBattery >= 25) {
            cout << "Разведывательный дрон начал разведку местности." << endl;
            currentBattery -= 20;
        } else {
            cout << "Разведывательный дрон не может взлететь. Заряда слишком мало. ОПАСНО!!!" << endl;
        }
    }
};

class CargoDrone : public Drone {
private:
    float maxCargoWeight;

public:
    CargoDrone(string model, int weight, float maxSpeed, int batteryLife, float maxCargoWeight)
        : Drone(model, weight, maxSpeed,  batteryLife), maxCargoWeight(maxCargoWeight) {
        currentBattery = 35; // Установим начальный заряд
    }

    void printInfo() override {
        Drone::printInfo();
        cout << "Максимальный вес груза: " << maxCargoWeight << " кг" << endl;
    }

    void fly() override {
        if (currentBattery >= 20) {
            cout << "Грузовой дрон выполняет доставку груза." << endl;
            currentBattery -= 20;
        } else {
            cout << "Грузовой дрон не может взлететь. Заряд меньше 20 процентов. ОПАСНО" << endl;
        }
    }
};

int main() {
    return 0;
}
