//CaretController.cpp
/*
���ϸ� : CaretController.cpp
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : ���α�
��� : ĳ������ Ŭ�������� �����ϴ� Ŭ����
���� : 20190410 GetXPosCaret �����߰�
*/

#include "CaretController.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "Caret.h"
#include "CaretCoordinator.h"
#include "Memo.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"

/*
�Լ��� : CaretController
��� : ����Ʈ������
*/
CaretController::CaretController() {
	this->codeEditorForm = 0;
	this->caret = 0;
	this->line = 0;
	this->row = 0;
}

/*
�Լ��� : CaretController
��� : �Ű������� ������ ������
*/
CaretController::CaretController(CodeEditorForm *codeEditorForm, Glyph *line, Long row) {
	this->codeEditorForm = codeEditorForm;
	this->caret = new Caret(this->codeEditorForm);
	this->line = line;
	this->row = row;
	this->codeEditorForm->SubjectAttach(this);
}

/*
�Լ��� : CaretController
��� : ���������
*/
CaretController::CaretController(const CaretController& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->caret = source.caret;
	this->line = source.line;
	this->row = source.row;
}

/*
�Լ��� : ~CaretController
��� : �Ҹ���
����: 20190407 caret,caretCoordinator ���� �Ҵ�����
*/
CaretController::~CaretController() {
	this->codeEditorForm->SubjectDetach(this);
	delete this->caret;
	this->caret = NULL;
}

/*
�Լ��� : MakeCaret
��� : ĳ���� �����.
*/
void CaretController::MakeCaret() {
	Long width = 2;
	Long height;

	if (this->codeEditorForm->isComposing == TRUE ) {
		width -= this->codeEditorForm->fontMatrix->GetDoubleByteWidth();
	}

	height = this->codeEditorForm->fontMatrix->GetHeight();
	this->caret->Make(width, height);
}

/*
�Լ���: MoveCaret
��� : ĳ���� �̵��Ѵ�.
����: 20190407 �ŰԺ��� ���, �����͸���� ����ϵ��� ����
*/
void CaretController::MoveCaret() {
	CPoint point;
	Long xPos;
	Long yPos;
	CPoint nPos;

	nPos.SetPoint(this->codeEditorForm->GetScrollPos(SB_HORZ), this->codeEditorForm->GetScrollPos(SB_VERT));
	xPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	yPos = this->codeEditorForm->caretCoordinator->GetYPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->memo->GetCurrent());
	point.SetPoint(xPos - nPos.x, yPos - nPos.y);

	/*if (nPos.x > 0) {
		point.x -= 5 ;
	}*/

	this->caret->Move(point);
}

/*
�Լ���: ShowCaret
��� : ĳ���� �����ְų� �����.
*/
void CaretController::ShowCaret(bool isShow) {
	CPoint nPos;
	Long xPos;

	if (this != NULL) {
		nPos.SetPoint(this->codeEditorForm->GetScrollPos(SB_HORZ), this->codeEditorForm->GetScrollPos(SB_VERT));
		xPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
		if (xPos- nPos.x < this->codeEditorForm->marginWidth) {
			this->caret->Show(false);
		}
		else {
		this->caret->Show(isShow);
		}
	}
}

/*
�Լ���: DeleteCaret
��� : ĳ���� �����Ѵ�.
*/
void CaretController::DeleteCaret() {
	this->caret->Delete();
}

/*
�Լ���: Update
��� : line�� column�� ������Ʈ �Ѵ�.
���� : MakeCaret, MoveCaret, ShowCaret �߰�
*/
void CaretController::Update() {
	this->row = this->codeEditorForm->memo->GetCurrent();
	this->line = this->codeEditorForm->memo->GetAt(this->row);

	this->MakeCaret();
	this->MoveCaret();
	this->ShowCaret(TRUE);
}

/*
�Լ���: operator=
��� : ġȯ ������
*/
CaretController& CaretController::operator=(const CaretController& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->caret = source.caret;
	this->line = source.line;
	this->row = source.row;

	return *this;
}