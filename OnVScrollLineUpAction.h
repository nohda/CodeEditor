#pragma once
//OnVScrollLineUpAction.h
#ifndef _ONVSCROLLLINEUPACTION_H
#define _ONVSCROLLLINEUPACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnVScrollLineUpAction :public ScrollAction {
public:
	OnVScrollLineUpAction(CodeEditorForm *codeEditorForm);
	virtual ~OnVScrollLineUpAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONVSCROLLLINEUPACTION_H