//CtrlLeftKeyAction.cpp
/*
파일명 : CtrlLeftKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 왼쪽 방향키
수정 :
*/

#include "CtrlLeftKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "CaretCoordinator.h"
#include "Scroll.h"
#include "Select.h"

CtrlLeftKeyAction::CtrlLeftKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlLeftKeyAction::~CtrlLeftKeyAction() {
}

void CtrlLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//CaretCoordinator *caretCoordinator;
	//CRect rect;
	SCROLLINFO si;
	//Long nPos;
	Long lineCurrent;
	Long memoCurrent;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	lineCurrent = this->codeEditorForm->current->GetCurrent();

	if (lineCurrent > 0) { //라인위치가 처음보다 클때 현재줄에서 단어이동
		this->codeEditorForm->current->LeftWord();
	}
	else if (memoCurrent > 0) { //이전줄이 있다면
		memoCurrent = this->codeEditorForm->memo->Previous(); //이전줄로 이동
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //현재줄을 첨자번째로 설정
		this->codeEditorForm->current->Last(); //현재줄의 끝으로 이동
	}

	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_PAGE);
	//this->codeEditorForm->GetClientRect(rect);
	//nPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	//this->codeEditorForm->OnHScroll(SB_THUMBTRACK, nPos - rect.right + (si.nPage * 1), this->codeEditorForm->scroll->GetScrollBar());//형변환

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->EndArea(CPoint(this->codeEditorForm->current->GetCurrent(), this->codeEditorForm->memo->GetCurrent()));
	}
}