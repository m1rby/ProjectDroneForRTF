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
        cout << "Максимальный заряд батареи: " << batteryLife << " процентов" << endl;
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

int main() {
    return 0;
}
