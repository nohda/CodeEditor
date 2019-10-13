//DeleteKeyAction.h
#ifndef _DELETEKEYACTION_H
#define _DELETEKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class DeleteKeyAction :public KeyAction {
public:
	DeleteKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~DeleteKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_DELETEKEYACTION_H
