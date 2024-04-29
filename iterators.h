#ifndef ITERATORS_H
#define ITERATORS_H

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

#endif // ITERATORS_H
