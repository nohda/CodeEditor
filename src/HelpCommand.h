//HelpCommand.h

#ifndef _HELPCOMMAND_H
#define _HELPCOMMAND_H

#include "Command.h"

class CodeEditorForm;
class Command;
class HelpCommand :public Command {
public:
	HelpCommand(CodeEditorForm* codeEditorForm);
	virtual ~HelpCommand();
	virtual void Execute();
};
#endif //_HELPCOMMAND_H