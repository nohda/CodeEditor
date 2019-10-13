//HomeKeyAction.cpp
/*
���ϸ� : HomeKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : Ȩ Ű
���� :
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