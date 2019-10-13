//OnHScrollPageRightAction.h
#include "OnHScrollPageRightAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"
#include "FontMatrix.h"

OnHScrollPageRightAction::OnHScrollPageRightAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnHScrollPageRightAction::~OnHScrollPageRightAction() {

}
void OnHScrollPageRightAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;

	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_ALL);
	si.nPos = min(si.nMax - si.nPage, si.nPos + si.nPage);
	this->codeEditorForm->SetScrollPos(SB_HORZ, si.nPos, TRUE);
}