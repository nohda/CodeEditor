#pragma once

#ifndef _F5KEYACTION_H
#define _F5KEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class F5KeyAction :public KeyAction {
public:
	F5KeyAction(CodeEditorForm* codeEditorForm);
	virtual ~F5KeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif //_F5KEYACTION_H