#include "AllSelectCommand.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"
#include "CtrlAKeyAction.h"

AllSelectCommand::AllSelectCommand(CodeEditorForm* codeEditorForm) : Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

AllSelectCommand::~AllSelectCommand() {
}

void AllSelectCommand::Execute() {
	CtrlAKeyAction* ctrlAKeyAction = NULL;

	ctrlAKeyAction = new CtrlAKeyAction(this->codeEditorForm);
	ctrlAKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlAKeyAction;
}