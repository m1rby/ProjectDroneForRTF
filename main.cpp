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
        cout << "������: " << model << endl;
        cout << "���: " << weight << " ��" << endl;
        cout << "������������ ��������: " << maxSpeed << " �/�" << endl;
        cout << "������������ ����� �������: " << batteryLife << " ���������" << endl;
        cout << "����� �������: " << currentBattery << " ���������" << endl;
    }

    virtual void fly() {
        if (currentBattery > 0) {
            cout << "���� �������." << endl;
        } else {
            cout << "���� �� ����� ��������. ������� ���������." << endl;
        }
    }

    virtual void chargeBattery() {
        currentBattery = batteryLife;
        cout << "������� ����� ��������� ��������." << endl;
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

    virtual ~Drone() {} // ����������� ����������
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
        cout << "���������� ������: " << cameraResolution << " ��" << endl;
    }

    void fly() override {
        if (currentBattery >= 25) {
            cout << "���������������� ���� ����� �������� ���������. ... ���������������� ���� ��������." << endl;
            currentBattery -= 20;
        } else {
            cout << "���������������� ���� �� ����� ��������. ���� ������. ������!!!" << endl;
        }
    }
};

class CargoDrone : public Drone {
private:
    float maxCargoWeight;

public:
    CargoDrone(string model, int weight, float maxSpeed, int batteryLife, float maxCargoWeight)
        : Drone(model, weight, maxSpeed,  batteryLife), maxCargoWeight(maxCargoWeight) {
        currentBattery = 35; // ��������� ��������� �����
    }

    void printInfo() override {
        Drone::printInfo();
        cout << "������������ ��� �����: " << maxCargoWeight << " ��" << endl;
    }

    void fly() override {
        if (currentBattery >= 20) {
            cout << "�������� ���� ��������� �������� �����. ... �������� ���� ��������" << endl;
            currentBattery -= 20;
        } else {
            cout << "�������� ���� �� ����� ��������. ����� ������ 20 ���������. ������" << endl;
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
        for (auto drone : drones) { // �������� �� ���� ������ � �������
            drone->printInfo(); // ������� ���������� � ������ �����
        }
    }
};

class ListDroneIterator : public DroneIterator<Drone *> { //��� ������ ������
private:
    list<Drone *> *drones; // ������ �� ������ ������
    list<Drone *>::const_iterator it; // �������� ��� ������

public:
    ListDroneIterator(list<Drone *> *drones) : drones(drones) {}

    void first() {
        it = drones->begin(); // ������������� �������� �� ������ ������
    }

    void next() {
        it++; // ��������� � ���������� ��������
    }

    bool hasNext() {
        return it != drones->end(); // ���������, ���� �� ��������� �������
    }

    bool isDone() {
        return it == drones->end(); // ���������, ����� �� �� ������� ����������
    }

    Drone* getCurrent() override {
        if (it != drones->end()) {
            return *it; // ���������� ������� �������
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
        for (auto drone : drones) { // �������� �� ���� ������ � ������
            drone->printInfo(); // ������� ���������� � ������ �����
        }
    }
};



class VectorDroneIterator : public DroneIterator<Drone *> { //��� ������� ������
private:
    vector<Drone *> &drones; // ������ �� ������ ������
    size_t amount;
    size_t index; // ������ �������� ��������

public:
    VectorDroneIterator(vector<Drone *> &drones) : drones(drones), amount(drones.size()), index(0) {}

    void first() {
        index = 0; // ������������� �������� �� ������ �������
    }

    void next() {
        index++; // ��������� � ���������� ��������
    }

    bool hasNext() {
        return index < drones.size(); // ���������, ���� �� ��������� �������
    }

    bool isDone() {
        return index>=amount; // ���������, ����� �� �� ������� ����������
    }

    Drone* getCurrent() {
        if (index < drones.size()) {
            return drones[index]; // ���������� ������� �������
        }
        return nullptr;
    }
};

class WeightFilterIteratorDecorator : public DroneIterator<Drone *> { //��������� ������ �� ����
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

class BatteryLevelFilterIteratorDecorator : public DroneIterator<Drone *> { //��������� �� ������ �������
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
        cout << "�������� ����:" << endl;
        cout << "1. ���������������� ����" << endl;
        cout << "2. �������� ����" << endl;
        cout << "0. ����� �� ���������" << endl;
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
            cout << "�������� �����." << endl;
            continue;
        }

        selectedDrone->printInfo();

        do {
            cout << "�������� ��������:" << endl;
            cout << "1. ��������� ����" << endl;
            cout << "2. �������� �������" << endl;
            cout << "3. ��������" << endl;
            cout << "0. ������� ������ ����" << endl;
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
                    cout << "�������� �����." << endl;
            }
        } while (choice != 0);

        delete selectedDrone;
    } while (true);

    return 0;
}

