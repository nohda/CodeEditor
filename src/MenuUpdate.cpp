#include "MenuUpdate.h"
#include "CodeEditorForm.h"
#include "CodeEditorFormFrame.h"
#include "Select.h"
#include "Glyph.h"
#include "resource.h"
#include "Cancellation.h"
#include "Status.h"

MenuUpdate::MenuUpdate(){
	this->codeEditorForm = 0;
}

MenuUpdate::MenuUpdate(CodeEditorForm *codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

MenuUpdate::MenuUpdate(const MenuUpdate& source) {
	this->codeEditorForm = source.codeEditorForm;
}

MenuUpdate::~MenuUpdate() {
}

void MenuUpdate::Update(CCmdUI *pCmdUI) {
	UINT ID;
	Long i = 0;
	Memory *temp = NULL;
	bool out = false;

	ID = pCmdUI->m_nID;

	if (ID == IDM_EDIT_UNDO) { //실행취소 재실행이라면
		i = this->codeEditorForm->cancellation->GetLength();
		while (i > 0 && out != true) {
			temp = this->codeEditorForm->cancellation->GetAt(i - 1);
			if (temp->status == false) {
				out = true;
			}
			i--;
		}
		if (out == false) { //실행취소가 안되다면
			pCmdUI->Enable(FALSE); //메뉴를 비활성화 한다.
		}
		else {
			pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.
		}
	}
		if (ID == IDM_EDIT_REDO) { //실행취소 재실행이라면
			i = 0;
			out = false;
			while (i < this->codeEditorForm->cancellation->GetLength() && out != true) {
				temp = this->codeEditorForm->cancellation->GetAt(i);
				if (temp->status == true) {
					out = true;
				}
				i++;
			}

			if (out == false) { //재실행이 안된다면
				pCmdUI->Enable(FALSE); //메뉴를 비활성화 한다.
			}
			else {
				pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.
			}
		}


	if (ID == IDM_EDIT_CUT || ID == IDM_EDIT_COPY || ID == IDM_EDIT_DELETE) { //잘라내기 복사 삭제라면
		if (this->codeEditorForm->select->GetStartPoint() == this->codeEditorForm->select->GetEndPoint()) { //선택영역이 없다면
			pCmdUI->Enable(FALSE); //메뉴를 비활성화 한다.

		}
		else {
			pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.
		}
	}

	if (ID == IDM_EDIT_PASTE) { //붙여넣기라면
		this->codeEditorForm->OpenClipboard();
		HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);

		if (h_clipboard_data == NULL) { //클립보드에 글자가 없다면

			pCmdUI->Enable(FALSE); //메뉴를 비활성화 한다.
		}
		else {
			pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.
		}
		::CloseClipboard();
	}

	if (ID == IDM_EDIT_FIND || ID == IDM_EDIT_NEXTFIND) { //찾기 다음찾기라면
		if (this->codeEditorForm->current->GetLength() < 1 && this->codeEditorForm->memo->GetLength() < 2) { //글자와 줄을 확인 후
			pCmdUI->Enable(FALSE); //메뉴를 비활성화 한다.
		}
		else {
			pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.
		}
	}

	if (ID == IDM_STATE_STATUSBAR) { //상태 표시줄이라면
		pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.	
		CodeEditorFormFrame *pFrame = (CodeEditorFormFrame*)AfxGetMainWnd();

		if (pFrame->GetMessageBar() != NULL) { //스테이터스바가 있다면
			pCmdUI->SetCheck(TRUE); //메뉴를 체크한다.
		}
		else {
			pCmdUI->SetCheck(FALSE); //메뉴를 체크해제한다.
		}
	}

	if (ID == IDM_HELP_INFORMATION) { //도움말 정보라면
		pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.
	}

	if (ID == IDM_HELP_ABOUT) { //프로그램 정보라면
		pCmdUI->Enable(TRUE); //메뉴를 활성화 한다.
	}
}

MenuUpdate& MenuUpdate::operator=(const MenuUpdate& source) {
	this->codeEditorForm = source.codeEditorForm;

	return *this;
}