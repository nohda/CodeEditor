//UpKeyAction.cpp
/*
���ϸ� : UpKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : ���� ����Ű
���� :
*/

#include "UpKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "CaretCoordinator.h"
#include "Select.h"

//�Ű������� �ִ� ������
UpKeyAction::UpKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

//�Ҹ���
UpKeyAction::~UpKeyAction() {
}

void UpKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	Long previousX;
	Long currentX;
	Long memoCurrent;
	Long lineCurrent;
	Long lineLength;
	Long memoPrevious;
	Long linePrevious;

	previousX = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	memoPrevious = this->codeEditorForm->memo->GetCurrent();
	memoCurrent = this->codeEditorForm->memo->Previous();
	linePrevious = this->codeEditorForm->current->GetCurrent();

	if (memoCurrent != memoPrevious) {
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
		this->codeEditorForm->current->First();
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