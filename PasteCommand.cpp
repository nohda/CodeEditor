#include "PasteCommand.h"
#include "CodeEditorForm.h"
#include "CtrlVKeyAction.h"

PasteCommand::PasteCommand(CodeEditorForm * codeEditorForm) : Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

PasteCommand::~PasteCommand(){
}

void PasteCommand::Execute(){
	CtrlVKeyAction* ctrlVKeyAction = NULL;

	ctrlVKeyAction = new CtrlVKeyAction(this->codeEditorForm);
	ctrlVKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlVKeyAction;
}
