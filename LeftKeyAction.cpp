//LeftKeyAction.cpp

/*
파일명 : LeftKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 왼쪽 방향키
수정 :
*/

#include "LeftKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"


LeftKeyAction::LeftKeyAction(CodeEditorForm *codeEditorForm) 
	:KeyAction(codeEditorForm) {
}

LeftKeyAction:: ~LeftKeyAction() {
}

void LeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long linePrevious;
	Long lineCurrent;
	Long memoPrevious;
	Long memoCurrent;
	
	linePrevious = this->codeEditorForm->current->GetCurrent();
	lineCurrent = this->codeEditorForm->current->Previous();
	memoPrevious = this->codeEditorForm->memo->GetCurrent();

	if (linePrevious == lineCurrent) {
		memoCurrent = this->codeEditorForm->memo->Previous();

		if (memoPrevious != memoCurrent) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			lineCurrent = this->codeEditorForm->current->Last();
		}
	}
	else if (linePrevious == -1) {
		linePrevious = lineCurrent;
		memoCurrent = memoPrevious;
	}
	else {
		memoCurrent = memoPrevious;
	}

	if (GetKeyState(VK_SHIFT) < 0) { //쉬프트키가 눌렸다면
		if (this->codeEditorForm->select->GetStartPoint() == this->codeEditorForm->select->GetEndPoint()) { //선택영역이 없다면
			this->codeEditorForm->select->StartArea(CPoint(linePrevious, memoPrevious)); //시작점과 끝점을 설정한다.
			this->codeEditorForm->select->EndArea(CPoint(lineCurrent, memoCurrent));
		}
		else { //선택영역이 있다면
			this->codeEditorForm->select->EndArea(CPoint(lineCurrent, memoCurrent)); //끝점을 설정한다.
		}
	}
	else { //쉬프트키가 눌리지 않았다면
		this->codeEditorForm->select->Reset();
	}
}