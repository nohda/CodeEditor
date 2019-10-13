#include "CtrlGKeyAction.h"
#include "CodeEditorForm.h"
#include "LineMove.h"

CtrlGKeyAction::CtrlGKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm){
}

CtrlGKeyAction::~CtrlGKeyAction(){
}

void CtrlGKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	LineMove cDialog(this->codeEditorForm);

	cDialog.DoModal();
}