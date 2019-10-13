//DeleteCommand.h
#pragma once
#ifndef _DELETECOMMAND_H
#define _DELETECOMMAND_H
#include "Command.h"

class CodeEditorForm;
class DeleteCommand : public Command {
public:
	DeleteCommand(CodeEditorForm* codeEditorForm);
	virtual ~DeleteCommand();
	virtual void Execute();
};
#endif //_DELETECOMMAND_H