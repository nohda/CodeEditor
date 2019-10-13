#pragma once
//OnVScrollPageUpAction.h
#ifndef _ONVSCROLLPAGEUPACTION_H
#define _ONVSCROLLPAGEUPACTION_H

#include "ScrollAction.h"
#include <afxwin.h>

class CodeEditorForm;
class OnVScrollPageUpAction :public ScrollAction {
public:
	OnVScrollPageUpAction(CodeEditorForm *codeEditorForm);
	virtual ~OnVScrollPageUpAction();
	virtual void Move(UINT nSBCode, UINT nPos);
};
#endif // !_ONVSCROLLPAGEUPACTION_H