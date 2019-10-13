//F3KeyAction.h

#ifndef _F3KEYACTION_H
#define _F3KEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class F3KeyAction :public KeyAction {
public:
	F3KeyAction(CodeEditorForm *codeEditorForm);
	virtual ~F3KeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif//_F3KEYACTION_H