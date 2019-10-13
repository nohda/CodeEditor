//MoveCommand.h

#pragma once

#ifndef _MOVECOMMAND_H
#define _MOVECOMMAND_H
#include "Command.h"

class CodeEditorForm;
class Command;
class MoveCommand : public Command {
public:
	MoveCommand(CodeEditorForm* codeEditorForm);
	virtual ~MoveCommand();
	virtual void Execute();
};
#endif //_MOVECOMMAND_H