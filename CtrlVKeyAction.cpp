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
	while (start.y != end.y || start.x != end.x) {//선택영역동안 반복한다.
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
			previous = this->codeEditorForm->memo->GetAt(end.y);//end.y번째에 있는 줄 찾기
			lineCurrent = previous->GetLength();//end.y 줄의 length만큼 글자를 옮긴다.
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

			content[0] = LOBYTE(LOWORD(contents[i])); //유니코드는 1BYTE이므로 LOBYTE사용

			if (content[0] != '\r') {

				if (content[0] != '\n' && content[0] != '\0') {

					if (Long(content[0]) >= 32 && Long(content[0]) <= 126 || Long(content[0]) == 9) { //문자 유니코드일시
						letter = new SingleByteLetter(content[0]);
					}
					else { // 한글 유니코드일시

						content[1] = LOBYTE(LOWORD(contents[i + 1])); // 한글의 사이즈인 2BYTE만큼이 필요하므로 다음번째 유니코드를 한번 더 추출
						letter = new DoubleByteLetter(content);
						i++; //다음문자를 읽어야하므로 i증가
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
					//현재줄이 끝줄이라면
					line = new Line;

					if (memoCurrent == memoLength - 1) {
						this->codeEditorForm->memo->Add(line); //줄을 붙인다.
					}
					else {
						this->codeEditorForm->memo->Add(line, memoCurrent + 1);
					}
					memoCurrent = this->codeEditorForm->memo->GetCurrent();
					this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
					previousCurrent = this->codeEditorForm->current->GetCurrent();

					////현재 위치의 뒤에 글자가 있다면 
					if (lineCurrent != lineLength) {
						if (lineCurrent != -1 && lineCurrent != lineLength) { //끼워쓰기 로직
							j = lineCurrent;

							while (j < lineLength) { //새줄에 글자 복사 로직
								letter = previous->GetAt(j);
								this->codeEditorForm->current->Add(letter->Clone());
								j++;
							}
							j = lineLength;

							while (j > lineCurrent) { //기존 줄 글자 삭제 로직
								previous->Remove(lineCurrent);
								j--;
							}
							this->codeEditorForm->current->Move(0);
						}
						else {
							j = 0;

							while (j < lineLength) { //새줄에 글자 복사 로직
								letter = previous->GetAt(j);
								this->codeEditorForm->current->Add(letter->Clone());
								j++;
							}
							j = lineLength;

							while (j > 0) { //기존 줄 글자 삭제 로직
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