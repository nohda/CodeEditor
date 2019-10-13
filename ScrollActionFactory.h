#pragma once
//ScrollActionFactory.h
#ifndef _SCROLLACTIONFACTORY_H
#define _SCROLLACTIONFACTORY_H
#include <afxwin.h>

class CodeEditorForm;
class ScrollAction;
class ScrollActionFactory {
public:
	ScrollActionFactory(CodeEditorForm* codeEditorForm = NULL);
	~ScrollActionFactory();
	ScrollAction* Make(UINT nSBCode, BOOL isBar);
protected:
	CodeEditorForm *codeEditorForm;
};
#endif //_SCROLLACTIONFACTORY_H