/*
파일명 : SingleByteLetter.h
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : SingleByteCharacter의 생성자, 매개변수를 갖는 생성자, 복사생성자, 소멸자, 클론(prototype pattern), 문자열 만들기, 연산자 =선언
수정 : -
*/
//SingleByteLetter.h

#pragma once
#ifndef _SINGLEBYTELETTER_H
#define _SINGLEBYTELETTER_H
#include "Letter.h"
#include <string>
using namespace std;

class SingleByteLetter :public Letter {
public:
	SingleByteLetter();
	SingleByteLetter(char content);
	SingleByteLetter(const SingleByteLetter& source);
	virtual ~SingleByteLetter();
	virtual string GetContents();
	virtual Glyph* Clone();
	SingleByteLetter& operator=(const SingleByteLetter& source);
	char GetContent()const;

private:
	char content;
};

inline char SingleByteLetter::GetContent() const {
	return this->content;
}
#endif //_SINGLEBYTELETTER_H
 