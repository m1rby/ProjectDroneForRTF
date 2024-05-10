#ifndef ITERATORS_H
#define ITERATORS_H
#include "classes.h"
using namespace std;
template<class Type>
class DroneIterator { //общий класс для итератора
protected:
    DroneIterator(){}
public:
    virtual void first() = 0; // Установить итератор на первый элемент
    virtual void next() = 0;  // Перейти к следующему элементу
    virtual bool hasNext() = 0; // Проверить, есть ли следующий элемент
    virtual bool isDone() const = 0; // Проверить, конец ли контейнера
    virtual Type getCurrent() = 0; // Получить текущий элемент
    virtual ~DroneIterator() {} // Виртуальный деструктор
};

class VectorDroneIterator : public DroneIterator<Drone *> { //для вектора дронов
private:
    vector<Drone *> &drones; // Ссылка на вектор дронов
    size_t index; // Индекс текущего элемента

public:
    VectorDroneIterator(vector<Drone *> &drones) : drones(drones), index(0) {}

    void first() override {
        index = 0; // Устанавливаем итератор на начало вектора
    }

    void next() override {
        index++; // Переходим к следующему элементу
    }

    bool hasNext() override {
        return index < drones.size(); // Проверяем, есть ли следующий элемент
    }

    bool isDone() const override {
        return index >= drones.size(); // Проверяем, дошли ли до предела контейнера
    }

    Drone* getCurrent() override {
        if (index < drones.size()) {
            return drones[index]; // Возвращаем текущий элемент
        }
        return nullptr;
    }
};

class ListDroneIterator : public DroneIterator<Drone *> { //для списка дронов
private:
    list<Drone *> *drones; // Ссылка на список дронов
    list<Drone *>::const_iterator it; // Итератор для списка

public:
    ListDroneIterator(list<Drone *> *drones) : drones(drones) {}

    void first() override {
        it = drones->begin(); // Устанавливаем итератор на начало списка
    }

    void next() override {
        it++; // Переходим к следующему элементу
    }

    bool hasNext() override {
        return it != drones->end(); // Проверяем, есть ли следующий элемент
    }

    bool isDone() const override {
        return it == drones->end(); // Проверяем, дошли ли до предела контейнера
    }

    Drone* getCurrent() override {
        if (it != drones->end()) {
            return *it; // Возвращаем текущий элемент
        }
        return nullptr;
    }
};
#endif // ITERATORS_H
