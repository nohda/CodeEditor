#include "StatusCommand.h"
#include "CodeEditorForm.h"
#include "Status.h"
#include "resource.h"
#include <afxext.h>

StatusCommand::StatusCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

StatusCommand::~StatusCommand() {

}

void StatusCommand::Execute() {

	if(this->codeEditorForm->status->GetStatusBar() == NULL){ //���¹ٰ� ���ٸ�
		this->codeEditorForm->status->Create(); //���¹ٸ� �����.
	}
	else { //���¹ٸ� �����.
		this->codeEditorForm->status->Delete();
	}
}