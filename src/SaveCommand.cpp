#include "SaveCommand.h"
#include <afxdlgs.h>
#include <string>
#include "CodeEditorForm.h"
#include "File.h"
#include "Glyph.h"
#include "CtrlSKeyAction.h"

SaveCommand::SaveCommand(CodeEditorForm* codeEditorForm): Command(codeEditorForm){
	this->codeEditorForm = codeEditorForm;
}

SaveCommand::~SaveCommand() {
}

void SaveCommand::Execute() {
	CtrlSKeyAction* ctrlSKeyAction = NULL;

	ctrlSKeyAction = new CtrlSKeyAction(this->codeEditorForm);
	ctrlSKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlSKeyAction;
}