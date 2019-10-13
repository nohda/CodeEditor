//TimeOfDayCommand.h

#ifndef _TIMEOFDAYCOMMAND_H
#define _TIMEOFDAYCOMMAND_H

#include "Command.h"

class CodeEditorForm;
class Command;
class TimeOfDayCommand :public Command {
public:
	TimeOfDayCommand(CodeEditorForm* codeEditorForm);
	virtual ~TimeOfDayCommand();
	virtual void Execute();
};
#endif //_TIMEOFDAYCOMMAND_H