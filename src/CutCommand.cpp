#include "CutCommand.h"
#include "CodeEditorForm.h"
#include "CtrlXKeyAction.h"

CutCommand::CutCommand(CodeEditorForm * codeEditorForm) : Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

CutCommand::~CutCommand(){
}

void CutCommand::Execute(){
	CtrlXKeyAction* ctrlXKeyAction = NULL;

	ctrlXKeyAction = new CtrlXKeyAction(this->codeEditorForm);
	ctrlXKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlXKeyAction;
}
