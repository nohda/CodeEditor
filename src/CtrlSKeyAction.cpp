#include "CtrlSKeyAction.h"
#include "CodeEditorForm.h"
#include "File.h"
#include "Glyph.h"

CtrlSKeyAction::CtrlSKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlSKeyAction::~CtrlSKeyAction() {
}

void CtrlSKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	string fileName;
	string pathName;
	string contents;
	bool state;

	fileName = this->codeEditorForm->file->GetFileName();

	if (fileName == "") { //한번도 저장안한 초기상태이면
		state = this->codeEditorForm->file->OpenDialog(FALSE);

		if (state == FALSE) { //저장 다이얼로그에서 저장을 안했을 경우 원래 제목으로 돌린다.
			this->codeEditorForm->SetWindowText("제목없음 - CodeEditorForm");
		}
		else { //저장 다이얼로그에서 저장을 했다면 저장한 파일명으로 제목을 바꾼다.
			pathName = this->codeEditorForm->file->GetPathName();
			fileName = this->codeEditorForm->file->GetFileName();
			this->codeEditorForm->SetWindowText(fileName.c_str());
		}
	}
	//저장을 한 상태라면 바로 다이얼로그없이 바로 저장한다.
	contents = this->codeEditorForm->memo->GetContents();
	this->codeEditorForm->file->Save(contents, fileName);
}