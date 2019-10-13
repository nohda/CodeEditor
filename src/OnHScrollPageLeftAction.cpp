//OnHScrollPageLeftAction.h
#include "OnHScrollPageLeftAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"
#include "FontMatrix.h"

OnHScrollPageLeftAction::OnHScrollPageLeftAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnHScrollPageLeftAction::~OnHScrollPageLeftAction() {

}
void OnHScrollPageLeftAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;

	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_ALL);
	si.nPos = max(0, si.nPos - si.nPage);
	this->codeEditorForm->SetScrollPos(SB_HORZ, si.nPos, TRUE);

}