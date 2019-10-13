//OnVScrollLineUpAction.h
#include "OnVScrollLineUpAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"
#include "Glyph.h"
#include "FontMatrix.h"
#include "CaretCoordinator.h"

OnVScrollLineUpAction::OnVScrollLineUpAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnVScrollLineUpAction::~OnVScrollLineUpAction(){

}

void OnVScrollLineUpAction::Move(UINT nSBCode, UINT nPos){
//	CaretCoordinator *caretCoordinator;
	SCROLLINFO si;
	Long memoCurrent;
	Long yPos;
	Long fontHeight;
	Long longestHeightX;

	this->codeEditorForm->GetScrollInfo(SB_VERT, &si, SIF_ALL);
	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	yPos = this->codeEditorForm->caretCoordinator->GetYPos(this->codeEditorForm->fontMatrix, memoCurrent + 1);
	fontHeight = this->codeEditorForm->fontMatrix->GetHeight();
	longestHeightX = this->codeEditorForm->memo->GetLength()*fontHeight;

	if (yPos != this->codeEditorForm->scroll->GetYPos() && longestHeightX != this->codeEditorForm->scroll->GetLongestHeight()) { //���� ������ �ִٸ�
		si.nPos = yPos - si.nPage;
	}
	else { //������ ���ٸ�
		si.nPos -= fontHeight;
	}

	this->codeEditorForm->SetScrollPos(SB_VERT, si.nPos, TRUE);
}

