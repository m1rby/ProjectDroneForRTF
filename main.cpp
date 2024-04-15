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

    virtual ~Drone() {} // ����������� ����������
};

int main() {
    return 0;
}
