//F1KeyAction.h

#ifndef _F1KEYACTION_H
#define _F1KEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class F1KeyAction :public KeyAction {
public:
	F1KeyAction(CodeEditorForm* codeEditorForm);
	virtual ~F1KeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_F1KEYACTION_H