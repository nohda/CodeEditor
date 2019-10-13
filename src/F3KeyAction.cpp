#include "F3KeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Find.h"

F3KeyAction::F3KeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

F3KeyAction::~F3KeyAction(){
}

void F3KeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	Long lineLength;
	Long memoLength;

	lineLength = this->codeEditorForm->current->GetLength();
	memoLength = this->codeEditorForm->memo->GetLength();

	if ((lineLength > 0 && memoLength > 0) || lineLength >= 0 && memoLength > 1) { //�ѱ��ڶ� �ְų� �����̻��̸�
		if (this->codeEditorForm->find->GetFindStr() == "") { //ã��â���� ã�ƺ� ������ ���ٸ�
			this->codeEditorForm->find->Create(TRUE);
		}
		else {
			if (this->codeEditorForm->find->GetSearchDown()) {
				this->codeEditorForm->find->FindDown(this->codeEditorForm->find->GetFindStr(), this->codeEditorForm->find->GetMatchCase());
			}
			else {
				this->codeEditorForm->find->FindUp(this->codeEditorForm->find->GetFindStr(), this->codeEditorForm->find->GetMatchCase());
			}
		}
	}
}