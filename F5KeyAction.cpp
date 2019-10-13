//F5KeyAction.cpp

#include "CodeEditorForm.h"
#include "F5KeyAction.h"
#include "Glyph.h"
#include "SingleByteLetter.h"
#include "Cancellation.h"

F5KeyAction::F5KeyAction(CodeEditorForm* codeEditorForm) :KeyAction(codeEditorForm) {
}

F5KeyAction::~F5KeyAction() {
}

void F5KeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CTime cTime = CTime::GetCurrentTime(); // ���� �ý������κ��� ��¥ �� �ð��� ��� �´�.
	char content[3] = { 0, };
	Glyph* letter;
	CString strDate;
	CString strTime;
	Long i = 0;
	Long lineCurrent;

	strDate.Format("%04d-%02d-%02d ", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay()); //n�� n�� n���� ���Ѵ�.
	strTime.Format("%02d:%02d", cTime.GetHour(), cTime.GetMinute()); //n�� n�� n�ʸ� ���Ѵ�.
	strDate.Insert(strDate.GetLength(), strTime);

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	
	if (lineCurrent == -1) {
		lineCurrent = 0;
	}

	this->codeEditorForm->cancellation->UndoPush(1, (LPCTSTR)strDate);

	while (i < strDate.GetLength()) { //���� �� ��ŭ �ݺ��Ѵ�.
		content[0] = LOBYTE(LOWORD(strDate[i])); //���ڸ� �����.
		letter = new SingleByteLetter(content[0]);

		//������ġ �ڿ� ���ڰ� ���ٸ� Append
		if (lineCurrent == this->codeEditorForm->current->GetLength()) {
			this->codeEditorForm->current->Add(letter);
		}
		else { //������ġ �ڿ� ���ڰ� �ִٸ� Insert
			this->codeEditorForm->current->Add(letter, lineCurrent);
		}
		lineCurrent++;
		i++;
	}
}