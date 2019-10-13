//FindCommand.h

#pragma once

#ifndef _FINDCOMMAND_H
#define _FINDCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class Command;
class FindCommand : public Command {
public:
	FindCommand(CodeEditorForm* codeEditorForm);
	virtual ~FindCommand();
	virtual void Execute();
};
#endif //_FINDCOMMAND_H