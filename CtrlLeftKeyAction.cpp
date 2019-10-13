//CtrlLeftKeyAction.cpp
/*
���ϸ� : CtrlLeftKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : Ctrl + ���� ����Ű
���� :
*/

#include "CtrlLeftKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "CaretCoordinator.h"
#include "Scroll.h"
#include "Select.h"

CtrlLeftKeyAction::CtrlLeftKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlLeftKeyAction::~CtrlLeftKeyAction() {
}

void CtrlLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//CaretCoordinator *caretCoordinator;
	//CRect rect;
	SCROLLINFO si;
	//Long nPos;
	Long lineCurrent;
	Long memoCurrent;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	lineCurrent = this->codeEditorForm->current->GetCurrent();

	if (lineCurrent > 0) { //������ġ�� ó������ Ŭ�� �����ٿ��� �ܾ��̵�
		this->codeEditorForm->current->LeftWord();
	}
	else if (memoCurrent > 0) { //�������� �ִٸ�
		memoCurrent = this->codeEditorForm->memo->Previous(); //�����ٷ� �̵�
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //�������� ÷�ڹ�°�� ����
		this->codeEditorForm->current->Last(); //�������� ������ �̵�
	}

	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_PAGE);
	//this->codeEditorForm->GetClientRect(rect);
	//nPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	//this->codeEditorForm->OnHScroll(SB_THUMBTRACK, nPos - rect.right + (si.nPage * 1), this->codeEditorForm->scroll->GetScrollBar());//����ȯ

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->EndArea(CPoint(this->codeEditorForm->current->GetCurrent(), this->codeEditorForm->memo->GetCurrent()));
	}
}