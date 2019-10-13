//OnVScrollThumbTrackAction.h
#include "OnVScrollThumbTrackAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"

OnVScrollThumbTrackAction::OnVScrollThumbTrackAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {
}

OnVScrollThumbTrackAction::~OnVScrollThumbTrackAction() {

}
void OnVScrollThumbTrackAction::Move(UINT nSBCode, UINT nPos) {
	this->codeEditorForm->SetScrollPos(SB_VERT, nPos, TRUE);
}