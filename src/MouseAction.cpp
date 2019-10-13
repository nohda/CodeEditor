//MouseAction.cpp

#include "MouseAction.h"
#include "CodeEditorForm.h"
#include "CaretCoordinator.h"
#include "FontMatrix.h"
#include "TextCoordinator.h"
#include "Glyph.h"
#include "ScrollActionFactory.h"
#include "ScrollAction.h"
#include "Select.h"
#include "Line.h"

MouseAction::MouseAction(){
	this->codeEditorForm = 0;
	this->lbuttonDownPoint = 0;
	this->lbuttonUpPoint = 0;
	this->dblClkStart = 0;
	this->dblClkEnd = 0;
}

MouseAction::MouseAction(CodeEditorForm *codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	this->lbuttonDownPoint.SetPoint(0, 0);
	this->lbuttonUpPoint.SetPoint(0, 0);
	this->dblClkStart.SetPoint(0, 0);
	this->dblClkEnd.SetPoint(0, 0);
}

MouseAction::MouseAction(const MouseAction& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->lbuttonDownPoint = source.lbuttonDownPoint;
	this->lbuttonUpPoint = source.lbuttonUpPoint;
	this->dblClkStart = source.dblClkStart;
	this->dblClkEnd = source.dblClkEnd;
}

MouseAction::~MouseAction() {
}

CPoint MouseAction::LButton(CPoint point) {
	Long xPos = 5 + this->codeEditorForm->marginWidth;
	Long memoCurrent;
	Long memoLength;
	Long lineCurrent;
	Long lineLength;
	CPoint nPos;
	CPoint text;
	CPoint outPoint;

	nPos.SetPoint(this->codeEditorForm->GetScrollPos(SB_HORZ), this->codeEditorForm->GetScrollPos(SB_VERT));
	text = this->codeEditorForm->textCoordinator->TextPos(nPos);//텍스트 좌표를 구한다,

	point.y -= text.y;  //마우스 클릭으로 나온 y좌표에 텍스트의 y좌표(y좌표는 0보다 작거나 같다.)를 더한다.
	memoCurrent = point.y / this->codeEditorForm->fontMatrix->GetHeight();  //마우스 클릭으로 나온 y좌표를 글자의 높이로 나눠 이동할 줄의 위치를 구한다.
	if (memoCurrent < 0) {
		memoCurrent = 0;
	}//memoCurrent가 음수일경우에 막아줌.
	memoLength = this->codeEditorForm->memo->GetLength();  //메모의 사용량을 구한다.

	if (memoCurrent < memoLength) {  //메모의 이동할 줄이 사용량보다 작다면
		this->codeEditorForm->memo->Move(memoCurrent);//위에서 구한 줄로 이동한다.
	}
	else {
		this->codeEditorForm->memo->Last();//마우스 좌표로 구한 메모의 이동할 줄이 사용량보다 크거나 같으면 마지막 줄로 이동한다.
	}
	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //현재 줄을 설정한다.
	lineCurrent = this->codeEditorForm->current->First();//줄에 처음으로 이동한다,
	lineLength = this->codeEditorForm->current->GetLength();//줄의 사용량을 구한다,
	
	if (text.x < 5+ this->codeEditorForm->marginWidth) {//텍스트좌표가 기본 시작점이면 마우스를 클릭으로 나온 x좌에 텍스트 x좌표(5아니면 음수)를 더한다.
		point.x -= text.x - this->codeEditorForm->marginWidth;
	}

	while (point.x > 5 && point.x / xPos > 0 && lineCurrent < lineLength) {//마우스 클릭으로 구한 x좌표가 기본 시작점보다 크고
		lineCurrent = this->codeEditorForm->current->Next();							   //마우스 클릭으로 구한 x좌표와 줄에서 현재 위치가 줄에서 현재 위치가 줄의 사용량보다 작다면
		xPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);  //현재 위치를 다음 칸으로 이동하고 현재위치까지의 너비를 구한다,
	}
	this->codeEditorForm->current->Move(lineCurrent);//구한 위치로 이동한다.
	outPoint.SetPoint(lineCurrent, memoCurrent);

	return outPoint;
}

void MouseAction::DblClk(CPoint point){
	Glyph *line;
	Glyph *letter;
	Long lineCurrent;
	Long lineLength;
	string content;
	string temp;

	line = this->codeEditorForm->memo->GetAt(point.y);
	lineLength = line->GetLength();
	
	if (lineLength > 0) { 
		letter = line->GetAt(point.x);
		content = letter->GetContents();
		temp = content;
		lineCurrent = point.x;

		while (content[0] == ' ' && lineCurrent > 0) {
			lineCurrent = line->Previous();

			if (lineCurrent > 0) {
				letter = line->GetAt(lineCurrent);
				content = letter->GetContents();
			}
		}

		while (content[0] != ' ' && lineCurrent > 0) {
			lineCurrent = line->Previous();

			if (lineCurrent > 0) {
				letter = line->GetAt(lineCurrent);
				content = letter->GetContents();
			}
		}

		if (content[0] == ' ' && lineCurrent != 0) {
			lineCurrent = line->Next();
		}

		this->dblClkStart.SetPoint(lineCurrent, point.y);
		lineCurrent = point.x;
		this->codeEditorForm->current->Move(lineCurrent);
		content = temp;

		while (content[0] != ' ' && lineCurrent < lineLength) {
			lineCurrent = this->codeEditorForm->current->Next();

			if (lineCurrent < lineLength) {
				letter = this->codeEditorForm->current->GetAt(lineCurrent);
				content = letter->GetContents();
			}
		}

		while (content[0] == ' ' && lineCurrent < lineLength) {
			lineCurrent = this->codeEditorForm->current->Next();

			if (lineCurrent < lineLength) {
				letter = this->codeEditorForm->current->GetAt(lineCurrent);
				content = letter->GetContents();
			}
		}
	}
	else {
		lineCurrent = 0;
	}
	
	this->dblClkEnd.SetPoint(lineCurrent, point.y);
}
 
void MouseAction::Wheel(WPARAM wParam, LPARAM lParam) {
	ScrollActionFactory scrollActionFactory(this->codeEditorForm);
	ScrollAction *scrollAction;
	UINT nSBCode;

	if ((LONG)wParam > 0) {
		nSBCode = SB_PAGEUP;
	}
	else {
		nSBCode = SB_PAGEDOWN;
	}

	this->codeEditorForm->nSBCode = TRUE;
	scrollAction = scrollActionFactory.Make(nSBCode, TRUE);

	if (scrollAction != NULL) {
		scrollAction->Move(nSBCode, 0); //NULL이 아니면 Move 호출
	}
}

MouseAction& MouseAction::operator=(const MouseAction& source) {
	this->lbuttonDownPoint = source.lbuttonDownPoint;
	this->lbuttonUpPoint = source.lbuttonUpPoint;
	this->dblClkStart = source.dblClkStart;
	this->dblClkEnd = source.dblClkEnd;

	return *this;
}