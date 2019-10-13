/*
���ϸ� : ArrayIterator.h
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �����
��� : ArrayIterator������ ���� �ݺ��� ArrayIterator�ȿ��� �ذ�

*/
//ArrayIterator.h

#pragma once
#ifndef _ARRAYITERATOR_H
#define _ARRAYITERATOR_H

#include "Iterator.h"
#include "Array.h"

typedef signed long int Long;

template <typename T>
class ArrayIterator :public Iterator<T> {
public:
	ArrayIterator(Array<T>* aArray);
	virtual void First();
	virtual void Next();
	virtual bool IsDone() const;
	virtual T CurrentItem() const;

private:
	Array<T>*array;
	Long current;
};

template<typename T>
ArrayIterator<T>::ArrayIterator(Array<T>* aArray) :array(aArray), current(0) {

}

template <typename T>
void ArrayIterator<T>::First() {
	this->current = 0;
}

template <typename T>
void ArrayIterator<T>::Next() {
	this->current++;
}


template <typename T>
bool ArrayIterator<T>::IsDone()const {
	return this->current >= this->array->GetLength();
}

template <typename T>
T ArrayIterator<T>::CurrentItem() const {
	T index = 0;

	if (!IsDone()) {
		index = this->array->GetAt(current);
	}
	return index;
}
#endif //_ARRAYITERATOR_H
