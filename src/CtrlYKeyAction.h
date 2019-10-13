//CtrlYKeyAction.h
#pragma once
#ifndef _CTRLYKEYACTION_H
#define _CTRLYKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CtrlYKeyAction :public KeyAction {
public:
	CtrlYKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlYKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLYKEYACTION_H

