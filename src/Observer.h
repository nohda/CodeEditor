/*
파일명 : Observer.h
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 :
수정 :
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