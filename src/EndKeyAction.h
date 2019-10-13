//EndKeyAction.h

#ifndef _ENDKEYACTION_H
#define _ENDKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class EndKeyAction :public KeyAction {
public:
	EndKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~EndKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//ENDKEYACTION_H