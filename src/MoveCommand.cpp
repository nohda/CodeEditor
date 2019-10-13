#include "MoveCommand.h"
#include "CodeEditorForm.h"
#include "CtrlGKeyAction.h"

MoveCommand::MoveCommand(CodeEditorForm * codeEditorForm) :Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

MoveCommand::~MoveCommand(){
}

void MoveCommand::Execute(){
	CtrlGKeyAction* ctrlGKeyAction = NULL;

	ctrlGKeyAction = new CtrlGKeyAction(this->codeEditorForm);
	ctrlGKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlGKeyAction;
}
