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
	CTime cTime = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.
	char content[3] = { 0, };
	Glyph* letter;
	CString strDate;
	CString strTime;
	Long i = 0;
	Long lineCurrent;

	strDate.Format("%04d-%02d-%02d ", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay()); //n년 n월 n일을 구한다.
	strTime.Format("%02d:%02d", cTime.GetHour(), cTime.GetMinute()); //n시 n분 n초를 구한다.
	strDate.Insert(strDate.GetLength(), strTime);

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	
	if (lineCurrent == -1) {
		lineCurrent = 0;
	}

	this->codeEditorForm->cancellation->UndoPush(1, (LPCTSTR)strDate);

	while (i < strDate.GetLength()) { //글자 수 만큼 반복한다.
		content[0] = LOBYTE(LOWORD(strDate[i])); //글자를 만든다.
		letter = new SingleByteLetter(content[0]);

		//현재위치 뒤에 글자가 없다면 Append
		if (lineCurrent == this->codeEditorForm->current->GetLength()) {
			this->codeEditorForm->current->Add(letter);
		}
		else { //현재위치 뒤에 글자가 있다면 Insert
			this->codeEditorForm->current->Add(letter, lineCurrent);
		}
		lineCurrent++;
		i++;
	}
}