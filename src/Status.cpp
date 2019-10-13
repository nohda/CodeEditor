#include "Status.h"
#include "CodeEditorForm.h"
#include "CodeEditorFormFrame.h"
#include "resource.h"
#include "Glyph.h"
#include <afxext.h>
#include <afxcmn.h>

Status::Status() {
	this->codeEditorForm = NULL;
	this->status = NULL;
	this->current = 0;
	this->memoCurrent = 0;
}

Status::Status(CodeEditorForm* codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	this->status = NULL;
	this->current = 0;
	this->memoCurrent = 0;
	this->codeEditorForm->SubjectAttach(this);

}

Status::~Status(){
	this->codeEditorForm->SubjectDetach(this);
	if (this->status != NULL) {
		delete this->status;
		this->status = NULL;
	}
}

void Status::Create() {
	CString line;
	CString memo;
	Long lineCurrent;
	Long memoCurrent;
	CRect rect;
	UINT indicators[] = { IDS_STATUS_TEXT };

	CodeEditorFormFrame *pFrame = (CodeEditorFormFrame*)AfxGetMainWnd();

	pFrame->GetClientRect(rect);
	this->status = new CStatusBar;
	this->status->Create(pFrame, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM | SBARS_SIZEGRIP, AFX_IDW_STATUS_BAR); //���¹ٸ� �����.
	this->status->SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)); //���¸� ǥ�� �� ID�� ID�� ������ �����Ѵ�.
	this->status->SetPaneInfo(0, IDS_STATUS_TEXT, SBPS_NORMAL, rect.right); //ǥ�� �� �簢 �ڽ��� ���̸� �����Ѵ�. �ϴ��� ���� ����

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	memoCurrent = this->codeEditorForm->memo->GetCurrent();

	if (lineCurrent == -1) {
		lineCurrent = 1;
	}
	else {
		lineCurrent++;
	}

	//���¹��� �ؽ�Ʈ�� �����Ѵ�.
	memo.Format(_T(" %d"), lineCurrent);
	memo.Insert(0, "Col");
	line.Format(_T("%d ,"), memoCurrent += 1);
	line.Insert(0, " Line ");
	memo.Insert(0, line);
	this->status->SetPaneText(0, memo);
	pFrame->ShowControlBar(this->status, TRUE, FALSE); //���¹ٸ� �����ش�.
}

void Status::Delete() {
	if (this->status != NULL) {
		delete this->status;
		this->status = NULL;
	}
}

void Status::Update() {
	CodeEditorFormFrame *pFrame = (CodeEditorFormFrame*)AfxGetMainWnd();

	if (pFrame->GetMessageBar() != NULL) { //���¹ٰ� �ִٸ� �����Ѵ�.
		this->Delete();
		this->Create();
	}
}