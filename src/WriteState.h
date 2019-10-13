/*
���ϸ� : WriteState.h
�ۼ����� : 2019�� 04�� 24��
�ۼ��� : 
��� : ���ǿ� ���� ���º���
���� :
*/

#pragma once
#ifndef _WRITESTATE_H
#define _WRITESTATE_H

#include <afxwin.h>
#include "CodeEditorForm.h"
#include <string>

//using namespace std;
typedef signed long int Long;

class CodeEditorForm;
class WriteState {
	public:
		~WriteState();
		WriteState(CodeEditorForm* codeEditorForm);
		virtual void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		virtual LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
		void ChangeState();
	private:
		CodeEditorForm* codeEditorForm;
};

#endif _WRITESTATE_H
