//HelpCommand.cpp

#include "HelpCommand.h"
#include "CodeEditorForm.h"

HelpCommand::HelpCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

HelpCommand::~HelpCommand() {
}

void HelpCommand::Execute() {
	CString path = "CodeEditor.chm";
	::ShellExecute(::GetDesktopWindow(), _T("open"), path, 0, 0, SW_SHOWMAXIMIZED);
}