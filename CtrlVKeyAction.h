//CtrlVKeyAction.h
#pragma once

#ifndef _CTRLVKEYACTION_H
#define _CTRLVKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CtrlVKeyAction :public KeyAction {
public:
	CtrlVKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlVKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLVKEYACTION_H
