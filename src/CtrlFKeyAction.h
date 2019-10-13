//CtrlAKeyAction.h

#ifndef _CTRLFKEYACTION_H
#define _CTRLFKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class CFindReplaceDialog;
class CtrlFKeyAction :public KeyAction {
public:
	CtrlFKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~CtrlFKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_CTRLFKEYACTION_H
