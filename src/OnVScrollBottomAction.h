//OnVScrollBottomAction.h
#pragma once
#ifndef _ONVSCROLLBOTTOMACTION_H
#define _ONVSCROLLBOTTOMACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnVScrollBottomAction :public ScrollAction {
public:
	OnVScrollBottomAction(CodeEditorForm *codeEditorForm);
	virtual ~OnVScrollBottomAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONVSCROLLBOTTOMACTION_H