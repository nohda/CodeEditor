#pragma once
//OnVScrollThumbTrackAction.h
#ifndef _ONVSCROLLTHUMBTRACKACTION_H
#define _ONVSCROLLTHUMBTRACKACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnVScrollThumbTrackAction :public ScrollAction {
public:
	OnVScrollThumbTrackAction(CodeEditorForm *codeEditorForm);
	virtual ~OnVScrollThumbTrackAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONVSCROLLTHUMBTRACKACTION_H