#include "CorrectCommand.h"
#include "CodeEditorForm.h"
#include "CtrlHKeyAction.h"

CorrectCommand::CorrectCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

CorrectCommand::~CorrectCommand() {
}

void CorrectCommand::Execute() {
	CtrlHKeyAction* ctrlHKeyAction = NULL;

	ctrlHKeyAction = new CtrlHKeyAction(this->codeEditorForm);
	ctrlHKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlHKeyAction;
}