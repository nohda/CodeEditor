// DoubleByteLetter.cpp
/*
파일명 : DoubleByteLetter.cpp
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : DoubleByteLetter의 생성자, 매개변수를 갖는 생성자, 복사생성자, 소멸자, 클론(prototype pattern), 문자열 만들기, 연산자 =선언
수정 : -
*/

#include "DoubleByteLetter.h"

/*
함수명: DoubleByteLetter
기능: 디폴트 생성자
*/
DoubleByteLetter::DoubleByteLetter() {
	this->content[0] = ' ';
	this->content[1] = ' ';
}

/*
함수명: DoubleByteLetter
기능: 매개변수 생성자
*/
DoubleByteLetter::DoubleByteLetter(char(*content)) {
	this->content[0] = content[0];
	this->content[1] = content[1];
}

/*
함수명: DoubleByteLetter
기능: 복사 생성자
*/
DoubleByteLetter::DoubleByteLetter(const DoubleByteLetter& source) {
	this->content[0] = source.content[0];
	this->content[1] = source.content[1];
}

/*
함수명: ~DoubleByteLetter
기능: 소멸자
*/
DoubleByteLetter::~DoubleByteLetter() {
}

/*
함수명: GetContents
기능: 문자열을 만든다
*/
string DoubleByteLetter::GetContents() {
	char buffer[3];
	buffer[0] = this->content[0];
	buffer[1] = this->content[1];
	buffer[2] = '\0';
	return string(buffer);
}

/*
함수명: Clone
기능: 복사한다
*/
Glyph* DoubleByteLetter::Clone() {
	return new DoubleByteLetter(*this);
}

/*
함수명: operator=
기능: 치환 연산자
*/
DoubleByteLetter& DoubleByteLetter::operator=(const DoubleByteLetter& source) {
	this->content[0] = source.content[0];
	this->content[0] = source.content[1];
	return *this;
}