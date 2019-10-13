#include "CopyCommand.h"
#include "CodeEditorForm.h"
#include "CtrlCKeyAction.h"

CopyCommand::CopyCommand(CodeEditorForm * codeEditorForm) : Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

CopyCommand::~CopyCommand(){
}

void CopyCommand::Execute(){
	CtrlCKeyAction* ctrlCKeyAction = NULL;
	
	ctrlCKeyAction = new CtrlCKeyAction(this->codeEditorForm);
	ctrlCKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlCKeyAction;
}