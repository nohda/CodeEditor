/*
파일명 : Letter.h
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : Letter(싱글, 더블) 추상 클래스 선언
수정 : -
*/

//Letter.h

#pragma once
#ifndef _LETTER_H
#define _LETTER_H
#include "Glyph.h"

class Letter :public Glyph {
public:
	Letter() {}
	virtual ~Letter() = 0;
};

#endif //_LETTER_H