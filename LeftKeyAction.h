
/*
���ϸ� : LeftkeyAction.h
�ۼ����� : 2019�� 04�� 14��
�ۼ��� : �����
��� : LeftKeyAction ���� ����
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
