//CodeEditorFormApp.cpp
/*
파일명 : CodeEditorForm.cpp
작성일자 : 2019년 03월 27일
작성자 : 김영재
기능 : 메인
수정 :
*/

#include "CodeEditorFormApp.h"
#include "CodeEditorFormFrame.h"
#include "CodeEditorForm.h"
#include "resource.h"

/*
함수명: Initinstance
기능: MFC 메인
*/
BOOL CodeEditorFormApp::InitInstance() {
	CodeEditorFormFrame *codeEditorFormFrame = new CodeEditorFormFrame;
	this->m_pMainWnd = codeEditorFormFrame;
	codeEditorFormFrame->Create(NULL, (LPCTSTR)"제목없음 - CodeEditor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CRect(200, 120, 837, 800), NULL, MAKEINTRESOURCE(IDR_MENU1), NULL);
	codeEditorFormFrame->ShowWindow(SW_SHOW);
	codeEditorFormFrame->UpdateWindow();
	codeEditorFormFrame->RegisterTouchWindow(WM_MOUSEHWHEEL);

	return TRUE;
}
CodeEditorFormApp codeEditorFormApp;