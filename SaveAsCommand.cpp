#include "SaveAsCommand.h"
#include <afxdlgs.h>
#include <string>
#include "CodeEditorForm.h"
#include "File.h"
#include "Glyph.h"

SaveAsCommand::SaveAsCommand(CodeEditorForm* codeEditorForm): Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

SaveAsCommand::~SaveAsCommand() {

}

void SaveAsCommand::Execute() {
	string contents;
	string pathName;
	string fileName;

	this->codeEditorForm->file->OpenDialog(FALSE);
	contents = this->codeEditorForm->memo->GetContents();
	pathName = this->codeEditorForm->file->GetPathName();

	this->codeEditorForm->file->Save(contents, pathName);
	fileName = this->codeEditorForm->file->GetFileName();
	this->codeEditorForm->SetWindowText(fileName.c_str());
}