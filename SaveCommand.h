//SaveCommand.h

#pragma once

#ifndef _SAVECOMMAND_H
#define _SAVECOMMAND_H
#include "Command.h"

class CodeEditorForm;
class SaveCommand: public Command {
public:
	SaveCommand(CodeEditorForm* codeEditorForm);
	virtual ~SaveCommand();
	virtual void Execute();
};
#endif //_SAVECOMMAND_H
