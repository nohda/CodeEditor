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

	if(this->codeEditorForm->status->GetStatusBar() == NULL){ //상태바가 없다면
		this->codeEditorForm->status->Create(); //상태바를 만든다.
	}
	else { //상태바를 지운다.
		this->codeEditorForm->status->Delete();
	}
}