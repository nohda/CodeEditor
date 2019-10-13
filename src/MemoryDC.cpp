#include "MemoryDC.h"
#include "CodeEditorForm.h"
#include "Font.h"
#include "TextCoordinator.h"
#include "FontMatrix.h"
#include "Glyph.h"
#include "Select.h"
#include "TextEdit.h"
#include "CaretCoordinator.h"
#include "ContentsEdit.h"
#include "Status.h"
#include "CodeEditorFormFrame.h"
#include <afxext.h>
#include <afxcmn.h>

MemoryDC::MemoryDC() {
	this->buffer = 0;
	this->oldBuffer = 0;
	this->memDC = 0;
	this->codeEditorForm = 0;
}

MemoryDC::MemoryDC(CodeEditorForm* codeEditorForm) {
	this->buffer = NULL;
	this->oldBuffer = NULL;
	this->memDC = new CDC;
	this->codeEditorForm = codeEditorForm;
}

MemoryDC::MemoryDC(const MemoryDC& source) {
	this->buffer = source.buffer;
	this->oldBuffer = source.oldBuffer;
	this->memDC = source.memDC;
	this->codeEditorForm = source.codeEditorForm;
}

MemoryDC::~MemoryDC() {
	if (this->buffer != NULL) {
		delete this->buffer;
		this->buffer = NULL;
	}
	if (this->memDC != NULL) {
		delete this->memDC;
		this->memDC = NULL;
	}
}

void MemoryDC::Make(CPaintDC *dc) {
	CRect rect;

	this->codeEditorForm->GetClientRect(rect);
	this->buffer = new CBitmap;
	this->buffer->CreateCompatibleBitmap(dc, rect.right, rect.bottom);
}

void MemoryDC::Draw(CPaintDC *dc) {
	CPoint nPos;
	CPoint point;
	Glyph* line;
	Long height;
	string contents;
	CString CText;
	Long Number;
	CPoint Numberpoint;
	Long i = 0;
	Long interval;
	Long memoLength;
	Glyph* letter = NULL;
	ContentsEdit contentsEdit(this->codeEditorForm);
	Long firstContentNumber;
	Long lastContentNumber;

	this->memDC->CreateCompatibleDC(dc); //CPaintDC와 호환되는 버퍼DC를 만든다.
	this->oldBuffer = this->memDC->SelectObject(this->buffer); //버퍼DC에 비트맵을 세팅한다.
	this->memDC->SelectObject(this->codeEditorForm->font->GetFont()); //버퍼DC에 폰트정보를 세팅한다.
	this->memDC->PatBlt(0, 0, this->codeEditorForm->clientRect.right, this->codeEditorForm->clientRect.bottom, WHITENESS); //버퍼DC를 흰색으로 칠한다

	nPos.SetPoint(this->codeEditorForm->GetScrollPos(SB_HORZ), this->codeEditorForm->GetScrollPos(SB_VERT)); //스크롤에 설정된 nPos를 가져온다.
	point = this->codeEditorForm->textCoordinator->TextPos(nPos); //텍스트 좌표를 보정한다.
	height = this->codeEditorForm->fontMatrix->GetHeight(); //줄의 높이를 구한다.
	i = contentsEdit.FirstLineNumber(point.y, height); //영역 첫줄부터 보여 줄 줄을 구한다.
	memoLength = this->codeEditorForm->memo->GetLength(); //모든줄의 갯수를 구한다.
	memoLength = i + contentsEdit.LastLineNumber(height, this->codeEditorForm->clientRect.bottom, memoLength); //영역 마지막줄까지 보여 줄 줄을 구한다.

	//버퍼에 쓸 줄만큼 반복한다.
	while (i < memoLength) {
		firstContentNumber = 0;
		line = this->codeEditorForm->memo->GetAt(i); //줄을 가져온다.
		contents = "";
		contents = line->GetContents(); //줄의 글자들을 가져온다.
		interval = point.x - this->codeEditorForm->marginWidth;

		//보여 줄 첫 글자의 위치를 구한다.
		firstContentNumber = contentsEdit.FirstContentNumber(point.x - this->codeEditorForm->marginWidth, contents);

		//보여 줄 마지막 글자의 위치를 구한다.
		lastContentNumber = contentsEdit.LastContentsNumber(line, this->codeEditorForm->clientRect.right - this->codeEditorForm->marginWidth);

		if (firstContentNumber <= lastContentNumber) { //보여 줄 글자가 있다면
			contents = contents.substr(firstContentNumber, lastContentNumber); //작업영역의 너비만큼 글자를 뽑아낸다.
		}
		else{
			contents.erase(); //보여 줄 글자가 없다면 모두 비운다.
		}

		interval = contentsEdit.GetInterval(); //글자 추가 간격

		CText = CString(contents.c_str());
		this->memDC->SetTextColor(RGB(0, 0, 0));
		this->memDC->TextOut(point.x + interval, point.y + (i * height), CText); //버퍼DC에 글자를 쓴다
		this->codeEditorForm->textEdit->isHighlight(this->memDC, line, point, i); //버퍼DC에 글자를 강조한다.
		i++;
	}

	this->codeEditorForm->select->Draw(this->memDC, point);
	this->memDC->PatBlt(0, this->codeEditorForm->clientRect.top, this->codeEditorForm->clientRect.left - 1, this->codeEditorForm->clientRect.bottom, WHITENESS); //버퍼DC를 흰색으로 칠한다
	this->memDC->PatBlt(this->codeEditorForm->clientRect.left - 1, this->codeEditorForm->clientRect.top, 1, this->codeEditorForm->clientRect.bottom, BLACKNESS);
	Numberpoint = this->codeEditorForm->textCoordinator->NumberPos(nPos);
	i = contentsEdit.GetFirstLineNumber();
	memoLength = i + contentsEdit.GetLastLineNumber();

	while (i < memoLength) { //줄번호
		Number = i + 1;
		CText.Format(_T("%d"), Number);
		this->memDC->SetTextColor(RGB(97, 97, 97));
		this->memDC->SetBkColor(RGB(255, 255, 255));
		this->memDC->TextOut(Numberpoint.x, Numberpoint.y + (i * height), CText); //버퍼DC에 글자를 쓴다
		i++;
	}
}

void MemoryDC::Resize() {
	delete this->buffer;
	this->buffer = NULL;
}

void MemoryDC::SetOfDelete() {
	this->memDC->SelectObject(this->oldBuffer); //버퍼DC에 기존비트맵을 세팅한다.
	this->memDC->DeleteDC(); //버퍼DC 할당해제
}

MemoryDC& MemoryDC::operator=(const MemoryDC& source) {
	this->buffer = source.buffer;
	this->oldBuffer = source.oldBuffer;
	this->memDC = source.memDC;
	this->codeEditorForm = source.codeEditorForm;

	return *this;
}