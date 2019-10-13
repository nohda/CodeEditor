//LineMove.cpp
#include "LineMove.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

BEGIN_MESSAGE_MAP(LineMove, CDialog)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDOK, OnMoveClicked)
	ON_BN_CLICKED(IDCANCEL, OnClose)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

LineMove::LineMove(CodeEditorForm* codeEditorForm) :CDialog(LineMove::IDD, codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	this->memoCurrent = 0;
	this->memoLength = 0;
}

void LineMove::DoDataExchange(CDataExchange* pDX) {
	DDX_Control(pDX, IDC_STATIC_MOVENUMBER, this->edit); //EDit의 주소를 얻는다. (SetSel을 위함)
}

BOOL LineMove::OnInitDialog() {
	CDialog::OnInitDialog(); //오버라이딩
	BOOL sw = TRUE;
	MSG msg;

	this->memoLength = this->codeEditorForm->memo->GetLength(); //줄의 갯수를 알아낸다.
	this->memoCurrent = this->codeEditorForm->memo->GetCurrent(); //현재 줄번호를 알아낸다.
	this->SetDlgItemInt(IDC_STATIC_MOVENUMBER, this->memoCurrent + 1); //줄번호를 세팅한다.
	GetDlgItem(IDC_STATIC_MOVENUMBER)->SetFocus(); //에디트에 포커스를 준다.
	this->edit.SetSel(0, -1); //에디트의 수들을 전체 선택한다.

	while (sw) {
		sw = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE); //현재의 thread를 호출한 윈도우와 관련된 메시지를 보고 지운다. (큐에 있는 모든 메세지 지우기)
	}

	return FALSE;
}

void LineMove::OnMoveClicked() {
	BOOL ret = TRUE;

	this->memoCurrent = GetDlgItemInt(IDC_STATIC_MOVENUMBER); //입력한 줄번호를 알아낸다.
	this->memoCurrent -= 1; //0베이스로 맞춘다.

	if (this->memoCurrent > -1 && this->memoCurrent < this->memoLength) { //이동 가능한 줄번호라면 이동한다.
		this->codeEditorForm->memo->Move(this->memoCurrent);
		this->codeEditorForm->current->First();
	}
	else if (this->memoCurrent < 1) { //첫째 줄 번호보다 작다면
		ret = !MessageBox((LPCTSTR)"이동 가능한 줄 번호보다 작습니다", (LPCTSTR)"확인", MB_OK);
	}
	else if (this->memoCurrent >= this->memoLength) { //전체 줄 번호보다 크다면
		ret = !MessageBox((LPCTSTR)"이동 가능한 줄 번호보다 큽니다", (LPCTSTR)"확인", MB_OK);
	}

	if (ret == TRUE) { //정상적으로 이동했다면 다이얼로그를 닫는다.
		this->EndDialog(0);
	}
}

void LineMove::OnClose() {
	this->EndDialog(0);
}