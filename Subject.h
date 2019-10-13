/*
���ϸ� : Subject.h
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �迵��
��� :
���� :
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