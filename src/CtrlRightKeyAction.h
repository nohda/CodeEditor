//CtrlRightKeyAction.h
#ifndef _CTRLRIGHTKEYACTION_H
#define _CTRLRIGHTKEYACTION_H
#include "KeyAction.h"

class CtrlRightKeyAction :public KeyAction {
public:
	CtrlRightKeyAction(CodeEditorForm *codeEditForm);
	virtual ~CtrlRightKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLRIGHTKEYACTION_H

