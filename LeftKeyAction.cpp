//LeftKeyAction.cpp

/*
���ϸ� : LeftKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : ���� ����Ű
���� :
*/

#include "LeftKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"


LeftKeyAction::LeftKeyAction(CodeEditorForm *codeEditorForm) 
	:KeyAction(codeEditorForm) {
}

LeftKeyAction:: ~LeftKeyAction() {
}

void LeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long linePrevious;
	Long lineCurrent;
	Long memoPrevious;
	Long memoCurrent;
	
	linePrevious = this->codeEditorForm->current->GetCurrent();
	lineCurrent = this->codeEditorForm->current->Previous();
	memoPrevious = this->codeEditorForm->memo->GetCurrent();

	if (linePrevious == lineCurrent) {
		memoCurrent = this->codeEditorForm->memo->Previous();

		if (memoPrevious != memoCurrent) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			lineCurrent = this->codeEditorForm->current->Last();
		}
	}
	else if (linePrevious == -1) {
		linePrevious = lineCurrent;
		memoCurrent = memoPrevious;
	}
	else {
		memoCurrent = memoPrevious;
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