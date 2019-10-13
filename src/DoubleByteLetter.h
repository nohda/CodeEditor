/*
파일명 : DoubleByteLetter.h
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : DoubleByteLetter의 생성자, 매개변수를 갖는 생성자, 복사생성자, 소멸자, 클론(prototype pattern), 문자열 만들기, 연산자 =선언
수정 : -
*/
//DoubleByteLetter.h

#pragma once
#ifndef _DOUBLEBYTELETTER_H
#define _DOUBLEBYTELETTER_H
#include "Letter.h"
#include <string>
using namespace std;

class DoubleByteLetter :public Letter {
public:
	DoubleByteLetter();
	DoubleByteLetter(char(*content));
	DoubleByteLetter(const DoubleByteLetter& source);
	virtual ~DoubleByteLetter();
	virtual string GetContents();
	virtual Glyph* Clone();
	DoubleByteLetter& operator=(const DoubleByteLetter& source);
	char* GetContent()const;
private:
	char content[2];
};
inline char* DoubleByteLetter::GetContent()const {
	return const_cast<char*>(this->content);
}
#endif //_DOUBLEBYTELETTER_H