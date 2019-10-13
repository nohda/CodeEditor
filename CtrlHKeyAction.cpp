//CtrlHKeyAction.cpp

#include "CtrlHKeyAction.h"
#include "CodeEditorForm.h"
#include "Find.h"


CtrlHKeyAction::CtrlHKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlHKeyAction::~CtrlHKeyAction() {
}

void CtrlHKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->codeEditorForm->find->Create(FALSE);
}