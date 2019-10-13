//NextFindCommand.h

#pragma once

#ifndef _NEXTFINDCOMMAND_H
#define _NEXTFINDCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class Command;
class NextFindCommand : public Command {
public:
	NextFindCommand(CodeEditorForm* codeEditorForm);
	virtual ~NextFindCommand();
	virtual void Execute();
};
#endif //_NEXTFINDCOMMAND_H