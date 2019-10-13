#pragma once
//OnHScrollLineRightAction.h
#ifndef _ONHSCROLLLINERIGHTACTION_H
#define _ONHSCROLLLINERIGHTACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnHScrollLineRightAction :public ScrollAction {
public:
	OnHScrollLineRightAction(CodeEditorForm *codeEditorForm);
	virtual ~OnHScrollLineRightAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONHSCROLLLINERIGHTACTION_H