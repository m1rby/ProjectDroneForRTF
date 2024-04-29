#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
#include "iterators.h"

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

    int getWeight() const {
        return weight;
    }

    int getCurrentBattery() const {
        return currentBattery;
    }

    int getMaxSpeed() const {
    return maxSpeed;
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
            cout << "Разведывательный дрон начал разведку местности. ... Разведовательный дрон вернулся." << endl;
            currentBattery -= 20;
        } else {
            cout << "Разведывательный дрон не может взлететь. Мало заряда. ОПАСНО!!!" << endl;
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
            cout << "Грузовой дрон выполняет доставку груза. ... Грузовой дрон вернулся" << endl;
            currentBattery -= 20;
        } else {
            cout << "Грузовой дрон не может взлететь. Заряд меньше 20 процентов. ОПАСНО" << endl;
        }
    }
};

class DroneContainer {
public:
    virtual void addDrone(Drone *drone) = 0;
    virtual void removeDrone(Drone *drone) = 0;
    virtual void printAllDrones() = 0;
    virtual DroneIterator<Drone *> *getIterator() = 0;
    virtual ~DroneContainer() {}
};

class VectorDroneContainer : public DroneContainer {
private:
    vector<Drone *> drones;

public:
    void addDrone(Drone *drone) override {
        drones.push_back(drone);
    }

    void removeDrone(Drone *drone) override {
        drones.erase(remove(drones.begin(), drones.end(), drone), drones.end());
    }

    void printAllDrones() override {
        for (auto drone : drones) { // Проходим по всем дронам в векторе
            drone->printInfo(); // Выводим информацию о каждом дроне
        }
    }
};

class ListDroneIterator : public DroneIterator<Drone *> { //для списка дронов
private:
    list<Drone *> *drones; // Ссылка на список дронов
    list<Drone *>::const_iterator it; // Итератор для списка

public:
    ListDroneIterator(list<Drone *> *drones) : drones(drones) {}

    void first() {
        it = drones->begin(); // Устанавливаем итератор на начало списка
    }

    void next() {
        it++; // Переходим к следующему элементу
    }

    bool hasNext() {
        return it != drones->end(); // Проверяем, есть ли следующий элемент
    }

    bool isDone() {
        return it == drones->end(); // Проверяем, дошли ли до предела контейнера
    }

    Drone* getCurrent() override {
        if (it != drones->end()) {
            return *it; // Возвращаем текущий элемент
        }
        return nullptr;
    }
};

class ListDroneContainer : public DroneContainer {
private:
    list<Drone *> drones;

public:
    void addDrone(Drone *drone) override {
        drones.push_back(drone);
    }

    void removeDrone(Drone *drone) override {
        drones.remove(drone);
    }

    void printAllDrones() override {
        for (auto drone : drones) { // Проходим по всем дронам в списке
            drone->printInfo(); // Выводим информацию о каждом дроне
        }
    }
};



class VectorDroneIterator : public DroneIterator<Drone *> { //для вектора дронов
private:
    vector<Drone *> &drones; // Ссылка на вектор дронов
    size_t amount;
    size_t index; // Индекс текущего элемента

public:
    VectorDroneIterator(vector<Drone *> &drones) : drones(drones), amount(drones.size()), index(0) {}

    void first() {
        index = 0; // Устанавливаем итератор на начало вектора
    }

    void next() {
        index++; // Переходим к следующему элементу
    }

    bool hasNext() {
        return index < drones.size(); // Проверяем, есть ли следующий элемент
    }

    bool isDone() {
        return index>=amount; // Проверяем, дошли ли до предела контейнера
    }

    Drone* getCurrent() {
        if (index < drones.size()) {
            return drones[index]; // Возвращаем текущий элемент
        }
        return nullptr;
    }
};

class WeightFilterIteratorDecorator : public DroneIterator<Drone *> { //декаратор фильтр по весу
private:
    DroneIterator<Drone *> *iterator;
    int maxWeight;

public:
    WeightFilterIteratorDecorator(DroneIterator<Drone *> *iterator, int maxWeight)
        : iterator(iterator), maxWeight(maxWeight) {}

    void first() override {
        iterator->first();
    }

    void next() override {
        iterator->next();
    }

    bool hasNext() override {
        while (iterator->hasNext()) {
            Drone *currentDrone = iterator->getCurrent();
            if (currentDrone && currentDrone->getWeight() <= maxWeight) {
                return true;
            }
            iterator->next();
        }
        return false;
    }

    bool isDone() {
        return iterator->isDone();
    }

    Drone* getCurrent() override {
        return iterator->getCurrent();
    }
};

class BatteryLevelFilterIteratorDecorator : public DroneIterator<Drone *> { //декоратор по уровню батареи
private:
    DroneIterator<Drone *> *iterator;
    int minBatteryLevel;

public:
    BatteryLevelFilterIteratorDecorator(DroneIterator<Drone *> *iterator, int minBatteryLevel)
        : iterator(iterator), minBatteryLevel(minBatteryLevel) {}

    void first() override {
        iterator->first();
    }

    void next() override {
        iterator->next();
    }

    bool hasNext() override {
        while (iterator->hasNext()) {
            Drone *currentDrone = iterator->getCurrent();
            if (currentDrone && currentDrone->getCurrentBattery() >= minBatteryLevel) {
                return true;
            }
            iterator->next();
        }
        return false;
    }

    bool isDone() {
        return iterator->isDone();
    }

    Drone* getCurrent() override {
        return iterator->getCurrent();
    }
};

class MaxSpeedFilterIteratorDecorator : public DroneIterator<Drone *> {
private:
    DroneIterator<Drone *> *iterator;
    float maxSpeed;

public:
    MaxSpeedFilterIteratorDecorator(DroneIterator<Drone *> *iterator, float maxSpeed)
        : iterator(iterator), maxSpeed(maxSpeed) {}

    void first() override {
        iterator->first();
    }

    void next() override {
        iterator->next();
    }

    bool hasNext() override {
        while (iterator->hasNext()) {
            Drone *currentDrone = iterator->getCurrent();
            if (currentDrone && currentDrone->getMaxSpeed() <= maxSpeed) {
                return true;
            }
            iterator->next();
        }
        return false;
    }

    bool isDone() {
        return iterator->isDone();
    }

    Drone* getCurrent() override {
        return iterator->getCurrent();
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
            cout << "1. Проверить дрон" << endl;
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

