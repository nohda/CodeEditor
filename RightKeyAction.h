/*
파일명 : RightKeyAction.h
작성일자 : 2019년 04월 14일
작성자 : 허수진
기능 : LeftKeyAction 정의 선언
*/
//RightKeyAction.h
#ifndef _RIGHTKEYACTION_H
#define _RIGHTKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class RightKeyAction :public KeyAction {
public:
	RightKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~RightKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_RIGHTKEYACTION_H
