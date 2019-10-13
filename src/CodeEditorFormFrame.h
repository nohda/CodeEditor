//CodeEditorFormFrame.h
#pragma once

#ifndef _CODEEDITORFORMFRAME_H
#define _CODEEDITORFORMFRAME_H

#include <string>
#include <afxwin.h>
#include <afxdlgs.h>
#include <wingdi.h>
#include <WinUser.h>

using namespace std;
typedef signed long int Long;

class StatusBar;
class CStatusBar;
class CodeEditorForm;
class CodeEditorFormFrame :public CFrameWnd {
public:
	CodeEditorFormFrame();
protected:
	CodeEditorForm *codeEditorForm;

public:
	StatusBar *statusBar;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnMenuButtonClicked(UINT id);
	afx_msg void OnMenuButtonUpdate(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()

};
#endif //_CODEEDITORFORMFRAME_H