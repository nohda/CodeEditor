/*
���ϸ� : RightKeyAction.h
�ۼ����� : 2019�� 04�� 14��
�ۼ��� : �����
��� : LeftKeyAction ���� ����
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
