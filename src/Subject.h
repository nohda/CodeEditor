/*
파일명 : Subject.h
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 :
수정 :
*/

#pragma once

#ifndef _SUBJECT_H
#define _SUBJECT_H

#include "Array.h"

class Observer;
class Subject {
public:
	virtual ~Subject() = 0;
	virtual void SubjectAttach(Observer *observer);
	virtual void SubjectDetach(Observer *observer);
	virtual void Notify();

protected:
	Subject(Long capacity = 256);

private:
	Array<Observer*>observers;
	Long capacity;
	Long length;
};

#endif //_SUBJECT_H