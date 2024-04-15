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
        cout << "������: " << model << endl;
        cout << "���: " << weight << " ��" << endl;
        cout << "������������ ��������: " << maxSpeed << " �/�" << endl;
        cout << "������������ ����� �������: " << batteryLife << "���������" << endl;
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
            cout << "���������������� ���� ����� �������� ���������." << endl;
            currentBattery -= 20;
        } else {
            cout << "���������������� ���� �� ����� ��������. ����� ������ ������ 25 �����. ������!!!" << endl;
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
            cout << "�������� ���� ��������� �������� �����." << endl;
            currentBattery -= 20;
        } else {
            cout << "�������� ���� �� ����� ��������. ����� ������ 20 ���������. ������" << endl;
        }
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
            cout << "1. ��������� ����� �������" << endl;
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
