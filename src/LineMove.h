#pragma once
#ifndef _LINEMOVE_H
#define _LINEMOVE_H

#include "resource.h"
#include <afxwin.h>

typedef signed long int Long;

class CodeEditorForm;
class LineMove : public CDialog {
public:
	enum { IDD = IDR_MOVEDIALOG };
public:
	LineMove(CodeEditorForm* codeEditorForm = NULL);
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnMoveClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP();

private:
	CEdit edit;
	CodeEditorForm* codeEditorForm;
	Long memoCurrent;
	Long memoLength;
};

#endif //_LINEMOVE_H