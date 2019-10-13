//Command.h

#pragma once

#ifndef _COMMAND_H
#define _COMMAND_H
#include "CodeEditorForm.h"
//#include <afxwin.h>
#include <string>
//using namespace std;

class CodeEditorForm;
class Command {
	public:
		Command(CodeEditorForm* codeEdtiorForm);
		virtual ~Command() = 0;
		virtual void Execute() {};

	protected:
		CodeEditorForm *codeEditorForm;
};

#endif //_COMMAND_H

