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
            cout << "Разведывательный дрон не может взлететь. Время полета меньше 25 минут. ОПАСНО!!!" << endl;
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
    setlocale(LC_ALL,"");
    int choice;

    do {
        cout << "Выберите дрон:" << endl;
        cout << "1. Разведывательный дрон" << endl;
        cout << "2. Грузовой дрон" << endl;
        cout << "0. Выйти из программы" << endl;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        Drone *selectedDrone;
        if (choice == 1) {
            selectedDrone = new ScoutDrone("Scout X1", 2, 15.5, 100, 100);
        } else if (choice == 2) {
            selectedDrone = new CargoDrone("Cargo Master 5000", 5, 10.0, 100, 100);
        } else {
            cout << "Неверный выбор." << endl;
            continue;
        }

        selectedDrone->printInfo();

        do {
            cout << "Выберите действие:" << endl;
            cout << "1. Проверить заряд батареи" << endl;
            cout << "2. Зарядить батарею" << endl;
            cout << "3. Взлететь" << endl;
            cout << "0. Выбрать другой дрон" << endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    selectedDrone->printInfo();
                    break;
                case 2:
                    selectedDrone->chargeBattery();
                    break;
                case 3:
                    selectedDrone->fly();
                    break;
                case 0:
                    break;
                default:
                    cout << "Неверный выбор." << endl;
            }
        } while (choice != 0);

        delete selectedDrone;
    } while (true);

    return 0;
}
