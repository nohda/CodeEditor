//CtrlEndKeyAction.cpp
/*
파일명 : CtrlEndKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 엔드 키
수정 :
*/
#include "CtrlEndKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"

CtrlEndKeyAction::CtrlEndKeyAction(CodeEditorForm *codeEditorForm) : KeyAction(codeEditorForm) {
}

CtrlEndKeyAction::~CtrlEndKeyAction() {
}

void CtrlEndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long startMemoCurrent;
	Long endMemoCurrent;
	Long startCurrent;
	Long endCurrent;

	startMemoCurrent = this->codeEditorForm->memo->GetCurrent();
	startCurrent = this->codeEditorForm->current->GetCurrent();
	endMemoCurrent = this->codeEditorForm->memo->Last();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(endMemoCurrent);
	endCurrent = this->codeEditorForm->current->Last();

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->StartArea(CPoint(startCurrent, startMemoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(endCurrent, endMemoCurrent));
	}
}