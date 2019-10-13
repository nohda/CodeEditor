//CtrlAKeyAction.cpp

#include "CtrlAKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"


CtrlAKeyAction::CtrlAKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlAKeyAction::~CtrlAKeyAction() {
}

void CtrlAKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long memoCurrent;

	memoCurrent = this->codeEditorForm->memo->Last();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->Last();

	this->codeEditorForm->select->StartArea(CPoint(0,0));
	this->codeEditorForm->select->EndArea(CPoint(this->codeEditorForm->current->GetCurrent(), this->codeEditorForm->memo->GetCurrent()));
}
