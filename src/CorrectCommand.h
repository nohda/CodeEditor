//CorrectCommand.h

#pragma once

#ifndef _CORRECTCOMMAND_H
#define _CORRECTCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class Command;
class CorrectCommand : public Command {
public:
	CorrectCommand(CodeEditorForm* codeEditorForm);
	virtual ~CorrectCommand();
	virtual void Execute();
};
#endif //CorrectCommand