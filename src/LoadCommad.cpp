#include "LoadCommad.h"
#include <afxdlgs.h>
#include <string>
#include "CodeEditorForm.h"
#include "File.h"
#include "Glyph.h"

LoadCommand::LoadCommand(CodeEditorForm* codeEditorForm) : Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

LoadCommand::~LoadCommand() {
}

void LoadCommand::Execute() {
	int messageBox;
	string contents;
	string pathName;
	string fileName;
	string text;

	messageBox = this->codeEditorForm->MessageBox("저장하시겠습니까?", "저장", MB_YESNOCANCEL);

	switch (messageBox) {
	case IDYES:
		fileName = this->codeEditorForm->file->GetFileName();

		if (fileName == "*.txt") {
			this->codeEditorForm->file->OpenDialog(FALSE);
			pathName = this->codeEditorForm->file->GetPathName();
			fileName = this->codeEditorForm->file->GetFileName();
			this->codeEditorForm->SetWindowText(fileName.c_str());
		}

		contents = this->codeEditorForm->memo->GetContents();
		this->codeEditorForm->file->Save(contents, pathName);
		break;

	default:
		break;
	}

	this->codeEditorForm->file->OpenDialog(TRUE);
	pathName = this->codeEditorForm->file->GetPathName();
	fileName = this->codeEditorForm->file->GetFileName();

	if (pathName != "") {
		this->codeEditorForm->SetWindowText(fileName.c_str());
		text = this->codeEditorForm->file->Load(pathName);
		this->codeEditorForm->TakeIn(text);
	}
}