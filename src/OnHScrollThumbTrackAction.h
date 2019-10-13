#pragma once
//OnHScrollThumbTrackAction.h
#ifndef _ONHSCROLLTHUMBTRACKACTION_H
#define _ONHSCROLLTHUMBTRACKACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnHScrollThumbTrackAction :public ScrollAction {
public:
	OnHScrollThumbTrackAction(CodeEditorForm *codeEditorForm);
	virtual ~OnHScrollThumbTrackAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONHSCROLLTHUMBTRACKACTION_H
