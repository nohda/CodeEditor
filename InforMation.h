#pragma once
#ifndef _INFORMATION_H
#define _INFORMATION_H
#define STATUS_SUCCESS (0x00000000)

#include "resource.h"
#include <afxwin.h>

typedef signed long int Long;
typedef LONG NTSTATUS, * PNTSTATUS;
typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

class CodeEditorForm;
class InforMation : public CDialog {
public:
	enum { IDD = IDR_INFORMATIONDIALOG };
public:
	InforMation(CodeEditorForm* codeEditorForm = NULL);
	virtual BOOL OnInitDialog();

protected:
	afx_msg void OnClose();
	RTL_OSVERSIONINFOW GetRealOSVersion();
	DECLARE_MESSAGE_MAP();

private:
	CodeEditorForm* codeEditorForm;
public:
	afx_msg void OnStnClickedStaticInformationText();
};

#endif //_INFORMATION_H