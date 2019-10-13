//CtrlCKeyAction.h
#pragma once

#ifndef _CTRLCKEYACTION_H
#define _CTRLCKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CtrlCKeyAction :public KeyAction {
public:
	CtrlCKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlCKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLCKEYACTION_H
