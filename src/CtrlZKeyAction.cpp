#include "CtrlZKeyAction.h"
#include "CodeEditorForm.h"
#include "Cancellation.h"


CtrlZKeyAction::CtrlZKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm){
}

CtrlZKeyAction::~CtrlZKeyAction(){
}

void CtrlZKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	this->codeEditorForm->cancellation->UndoPop();
}
