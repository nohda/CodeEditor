
/*
파일명 : LeftkeyAction.h
작성일자 : 2019년 04월 14일
작성자 : 허수진
기능 : LeftKeyAction 정의 선언
*/
//LeftkeyAction.h
#ifndef _LEFTKEYACTION_H
#define _LEFTKEYACTION_H
#include "KeyAction.h"

class CodeEditorForm;
class LeftKeyAction :public KeyAction {
public:
	LeftKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~LeftKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif //_LEFTKEYACTION_H
