#include "DeleteCommand.h"
#include "CodeEditorForm.h"
#include "DeleteKeyAction.h"

DeleteCommand::DeleteCommand(CodeEditorForm * codeEditorForm) : Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

DeleteCommand::~DeleteCommand(){

}

void DeleteCommand::Execute(){
	DeleteKeyAction* deleteKeyAction = NULL;

	deleteKeyAction = new DeleteKeyAction(this->codeEditorForm);
	deleteKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete deleteKeyAction;
}
