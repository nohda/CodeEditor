//CtrlAKeyAction.h

#ifndef _CTRLAKEYACTION_H
#define _CTRLAKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CtrlAKeyAction :public KeyAction {
public:
	CtrlAKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlAKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLAKEYACTION_H
