//EnterKeyAction.h
#ifndef _ENTERKEYACTION_H
#define _ENTERKEYACTION_H
#include "KeyAction.h"

class CodeEdtorForm;
class EnterKeyAction :public KeyAction {
public:
	EnterKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~EnterKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif//ENTERKEYACTION_H