//InformationCommand.h

#ifndef _INFORMATIONCOMMAND_H
#define _INFORMATIONCOMMAND_H

#include "Command.h"

class CodeEditorForm;
class Command;
class InformationCommand :public Command {
public:
	InformationCommand(CodeEditorForm* codeEditorForm);
	virtual ~InformationCommand();
	virtual void Execute();
};
#endif //_INFORMATIONCOMMAND_H