#include "FindCommand.h"
#include "CodeEditorForm.h"
#include "CtrlFKeyAction.h"

FindCommand::FindCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

FindCommand::~FindCommand(){
}

void FindCommand::Execute(){
	CtrlFKeyAction* ctrlFKeyAction = NULL;

	ctrlFKeyAction = new CtrlFKeyAction(this->codeEditorForm);
	ctrlFKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlFKeyAction;
}