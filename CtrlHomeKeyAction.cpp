//CtrlHomeKeyAction.cpp
/*
���ϸ� : CtrlHomeKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : Ctrl + Ȩ Ű
���� :
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