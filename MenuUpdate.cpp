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

	if (ID == IDM_EDIT_UNDO) { //������� ������̶��
		i = this->codeEditorForm->cancellation->GetLength();
		while (i > 0 && out != true) {
			temp = this->codeEditorForm->cancellation->GetAt(i - 1);
			if (temp->status == false) {
				out = true;
			}
			i--;
		}
		if (out == false) { //������Ұ� �ȵǴٸ�
			pCmdUI->Enable(FALSE); //�޴��� ��Ȱ��ȭ �Ѵ�.
		}
		else {
			pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.
		}
	}
		if (ID == IDM_EDIT_REDO) { //������� ������̶��
			i = 0;
			out = false;
			while (i < this->codeEditorForm->cancellation->GetLength() && out != true) {
				temp = this->codeEditorForm->cancellation->GetAt(i);
				if (temp->status == true) {
					out = true;
				}
				i++;
			}

			if (out == false) { //������� �ȵȴٸ�
				pCmdUI->Enable(FALSE); //�޴��� ��Ȱ��ȭ �Ѵ�.
			}
			else {
				pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.
			}
		}


	if (ID == IDM_EDIT_CUT || ID == IDM_EDIT_COPY || ID == IDM_EDIT_DELETE) { //�߶󳻱� ���� �������
		if (this->codeEditorForm->select->GetStartPoint() == this->codeEditorForm->select->GetEndPoint()) { //���ÿ����� ���ٸ�
			pCmdUI->Enable(FALSE); //�޴��� ��Ȱ��ȭ �Ѵ�.

		}
		else {
			pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.
		}
	}

	if (ID == IDM_EDIT_PASTE) { //�ٿ��ֱ���
		this->codeEditorForm->OpenClipboard();
		HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);

		if (h_clipboard_data == NULL) { //Ŭ�����忡 ���ڰ� ���ٸ�

			pCmdUI->Enable(FALSE); //�޴��� ��Ȱ��ȭ �Ѵ�.
		}
		else {
			pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.
		}
		::CloseClipboard();
	}

	if (ID == IDM_EDIT_FIND || ID == IDM_EDIT_NEXTFIND) { //ã�� ����ã����
		if (this->codeEditorForm->current->GetLength() < 1 && this->codeEditorForm->memo->GetLength() < 2) { //���ڿ� ���� Ȯ�� ��
			pCmdUI->Enable(FALSE); //�޴��� ��Ȱ��ȭ �Ѵ�.
		}
		else {
			pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.
		}
	}

	if (ID == IDM_STATE_STATUSBAR) { //���� ǥ�����̶��
		pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.	
		CodeEditorFormFrame *pFrame = (CodeEditorFormFrame*)AfxGetMainWnd();

		if (pFrame->GetMessageBar() != NULL) { //�������ͽ��ٰ� �ִٸ�
			pCmdUI->SetCheck(TRUE); //�޴��� üũ�Ѵ�.
		}
		else {
			pCmdUI->SetCheck(FALSE); //�޴��� üũ�����Ѵ�.
		}
	}

	if (ID == IDM_HELP_INFORMATION) { //���� �������
		pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.
	}

	if (ID == IDM_HELP_ABOUT) { //���α׷� �������
		pCmdUI->Enable(TRUE); //�޴��� Ȱ��ȭ �Ѵ�.
	}
}

MenuUpdate& MenuUpdate::operator=(const MenuUpdate& source) {
	this->codeEditorForm = source.codeEditorForm;

	return *this;
}