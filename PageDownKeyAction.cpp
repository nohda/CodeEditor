//PageDownKeyAction.cpp
#include "PageDownKeyAction.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "CaretCoordinator.h"
#include "Glyph.h"
#include "Scroll.h"

PageDownKeyAction::PageDownKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

PageDownKeyAction::~PageDownKeyAction() {
}

void PageDownKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long memoCurrent;  //현재 메모의 위치
	Long memoLength;   // 메모의 사용량
	Long lineLength;  //줄의 사용량
	Long lineCurrent;  //현재 줄의 위치
	Long previousWidth;  //이전 줄의 현재 위치까지의 너비
	Long currentWidth;   //바뀐 줄의 현재 위치까지의 너비
	//Long fontHeight;  //글자의 높이
	Long moveCurrent;  //이동거리
	Long i = 0;
	Long height;
	CRect rect;
	Long count = 0;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();  //메모의 현위치를 구한다.
	memoLength = this->codeEditorForm->memo->GetLength();  //메모의 사용량을 구한다,
	height = this->codeEditorForm->fontMatrix->GetHeight();
	this->codeEditorForm->GetClientRect(rect);
	//화면에 몇개의 줄까지 표시할 수 있는지 구한다.
	while (i * height < rect.bottom && i < memoLength) {
		if ((i + 1) * height < rect.bottom) {
			count++;
			i++;
		}
		else {
			break;
		}
	}
	moveCurrent = memoCurrent + count;
	if (memoLength - moveCurrent < count) { //제일 아래쪽 페이지라면 첫줄로 설정한다.
		moveCurrent = memoLength;
	}
		previousWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);  //현재 줄의 현재위치까지의 너비를 구한다,
		memoCurrent = this->codeEditorForm->memo->Move(moveCurrent);  //메모의 위치를 이동시킨다.

		if (moveCurrent == memoLength) {
			memoCurrent = this->codeEditorForm->memo->Last();
		}
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(moveCurrent-1);    //줄을 이동한다.
		this->codeEditorForm->current->First();    //줄의 처음으로 이동한다.
		lineLength = this->codeEditorForm->current->GetLength();
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		currentWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current); //바뀐 줄의 현재 위치까지의 너비를 구한다.

		while (currentWidth < previousWidth && lineCurrent < lineLength) {
			lineCurrent = this->codeEditorForm->current->Next();  
			currentWidth = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
		}
}
