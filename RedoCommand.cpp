#include "RedoCommand.h"
#include "Cancellation.h"
#include "CtrlYKeyAction.h"

RedoCommand::RedoCommand(CodeEditorForm* codeEditorForm) : Command(codeEditorForm){
	this->codeEditorForm = codeEditorForm;
}

RedoCommand::~RedoCommand(){
}

void RedoCommand::Execute(){
	CtrlYKeyAction* ctrlYKeyAction = NULL;

	ctrlYKeyAction = new CtrlYKeyAction(this->codeEditorForm);
	ctrlYKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlYKeyAction;
}
