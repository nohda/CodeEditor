/*
���ϸ� : RightKeyAction.cpp
�ۼ����� : 2019�� 04�� 14��
�ۼ��� : �����
��� : RightKeyAction
*/
//RightKeyAction.cpp

/*
���ϸ� : RightKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : ������ ����Ű
���� :
*/

#include "RightKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"


RightKeyAction::RightKeyAction(CodeEditorForm *codeEditorForm):KeyAction(codeEditorForm) {
}

RightKeyAction:: ~RightKeyAction() {

}

void RightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long linePrevious;
	Long lineCurrent;
	Long memoPrevious;
	Long memoCurrent;
	
	linePrevious = this->codeEditorForm->current->GetCurrent();
	lineCurrent = this->codeEditorForm->current->Next();
	memoPrevious = this->codeEditorForm->memo->GetCurrent();

	if (linePrevious == lineCurrent) {
		memoCurrent = this->codeEditorForm->memo->Next();
		if (memoCurrent != memoPrevious) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			lineCurrent = this->codeEditorForm->current->First();
		}
	}
	else if(linePrevious == -1){
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
		}else{ //���ÿ����� �ִٸ�
			this->codeEditorForm->select->EndArea(CPoint(lineCurrent, memoCurrent)); //������ �����Ѵ�.
		}
	}
	else { //����ƮŰ�� ������ �ʾҴٸ�
		this->codeEditorForm->select->Reset();
	}
}