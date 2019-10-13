//ScrollActionFactory.cpp
#include "ScrollActionFactory.h"
#include "OnVScrollTopAction.h"
#include "OnVScrollBottomAction.h"
#include "OnVScrollLineUpAction.h"
#include "OnVScrollLineDownAction.h"
#include "OnVScrollPageUpAction.h"
#include "OnVScrollPageDownAction.h"
#include "OnVScrollThumbTrackAction.h"
#include "OnHScrollLeftAction.h"
#include "OnHScrollRightAction.h"
#include "OnHScrollLineLeftAction.h"
#include "OnHScrollLineRightAction.h"
#include "OnHScrollPageLeftAction.h"
#include "OnHScrollPageRightAction.h"
#include "OnHScrollThumbTrackAction.h"

ScrollActionFactory::ScrollActionFactory(CodeEditorForm* codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

ScrollActionFactory::~ScrollActionFactory() {
}

ScrollAction* ScrollActionFactory::Make(UINT nSBCode, BOOL isVert) {
	ScrollAction *scrollAction = NULL;

	if (isVert == TRUE) {
		if (nSBCode == SB_TOP) {
			scrollAction = new OnVScrollTopAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_BOTTOM) {
			scrollAction = new OnVScrollBottomAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_LINEUP) {
			scrollAction = new OnVScrollLineUpAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_LINEDOWN) {
			scrollAction = new OnVScrollLineDownAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_PAGEUP) {
			scrollAction = new OnVScrollPageUpAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_PAGEDOWN) {
			scrollAction = new OnVScrollPageDownAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_THUMBTRACK) {
			scrollAction = new OnVScrollThumbTrackAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_ENDSCROLL) {
		}
	}
	else {
		if (nSBCode == SB_LEFT) {
			scrollAction = new OnHScrollLeftAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_RIGHT) {
			scrollAction = new OnHScrollRightAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_LINELEFT) {
			scrollAction = new OnHScrollLineLeftAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_LINERIGHT) {
			scrollAction = new OnHScrollLineRightAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_PAGELEFT) {
			scrollAction = new OnHScrollPageLeftAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_PAGERIGHT) {
			scrollAction = new OnHScrollPageRightAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_THUMBTRACK) {
			scrollAction = new OnHScrollThumbTrackAction(this->codeEditorForm);
		}
		else if (nSBCode == SB_ENDSCROLL) {
		}
	}

	return scrollAction;
}
