
#pragma once

#ifndef _WRITESTATEINSERT_H
#define _WRITESTATEINSERT_H

#include "WriteState.h"

class CodeEditorForm;
class WriteStateInsert : public WriteState {
public:
	~WriteStateInsert();
	static WriteStateInsert* WriteInsertInstance(CodeEditorForm* codeEditorForm);
	virtual void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
protected:
	WriteStateInsert(CodeEditorForm* codeEditorForm);
private:
	CodeEditorForm* codeEditorForm;
	static WriteStateInsert* instance;
};

#endif _WRITESTATEINSERT_H
