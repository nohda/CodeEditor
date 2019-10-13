//Caret.cpp
/*
파일명 : Caret.cpp
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 : 캐럿에 대한 생성,이동,보여주기
수정 : 
*/

#include "Caret.h"
#include "CodeEditorForm.h"

/*
함수명 : Caret
기능 : 기본 생성자
*/
Caret::Caret() {
	this->codeEditorForm = 0;
	this->width = 0;
	this->height = 0;
}

/*
함수명 : Caret
기능 : 매개변수 생성자
*/
Caret::Caret(CodeEditorForm * codeEditorForm, Long width, Long height) {
	this->codeEditorForm = codeEditorForm;
	this->width = width;
	this->height = height;
}

/*
함수명 : Caret
기능 : 복사 생성자
*/
Caret::Caret(const Caret& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->width = source.width;
	this->height = source.height;
}

/*
함수명 : Caret
기능 : 소멸자
*/
Caret::~Caret() {
}

/*
함수명 : Make
기능 : 캐럿을 만든다
수정 : 캐럿의 모양을 width,height를 바꿔준다.
*/
void Caret::Make(Long width, Long height) {
	
	this->width = width;
	this->height = height;
	this->codeEditorForm->CreateSolidCaret(this->width, this->height);
}

/*
함수명 : Move
기능 : 캐럿을 이동한다
*/
void Caret::Move(CPoint point) {

	this->codeEditorForm->SetCaretPos(point);
}

/*
함수명 : Show
기능 : 캐럿을 보여주거나 숨긴다
*/
void Caret::Show(bool isShow) {
	if (isShow == TRUE) {
		this->codeEditorForm->ShowCaret();
	}
	else {
		this->codeEditorForm->HideCaret();
	}
}

/*
함수명 : Delete
기능 : 캐럿을 지운다
*/
void Caret::Delete() {
	DestroyCaret();
}

/*
함수명 : operator=
기능 : 치환 연산자
*/
Caret& Caret::operator=(const Caret& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->width = source.width;
	this->height = source.height;
	
	return *this;
}
