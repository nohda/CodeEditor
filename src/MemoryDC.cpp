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

	this->memDC->CreateCompatibleDC(dc); //CPaintDC�� ȣȯ�Ǵ� ����DC�� �����.
	this->oldBuffer = this->memDC->SelectObject(this->buffer); //����DC�� ��Ʈ���� �����Ѵ�.
	this->memDC->SelectObject(this->codeEditorForm->font->GetFont()); //����DC�� ��Ʈ������ �����Ѵ�.
	this->memDC->PatBlt(0, 0, this->codeEditorForm->clientRect.right, this->codeEditorForm->clientRect.bottom, WHITENESS); //����DC�� ������� ĥ�Ѵ�

	nPos.SetPoint(this->codeEditorForm->GetScrollPos(SB_HORZ), this->codeEditorForm->GetScrollPos(SB_VERT)); //��ũ�ѿ� ������ nPos�� �����´�.
	point = this->codeEditorForm->textCoordinator->TextPos(nPos); //�ؽ�Ʈ ��ǥ�� �����Ѵ�.
	height = this->codeEditorForm->fontMatrix->GetHeight(); //���� ���̸� ���Ѵ�.
	i = contentsEdit.FirstLineNumber(point.y, height); //���� ù�ٺ��� ���� �� ���� ���Ѵ�.
	memoLength = this->codeEditorForm->memo->GetLength(); //������� ������ ���Ѵ�.
	memoLength = i + contentsEdit.LastLineNumber(height, this->codeEditorForm->clientRect.bottom, memoLength); //���� �������ٱ��� ���� �� ���� ���Ѵ�.

	//���ۿ� �� �ٸ�ŭ �ݺ��Ѵ�.
	while (i < memoLength) {
		firstContentNumber = 0;
		line = this->codeEditorForm->memo->GetAt(i); //���� �����´�.
		contents = "";
		contents = line->GetContents(); //���� ���ڵ��� �����´�.
		interval = point.x - this->codeEditorForm->marginWidth;

		//���� �� ù ������ ��ġ�� ���Ѵ�.
		firstContentNumber = contentsEdit.FirstContentNumber(point.x - this->codeEditorForm->marginWidth, contents);

		//���� �� ������ ������ ��ġ�� ���Ѵ�.
		lastContentNumber = contentsEdit.LastContentsNumber(line, this->codeEditorForm->clientRect.right - this->codeEditorForm->marginWidth);

		if (firstContentNumber <= lastContentNumber) { //���� �� ���ڰ� �ִٸ�
			contents = contents.substr(firstContentNumber, lastContentNumber); //�۾������� �ʺ�ŭ ���ڸ� �̾Ƴ���.
		}
		else{
			contents.erase(); //���� �� ���ڰ� ���ٸ� ��� ����.
		}

		interval = contentsEdit.GetInterval(); //���� �߰� ����

		CText = CString(contents.c_str());
		this->memDC->SetTextColor(RGB(0, 0, 0));
		this->memDC->TextOut(point.x + interval, point.y + (i * height), CText); //����DC�� ���ڸ� ����
		this->codeEditorForm->textEdit->isHighlight(this->memDC, line, point, i); //����DC�� ���ڸ� �����Ѵ�.
		i++;
	}

	this->codeEditorForm->select->Draw(this->memDC, point);
	this->memDC->PatBlt(0, this->codeEditorForm->clientRect.top, this->codeEditorForm->clientRect.left - 1, this->codeEditorForm->clientRect.bottom, WHITENESS); //����DC�� ������� ĥ�Ѵ�
	this->memDC->PatBlt(this->codeEditorForm->clientRect.left - 1, this->codeEditorForm->clientRect.top, 1, this->codeEditorForm->clientRect.bottom, BLACKNESS);
	Numberpoint = this->codeEditorForm->textCoordinator->NumberPos(nPos);
	i = contentsEdit.GetFirstLineNumber();
	memoLength = i + contentsEdit.GetLastLineNumber();

	while (i < memoLength) { //�ٹ�ȣ
		Number = i + 1;
		CText.Format(_T("%d"), Number);
		this->memDC->SetTextColor(RGB(97, 97, 97));
		this->memDC->SetBkColor(RGB(255, 255, 255));
		this->memDC->TextOut(Numberpoint.x, Numberpoint.y + (i * height), CText); //����DC�� ���ڸ� ����
		i++;
	}
}

void MemoryDC::Resize() {
	delete this->buffer;
	this->buffer = NULL;
}

void MemoryDC::SetOfDelete() {
	this->memDC->SelectObject(this->oldBuffer); //����DC�� ������Ʈ���� �����Ѵ�.
	this->memDC->DeleteDC(); //����DC �Ҵ�����
}

MemoryDC& MemoryDC::operator=(const MemoryDC& source) {
	this->buffer = source.buffer;
	this->oldBuffer = source.oldBuffer;
	this->memDC = source.memDC;
	this->codeEditorForm = source.codeEditorForm;

	return *this;
}