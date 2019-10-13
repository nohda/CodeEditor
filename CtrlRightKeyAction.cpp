//CtrlRightKeyAction.cpp
/*
파일명 : CtrlRightKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : Ctrl + 오른쪽 방향키
수정 :
*/

#include "CtrlRightKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "scroll.h"
#include "CaretCoordinator.h"
#include "Select.h"

CtrlRightKeyAction::CtrlRightKeyAction(CodeEditorForm * codeEditorForm)
	:KeyAction(codeEditorForm) {
	
}

CtrlRightKeyAction::~CtrlRightKeyAction() {
}

void CtrlRightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//CaretCoordinator *caretCoordinator;
	//CRect rect;
	SCROLLINFO si;
	//Long nPos;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent < lineLength && lineCurrent != -1) { //라인위치가 끝보다 작을때 현재줄에서 단어이동
		this->codeEditorForm->current->RightWord();
	}
	else if (memoCurrent < memoLength - 1) { //다음줄이 있다면
		memoCurrent = this->codeEditorForm->memo->Next(); //다음줄로 이동
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //현재줄을 첨자번째로 설정
		this->codeEditorForm->current->First(); //현재줄의 처음으로 이동
	}
	
	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_PAGE);
	//this->codeEditorForm->GetClientRect(rect);
	//nPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	//this->codeEditorForm->OnHScroll(SB_THUMBTRACK, nPos - rect.right + ( si.nPage * 1), this->codeEditorForm->scroll->GetScrollBar());//형변환

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->EndArea(CPoint(this->codeEditorForm->current->GetCurrent(), this->codeEditorForm->memo->GetCurrent()));
	}
}
