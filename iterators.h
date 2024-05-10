#ifndef ITERATORS_H
#define ITERATORS_H
#include "classes.h"
using namespace std;
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
#endif // ITERATORS_H
