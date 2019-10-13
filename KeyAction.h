//KeyAction.h
#ifndef _KEYACTION_H
#define _KEYACTION_H
#include <afxwin.h>

class CodeEditorForm;
class KeyActionFactory;
class KeyAction {
public:
	KeyAction(CodeEditorForm *codeEditorForm);
	virtual ~KeyAction() = 0;
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {};

protected:
	CodeEditorForm *codeEditorForm;
};

#endif //_KETACTION_H