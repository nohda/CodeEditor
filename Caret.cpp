//Caret.cpp
/*
���ϸ� : Caret.cpp
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �迵��
��� : ĳ���� ���� ����,�̵�,�����ֱ�
���� : 
*/

#include "Caret.h"
#include "CodeEditorForm.h"

/*
�Լ��� : Caret
��� : �⺻ ������
*/
Caret::Caret() {
	this->codeEditorForm = 0;
	this->width = 0;
	this->height = 0;
}

/*
�Լ��� : Caret
��� : �Ű����� ������
*/
Caret::Caret(CodeEditorForm * codeEditorForm, Long width, Long height) {
	this->codeEditorForm = codeEditorForm;
	this->width = width;
	this->height = height;
}

/*
�Լ��� : Caret
��� : ���� ������
*/
Caret::Caret(const Caret& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->width = source.width;
	this->height = source.height;
}

/*
�Լ��� : Caret
��� : �Ҹ���
*/
Caret::~Caret() {
}

/*
�Լ��� : Make
��� : ĳ���� �����
���� : ĳ���� ����� width,height�� �ٲ��ش�.
*/
void Caret::Make(Long width, Long height) {
	
	this->width = width;
	this->height = height;
	this->codeEditorForm->CreateSolidCaret(this->width, this->height);
}

/*
�Լ��� : Move
��� : ĳ���� �̵��Ѵ�
*/
void Caret::Move(CPoint point) {

	this->codeEditorForm->SetCaretPos(point);
}

/*
�Լ��� : Show
��� : ĳ���� �����ְų� �����
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
�Լ��� : Delete
��� : ĳ���� �����
*/
void Caret::Delete() {
	DestroyCaret();
}

/*
�Լ��� : operator=
��� : ġȯ ������
*/
Caret& Caret::operator=(const Caret& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->width = source.width;
	this->height = source.height;
	
	return *this;
}
