#ifndef DECORATORS_H
#define DECORATORS_H
#include "classes.h"
#include "iterators.h"
using namespace std;

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

    bool isDone() const override {
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

#endif // CLASSES.H
