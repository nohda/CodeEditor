//UpKeyAction.h
#ifndef _UPKEYACTION_H
#define _UPKEYACTION_H
#include "KeyAction.h"

typedef signed long int Long;

class CodeEditForm;
class UpKeyAction : public KeyAction {
public:
	UpKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~UpKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif //_UPKEYACTION_H

