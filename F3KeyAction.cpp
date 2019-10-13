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

	if ((lineLength > 0 && memoLength > 0) || lineLength >= 0 && memoLength > 1) { //한글자라도 있거나 두줄이상이면
		if (this->codeEditorForm->find->GetFindStr() == "") { //찾기창에서 찾아본 내역이 없다면
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