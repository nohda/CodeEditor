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
	text = this->codeEditorForm->textCoordinator->TextPos(nPos);//�ؽ�Ʈ ��ǥ�� ���Ѵ�,

	point.y -= text.y;  //���콺 Ŭ������ ���� y��ǥ�� �ؽ�Ʈ�� y��ǥ(y��ǥ�� 0���� �۰ų� ����.)�� ���Ѵ�.
	memoCurrent = point.y / this->codeEditorForm->fontMatrix->GetHeight();  //���콺 Ŭ������ ���� y��ǥ�� ������ ���̷� ���� �̵��� ���� ��ġ�� ���Ѵ�.
	if (memoCurrent < 0) {
		memoCurrent = 0;
	}//memoCurrent�� �����ϰ�쿡 ������.
	memoLength = this->codeEditorForm->memo->GetLength();  //�޸��� ��뷮�� ���Ѵ�.

	if (memoCurrent < memoLength) {  //�޸��� �̵��� ���� ��뷮���� �۴ٸ�
		this->codeEditorForm->memo->Move(memoCurrent);//������ ���� �ٷ� �̵��Ѵ�.
	}
	else {
		this->codeEditorForm->memo->Last();//���콺 ��ǥ�� ���� �޸��� �̵��� ���� ��뷮���� ũ�ų� ������ ������ �ٷ� �̵��Ѵ�.
	}
	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //���� ���� �����Ѵ�.
	lineCurrent = this->codeEditorForm->current->First();//�ٿ� ó������ �̵��Ѵ�,
	lineLength = this->codeEditorForm->current->GetLength();//���� ��뷮�� ���Ѵ�,
	
	if (text.x < 5+ this->codeEditorForm->marginWidth) {//�ؽ�Ʈ��ǥ�� �⺻ �������̸� ���콺�� Ŭ������ ���� x�¿� �ؽ�Ʈ x��ǥ(5�ƴϸ� ����)�� ���Ѵ�.
		point.x -= text.x - this->codeEditorForm->marginWidth;
	}

	while (point.x > 5 && point.x / xPos > 0 && lineCurrent < lineLength) {//���콺 Ŭ������ ���� x��ǥ�� �⺻ ���������� ũ��
		lineCurrent = this->codeEditorForm->current->Next();							   //���콺 Ŭ������ ���� x��ǥ�� �ٿ��� ���� ��ġ�� �ٿ��� ���� ��ġ�� ���� ��뷮���� �۴ٸ�
		xPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);  //���� ��ġ�� ���� ĭ���� �̵��ϰ� ������ġ������ �ʺ� ���Ѵ�,
	}
	this->codeEditorForm->current->Move(lineCurrent);//���� ��ġ�� �̵��Ѵ�.
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
		scrollAction->Move(nSBCode, 0); //NULL�� �ƴϸ� Move ȣ��
	}
}

MouseAction& MouseAction::operator=(const MouseAction& source) {
	this->lbuttonDownPoint = source.lbuttonDownPoint;
	this->lbuttonUpPoint = source.lbuttonUpPoint;
	this->dblClkStart = source.dblClkStart;
	this->dblClkEnd = source.dblClkEnd;

	return *this;
}