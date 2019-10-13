//PasteCommand.h
#pragma once
#ifndef _PASTECOMMAND_H
#define _PASTECOMMAND_H
#include "Command.h"

class CodeEditorForm;
class PasteCommand : public Command {
public:
	PasteCommand(CodeEditorForm* codeEditorForm);
	virtual ~PasteCommand();
	virtual void Execute();
};
#endif //_PASTECOMMAND_H