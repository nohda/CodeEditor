#include "UndoCommand.h"
#include "Cancellation.h"
#include "CtrlZKeyAction.h"

UndoCommand::UndoCommand(CodeEditorForm * codeEditorForm) : Command(codeEditorForm)
{
	this->codeEditorForm = codeEditorForm;
}

UndoCommand::~UndoCommand()
{
}

void UndoCommand::Execute(){
	CtrlZKeyAction* ctrlZKeyAction = NULL;

	ctrlZKeyAction = new CtrlZKeyAction(this->codeEditorForm);
	ctrlZKeyAction->OnKeyDown(NULL, NULL, NULL);
	delete ctrlZKeyAction;
	this->codeEditorForm->cancellation->UndoPop();
}
