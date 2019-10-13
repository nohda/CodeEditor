//EndKeyAction.cpp

/*
���ϸ� : EndtKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : ���� Ű
���� :
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
