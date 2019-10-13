//OnHScrollLineRightAction.h
#include "OnHScrollLineRightAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"
#include "Glyph.h"
#include "FontMatrix.h"
#include "CaretCoordinator.h"

OnHScrollLineRightAction::OnHScrollLineRightAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnHScrollLineRightAction::~OnHScrollLineRightAction() {

}
void OnHScrollLineRightAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;
	Long xPos;
	Long longestWidth;
	Long fontAveWidth;
	Long fontWidth=10;
	Glyph* letter;


	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_ALL);
	xPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	longestWidth = this->codeEditorForm->caretCoordinator->GetLongestWidth(this->codeEditorForm->fontMatrix, this->codeEditorForm->memo);
	fontAveWidth = this->codeEditorForm->caretCoordinator->GetAveWidth();
	letter = this->codeEditorForm->current->GetAt(this->codeEditorForm->current->GetCurrent());
	if (letter != NULL) {
		if (letter->GetContents() == "") {
			fontWidth = this->codeEditorForm->fontMatrix->GetWidth(letter);
		}
	}
	if (xPos != this->codeEditorForm->scroll->GetXPos()) {
		si.nPos = (xPos - this->codeEditorForm->marginWidth) - si.nPage;
	}
	else if (xPos != longestWidth && this->codeEditorForm->nSBCode == FALSE) {
		si.nPos = ( (xPos + fontWidth) - this->codeEditorForm->clientRect.right);
	}
	else{
		si.nPos += fontAveWidth;
	}

	this->codeEditorForm->SetScrollPos(SB_HORZ, si.nPos, TRUE);
}