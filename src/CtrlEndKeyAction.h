#pragma once
//EndKeyAction.h

#ifndef _CONTROLENDKEYACTION_H
#define _CONTROLENDKEYACTION_H
#include "KeyAction.h"

class CodeEdtorForm;
class CtrlEndKeyAction :public KeyAction {
public:
	CtrlEndKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlEndKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif//CONTROLENDKEYACTION_H