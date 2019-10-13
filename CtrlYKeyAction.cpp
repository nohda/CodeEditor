#include "CtrlYKeyAction.h"
#include "CodeEditorForm.h"
#include "Cancellation.h"

CtrlYKeyAction::CtrlYKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm){
}

CtrlYKeyAction::~CtrlYKeyAction(){
}

void CtrlYKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	this->codeEditorForm->cancellation->RedoPop();
}
