//Select.cpp

#include "Select.h"
#include "CodeEditorForm.h"
#include "CaretCoordinator.h"
#include "TextCoordinator.h"
#include "FontMatrix.h"
#include "Glyph.h"
#include "TextCoordinator.h"
#include <string>
//using namespace std;

Select::Select() {
	this->codeEditorForm = 0;
	this->start = 0;
	this->end = 0;
}

Select::Select(CodeEditorForm * codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	this->start.SetPoint(0, 0);
	this->end.SetPoint(0, 0);
}

Select::Select(const Select & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->start = source.start;
	this->end = source.end;
}

Select::~Select() {
}

void Select::StartArea(CPoint point) {
	this->start = point;//current
	this->end = point;
}

void Select::EndArea(CPoint point) {
	this->end = point;
}

void Select::WordArea(CPoint dblClkStart, CPoint dblClkEnd) {
	this->start = dblClkStart;
	this->end = dblClkEnd;
}

void Select::Reset() {
	this->start.SetPoint(0, 0);
	this->end.SetPoint(0, 0);
}

void Select::Draw(CDC *memDC, CPoint point) {
	Glyph *line;
	Glyph *letter;
	CPoint temp;
	string contents;
	CString CText;
	CRect rect;
	BOOL Select;
	Long height;
	Long memoCurrent;
	Long memoLength;
	Long lineCurrent;
	Long lineLength;
	Long viewXPos;
	Long xPos;
	Long nPos;
	Long i = 0;

	if (this->start.y != this->end.y || this->start.x != this->end.x) { // 왼쪽클릭 후 이동없이 바로 뗐을경우 그리지 않는다.
		if (this->start.y > this->end.y || (this->start.y == this->end.y && this->start.x > this->end.x)) { //우에서 좌로 선택했다면 스위치
			Select = TRUE;//역방향
		}
		else {
			Select = FALSE;//정방향
		}

		memoCurrent = this->start.y;
		memoLength = this->end.y;
		memDC->SetTextColor(RGB(255, 255, 255)); //글자의 색을 흰색으로 설정한다.
		memDC->SetBkColor(RGB(0, 170, 255)); //글자의 배경색을 파랑으로 설정한다.

		temp = point;
		height = this->codeEditorForm->fontMatrix->GetHeight();

		while (memoCurrent <= memoLength && Select == FALSE) { //정방향이라면
			contents = "";
			CText = CString(contents.c_str());
			point = temp;
			line = this->codeEditorForm->memo->GetAt(memoCurrent);

			if (i == 0 && memoCurrent == memoLength) { //첫줄이자 마지막줄이라면
				lineCurrent = this->start.x; //시작점을 LButtonDown 글자로 설정한다.
				lineLength = this->end.x; //끝점을 LButtonUp 글자로 설정한다.
			}
			else if (i == 0 && memoCurrent != memoLength) { //첫줄이자 마지막줄이 아니라면
				lineCurrent = this->start.x; //시작점을 LButtonDown 글자로 설정한다.
				lineLength = line->GetLength(); //끝점을 마지막 글자까지 설정한다.
			}
			else if (memoCurrent == memoLength && Select == FALSE) { //마지막줄이고 정방향이라면
				lineCurrent = 0; //시작점을 첫글자로 설정한다.
				lineLength = this->end.x; //끝점을 LButtonUp 글자로 설정한다.
			}
			else { //기타등등 줄이면
				lineCurrent = 0; //시작점과 끝점을 모든글자로 설정한다.
				lineLength = line->GetLength();
			}

			xPos = this->codeEditorForm->caretCoordinator->GetSelectXPos(this->codeEditorForm->fontMatrix, line, lineCurrent); //스크롤좌표를 연동한다.
			point.x += xPos;

			while (lineCurrent < lineLength) {
				letter = line->GetAt(lineCurrent);
				contents += letter->GetContents();
				CText = CString(contents.c_str());
				lineCurrent++;
			}
			memDC->TextOut(point.x - this->codeEditorForm->marginWidth, point.y + (memoCurrent * height), CText);
			i++;
			memoCurrent++;
		}

		while (memoCurrent >= memoLength && Select == TRUE) { //역방향이라면
			contents = "";
			CText = CString(contents.c_str());
			point = temp;
			line = this->codeEditorForm->memo->GetAt(memoCurrent);

			if (i == 0 && memoCurrent == memoLength) {//첫줄이자 마지막줄이라면
				lineCurrent = this->end.x; //시작점을 LButtonUp 글자로 설정한다.
				lineLength = this->start.x; //끝점을 LButtonDown 글자로 설정한다.
			}
			else if (i == 0 && memoCurrent != memoLength) { //첫줄이자 마지막줄이 아니라면
				lineCurrent = 0; //시작점을 첫 글자로 설정한다.
				lineLength = this->start.x; //끝점을 LButtonDown 글자로 설정한다.
			}
			else if (memoCurrent == memoLength) { //마지막줄이라면
				lineCurrent = this->end.x; //시작점을 LButtonUp 글자로 설정한다.
				lineLength = line->GetLength(); //끝점을 마지막 글자로 설정한다.
			}
			else { //기타등등 줄이면
				lineCurrent = 0; //시작점과 끝점을 모든글자로 설정한다.
				lineLength = line->GetLength();
			}

			xPos = this->codeEditorForm->caretCoordinator->GetSelectXPos(this->codeEditorForm->fontMatrix, line, lineCurrent); //스크롤좌표를 연동한다.
			nPos = this->codeEditorForm->GetScrollPos(SB_HORZ);
			if (nPos != 0) {
				point.x = xPos - nPos;
			}
			else {
				viewXPos = xPos - nPos;
				point.x = viewXPos /*+ 5*/;
			}

			while (lineCurrent < lineLength) {
				letter = line->GetAt(lineCurrent);
				contents += letter->GetContents();
				CText = CString(contents.c_str());
				lineCurrent++;
			}
			memDC->TextOut(point.x , point.y + (memoCurrent * height), CText);
			i++;
			memoCurrent--;
		}
	}
}


Select & Select::operator=(const Select & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->start = source.start;
	this->end = source.end;

	return *this;
}