//KeyActionFactory.h
#ifndef _KEYACTIONFACTORY_H
#define _KEYACTIONFACTORY_H
#include <afxwin.h>

class CodeEditorForm;
class KeyAction;
class KeyActionFactory {
public:
	KeyActionFactory(CodeEditorForm* codeEditorForm = NULL);
	~KeyActionFactory();
	KeyAction* Make(UINT nChar);
protected:
	CodeEditorForm *codeEditorForm;
};
#endif // _KEYACTIONFACTORY_H
