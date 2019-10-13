//HomeKeyAction.h

#ifndef _HOMEKEYACTION_H
#define _HOMEKEYACTION_H
#include "KeyAction.h"

class CodeEdtorForm;
class HomeKeyAction :public KeyAction {
public:
	HomeKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~HomeKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//HOMEKEYACTION_H
