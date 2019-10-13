#include "CodeEditorFormFrame.h"
#include "CodeEditorForm.h"
#include "CommandFactory.h"
#include "Command.h"
#include "MenuUpdate.h"
#include "resource.h"
#include <afxext.h>
#include <afxcmn.h>

static const UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

BEGIN_MESSAGE_MAP(CodeEditorFormFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDM_FILE_EXIT, OnClose) //01
	ON_UPDATE_COMMAND_UI_RANGE(IDM_EDIT_UNDO, IDM_STATE_STATUSBAR, OnMenuButtonUpdate) //02 ~ 10
	ON_COMMAND_RANGE(IDM_EDIT_UNDO, IDM_HELP_ABOUT, OnMenuButtonClicked) //02 ~ 20
	//ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFind)
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()

END_MESSAGE_MAP()


CodeEditorFormFrame::CodeEditorFormFrame(){
	this->codeEditorForm = NULL;
	this->statusBar = NULL;
}

int CodeEditorFormFrame::OnCreate(LPCREATESTRUCT lpCreateStruct){
	CFrameWnd::OnCreate(lpCreateStruct);
	CRect rect;

	this->GetClientRect(rect);
	this->codeEditorForm = new CodeEditorForm;
	this->codeEditorForm->Create(NULL,NULL, WS_CHILD |WS_VISIBLE , rect,this, NULL);

	return 0;
}

void CodeEditorFormFrame::OnSize(UINT nType, int cx, int cy){
	this->codeEditorForm->SendMessage(WM_SIZE, (UINT)nType, MAKELPARAM((int)cx, (int)cy));
}

void CodeEditorFormFrame::OnMenuButtonClicked(UINT id){
	this->codeEditorForm->SendMessage(WM_COMMAND, (UINT)id,0);

	if (id == IDM_STATE_STATUSBAR) {
		SCROLLINFO si;
		this->codeEditorForm->GetScrollInfo(SB_VERT, &si);
		this->codeEditorForm->SendMessage(WM_SIZE, 0, si.nPage);
	}
}

void CodeEditorFormFrame::OnMenuButtonUpdate(CCmdUI * pCmdUI){
	MenuUpdate menuUpdate(this->codeEditorForm);

	menuUpdate.Update(pCmdUI);
}

BOOL CodeEditorFormFrame::OnEraseBkgnd(CDC* pDC) {
	return FALSE;
}

void CodeEditorFormFrame::OnSetFocus(CWnd * pOldWnd){
	this->codeEditorForm->SetFocus();
}

void CodeEditorFormFrame::OnClose(){
	int messageBox;

	messageBox = MessageBox((LPCTSTR)"저장하시겠습니까?", (LPCTSTR)"저장", MB_YESNOCANCEL);

	if (messageBox == IDYES || messageBox == IDNO) {

		if (messageBox == IDYES) {
			this->OnMenuButtonClicked(IDM_FILE_SAVE);
		}
	}
	CFrameWnd::OnClose();
}


