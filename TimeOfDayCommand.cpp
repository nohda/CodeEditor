//TimeOfDayCommand.cpp

#include "TimeOfDayCommand.h"
#include "CodeEditorForm.h"
#include "F5KeyAction.h"

TimeOfDayCommand::TimeOfDayCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm){
	this->codeEditorForm = codeEditorForm;
}

TimeOfDayCommand::~TimeOfDayCommand() {
}

void TimeOfDayCommand::Execute() {
	F5KeyAction* f5KeyAction = NULL;

	f5KeyAction = new F5KeyAction(this->codeEditorForm);
	f5KeyAction->OnKeyDown(NULL, NULL, NULL);
	delete f5KeyAction;
}