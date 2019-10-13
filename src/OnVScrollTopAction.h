#pragma once
//OnVScrollTopAction.h
#ifndef _ONVSCROLLTOPACTION_H
#define _ONVSCROLLTOPACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnVScrollTopAction :public ScrollAction {
public:
	OnVScrollTopAction(CodeEditorForm *codeEditorForm);
	virtual ~OnVScrollTopAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONVSCROLLTOPACTION_H