#pragma once
//OnVScrollLineDownAction.h
#ifndef _ONVSCROLLLINEDOWNACTION_H
#define _ONVSCROLLLINEDOWNACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnVScrollLineDownAction :public ScrollAction {
public:
	OnVScrollLineDownAction(CodeEditorForm *codeEditorForm);
	virtual ~OnVScrollLineDownAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONVSCROLLLINEDOWNACTION_H