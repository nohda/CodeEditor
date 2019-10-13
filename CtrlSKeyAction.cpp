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

	if (fileName == "") { //�ѹ��� ������� �ʱ�����̸�
		state = this->codeEditorForm->file->OpenDialog(FALSE);

		if (state == FALSE) { //���� ���̾�α׿��� ������ ������ ��� ���� �������� ������.
			this->codeEditorForm->SetWindowText("������� - CodeEditorForm");
		}
		else { //���� ���̾�α׿��� ������ �ߴٸ� ������ ���ϸ����� ������ �ٲ۴�.
			pathName = this->codeEditorForm->file->GetPathName();
			fileName = this->codeEditorForm->file->GetFileName();
			this->codeEditorForm->SetWindowText(fileName.c_str());
		}
	}
	//������ �� ���¶�� �ٷ� ���̾�α׾��� �ٷ� �����Ѵ�.
	contents = this->codeEditorForm->memo->GetContents();
	this->codeEditorForm->file->Save(contents, fileName);
}