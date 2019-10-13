#include "CommandFactory.h"
#include "FontCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "LoadCommad.h"
#include "AllSelectCommand.h"
#include "DeleteCommand.h"
#include "CopyCommand.h"
#include "PasteCommand.h"
#include "CutCommand.h"
#include "FindCommand.h"
#include "NextFindCommand.h"
#include "CorrectCommand.h"
#include "UndoCommand.h"
#include "RedoCommand.h"
#include "MoveCommand.h"
#include "StatusCommand.h"
#include "TimeOfDayCommand.h"
#include "HelpCommand.h"
#include "InformationCommand.h"

CommandFactory::CommandFactory(CodeEditorForm * codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

CommandFactory::~CommandFactory() {
}

Command* CommandFactory::Make(UINT id) {
	Command *command = NULL;

	if (id == IDM_FORMAT_FONT) {
		command = new FontCommand(this->codeEditorForm);
	}
	else if (id == IDM_FILE_SAVE) {
		command = new SaveCommand(this->codeEditorForm);
	}
	else if (id == IDM_FILE_SAVEAS) {
		command = new SaveAsCommand(this->codeEditorForm);
	}
	else if (id == IDM_FILE_LOAD) {
		command = new LoadCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_ALLSELECT) {
		command = new AllSelectCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_DELETE) {
		command = new DeleteCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_COPY) {
		command = new CopyCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_PASTE) {
		command = new PasteCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_CUT) {
		command = new CutCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_FIND) {
		command = new FindCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_NEXTFIND) {
		command = new NextFindCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_CORRECT) {
		command = new CorrectCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_UNDO) {
		command = new UndoCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_REDO) {
		command = new RedoCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_MOVE) {
		command = new MoveCommand(this->codeEditorForm);
	}
	else if (id == IDM_STATE_STATUSBAR) {
		command = new StatusCommand(this->codeEditorForm);
	}
	else if (id == IDM_EDIT_TIMEOFDAY) {
		command = new TimeOfDayCommand(this->codeEditorForm);
	}
	else if (id == IDM_HELP_INFORMATION) {
		command = new HelpCommand(this->codeEditorForm);
	}
	else if (id == IDM_HELP_ABOUT) {
		command = new InformationCommand(this->codeEditorForm);
	}

	return command;
}
