#pragma once
//OnHScrollPageRightAction.h
#ifndef _ONHSCROLLPAGERIGHTACTION_H
#define _ONHSCROLLPAGERIGHTACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnHScrollPageRightAction :public ScrollAction {
public:
	OnHScrollPageRightAction(CodeEditorForm *codeEditorForm);
	virtual ~OnHScrollPageRightAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONHSCROLLPAGERIGHTACTION_H
