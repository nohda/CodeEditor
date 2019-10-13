//UndoCommand.h

#pragma once

#ifndef _UNDOCOMMAND_H
#define _UNDOCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class Command;
class UndoCommand : public Command {
public:
	UndoCommand(CodeEditorForm* codeEditorForm);
	virtual ~UndoCommand();
	virtual void Execute();
};
#endif // !_UNDOCOMMAND_H