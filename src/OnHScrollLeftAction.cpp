//OnHScrollLeftAction.h
#include "OnHScrollLeftAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"

OnHScrollLeftAction::OnHScrollLeftAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnHScrollLeftAction::~OnHScrollLeftAction() {

}
void OnHScrollLeftAction::Move(UINT nSBCode, UINT nPos) {
	this->codeEditorForm->SetScrollPos(SB_HORZ, 0, TRUE);
}