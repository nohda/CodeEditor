//CtrlZKeyAction.h
#pragma once

#ifndef _CTRLZKEYACTION_H
#define _CTRLZKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CtrlZKeyAction :public KeyAction {
public:
	CtrlZKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlZKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLZKEYACTION_H
