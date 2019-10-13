//CtrlXKeyAction.h

#ifndef _CTRLXKEYACTION_H
#define _CTRLXKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CtrlXKeyAction :public KeyAction {
public:
	CtrlXKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlXKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLXKEYACTION_H
