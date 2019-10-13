#include "NextFindCommand.h"
#include "CodeEditorForm.h"
#include "F3KeyAction.h"

NextFindCommand::NextFindCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}


NextFindCommand::~NextFindCommand(){
}

void NextFindCommand::Execute(){
	F3KeyAction* f3KeyAction = NULL;

	f3KeyAction = new F3KeyAction(this->codeEditorForm);
	f3KeyAction->OnKeyDown(NULL, NULL, NULL);
	delete f3KeyAction;
}