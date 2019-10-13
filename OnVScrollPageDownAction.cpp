//OnVScrollPageDownAction.h
#include "OnVScrollPageDownAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"
#include "FontMatrix.h"

OnVScrollPageDownAction::OnVScrollPageDownAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnVScrollPageDownAction::~OnVScrollPageDownAction() {

}
void OnVScrollPageDownAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;

	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_ALL);
	si.nPos = min(si.nMax - si.nPage, si.nPos + si.nPage);
	this->codeEditorForm->SetScrollPos(SB_VERT, si.nPos, TRUE);
}