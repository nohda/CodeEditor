//StatusCommand.h

#pragma once

#ifndef _STATUSCOMMAND_H
#define _STATUSCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class Command;
class StatusCommand : public Command {
public:
	StatusCommand(CodeEditorForm* codeEditorForm);
	virtual ~StatusCommand();
	virtual void Execute();
};
#endif //StatusCommand