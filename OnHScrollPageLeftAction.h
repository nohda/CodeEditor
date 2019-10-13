#pragma once
//OnHScrollPageLeftAction.h
#ifndef _ONHSCROLLPAGELEFTACTION_H
#define _ONHSCROLLPAGELEFTACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnHScrollPageLeftAction :public ScrollAction {
public:
	OnHScrollPageLeftAction(CodeEditorForm *codeEditorForm);
	virtual ~OnHScrollPageLeftAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONHSCROLLPAGELEFTACTION_H
