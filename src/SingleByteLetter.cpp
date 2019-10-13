//SingleByteLetter.cpp
/*
파일명 : SingleByteLetter.cpp
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : SingleByteCharacter의 생성자, 매개변수를 갖는 생성자, 복사생성자, 소멸자, 클론(prototype pattern), 문자열 만들기, 연산자 =정의
수정 : -
*/

#include "SingleByteLetter.h"

/*
함수명: SingleByteLetter
기능: 디폴트 생성자
*/
SingleByteLetter::SingleByteLetter() {
	this->content = ' ';
}

/*
함수명: SingleByteLetter
기능: 매개변수 생성자
*/
SingleByteLetter::SingleByteLetter(char content) {
	this->content = content;
}

/*
함수명: SingleByteLetter
기능: 복사 생성자
*/
SingleByteLetter::SingleByteLetter(const SingleByteLetter& source) {
	this->content = source.content;
}

/*
함수명: ~SingleByteLetter
기능: 소멸자
*/
SingleByteLetter::~SingleByteLetter(){
}


/*
함수명: Gecontents
기능: 문자를 만든다
*/
string SingleByteLetter::GetContents() {
	char buffer[9]; //탭문자, 스페이스바 8개 NULL문자 1개
	Long i;

	if (this->content == '\t') {
		for (i = 0; i < 8; i++) {
			buffer[i] = ' ';
		}
			buffer[8] = '\0';
	}
	else {
		buffer[0] = this->content;
		buffer[1] = '\0';
	}

	return string(buffer);
}

/*
함수명: Clone
기능: 복사한다
*/
Glyph* SingleByteLetter::Clone() {
	return new SingleByteLetter(*this);
}

/*
함수명: operator=
기능: 치환 연산자
*/
SingleByteLetter& SingleByteLetter::operator=(const SingleByteLetter& source) {
	this->content = source.content;
	return *this;
}