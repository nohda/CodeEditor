//HomeKeyAction.cpp
/*
파일명 : HomeKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 홈 키
수정 :
*/

#include "HomeKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"

HomeKeyAction::HomeKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

HomeKeyAction::~HomeKeyAction() {
}

void HomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long startCurrent;
	Long endCurrent;
	Long memoCurrent;

	startCurrent = this->codeEditorForm->current->GetCurrent();
	endCurrent = this->codeEditorForm->current->First();
	memoCurrent = this->codeEditorForm->memo->GetCurrent();

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->StartArea(CPoint(startCurrent, memoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(endCurrent, memoCurrent));
	}
}