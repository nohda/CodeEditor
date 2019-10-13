#pragma once
//OnHScrollLineLeftAction.h
#ifndef _ONHSCROLLLINELEFTACTION_H
#define _ONHSCROLLLINELEFTACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnHScrollLineLeftAction :public ScrollAction {
public:
	OnHScrollLineLeftAction(CodeEditorForm *codeEditorForm);
	virtual ~OnHScrollLineLeftAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONHSCROLLLINELEFTACTION_H