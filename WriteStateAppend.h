#pragma once

#ifndef _WRITESTATEAPPEND_H
#define _WRITESTATEAPPEND_H

#include "WriteState.h"

class CodeEditorForm;
class WriteStateAppend: public WriteState {
public:
	~WriteStateAppend();
	static WriteStateAppend* WriteAppendInstance(CodeEditorForm* codeEditorForm);
	virtual void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
protected:
	WriteStateAppend(CodeEditorForm* codeEditorForm);
private:
	CodeEditorForm* codeEditorForm;
	static WriteStateAppend* instance;
};

#endif _WRITESTATEAPPEND_H