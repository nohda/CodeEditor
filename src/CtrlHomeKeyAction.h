#pragma once
//HomeKeyAction.h

#ifndef _CONTROLHOMEKEYACTION_H
#define _CONTROLHOMEKEYACTION_H
#include "KeyAction.h"

class CodeEdtorForm;
class CtrlHomeKeyAction :public KeyAction {
public:
	CtrlHomeKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlHomeKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif//CONTROLHOMEKEYACTION_H