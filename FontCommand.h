//FontCommand.h

#pragma once

#ifndef _FONTCOMMAND_H
#define _FONTCOMMAND_H
#include "Command.h"
#include <wingdi.h>

class CodeEditorForm;
class Command;
class FontCommand: public Command {
	public:
		FontCommand(CodeEditorForm* codeEditorForm);
		virtual ~FontCommand();
		virtual void Execute();
};
#endif // !_FONTCOMMAND_H

