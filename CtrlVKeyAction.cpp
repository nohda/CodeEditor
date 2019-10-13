#include "CtrlVKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Memo.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "Select.h"
#include "Cancellation.h"

CtrlVKeyAction::CtrlVKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm){
}

CtrlVKeyAction::~CtrlVKeyAction(){
}

void CtrlVKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CPoint start;
	CPoint end;
	CPoint temp;
	string contents;
	Glyph *line;
	Glyph *letter;
	char content[3] = { 0, };
	Long textSize = 0;
	Long i = 0;
	Long j = 0;
	unsigned int priority_list = CF_TEXT;
	char *p_string = NULL;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;
	Long previousCurrent;
	Glyph *previous;
	HANDLE h_clipboard_data;
	char *p_clipboard_data;
	int string_len;

	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();
	if (start != end) {

	if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
		temp = end;
		end = start;
		start = temp;

		this->codeEditorForm->memo->Move(end.y);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
		this->codeEditorForm->current->Move(end.x);
	}
		this->codeEditorForm->cancellation->UndoPush(3);
	while (start.y != end.y || start.x != end.x) {//���ÿ������� �ݺ��Ѵ�.
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		lineLength = this->codeEditorForm->current->GetLength();
		if (end.x > 0) {
			if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
				lineCurrent = this->codeEditorForm->current->Previous();
			}
			this->codeEditorForm->current->Remove(end.x - 1);
			end.x--;
		}
		else {
			previous = this->codeEditorForm->memo->GetAt(end.y);//end.y��°�� �ִ� �� ã��
			lineCurrent = previous->GetLength();//end.y ���� length��ŭ ���ڸ� �ű��.
			memoCurrent = this->codeEditorForm->memo->Previous();
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			lineLength = this->codeEditorForm->current->GetLength();
			i = 0;
			while (i < lineCurrent) {
				letter = previous->GetAt(i);
				this->codeEditorForm->current->Add(letter->Clone());
				i++;
			}
			this->codeEditorForm->memo->Remove(end.y);
			end.y--;
			end.x = lineLength;
			this->codeEditorForm->current->Move(end.x);
		}
	}
	this->codeEditorForm->current->Move(start.x);
	this->codeEditorForm->select->Reset();
	}

	this->codeEditorForm->OpenClipboard();
	h_clipboard_data = ::GetClipboardData(CF_TEXT);

	if (::GetPriorityClipboardFormat(&priority_list, 1) == CF_TEXT) {
		if (h_clipboard_data != NULL) {
			p_clipboard_data = (char *)::GlobalLock(h_clipboard_data);
			string_len = strlen(p_clipboard_data) + 1;
			p_string = new char[string_len];
			memcpy(p_string, p_clipboard_data, string_len);
			::GlobalUnlock(h_clipboard_data);
		}
		contents="";
		for (int i = 0; i < (Long)strlen(p_string); i++) {
			contents += p_string[i];
		}
		if (CF_TEXT != NULL) {
			this->codeEditorForm->cancellation->UndoPush(1, contents);
		}
		textSize = contents.length();
		while (i < textSize) {

			content[0] = LOBYTE(LOWORD(contents[i])); //�����ڵ�� 1BYTE�̹Ƿ� LOBYTE���

			if (content[0] != '\r') {

				if (content[0] != '\n' && content[0] != '\0') {

					if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) { //���� �����ڵ��Ͻ�
						letter = new SingleByteLetter(content[0]);
					}
					else { // �ѱ� �����ڵ��Ͻ�

						content[1] = LOBYTE(LOWORD(contents[i + 1])); // �ѱ��� �������� 2BYTE��ŭ�� �ʿ��ϹǷ� ������° �����ڵ带 �ѹ� �� ����
						letter = new DoubleByteLetter(content);
						i++; //�������ڸ� �о���ϹǷ� i����
					}

					lineCurrent = this->codeEditorForm->current->GetCurrent();
					if (lineCurrent == -1) {
						this->codeEditorForm->current->Add(letter);
					}
					else {
	
						this->codeEditorForm->current->Add(letter, lineCurrent);
					}
				}
				else {
					memoCurrent = this->codeEditorForm->memo->GetCurrent();
					memoLength = this->codeEditorForm->memo->GetLength();
					lineCurrent = this->codeEditorForm->current->GetCurrent();
					lineLength = this->codeEditorForm->current->GetLength();
					previous = this->codeEditorForm->current;
					//�������� �����̶��
					line = new Line;

					if (memoCurrent == memoLength - 1) {
						this->codeEditorForm->memo->Add(line); //���� ���δ�.
					}
					else {
						this->codeEditorForm->memo->Add(line, memoCurrent + 1);
					}
					memoCurrent = this->codeEditorForm->memo->GetCurrent();
					this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
					previousCurrent = this->codeEditorForm->current->GetCurrent();

					////���� ��ġ�� �ڿ� ���ڰ� �ִٸ� 
					if (lineCurrent != lineLength) {
						if (lineCurrent != -1 && lineCurrent != lineLength) { //�������� ����
							j = lineCurrent;

							while (j < lineLength) { //���ٿ� ���� ���� ����
								letter = previous->GetAt(j);
								this->codeEditorForm->current->Add(letter->Clone());
								j++;
							}
							j = lineLength;

							while (j > lineCurrent) { //���� �� ���� ���� ����
								previous->Remove(lineCurrent);
								j--;
							}
							this->codeEditorForm->current->Move(0);
						}
						else {
							j = 0;

							while (j < lineLength) { //���ٿ� ���� ���� ����
								letter = previous->GetAt(j);
								this->codeEditorForm->current->Add(letter->Clone());
								j++;
							}
							j = lineLength;

							while (j > 0) { //���� �� ���� ���� ����
								previous->Remove(j - 1);
								j--;
							}
							this->codeEditorForm->current->Move(0);
						}
					
					}
				}
			}
			i++;
		}
		
	}
	
	EmptyClipboard();
	CloseClipboard();
}