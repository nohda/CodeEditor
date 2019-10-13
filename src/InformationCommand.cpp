//InformationCommand.cpp

#include "InformationCommand.h"
#include "CodeEditorForm.h"
#include "InforMation.h"

InformationCommand::InformationCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

InformationCommand::~InformationCommand() {
}

void InformationCommand::Execute() {
	InforMation cDialog(this->codeEditorForm);

	cDialog.DoModal();
}