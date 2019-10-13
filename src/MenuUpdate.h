#pragma once

#ifndef _MENUUPDATE_H
#define _MENUUPDATE_H

#include <afxwin.h>

class CCmdUI;
class CodeEditorForm;
class MenuUpdate {
public:
	MenuUpdate();
	MenuUpdate(CodeEditorForm *codeEditorForm);
	MenuUpdate(const MenuUpdate& source);
	~MenuUpdate();
	void Update(CCmdUI *pCmdUI);
	MenuUpdate& operator=(const MenuUpdate& source);

private:
	CodeEditorForm *codeEditorForm;
};
#endif //_MENUUPDATE_H