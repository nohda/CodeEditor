/*
파일명 : Iterator.h
작성일자 : 2019년 03월 29일
작성자 : 허수진
기능 : Iterator패턴을 적용 반복을 Iterator안에서 해결

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
