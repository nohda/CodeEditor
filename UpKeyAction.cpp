//UpKeyAction.cpp
/*
파일명 : UpKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 위쪽 방향키
수정 :
*/

#include "UpKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "CaretCoordinator.h"
#include "Select.h"

//매개변수가 있는 생성자
UpKeyAction::UpKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

//소멸자
UpKeyAction::~UpKeyAction() {
}

void UpKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	Long previousX;
	Long currentX;
	Long memoCurrent;
	Long lineCurrent;
	Long lineLength;
	Long memoPrevious;
	Long linePrevious;

	previousX = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	memoPrevious = this->codeEditorForm->memo->GetCurrent();
	memoCurrent = this->codeEditorForm->memo->Previous();
	linePrevious = this->codeEditorForm->current->GetCurrent();

	if (memoCurrent != memoPrevious) {
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
		this->codeEditorForm->current->First();
		lineLength = this->codeEditorForm->current->GetLength();
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		currentX = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);

		while (currentX < previousX && lineCurrent != lineLength) {
			lineCurrent = this->codeEditorForm->current->Next();
			currentX = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
		}
	}
	else {
		lineCurrent = linePrevious;
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