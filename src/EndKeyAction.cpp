//EndKeyAction.cpp

/*
파일명 : EndtKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 엔드 키
수정 :
*/

#include "EndKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"

EndKeyAction::EndKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

EndKeyAction::~EndKeyAction() {
}

void EndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long startCurrent;
	Long endCurrent;
	Long memoCurrent;

	startCurrent = this->codeEditorForm->current->GetCurrent();
	endCurrent = this->codeEditorForm->current->Last();
	memoCurrent = this->codeEditorForm->memo->GetCurrent();

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->StartArea(CPoint(startCurrent, memoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(endCurrent, memoCurrent));
	}
}
