/*
파일명 : RightKeyAction.cpp
작성일자 : 2019년 04월 14일
작성자 : 허수진
기능 : RightKeyAction
*/
//RightKeyAction.cpp

/*
파일명 : RightKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 오른쪽 방향키
수정 :
*/

#include "RightKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"


RightKeyAction::RightKeyAction(CodeEditorForm *codeEditorForm):KeyAction(codeEditorForm) {
}

RightKeyAction:: ~RightKeyAction() {

}

void RightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long linePrevious;
	Long lineCurrent;
	Long memoPrevious;
	Long memoCurrent;
	
	linePrevious = this->codeEditorForm->current->GetCurrent();
	lineCurrent = this->codeEditorForm->current->Next();
	memoPrevious = this->codeEditorForm->memo->GetCurrent();

	if (linePrevious == lineCurrent) {
		memoCurrent = this->codeEditorForm->memo->Next();
		if (memoCurrent != memoPrevious) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			lineCurrent = this->codeEditorForm->current->First();
		}
	}
	else if(linePrevious == -1){
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
		}else{ //선택영역이 있다면
			this->codeEditorForm->select->EndArea(CPoint(lineCurrent, memoCurrent)); //끝점을 설정한다.
		}
	}
	else { //쉬프트키가 눌리지 않았다면
		this->codeEditorForm->select->Reset();
	}
}