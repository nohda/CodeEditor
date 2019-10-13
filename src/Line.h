
/*
파일명 : Line.h
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : 생성자, 복사생성자, 소멸자, , 문자열 만들기, 연산자= 선언
수정 : 0329 ArrayIterator 추가하여 GetContents 정의
	   20190410 LeftWord, RightWord 연산추가
*/
//Line.h

#pragma once
#ifndef _LINE_H
#define _LINE_H
#include "Composite.h"
#include <string>

typedef signed long int Long;

class Line:public Composite {
public:
	Line(Long capacity = 256);
	Line(const Line& source);
	virtual ~Line();
	virtual Long Add(Glyph* glyph);
	virtual Long Add(Glyph *glyph, Long index);
	virtual Long LeftWord();
	virtual Long RightWord();
	virtual Glyph* Clone();
	virtual string GetContent();
	virtual string GetContents();
	Line& operator=(const Line& source);
};

#endif //_LINE_H