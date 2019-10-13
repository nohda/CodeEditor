//OnVScrollPageUpAction.h
#include "OnVScrollPageUpAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"
#include "FontMatrix.h"

OnVScrollPageUpAction::OnVScrollPageUpAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnVScrollPageUpAction::~OnVScrollPageUpAction() {

}
void OnVScrollPageUpAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;
	Long fontHeight;

	fontHeight = this->codeEditorForm->fontMatrix->GetHeight();
	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_ALL);
	si.nPos = max(0, si.nPos - si.nPage + fontHeight);
	this->codeEditorForm->SetScrollPos(SB_VERT, si.nPos, TRUE);

}