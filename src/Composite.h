/*
파일명 : Composite.h
작성일자 : 2019년 03월 27일
작성자 :허수진
기능 : Line, Memo을 포함하는 추상 클래스로 생성자, 복사생성자, 소멸자, add, getAt ,Remove,연산자 =선언 (속성: 할당량, 사용량, 현재위치)
수정 : 0328	GetContents Iterator 생성자 추가
	   20190410 FIrst, Previous, Next, Last 연산추가, private -> protected로 변경
*/
//Composite.h

#pragma once
#ifndef _COMPOSITE_H
#define _COMPOSITE_H

#include "Glyph.h"
#include "Array.h"

typedef signed long int Long;

class Composite :public Glyph {
public:
	Composite(Long capacity = 256);
	Composite(const Composite& source);
	virtual ~Composite() = 0;
	virtual Long Add(Glyph* glyph);
	virtual Long Add(Glyph *glyph, Long index);
	virtual Glyph* GetAt(Long index);
	virtual Long Remove(Long index);
	virtual Long First();
	virtual Long Previous();
	virtual Long Next();
	virtual Long Last();
	virtual Long Move(Long index);
	virtual Long GetCapacity()const;
	virtual Long GetLength()const;
	virtual Long GetCurrent()const;
	virtual Iterator<Glyph*>* CreateItorator();
	Composite& operator=(const Composite& source);
	Glyph * operator[](Long index);

protected:
	Array<Glyph*>glyphs;
	Long capacity;
	Long length;
	Long current;
};

inline Long Composite::GetCapacity()const {
	return this->capacity;
}
inline Long Composite::GetLength()const {
	return this->length;
}
inline Long Composite::GetCurrent()const {
	return this->current;
}
#endif //_COMPOSITE_H