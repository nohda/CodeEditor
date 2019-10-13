/*
파일명 : WriteState.h
작성일자 : 2019년 04월 24일
작성자 : 
기능 : 조건에 따른 상태변경
수정 :
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
