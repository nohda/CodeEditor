//PageUpKeyAction.h
#ifndef _PAGEUPKEYACTION_H
#define _PAGEUPKEYACTION_H
#include "KeyAction.h"

typedef signed long int Long;

class CodeEdtorForm;
class PageUpKeyAction :public KeyAction {
public:
	PageUpKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~PageUpKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_PAGEUPKEYACTION_H
