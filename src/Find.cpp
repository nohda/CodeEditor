#include "Find.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Select.h"
#include "Cancellation.h"
#include <cctype>
#include <algorithm>
#include <afxdlgs.h>

Find::Find() {
	this->codeEditorForm = 0;
	this->findDialog = 0;
	this->findStr = "";
	this->correctStr = "";
	this->searchDown = FALSE;
	this->matchCase = FALSE;
	this->sw = FALSE;
}

Find::Find(CodeEditorForm * codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
	this->findDialog = NULL;
	this->findStr = "";
	this->correctStr = "";
	this->searchDown = FALSE;
	this->matchCase = FALSE;
	this->sw = FALSE;
}

Find::Find(const Find & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->findDialog = source.findDialog;
	this->findStr = source.findStr;
	this->correctStr = source.correctStr;
	this->searchDown = source.searchDown;
	this->matchCase = source.matchCase;
	this->sw = source.sw;
}

Find::~Find() {
	if (this->findDialog != NULL) {
		this->findDialog = NULL;
	}
}


void Find::Create(BOOL find) {

	if (this->findDialog == NULL) { //찾기창이 없다면 모달리스형 다이얼로그를 생성한다.
		this->findDialog = new CFindReplaceDialog;
		this->findDialog->Create(find, this->findStr.c_str(), this->correctStr.c_str(), FR_DOWN | FR_HIDEWHOLEWORD, this->codeEditorForm); //find가 TRUE면 찾기, FALSE면 바꾸기창
		this->findDialog->m_fr.lStructSize = sizeof(FINDREPLACE); //다이얼로그의 정보를 세팅한다.
		this->findDialog->m_fr.hwndOwner = this->codeEditorForm->m_hWnd;
		this->findDialog->m_fr.lpstrFindWhat = const_cast<char *>(this->findStr.c_str());
		this->findDialog->m_fr.lpstrReplaceWith = const_cast<char *>(this->correctStr.c_str());
		//this->findDialog->GetDlgItem(480)->SetFocus();
		

	}
	else { //찾기창이 있다면 포커스만 옮겨준다.
		//this->findDialog->SetFocus();
		
	}

#if 0
	while (GetMessage(&msg, 0, 0, 0) && this->findDialog != NULL) {
		//this->codeEditorForm->hwnd
		//문제1 창전환이 불가능해짐
		//0
		//문제1 찾기 띄워질때 포커스
		if (!IsDialogMessage(this->findDialog->GetSafeHwnd(), &msg)) { //찾기 메세지가 아니면
			if (!TranslateMDISysAccel(this->findDialog->GetSafeHwnd(), &msg)) { //메세지가 아니면
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	while (GetMessage(&msg, this->findDialog->GetSafeHwnd(), 0, 0)) {
		if (!IsWindow(this->findDialog->GetSafeHwnd()) || !IsDialogMessage(this->findDialog->GetSafeHwnd(), &msg)) {
			if (!TranslateMDISysAccel(this->findDialog->GetSafeHwnd(), &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
#endif
}

void Find::Delete() {
	if (this->findDialog != NULL) {
		this->findStr = (LPCTSTR)this->findDialog->GetFindString();
		this->correctStr = (LPCTSTR)this->findDialog->GetReplaceString();
		this->searchDown = this->findDialog->SearchDown();
		this->matchCase = this->findDialog->MatchCase();
		this->findDialog = NULL;
	}
}

void Find::FindUp(string findContents, BOOL match) {
	Glyph* letter;
	char temp[3] = { 0, };
	Long memoCurrent;
	Long memoCurrentX;
	Long memoTemp;
	Long memoLength;
	Long lineCurrent;
	Long lineTemp;
	Long previousTemp;
	Long length = 0;
	Long i = 0;
	Long j;
	Long start = 0;
	string searchWord;
	string content;
	string notFind = "\"\"을(를) 찾을 수 없습니다.";
	BOOL findStr = FALSE;
	BOOL notStr = FALSE;
	BOOL select = FALSE;

	while (i < (LONG)findContents.length()) { //찾을 글자들에서 한글영문 개수 당 공통으로 length를 1로 구한다. abc면 length는 3, 김영재면 length는 3, a영재면 length는 3
		temp[0] = LOBYTE(LOWORD(findContents[i]));

		if (Long(temp[0]) >= 32 && Long(temp[0]) <= 126 || Long(temp[0]) == 9) {
		}
		else {
			i++;
		}
		length++;
		i++;
	}

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	memoTemp = memoCurrent;
	lineTemp = lineCurrent;
	previousTemp = lineTemp;

	if (this->codeEditorForm->select->GetStartPoint() != this->codeEditorForm->select->GetEndPoint()) {
		select = true;
		start = this->codeEditorForm->select->GetStartPoint().x;
		this->codeEditorForm->select->Reset();
		lineCurrent = this->codeEditorForm->current->Previous();
	}

	while (memoCurrent >= 0 && findStr == FALSE && notStr == FALSE) {
		i = 0;

		while (lineCurrent - length > -1 && findStr == FALSE) {
			searchWord = "";
			j = 0;

			while (j < length) { //글자수만큼 반복한다.
				letter = this->codeEditorForm->current->GetAt(lineCurrent - 1);
				content = letter->GetContents(); //글자들을 만든다.
				searchWord.insert(0, content);
				lineCurrent = this->codeEditorForm->current->Previous();
				j++;
			}

			if (match == FALSE) { //대소문자를 구분하지않고 찾는다면
				string temp = findContents;
				string temp2 = searchWord;

				std::transform(temp.begin(), temp.end(), temp.begin(), tolower);
				std::transform(temp2.begin(), temp2.end(), temp2.begin(), tolower);

				if (_stricmp(temp.c_str(), temp2.c_str()) == 0) {
					findStr = TRUE;
				}
			} //대소문자를 구분하고 찾는다면
			else if (findContents == searchWord) {
				this->codeEditorForm->current->Move(lineCurrent + length); //현재위치를 i번째로 이동
				findStr = TRUE;
			}

			if (findStr == TRUE) {
				start = lineCurrent;
			}
			else { //일치하지 않았다면 커런트를 이동시킨다.
				i++;
				lineCurrent = this->codeEditorForm->current->Move(lineTemp - i);
			}
		}

		if (findStr == FALSE) { //한줄 검색해도 못찾았다면 이전줄로 이동
			memoCurrentX = this->codeEditorForm->memo->Previous();

			if (memoCurrent == memoCurrentX) {
				notStr = TRUE; //첫번째줄에 첫번째 위치까지 가도 찾을 수 없음
			}
			else {
				memoCurrent = memoCurrentX;
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //현재줄을 변경
				lineCurrent = this->codeEditorForm->current->Last(); //현재줄의 마지막으로 이동
				lineTemp = lineCurrent;
			}
		}
	}

	if (findStr == TRUE) { //찾은 문자열을 선택한다.
		this->sw = FALSE;
		this->codeEditorForm->select->StartArea(CPoint(start, memoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(start + length, memoCurrent));
		this->codeEditorForm->current->Move(lineCurrent + length);
	}
	else if (notStr == TRUE) { //찾지 못했다면 찾기 이전 n번째줄의 n번째 위치로 돌아간다.
		this->sw = TRUE;
		memoCurrent = this->codeEditorForm->memo->Move(memoTemp);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
		this->codeEditorForm->current->Move(previousTemp);

		if (select == TRUE) { //이전에 선택영역이 있었다면 되돌린다.
			this->codeEditorForm->select->StartArea(CPoint(start, memoTemp));
			this->codeEditorForm->select->EndArea(CPoint(start + length, memoTemp));
			this->codeEditorForm->current->Move(start + length);
		}
		notFind.insert(1, findContents);

		if (this->findDialog != NULL) { //찾기창을 띄우고 찾는지 다음찾기로 찾는지 확인한다.
			MessageBox(this->findDialog->m_hWnd, notFind.c_str(), "CodeEditorForm", MB_OK);
		}
		else {
			MessageBox(this->codeEditorForm->m_hWnd, notFind.c_str(), "CodeEditorForm", MB_OK);
		}
	}
}

BOOL Find::FindDown(string findContents, BOOL match, BOOL allCorrect) {
	Glyph* letter;
	char temp[3] = { 0, };
	Long memoCurrent;
	Long memoCurrentX;
	Long memoTemp;
	Long memoLength;
	Long lineCurrent;
	Long lineTemp;
	Long previousTemp;
	Long length = 0;
	Long i = 0;;
	Long j;
	Long end;
	Long start;
	string content;
	string searchWord;
	string notFind = "\"\"을(를) 찾을 수 없습니다.";
	BOOL findStr = FALSE;
	BOOL notStr = FALSE;
	BOOL select = FALSE;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	memoTemp = memoCurrent;
	lineTemp = lineCurrent;
	previousTemp = lineTemp;

	while (i < (LONG)findContents.length()) { //찾을 글자들에서 한글영문 개수 당 공통으로 length를 1로 구한다. abc면 length는 3, 김영재면 length는 3, a영재면 length는 3
		temp[0] = LOBYTE(LOWORD(findContents[i]));

		if (Long(temp[0]) >= 32 && Long(temp[0]) <= 126 || Long(temp[0]) == 9) {
		}
		else {
			i++;
		}
		length++;
		i++;
	}

	if (this->codeEditorForm->select->GetStartPoint() != this->codeEditorForm->select->GetEndPoint()) {
		end = this->codeEditorForm->select->GetEndPoint().x;
	}

	while (memoCurrent < memoLength && findStr == false && notStr == FALSE) { //줄개수만큼 반복한다.
		i = 0;

		while (lineCurrent + length <= this->codeEditorForm->current->GetLength() && findStr == FALSE) { //찾는 글자의 길이를 고려하며 줄의 끝인지 확인한다.
			searchWord = "";
			j = 0;

			while (j < length) { //글자수만큼 반복한다.
				letter = this->codeEditorForm->current->GetAt(lineCurrent); //글자를 뽑는다.
				content = letter->GetContents();
				searchWord += content; //글자들을 만든다.
				lineCurrent = this->codeEditorForm->current->Next();
				j++;
			}

			if (match == FALSE) { //대소문자를 구분하지 않고 일치한다면
				string temp = findContents;
				string temp2 = searchWord;

				std::transform(temp.begin(), temp.end(), temp.begin(), tolower); //찾기에서 입력한 문자들과 뽑아낸 글자들을 모두 소문자로 변경한다.
				std::transform(temp2.begin(), temp2.end(), temp2.begin(), tolower);

				if (_stricmp(temp.c_str(), temp2.c_str()) == 0) {
					findStr = TRUE;
				}
			}
			else if (findContents == searchWord) { //대소문자를 구분하고 일치한다면
				findStr = TRUE;
			}

			if (findStr == TRUE) { //일치한다면 선택시킬 영역을 알아낸다.
				start = lineCurrent - length;
			}
			else { //일치하지 않았다면 커런트를 이동시킨다.
				i++;
				lineCurrent = this->codeEditorForm->current->Move(lineTemp + i);
			}
		}

		if (findStr == FALSE) { //한줄 검색해도 못찾았다면 다음줄로 이동
			memoCurrentX = this->codeEditorForm->memo->Next();

			if (memoCurrent == memoCurrentX) {
				notStr = TRUE; //마지막줄에 마지막위치까지 가도 찾을 수 없음
			}
			else {
				memoCurrent = memoCurrentX;
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //현재줄을 변경
				lineCurrent = this->codeEditorForm->current->First(); //현재줄의 처음으로 이동
				lineTemp = 0;
			}
		}
	}

	if (findStr == TRUE) { //찾은 문자열을 선택한다.
		this->sw = FALSE;
		this->codeEditorForm->select->StartArea(CPoint(start, memoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(start + length, memoCurrent));
	}
	else if (notStr == TRUE) { //찾지 못했다면 찾기 이전 n번째줄의 n번째 위치로 돌아간다.
		this->sw = TRUE;
		memoCurrent = this->codeEditorForm->memo->Move(memoTemp);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
		this->codeEditorForm->current->Move(previousTemp);

		if (select == TRUE) { //이전에 선택영역이 있었다면 되돌린다.
			this->codeEditorForm->select->StartArea(CPoint(lineTemp - length, memoTemp));
			this->codeEditorForm->select->EndArea(CPoint(end, memoTemp));
		}
		notFind.insert(1, findContents);

		//찾기창을 띄우고 찾는지 다음찾기로 찾는지 확인한다.
		if (this->findDialog != NULL) { //allCorrect가 true인 경우는 모두 바꾸기에서 메시지박스를 안띄우기 위함
			if (allCorrect == FALSE) {
				MessageBox(this->findDialog->m_hWnd, notFind.c_str(), "CodeEditorForm", MB_OK);
			}
		}
		else {
			MessageBox(this->codeEditorForm->m_hWnd, notFind.c_str(), "CodeEditorForm", MB_OK);
		}
	}

	return notStr;
}

BOOL Find::Correct(string findContents, string correctContents, BOOL match, BOOL allCorrect) {
	Glyph* letter;
	char temp[3] = { 0, };
	char content[3] = { 0, };
	Long memoCurrent;
	Long memoLength;
	Long lineCurrent;
	Long lineCurrentX;
	Long memoTemp;
	Long lineTemp;
	Long findLength = 0;
	Long correctLength = 0;
	Long remove;
	Long i = 0;
	Long j = 0;
	BOOL all = TRUE;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	memoTemp = memoCurrent;
	lineTemp = lineCurrent;

	while (i < (LONG)findContents.length()) { //찾을 글자들에서 한글영문 개수 당 공통으로 length를 1로 구한다. abc면 length는 3, 김영재면 length는 3, a영재면 length는 3
		temp[0] = LOBYTE(LOWORD(findContents[i]));

		if (Long(temp[0]) >= 32 && Long(temp[0]) <= 126 || Long(temp[0]) == 9) {
		}
		else {
			i++;
		}
		findLength++;
		i++;
	}
	i = 0;

	while (i < (LONG)correctContents.length()) {
		temp[0] = LOBYTE(LOWORD(correctContents[i]));

		if (Long(temp[0]) >= 32 && Long(temp[0]) <= 126 || Long(temp[0]) == 9) {
		}
		else {
			i++;
		}
		correctLength++;
		i++;
	}

	if (this->sw == FALSE && this->codeEditorForm->select->GetStartPoint() == this->codeEditorForm->select->GetEndPoint()) { //단어를 찾지 않았다면 찾는다.
		all = this->FindDown(findContents, match, allCorrect);
		lineCurrentX = this->codeEditorForm->current->GetCurrent(); //함수로 호출해서 단어를 찾으므로 커런트를 다시 구한다.

		if (lineCurrent != lineCurrentX) {
			lineCurrent = lineCurrentX;
		}
	}

	else if (this->sw == FALSE && this->codeEditorForm->select->GetStartPoint() != this->codeEditorForm->select->GetEndPoint()) { //단어를 찾았고 선택되어있다면 바꾼다.

		remove = lineCurrent;
		i = 0;
		this->codeEditorForm->cancellation->UndoPush(3);
		while (i < findLength) { //찾은 문자의 개수만큼 지운다.
			if (this->codeEditorForm->current->GetCurrent() >= 0) { //처음이 아니라면

				if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
					this->codeEditorForm->current->Previous();
				}

				this->codeEditorForm->current->Remove(remove - 1);
				remove--;
				i++;
			}
		}
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		i = 0;
		this->codeEditorForm->cancellation->UndoPush(1, correctContents, lineCurrent);
		while (i < correctLength) { //바꿀 문자의 개수만큼 입력한다.
			content[0] = LOBYTE(LOWORD(correctContents[i + j])); //바꿀 단어의 i번째 위치의 글자를 구한다

			if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) {
				letter = new SingleByteLetter(content[0]);
			}
			else {
				j++;
				content[1] = LOBYTE(LOWORD(correctContents[i + j]));
				letter = new DoubleByteLetter(content);
			}

			if (lineCurrent == this->codeEditorForm->current->GetLength()) { //현재위치 뒤에 글자가 없다면 Append
				this->codeEditorForm->current->Add(letter);
			}
			else {  //현재위치 뒤에 글자가 있다면 Insert
				this->codeEditorForm->current->Add(letter, lineCurrent);
			}
			lineCurrent++;
			i++;
		}

		this->codeEditorForm->select->StartArea(CPoint(lineCurrent - correctLength, memoTemp)); //바꾼 글자를 선택한다.
		this->codeEditorForm->select->EndArea(CPoint(lineCurrent, memoTemp));
		this->codeEditorForm->Invalidate();
		all = this->FindDown(findContents, match, allCorrect);
	}
	else {
		all = this->FindDown(findContents, match, allCorrect);
	}

	return all;
}

void Find::AllCorrect(string findContents, string correctContents, BOOL match) {
	Long memoCurrent;
	BOOL stop = FALSE;

	//선택영역이 있다면 초기화하고 첫줄의 첫칸으로 이동한다.
	this->codeEditorForm->select->Reset();
	memoCurrent = this->codeEditorForm->memo->First();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->First();

	//모두 바꿀때까지 반복한다.
	while (stop == FALSE) {
		stop = this->Correct(findContents, correctContents, match, TRUE);
	}

	this->codeEditorForm->select->Reset(); //바꾸고나면 선택영역이 지정되므로 리셋한다.
	this->sw = FALSE;
}

Find & Find::operator=(const Find & source) {
	this->codeEditorForm = source.codeEditorForm;
	this->findDialog = source.findDialog;
	this->findStr = source.findStr;
	this->correctStr = source.correctStr;
	this->searchDown = source.searchDown;
	this->matchCase = source.matchCase;
	this->sw = source.sw;

	return *this;
}