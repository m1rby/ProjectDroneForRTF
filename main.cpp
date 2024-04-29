#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>   // ��� ������������� ���������� ��������� �����
#include <cstdlib> // ��� ������������� rand()
#include <cmath> // ��� ������� (������� 9)

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

template<class Type>
class DroneIterator { //����� ����� ��� ���������
protected:
    DroneIterator(){}
public:
    virtual void first() = 0; // ���������� �������� �� ������ �������
    virtual void next() = 0;  // ������� � ���������� ��������
    virtual bool hasNext() = 0; // ���������, ���� �� ��������� �������
    virtual bool isDone() const = 0; // ���������, ����� �� ����������
    virtual Type getCurrent() = 0; // �������� ������� �������
    virtual ~DroneIterator() {} // ����������� ����������
};


class DroneContainer {
public:
    virtual void addDrone(Drone *drone) = 0;
    virtual void removeDrone(Drone *drone) = 0;
    virtual void printAllDrones() = 0;
    virtual DroneIterator<Drone *> *getIterator() = 0;
    virtual ~DroneContainer() {}
};

class VectorDroneIterator : public DroneIterator<Drone *> { //��� ������� ������
private:
    vector<Drone *> &drones; // ������ �� ������ ������
    size_t index; // ������ �������� ��������

public:
    VectorDroneIterator(vector<Drone *> &drones) : drones(drones), index(0) {}

    void first() override {
        index = 0; // ������������� �������� �� ������ �������
    }

    void next() override {
        index++; // ��������� � ���������� ��������
    }

    bool hasNext() override {
        return index < drones.size(); // ���������, ���� �� ��������� �������
    }

    bool isDone() const override {
        return index >= drones.size(); // ���������, ����� �� �� ������� ����������
    }

    Drone* getCurrent() override {
        if (index < drones.size()) {
            return drones[index]; // ���������� ������� �������
        }
        return nullptr;
    }
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
        for (auto drone : drones) {
            drone->printInfo();
        }
    }

    VectorDroneIterator *getIterator() override {
        return new VectorDroneIterator(drones);
    }
};

class ListDroneIterator : public DroneIterator<Drone *> { //��� ������ ������
private:
    list<Drone *> *drones; // ������ �� ������ ������
    list<Drone *>::const_iterator it; // �������� ��� ������

public:
    ListDroneIterator(list<Drone *> *drones) : drones(drones) {}

    void first() override {
        it = drones->begin(); // ������������� �������� �� ������ ������
    }

    void next() override {
        it++; // ��������� � ���������� ��������
    }

    bool hasNext() override {
        return it != drones->end(); // ���������, ���� �� ��������� �������
    }

    bool isDone() const override {
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

    DroneIterator<Drone *> *getIterator() override {
        return new ListDroneIterator(&drones);
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

    bool isDone() const override {
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

    bool isDone() const override {
        return iterator->isDone();
    }

    Drone* getCurrent() override {
        return iterator->getCurrent();
    }
};

class VectorMaxSpeedFilterIteratorDecorator : public DroneIterator<Drone *> {
private:
    VectorDroneIterator *iterator;
    float maxSpeed;

public:
    VectorMaxSpeedFilterIteratorDecorator(VectorDroneIterator *iterator, float maxSpeed)
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

    bool isDone() const override {
        return iterator->isDone();
    }

    Drone* getCurrent() override {
        return iterator->getCurrent();
    }
};

template<class Factory>
class DroneFactory {
public:
    Factory* create(string model, int weight, float maxSpeed, int batteryLife, int currentBattery) const {
        return new Factory(model, weight, maxSpeed, batteryLife, currentBattery);
    }
};

template <class ContainerType>
void filterAndPrintDronesByMaxSpeed(ContainerType* container, float maxSpeed) {
    // �������� �������� ���������� ������
    auto iterator = container->getIterator();

    // ������� ��������� ��� ���������� �� ������������ ��������
    auto vectorIterator = dynamic_cast<VectorDroneIterator *>(iterator);
    if (vectorIterator) {
        auto speedFilterDecorator = new VectorMaxSpeedFilterIteratorDecorator(vectorIterator, maxSpeed);
        iterator = speedFilterDecorator;
    } else {

    }
    // ������� ���������� � ������ � ������ ���������� �� ������������ ��������
    cout << "����� � ������������ ��������� �� ����� " << maxSpeed << " �/�:" << endl;
    while (!iterator->isDone()) {
        Drone *currentDrone = iterator->getCurrent();
        if (currentDrone) {
            // ��������� �������� ����� �������, ��� ������������ �������� ����� ������ ��� ����� ��������
            if (currentDrone->getMaxSpeed() < maxSpeed) {
                currentDrone->printInfo();
            }
        }
        iterator->next();
    }
}



int main() {
    cout << "-------------------------" << endl;
    setlocale(LC_ALL,"");
    srand(time(0));
    // ������� ��������� ������� ������
    DroneContainer *container = new VectorDroneContainer;


    // ������� ��������� ������ � ��������� �� � ���������
    DroneFactory<ScoutDrone> scoutFactory;
    DroneFactory<CargoDrone> cargoFactory;

    // ��������� ���������� ����� ������ �� 1 �� 10
int numDrones = rand() % 10 + 1;

for (int i = 0; i < numDrones; ++i) {
    // ��������� ��������� ������, ����, ������������ ��������,
    // ����� ������� � �������� ������ ������� ��� ������� �����
    string model = "Model" + to_string(i);
    int weight = rand() % 1000 + 500;
    float maxSpeed = (rand() % 50 + 10) / 10.0f;
    int batteryLife = rand() % 200 + 100;
    int currentBattery = rand() % 200 + 100;

    Drone* drone;
    if (rand() % 2 == 0) {
        drone = scoutFactory.create(model, weight, maxSpeed, batteryLife, currentBattery);
    } else {
        drone = cargoFactory.create(model, weight, maxSpeed, batteryLife, currentBattery);
    }
    container->addDrone(drone);
}


    // �������� ������� ��� ���������� � ������ ������ �� ������������ ��������
    float maxSpeedFilter = 5.00f;
    filterAndPrintDronesByMaxSpeed(container, maxSpeedFilter);

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

    delete container; // ������� ������ �� ����������

    return 0;
}
