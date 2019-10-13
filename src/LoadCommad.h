//LoadCommand.h
#pragma once
#ifndef _LOADCOMMAND_H
#define _LOADCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class LoadCommand : public Command {
public:
	LoadCommand(CodeEditorForm* codeEditorForm);
	virtual ~LoadCommand();
	virtual void Execute();
};
#endif //_LOADCOMMAND_H