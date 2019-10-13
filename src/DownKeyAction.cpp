//DownKeyAction.cpp

/*
���ϸ� : DownKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : �Ʒ��� ����Ű
���� :
*/

#include "DownKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "CaretCoordinator.h"
#include "Select.h"

//�Ű������� �ִ� ������
DownKeyAction::DownKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

//�Ҹ���
DownKeyAction::~DownKeyAction() {
}

void DownKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long previousX;
	Long currentX;
	Long memoCurrent;
	Long lineCurrent;
	Long lineLength;
	Long memoPrevious;
	Long linePrevious;

	previousX = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	memoPrevious = this->codeEditorForm->memo->GetCurrent();
	memoCurrent = this->codeEditorForm->memo->Next();
	linePrevious = this->codeEditorForm->current->GetCurrent();

	if (memoCurrent != memoPrevious) {
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //���� �ٲ۴�.
		this->codeEditorForm->current->First(); //���� ó������ �̵��Ѵ�.
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

	if (GetKeyState(VK_SHIFT) < 0) { //����ƮŰ�� ���ȴٸ�
		if (this->codeEditorForm->select->GetStartPoint() == this->codeEditorForm->select->GetEndPoint()) { //���ÿ����� ���ٸ�
			this->codeEditorForm->select->StartArea(CPoint(linePrevious, memoPrevious)); //�������� ������ �����Ѵ�.
			this->codeEditorForm->select->EndArea(CPoint(lineCurrent, memoCurrent));
		}
		else { //���ÿ����� �ִٸ�
			this->codeEditorForm->select->EndArea(CPoint(lineCurrent, memoCurrent)); //������ �����Ѵ�.
		}
	}
	else { //����ƮŰ�� ������ �ʾҴٸ�
		this->codeEditorForm->select->Reset();
	}
}