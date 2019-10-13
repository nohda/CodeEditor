//PageDownKeyAction.h
#ifndef _PAGEDOWNKEYACTION_H
#define _PAGEDOWNKEYACTION_H
#include "KeyAction.h"

typedef signed long int Long;

class CodeEdtorForm;
class PageDownKeyAction :public KeyAction {
public:
	PageDownKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~PageDownKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_PAGEDOWNKEYACTION_H
