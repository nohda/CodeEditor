/*
파일명 : Line.h
//Line.cpp
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : 생성자, 복사생성자, 소멸자, , 문자열 만들기, 연산자= 선언
수정 : 1900402 GetContents 정의(Tab처리)
*/
#include "Line.h"
#include "iterator.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"

/*
함수명 : Line
기능 : 생성자
*/
Line::Line(Long capacity) :Composite(capacity) {
}

/*
함수명 : Line
기능 : 복사 생성자
*/
Line::Line(const Line& source) : Composite(source) {
	}

/*
함수명 : ~Line
기능 : 소멸자
*/
Line::~Line() {
}


/*
함수명 : Add
기능 : Add 오버라이드
*/
Long Line::Add(Glyph* glyph) {
	if (this->capacity > this->length) {
		this->current = glyphs.Store(this->length, glyph) + 1;
	}
	else {
		this->current = glyphs.AppendFromRear(glyph) + 1;
		this->capacity++;
	}
	this->length++;
	return this->current;
}

Long Line::Add(Glyph * glyph, Long index) {
	Composite::Add(glyph, index);
	
	this->current++;

	return this->current;
}

/*
함수명 : LeftWord
기능 : 왼쪽으로 한 단어 이동
*/
Long Line::LeftWord() {
	Glyph *letter;
	string contents;

	letter = this->glyphs.GetAt(this->current - 1);
	contents = letter->GetContents();

	while (this->current > 0 && contents[0] == ' ') { //라인위치가 0보다 크고 콘텐츠가 공백이라면
		this->Previous(); //라인위치 이전으로

		if (this->current > 0) { //라인위치가 0보다 크다면
			letter = this->glyphs.GetAt(this->current - 1); //이전라인의 콘텐츠를 가져온다.
			contents = letter->GetContents();
		}
	}
	
	while (this->current > 0 && contents[0] != ' ') { //라인위치가 0보다 크고 콘텐츠가 공백이 아니라면
		this->Previous();
		
		if (this->current > 0) { //라인위치가 0보다 크다면
			letter = this->glyphs.GetAt(this->current - 1); //이전라인의 콘텐츠를 가져온다.
			contents = letter->GetContents();
		}
	}

	return this->current;
}

/*
함수명 : RightWord
기능 : 오른쪽으로 한 단어 이동
*/
Long Line::RightWord() {
	Glyph *letter;
	string contents;

	letter = this->glyphs.GetAt(this->current);
	contents = letter->GetContents();

	//전제
	//(1) 첫문자를 만날때까지 공백을 건너 뛸 반복문
	//(2) 첫문자를 만나고 문자의 끝으로 이동 할 반복문
	//(3) 다음문자의 앞까지 공백을 건너 뛸 반복문
	while (this->current < this->length && contents[0] == ' ') {
		this->Next();
		
		if (this->current < this->length){ 
			letter = this->glyphs.GetAt(this->current);
			contents = letter->GetContents();
		}
	}

	while (this->current < this->length && contents[0] != ' ') {
		this->Next();
		
		if (this->current < this->length){
			letter = this->glyphs.GetAt(this->current);
			contents = letter->GetContents();
		}
	}

	while (this->current < this->length && contents[0] == ' ') {
		this->Next();

		if (this->current < this->length) {
			letter = this->glyphs.GetAt(this->current);
			contents = letter->GetContents();
		}
	}

	return this->current;
}

/*
함수명 : Clone
기능 : 복사한다
*/
Glyph* Line::Clone() {
	return new Line(*this);
}

/*
함수명 : Getcontent
기능 : 글자를 가져온다.
*/
string Line::GetContent() {
	Glyph *letter;

	letter = this->GetAt(this->current);
	return letter->GetContents();
}

/*
함수명 : Getcontents
기능 : 문자열을 만든다
*/
string Line::GetContents() {
	string text = "";
	string contents;

	Iterator<Glyph*>*iterator = this->CreateItorator();

	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {	
		contents = iterator->CurrentItem()->GetContents();
		text += contents;
	}
	return text;
}


/*
함수명 : operator=
기능 : 치환 연산자
*/
Line& Line::operator=(const Line& source) {
	Composite::operator=(source);
	return *this;
}