//CodeEditorFormApp.cpp
/*
���ϸ� : CodeEditorForm.cpp
�ۼ����� : 2019�� 03�� 27��
�ۼ��� : �迵��
��� : ����
���� :
*/

#include "CodeEditorFormApp.h"
#include "CodeEditorFormFrame.h"
#include "CodeEditorForm.h"
#include "resource.h"

/*
�Լ���: Initinstance
���: MFC ����
*/
BOOL CodeEditorFormApp::InitInstance() {
	CodeEditorFormFrame *codeEditorFormFrame = new CodeEditorFormFrame;
	this->m_pMainWnd = codeEditorFormFrame;
	codeEditorFormFrame->Create(NULL, (LPCTSTR)"������� - CodeEditor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CRect(200, 120, 837, 800), NULL, MAKEINTRESOURCE(IDR_MENU1), NULL);
	codeEditorFormFrame->ShowWindow(SW_SHOW);
	codeEditorFormFrame->UpdateWindow();
	codeEditorFormFrame->RegisterTouchWindow(WM_MOUSEHWHEEL);

	return TRUE;
}
CodeEditorFormApp codeEditorFormApp;