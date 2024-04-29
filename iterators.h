#ifndef ITERATORS_H
#define ITERATORS_H

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

#endif // ITERATORS_H
