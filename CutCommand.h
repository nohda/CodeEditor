//CutCommand.h
#pragma once
#ifndef _CUTCOMMAND_H
#define _CUTCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class CutCommand : public Command {
public:
	CutCommand(CodeEditorForm* codeEditorForm);
	virtual ~CutCommand();
	virtual void Execute();
};
#endif //_CUTCOMMAND_H