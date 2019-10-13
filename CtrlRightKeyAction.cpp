//CtrlRightKeyAction.cpp
/*
���ϸ� : CtrlRightKeyAction.cpp
�ۼ����� : 2019�� 04�� 15��
�ۼ��� : �迵��
��� : Ctrl + ������ ����Ű
���� :
*/

#include "CtrlRightKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "scroll.h"
#include "CaretCoordinator.h"
#include "Select.h"

CtrlRightKeyAction::CtrlRightKeyAction(CodeEditorForm * codeEditorForm)
	:KeyAction(codeEditorForm) {
	
}

CtrlRightKeyAction::~CtrlRightKeyAction() {
}

void CtrlRightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//CaretCoordinator *caretCoordinator;
	//CRect rect;
	SCROLLINFO si;
	//Long nPos;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent < lineLength && lineCurrent != -1) { //������ġ�� ������ ������ �����ٿ��� �ܾ��̵�
		this->codeEditorForm->current->RightWord();
	}
	else if (memoCurrent < memoLength - 1) { //�������� �ִٸ�
		memoCurrent = this->codeEditorForm->memo->Next(); //�����ٷ� �̵�
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //�������� ÷�ڹ�°�� ����
		this->codeEditorForm->current->First(); //�������� ó������ �̵�
	}
	
	this->codeEditorForm->GetScrollInfo(SB_HORZ, &si, SIF_PAGE);
	//this->codeEditorForm->GetClientRect(rect);
	//nPos = this->codeEditorForm->caretCoordinator->GetXPos(this->codeEditorForm->fontMatrix, this->codeEditorForm->current);
	//this->codeEditorForm->OnHScroll(SB_THUMBTRACK, nPos - rect.right + ( si.nPage * 1), this->codeEditorForm->scroll->GetScrollBar());//����ȯ

	if (GetKeyState(VK_SHIFT) < 0) {
		this->codeEditorForm->select->EndArea(CPoint(this->codeEditorForm->current->GetCurrent(), this->codeEditorForm->memo->GetCurrent()));
	}
}
