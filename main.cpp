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
            cout << "���������������� ���� �� ����� ��������. ������ ������� ����. ������!!!" << endl;
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
    return 0;
}
