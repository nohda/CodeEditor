//SaveAsCommand.h

#pragma once

#ifndef _SAVEASCOMMAND_H
#define _SAVEASCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class SaveAsCommand: public Command {
public:
	SaveAsCommand(CodeEditorForm* codeEditorForm);
	virtual ~SaveAsCommand();
	virtual void Execute();
};
#endif //_SAVEASCOMMAND_H
