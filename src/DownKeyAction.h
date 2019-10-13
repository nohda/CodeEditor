#pragma once
//DownKeyAction.h
#ifndef _DOWNKEYACTION_H
#define _DOWNKEYACTION_H
#include "KeyAction.h"

typedef signed long int Long;

class CodiEditorForm;
class DownKeyAction : public KeyAction {
public:
	DownKeyAction(CodeEditorForm *codeEditForm);
	virtual ~DownKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif //_DOWNKEYACTION_H