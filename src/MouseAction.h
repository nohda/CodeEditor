#pragma once

#ifndef _MOUSEACTION_H
#define _MOUSEACTION_H

#include <afxwin.h>

typedef signed long int Long;

class CodeEditorForm;
class CPoint;
class Select;
class MouseAction {
public:
	MouseAction();
	MouseAction(CodeEditorForm *codeEditorForm);
	MouseAction(const MouseAction& source);
	~MouseAction();
	CPoint LButton(CPoint point);
	void DblClk(CPoint point);
	void Wheel(WPARAM wParam, LPARAM lParam);
	CPoint GetLButtonDownPoint()const;
	CPoint GetLButtonUpPoint()const;
	CPoint GetDblClkStart()const;
	CPoint GetDblClkEnd()const;
	MouseAction& operator=(const MouseAction& source);

private:
	CodeEditorForm *codeEditorForm;
	CPoint lbuttonDownPoint;
	CPoint lbuttonUpPoint;
	CPoint dblClkStart;
	CPoint dblClkEnd;
};

inline CPoint MouseAction::GetLButtonDownPoint()const {
	return this->lbuttonDownPoint;
}
inline CPoint MouseAction::GetLButtonUpPoint()const {
	return this->lbuttonUpPoint;
}
inline CPoint MouseAction::GetDblClkStart()const {
	return this->dblClkStart;
}
inline CPoint MouseAction::GetDblClkEnd()const {
	return this->dblClkEnd;
}
#endif //_MOUSEACTION_H