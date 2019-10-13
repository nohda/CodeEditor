//RedoCommand.h

#pragma once

#ifndef _REDOCOMMAND_H
#define _REDOCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class Command;
class RedoCommand : public Command {
public:
	RedoCommand(CodeEditorForm* codeEditorForm);
	virtual ~RedoCommand();
	virtual void Execute();
};
#endif // !_REDOCOMMAND_H