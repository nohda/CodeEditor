//OnHScrollLineLeftAction.h
#include "OnHScrollLineLeftAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "FontMatrix.h"
#include "Scroll.h"
#include "CaretCoordinator.h"

OnHScrollLineLeftAction::OnHScrollLineLeftAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnHScrollLineLeftAction::~OnHScrollLineLeftAction() {

}
void OnHScrollLineLeftAction::Move(UINT nSBCode, UINT nPos) {
	SCROLLINFO si;
	Glyph* letter;
	Long PreviousWidth;
	Long xPos;
	Long longestWidth;
	Long fontWidth;

	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_ALL);
	xPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	longestWidth = this->codeEditorForm->caretCoordinator->GetLongestWidth(this->codeEditorForm->fontMatrix, this->codeEditorForm->memo); //ave구하기 위해서 사용
	fontWidth = this->codeEditorForm->caretCoordinator->GetAveWidth();

	if (xPos != this->codeEditorForm->scroll->GetXPos()) {
		si.nPos = xPos - si.nPage;
	}
	else if (xPos != longestWidth && this->codeEditorForm->nSBCode == FALSE) {
		letter = this->codeEditorForm->current->GetAt(this->codeEditorForm->current->GetCurrent());
		PreviousWidth = this->codeEditorForm->fontMatrix->GetWidth(letter);
		si.nPos -= PreviousWidth;
	}
	else {
		si.nPos -= fontWidth;
	}

	this->codeEditorForm->SetScrollPos(SB_HORZ, si.nPos, TRUE);
}