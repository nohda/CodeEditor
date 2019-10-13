/*
���ϸ� : Observer.h
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �迵��
��� :
���� :
*/

#pragma once

#ifndef _OBSERVER_H
#define _OBSERVER_H

class Subject;
class Observer {
public:
	virtual ~Observer();
	virtual void Update()=0;

protected:
	Observer();
};

#endif //_OBSERVER_H