/*
파일명 : Memo.h
작성일자 : 2019년 03월27일
작성자 : 허수진
기능 : 생성자, 복사생성자, 소멸자, , 문자열 만들기, 연산자= 선언
수정 : 20190410 LeftWord, RightWord 연산추가
*/
//Memo.h

#pragma once
#ifndef _MEMO_H
#define _MEMO_H
#include "Composite.h"

typedef signed long int Long;

class Memo :public Composite {
public:
	Memo(Long capacity = 256);
	Memo(const Memo& source);
	virtual ~Memo();
	virtual Long Next();
	virtual Long Last();
	virtual Long LeftWord();
	virtual Long RightWord();
	virtual Glyph* Clone();
	virtual string GetContents();
	Memo& operator=(const Memo& source);

};
#endif //_MEMO_H