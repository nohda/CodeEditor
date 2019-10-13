//CtrlSKeyAction.h

#ifndef _CTRLSKEYACTION_H
#define _CTRLSKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CtrlSKeyAction :public KeyAction {
public:
	CtrlSKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlSKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLSKEYACTION_H