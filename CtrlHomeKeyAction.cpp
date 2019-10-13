//CtrlHomeKeyAction.cpp
/*
파일명 : CtrlHomeKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 홈 키
수정 :
*/
#include "CtrlHomeKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"

CtrlHomeKeyAction::CtrlHomeKeyAction(CodeEditorForm *codeEditorForm) : KeyAction(codeEditorForm) {
}

CtrlHomeKeyAction::~CtrlHomeKeyAction() {
}

void CtrlHomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long startMemoCurrent;
	Long endMemoCurrent;
	Long startCurrent;
	Long endCurrent;

	startMemoCurrent = this->codeEditorForm->memo->GetCurrent();
	startCurrent = this->codeEditorForm->current->GetCurrent();
	endMemoCurrent = this->codeEditorForm->memo->First();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(endMemoCurrent);
	endCurrent = this->codeEditorForm->current->First();

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->StartArea(CPoint(startCurrent, startMemoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(endCurrent, endMemoCurrent));
	}
}