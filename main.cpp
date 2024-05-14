#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>   // ��� ������������� ���������� ��������� �����
#include <cstdlib> // ��� ������������� rand()
#include <cmath> // ��� ������� (������� 9)
#include <string>
#include "iterators.h"
#include "decorators.h"
#include "classes.h"
#include "sqlite3.h"
#include <cstdio> // ��� ������������� ������� remove()
#include "db.h"

using namespace std;

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
        for (auto drone : drones) {
            drone->printInfo();
        }
    }

    VectorDroneIterator *getIterator() override {
        return new VectorDroneIterator(drones);
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
 setlocale(LC_ALL,"");
    cout << "--------------��� ����� �� ���� ������------------------" << endl;
    initializeDroneDatabase();
    // ����� ����������� ���� ������
    printDroneDatabaseContents();
    // ������� ��������� ������� ������
    cout << "-------------------------" << endl;
    srand(time(0));

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
    int batteryLife = 100;
    int currentBattery = rand() % 100 + 1;

    Drone* drone;
    if (rand() % 2 == 0) {
        drone = scoutFactory.create(model, weight, maxSpeed, batteryLife, currentBattery);
    } else {
        drone = cargoFactory.create(model, weight, maxSpeed, batteryLife, currentBattery);
    }
    container->addDrone(drone);
}


    // �������� ������� ��� ���������� � ������ ������ �� ������������ ��������
    float maxSpeedFilter = 5.00f; //�������� �������� �� ������� ���������
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
