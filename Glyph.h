/*
파일명 : Glyph.h
작성일자 : 2019년 03월 210일
작성자 : 허수진
기능 : CodeEditoreForm의 super 클래스 선언
수정 : 20190410 First, Previous, Next, Last, LeftWord, RightWord 연산추가
*/

//Glyph.h

#pragma once
#ifndef _GLYPH_H
#define _GLYPH_H
#include <string>

using namespace std;
typedef signed long int Long;

template <typename T>
class Iterator;

class Glyph {
public:
	Glyph() {}
	virtual ~Glyph() = 0;
	virtual Long Add(Glyph *glyph) { return -1; }
	virtual Long Add(Glyph *glyph, Long index) { return -1; }
	virtual Glyph* GetAt(Long index) { return 0; }
	virtual Long Remove(Long index) { return -1; }
	virtual Long First() { return -1; }
	virtual Long Previous() { return -1; }
	virtual Long Next() { return -1; }
	virtual Long Last() { return -1; }
	virtual Long LeftWord() { return -1; }
	virtual Long RightWord() { return -1; }
	virtual Long Move(Long index) { return -1; }
	virtual string GetContents() { return string(""); }
	virtual string GetContent() { return string(""); }
	virtual Glyph* Clone() = 0;
	virtual Iterator<Glyph*>* CreateItorator() { return 0; }
	virtual Long GetCapacity()const { return 0; }
	virtual Long GetLength()const { return 0; }
	virtual Long GetCurrent()const { return 0; }
};

#endif //_GLYPH_H