#pragma once
//ScrollAction.h
#ifndef _SCROLLACTION_H
#define _SCROLLACTION_H
#include <afxwin.h>

typedef signed long int Long;

class CodeEditorForm;
class ScrollAction {
public:
	ScrollAction(CodeEditorForm *codeEditorForm);
	virtual ~ScrollAction() = 0;
	virtual void Move(UINT nSBCode, UINT nPos) {};
protected:
	CodeEditorForm *codeEditorForm;
};

#endif //_SCROLLACTION_H