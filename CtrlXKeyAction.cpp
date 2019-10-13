#include "CtrlXKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Select.h"
#include "Cancellation.h"


CtrlXKeyAction::CtrlXKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

CtrlXKeyAction::~CtrlXKeyAction(){
}

void CtrlXKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	CPoint start;
	CPoint end;
	CPoint temp;
	Glyph *line;
	Glyph *letter;
	Glyph *previous;
	string contents = "";
	Long memoCurrent;
	Long memoLength;
	Long lineCurrent;
	Long lineLength;
	Long i = 0;
	HANDLE h_data;
	const char * content;
	char *p_data;

	start = this->codeEditorForm->select->GetStartPoint();
	end = this->codeEditorForm->select->GetEndPoint();
	
	if (start.y > end.y || (start.y == end.y && start.x > end.x)) {
		temp = end;
		end = start;
		start = temp;

		this->codeEditorForm->memo->Move(end.y);
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(end.y);
		this->codeEditorForm->current->Move(end.x);
	}
	if (start != end) {
		//this->codeEditorForm->cancellation->UndoPush(3);
		this->codeEditorForm->OpenClipboard();
		EmptyClipboard();

		memoCurrent = start.y;
		memoLength = end.y;

		while (memoCurrent <= memoLength) {
			line = this->codeEditorForm->memo->GetAt(memoCurrent);

			if (i == 0 && memoCurrent == memoLength) {
				lineCurrent = start.x;
				lineLength = end.x;
			}
			else if (i == 0 && memoCurrent != memoLength) {
				lineCurrent = start.x;
				lineLength = line->GetLength();
			}
			else if (memoCurrent == memoLength) {
				lineCurrent = 0;
				lineLength = end.x;
			}
			else {
				lineCurrent = 0;
				lineLength = line->GetLength();
			}

			while (lineCurrent < lineLength) {
				letter = line->GetAt(lineCurrent);
				contents += letter->GetContents();
				lineCurrent++;
			}
			if (memoCurrent != memoLength) {
				contents += "\r\n";
			}
			i++;
			memoCurrent++;
		}

		content = contents.c_str();
		int string_length = strlen(content) + 1;
		h_data = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, string_length);
		p_data = (char *)::GlobalLock(h_data);
		if (NULL != p_data) {
			this->codeEditorForm->cancellation->UndoPush(3, contents);
			memcpy(p_data, content, string_length);
			::GlobalUnlock(h_data);
		}
		::SetClipboardData(CF_TEXT, h_data);
		::CloseClipboard();

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
		this->codeEditorForm->select->Reset();
	}

}
