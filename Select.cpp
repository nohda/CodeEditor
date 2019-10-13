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

	if (this->start.y != this->end.y || this->start.x != this->end.x) { // ����Ŭ�� �� �̵����� �ٷ� ������� �׸��� �ʴ´�.
		if (this->start.y > this->end.y || (this->start.y == this->end.y && this->start.x > this->end.x)) { //�쿡�� �·� �����ߴٸ� ����ġ
			Select = TRUE;//������
		}
		else {
			Select = FALSE;//������
		}

		memoCurrent = this->start.y;
		memoLength = this->end.y;
		memDC->SetTextColor(RGB(255, 255, 255)); //������ ���� ������� �����Ѵ�.
		memDC->SetBkColor(RGB(0, 170, 255)); //������ ������ �Ķ����� �����Ѵ�.

		temp = point;
		height = this->codeEditorForm->fontMatrix->GetHeight();

		while (memoCurrent <= memoLength && Select == FALSE) { //�������̶��
			contents = "";
			CText = CString(contents.c_str());
			point = temp;
			line = this->codeEditorForm->memo->GetAt(memoCurrent);

			if (i == 0 && memoCurrent == memoLength) { //ù������ ���������̶��
				lineCurrent = this->start.x; //�������� LButtonDown ���ڷ� �����Ѵ�.
				lineLength = this->end.x; //������ LButtonUp ���ڷ� �����Ѵ�.
			}
			else if (i == 0 && memoCurrent != memoLength) { //ù������ ���������� �ƴ϶��
				lineCurrent = this->start.x; //�������� LButtonDown ���ڷ� �����Ѵ�.
				lineLength = line->GetLength(); //������ ������ ���ڱ��� �����Ѵ�.
			}
			else if (memoCurrent == memoLength && Select == FALSE) { //���������̰� �������̶��
				lineCurrent = 0; //�������� ù���ڷ� �����Ѵ�.
				lineLength = this->end.x; //������ LButtonUp ���ڷ� �����Ѵ�.
			}
			else { //��Ÿ��� ���̸�
				lineCurrent = 0; //�������� ������ �����ڷ� �����Ѵ�.
				lineLength = line->GetLength();
			}

			xPos = this->codeEditorForm->caretCoordinator->GetSelectXPos(this->codeEditorForm->fontMatrix, line, lineCurrent); //��ũ����ǥ�� �����Ѵ�.
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

		while (memoCurrent >= memoLength && Select == TRUE) { //�������̶��
			contents = "";
			CText = CString(contents.c_str());
			point = temp;
			line = this->codeEditorForm->memo->GetAt(memoCurrent);

			if (i == 0 && memoCurrent == memoLength) {//ù������ ���������̶��
				lineCurrent = this->end.x; //�������� LButtonUp ���ڷ� �����Ѵ�.
				lineLength = this->start.x; //������ LButtonDown ���ڷ� �����Ѵ�.
			}
			else if (i == 0 && memoCurrent != memoLength) { //ù������ ���������� �ƴ϶��
				lineCurrent = 0; //�������� ù ���ڷ� �����Ѵ�.
				lineLength = this->start.x; //������ LButtonDown ���ڷ� �����Ѵ�.
			}
			else if (memoCurrent == memoLength) { //���������̶��
				lineCurrent = this->end.x; //�������� LButtonUp ���ڷ� �����Ѵ�.
				lineLength = line->GetLength(); //������ ������ ���ڷ� �����Ѵ�.
			}
			else { //��Ÿ��� ���̸�
				lineCurrent = 0; //�������� ������ �����ڷ� �����Ѵ�.
				lineLength = line->GetLength();
			}

			xPos = this->codeEditorForm->caretCoordinator->GetSelectXPos(this->codeEditorForm->fontMatrix, line, lineCurrent); //��ũ����ǥ�� �����Ѵ�.
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