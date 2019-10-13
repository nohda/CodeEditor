//OnVScrollTopAction.h
#include "OnVScrollTopAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"

OnVScrollTopAction::OnVScrollTopAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnVScrollTopAction::~OnVScrollTopAction(){

}
void OnVScrollTopAction::Move(UINT nSBCode, UINT nPos){
	this->codeEditorForm->SetScrollPos(SB_VERT, 0, TRUE);
}
