//CtrlEndKeyAction.cpp
/*
���ϸ� : CtrlEndKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : Ctrl + ���� Ű
���� :
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