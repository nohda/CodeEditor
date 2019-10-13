//CopyCommand.h
#pragma once
#ifndef _COPYCOMMAND_H
#define _COPYCOMMAND_H
#include "Command.h"

class CodeEditorForm;
class CopyCommand : public Command {
public:
	CopyCommand(CodeEditorForm* codeEditorForm);
	virtual ~CopyCommand();
	virtual void Execute();
};
#endif //_COPYCOMMAND_H