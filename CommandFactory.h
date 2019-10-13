//CommandFactory.h

#pragma once

#ifndef _COMMANDFACTORY_H
#define _COMMANDFACTORY_H
#include <afxwin.h>
#include "resource.h"

class CodeEditorForm;
class Command;
class CommandFactory {
	public:
		CommandFactory(CodeEditorForm* codeEditorForm);
		~CommandFactory();
		Command* Make(UINT id);

	protected:
		CodeEditorForm* codeEditorForm;
};
#endif // !_COMMANDFACTORY_H

