/*
파일명 : CodeEitorForm.h
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : CodeEitorForm CFrameWnd 선언
*/
//CodeEitorForm.h

#pragma once

#ifndef _CODEEDITORFORM_H
#define _CODEEDITORFORM_H

#include "Subject.h"
#include <string>
#include <afxwin.h>
#include <afxdlgs.h>
#include <wingdi.h>
#include <WinUser.h>

using namespace std;
typedef signed long int Long;

class Glyph;
class Memo;
class File;
class Font;
class FontMatrix;
class CaretController;
class CaretCoordinator;
class Scroll;
class MemoryDC;
class TextCoordinator;
class TextEdit;
class MouseAction;
class Select;
class WriteState;
class Cancellation;
class Memory;
class MemoryInsert;
class MemoryDelete;
class Find;
class Status;
class CodeEditorForm :public CWnd, public Subject {
public:
	CodeEditorForm();
public:
	Glyph *current;
	Glyph *memo;
	BOOL isComposing;
	File *file;
	Font* font;
	FontMatrix* fontMatrix;
	Scroll *scroll;
	BOOL nSBCode;
	MemoryDC *memoryDC;
	CaretController *caretController;
	CaretCoordinator *caretCoordinator;
	TextCoordinator *textCoordinator;
	TextEdit *textEdit;
	WriteState* states[2];
	WriteState* state;
	MouseAction *mouseAction;
	Select *select;
	Cancellation *cancellation;
	Memory *memory;
	MemoryInsert *memoryInsert;
	MemoryDelete *memoryDelete;
	Find *find;
	BOOL nFlagUndo;
	RECT clientRect;
	Long marginWidth;
	Status* status;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* cScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* cScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMenuButtonClicked(UINT id);
	afx_msg void OnMenuButtonUpdate(CCmdUI *pCmdUI);
	afx_msg LRESULT OnFind(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()

public:
	void TakeIn(string text);

private:

};
#endif //_CODEEDITORFORM_H