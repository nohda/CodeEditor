/*
���ϸ� : Iterator.h
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �����
��� : Iterator������ ���� �ݺ��� Iterator�ȿ��� �ذ�

*/
//Iterator.h

#pragma once
#ifndef _ITERATOR_H
#define _IETRATOR_H

template <typename T>
class Iterator {
public:
	virtual ~Iterator() = 0;
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual T CurrentItem() const = 0;

protected:
	Iterator();
};

template<typename T>
Iterator<T>::Iterator() {

}

template <typename T>
Iterator<T>::~Iterator() {

}
#endif //_ITERATOR_H
