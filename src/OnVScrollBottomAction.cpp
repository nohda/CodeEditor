//OnVScrollBottomAction.h
#include "OnVScrollBottomAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"

OnVScrollBottomAction::OnVScrollBottomAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnVScrollBottomAction::~OnVScrollBottomAction() {

}
void OnVScrollBottomAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;
	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_RANGE | SIF_PAGE);
	this->codeEditorForm->SetScrollPos(SB_VERT, si.nMax - si.nPage, TRUE);
}