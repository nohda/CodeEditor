//OnHScrollRightAction.h
#include "OnHScrollRightAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"

OnHScrollRightAction::OnHScrollRightAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnHScrollRightAction::~OnHScrollRightAction() {

}
void OnHScrollRightAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;
	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_RANGE | SIF_PAGE);
	this->codeEditorForm->SetScrollPos(SB_HORZ, si.nMax - si.nPage + 5, TRUE);
}