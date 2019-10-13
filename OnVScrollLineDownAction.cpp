//OnVScrollLineDownAction.h
#include "OnVScrollLineDownAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "FontMatrix.h"
#include "Scroll.h"
#include "CaretCoordinator.h"

OnVScrollLineDownAction::OnVScrollLineDownAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnVScrollLineDownAction::~OnVScrollLineDownAction() {

}
void OnVScrollLineDownAction::Move(UINT nSBCode, UINT nPos){
	//CaretCoordinator *caretCoordinator;
	SCROLLINFO si;
	Long yPos;
	Long fontHeight;
		
	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_ALL);
	yPos = this->codeEditorForm->caretCoordinator->GetYPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->memo->GetCurrent() + 1);
	fontHeight = this->codeEditorForm->fontMatrix->GetHeight();

	if (yPos != this->codeEditorForm->scroll->GetYPos()) {
		si.nPos = yPos - si.nPage;
	}
	else {
		si.nPos += fontHeight;
	}

	this->codeEditorForm->SetScrollPos(SB_VERT, si.nPos, TRUE);
}