#pragma once
//OnHScrollRightAction.h
#ifndef _ONHSCROLLRIGHTACTION_H
#define _ONHSCROLLRIGHTACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnHScrollRightAction :public ScrollAction {
public:
	OnHScrollRightAction(CodeEditorForm *codeEditorForm);
	virtual ~OnHScrollRightAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONHSCROLLRIGHTACTION_H
