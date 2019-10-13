#pragma once
//OnHScrollLeftAction.h
#ifndef _ONHSCROLLLEFTACTION_H
#define _ONHSCROLLLEFTACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnHScrollLeftAction :public ScrollAction {
public:
	OnHScrollLeftAction(CodeEditorForm *codeEditorForm);
	virtual ~OnHScrollLeftAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONHSCROLLLEFTACTION_H