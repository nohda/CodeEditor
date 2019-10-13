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

	if (this->findDialog == NULL) { //ã��â�� ���ٸ� ��޸����� ���̾�α׸� �����Ѵ�.
		this->findDialog = new CFindReplaceDialog;
		this->findDialog->Create(find, this->findStr.c_str(), this->correctStr.c_str(), FR_DOWN | FR_HIDEWHOLEWORD, this->codeEditorForm); //find�� TRUE�� ã��, FALSE�� �ٲٱ�â
		this->findDialog->m_fr.lStructSize = sizeof(FINDREPLACE); //���̾�α��� ������ �����Ѵ�.
		this->findDialog->m_fr.hwndOwner = this->codeEditorForm->m_hWnd;
		this->findDialog->m_fr.lpstrFindWhat = const_cast<char *>(this->findStr.c_str());
		this->findDialog->m_fr.lpstrReplaceWith = const_cast<char *>(this->correctStr.c_str());
		//this->findDialog->GetDlgItem(480)->SetFocus();
		

	}
	else { //ã��â�� �ִٸ� ��Ŀ���� �Ű��ش�.
		//this->findDialog->SetFocus();
		
	}

#if 0
	while (GetMessage(&msg, 0, 0, 0) && this->findDialog != NULL) {
		//this->codeEditorForm->hwnd
		//����1 â��ȯ�� �Ұ�������
		//0
		//����1 ã�� ������� ��Ŀ��
		if (!IsDialogMessage(this->findDialog->GetSafeHwnd(), &msg)) { //ã�� �޼����� �ƴϸ�
			if (!TranslateMDISysAccel(this->findDialog->GetSafeHwnd(), &msg)) { //�޼����� �ƴϸ�
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
	string notFind = "\"\"��(��) ã�� �� �����ϴ�.";
	BOOL findStr = FALSE;
	BOOL notStr = FALSE;
	BOOL select = FALSE;

	while (i < (LONG)findContents.length()) { //ã�� ���ڵ鿡�� �ѱۿ��� ���� �� �������� length�� 1�� ���Ѵ�. abc�� length�� 3, �迵��� length�� 3, a����� length�� 3
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

			while (j < length) { //���ڼ���ŭ �ݺ��Ѵ�.
				letter = this->codeEditorForm->current->GetAt(lineCurrent - 1);
				content = letter->GetContents(); //���ڵ��� �����.
				searchWord.insert(0, content);
				lineCurrent = this->codeEditorForm->current->Previous();
				j++;
			}

			if (match == FALSE) { //��ҹ��ڸ� ���������ʰ� ã�´ٸ�
				string temp = findContents;
				string temp2 = searchWord;

				std::transform(temp.begin(), temp.end(), temp.begin(), tolower);
				std::transform(temp2.begin(), temp2.end(), temp2.begin(), tolower);

				if (_stricmp(temp.c_str(), temp2.c_str()) == 0) {
					findStr = TRUE;
				}
			} //��ҹ��ڸ� �����ϰ� ã�´ٸ�
			else if (findContents == searchWord) {
				this->codeEditorForm->current->Move(lineCurrent + length); //������ġ�� i��°�� �̵�
				findStr = TRUE;
			}

			if (findStr == TRUE) {
				start = lineCurrent;
			}
			else { //��ġ���� �ʾҴٸ� Ŀ��Ʈ�� �̵���Ų��.
				i++;
				lineCurrent = this->codeEditorForm->current->Move(lineTemp - i);
			}
		}

		if (findStr == FALSE) { //���� �˻��ص� ��ã�Ҵٸ� �����ٷ� �̵�
			memoCurrentX = this->codeEditorForm->memo->Previous();

			if (memoCurrent == memoCurrentX) {
				notStr = TRUE; //ù��°�ٿ� ù��° ��ġ���� ���� ã�� �� ����
			}
			else {
				memoCurrent = memoCurrentX;
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //�������� ����
				lineCurrent = this->codeEditorForm->current->Last(); //�������� ���������� �̵�
				lineTemp = lineCurrent;
			}
		}
	}

	if (findStr == TRUE) { //ã�� ���ڿ��� �����Ѵ�.
		this->sw = FALSE;
		this->codeEditorForm->select->StartArea(CPoint(start, memoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(start + length, memoCurrent));
		this->codeEditorForm->current->Move(lineCurrent + length);
	}
	else if (notStr == TRUE) { //ã�� ���ߴٸ� ã�� ���� n��°���� n��° ��ġ�� ���ư���.
		this->sw = TRUE;
		memoCurrent = this->codeEditorForm->memo->Move(memoTemp);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
		this->codeEditorForm->current->Move(previousTemp);

		if (select == TRUE) { //������ ���ÿ����� �־��ٸ� �ǵ�����.
			this->codeEditorForm->select->StartArea(CPoint(start, memoTemp));
			this->codeEditorForm->select->EndArea(CPoint(start + length, memoTemp));
			this->codeEditorForm->current->Move(start + length);
		}
		notFind.insert(1, findContents);

		if (this->findDialog != NULL) { //ã��â�� ���� ã���� ����ã��� ã���� Ȯ���Ѵ�.
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
	string notFind = "\"\"��(��) ã�� �� �����ϴ�.";
	BOOL findStr = FALSE;
	BOOL notStr = FALSE;
	BOOL select = FALSE;

	memoCurrent = this->codeEditorForm->memo->GetCurrent();
	memoLength = this->codeEditorForm->memo->GetLength();
	lineCurrent = this->codeEditorForm->current->GetCurrent();
	memoTemp = memoCurrent;
	lineTemp = lineCurrent;
	previousTemp = lineTemp;

	while (i < (LONG)findContents.length()) { //ã�� ���ڵ鿡�� �ѱۿ��� ���� �� �������� length�� 1�� ���Ѵ�. abc�� length�� 3, �迵��� length�� 3, a����� length�� 3
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

	while (memoCurrent < memoLength && findStr == false && notStr == FALSE) { //�ٰ�����ŭ �ݺ��Ѵ�.
		i = 0;

		while (lineCurrent + length <= this->codeEditorForm->current->GetLength() && findStr == FALSE) { //ã�� ������ ���̸� ����ϸ� ���� ������ Ȯ���Ѵ�.
			searchWord = "";
			j = 0;

			while (j < length) { //���ڼ���ŭ �ݺ��Ѵ�.
				letter = this->codeEditorForm->current->GetAt(lineCurrent); //���ڸ� �̴´�.
				content = letter->GetContents();
				searchWord += content; //���ڵ��� �����.
				lineCurrent = this->codeEditorForm->current->Next();
				j++;
			}

			if (match == FALSE) { //��ҹ��ڸ� �������� �ʰ� ��ġ�Ѵٸ�
				string temp = findContents;
				string temp2 = searchWord;

				std::transform(temp.begin(), temp.end(), temp.begin(), tolower); //ã�⿡�� �Է��� ���ڵ�� �̾Ƴ� ���ڵ��� ��� �ҹ��ڷ� �����Ѵ�.
				std::transform(temp2.begin(), temp2.end(), temp2.begin(), tolower);

				if (_stricmp(temp.c_str(), temp2.c_str()) == 0) {
					findStr = TRUE;
				}
			}
			else if (findContents == searchWord) { //��ҹ��ڸ� �����ϰ� ��ġ�Ѵٸ�
				findStr = TRUE;
			}

			if (findStr == TRUE) { //��ġ�Ѵٸ� ���ý�ų ������ �˾Ƴ���.
				start = lineCurrent - length;
			}
			else { //��ġ���� �ʾҴٸ� Ŀ��Ʈ�� �̵���Ų��.
				i++;
				lineCurrent = this->codeEditorForm->current->Move(lineTemp + i);
			}
		}

		if (findStr == FALSE) { //���� �˻��ص� ��ã�Ҵٸ� �����ٷ� �̵�
			memoCurrentX = this->codeEditorForm->memo->Next();

			if (memoCurrent == memoCurrentX) {
				notStr = TRUE; //�������ٿ� ��������ġ���� ���� ã�� �� ����
			}
			else {
				memoCurrent = memoCurrentX;
				this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent); //�������� ����
				lineCurrent = this->codeEditorForm->current->First(); //�������� ó������ �̵�
				lineTemp = 0;
			}
		}
	}

	if (findStr == TRUE) { //ã�� ���ڿ��� �����Ѵ�.
		this->sw = FALSE;
		this->codeEditorForm->select->StartArea(CPoint(start, memoCurrent));
		this->codeEditorForm->select->EndArea(CPoint(start + length, memoCurrent));
	}
	else if (notStr == TRUE) { //ã�� ���ߴٸ� ã�� ���� n��°���� n��° ��ġ�� ���ư���.
		this->sw = TRUE;
		memoCurrent = this->codeEditorForm->memo->Move(memoTemp);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
		this->codeEditorForm->current->Move(previousTemp);

		if (select == TRUE) { //������ ���ÿ����� �־��ٸ� �ǵ�����.
			this->codeEditorForm->select->StartArea(CPoint(lineTemp - length, memoTemp));
			this->codeEditorForm->select->EndArea(CPoint(end, memoTemp));
		}
		notFind.insert(1, findContents);

		//ã��â�� ���� ã���� ����ã��� ã���� Ȯ���Ѵ�.
		if (this->findDialog != NULL) { //allCorrect�� true�� ���� ��� �ٲٱ⿡�� �޽����ڽ��� �ȶ��� ����
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

	while (i < (LONG)findContents.length()) { //ã�� ���ڵ鿡�� �ѱۿ��� ���� �� �������� length�� 1�� ���Ѵ�. abc�� length�� 3, �迵��� length�� 3, a����� length�� 3
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

	if (this->sw == FALSE && this->codeEditorForm->select->GetStartPoint() == this->codeEditorForm->select->GetEndPoint()) { //�ܾ ã�� �ʾҴٸ� ã�´�.
		all = this->FindDown(findContents, match, allCorrect);
		lineCurrentX = this->codeEditorForm->current->GetCurrent(); //�Լ��� ȣ���ؼ� �ܾ ã���Ƿ� Ŀ��Ʈ�� �ٽ� ���Ѵ�.

		if (lineCurrent != lineCurrentX) {
			lineCurrent = lineCurrentX;
		}
	}

	else if (this->sw == FALSE && this->codeEditorForm->select->GetStartPoint() != this->codeEditorForm->select->GetEndPoint()) { //�ܾ ã�Ұ� ���õǾ��ִٸ� �ٲ۴�.

		remove = lineCurrent;
		i = 0;
		this->codeEditorForm->cancellation->UndoPush(3);
		while (i < findLength) { //ã�� ������ ������ŭ �����.
			if (this->codeEditorForm->current->GetCurrent() >= 0) { //ó���� �ƴ϶��

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
		while (i < correctLength) { //�ٲ� ������ ������ŭ �Է��Ѵ�.
			content[0] = LOBYTE(LOWORD(correctContents[i + j])); //�ٲ� �ܾ��� i��° ��ġ�� ���ڸ� ���Ѵ�

			if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) {
				letter = new SingleByteLetter(content[0]);
			}
			else {
				j++;
				content[1] = LOBYTE(LOWORD(correctContents[i + j]));
				letter = new DoubleByteLetter(content);
			}

			if (lineCurrent == this->codeEditorForm->current->GetLength()) { //������ġ �ڿ� ���ڰ� ���ٸ� Append
				this->codeEditorForm->current->Add(letter);
			}
			else {  //������ġ �ڿ� ���ڰ� �ִٸ� Insert
				this->codeEditorForm->current->Add(letter, lineCurrent);
			}
			lineCurrent++;
			i++;
		}

		this->codeEditorForm->select->StartArea(CPoint(lineCurrent - correctLength, memoTemp)); //�ٲ� ���ڸ� �����Ѵ�.
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

	//���ÿ����� �ִٸ� �ʱ�ȭ�ϰ� ù���� ùĭ���� �̵��Ѵ�.
	this->codeEditorForm->select->Reset();
	memoCurrent = this->codeEditorForm->memo->First();
	this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
	this->codeEditorForm->current->First();

	//��� �ٲܶ����� �ݺ��Ѵ�.
	while (stop == FALSE) {
		stop = this->Correct(findContents, correctContents, match, TRUE);
	}

	this->codeEditorForm->select->Reset(); //�ٲٰ��� ���ÿ����� �����ǹǷ� �����Ѵ�.
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