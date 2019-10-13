//BackspaceKeyAction.h

#ifndef _BACKSPACEKEYACTION_H
#define _BACKSPACEKEYACTION_H

#include "KeyAction.h"

typedef signed long int Long;

class CodeEditorForm;
class BackspaceKeyAction :public KeyAction {
public:
	BackspaceKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~BackspaceKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif //__BACKSPACEKEYACTION_H