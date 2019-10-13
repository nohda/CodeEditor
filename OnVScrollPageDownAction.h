#pragma once
//OnVScrollPageDownAction.h
#ifndef _ONVSCROLLPAGEDOWNACTION_H
#define _ONVSCROLLPAGEDOWNACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnVScrollPageDownAction :public ScrollAction {
public:
	OnVScrollPageDownAction(CodeEditorForm *codeEditorForm);
	virtual ~OnVScrollPageDownAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONVSCROLLPAGEDOWNACTION_H