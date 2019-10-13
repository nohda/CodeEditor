//AllSelectCommand.h
#pragma once
#ifndef _ALLSELECTCOMMAND_H
#define _ALLSELECTCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class AllSelectCommand : public Command {
public:
	AllSelectCommand(CodeEditorForm* codeEditorForm);
	virtual ~AllSelectCommand();
	virtual void Execute();
};
#endif //_ALLSELECTCOMMAND_H