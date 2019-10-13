//OnHScrollThumbTrackAction.h
#include "OnHScrollThumbTrackAction.h"
#include "CodeEditorForm.h"
#include "Scroll.h"

OnHScrollThumbTrackAction::OnHScrollThumbTrackAction(CodeEditorForm *codeEditorForm) :ScrollAction(codeEditorForm) {

}

OnHScrollThumbTrackAction::~OnHScrollThumbTrackAction() {

}
void OnHScrollThumbTrackAction::Move(UINT nSBCode, UINT nPos) {
	
	this->codeEditorForm->SetScrollPos(SB_HORZ, nPos, TRUE);
}