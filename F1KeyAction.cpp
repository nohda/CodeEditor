#include "F1KeyAction.h"
#include "CodeEditorForm.h"

F1KeyAction::F1KeyAction(CodeEditorForm* codeEditorForm) :KeyAction(codeEditorForm) {
}

F1KeyAction::~F1KeyAction() {
}

void F1KeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	CString path = "CodeEditor.chm";
	::ShellExecute(::GetDesktopWindow(), _T("open"), path, 0, 0, SW_SHOWMAXIMIZED);
}