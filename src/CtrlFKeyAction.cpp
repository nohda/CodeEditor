#include "CtrlFKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Find.h"

CtrlFKeyAction::CtrlFKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlFKeyAction::~CtrlFKeyAction() {
}

void CtrlFKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long lineLength;
	Long memoLength;

	lineLength = this->codeEditorForm->current->GetLength();
	memoLength = this->codeEditorForm->memo->GetLength();

	if ((lineLength > 0 && memoLength > 0) || lineLength >= 0 && memoLength > 1) { //�ѱ��ڶ� �ְų� �����̻��̸�
		this->codeEditorForm->find->Create(TRUE); //ã��â�� ����
	}
}